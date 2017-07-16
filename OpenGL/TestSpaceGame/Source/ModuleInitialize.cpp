#include "stdafx.h"

#include "ModuleInitializeFuncs.h"


namespace TestSpaceGame
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestCelesteEnginePlus_Initialize)
  {
    GenericModuleInitialize();
  }

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_CLEANUP(TestCelesteEnginePlus_Cleanup)
  {
    GenericModuleCleanup();
  }
}