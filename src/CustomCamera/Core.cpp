#include "CustomCamera/Core.h"
#include "CustomCamera/CoreData.h"

namespace CustomCamera
{
	void Core::Init()
	{
		RE::TESFurnitureEvent::GetEventSource()->RegisterSink(this);

		const auto ini = RE::INISettingCollection::GetSingleton();
		m_cameraOverShoulderPosX = ini->GetSetting("fOverShoulderPosX:Camera");
		m_cameraOverShoulderMeleeCombatPosX = ini->GetSetting("fOverShoulderMeleeCombatPosX:Camera");
		m_cameraOverShoulderCombatPosX = ini->GetSetting("fOverShoulderCombatPosX:Camera");

		m_cameraOverShoulderPosZ = ini->GetSetting("fOverShoulderPosZ:Camera");
		m_cameraOverShoulderMeleeCombatPosZ = ini->GetSetting("fOverShoulderMeleeCombatPosZ:Camera");
		m_cameraOverShoulderCombatPosZ = ini->GetSetting("fOverShoulderCombatPosZ:Camera");

		m_camera3rdPersonAimDist = ini->GetSetting("f3rdPersonAimDist:Camera");

		m_cameraOverShoulderMeleeCombatAddY = ini->GetSetting("fOverShoulderMeleeCombatAddY:Camera");
		m_cameraOverShoulderCombatAddY = ini->GetSetting("fOverShoulderCombatAddY:Camera");

		m_cameraDisableAutoVanityMode = ini->GetSetting("bDisableAutoVanityMode:Camera");
		m_cameraVanityModeMinDist = ini->GetSetting("fVanityModeMinDist:Camera");
		m_cameraVanityModeMaxDist = ini->GetSetting("fVanityModeMaxDist:Camera");

		m_cameraMouseWheelZoomSpeed = ini->GetSetting("fMouseWheelZoomSpeed:Camera");
		m_cameraMouseWheelZoomIncrement = ini->GetSetting("fMouseWheelZoomIncrement:Camera");

		m_cameraDefault1stPersonFOV = ini->GetSetting("fDefault1stPersonFOV:Display");
		m_cameraDefaultWorldFOV = ini->GetSetting("fDefaultWorldFOV:Display");
		m_camera3rdPersonAimFOV = ini->GetSetting("f3rdPersonAimFOV:Camera");

		m_cameraChangeSpeed = ini->GetSetting("fShoulderDollySpeed:Camera");
		m_cameraPitchZoom = ini->GetSetting("fPitchZoomOutMaxDist:Camera");

		ini->GetSetting("bApplyCameraNodeAnimations:Camera")->SetBinary(false);

		Update();
	}

	void Core::OnSerialLoad(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_version, std::uint32_t& a_length)
	{
		if (!a_intfc->ReadRecordDataEx(a_length, m_leftShoulder)) {
			logs::error("failed to load m_leftShoulder");
		}
	}

	void Core::OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
	{
		if (a_intfc->OpenRecord(a_type, a_version)) {
			a_intfc->WriteRecordData(m_leftShoulder);
		}
	}

	void Core::OnSerialRevert()
	{
		m_leftShoulder = false;
	}

	void Core::ToggleShoulder()
	{
		m_leftShoulder = !m_leftShoulder;
	}

	void Core::SetSneaking(bool a_sneaking)
	{
		m_sneaking = a_sneaking;
	}

	void Core::Update()
	{
		UpdateHorizontal();
		UpdateVertical();
		UpdateOffset();
		UpdateMisc();
		UpdateZoom();
		UpdateVanity();
		UpdateMouse();
		UpdateFOV();
		UpdateMisc();

		Apply();
	}

	void Core::UpdateCamera()
	{
		const auto camera = RE::PlayerCamera::GetSingleton();
		const auto player = RE::PlayerCharacter::GetSingleton();
		if (camera && player) {
			if (auto state = camera->GetState<RE::ThirdPersonState>())
				state->ProcessWeaponDrawnChange(player->GetWeaponMagicDrawn());
		}
	}

