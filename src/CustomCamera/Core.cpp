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
		if (!a_intfc->ReadRecordDataEx(a_length, m_leftSide)) {
			logs::error("failed to load m_leftSide");
		}
	}

	void Core::OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
	{
		if (a_intfc->OpenRecord(a_type, a_version)) {
			a_intfc->WriteRecordData(m_leftSide);
		}
	}

	void Core::OnSerialRevert()
	{
		m_leftSide = false;
	}

	void Core::ToggleSide()
	{
		m_leftSide = !m_leftSide;
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
				m_cameraOverShoulderPosX->SetFloat(m_leftSide ? mcm.cameraPANormalSneakPosXLeft : mcm.cameraPANormalSneakPosXRight);
				m_cameraOverShoulderMeleeCombatPosX->SetFloat(m_leftSide ? mcm.cameraPAMeleeSneakPosXLeft : mcm.cameraPAMeleeSneakPosXRight);
				m_cameraOverShoulderCombatPosX->SetFloat(m_leftSide ? mcm.cameraPACombatSneakPosXLeft : mcm.cameraPACombatSneakPosXRight);
			} else {
				m_cameraOverShoulderPosX->SetFloat(m_leftSide ? mcm.cameraPANormalStandPosXLeft : mcm.cameraPANormalStandPosXRight);
				m_cameraOverShoulderMeleeCombatPosX->SetFloat(m_leftSide ? mcm.cameraPAMeleeStandPosXLeft : mcm.cameraPAMeleeStandPosXRight);
				m_cameraOverShoulderCombatPosX->SetFloat(m_leftSide ? mcm.cameraPACombatStandPosXLeft : mcm.cameraPACombatStandPosXRight);
			}
		} else {
			if (m_sneaking) {
				m_cameraOverShoulderPosX->SetFloat(m_leftSide ? mcm.cameraACNormalSneakPosXLeft : mcm.cameraACNormalSneakPosXRight);
				m_cameraOverShoulderMeleeCombatPosX->SetFloat(m_leftSide ? mcm.cameraACMeleeSneakPosXLeft : mcm.cameraACMeleeSneakPosXRight);
				m_cameraOverShoulderCombatPosX->SetFloat(m_leftSide ? mcm.cameraACCombatSneakPosXLeft : mcm.cameraACCombatSneakPosXRight);
			} else {
				m_cameraOverShoulderPosX->SetFloat(m_leftSide ? mcm.cameraACNormalStandPosXLeft : mcm.cameraACNormalStandPosXRight);
				m_cameraOverShoulderMeleeCombatPosX->SetFloat(m_leftSide ? mcm.cameraACMeleeStandPosXLeft : mcm.cameraACMeleeStandPosXRight);
				m_cameraOverShoulderCombatPosX->SetFloat(m_leftSide ? mcm.cameraACCombatStandPosXLeft : mcm.cameraACCombatStandPosXRight);
			}
		}
	}

	void Core::UpdateVertical()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraOverShoulderPosZ->SetFloat(m_sneaking ? mcm.cameraPANormalSneakPosZ : mcm.cameraPANormalStandPosZ);
			m_cameraOverShoulderMeleeCombatPosZ->SetFloat(m_sneaking ? mcm.cameraPAMeleeSneakPosZ : mcm.cameraPAMeleeStandPosZ);
			m_cameraOverShoulderCombatPosZ->SetFloat(m_sneaking ? mcm.cameraPACombatSneakPosZ : mcm.cameraPACombatStandPosZ);
		} else {
			m_cameraOverShoulderPosZ->SetFloat(m_sneaking ? mcm.cameraACNormalSneakPosZ : mcm.cameraACNormalStandPosZ);
			m_cameraOverShoulderMeleeCombatPosZ->SetFloat(m_sneaking ? mcm.cameraACMeleeSneakPosZ : mcm.cameraACMeleeStandPosZ);
			m_cameraOverShoulderCombatPosZ->SetFloat(m_sneaking ? mcm.cameraACCombatSneakPosZ : mcm.cameraACCombatStandPosZ);
		}
	}

	void Core::UpdateOffset()
	{
		float x = std::powf(std::fabsf(m_cameraOverShoulderCombatPosX->GetFloat()), 2.0f);
		float z = std::powf(m_cameraOverShoulderCombatPosZ->GetFloat(), 2.0f);
		m_camera3rdPersonAimDist->SetFloat(std::sqrtf(x + z));
	}

	void Core::UpdateZoom()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraOverShoulderMeleeCombatAddY->SetFloat(mcm.cameraPAMeleeZoom);
			m_cameraOverShoulderCombatAddY->SetFloat(mcm.cameraPACombatZoom);
		} else {
			m_cameraOverShoulderMeleeCombatAddY->SetFloat(mcm.cameraACMeleeZoom);
			m_cameraOverShoulderCombatAddY->SetFloat(mcm.cameraACCombatZoom);
		}
	}

	void Core::UpdateVanity()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraDisableAutoVanityMode->SetBinary(mcm.mainVanityMode);
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraVanityModeMinDist->SetFloat(mcm.cameraPAMinDist);
			m_cameraVanityModeMaxDist->SetFloat(mcm.cameraPAMaxDist);
		} else {
			m_cameraVanityModeMinDist->SetFloat(mcm.cameraACMinDist);
			m_cameraVanityModeMaxDist->SetFloat(mcm.cameraACMaxDist);
		}
	}

	void Core::UpdateMouse()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		if (RE::PowerArmor::PlayerInPowerArmor()) {
			m_cameraMouseWheelZoomSpeed->SetFloat(mcm.cameraPAZoomSpeed);
			m_cameraMouseWheelZoomIncrement->SetFloat(mcm.cameraPAZoomIncrement);
		} else {
			m_cameraMouseWheelZoomSpeed->SetFloat(mcm.cameraACZoomSpeed);
			m_cameraMouseWheelZoomIncrement->SetFloat(mcm.cameraACZoomIncrement);
		}
	}

	void Core::UpdateFOV()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraDefault1stPersonFOV->SetFloat(mcm.camera1stFOV);
		m_cameraDefaultWorldFOV->SetFloat(mcm.camera3rdFOV);
		m_camera3rdPersonAimFOV->SetFloat(mcm.camera3rdAimFOV);
	}

	void Core::UpdateMisc()
	{
		const auto& mcm = CoreData::GetSingleton()->GetMCM();
		m_cameraChangeSpeed->SetFloat(mcm.cameraChangeSpeed);
		m_cameraPitchZoom->SetFloat(mcm.cameraPitchZoom);
	}

	RE::BSEventNotifyControl Core::ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*)
	{
		if (a_event.actor->IsPlayerRef())
			Update();

		return RE::BSEventNotifyControl::kContinue;
	}
}
