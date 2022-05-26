///////////////////////////////////////////////////////////////////////////
////                     USB_BOOTLOADER.H                              ////
////                                                                   ////
////  This include file must be included by any application loaded     ////
////  by the example USB bootloader (ex_usb_bootloader                 ////
////                                                                   ////
////  The directives in this file relocate the reset and interrupt     ////
////  vectors as well as reserving space for the bootloader.           ////
////                                                                   ////
////  For more documentation see ex_usb_bootloader.c                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2007 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS    ////
//// C compiler.  This source code may only be distributed to other    ////
//// licensed users of the CCS C compiler.  No other use,              ////
//// reproduction or distribution is permitted without written         ////
//// permission.  Derivative programs created using this software      ////
//// in object code form are not restricted in any way.                ////
///////////////////////////////////////////////////////////////////////////

//how big is the bootloader?
//the bootloader will reside from address 0x0000 to this location.  the
//application will then sit at this location+1 to the end of program memory.
#define LOADER_SIZE        (0x17FF)

//the loader and application need a common flag that determines if we are in
//the bootloader or application, that way the ISR knows where to go.  this
//is the location in ram that is reserved for this flag.
#define LOC_IN_LOADER_FLAG  0x25

//// --- end configuration --- ////////////////////////////////////////////

#reserve LOC_IN_LOADER_FLAG

int8 g_InBootloader;
#locate g_InBootloader=LOC_IN_LOADER_FLAG

#define LOADER_START       (0)
#define LOADER_END         (LOADER_SIZE)
#define APPLICATION_START  (LOADER_SIZE+1)
#define APPLICATION_END    (getenv("PROGRAM_MEMORY")-1)
#define APPLICATION_ISR    (APPLICATION_START+8)

#ifdef _bootloader
 /*
  Provide an empty application, so if you load this .HEX file into the pic
  without an application this will prevent the pic from executing unknown code.
 */
 #org APPLICATION_START,APPLICATION_START+0xF
 void BlankApplication(void) 
 {
   while(TRUE);
 }

 //we need to prevent the loader from using application space
 #if APPLICATION_END>0xFFFF
   #org APPLICATION_START+0x10, 0xFFFF {}
   #if APPLICATION_END>0x1FFFF
      #org 0xFFFF, 0x1FFFF {}
   #else
      #org 0xFFFF, APPLICATION_END {}
   #endif
 #else
   #org APPLICATION_START+0x10, APPLICATION_END {}
 #endif
#endif

#ifndef _bootloader
 //in the application, this moves the reset and isr vector out of the bootload
 //space.  it then reserves the loader space from being used by the application.
 #build(reset=APPLICATION_START, interrupt=APPLICATION_ISR)
 #org 0, LOADER_END {}
#endif
