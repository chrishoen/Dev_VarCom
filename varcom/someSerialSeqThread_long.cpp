/*==============================================================================
Detestion:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someExampleParms.h"
#include "someExampleQCallThread.h"

#include "someSerialSeqThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Run sequence qcall function. This is bound to the qcall. Execute an
// infinite loop sequence that sends a request to the slave, waits for the
// response, and processes it. It executes in the context of the long
// thread. The purpose of this is to provide long thread execution context
// for message processing.

void SerialSeqThread::executeRunSeq1()
{
   Prn::print(0, "SerialSeqThread::executeRunSeq1 BEGIN");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do this first.

   // Initialize the synchronization objects.
   mSeqWaitable.initialize(gExampleParms.mTimerPeriod);
   mNotify.reset();

   // Reset variables. 
   resetVars();

   try
   {
      // Seq to transmit and receive messages.
      while (true)
      {
         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Wait.

         // If true then there was a serial timeout.
         bool tTimeoutFlag = false;

         // If true then there was a processing error.
         bool tProcErrorFlag = false;

         // Wait for timer or abort.
         mSeqWaitable.waitForTimerOrSemaphore();

         // Test for an abort
         if (mSeqWaitable.wasSemaphore()) throw 668;

         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Send a request to the slave, wait for the response and process it.

         try
         {
            // Default. This will be set by the specific subfunction.
            mSeqExitCode = cSeqExitNormal;

            // Test for a notification exception.
            // This can throw an execption if there's an abort.
            mNotify.testException();

            // Set the thread notification mask.
            mNotify.setMaskOne("Response", cResponseNotifyCode);

            // Invoke the qcall thread request qcall.
            gExampleQCallThread->mRequestQCall(mTxCount++);

         }
         catch (int aException)
         {
            if (aException == Ris::Threads::Notify::cTimeoutException)
            {
               Prn::print(0, "EXCEPTION SerialSeqThread::doProcess TIMEOUT %d", aException);

               // Rx timeout.
               tTimeoutFlag = true;

               // There was a processing error.
               tProcErrorFlag = true;
            }
            else if (aException == cSeqExitError)
            {
               Prn::print(0, "EXCEPTION SerialSeqThread::doProcess ERROR %d", aException);

               // There was a processing error.
               tProcErrorFlag = true;
            }
            else
            {
               Prn::print(0, "EXCEPTION SerialSeqThread::doProcess %d %s", aException, mNotify.mException);

               // There was a processing error.
               tProcErrorFlag = true;
            }
         }

         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Check errors.
         
         if (tProcErrorFlag)
         {
         }

         //*********************************************************************
         //*********************************************************************
         //*********************************************************************
         // Events.

         // Test for a timeout.
         if (tTimeoutFlag)
         {
         }
      }
   }
   catch (int aException)
   {
      if (aException == 668)
      {
         Prn::print(0, "EXCEPTION SerialSeqThread::executeRunSeq1 ABORT %d %s", aException, mNotify.mException);
         mSeqExitCode = cSeqExitAborted;
      }
      else
      {
         Prn::print(0, "EXCEPTION SerialSeqThread::executeRunSeq1 %d", aException);
         mSeqExitCode = cSeqExitError;
      }
   }
   catch (...)
   {
      Prn::print(0, "EXCEPTION SerialSeqThread::executeRunSeq1 UNKNOWN");
      mSeqExitCode = cSeqExitError;
   }

   // Finalize the synchronization objects.
   mSeqWaitable.finalize();
   mNotify.clearFlags();

   Prn::print(0, "SerialSeqThread::executeRunSeq1 END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace