project(vtkCjyx${MODULE_NAME}ModuleDRML)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_CJYX_${MODULE_NAME_UPPER}_MODULE_DRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${DRMLCore_INCLUDE_DIRS}
  )

set(${KIT}_SRCS
  vtkDRML${MODULE_NAME}Node.cxx
  vtkDRML${MODULE_NAME}Node.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${DRML_LIBRARIES}
  vtkCjyxMarkupsModuleDRML
  )

# --------------------------------------------------------------------------
CjyxMacroBuildModuleDRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
