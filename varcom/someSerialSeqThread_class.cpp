/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPriorities.h"
#include "someExampleParms.h"

#define  _SOMEEXAMPLETWOTHREAD_CPP_
#include "someSerialSeqThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor. True is tta, false is da.

SerialSeqThread::SerialSeqThread()
   : mResponseNotify(&mNotify, cResponseNotifyCode)
{
   using namespace std::placeholders;

   // Set base class thread variables.
   BaseClass::mShortThread->setThreadName("ExampleShort");
   BaseClass::mLongThread->setThreadName("ExampleLong");

   BaseClass::mShortThread->setThreadPriority(Cmn::gPriorities.mShort);

   BaseClass::mLongThread->setThreadPriority(Cmn::gPriorities.mLong);

   // Set base class call pointers.
   BaseClass::mShortThread->mThreadInitCallPointer = std::bind(&SerialSeqThread::threadInitFunction, this);
   BaseClass::mShortThread->mThreadExitCallPointer = std::bind(&SerialSeqThread::threadExitFunction, this);
   BaseClass::mShortThread->mThreadExecuteOnTimerCallPointer = std::bind(&SerialSeqThread::executeOnTimer, this, _1);

   // Set qcalls.
   mRunSeq1QCall.bind(this->mLongThread, this, &SerialSeqThread::executeRunSeq1);
   mResponseQCall.bind(this->mShortThread, this, &SerialSeqThread::executeResponse);
   mAbortQCall.bind(this->mShortThread, this, &SerialSeqThread::executeAbort);

   // Set member variables.
   resetVars();
}

void SerialSeqThread::resetVars()
{
   mSeqExitCode = 0;
   mTxCount = 0;
   mRxCount = 0;
   mSeqState = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// before the thread starts running.

void SerialSeqThread::threadInitFunction()
{
   // Launch the sequence qcall.
   mRunSeq1QCall();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately 
// after  the thread starts running.

void SerialSeqThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This shuts down the two threads.

void SerialSeqThread::shutdownThreads()
{
   // Abort the long thread.
   BaseClass::mNotify.abort();
   mSeqWaitable.postSemaphore();

   // Shutdown the two threads.
   BaseClass::shutdownThreads();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// The qcall function. Post to the waitable to abort the long thread
// qcall. Execute in the context of the short thread.

void SerialSeqThread::executeAbort()
{
   Prn::print(0, "ABORT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

   // Abort the long thread.
   mSeqWaitable.postSemaphore();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace