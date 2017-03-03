========================================================================
    SteelBattalionController Project Overview
========================================================================

This file contains a summary of what you will find in each of the files that make up your project.

SteelBattalionController.vcxproj
    This is the main project file for projects generated using an Application Wizard. 
    It contains information about the version of the product that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

SteelBattalionController.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

SteelBattalionController.inf
    Text file used for driver installation. After creating this driver using the template, the user
    *must* update the hardware ID from "USB\VID_vvvv&PID_pppp" to the hardware ID of the USB device
    that the driver should be installed on.

Dllsup.cpp
    DLL Support code - provides the DLL's entry point as well as DllGetClassObject 
    (which is the only export required by UMDF).

Exports.def
    This file lists the functions that the driver DLL exports.
  
Internal.h
    This is the common header file for all the driver files. 
 
Driver.cpp & Driver.h
    Definition and implementation of the driver callback class. 
 
Device.cpp & Device.h
    Definition and implementation of the device callback class.

IoQueue.cpp & IoQueue.h	
    Definition and implementation of the queue callback class.
 
SteelBattalionController.rc
    This file defines resource information for the driver.
 
/////////////////////////////////////////////////////////////////////////////

Learn more about User Mode Driver Framework here:

http://msdn.microsoft.com/en-us/library/ff554928(v=VS.85).aspx

Related WDK samples and what they demonstrate:

    UMDF OSR USB FX2 driver (fx2_driver) - bulk/interrupt transfers, continuous readers

/////////////////////////////////////////////////////////////////////////////
