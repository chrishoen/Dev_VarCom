//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "risPortableCalls.h"


#define  _PROCOUDPSETTINGS_CPP_
#include "procoUdpSettings.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace ProtoComm
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

UdpSettings::UdpSettings()
{
   reset();
}

void UdpSettings::reset()
{
   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("c:/aaa_prime/Example/ProtoComm_UdpSettings.txt");
   }
   else
   {
      BaseClass::setFilePath("/opt/prime/files/ProtoComm_UdpSettings.txt");
   }

   mMyAppNumber = 0;

   mMyUdpPort = 0;
   mOtherUdpIPAddress[0]=0;
   mOtherUdpPort = 0;
   mUdpWrapFlag = false;

   mThreadTimerPeriod = 0;

   mNumWords = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void UdpSettings::show()
{
   printf("\n");
   printf("UdpSettings************************************************ %s\n", mTargetSection);

   printf("FilePath                %s\n",   BaseClass::mFilePath);
   printf("MyAppNumber             %16d\n", mMyAppNumber);

   printf("MyUdpPort               %16d\n",mMyUdpPort);
   printf("OtherUdpAddress         %16s\n", mOtherUdpIPAddress);
   printf("OtherUdpPort            %16d\n", mOtherUdpPort);
   printf("UdpWrapflag             %16s\n", my_string_from_bool(mUdpWrapFlag));

   printf("\n");
   printf("ThreadTimerPeriod       %16d\n", mThreadTimerPeriod);
   printf("NumWords                %16d\n", mNumWords);

   printf("UdpSettings************************************************\n");
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void UdpSettings::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("MyAppNumber"))         mMyAppNumber = aCmd->argInt(1);

   if (aCmd->isCmd("MyUdpPort"))           mMyUdpPort = aCmd->argInt(1);
   if (aCmd->isCmd("OtherUdpAddress"))     aCmd->copyArgString(1, mOtherUdpIPAddress,cMaxStringSize);
   if (aCmd->isCmd("OtherUdpPort"))        mOtherUdpPort = aCmd->argInt(1);
   if (aCmd->isCmd("UdpWrapFlag"))         mUdpWrapFlag = aCmd->argBool(1);

   if (aCmd->isCmd("ThreadTimerPeriod"))   mThreadTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("NumWords"))            mNumWords = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void UdpSettings::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace