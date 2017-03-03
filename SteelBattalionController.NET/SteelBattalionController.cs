using Net.Classes;
using Net.Enums;
using System;
using System.ComponentModel;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Threading;

namespace Net
{
    public class SteelBattalionController : INotifyPropertyChanged, IDisposable
    {
        private const string pipeName = "sbc_comm_CF3BD514-7B12-4D18-BFB2-60BB0F82E003";
        private Thread listeningThread;         // The thread in which the process listens for state changes to the Steel Battalion Controller
        private NamedPipeServerStream server;   // The pipe server that the driver will connect to
        private IAsyncResult iar;               // The return value for an async wait for connect call

        #region Properties

        #region Left Block

        private Gear gear;
        public Gear Gear
        {
            get
            {
                return gear;
            }
            set
            {
                if (gear != value)
                {
                    gear = value;
                    OnPropertyChanged("Gear");
                }
            }
        }

        private float rotation;
        public float Rotation
        {
            get
            {
                return rotation;
            }
            set
            {
                if (rotation != value)
                {
                    rotation = value;
                    OnPropertyChanged("Rotation");
                }
            }
        }

        private float sightChangeX; 
        public float SightChangeX
        {
            get
            {
                return sightChangeX;
            }
            set
            {
                if (sightChangeX != value)
                {
                    sightChangeX = value;
                    OnPropertyChanged("SightChangeX");
                }
            }
        }

        private float sightChangeY;
        public float SightChangeY
        {
            get
            {
                return sightChangeY;
            }
            set
            {
                if (sightChangeY != value)
                {
                    sightChangeY = value;
                    OnPropertyChanged("SightChangeY");
                }
            }
        }

        private bool sightChangePressed;
        public bool SightChangePressed
        {
            get
            {
                return sightChangePressed;
            }
            set
            {
                if (sightChangePressed != value)
                {
                    sightChangePressed = value;
                    OnPropertyChanged("SightChangePressed");
                }
            }
        }

        private bool oxygenSupplyEnabled;
        public bool OxygenSupplyEnabled
        {
            get
            {
                return oxygenSupplyEnabled;
            }
            set
            {
                if (oxygenSupplyEnabled != value)
                {
                    oxygenSupplyEnabled = value;
                    OnPropertyChanged("OxygenSupplyEnabled");
                }
            }
        }

        private bool filterControlSystemEnabled;
        public bool FilterControlSystemEnabled
        {
            get
            {
                return filterControlSystemEnabled;
            }
            set
            {
                if (filterControlSystemEnabled != value)
                {
                    filterControlSystemEnabled = value;
                    OnPropertyChanged("FilterControlSystemEnabled");
                }
            }
        }

        private bool vtLocationMeasurementEnabled;
        public bool VTLocationMeasurementEnabled
        {
            get
            {
                return vtLocationMeasurementEnabled;
            }
            set
            {
                if (vtLocationMeasurementEnabled != value)
                {
                    vtLocationMeasurementEnabled = value;
                    OnPropertyChanged("VTLocationMeasurementEnabled");
                }
            }
        }

        private bool bufferMaterialEnabled;
        public bool BufferMaterialEnabled
        {
            get
            {
                return bufferMaterialEnabled;
            }
            set
            {
                if (bufferMaterialEnabled != value)
                {
                    bufferMaterialEnabled = value;
                    OnPropertyChanged("BufferMaterialEnabled");
                }
            }
        }

        private bool fuelFlowRateEnabled;
        public bool FuelFlowRateEnabled
        {
            get
            {
                return fuelFlowRateEnabled;
            }
            set
            {
                if (fuelFlowRateEnabled != value)
                {
                    fuelFlowRateEnabled = value;
                    OnPropertyChanged("FuelFlowRateEnabled");
                }
            }
        }

        #endregion Left Block

        #region Center Block

        private bool comm1;
        public bool Comm1Pressed
        {
            get
            {
                return comm1;
            }
            set
            {
                if (comm1 != value)
                {
                    comm1 = value;
                    OnPropertyChanged("Comm1Pressed");
                }
            }
        }

        private bool comm2;
        public bool Comm2Pressed
        {
            get
            {
                return comm2;
            }
            set
            {
                if (comm2 != value)
                {
                    comm2 = value;
                    OnPropertyChanged("Comm2Pressed");
                }
            }
        }

        private bool comm3;
        public bool Comm3Pressed
        {
            get
            {
                return comm3;
            }
            set
            {
                if (comm3 != value)
                {
                    comm3 = value;
                    OnPropertyChanged("Comm3Pressed");
                }
            }
        }

        private bool comm4;
        public bool Comm4Pressed
        {
            get
            {
                return comm4;
            }
            set
            {
                if (comm4 != value)
                {
                    comm4 = value;
                    OnPropertyChanged("Comm4Pressed");
                }
            }
        }

        private bool comm5;
        public bool Comm5Pressed
        {
            get
            {
                return comm5;
            }
            set
            {
                if (comm5 != value)
                {
                    comm5 = value;
                    OnPropertyChanged("Comm5Pressed");
                }
            }
        }

        private short tunerDial;
        public short TunerDial
        {
            get
            {
                return tunerDial;
            }
            set
            {
                if (tunerDial != value)
                {
                    tunerDial = value;
                    OnPropertyChanged("TunerDial");
                }
            }
        }

        private bool f1;
        public bool F1Pressed
        {
            get
            {
                return f1;
            }
            set
            {
                if (f1 != value)
                {
                    f1 = value;
                    OnPropertyChanged("F1Pressed");
                }
            }
        }

        private bool f2;
        public bool F2Pressed
        {
            get
            {
                return f2;
            }
            set
            {
                if (f2 != value)
                {
                    f2 = value;
                    OnPropertyChanged("F2Pressed");
                }
            }
        }

        private bool f3;
        public bool F3Pressed
        {
            get
            {
                return f3;
            }
            set
            {
                if (f3 != value)
                {
                    f3 = value;
                    OnPropertyChanged("F3Pressed");
                }
            }
        }

        private bool tankDetachPressed;
        public bool TankDetachPressed
        {
            get
            {
                return tankDetachPressed;
            }
            set
            {
                if (tankDetachPressed != value)
                {
                    tankDetachPressed = value;
                    OnPropertyChanged("TankDetachPressed");
                }
            }
        }

        private bool overridePressed;
        public bool OverridePressed
        {
            get
            {
                return overridePressed;
            }
            set
            {
                if (overridePressed != value)
                {
                    overridePressed = value;
                    OnPropertyChanged("OverridePressed");
                }
            }
        }

        private bool nightScopePressed;
        public bool NightScopePressed
        {
            get
            {
                return nightScopePressed;
            }
            set
            {
                if (nightScopePressed != value)
                {
                    nightScopePressed = value;
                    OnPropertyChanged("NightScopePressed");
                }
            }
        }

        private bool forecastShootingSystemPressed;
        public bool ForecastShootingSystemPressed
        {
            get
            {
                return forecastShootingSystemPressed;
            }
            set
            {
                if (forecastShootingSystemPressed != value)
                {
                    forecastShootingSystemPressed = value;
                    OnPropertyChanged("ForecastShootingSystemPressed");
                }
            }
        }

        private bool manipulatorPressed;
        public bool ManipulatorPressed
        {
            get
            {
                return manipulatorPressed;
            }
            set
            {
                if (manipulatorPressed != value)
                {
                    manipulatorPressed = value;
                    OnPropertyChanged("ManipulatorPressed");
                }
            }
        }

        private bool lineColorChangePressed;
        public bool LineColorChangePressed
        {
            get
            {
                return lineColorChangePressed;
            }
            set
            {
                if (lineColorChangePressed != value)
                {
                    lineColorChangePressed = value;
                    OnPropertyChanged("LineColorChangePressed");
                }
            }
        }

        private bool washingPressed;
        public bool WashingPressed
        {
            get
            {
                return washingPressed;
            }
            set
            {
                if (washingPressed != value)
                {
                    washingPressed = value;
                    OnPropertyChanged("WashingPressed");
                }
            }
        }

        private bool mainWeaponControlPressed;
        public bool MainWeaponControlPressed
        {
            get
            {
                return mainWeaponControlPressed;
            }
            set
            {
                if (mainWeaponControlPressed != value)
                {
                    mainWeaponControlPressed = value;
                    OnPropertyChanged("MainWeaponControlPressed");
                }
            }
        }

        private bool extinguisherPressed;
        public bool ExtinguisherPressed
        {
            get
            {
                return extinguisherPressed;
            }
            set
            {
                if (extinguisherPressed != value)
                {
                    extinguisherPressed = value;
                    OnPropertyChanged("ExtinguisherPressed");
                }
            }
        }
        
        private bool subWeaponControlPressed;
        public bool SubWeaponControlPressed
        {
            get
            {
                return subWeaponControlPressed;
            }
            set
            {
                if (subWeaponControlPressed != value)
                {
                    subWeaponControlPressed = value;
                    OnPropertyChanged("SubWeaponControlPressed");
                }
            }
        }

        private bool chaffPressed;
        public bool ChaffPressed
        {
            get
            {
                return chaffPressed;
            }
            set
            {
                if (chaffPressed != value)
                {
                    chaffPressed = value;
                    OnPropertyChanged("ChaffPressed");
                }
            }
        }

        private bool magazineChangePressed;
        public bool MagazineChangePressed
        {
            get
            {
                return magazineChangePressed;
            }
            set
            {
                if (magazineChangePressed != value)
                {
                    magazineChangePressed = value;
                    OnPropertyChanged("MagazineChangePressed");
                }
            }
        }

        #endregion Center Block

        #region Right Block

        private float aimingX;
        public float AimingX
        {
            get
            {
                return aimingX;
            }
            set
            {
                if (aimingX != value)
                {
                    aimingX = value;
                    OnPropertyChanged("AimingX");
                }
            }
        }

        private float aimingY;
        public float AimingY
        {
            get
            {
                return aimingY;
            }
            set
            {
                if (aimingY != value)
                {
                    aimingY = value;
                    OnPropertyChanged("AimingY");
                }
            }
        }

        private bool lockOn;
        public bool LockOnPressed
        {
            get
            {
                return lockOn;
            }
            set
            {
                if (lockOn != value)
                {
                    lockOn = value;
                    OnPropertyChanged("LockOnPressed");
                }
            }
        }

        private bool mainWeaponFire;
        public bool MainWeaponFirePressed
        {
            get
            {
                return mainWeaponFire;
            }
            set
            {
                if (mainWeaponFire != value)
                {
                    mainWeaponFire = value;
                    OnPropertyChanged("MainWeaponFirePressed");
                }
            }
        }

        private bool subWeaponFire;
        public bool SubWeaponFirePressed
        {
            get
            {
                return subWeaponFire;
            }
            set
            {
                if (subWeaponFire != value)
                {
                    subWeaponFire = value;
                    OnPropertyChanged("SubWeaponFirePressed");
                }
            }
        }

        private bool multiMonitorOpenClose;
        public bool MultiMonitorOpenClosePressed
        {
            get
            {
                return multiMonitorOpenClose;
            }
            set
            {
                if (multiMonitorOpenClose != value)
                {
                    multiMonitorOpenClose = value;
                    OnPropertyChanged("MultiMonitorOpenClosePressed");
                }
            }
        }

        private bool multiMonitorModeSelect;
        public bool MultiMonitorModeSelectPressed
        {
            get
            {
                return multiMonitorModeSelect;
            }
            set
            {
                if (multiMonitorModeSelect != value)
                {
                    multiMonitorModeSelect = value;
                    OnPropertyChanged("MultiMonitorModeSelectPressed");
                }
            }
        }

        private bool mainMonitorZoomIn;
        public bool MainMonitorZoomInPressed
        {
            get
            {
                return mainMonitorZoomIn;
            }
            set
            {
                if (mainMonitorZoomIn != value)
                {
                    mainMonitorZoomIn = value;
                    OnPropertyChanged("MainMonitorZoomInPressed");
                }
            }
        }

        private bool multiMonitorMapZoom;
        public bool MultiMonitorMapZoomPressed
        {
            get
            {
                return multiMonitorMapZoom;
            }
            set
            {
                if (multiMonitorMapZoom != value)
                {
                    multiMonitorMapZoom = value;
                    OnPropertyChanged("MultiMonitorMapZoomPressed");
                }
            }
        }

        private bool subMonitorModeSelect;
        public bool SubMonitorModeSelectPressed
        {
            get
            {
                return subMonitorModeSelect;
            }
            set
            {
                if (subMonitorModeSelect != value)
                {
                    subMonitorModeSelect = value;
                    OnPropertyChanged("SubMonitorModeSelectPressed");
                }
            }
        }

        private bool mainMonitorZoomOut;
        public bool MainMonitorZoomOutPressed
        {
            get
            {
                return mainMonitorZoomOut;
            }
            set
            {
                if (mainMonitorZoomOut != value)
                {
                    mainMonitorZoomOut = value;
                    OnPropertyChanged("MainMonitorZoomOutPressed");
                }
            }
        }

        private bool startPressed;
        public bool StartPressed
        {
            get
            {
                return startPressed;
            }
            set
            {
                if (startPressed != value)
                {
                    startPressed = value;
                    OnPropertyChanged("StartPressed");
                }
            }
        }

        private bool ignitionPressed;
        public bool IgnitionPressed
        {
            get
            {
                return ignitionPressed;
            }
            set
            {
                if (ignitionPressed != value)
                {
                    ignitionPressed = value;
                    OnPropertyChanged("IgnitionPressed");
                }
            }
        }

        private bool cockpitHatchPressed;
        public bool CockpitHatchPressed
        {
            get
            {
                return cockpitHatchPressed;
            }
            set
            {
                if (cockpitHatchPressed != value)
                {
                    cockpitHatchPressed = value;
                    OnPropertyChanged("CockpitHatchPressed");
                }
            }
        }

        private bool ejectPressed;
        public bool EjectPressed
        {
            get
            {
                return ejectPressed;
            }
            set
            {
                if (ejectPressed != value)
                {
                    ejectPressed = value;
                    OnPropertyChanged("EjectPressed");
                }
            }
        }

        #endregion Right Block

        #region Pedals

        private float strafe;
        public float Strafe
        {
            get
            {
                return strafe;
            }
            set
            {
                if (strafe != value)
                {
                    strafe = value;
                    OnPropertyChanged("Strafe");
                }
            }
        }

        private float brake;
        public float Brake
        {
            get
            {
                return brake;
            }
            set
            {
                if (brake != value)
                {
                    brake = value;
                    OnPropertyChanged("Brake");
                }
            }
        }

        private float gas;
        public float Gas
        {
            get
            {
                return gas;
            }
            set
            {
                if (gas != value)
                {
                    gas = value;
                    OnPropertyChanged("Gas");
                }
            }
        }

        #endregion

        #endregion Properties

        public SteelBattalionController()
        {
            ButtonStateChanged += SteelBattalionController_ButtonStateChanged;
            AxisStateChanged += SteelBattalionController_AxisStateChanged;
            TunerStateChanged += SteelBattalionController_TunerStateChanged;
            GearChanged += SteelBattalionController_GearChanged;

            Connect();
        }

        private void SteelBattalionController_GearChanged(Gear gear)
        {
            Gear = gear;
        }

        private void SteelBattalionController_TunerStateChanged(int channel)
        {
            TunerDial = (short)channel;
        }

        private void SteelBattalionController_AxisStateChanged(Axis axis, float state)
        {
            switch(axis)
            {
                case Axis.Rotation:
                    Rotation = state;
                    break;
                case Axis.SightChangeX:
                    SightChangeX = state;
                    break;
                case Axis.SightChangeY:
                    SightChangeY = state;
                    break;
                case Axis.AimingX:
                    AimingX = state;
                    break;
                case Axis.AimingY:
                    AimingY = state;
                    break;
                case Axis.StrafePedal:
                    Strafe = state;
                    break;
                case Axis.BrakePedal:
                    Brake = state;
                    break;
                case Axis.Throttle:
                    Gas = state;
                    break;
            }
        }

        private void SteelBattalionController_ButtonStateChanged(Button button, bool state)
        {
            switch(button)
            {
                #region Left Block

                case Button.LeftJoySightChange:
                    SightChangePressed = state;
                    break;
                case Button.ToggleOxygenSupply:
                    OxygenSupplyEnabled = state;
                    break;
                case Button.ToggleFilterControl:
                    FilterControlSystemEnabled = state;
                    break;
                case Button.ToggleVTLocation:
                    VTLocationMeasurementEnabled = state;
                    break;
                case Button.ToggleBufferMaterial:
                    BufferMaterialEnabled = state;
                    break;
                case Button.ToggleFuelFlowRate:
                    FuelFlowRateEnabled = state;
                    break;

                #endregion Left Block

                #region Center Block

                case Button.Comm1:
                    Comm1Pressed = state;
                    break;
                case Button.Comm2:
                    Comm2Pressed = state;
                    break;
                case Button.Comm3:
                    Comm3Pressed = state;
                    break;
                case Button.Comm4:
                    Comm4Pressed = state;
                    break;
                case Button.Comm5:
                    Comm5Pressed = state;
                    break;
                case Button.FunctionF1:
                    F1Pressed = state;
                    break;
                case Button.FunctionF2:
                    F2Pressed = state;
                    break;
                case Button.FunctionF3:
                    F3Pressed = state;
                    break;
                case Button.FunctionTankDetach:
                    TankDetachPressed = state;
                    break;
                case Button.FunctionOverride:
                    OverridePressed = state;
                    break;
                case Button.FunctionNightScope:
                    NightScopePressed = state;
                    break;
                case Button.FunctionFSS:
                    ForecastShootingSystemPressed = state;
                    break;
                case Button.FunctionManipulator:
                    ManipulatorPressed = state;
                    break;
                case Button.FunctionLineColorChange:
                    LineColorChangePressed = state;
                    break;
                case Button.Washing:
                    WashingPressed = state;
                    break;
                case Button.Extinguisher:
                    ExtinguisherPressed = state;
                    break;
                case Button.Chaff:
                    ChaffPressed = state;
                    break;
                case Button.WeaponConMain:
                    MainWeaponControlPressed = state;
                    break;
                case Button.WeaponConSub:
                    SubWeaponControlPressed = state;
                    break;
                case Button.WeaponConMagazine:
                    MagazineChangePressed = state;
                    break;

                #endregion Center Block

                #region Right Block

                case Button.RightJoyLockOn:
                    LockOnPressed = state;
                    break;
                case Button.RightJoyMainWeapon:
                    MainWeaponFirePressed = state;
                    break;
                case Button.RightJoyFire:
                    SubWeaponFirePressed = state;
                    break;
                case Button.MultiMonOpenClose:
                    MultiMonitorOpenClosePressed = state;
                    break;
                case Button.MultiMonModeSelect:
                    MultiMonitorModeSelectPressed = state;
                    break;
                case Button.MainMonZoomIn:
                    MainMonitorZoomInPressed = state;
                    break;
                case Button.MultiMonMapZoomInOut:
                    MultiMonitorMapZoomPressed = state;
                    break;
                case Button.SubMonitorModeSelect:
                    SubMonitorModeSelectPressed = state;
                    break;
                case Button.MainMonZoomOut:
                    MainMonitorZoomOutPressed = state;
                    break;
                case Button.Start:
                    StartPressed = state;
                    break;
                case Button.Ignition:
                    IgnitionPressed = state;
                    break;
                case Button.CockpitHatch:
                    CockpitHatchPressed = state;
                    break;
                case Button.Eject:
                    EjectPressed = state;
                    break;

                #endregion Right Block
            }
        }

        private void Connect()
        {
            // Security rule that says anyone can use it so that we know the driver can connect to it
            var sid = new SecurityIdentifier(WellKnownSidType.WorldSid, null);
            var rule = new PipeAccessRule(sid, PipeAccessRights.ReadWrite,
                                          AccessControlType.Allow);
            var security = new PipeSecurity();
            security.AddAccessRule(rule);

            // Create a pipe server stream
            server = new NamedPipeServerStream(
                pipeName,                          // The defined name of the pipe. This must be the same pipe name that the driver is connecting to
                PipeDirection.InOut,               // In/Out read mode. We want to be able to send commands to the controller to adjust the leds
                1,                                 // Only 1 instance of this server at a time
                PipeTransmissionMode.Message,      // We're sending messages
                PipeOptions.Asynchronous,          // We want to be able to read/write the pipe at the same time
                65536,                             // 64KB buffer size
                65536,                             // 64KB buffer size
                security);                         // Use the security rule we made

            iar = server.BeginWaitForConnection(driverConnected, null);
        }

