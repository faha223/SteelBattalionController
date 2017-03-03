/*++

Module Name:

    IoQueue.cpp

Abstract:

    This file implements the I/O queue interface and performs
    the ioctl operations.

Environment:

    Windows User-Mode Driver Framework (WUDF)

--*/

#include "internal.h"
#include "ioqueue.tmh"

 
HRESULT 
CMyIoQueue::CreateInstanceAndInitialize(
    __in IWDFDevice *FxDevice,
    __in CMyDevice *MyDevice,
    __out CMyIoQueue** Queue
    )
/*++

Routine Description:

    CreateInstanceAndInitialize creates an instance of the queue object.

Arguments:
    

Return Value:

    HRESULT indicating success or failure

--*/
{

    CComObject<CMyIoQueue> *pMyQueue = NULL;
    HRESULT hr = S_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Entry");

    //
    // Create a new instance of the device class
    //
    hr = CComObject<CMyIoQueue>::CreateInstance( &pMyQueue );
    if (FAILED(hr))
    {
        TraceEvents(TRACE_LEVEL_ERROR,
                    TRACE_QUEUE,
                    "%!FUNC! Failed to create instance %!hresult!",
                    hr);
        goto Exit;
    }

    //
    // Initialize the instance.
    //
    hr = pMyQueue->Initialize(FxDevice, MyDevice);
    if (FAILED(hr))
    {
        TraceEvents(TRACE_LEVEL_ERROR,
                    TRACE_QUEUE,
                    "%!FUNC! Failed to initialize %!hresult!",
                    hr);
        goto Exit;
    }

    *Queue = pMyQueue;

Exit:

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Exit");

    return hr;
}

HRESULT
CMyIoQueue::Initialize(
    __in IWDFDevice *FxDevice,
    __in CMyDevice *MyDevice
    )
/*++

Routine Description:

    Initialize creates a framework queue and sets up I/O for the queue object.

Arguments:

    FxDevice - Framework device associated with this queue.

    MyDevice - Pointer to the device class object.

Return Value:

    HRESULT indicating success or failure

--*/
{
    IWDFIoQueue *fxQueue = NULL;
    HRESULT hr = S_OK;
    IUnknown *unknown = NULL;

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Entry");
    
    //
    // Make sure we have valid parameters.
    //
    assert(FxDevice != NULL);
    assert(MyDevice != NULL);

    //
    // Create the framework queue
    //
    hr = this->QueryInterface(__uuidof(IUnknown), (void **)&unknown);
    if (FAILED(hr))
    {
        TraceEvents(TRACE_LEVEL_ERROR,
                    TRACE_QUEUE,
                    "%!FUNC! Failed to query IUnknown interface %!hresult!",
                    hr);
        goto Exit;
    }

    hr = FxDevice->CreateIoQueue(unknown,
                                 FALSE,     // Default Queue?
                                 WdfIoQueueDispatchParallel,  // Dispatch type
                                 TRUE,     // Power managed?
                                 FALSE,     // Allow zero-length requests?
                                 &fxQueue); // I/O queue
    DriverSafeRelease(unknown);

    if (FAILED(hr))
    {
        TraceEvents(TRACE_LEVEL_ERROR, 
                   TRACE_QUEUE, 
                   "%!FUNC! Failed to create framework queue.");
        goto Exit;
    }

    //
    // Configure this queue to filter all Device I/O requests.
    //
    hr = FxDevice->ConfigureRequestDispatching(fxQueue,
                                               WdfRequestDeviceIoControl,
                                               TRUE);

    if (FAILED(hr))
    {
        TraceEvents(TRACE_LEVEL_ERROR, 
                   TRACE_QUEUE, 
                   "%!FUNC! Failed to configure request dispatching %!hresult!.",
                   hr);
        goto Exit;
    }

    //
    // Keep references in member variables.
    //
    m_FxQueue = fxQueue;
    m_Device= MyDevice;

Exit:

    //
    // Safe to release here.  The framework keeps a reference to the Queue
    // for the lifetime of the device.
    //
    DriverSafeRelease(fxQueue);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Exit");

    return hr;
}

VOID
STDMETHODCALLTYPE
CMyIoQueue::OnDeviceIoControl(
    __in IWDFIoQueue *FxQueue,
    __in IWDFIoRequest *FxRequest,
    __in ULONG ControlCode,
    __in SIZE_T InputBufferSizeInBytes,
    __in SIZE_T OutputBufferSizeInBytes
    )
/*++

Routine Description:


    DeviceIoControl dispatch routine

Aruments:

    FxQueue - Framework Queue instance
    FxRequest - Framework Request  instance
    ControlCode - IO Control Code
    InputBufferSizeInBytes - Lenth of input buffer
    OutputBufferSizeInBytes - Lenth of output buffer

    Always succeeds DeviceIoIoctl
Return Value:

    VOID

--*/
{
    UNREFERENCED_PARAMETER(FxQueue);
    UNREFERENCED_PARAMETER(ControlCode);
    UNREFERENCED_PARAMETER(InputBufferSizeInBytes);
    UNREFERENCED_PARAMETER(OutputBufferSizeInBytes);

    HRESULT hr = S_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Entry");

    if (m_Device == NULL) {
        // We don't have pointer to device object
        TraceEvents(TRACE_LEVEL_ERROR, 
                   TRACE_QUEUE, 
                   "%!FUNC!NULL pointer to device object.");
        hr = E_POINTER;
        goto Exit;
    }

    //
    // Process the IOCTLs
    //

Exit:

    FxRequest->Complete(hr);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "%!FUNC! Exit");

    return;

}

