#include "SteelBattalionController.h"
using namespace std;

const char *commPipeName = "sbc_comm_CF3BD514-7B12-4D18-BFB2-60BB0F82E003";

#pragma region Button Masks

ButtonMask::ButtonMask(int bytePos, UCHAR mask) :
	bytePos(bytePos),
	mask(mask)
{
}

ButtonMask::ButtonMask() : bytePos(0), mask(0) { }

bool SteelBattalionController::MasksInitialized = false;
std::map<ButtonEnum, ButtonMask> SteelBattalionController::Masks;

void SteelBattalionController::InitMasks()
{
	if (!MasksInitialized)
	{
		MasksInitialized = true;
		Masks.insert_or_assign(ButtonEnum::RightJoyMainWeapon, ButtonMask(2, 0x01));
		Masks.insert_or_assign(ButtonEnum::RightJoyFire, ButtonMask(2, 0x02));
		Masks.insert_or_assign(ButtonEnum::RightJoyLockOn, ButtonMask(2, 0x04));
		Masks.insert_or_assign(ButtonEnum::CockpitHatch, ButtonMask(2, 0x10));
		Masks.insert_or_assign(ButtonEnum::Ignition, ButtonMask(2, 0x20));
		Masks.insert_or_assign(ButtonEnum::Start, ButtonMask(2, 0x40));
		Masks.insert_or_assign(ButtonEnum::Eject, ButtonMask(2, 0x08));
		Masks.insert_or_assign(ButtonEnum::MultiMonOpenClose, ButtonMask(2, 0x80));
		Masks.insert_or_assign(ButtonEnum::MultiMonMapZoomInOut, ButtonMask(3, 0x01));
		Masks.insert_or_assign(ButtonEnum::MultiMonModeSelect, ButtonMask(3, 0x02));
		Masks.insert_or_assign(ButtonEnum::MultiMonSubMonitor, ButtonMask(3, 0x04));
		Masks.insert_or_assign(ButtonEnum::MainMonZoomIn, ButtonMask(3, 0x08));
		Masks.insert_or_assign(ButtonEnum::MainMonZoomOut, ButtonMask(3, 0x10));
		Masks.insert_or_assign(ButtonEnum::Washing, ButtonMask(4, 0x01));
		Masks.insert_or_assign(ButtonEnum::Extinguisher, ButtonMask(4, 0x02));
		Masks.insert_or_assign(ButtonEnum::Chaff, ButtonMask(4, 0x04));
		Masks.insert_or_assign(ButtonEnum::WeaponConMain, ButtonMask(5, 0x02));
		Masks.insert_or_assign(ButtonEnum::WeaponConSub, ButtonMask(5, 0x04));
		Masks.insert_or_assign(ButtonEnum::WeaponConMagazine, ButtonMask(5, 0x08));
		Masks.insert_or_assign(ButtonEnum::FunctionFSS, ButtonMask(3, 0x20));
		Masks.insert_or_assign(ButtonEnum::FunctionManipulator, ButtonMask(3, 0x40));
		Masks.insert_or_assign(ButtonEnum::FunctionLineColorChange, ButtonMask(3, 0x80));
		Masks.insert_or_assign(ButtonEnum::FunctionTankDetach, ButtonMask(4, 0x08));
		Masks.insert_or_assign(ButtonEnum::FunctionOverride, ButtonMask(4, 0x10));
		Masks.insert_or_assign(ButtonEnum::FunctionNightScope, ButtonMask(4, 0x20));
		Masks.insert_or_assign(ButtonEnum::FunctionF1, ButtonMask(4, 0x40));
		Masks.insert_or_assign(ButtonEnum::FunctionF2, ButtonMask(4, 0x80));
		Masks.insert_or_assign(ButtonEnum::FunctionF3, ButtonMask(5, 0x01));
		Masks.insert_or_assign(ButtonEnum::Comm1, ButtonMask(5, 0x10));
		Masks.insert_or_assign(ButtonEnum::Comm2, ButtonMask(5, 0x20));
		Masks.insert_or_assign(ButtonEnum::Comm3, ButtonMask(5, 0x40));
		Masks.insert_or_assign(ButtonEnum::Comm4, ButtonMask(5, 0x80));
		Masks.insert_or_assign(ButtonEnum::Comm5, ButtonMask(6, 0x01));
		Masks.insert_or_assign(ButtonEnum::LeftJoySightChange, ButtonMask(6, 0x02));
		Masks.insert_or_assign(ButtonEnum::ToggleFilterControl, ButtonMask(6, 0x04));
		Masks.insert_or_assign(ButtonEnum::ToggleOxygenSupply, ButtonMask(6, 0x08));
		Masks.insert_or_assign(ButtonEnum::ToggleFuelFlowRate, ButtonMask(6, 0x10));
		Masks.insert_or_assign(ButtonEnum::ToggleBufferMaterial, ButtonMask(6, 0x20));
		Masks.insert_or_assign(ButtonEnum::ToggleVTLocation, ButtonMask(6, 0x40));
	}
}

#pragma endregion ButtonMasks

#pragma region Enum Lists

ControllerLEDEnum ControllerLEDEnums[] = {
	ControllerLEDEnum::EmergencyEject,
	ControllerLEDEnum::CockpitHatch,
	ControllerLEDEnum::Ignition,
	ControllerLEDEnum::Start,
	ControllerLEDEnum::OpenClose,
	ControllerLEDEnum::MapZoomInOut,
	ControllerLEDEnum::ModeSelect,
	ControllerLEDEnum::SubMonitorModeSelect,
	ControllerLEDEnum::MainMonitorZoomIn,
	ControllerLEDEnum::MainMonitorZoomOut,
	ControllerLEDEnum::Gear5,
	ControllerLEDEnum::Gear4,
	ControllerLEDEnum::Gear3,
	ControllerLEDEnum::Gear2,
	ControllerLEDEnum::Gear1,
	ControllerLEDEnum::GearN,
	ControllerLEDEnum::GearR,
	ControllerLEDEnum::Comm5,
	ControllerLEDEnum::Comm4,
	ControllerLEDEnum::Comm3,
	ControllerLEDEnum::Comm2,
	ControllerLEDEnum::Comm1,
	ControllerLEDEnum::MagazineChange,
	ControllerLEDEnum::SubWeaponControl,
	ControllerLEDEnum::MainWeaponControl,
	ControllerLEDEnum::F3,
	ControllerLEDEnum::F2,
	ControllerLEDEnum::F1,
	ControllerLEDEnum::NightScope,
	ControllerLEDEnum::Override,
	ControllerLEDEnum::TankDetach,
	ControllerLEDEnum::Chaff,
	ControllerLEDEnum::Extinguisher,
	ControllerLEDEnum::Washing,
	ControllerLEDEnum::LineColorChange,
	ControllerLEDEnum::Manipulator,
	ControllerLEDEnum::ForecastShootingSystem
};

ControllerLEDEnum GearLEDEnums[] = {
	ControllerLEDEnum::Gear5,
	ControllerLEDEnum::Gear4,
	ControllerLEDEnum::Gear3,
	ControllerLEDEnum::Gear2,
	ControllerLEDEnum::Gear1,
	ControllerLEDEnum::GearN,
	ControllerLEDEnum::GearR,
};

ButtonEnum ButtonEnums[] = {
	ButtonEnum::RightJoyMainWeapon,
	ButtonEnum::RightJoyFire,
	ButtonEnum::RightJoyLockOn,
	ButtonEnum::CockpitHatch,
	ButtonEnum::Ignition,
	ButtonEnum::Start,
	ButtonEnum::Eject,
	ButtonEnum::MultiMonOpenClose,
	ButtonEnum::MultiMonMapZoomInOut,
	ButtonEnum::MultiMonModeSelect,
	ButtonEnum::MultiMonSubMonitor,
	ButtonEnum::MainMonZoomIn,
	ButtonEnum::MainMonZoomOut,
	ButtonEnum::Washing,
	ButtonEnum::Extinguisher,
	ButtonEnum::Chaff,
	ButtonEnum::WeaponConMain,
	ButtonEnum::WeaponConSub,
	ButtonEnum::WeaponConMagazine,
	ButtonEnum::FunctionFSS,
	ButtonEnum::FunctionManipulator,
	ButtonEnum::FunctionLineColorChange,
	ButtonEnum::FunctionTankDetach,
	ButtonEnum::FunctionOverride,
	ButtonEnum::FunctionNightScope,
	ButtonEnum::FunctionF1,
	ButtonEnum::FunctionF2,
	ButtonEnum::FunctionF3,
	ButtonEnum::Comm1,
	ButtonEnum::Comm2,
	ButtonEnum::Comm3,
	ButtonEnum::Comm4,
	ButtonEnum::Comm5,
	ButtonEnum::LeftJoySightChange,
	ButtonEnum::ToggleFilterControl,
	ButtonEnum::ToggleOxygenSupply,
	ButtonEnum::ToggleFuelFlowRate,
	ButtonEnum::ToggleBufferMaterial,
	ButtonEnum::ToggleVTLocation
};

