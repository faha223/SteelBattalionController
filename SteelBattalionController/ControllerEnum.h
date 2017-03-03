#pragma once

enum ControllerLED
{
	None = 0,
	EmergencyEject = 4,
	CockpitHatch = 5,
	Ignition = 6,
	Start = 7,
	OpenClose = 8,
	MapZoomInOut = 9,
	ModeSelect = 10,
	SubMonitorModeSelect = 11,
	MainMonitorZoomIn = 12,
	MainMonitorZoomOut = 13,
	ForecastShootingSystem = 14,
	Manipulator = 15,
	LineColorChange = 16,
	Washing = 17,
	Extinguisher = 18,
	Chaff = 19,
	TankDetach = 20,
	Override = 21,
	NightScope = 22,
	F1 = 23,
	F2 = 24,
	F3 = 25,
	MainWeaponControl = 26,
	SubWeaponControl = 27,
	MagazineChange = 28,
	Comm1 = 29,
	Comm2 = 30,
	Comm3 = 31,
	Comm4 = 32,
	Comm5 = 33,
	GearR = 35,
	GearN = 36,
	Gear1 = 37,
	Gear2 = 38,
	Gear3 = 39,
	Gear4 = 40,
	Gear5 = 41,
};

enum ControllerButton
{
	RightJoyMainWeapon,
	RightJoyFire,
	RightJoyLockOn,
	CockpitHatch,
	Ignition,
	Start,
	Eject,
	MultiMonOpenClose,
	MultiMonMapZoomInOut,
	MultiMonModeSelect,
	MultiMonSubMonitor,
	MainMonZoomIn,
	MainMonZoomOut,
	Washing,
	Extinguisher,
	Chaff,
	WeaponConMain,
	WeaponConSub,
	WeaponConMagazine,
	FunctionFSS,
	FunctionManipulator,
	FunctionLineColorChange,
	FunctionTankDetach,
	FunctionOverride,
	FunctionNightScope,
	FunctionF1,
	FunctionF2,
	FunctionF3,
	Comm1,
	Comm2,
	Comm3,
	Comm4,
	Comm5,
	LeftJoySightChange,
	ToggleFilterControl,
	ToggleOxygenSupply,
	ToggleFuelFlowRate,
	ToggleBufferMaterial,
	ToggleVTLocation
};

struct ButtonMask {
	int bytePos;
	int maskValue;

	ButtonMask(int bytePos, int maskValue) {
		this->bytePos = bytePos;
		this->maskValue = maskValue;
	}
};

const ButtonMask ButtonMasks[50];

inline ControllerLED GetLED(ControllerButton button)
{
	switch (button)
	{
	default:
		return ForecastShootingSystem;
	}
}

inline ControllerButton GetButton(ControllerLED led)
{

}