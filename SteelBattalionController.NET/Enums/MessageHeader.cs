namespace Net.Enums
{
    enum MessageHeader : byte
    {
        NoMessage = 0,
        SetLED = 1,
        SetLEDs = 2,
        ButtonChanged = 3,
        AxisChanged = 4,
        GearChanged = 5,
        TunerChanged = 6,
        ControllerState = 7
    }
}
