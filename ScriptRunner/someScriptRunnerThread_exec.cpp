/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "someState.h"

#include "someScriptRunnerThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute a command line command. It calls one of
// the following specific command execution functions.

void ScriptRunnerThread::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FIRST"))    executeFirst(aCmd);
   if (aCmd->isCmd("ENABLE"))   executeEnable(aCmd);
   if (aCmd->isCmd("ECHO"))     executeEcho(aCmd);
   if (aCmd->isCmd("HOME"))     executeHome(aCmd);
   if (aCmd->isCmd("READY"))    executeReady(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeFirst(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeFirst");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a request to the motor.
   char tString1[40];
   sprintf(tString1, "\\%d", mAddr);
   std::string* tRequest = new std::string(tString1);
   sendString(tRequest);

   // Wait and read the response from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tResponse1 = mRxStringQueue.tryRead();
   if (tResponse1 == 0) throw 888;
   Trc::write(1, 0, "executeFirst RX %s", tResponse1->c_str());
   delete tResponse1;

   Trc::write(1, 0, "executeFirst done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeEnable(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeEnable");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a request to the motor.
   std::string* tRequest = new std::string("enable");
   sendString(tRequest);

   // Wait and read the response from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tResponse1 = mRxStringQueue.tryRead();
   if (tResponse1 == 0) throw 888;
   Trc::write(1, 0, "executeEnable RX %s", tResponse1->c_str());
   delete tResponse1;

   // Done.
   Trc::write(1, 0, "executeEnable done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeEcho(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeEcho");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a request to the motor.
   char tString1[40];
   sprintf(tString1, "echo %d", aCmd->argInt(1));
   std::string* tRequest = new std::string(tString1);
   sendString(tRequest);

   // Wait and read the response from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tResponse1 = mRxStringQueue.tryRead();
   if (tResponse1 == 0) throw 888;
   Trc::write(1, 0, "executeEcho RX %s", tResponse1->c_str());
   delete tResponse1;

   // Done.
   Trc::write(1, 0, "executeEcho done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeHome(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeHome");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a request to the motor.
   std::string* tRequest = new std::string("homecmd");
   sendString(tRequest);

   // Wait and read the response from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tResponse1 = mRxStringQueue.tryRead();
   if (tResponse1 == 0) throw 888;
   Trc::write(1, 0, "executeHome RX %s", tResponse1->c_str());
   delete tResponse1;

   // Done.
   Trc::write(1, 0, "executeHome done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeReady(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeReady");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a request to the motor.
   std::string* tRequest = new std::string("ready");
   sendString(tRequest);

   // Wait and read the response from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tResponse1 = mRxStringQueue.tryRead();
   if (tResponse1 == 0) throw 888;
   Trc::write(1, 0, "executeReady RX %s", tResponse1->c_str());
   delete tResponse1;

   // Done.
   Trc::write(1, 0, "executeReady done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace