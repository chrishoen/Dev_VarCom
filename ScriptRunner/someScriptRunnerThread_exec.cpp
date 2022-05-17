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
   if (aCmd->isCmd("RED"))    executeRed(aCmd);
   if (aCmd->isCmd("GREEN"))  executeGreen(aCmd);
   if (aCmd->isCmd("BLUE"))   executeBlue(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeRed(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeRed");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a string to the responder.
   std::string* tTxString = new std::string("red");
   sendString(tTxString);

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString1 = mRxStringQueue.tryRead();
   if (tRxString1 == 0) throw 888;
   Trc::write(1, 0, "executeRed RX %s", tRxString1->c_str());
   delete tRxString1;

   Trc::write(1, 0, "executeRed done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeGreen(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeGreen");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a string to the responder.
   std::string* tTxString = new std::string("green");
   sendString(tTxString);

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString1 = mRxStringQueue.tryRead();
   if (tRxString1 == 0) throw 888;
   Trc::write(1, 0, "executeGreen RX %s", tRxString1->c_str());
   delete tRxString1;

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString2 = mRxStringQueue.tryRead();
   if (tRxString2 == 0) throw 888;
   Trc::write(1, 0, "executeGreen RX %s", tRxString2->c_str());
   delete tRxString2;

   // Done.
   Trc::write(1, 0, "executeGreen done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ScriptRunnerThread::executeBlue(Ris::CmdLineCmd* aCmd)
{
   Trc::write(1, 0, "executeBlue");

   // Set the thread notification mask and flush the string queue.
   mNotify.setMaskOne("RxString", cRxStringNotifyCode);
   flushRxStringQueue();

   // Send a string to the responder.
   std::string* tTxString = new std::string("blue");
   sendString(tTxString);

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString1 = mRxStringQueue.tryRead();
   if (tRxString1 == 0) throw 888;
   Trc::write(1, 0, "executeBlue RX %s", tRxString1->c_str());
   delete tRxString1;

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString2 = mRxStringQueue.tryRead();
   if (tRxString2 == 0) throw 888;
   Trc::write(1, 0, "executeBlue RX %s", tRxString2->c_str());
   delete tRxString2;

   // Wait and read the receive string from the queue and process it.
   mNotify.wait(cInfiniteTimeout);
   std::string* tRxString3 = mRxStringQueue.tryRead();
   if (tRxString3 == 0) throw 888;
   Trc::write(1, 0, "executeBlue RX %s", tRxString3->c_str());
   delete tRxString3;

   // Done.
   Trc::write(1, 0, "executeBlue done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace