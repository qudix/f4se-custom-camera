#include "CustomCamera/Core.h"
#include "CustomCamera/Papyrus.h"

struct Hook_PlayerCharacter
{
	static bool DoCanRotate(RE::PlayerCharacter* a_this)
	{
		if (const auto camera = RE::PlayerCamera::GetSingleton())
			if (camera->QCameraEquals(RE::CameraState::kFree))
				return false;

		return _DoCanRotate(a_this);
	}

	static bool SetSneaking(RE::PlayerCharacter* a_this, bool a_sneaking)
	{
		bool result = _SetSneaking(a_this, a_sneaking);

		auto core = CustomCamera::Core::GetSingleton();
		core->SetSneaking(a_sneaking);
		core->Update();
		core->UpdateCamera();

		return result;
	}

	inline static REL::Relocation<decltype(DoCanRotate)> _DoCanRotate;
	inline static REL::Relocation<decltype(SetSneaking)> _SetSneaking;

	static void Install()
	{
		static REL::Relocation vtbl{ RE::PlayerCharacter::VTABLE[0] };
		_DoCanRotate = vtbl.write_vfunc(0x18, DoCanRotate);
		_SetSneaking = vtbl.write_vfunc(0x120, SetSneaking);
	}
};

void OnMessage(F4SE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type) {
		case F4SE::MessagingInterface::kPostLoad: {
			Hook_PlayerCharacter::Install();
		} break;
        case F4SE::MessagingInterface::kGameLoaded: {
			CustomCamera::CoreData::GetSingleton()->Load();
            CustomCamera::Core::GetSingleton()->Init();
        } break;
		case F4SE::MessagingInterface::kPostLoadGame: {
			CustomCamera::Core::GetSingleton()->Update();
		}
    }
}

void OnSerialLoad(const F4SE::SerializationInterface* a_intfc)
{
	std::uint32_t type;
	std::uint32_t version;
	std::uint32_t length;

	while (a_intfc->GetNextRecordInfo(type, version, length)) {
		switch (type) {
			case 'CORE': {
				const auto core = CustomCamera::Core::GetSingleton();
				core->OnSerialLoad(a_intfc, version, length);
			} break;
			default: {
				logs::error("unrecognized signature type!");
			} break;
		}
	}
}

void OnSerialSave(const F4SE::SerializationInterface* a_intfc)
{
	const auto core = CustomCamera::Core::GetSingleton();
	core->OnSerialSave(a_intfc, 'CORE', 1);
}

void OnSerialRevert(const F4SE::SerializationInterface*)
{
	const auto core = CustomCamera::Core::GetSingleton();
	core->OnSerialRevert();
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);

    if (const auto intfc = F4SE::GetMessagingInterface())
        intfc->RegisterListener(OnMessage);

	if (const auto intfc = F4SE::GetPapyrusInterface())
        intfc->Register(CustomCamera::Papyrus::Bind);

    if (const auto intfc = F4SE::GetSerializationInterface()) {
        intfc->SetUniqueID('CCAM');
        intfc->SetLoadCallback(OnSerialLoad);
		intfc->SetSaveCallback(OnSerialSave);
		intfc->SetRevertCallback(OnSerialRevert);
    }

	return true;
}
