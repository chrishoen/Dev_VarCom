
#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"

#include "someSerialParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
   printf("ScriptRunner Program**********************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Process configuration.

   // Set the program current working directory up one level from the 
   // program bin directory.
   Ris::portableChdirUpFromBin();

   // Set the base directory to the current working directory.
   Ris::setBaseDirectoryToCurrent();

   // Set the process priority class.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::Show1, true);
   Prn::setFilter(Prn::Show2, false);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize trace facility.

   Trc::reset();
   Trc::create_buffer(1,  3, "script");
   Trc::create_buffer(11, 3, "serial");
   Trc::set_default_trace_index(11);
   //Trc::create_log(11, 4, "log/ProtoSerial_trace11.log");
   Trc::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   Some::gSerialParms.reset();
   Some::gSerialParms.readSection("default");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Finalize trace facility.
   Trc::finalize();

   // Exit process
   Ris::Threads::exitProcess();

   printf("ScriptRunner Program**********************************************BEGIN\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
