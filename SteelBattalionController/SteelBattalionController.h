#pragma once
#include "WinUsb_ThreadSafe.h"
#include "NamedPipe.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <map>

#pragma region Enums

enum class ControllerLEDEnum : UCHAR
{
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
	Gear5 = 41,
	Gear4 = 40,
	Gear3 = 39,
	Gear2 = 38,
	Gear1 = 37,
	GearN = 36,
	GearR = 35,
	Comm5 = 33,
	Comm4 = 32,
	Comm3 = 31,
	Comm2 = 30,
	Comm1 = 29,
	MagazineChange = 28,
	SubWeaponControl = 27,
	MainWeaponControl = 26,
	F3 = 25,
	F2 = 24,
	F1 = 23,
	NightScope = 22,
	Override = 21,
	TankDetach = 20,
	Chaff = 19,
	Extinguisher = 18,
	Washing = 17,
	LineColorChange = 16,
	Manipulator = 15,
	ForecastShootingSystem = 14,
	None = 255
};

enum class ButtonEnum : UCHAR {
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

enum class GearEnum : UCHAR
{
	None = 0,
	Gear1 = 1,
	Gear2 = 2,
	Gear3 = 3,
	Gear4 = 4,
	Gear5 = 5,
	GearN = 255,
	GearR = 254
};

enum class AxisEnum : UCHAR
{
	AimingX = 4, // 9
	AimingY = 5, // 11
	Rotation = 6, // 13
	SightChangeX = 7, // 15
	SightChangeY = 8, // 17
	StrafePedal = 9, // 19
	BrakePedal = 10, // 21
	Throttle = 11 // 23
};

enum class MessageHeader : UCHAR
{
	NoMessage = 0,
	SetLED = 1,
	SetLEDs = 2,
	ButtonChanged = 3,
	AxisChanged = 4,
	GearChanged = 5,
	TunerChanged = 6,
	ControllerState = 7
};

inline ControllerLEDEnum GetLED(ButtonEnum button)
{
	switch (button)
	{
	case ButtonEnum::Chaff:
		return ControllerLEDEnum::Chaff;
	case ButtonEnum::CockpitHatch:
		return ControllerLEDEnum::CockpitHatch;
	case ButtonEnum::Comm1:
		return ControllerLEDEnum::Comm1;
	case ButtonEnum::Comm2:
		return ControllerLEDEnum::Comm2;
	case ButtonEnum::Comm3:
		return ControllerLEDEnum::Comm3;
	case ButtonEnum::Comm4:
		return ControllerLEDEnum::Comm4;
	case ButtonEnum::Comm5:
		return ControllerLEDEnum::Comm5;
	case ButtonEnum::Eject:
		return ControllerLEDEnum::EmergencyEject;
	case ButtonEnum::Extinguisher:
		return ControllerLEDEnum::Extinguisher;
	case ButtonEnum::FunctionF1:
		return ControllerLEDEnum::F1;
	case ButtonEnum::FunctionF2:
		return ControllerLEDEnum::F2;
	case ButtonEnum::FunctionF3:
		return ControllerLEDEnum::F3;
	case ButtonEnum::FunctionFSS:
		return ControllerLEDEnum::ForecastShootingSystem;
	case ButtonEnum::FunctionLineColorChange:
		return ControllerLEDEnum::LineColorChange;
	case ButtonEnum::FunctionManipulator:
		return ControllerLEDEnum::Manipulator;
	case ButtonEnum::FunctionNightScope:
		return ControllerLEDEnum::NightScope;
	case ButtonEnum::FunctionOverride:
		return ControllerLEDEnum::Override;
	case ButtonEnum::FunctionTankDetach:
		return ControllerLEDEnum::TankDetach;
	case ButtonEnum::Ignition:
		return ControllerLEDEnum::Ignition;
	case ButtonEnum::MainMonZoomIn:
		return ControllerLEDEnum::MainMonitorZoomIn;
	case ButtonEnum::MainMonZoomOut:
		return ControllerLEDEnum::MainMonitorZoomOut;
	case ButtonEnum::MultiMonMapZoomInOut:
		return ControllerLEDEnum::MapZoomInOut;
	case ButtonEnum::MultiMonModeSelect:
		return ControllerLEDEnum::ModeSelect;
	case ButtonEnum::MultiMonOpenClose:
		return ControllerLEDEnum::OpenClose;
	case ButtonEnum::MultiMonSubMonitor:
		return ControllerLEDEnum::SubMonitorModeSelect;
	case ButtonEnum::Start:
		return ControllerLEDEnum::Start;
	case ButtonEnum::WeaponConMain:
		return ControllerLEDEnum::MainWeaponControl;
	case ButtonEnum::WeaponConSub:
		return ControllerLEDEnum::SubWeaponControl;
	case ButtonEnum::WeaponConMagazine:
		return ControllerLEDEnum::MagazineChange;
	case ButtonEnum::Washing:
		return ControllerLEDEnum::Washing;
	default:
		return ControllerLEDEnum::None;
	}
}

inline ControllerLEDEnum GetLED(GearEnum gear)
{
	switch (gear)
	{
	case GearEnum::GearR:
		return ControllerLEDEnum::GearR;
	case GearEnum::GearN:
		return ControllerLEDEnum::GearN;
	case GearEnum::Gear1:
		return ControllerLEDEnum::Gear1;
	case GearEnum::Gear2:
		return ControllerLEDEnum::Gear2;
	case GearEnum::Gear3:
		return ControllerLEDEnum::Gear3;
	case GearEnum::Gear4:
		return ControllerLEDEnum::Gear4;
	case GearEnum::Gear5:
		return ControllerLEDEnum::Gear5;
	default:
		return ControllerLEDEnum::None;
	}
}

class ButtonMask
{
public:
	int bytePos;
	UCHAR mask;
	ButtonMask();
	ButtonMask(int bytePos, UCHAR mask);
};

#pragma endregion Enums

struct ControllerState
{
	float Rotation;
	float SightChangeX;
	float SightChangeY;
	float AimingX;
	float AimingY;
	float StrafePedal;
	float BrakePedal;
	float GasPedal;

	GearEnum Gear;
	
	UCHAR OxygenSupplySystem;
	UCHAR FilterControlSystem;
	UCHAR VTLocationMeasurement;
	UCHAR BufferMaterial;
	UCHAR FuelFlowRate;
	UCHAR SightChange;
	UCHAR Comm1;
	UCHAR Comm2;
	UCHAR Comm3;
	UCHAR Comm4;
	UCHAR Comm5;
	UCHAR TunerDial;
	UCHAR F1;
	UCHAR TankDetach;
	UCHAR ForecastShootingSystem;
	UCHAR F2;
	UCHAR Override;
	UCHAR Manipulator;
	UCHAR F3;
	UCHAR NightScope;
	UCHAR LineColorChange;
	UCHAR Washing;
	UCHAR Extinguisher;
	UCHAR Chaff;
	UCHAR MainWeaponControl;
	UCHAR SubWeaponControl;
	UCHAR MagazineChange;
	UCHAR LockOn;
	UCHAR MainWeaponFire;
	UCHAR SubWeaponFire;
	UCHAR MultiMonitorOpenClose;
	UCHAR MultiMonitorMapZoom;
	UCHAR MultiMonitorModeSelect;
	UCHAR SubMonitorModeSelect;
	UCHAR MainMonitorZoomIn;
	UCHAR MainMonitorZoomOut;
	UCHAR CockpitHatch;
	UCHAR Ignition;
	UCHAR Start;
	UCHAR Eject;
};

class SteelBattalionController
{
private:
	// Static Constants
	static const UCHAR PipeInId = 0x82;
	static const UCHAR PipeOutId = 0x01;

	// Static State
	static std::map<ButtonEnum, ButtonMask> Masks;
	static bool MasksInitialized;

	// Thread Maintenance
	std::atomic<bool> shutdown;
	// Thread Synchronization
	std::mutex ledThreadMutex;
	std::mutex inputThreadMutex;

	NamedPipe *commPipe;
	
	// Threads
	std::thread *ledThread;
	std::thread *inputThread;
	std::thread *pipeThread;

	// Device State
	UCHAR *ledState;
	UCHAR *inputState;

	// Safe Access to the Device
	WinUsb *m_WinUsb;

	// Initialization
	void Init();

	// Static Initialization
	static void InitMasks();

	// Thread Functions
	static void ledThreadFunc(SteelBattalionController *controller);
	static void inputThreadFunc(SteelBattalionController *controller);
	static void pipeThreadFunc(SteelBattalionController *controller);

	// Get/Set LEDs
	static void SetLEDState(ControllerLEDEnum LightId, int Intensity, UCHAR *ledBuffer);
	static int GetLEDState(ControllerLEDEnum LightId, UCHAR *ledBuffer);

	// Get Inputs
	static UCHAR GetAxisRaw(AxisEnum axis, UCHAR *rawInputData);

	static bool GetButtonState(ButtonEnum button, UCHAR *rawInputData);
	static GearEnum GetGearLever(UCHAR *rawInputData);
	static float GetRotation(UCHAR *rawInputData);
	static float GetSightChangeX(UCHAR *rawInputData);
	static float GetSightChangeY(UCHAR *rawInputData);
	static float GetAimingX(UCHAR *rawInputData);
	static float GetAimingY(UCHAR *rawInputData);
	static float GetStrafePedal(UCHAR *rawInputData);
	static float GetBrakePedal(UCHAR *rawInputData);
	static float GetThrottle(UCHAR *rawInputData);
	static UCHAR GetTunerDial(UCHAR *rawInputData);

	// Get Controller State
	static ControllerState GetState(UCHAR *rawInputData);

	// LED Behavior Helpers
	static void DimAllLEDs(UCHAR *ledBuffer);
	static void SetAllButtonLEDs(UCHAR *ledBuffer, UCHAR *inputbuffer);
	static void SetGearShiftLED(UCHAR *ledBuffer, UCHAR *inputSwap);

	// Proxy methods for WinUsb I/O
	BOOL WriteToBulkEndpoint(UCHAR* pID, UCHAR *szBuffer, ULONG cbSize, ULONG* pcbWritten);
	BOOL ReadFromBulkEndpoint(UCHAR *pID, UCHAR *szBuffer, ULONG cbSize, ULONG *pcbRead);

public:
	SteelBattalionController(WINUSB_INTERFACE_HANDLE handle);
	~SteelBattalionController();
};

