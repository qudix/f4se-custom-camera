#include "CustomCamera/CoreData.h"

#include <SimpleIni.h>

namespace CustomCamera
{
	void CoreData::Load()
	{
		CSimpleIniA ini;
		if (ini.LoadFile("Data/MCM/Settings/CustomCamera.ini") >= 0) {
			m_mcm.mainVanityMode = ini.GetBoolValue("Main", "bVanityMode", true);

			m_mcm.cameraACNormalStandPosXRight = (float)ini.GetDoubleValue("Camera", "fACNormalStandPosXRight", 0.0);
			m_mcm.cameraACNormalStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fACNormalStandPosXLeft", 0.0);
			m_mcm.cameraACNormalStandPosZ = (float)ini.GetDoubleValue("Camera", "fACNormalStandPosZ", 0.0);
			m_mcm.cameraACNormalSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fACNormalSneakPosXRight", 0.0);
			m_mcm.cameraACNormalSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fACNormalSneakPosXLeft", 0.0);
			m_mcm.cameraACNormalSneakPosZ = (float)ini.GetDoubleValue("Camera", "fACNormalSneakPosZ", 0.0);
			m_mcm.cameraACMeleeStandPosXRight = (float)ini.GetDoubleValue("Camera", "fACMeleeStandPosXRight", 30.0);
			m_mcm.cameraACMeleeStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fACMeleeStandPosXLeft", -30.0);
			m_mcm.cameraACMeleeStandPosZ = (float)ini.GetDoubleValue("Camera", "fACMeleeStandPosZ", 0.0);
			m_mcm.cameraACMeleeSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fACMeleeSneakPosXRight", 30.0);
			m_mcm.cameraACMeleeSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fACMeleeSneakPosXLeft", -30.0);
			m_mcm.cameraACMeleeSneakPosZ = (float)ini.GetDoubleValue("Camera", "fACMeleeSneakPosZ", 0.0);
			m_mcm.cameraACMeleeZoom = (float)ini.GetDoubleValue("Camera", "fACMeleeZoom", 0.0);
			m_mcm.cameraACCombatStandPosXRight = (float)ini.GetDoubleValue("Camera", "fACCombatStandPosXRight", 30.0);
			m_mcm.cameraACCombatStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fACCombatStandPosXLeft", -30.0);
			m_mcm.cameraACCombatStandPosZ = (float)ini.GetDoubleValue("Camera", "fACCombatStandPosZ", 0.0);
			m_mcm.cameraACCombatSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fACCombatSneakPosXRight", 30.0);
			m_mcm.cameraACCombatSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fACCombatSneakPosXLeft", -30.0);
			m_mcm.cameraACCombatSneakPosZ = (float)ini.GetDoubleValue("Camera", "fACCombatSneakPosZ", 0.0);
			m_mcm.cameraACCombatZoom = (float)ini.GetDoubleValue("Camera", "fACCombatZoom", 0.0);
			m_mcm.cameraACMinDist = (float)ini.GetDoubleValue("Camera", "fACMinDist", 50.0);
			m_mcm.cameraACMaxDist = (float)ini.GetDoubleValue("Camera", "fACMaxDist", 150.0);
			m_mcm.cameraACZoomSpeed = (float)ini.GetDoubleValue("Camera", "fACZoomSpeed", 3.0);
			m_mcm.cameraACZoomIncrement = (float)ini.GetDoubleValue("Camera", "fACZoomIncrement", 0.075);

			m_mcm.cameraPANormalStandPosXRight = (float)ini.GetDoubleValue("Camera", "fPANormalStandPosXRight", 0.0);
			m_mcm.cameraPANormalStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fPANormalStandPosXLeft", 0.0);
			m_mcm.cameraPANormalStandPosZ = (float)ini.GetDoubleValue("Camera", "fPANormalStandPosZ", 0.0);
			m_mcm.cameraPANormalSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fPANormalSneakPosXRight", 0.0);
			m_mcm.cameraPANormalSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fPANormalSneakPosXLeft", 0.0);
			m_mcm.cameraPANormalSneakPosZ = (float)ini.GetDoubleValue("Camera", "fPANormalSneakPosZ", 0.0);
			m_mcm.cameraPAMeleeStandPosXRight = (float)ini.GetDoubleValue("Camera", "fPAMeleeStandPosXRight", 50.0);
			m_mcm.cameraPAMeleeStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fPAMeleeStandPosXLeft", -50.0);
			m_mcm.cameraPAMeleeStandPosZ = (float)ini.GetDoubleValue("Camera", "fPAMeleeStandPosZ", 0.0);
			m_mcm.cameraPAMeleeSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fPAMeleeSneakPosXRight", 50.0);
			m_mcm.cameraPAMeleeSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fPAMeleeSneakPosXLeft", -50.0);
			m_mcm.cameraPAMeleeSneakPosZ = (float)ini.GetDoubleValue("Camera", "fPAMeleeSneakPosZ", 0.0);
			m_mcm.cameraPAMeleeZoom = (float)ini.GetDoubleValue("Camera", "fPAMeleeZoom", 0.0);
			m_mcm.cameraPACombatStandPosXRight = (float)ini.GetDoubleValue("Camera", "fPACombatStandPosXRight", 50.0);
			m_mcm.cameraPACombatStandPosXLeft = (float)ini.GetDoubleValue("Camera", "fPACombatStandPosXLeft", -50.0);
			m_mcm.cameraPACombatStandPosZ = (float)ini.GetDoubleValue("Camera", "fPACombatStandPosZ", 0.0);
			m_mcm.cameraPACombatSneakPosXRight = (float)ini.GetDoubleValue("Camera", "fPACombatSneakPosXRight", 50.0);
			m_mcm.cameraPACombatSneakPosXLeft = (float)ini.GetDoubleValue("Camera", "fPACombatSneakPosXLeft", -50.0);
			m_mcm.cameraPACombatSneakPosZ = (float)ini.GetDoubleValue("Camera", "fPACombatSneakPosZ", 0.0);
			m_mcm.cameraPACombatZoom = (float)ini.GetDoubleValue("Camera", "fPACombatZoom", 0.0);
			m_mcm.cameraPAMinDist = (float)ini.GetDoubleValue("Camera", "fPAMinDist", 50.0);
			m_mcm.cameraPAMaxDist = (float)ini.GetDoubleValue("Camera", "fPAMaxDist", 150.0);
			m_mcm.cameraPAZoomSpeed = (float)ini.GetDoubleValue("Camera", "fPAZoomSpeed", 3.0);
			m_mcm.cameraPAZoomIncrement = (float)ini.GetDoubleValue("Camera", "fPAZoomIncrement", 0.075);

			m_mcm.camera1stFOV = (float)ini.GetDoubleValue("Camera", "f1stFOV", 75.0);
			m_mcm.camera3rdFOV = (float)ini.GetDoubleValue("Camera", "f3rdFOV", 75.0);
			m_mcm.camera3rdAimFOV = (float)ini.GetDoubleValue("Camera", "f3rdAimFOV", 75.0);
			m_mcm.cameraChangeSpeed = (float)ini.GetDoubleValue("Camera", "fChangeSpeed", 3.0);
			m_mcm.cameraPitchZoom = (float)ini.GetDoubleValue("Camera", "fPitchZoom", 0.0);
		}
	}
}
