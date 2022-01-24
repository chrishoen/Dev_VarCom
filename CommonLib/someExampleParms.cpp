//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEEXAMPLEPARMS_CPP_
#include "someExampleParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ExampleParms::ExampleParms()
{
   reset();
}

void ExampleParms::reset()
{
   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("c:/aaa_prime/files/Example_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath("/opt/prime/files/Example_Parms.txt");
   }

   mPrintViewEnable = false;
   mPrintViewIPAddress[0] = 0;

   mTimerPeriod = 0;
   mDelay1 = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ExampleParms::show()
{
   printf("\n");
   printf("ExampleParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("TimerPeriod                %12d\n", mTimerPeriod);
   printf("Delay1                     %12d\n", mDelay1);

   printf("\n");
   printf("PrintViewEnable            %-12s\n", my_string_from_bool(mPrintViewEnable));
   printf("PrintViewIPAddress         %-12s\n", mPrintViewIPAddress);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ExampleParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))        mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("Delay1"))             mDelay1 = aCmd->argInt(1);

   if (aCmd->isCmd("PrintViewEnable"))    mPrintViewEnable = aCmd->argBool(1);
   if (aCmd->isCmd("PrintViewIPAddress")) aCmd->copyArgString(1, mPrintViewIPAddress, cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ExampleParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace