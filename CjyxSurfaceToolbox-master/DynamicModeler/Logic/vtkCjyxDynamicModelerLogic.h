/*==============================================================================

  Program: 3D Cjyx

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.cjyx.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Kyle Sunderland, PerkLab, Queen's University
  and was supported through CANARIE's Research Software Program, Cancer
  Care Ontario, OpenAnatomy, and Brigham and Women's Hospital through NIH grant R01MH112748.

==============================================================================*/

// .NAME vtkCjyxDynamicModelerLogic - cjyx logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkCjyxDynamicModelerLogic_h
#define __vtkCjyxDynamicModelerLogic_h

// Cjyx includes
#include "vtkCjyxModuleLogic.h"

// Logic includes
#include <vtkCjyxDynamicModelerTool.h>

// STD includes
#include <cstdlib>

#include "vtkCjyxDynamicModelerModuleLogicExport.h"

// VTK includes
#include <vtkSmartPointer.h>

class vtkDRMLDynamicModelerNode;

/// \ingroup Cjyx_QtModules_ExtensionTemplate
class VTK_CJYX_DYNAMICMODELER_MODULE_LOGIC_EXPORT vtkCjyxDynamicModelerLogic :
  public vtkCjyxModuleLogic
{
public:

  static vtkCjyxDynamicModelerLogic *New();
  vtkTypeMacro(vtkCjyxDynamicModelerLogic, vtkCjyxModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /// Returns the current tool object that is being used with the surface editor node
  vtkCjyxDynamicModelerTool* GetDynamicModelerTool(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Run the editor tool specified by the surface editor node
  void RunDynamicModelerTool(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Detects circular references in the output nodes that are used as inputs
  bool HasCircularReference(vtkDRMLDynamicModelerNode* surfaceEditorNode);

protected:
  vtkCjyxDynamicModelerLogic();
  virtual ~vtkCjyxDynamicModelerLogic();
  void ProcessDRMLNodesEvents(vtkObject* caller, unsigned long event, void* callData) override;
  void SetDRMLSceneInternal(vtkDRMLScene* newScene) override;

  /// Register DRML Node classes to Scene. Gets called automatically when the DRMLScene is attached to this logic class.
  void RegisterNodes() override;

  void OnDRMLSceneNodeAdded(vtkDRMLNode* node) override;
  void OnDRMLSceneNodeRemoved(vtkDRMLNode* node) override;
  void OnDRMLSceneEndImport() override;

  /// Ensures that the vtkCjyxDynamicModelerTool for each tool exists, and is up-to-date.
  void UpdateDynamicModelerTool(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  typedef std::map<std::string, vtkSmartPointer<vtkCjyxDynamicModelerTool> > DynamicModelerToolList;
  DynamicModelerToolList Tools;

private:
  vtkCjyxDynamicModelerLogic(const vtkCjyxDynamicModelerLogic&) = delete;
  void operator=(const vtkCjyxDynamicModelerLogic&) = delete;
};

#endif
