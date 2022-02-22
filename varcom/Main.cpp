#include "stdafx.h"

#include "risThreadsProcess.h"
#include "MainInit.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "someExampleTwoThread.h"
#include "someExampleQCallThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Begin program.

   main_initialize(argc, argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   Some::gExampleQCallThread = new Some::ExampleQCallThread;
   Some::gExampleQCallThread->launchThread();

   Some::gExampleTwoThread = new Some::ExampleTwoThread;
   Some::gExampleTwoThread->launchThreads();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (Some::gExampleTwoThread)   Some::gExampleTwoThread->showThreadInfo();
   if (Some::gExampleQCallThread) Some::gExampleQCallThread->showThreadInfo();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute console command line executive, wait for user to exit.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program threads.

   if (Some::gExampleTwoThread)   Some::gExampleTwoThread->shutdownThreads();
   if (Some::gExampleQCallThread) Some::gExampleQCallThread->shutdownThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (Some::gExampleTwoThread)
   {
      delete Some::gExampleTwoThread;
      Some::gExampleTwoThread = 0;
   }

   if (Some::gExampleQCallThread)
   {
      delete Some::gExampleQCallThread;
      Some::gExampleQCallThread = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // End program.

   main_finalize();
   return 0;
}
