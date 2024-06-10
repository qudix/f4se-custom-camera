#pragma once

#include "CustomCamera/CoreData.h"

namespace CustomCamera::Papyrus
{
	namespace Impl
	{
		inline void ToggleFreeCamera(bool a_freezeTime)
		{
			if (const auto camera = RE::PlayerCamera::GetSingleton()) {
				camera->ToggleFreeCameraMode(a_freezeTime);

				const auto control = RE::ControlMap::GetSingleton();
				if (camera->QCameraEquals(RE::CameraState::kFree))
					control->PushInputContext(RE::UserEvents::INPUT_CONTEXT_ID::kTFC);
				else
					control->PopInputContext(RE::UserEvents::INPUT_CONTEXT_ID::kTFC);
			}
		}
	}

	inline void Update(std::monostate)
	{
		CoreData::GetSingleton()->Load();
		const auto core = Core::GetSingleton();
		core->Update();
		core->UpdateCamera();
	}

	inline void ToggleShoulder(std::monostate)
	{
		const auto core = Core::GetSingleton();
		core->ToggleSide();
		core->Update();
		core->UpdateCamera();
	}

	inline void ToggleFreeCamera(std::monostate)
	{
		Impl::ToggleFreeCamera(false);
	}

	inline void ToggleFreeCameraFreeze(std::monostate)
	{
		Impl::ToggleFreeCamera(true);
	}

	inline bool Bind(RE::BSScript::IVirtualMachine* a_vm)
	{
		const auto obj = "CustomCamera"sv;
		a_vm->BindNativeMethod(obj, "Update"sv, Update);
		a_vm->BindNativeMethod(obj, "ToggleShoulder"sv, ToggleShoulder);
		a_vm->BindNativeMethod(obj, "ToggleFreeCamera"sv, ToggleFreeCamera);
		a_vm->BindNativeMethod(obj, "ToggleFreeCameraFreeze"sv, ToggleFreeCameraFreeze);

		return true;
	}
}
