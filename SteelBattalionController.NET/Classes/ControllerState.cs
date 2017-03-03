using Net.Enums;
using System.Runtime.InteropServices;

namespace Net.Classes
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct ControllerState
    {
        public float Rotation;
        public float SightChangeX;
        public float SightChangeY;
        public float AimingX;
        public float AimingY;
        public float StrafePedal;
        public float BrakePedal;
        public float GasPedal;

        public Gear Gear;

        public byte OxygenSupplySystem;
        public byte FilterControlSystem;
        public byte VTLocationMeasurement;
        public byte BufferMaterial;
        public byte FuelFlowRate;
        public byte SightChange;
        public byte Comm1;
        public byte Comm2;
        public byte Comm3;
        public byte Comm4;
        public byte Comm5;
        public byte TunerDial;
        public byte F1;
        public byte TankDetach;
        public byte ForecastShootingSystem;
        public byte F2;
        public byte Override;
        public byte Manipulator;
        public byte F3;
        public byte NightScope;
        public byte LineColorChange;
        public byte Washing;
        public byte Extinguisher;
        public byte Chaff;
        public byte MainWeaponControl;
        public byte SubWeaponControl;
        public byte MagazineChange;
        public byte LockOn;
        public byte MainWeaponFire;
        public byte SubWeaponFire;
        public byte MultiMonitorOpenClose;
        public byte MultiMonitorMapZoom;
        public byte MultiMonitorModeSelect;
        public byte SubMonitorModeSelect;
        public byte MainMonitorZoomIn;
        public byte MainMonitorZoomOut;
        public byte CockpitHatch;
        public byte Ignition;
        public byte Start;
        public byte Eject;
    };
}
