#pragma once

namespace CustomCamera
{
	class CoreData :
		public REX::Singleton<CoreData>
	{
	public:
		struct MCM
		{
			bool mainVanityMode{ true };

			float cameraACNormalStandPosXRight{ 0.0f };
			float cameraACNormalStandPosXLeft{ 0.0f };
			float cameraACNormalStandPosZ{ 0.0f };
			float cameraACNormalSneakPosXRight{ 0.0f };
			float cameraACNormalSneakPosXLeft{ 0.0f };
			float cameraACNormalSneakPosZ{ 0.0f };
			float cameraACMeleeStandPosXRight{ 30.0f };
			float cameraACMeleeStandPosXLeft{ -30.0f };
			float cameraACMeleeStandPosZ{ 0.0f };
			float cameraACMeleeSneakPosXRight{ 30.0f };
			float cameraACMeleeSneakPosXLeft{ -30.0f };
			float cameraACMeleeSneakPosZ{ 0.0f };
			float cameraACMeleeZoom{ 0.0f };
			float cameraACCombatStandPosXRight{ 30.0f };
			float cameraACCombatStandPosXLeft{ -30.0f };
			float cameraACCombatStandPosZ{ 0.0f };
			float cameraACCombatSneakPosXRight{ 30.0f };
			float cameraACCombatSneakPosXLeft{ -30.0f };
			float cameraACCombatSneakPosZ{ 0.0f };
			float cameraACCombatZoom{ 0.0f };
			float cameraACMinDist{ 50.0f };
			float cameraACMaxDist{ 150.0f };
			float cameraACZoomSpeed{ 3.0f };
			float cameraACZoomIncrement{ 0.075f };

			float cameraPANormalStandPosXRight{ 0.0f };
			float cameraPANormalStandPosXLeft{ 0.0f };
			float cameraPANormalStandPosZ{ 0.0f };
			float cameraPANormalSneakPosXRight{ 0.0f };
			float cameraPANormalSneakPosXLeft{ 0.0f };
			float cameraPANormalSneakPosZ{ 0.0f };
			float cameraPAMeleeStandPosXRight{ 50.0f };
			float cameraPAMeleeStandPosXLeft{ -50.0f };
			float cameraPAMeleeStandPosZ{ 0.0f };
			float cameraPAMeleeSneakPosXRight{ 50.0f };
			float cameraPAMeleeSneakPosXLeft{ -50.0f };
			float cameraPAMeleeSneakPosZ{ 0.0f };
			float cameraPAMeleeZoom{ 0.0f };
			float cameraPACombatStandPosXRight{ 50.0f };
			float cameraPACombatStandPosXLeft{ -50.0f };
			float cameraPACombatStandPosZ{ 0.0f };
			float cameraPACombatSneakPosXRight{ 50.0f };
			float cameraPACombatSneakPosXLeft{ -50.0f };
			float cameraPACombatSneakPosZ{ 0.0f };
			float cameraPACombatZoom{ 0.0f };
			float cameraPAMinDist{ 50.0f };
			float cameraPAMaxDist{ 150.0f };
			float cameraPAZoomSpeed{ 3.0f };
			float cameraPAZoomIncrement{ 0.075f };

			float camera1stFOV{ 75.0f };
			float camera3rdFOV{ 75.0f };
			float camera3rdAimFOV{ 75.0f };

			float cameraChangeSpeed{ 3.0f };
			float cameraPitchZoom{ 0.0f };
		};

		void Load();

		MCM& GetMCM() { return m_mcm; }

	private:
		MCM m_mcm;
	};
}
