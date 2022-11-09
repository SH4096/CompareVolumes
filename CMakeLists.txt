cmake_minimum_required(VERSION 3.13.0)

#-----------------------------------------------------------------------------
set(MODULE_NAME CompareVolumes)

#-----------------------------------------------------------------------------
if(NOT Cjyx_SOURCE_DIR)
  find_package(Cjyx REQUIRED)
  include(${Cjyx_USE_FILE})
endif()

#-----------------------------------------------------------------------------
set(MODULE_PYTHON_SCRIPTS
  ${MODULE_NAME}.py
  )

set(MODULE_PYTHON_RESOURCES
  )

#-----------------------------------------------------------------------------
cjyxMacroBuildScriptedModule(
  NAME ${MODULE_NAME}
  SCRIPTS ${MODULE_PYTHON_SCRIPTS}
  RESOURCES ${MODULE_PYTHON_RESOURCES}
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)

  # Register the unittest subclass in the main script as a ctest.
  # Note that the test will also be available at runtime.
  cjyx_add_python_unittest(SCRIPT CompareVolumes.py)
endif()