        private void driverConnected(IAsyncResult ar)
        {
            iar = null;
            server.EndWaitForConnection(ar);
            listeningThread = new Thread(listeningThreadFunc);
            listeningThread.IsBackground = true;
            listeningThread.Start();
        }

        private void listeningThreadFunc()
        {
            MessageHeader header = MessageHeader.NoMessage;
            Button button;
            Axis axis;
            Gear gear;
            byte tuner;
            byte bstate;
            float fstate;
            byte[] dword = { 0, 0, 0, 0 };
            ControllerState controller = new ControllerState();
            byte[] controllerStateBytes = new byte[Marshal.SizeOf(controller)];
            IntPtr ptr = IntPtr.Zero;

            do
            {
                try
                {
                    header = (MessageHeader)server.ReadByte();
                    switch (header)
                    {
                        case MessageHeader.ControllerState:
                            if (server.Read(controllerStateBytes, 0, controllerStateBytes.Length) == controllerStateBytes.Length)
                            {
                                var handle = GCHandle.Alloc(controllerStateBytes, GCHandleType.Pinned);
                                controller = (ControllerState)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(ControllerState));
                                handle.Free();
                                FireStateChangedEvents(controller);
                            }
                            break;
                        case MessageHeader.ButtonChanged:
                            button = (Button)server.ReadByte();
                            bstate = (byte)server.ReadByte();
                            ButtonStateChanged?.Invoke(button, bstate != 0);
                            break;
                        case MessageHeader.AxisChanged:
                            axis = (Axis)server.ReadByte();
                            server.Read(dword, 0, 4);
                            fstate = BitConverter.ToSingle(dword, 0);
                            AxisStateChanged?.Invoke(axis, fstate);
                            break;
                        case MessageHeader.GearChanged:
                            gear = (Gear)server.ReadByte();
                            controller.Gear = gear;
                            GearChanged?.Invoke(gear);
                            break;
                        case MessageHeader.TunerChanged:
                            tuner = (byte)server.ReadByte();
                            controller.TunerDial = tuner;
                            TunerStateChanged?.Invoke(tuner);
                            break;
                    }
                }
                catch
                {
                }
            } while (server.IsConnected);

            server.Dispose();
            server = null;
            Connect();
        }

        #region Helpers

        private void FireStateChangedEvents(ControllerState controller)
        {
            AxisStateChanged?.Invoke(Axis.AimingX, controller.AimingX);
            AxisStateChanged?.Invoke(Axis.AimingY, controller.AimingY);
            AxisStateChanged?.Invoke(Axis.BrakePedal, controller.BrakePedal);
            ButtonStateChanged?.Invoke(Button.ToggleBufferMaterial, controller.BufferMaterial != 0);
            ButtonStateChanged?.Invoke(Button.Chaff, controller.Chaff != 0);
            ButtonStateChanged?.Invoke(Button.CockpitHatch, controller.CockpitHatch != 0);
            ButtonStateChanged?.Invoke(Button.Comm1, controller.Comm1 != 0);
            ButtonStateChanged?.Invoke(Button.Comm2, controller.Comm2 != 0);
            ButtonStateChanged?.Invoke(Button.Comm3, controller.Comm3 != 0);
            ButtonStateChanged?.Invoke(Button.Comm4, controller.Comm4 != 0);
            ButtonStateChanged?.Invoke(Button.Comm5, controller.Comm5 != 0);
            ButtonStateChanged?.Invoke(Button.Eject, controller.Eject != 0);
            ButtonStateChanged?.Invoke(Button.Extinguisher, controller.Extinguisher != 0);
            ButtonStateChanged?.Invoke(Button.FunctionF1, controller.F1 != 0);
            ButtonStateChanged?.Invoke(Button.FunctionF2, controller.F2 != 0);
            ButtonStateChanged?.Invoke(Button.FunctionF3, controller.F3 != 0);
            ButtonStateChanged?.Invoke(Button.ToggleFilterControl, controller.FilterControlSystem != 0);
            ButtonStateChanged?.Invoke(Button.FunctionFSS, controller.ForecastShootingSystem != 0);
            ButtonStateChanged?.Invoke(Button.ToggleFuelFlowRate, controller.FuelFlowRate != 0);
            AxisStateChanged?.Invoke(Axis.Throttle, controller.GasPedal);
            GearChanged?.Invoke(controller.Gear);
            ButtonStateChanged?.Invoke(Button.Ignition, controller.Ignition != 0);
            ButtonStateChanged?.Invoke(Button.FunctionLineColorChange, controller.LineColorChange != 0);
            ButtonStateChanged?.Invoke(Button.RightJoyLockOn, controller.LockOn != 0);
            ButtonStateChanged?.Invoke(Button.WeaponConMagazine, controller.MagazineChange != 0);
            ButtonStateChanged?.Invoke(Button.MainMonZoomIn, controller.MainMonitorZoomIn != 0);
            ButtonStateChanged?.Invoke(Button.MainMonZoomOut, controller.MainMonitorZoomOut != 0);
            ButtonStateChanged?.Invoke(Button.WeaponConMain, controller.MainWeaponControl != 0);
            ButtonStateChanged?.Invoke(Button.RightJoyMainWeapon, controller.MainWeaponFire != 0);
            ButtonStateChanged?.Invoke(Button.FunctionManipulator, controller.Manipulator != 0);
            ButtonStateChanged?.Invoke(Button.MultiMonMapZoomInOut, controller.MultiMonitorMapZoom != 0);
            ButtonStateChanged?.Invoke(Button.MultiMonModeSelect, controller.MultiMonitorModeSelect != 0);
            ButtonStateChanged?.Invoke(Button.MultiMonOpenClose, controller.MultiMonitorOpenClose != 0);
            ButtonStateChanged?.Invoke(Button.FunctionNightScope, controller.NightScope != 0);
            ButtonStateChanged?.Invoke(Button.FunctionOverride, controller.Override != 0);
            ButtonStateChanged?.Invoke(Button.ToggleOxygenSupply, controller.OxygenSupplySystem != 0);
            AxisStateChanged?.Invoke(Axis.Rotation, controller.Rotation);
            ButtonStateChanged?.Invoke(Button.LeftJoySightChange, controller.SightChange != 0);
            AxisStateChanged?.Invoke(Axis.SightChangeX, controller.SightChangeX);
            AxisStateChanged?.Invoke(Axis.SightChangeY, controller.SightChangeY);
            ButtonStateChanged?.Invoke(Button.Start, controller.Start != 0);
            AxisStateChanged?.Invoke(Axis.StrafePedal, controller.StrafePedal);
            ButtonStateChanged?.Invoke(Button.SubMonitorModeSelect, controller.SubMonitorModeSelect != 0);
            ButtonStateChanged?.Invoke(Button.WeaponConSub, controller.SubWeaponControl != 0);
            ButtonStateChanged?.Invoke(Button.RightJoyFire, controller.SubWeaponFire != 0);
            ButtonStateChanged?.Invoke(Button.FunctionTankDetach, controller.TankDetach != 0);
            TunerStateChanged?.Invoke(controller.TunerDial);
            ButtonStateChanged?.Invoke(Button.ToggleVTLocation, controller.VTLocationMeasurement != 0);
            ButtonStateChanged?.Invoke(Button.Washing, controller.Washing != 0);
        }

        #endregion Helpers

        #region Events

        public delegate void ButtonStateChangedEvent(Button button, bool state);
        public event ButtonStateChangedEvent ButtonStateChanged;

        public delegate void AxisStateChangedEvent(Axis axis, float state);
        public event AxisStateChangedEvent AxisStateChanged;

        public delegate void GearChangedEvent(Gear gear);
        public event GearChangedEvent GearChanged;

        public delegate void TunerStateChangedEvent(int channel);
        public event TunerStateChangedEvent TunerStateChanged;

        #endregion Events

        #region INotifyPropertyChanged

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion INotifyPropertyChanged

        #region IDisposable

        public void Dispose()
        {
            if (server != null)
            {
                if (server.IsConnected)
                    server.Disconnect();
                server.Dispose();
                iar = null;
                server = null;
            }
            if (listeningThread != null)
            {
                listeningThread.Join();
            }
        }

        #endregion IDisposable
    }
}