AxisEnum AxisEnums[] = {
	AxisEnum::AimingX,
	AxisEnum::AimingY,
	AxisEnum::BrakePedal,
	AxisEnum::Rotation,
	AxisEnum::SightChangeX,
	AxisEnum::SightChangeY,
	AxisEnum::StrafePedal,
	AxisEnum::Throttle,
};

#pragma endregion Enum Lists

#pragma pack(push, 1)
struct ButtonStateChanged
{
	MessageHeader header = MessageHeader::ButtonChanged;
	ButtonEnum button;
	UCHAR state;
};

struct AxisStateChanged
{
	MessageHeader header = MessageHeader::AxisChanged;
	AxisEnum axis;
	float state;
};

struct GearChangedMessage
{
	MessageHeader header = MessageHeader::GearChanged;
	GearEnum Gear;
};

struct TunerChangedMessage
{
	MessageHeader header = MessageHeader::TunerChanged;
	UCHAR channel;
};

struct ControllerStateMessage
{
	MessageHeader header = MessageHeader::ControllerState;
	ControllerState state;
};
#pragma pack(pop)

SteelBattalionController::SteelBattalionController(WINUSB_INTERFACE_HANDLE handle) : 
	commPipe(nullptr),
	m_WinUsb(new WinUsb(handle))
{
	Init();
}

SteelBattalionController::~SteelBattalionController()
{
	shutdown.store(true);
	if(ledThread != nullptr)
		ledThread->join();
	if (inputThread != nullptr)
		inputThread->join();
	if (pipeThread != nullptr)
		pipeThread->join();

	if (commPipe != nullptr)
		delete commPipe;

	if (ledState != nullptr)
		delete[] ledState;
	if (inputState != nullptr)
		delete[] inputState;

	if(m_WinUsb != nullptr)
		delete m_WinUsb;
}

void SteelBattalionController::Init()
{
	InitMasks();
	ledState = new UCHAR[32];
	inputState = new UCHAR[26];
	memset(ledState, 0, 32 * sizeof(UCHAR));
	memset(inputState, 0, 26 * sizeof(UCHAR));
	shutdown.store(false);

	ledThread = new thread(ledThreadFunc, this);
	inputThread = new thread(inputThreadFunc, this);

	commPipe = new NamedPipe(commPipeName);
	pipeThread = new thread(pipeThreadFunc, this);
}

void SteelBattalionController::ledThreadFunc(SteelBattalionController *sbc)
{
	UCHAR *ledSwap = new UCHAR[32];
	UCHAR *inputSwap = new UCHAR[26];
	UCHAR pipeId = SteelBattalionController::PipeOutId;
	while (!sbc->shutdown.load())
	{
		{
			std::lock_guard<mutex> lk(sbc->ledThreadMutex);
			memcpy(ledSwap, sbc->ledState, 32 * sizeof(UCHAR));
		}
		{
			std::lock_guard<mutex> lk(sbc->inputThreadMutex);
			memcpy(inputSwap, sbc->inputState, 26 * sizeof(UCHAR));
		}

		DimAllLEDs(ledSwap);
		SetGearShiftLED(ledSwap, inputSwap);
		SetAllButtonLEDs(ledSwap, inputSwap);

		ULONG bytesWritten;
		if(sbc->WriteToBulkEndpoint(&pipeId, ledSwap, 32, &bytesWritten))
		{
			std::lock_guard<mutex> lk(sbc->ledThreadMutex);
			memcpy(sbc->ledState, ledSwap, 32 * sizeof(UCHAR));
		}
		std::this_thread::sleep_for(10ms);
	}
	delete[] ledSwap;
	delete[] inputSwap;
}

void SteelBattalionController::inputThreadFunc(SteelBattalionController *sbc)
{
	UCHAR *inputSwap = new UCHAR[26];
	UCHAR pipeId = SteelBattalionController::PipeInId;

	while (!sbc->shutdown.load())
	{
		ULONG bytesRead;
		if(sbc->ReadFromBulkEndpoint(&pipeId, inputSwap, 26, &bytesRead))
		{
			std::lock_guard<mutex> lk(sbc->inputThreadMutex);
			memcpy(sbc->inputState, inputSwap, 26 * sizeof(UCHAR));
		}
		
		std::this_thread::sleep_for(10ms);
	}
	delete[] inputSwap;
}

void SteelBattalionController::pipeThreadFunc(SteelBattalionController *sbc) 
{
	//UCHAR *ledSwap = new UCHAR[32];
	UCHAR *inputSwap = new UCHAR[26];
	ControllerState state;
	ControllerState previousState;
	memset(&state, 0, sizeof(ControllerState));
	memset(&previousState, 0, sizeof(ControllerState));
	
	while (!sbc->shutdown.load())
	{
		{	// Get the latest input state
			std::lock_guard<mutex> lk(sbc->inputThreadMutex);
			memcpy(inputSwap, sbc->inputState, 26 * sizeof(UCHAR));
			previousState = state;
			state = sbc->GetState(inputSwap);
		}

		if (!sbc->commPipe->IsConnected())
		{
			if (sbc->commPipe->Connect())
			{
				ControllerStateMessage msg;
				msg.state = state;
				sbc->commPipe->Write(&msg, sizeof(ControllerStateMessage));
			}
		}
		else
		{
			// Send updates for individual controls as necessary
			for (auto axis : AxisEnums)
			{
				bool changed = false;
				float value = 0.0f;
#pragma region Get Axis State Changed and Value
				switch (axis)
				{
				case AxisEnum::AimingX:
					changed = (state.AimingX != previousState.AimingX);
					value = state.AimingX;
					break;
				case AxisEnum::AimingY:
					changed = (state.AimingY != previousState.AimingY);
					value = state.AimingY;
					break;
				case AxisEnum::BrakePedal:
					changed = (state.BrakePedal != previousState.BrakePedal);
					value = state.BrakePedal;
					break;
				case AxisEnum::Rotation:
					changed = (state.Rotation != previousState.Rotation);
					value = state.Rotation;
					break;
				case AxisEnum::SightChangeX:
					changed = (state.SightChangeX != previousState.SightChangeX);
					value = state.SightChangeX;
					break;
				case AxisEnum::SightChangeY:
					changed = (state.SightChangeY != previousState.SightChangeY);
					value = state.SightChangeY;
					break;
				case AxisEnum::StrafePedal:
					changed = (state.StrafePedal != previousState.StrafePedal);
					value = state.StrafePedal;
					break;
				case AxisEnum::Throttle:
					changed = (state.GasPedal != previousState.GasPedal);
					value = state.GasPedal;
					break;
				}
#pragma endregion Get Axis State Changed and Value
				if (changed)
				{
					AxisStateChanged msg;
					msg.axis = axis;
					msg.state = value;
					sbc->commPipe->Write(&msg, sizeof(msg));
				}
			}

			for (auto button : ButtonEnums)
			{
				bool changed = false;
				UCHAR value = 0;
#pragma region Get Button State Change and Value
				switch (button)
				{
				case ButtonEnum::Chaff:
					changed = (state.Chaff != previousState.Chaff);
					value = state.Chaff;
					break;
				case ButtonEnum::CockpitHatch:
					changed = (state.CockpitHatch != previousState.CockpitHatch);
					value = state.CockpitHatch;
					break;
				case ButtonEnum::Comm1:
					changed = (state.Comm1 != previousState.Comm1);
					value = state.Comm1;
					break;
				case ButtonEnum::Comm2:
					changed = (state.Comm2 != previousState.Comm2);
					value = state.Comm2;
					break;
				case ButtonEnum::Comm3:
					changed = (state.Comm3 != previousState.Comm3);
					value = state.Comm3;
					break;
				case ButtonEnum::Comm4:
					changed = (state.Comm4 != previousState.Comm4);
					value = state.Comm4;
					break;
				case ButtonEnum::Comm5:
					changed = (state.Comm5 != previousState.Comm5);
					value = state.Comm5;
					break;
				case ButtonEnum::Eject:
					changed = (state.Eject != previousState.Eject);
					value = state.Eject;
					break;
				case ButtonEnum::Extinguisher:
					changed = (state.Extinguisher != previousState.Extinguisher);
					value = state.Extinguisher;
					break;
				case ButtonEnum::FunctionF1:
					changed = (state.F1 != previousState.F1);
					value = state.F1;
					break;
				case ButtonEnum::FunctionF2:
					changed = (state.F2 != previousState.F2);
					value = state.F2;
					break;
				case ButtonEnum::FunctionF3:
					changed = (state.F3 != previousState.F3);
					value = state.F3;
					break;
				case ButtonEnum::FunctionFSS:
					changed = (state.ForecastShootingSystem != previousState.ForecastShootingSystem);
					value = state.ForecastShootingSystem;
					break;
				case ButtonEnum::FunctionLineColorChange:
					changed = (state.LineColorChange != previousState.LineColorChange);
					value = state.LineColorChange;
					break;
				case ButtonEnum::FunctionManipulator:
					changed = (state.Manipulator != previousState.Manipulator);
					value = state.Manipulator;
					break;
				case ButtonEnum::FunctionNightScope:
					changed = (state.NightScope != previousState.NightScope);
					value = state.NightScope;
					break;
				case ButtonEnum::FunctionOverride:
					changed = (state.Override != previousState.Override);
					value = state.Override;
					break;
				case ButtonEnum::FunctionTankDetach:
					changed = (state.TankDetach != previousState.TankDetach);
					value = state.TankDetach;
					break;
				case ButtonEnum::Ignition:
					changed = (state.Ignition != previousState.Ignition);
					value = state.Ignition;
					break;
				case ButtonEnum::LeftJoySightChange:
					changed = (state.SightChange != previousState.SightChange);
					value = state.SightChange;
					break;
				case ButtonEnum::MainMonZoomIn:
					changed = (state.MainMonitorZoomIn != previousState.MainMonitorZoomIn);
					value = state.MainMonitorZoomIn;
					break;
				case ButtonEnum::MainMonZoomOut:
					changed = (state.MainMonitorZoomOut != previousState.MainMonitorZoomOut);
					value = state.MainMonitorZoomOut;
					break;
				case ButtonEnum::MultiMonMapZoomInOut:
					changed = (state.MultiMonitorMapZoom != previousState.MultiMonitorMapZoom);
					value = state.MultiMonitorMapZoom;
					break;
				case ButtonEnum::MultiMonModeSelect:
					changed = (state.MultiMonitorModeSelect != previousState.MultiMonitorModeSelect);
					value = state.MultiMonitorModeSelect;
					break;
				case ButtonEnum::MultiMonOpenClose:
					changed = (state.MultiMonitorOpenClose != previousState.MultiMonitorOpenClose);
					value = state.MultiMonitorOpenClose;
					break;
				case ButtonEnum::MultiMonSubMonitor:
					changed = (state.SubMonitorModeSelect != previousState.SubMonitorModeSelect);
					value = state.SubMonitorModeSelect;
					break;
				case ButtonEnum::RightJoyFire:
					changed = (state.SubWeaponFire != previousState.SubWeaponFire);
					value = state.SubWeaponFire;
					break;
				case ButtonEnum::RightJoyLockOn:
					changed = (state.LockOn != previousState.LockOn);
					value = state.LockOn;
					break;
				case ButtonEnum::RightJoyMainWeapon:
					changed = (state.MainWeaponFire != previousState.MainWeaponFire);
					value = state.MainWeaponFire;
					break;
				case ButtonEnum::Start:
					changed = (state.Start != previousState.Start);
					value = state.Start;
					break;
				case ButtonEnum::ToggleBufferMaterial:
					changed = (state.BufferMaterial != previousState.BufferMaterial);
					value = state.BufferMaterial;
					break;
				case ButtonEnum::ToggleFilterControl:
					changed = (state.FilterControlSystem != previousState.FilterControlSystem);
					value = state.FilterControlSystem;
					break;
				case ButtonEnum::ToggleFuelFlowRate:
					changed = (state.FuelFlowRate != previousState.FuelFlowRate);
					value = state.FuelFlowRate;
					break;
				case ButtonEnum::ToggleOxygenSupply:
					changed = (state.OxygenSupplySystem != previousState.OxygenSupplySystem);
					value = state.OxygenSupplySystem;
					break;
				case ButtonEnum::ToggleVTLocation:
					changed = (state.VTLocationMeasurement != previousState.VTLocationMeasurement);
					value = state.VTLocationMeasurement;
					break;
				case ButtonEnum::Washing:
					changed = (state.Washing != previousState.Washing);
					value = state.Washing;
					break;
				case ButtonEnum::WeaponConMagazine:
					changed = (state.MagazineChange != previousState.MagazineChange);
					value = state.MagazineChange;
					break;
				case ButtonEnum::WeaponConMain:
					changed = (state.MainWeaponControl != previousState.MainWeaponControl);
					value = state.MainWeaponControl;
					break;
				case ButtonEnum::WeaponConSub:
					changed = (state.SubWeaponControl != previousState.SubWeaponControl);
					value = state.SubWeaponControl;
					break;
				}
#pragma endregion Get Button State Change and Value
				if (changed)
				{
					ButtonStateChanged msg;
					msg.button = button;
					msg.state = value;
					sbc->commPipe->Write(&msg, sizeof(msg));
				}
			}

			if (state.Gear != previousState.Gear)
			{
				GearChangedMessage msg;
				msg.Gear = state.Gear;
				sbc->commPipe->Write(&msg, sizeof(msg));
			}

			if (state.TunerDial != previousState.TunerDial)
			{
				TunerChangedMessage msg;
				msg.channel = state.TunerDial;
				sbc->commPipe->Write(&msg, sizeof(msg));
			}
		}
		std::this_thread::sleep_for(10ms);
	}
}

