/*++

Module Name:

    Internal.h

Abstract:

    This module contains the local type definitions for the
    driver.

Environment:

    Windows User-Mode Driver Framework (WUDF)

--*/

#pragma once

#include <intsafe.h>
#include <assert.h>

//
// ATL support
//
#include "atlbase.h"
#include "atlcom.h"

//
// Include the WUDF Headers
//

#include "wudfddi.h"
#include "wudfusb.h"

//
// Use specstrings for in/out annotation of function parameters.
//

#include "specstrings.h"

//
// GUID include
//
#include <initguid.h>

//
// Windows IOCTL definitions.
//
#include "winioctl.h"

//
// Device Interface GUID
// 4955e7e4-99bd-4c2e-be1e-29f7df7f8cb0
//
DEFINE_GUID(GUID_DEVINTERFACE_SteelBattalionController,
    0x4955e7e4,0x99bd,0x4c2e,0xbe,0x1e,0x29,0xf7,0xdf,0x7f,0x8c,0xb0);

//
// Define the tracing flags.
//
// Tracing GUID - 68cd8193-32ae-4ec0-a52d-97e1cb1f158e
//

#define WPP_CONTROL_GUIDS                                              \
    WPP_DEFINE_CONTROL_GUID(                                           \
        MyDriver1TraceGuid, (68cd8193,32ae,4ec0,a52d,97e1cb1f158e), \
                                                                            \
        WPP_DEFINE_BIT(MYDRIVER_ALL_INFO)                              \
        WPP_DEFINE_BIT(TRACE_DRIVER)                                   \
        WPP_DEFINE_BIT(TRACE_DEVICE)                                   \
        WPP_DEFINE_BIT(TRACE_QUEUE)                                    \
        )                             

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                                  \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                                 \
    (WPP_LEVEL_ENABLED(flag) &&                                             \
     WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(lvl,flags) \
           WPP_LEVEL_LOGGER(flags)
               
#define WPP_LEVEL_FLAGS_ENABLED(lvl, flags) \
           (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= lvl)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// begin_wpp config
// FUNC Trace{FLAG=MYDRIVER_ALL_INFO}(LEVEL, MSG, ...);
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// end_wpp
//

//
// Forward definition of queue.
//
typedef class CMyIoQueue *PCMyIoQueue;

//
// Include the type specific headers.
//
#include "Driver.h"
#include "Device.h"
#include "IoQueue.h"

//
// Driver specific #defines
//
#define MYDRIVER_TRACING_ID      L"Microsoft\\UMDF\\SteelBattalionController V1.0"

template <typename T>
inline void DriverSafeRelease(T *&t)
{
      if(t)
            t->Release();
      t = NULL;
}


