/*++

Module Name:

    Driver.cpp

Abstract:

    This module contains the implementation of the
    core driver callback object.

Environment:

   Windows User-Mode Driver Framework (WUDF)

--*/

#include "internal.h"
#include "driver.tmh"

HRESULT
CMyDriver::OnDeviceAdd(
    __in IWDFDriver *FxWdfDriver,
    __in IWDFDeviceInitialize *FxDeviceInit
    )
/*++
 
  Routine Description:

    The FX invokes this method when it wants to install our driver on a device
    stack.  This method creates a device callback object, then calls the Fx
    to create an Fx device object and associate the new callback object with
    it.

  Arguments:

    FxWdfDriver - the Fx driver object.

    FxDeviceInit - the initialization information for the device.

  Return Value:

    status

--*/
{
    HRESULT hr = S_OK;
    CMyDevice *device = NULL;

    //
    // Create device callback object
    //
    hr = CMyDevice::CreateInstanceAndInitialize(FxWdfDriver,
                                                FxDeviceInit,
                                                &device);

    //
    // Call the device's construct method.  This 
    // allows the device to create any queues or other structures that it
    // needs now that the corresponding fx device object has been created.
    //
    if (SUCCEEDED(hr))
    {
        hr = device->Configure();
    }

    return hr;
}