	void Core::UpdateHorizontal()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			if (m_sneaking) {
				m_cameraOverShoulderPosX = m_leftShoulder ? mcm.cameraPANormalSneakPosXLeft : mcm.cameraPANormalSneakPosXRight;
				m_cameraOverShoulderMeleeCombatPosX = m_leftShoulder ? mcm.cameraPAMeleeSneakPosXLeft : mcm.cameraPAMeleeSneakPosXRight;
				m_cameraOverShoulderCombatPosX = m_leftShoulder ? mcm.cameraPACombatSneakPosXLeft : mcm.cameraPACombatSneakPosXRight;
			} else {
				m_cameraOverShoulderPosX = m_leftShoulder ? mcm.cameraPANormalStandPosXLeft : mcm.cameraPANormalStandPosXRight;
				m_cameraOverShoulderMeleeCombatPosX = m_leftShoulder ? mcm.cameraPAMeleeStandPosXLeft : mcm.cameraPAMeleeStandPosXRight;
				m_cameraOverShoulderCombatPosX = m_leftShoulder ? mcm.cameraPACombatStandPosXLeft : mcm.cameraPACombatStandPosXRight;
			}
		} else {
			if (m_sneaking) {
				m_cameraOverShoulderPosX = m_leftShoulder ? mcm.cameraACNormalSneakPosXLeft : mcm.cameraACNormalSneakPosXRight;
				m_cameraOverShoulderMeleeCombatPosX = m_leftShoulder ? mcm.cameraACMeleeSneakPosXLeft : mcm.cameraACMeleeSneakPosXRight;
				m_cameraOverShoulderCombatPosX = m_leftShoulder ? mcm.cameraACCombatSneakPosXLeft : mcm.cameraACCombatSneakPosXRight;
			} else {
				m_cameraOverShoulderPosX = m_leftShoulder ? mcm.cameraACNormalStandPosXLeft : mcm.cameraACNormalStandPosXRight;
				m_cameraOverShoulderMeleeCombatPosX = m_leftShoulder ? mcm.cameraACMeleeStandPosXLeft : mcm.cameraACMeleeStandPosXRight;
				m_cameraOverShoulderCombatPosX = m_leftShoulder ? mcm.cameraACCombatStandPosXLeft : mcm.cameraACCombatStandPosXRight;
			}
		}
	}

	void Core::UpdateVertical()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraOverShoulderPosZ = m_sneaking ? mcm.cameraPANormalSneakPosZ : mcm.cameraPANormalStandPosZ;
			m_cameraOverShoulderMeleeCombatPosZ = m_sneaking ? mcm.cameraPAMeleeSneakPosZ : mcm.cameraPAMeleeStandPosZ;
			m_cameraOverShoulderCombatPosZ = m_sneaking ? mcm.cameraPACombatSneakPosZ : mcm.cameraPACombatStandPosZ;
		} else {
			m_cameraOverShoulderPosZ = m_sneaking ? mcm.cameraACNormalSneakPosZ : mcm.cameraACNormalStandPosZ;
			m_cameraOverShoulderMeleeCombatPosZ = m_sneaking ? mcm.cameraACMeleeSneakPosZ : mcm.cameraACMeleeStandPosZ;
			m_cameraOverShoulderCombatPosZ = m_sneaking ? mcm.cameraACCombatSneakPosZ : mcm.cameraACCombatStandPosZ;
		}
	}

	void Core::UpdateOffset()
	{
		float x = std::powf(std::fabsf(m_cameraOverShoulderCombatPosX), 2.0f);
		float z = std::powf(m_cameraOverShoulderCombatPosZ, 2.0f);
		m_camera3rdPersonAimDist = std::sqrtf(x + z);
	}

	void Core::UpdateZoom()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraOverShoulderMeleeCombatAddY = mcm.cameraPAMeleeZoom;
			m_cameraOverShoulderCombatAddY = mcm.cameraPACombatZoom;
		} else {
			m_cameraOverShoulderMeleeCombatAddY = mcm.cameraACMeleeZoom;
			m_cameraOverShoulderCombatAddY = mcm.cameraACCombatZoom;
		}
	}

	void Core::UpdateVanity()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraDisableAutoVanityMode = mcm.mainVanityMode;
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraVanityModeMinDist = mcm.cameraPAMinDist;
			m_cameraVanityModeMaxDist = mcm.cameraPAMaxDist;
		} else {
			m_cameraVanityModeMinDist = mcm.cameraACMinDist;
			m_cameraVanityModeMaxDist = mcm.cameraACMaxDist;
		}
	}

	void Core::UpdateMouse()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraMouseWheelZoomSpeed = mcm.cameraPAZoomSpeed;
			m_cameraMouseWheelZoomIncrement = mcm.cameraPAZoomIncrement;
		} else {
			m_cameraMouseWheelZoomSpeed = mcm.cameraACZoomSpeed;
			m_cameraMouseWheelZoomIncrement = mcm.cameraACZoomIncrement;
		}
	}

	void Core::UpdateFOV()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraDefault1stPersonFOV = mcm.camera1stFOV;
		m_cameraDefaultWorldFOV = mcm.camera3rdFOV;
		m_camera3rdPersonAimFOV = mcm.camera3rdAimFOV;
	}

	void Core::UpdateMisc()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraChangeSpeed = mcm.cameraChangeSpeed;
		m_cameraPitchZoom = mcm.cameraPitchZoom;
	}

	void Core::Apply()
	{
		const auto ini = RE::INISettingCollection::GetSingleton();
		ini->GetSetting("fOverShoulderPosX:Camera")->SetFloat(m_cameraOverShoulderPosX);
		ini->GetSetting("fOverShoulderMeleeCombatPosX:Camera")->SetFloat(m_cameraOverShoulderMeleeCombatPosX);
		ini->GetSetting("fOverShoulderCombatPosX:Camera")->SetFloat(m_cameraOverShoulderCombatPosX);

		ini->GetSetting("fOverShoulderPosZ:Camera")->SetFloat(m_cameraOverShoulderPosZ);
		ini->GetSetting("fOverShoulderMeleeCombatPosZ:Camera")->SetFloat(m_cameraOverShoulderMeleeCombatPosZ);
		ini->GetSetting("fOverShoulderCombatPosZ:Camera")->SetFloat(m_cameraOverShoulderCombatPosZ);

		ini->GetSetting("f3rdPersonAimDist:Camera")->SetFloat(m_camera3rdPersonAimDist);

		ini->GetSetting("fOverShoulderMeleeCombatAddY:Camera")->SetFloat(m_cameraOverShoulderMeleeCombatAddY);
		ini->GetSetting("fOverShoulderCombatAddY:Camera")->SetFloat(m_cameraOverShoulderCombatAddY);

		ini->GetSetting("bDisableAutoVanityMode:Camera")->SetBinary(m_cameraDisableAutoVanityMode);
		ini->GetSetting("fVanityModeMinDist:Camera")->SetFloat(m_cameraVanityModeMinDist);
		ini->GetSetting("fVanityModeMaxDist:Camera")->SetFloat(m_cameraVanityModeMaxDist);

		ini->GetSetting("fMouseWheelZoomSpeed:Camera")->SetFloat(m_cameraMouseWheelZoomSpeed);
		ini->GetSetting("fMouseWheelZoomIncrement:Camera")->SetFloat(m_cameraMouseWheelZoomIncrement);

		ini->GetSetting("fDefault1stPersonFOV:Display")->SetFloat(m_cameraDefault1stPersonFOV);
		ini->GetSetting("fDefaultWorldFOV:Display")->SetFloat(m_cameraDefaultWorldFOV);
		ini->GetSetting("f3rdPersonAimFOV:Camera")->SetFloat(m_camera3rdPersonAimFOV);

		ini->GetSetting("fShoulderDollySpeed:Camera")->SetFloat(m_cameraChangeSpeed);
		ini->GetSetting("fPitchZoomOutMaxDist:Camera")->SetFloat(m_cameraPitchZoom);
	}

	RE::BSEventNotifyControl Core::ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*)
	{
		if (a_event.actor->IsPlayerRef())
			Update();

		return RE::BSEventNotifyControl::kContinue;
	}
}
