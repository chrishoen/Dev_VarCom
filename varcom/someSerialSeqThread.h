#pragma once

/*==============================================================================
Exampleple two thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsTwoThread.h"
#include "risThreadsWaitable.h"

namespace Some
{
 
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example two thread. It inherits from BaseTwoThread to obtain
// a two thread functionality.
//
// It is used in conjunction with the example qcall thread in a master/slave
// scheme. The two thread is a master that sends request qcalls to the slave
// qcall thread, who then sends response qcalls back to the master.
// 
// The long thread executes a sequence qcall that provides the execution
// context for the master/slave message processing sequence. The sequence
// qcall is executed at initialization and contains an infinite loop
// that sends requests to the slave qcall thread and waits for responses
// from it, via the short thread. The sequence only exits if it is aborted
// or the thread is terminated.
//
// The short thread executes a response qcall that is invoked by the slave
// qcall thread after it receives a request. It notifies the long thread
// when responses are received.
//
//******************************************************************************
//******************************************************************************
//******************************************************************************

class SerialSeqThread : public Ris::Threads::BaseTwoThread
{
public:
   typedef Ris::Threads::BaseTwoThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants:

   // Timer periods.
   static const int cSeqPeriod = 2000;

   // Wait timeouts.
   static const int cResponseTimeout = 2000;

   // Notification codes.
   static const int cResponseNotifyCode = 11;

   // Seq exit status codes.
   static const int cSeqExitNormal = 0;
   static const int cSeqExitAborted = 1;
   static const int cSeqExitError = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Notifications.
   Ris::Threads::NotifyWrapper mResponseNotify;

   // Waitable timer.
   Ris::Threads::Waitable mSeqWaitable;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Process sequence exit code.
   int mSeqExitCode;

   // Seq state. Based on message bing processed.
   int mSeqState;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Metrics.
   int mTxCount;
   int mRxCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SerialSeqThread();
   void resetVars();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // before the thread starts running.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immediately 
   // after the thread starts running.
   void threadExitFunction() override;

   // Thread shutdown function. This shuts down the two threads.
   void shutdownThreads() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Receive response callback qcall.
   Ris::Threads::QCall1<int> mResponseQCall;

   // Receive response qcall function. It is bound to the qcall. This is
   // invoked by the example qcall thread after it receives a request qcall
   // from the long thread. It executes in the context of the short thread.
   // It notifies the long thread that a response was received.
   void executeResponse(int);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. qcalls.

   // Run sequence qcall. 
   Ris::Threads::QCall0 mRunSeq1QCall;

   // Run sequence qcall function. This is bound to the qcall. Execute an
   // infinite loop sequence that sends a request to the slave, waits for the
   // response, and processes it. It executes in the context of the long
   // thread. The purpose of this is to provide long thread execution context
   // for message processing.
   void executeRunSeq1();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. qcalls.

   // Abort sequence qcall.
   Ris::Threads::QCall0 mAbortQCall;

   // Abort sequence qcall function. This is bound to the qcall. Post to the
   // waitable to abort the long thread qcall. Execute in the context of the
   // short thread.
   void executeAbort();

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _SOMEEXAMPLETWOTHREAD_CPP_
SerialSeqThread* gSerialSeqThread = 0;
#else
extern SerialSeqThread* gSerialSeqThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
