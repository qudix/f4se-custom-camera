#pragma once

namespace CustomCamera
{
	class Core :
		public REX::Singleton<Core>,
		public RE::BSTEventSink<RE::TESFurnitureEvent>
	{
	public:
		void Init();

		void OnSerialLoad(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_version, std::uint32_t& a_length);
		void OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
		void OnSerialRevert();

		void ToggleSide();

		void SetSneaking(bool a_sneaking);

		void Update();
		void UpdateCamera();
		void UpdateHorizontal();
		void UpdateVertical();
		void UpdateOffset();
		void UpdateZoom();
		void UpdateVanity();
		void UpdateMouse();
		void UpdateFOV();
		void UpdateMisc();

	public: // BSTEventSink
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) override;

	private:
		bool m_leftSide{ false };
		bool m_sneaking{ false };

		RE::Setting* m_cameraOverShoulderPosX;
		RE::Setting* m_cameraOverShoulderMeleeCombatPosX;
		RE::Setting* m_cameraOverShoulderCombatPosX;

		RE::Setting* m_cameraOverShoulderPosZ;
		RE::Setting* m_cameraOverShoulderMeleeCombatPosZ;
		RE::Setting* m_cameraOverShoulderCombatPosZ;

		RE::Setting* m_cameraOverShoulderMeleeCombatAddY;
		RE::Setting* m_cameraOverShoulderCombatAddY;

		RE::Setting* m_cameraDisableAutoVanityMode;
		RE::Setting* m_cameraVanityModeMinDist;
		RE::Setting* m_cameraVanityModeMaxDist;

		RE::Setting* m_cameraMouseWheelZoomSpeed;
		RE::Setting* m_cameraMouseWheelZoomIncrement;

		RE::Setting* m_cameraDefault1stPersonFOV;
		RE::Setting* m_cameraDefaultWorldFOV;
		RE::Setting* m_camera3rdPersonAimFOV;

		RE::Setting* m_cameraChangeSpeed;
		RE::Setting* m_cameraPitchZoom;

		RE::Setting* m_camera3rdPersonAimDist;
	};
}