void SteelBattalionController::SetLEDState(ControllerLEDEnum LightId, int Intensity, UCHAR *rawLEDData) {
	int hexPos = ((int)LightId) % 2;
	int bytePos = (((int)LightId) - hexPos) / 2;

	if (Intensity > 0x0f) Intensity = 0x0f;

	// Erase the byte position, and set the light intensity
	rawLEDData[bytePos] &= (byte)((hexPos == 1) ? 0x0F : 0xF0);
	rawLEDData[bytePos] += (byte)(Intensity * ((hexPos == 1) ? 0x10 : 0x01));
}

int SteelBattalionController::GetLEDState(ControllerLEDEnum LightId, UCHAR *rawLEDData) {
	int hexPos = ((int)LightId) % 2;
	int bytePos = (((int)LightId) - hexPos) / 2;

	return (((int)rawLEDData[bytePos]) & ((hexPos == 1) ? 0xF0 : 0x0F)) / ((hexPos == 1) ? 0x10 : 0x01);
}

#pragma region Get Inputs

bool SteelBattalionController::GetButtonState(ButtonEnum button, UCHAR *rawInputData)
{
	for (auto it = Masks.begin(); it != Masks.end(); it++)
	{
		if (it->first == button)
		{
			auto mask = it->second;
			return ((rawInputData[mask.bytePos] & mask.mask) != 0x00);
		}
	}
	return false;
}

GearEnum SteelBattalionController::GetGearLever(UCHAR *rawInputData)
{
	return (GearEnum)rawInputData[25];
}

inline float GetFloat(UCHAR raw)
{
	return (float)raw / 255.0f;
}

inline float GetSignedFloat(UCHAR raw)
{
	return (2.0f * GetFloat(raw)) - 1.0f;
}

inline float GetSignedFloat(CHAR raw)
{
	return (float)raw / 128.0f;
}

UCHAR SteelBattalionController::GetAxisRaw(AxisEnum axis, UCHAR *rawInputData)
{
	return rawInputData[1 + (2 * (int)axis)];
}

float SteelBattalionController::GetRotation(UCHAR *rawInputData)
{
	return GetSignedFloat((CHAR)GetAxisRaw(AxisEnum::Rotation, rawInputData));
}

float SteelBattalionController::GetSightChangeX(UCHAR *rawInputData)
{
	return GetSignedFloat((CHAR)GetAxisRaw(AxisEnum::SightChangeX, rawInputData));
}

float SteelBattalionController::GetSightChangeY(UCHAR *rawInputData)
{
	return -GetSignedFloat((CHAR)GetAxisRaw(AxisEnum::SightChangeY, rawInputData));
}

float SteelBattalionController::GetAimingX(UCHAR *rawInputData)
{	
	return GetSignedFloat(GetAxisRaw(AxisEnum::AimingX, rawInputData));
}

float SteelBattalionController::GetAimingY(UCHAR *rawInputData)
{
	return -GetSignedFloat(GetAxisRaw(AxisEnum::AimingY, rawInputData));
}

float SteelBattalionController::GetStrafePedal(UCHAR *rawInputData)
{
	return GetFloat(GetAxisRaw(AxisEnum::StrafePedal, rawInputData));
}

float SteelBattalionController::GetBrakePedal(UCHAR *rawInputData)
{
	return GetFloat(GetAxisRaw(AxisEnum::BrakePedal, rawInputData));
}

float SteelBattalionController::GetThrottle(UCHAR *rawInputData)
{
	return GetFloat(GetAxisRaw(AxisEnum::Throttle, rawInputData));
}

UCHAR SteelBattalionController::GetTunerDial(UCHAR *rawInputData)
{
	return (UCHAR)(rawInputData[24] & 0x0F);
}

ControllerState SteelBattalionController::GetState(UCHAR *rawInputData)
{
	ControllerState state;

#pragma region Populate the Controller State

#pragma region Left Block
	// Gear Lever
	state.Gear = GetGearLever(rawInputData);
	// Toggle Switches
	state.OxygenSupplySystem = GetButtonState(ButtonEnum::ToggleOxygenSupply, rawInputData);
	state.FilterControlSystem = GetButtonState(ButtonEnum::ToggleFilterControl, rawInputData);
	state.VTLocationMeasurement = GetButtonState(ButtonEnum::ToggleVTLocation, rawInputData);
	state.BufferMaterial = GetButtonState(ButtonEnum::ToggleBufferMaterial, rawInputData);
	state.FuelFlowRate = GetButtonState(ButtonEnum::ToggleFuelFlowRate, rawInputData);
	// Rotation Lever
	state.SightChange = GetButtonState(ButtonEnum::LeftJoySightChange, rawInputData);
	state.Rotation = GetRotation(rawInputData);
	state.SightChangeX = GetSightChangeX(rawInputData);
	state.SightChangeY = GetSightChangeY(rawInputData);
#pragma endregion Left Block

#pragma region Center Block
	// Communication Buttons
	state.Comm1 = GetButtonState(ButtonEnum::Comm1, rawInputData);
	state.Comm2 = GetButtonState(ButtonEnum::Comm2, rawInputData);
	state.Comm3 = GetButtonState(ButtonEnum::Comm3, rawInputData);
	state.Comm4 = GetButtonState(ButtonEnum::Comm4, rawInputData);
	state.Comm5 = GetButtonState(ButtonEnum::Comm5, rawInputData);
	// Communication Tuner
	state.TunerDial = GetTunerDial(rawInputData);
	// Function Switches
	state.F1 = GetButtonState(ButtonEnum::FunctionF1, rawInputData);
	state.TankDetach = GetButtonState(ButtonEnum::FunctionTankDetach, rawInputData);
	state.ForecastShootingSystem = GetButtonState(ButtonEnum::FunctionFSS, rawInputData);
	state.F2 = GetButtonState(ButtonEnum::FunctionF2, rawInputData);
	state.Override = GetButtonState(ButtonEnum::FunctionOverride, rawInputData);
	state.Manipulator = GetButtonState(ButtonEnum::FunctionManipulator, rawInputData);
	state.F3 = GetButtonState(ButtonEnum::FunctionF3, rawInputData);
	state.NightScope = GetButtonState(ButtonEnum::FunctionNightScope, rawInputData);
	state.LineColorChange = GetButtonState(ButtonEnum::FunctionLineColorChange, rawInputData);
	// Maintenance Controls
	state.Washing = GetButtonState(ButtonEnum::Washing, rawInputData);
	state.Extinguisher = GetButtonState(ButtonEnum::Extinguisher, rawInputData);
	state.Chaff = GetButtonState(ButtonEnum::Chaff, rawInputData);
	// Weapon Controls
	state.MainWeaponControl = GetButtonState(ButtonEnum::WeaponConMain, rawInputData);
	state.SubWeaponControl = GetButtonState(ButtonEnum::WeaponConSub, rawInputData);
	state.MagazineChange = GetButtonState(ButtonEnum::WeaponConMagazine, rawInputData);
#pragma endregion Center Block

#pragma region Right Block
	// Aiming Lever
	state.AimingX = GetAimingX(rawInputData);
	state.AimingY = GetAimingY(rawInputData);
	state.LockOn = GetButtonState(ButtonEnum::RightJoyLockOn, rawInputData);
	state.MainWeaponFire = GetButtonState(ButtonEnum::RightJoyMainWeapon, rawInputData);
	state.SubWeaponFire = GetButtonState(ButtonEnum::RightJoyFire, rawInputData);
	// Multi Monitor
	state.MultiMonitorOpenClose = GetButtonState(ButtonEnum::MultiMonOpenClose, rawInputData);
	state.MultiMonitorMapZoom = GetButtonState(ButtonEnum::MultiMonMapZoomInOut, rawInputData);
	state.MultiMonitorModeSelect = GetButtonState(ButtonEnum::MultiMonModeSelect, rawInputData);
	state.SubMonitorModeSelect = GetButtonState(ButtonEnum::MultiMonSubMonitor, rawInputData);
	// Main Monitor Zoom
	state.MainMonitorZoomIn = GetButtonState(ButtonEnum::MainMonZoomIn, rawInputData);
	state.MainMonitorZoomOut = GetButtonState(ButtonEnum::MainMonZoomOut, rawInputData);
	// Startup Sequence
	state.CockpitHatch = GetButtonState(ButtonEnum::CockpitHatch, rawInputData);
	state.Ignition = GetButtonState(ButtonEnum::Ignition, rawInputData);
	state.Start = GetButtonState(ButtonEnum::Start, rawInputData);
	// Eject - Cmd
	state.Eject = GetButtonState(ButtonEnum::Eject, rawInputData);

	// -- Pedals
	state.StrafePedal = GetStrafePedal(rawInputData);
	state.BrakePedal = GetBrakePedal(rawInputData);
	state.GasPedal = GetThrottle(rawInputData);
#pragma endregion Right Block

#pragma endregion Populate the Controller State

	return state;
}

#pragma endregion Get Inputs

void SteelBattalionController::DimAllLEDs(UCHAR *rawLEDData)
{
	for (auto led : ControllerLEDEnums)
	{
		SetLEDState(
			(ControllerLEDEnum)led, 
			max(0, GetLEDState((ControllerLEDEnum)led, rawLEDData) - 1), 
			rawLEDData
		);
	}
}

void SteelBattalionController::SetAllButtonLEDs(UCHAR *ledBuffer, UCHAR *inputBuffer)
{
	for (auto btn : ButtonEnums)
	{
		auto led = GetLED((ButtonEnum)btn);
		if (led != ControllerLEDEnum::None)
		{
			if (GetButtonState((ButtonEnum)btn, inputBuffer))
				SetLEDState(led, 15, ledBuffer);
		}
	}
}

void SteelBattalionController::SetGearShiftLED(UCHAR *rawLEDData, UCHAR *rawInputData)
{
	for(auto led : GearLEDEnums)
		SetLEDState(led, 0, rawLEDData);

	auto gear = GetGearLever(rawInputData);
	if (gear != GearEnum::None)
		SetLEDState(GetLED(gear), 15, rawLEDData);
}

BOOL SteelBattalionController::WriteToBulkEndpoint(UCHAR* pID, UCHAR *szBuffer, ULONG cbSize, ULONG* pcbWritten)
{
	if (m_WinUsb != nullptr)
	{
		return m_WinUsb->WriteToBulkEndpoint(pID, szBuffer, cbSize, pcbWritten);
	}
	return false;
}

BOOL SteelBattalionController::ReadFromBulkEndpoint(UCHAR *pID, UCHAR *szBuffer, ULONG cbSize, ULONG *pcbRead)
{
	if (m_WinUsb != nullptr)
	{
		return m_WinUsb->ReadFromBulkEndpoint(pID, szBuffer, cbSize, pcbRead);
	}
	return false;
}