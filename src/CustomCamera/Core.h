#pragma once

namespace CustomCamera
{
	class Core :
		public REX::Singleton<Core>,
		public RE::BSTEventSink<RE::TESFurnitureEvent>,
		public RE::BSTEventSink<RE::ActorEquipManagerEvent::Event>
	{
	public:
		void Init();

		void OnSerialLoad(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_version, std::uint32_t& a_length);
		void OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
		void OnSerialRevert();

		void ToggleShoulder();

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

		void Apply();

	public: // BSTEventSink
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) override;
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::ActorEquipManagerEvent::Event& a_event, RE::BSTEventSource<RE::ActorEquipManagerEvent::Event>*) override;

	private:
		bool m_leftShoulder{ false };
		bool m_sneaking{ false };

		float m_cameraOverShoulderPosX;
		float m_cameraOverShoulderMeleeCombatPosX;
		float m_cameraOverShoulderCombatPosX;

		float m_cameraOverShoulderPosZ;
		float m_cameraOverShoulderMeleeCombatPosZ;
		float m_cameraOverShoulderCombatPosZ;

		float m_cameraOverShoulderMeleeCombatAddY;
		float m_cameraOverShoulderCombatAddY;

		bool m_cameraDisableAutoVanityMode;
		float m_cameraVanityModeMinDist;
		float m_cameraVanityModeMaxDist;

		float m_cameraMouseWheelZoomSpeed;
		float m_cameraMouseWheelZoomIncrement;

		float m_cameraDefault1stPersonFOV;
		float m_cameraDefaultWorldFOV;
		float m_camera3rdPersonAimFOV;

		float m_cameraChangeSpeed;
		float m_cameraPitchZoom;

		float m_camera3rdPersonAimDist;
	};
}
