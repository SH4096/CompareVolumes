/*==============================================================================

  Copyright (c) Laboratory for Percutaneous Surgery (PerkLab)
  Queen's University, Kingston, ON, Canada. All Rights Reserved.

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

#ifndef __vtkCjyxDynamicModelerTool_h
#define __vtkCjyxDynamicModelerTool_h

#include "vtkCjyxDynamicModelerModuleLogicExport.h"

// VTK includes
#include <vtkIntArray.h>
#include <vtkObject.h>
#include <vtkStringArray.h>

// STD includes
#include <map>
#include <string>
#include <vector>

class vtkCollection;
class vtkDRMLDisplayableNode;
class vtkDRMLDisplayNode;
class vtkDRMLDynamicModelerNode;
class vtkDRMLNode;

/// Helper macro for supporting cloning of tools
#ifndef vtkToolNewMacro
#define vtkToolNewMacro(newClass) \
vtkStandardNewMacro(newClass); \
vtkCjyxDynamicModelerTool* newClass::CreateToolInstance() \
{ \
return newClass::New(); \
}
#endif

/// \brief Dynamic modeler tool
///
/// Abstract class for parmetric surface modification tools.
/// Each tool can have multiple input and output nodes (stored in the InputNodeInfo and OutputNodeInfo lists).
class VTK_CJYX_DYNAMICMODELER_MODULE_LOGIC_EXPORT vtkCjyxDynamicModelerTool : public vtkObject
{
public:
  vtkTypeMacro(vtkCjyxDynamicModelerTool, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /// Create instance of the default node. Similar to New but virtual method.
  /// Subclasses should implement this method by
  virtual vtkCjyxDynamicModelerTool* CreateToolInstance() = 0;

  /// Create a new instance of this tool and copy its contents.
  virtual vtkCjyxDynamicModelerTool* Clone();

  /// Human-readable name of the mesh modification tool.
  virtual const char* GetName() = 0;

  /// The number of vtkDRMLNode that can be used as input for this tool.
  /// Some inputs may be required \sa GetNthInputNodeRequired.
  int GetNumberOfInputNodes();

  /// The number of parameters that can be used to change the behavior of the tool
  int GetNumberOfInputParameters();

  /// The number of vtkDRMLNode that can be used as output for this tool.
  /// Some outputs may be required \sa GetNthOutputNodeRequired.
  int GetNumberOfOutputNodes();

  /// Returns the name of the Nth input node.
  std::string GetNthInputNodeName(int n);

  /// Returns the description of the Nth input node.
  std::string GetNthInputNodeDescription(int n);

  /// Returns the class name of the Nth input node.
  vtkStringArray* GetNthInputNodeClassNames(int n);

  /// Returns the reference role of the Nth input node.
  std::string GetNthInputNodeReferenceRole(int n);

  /// Returns true if the input is required for the tool to be run.
  bool GetNthInputNodeRequired(int n);

  /// Returns true if the input is repeatable
  bool GetNthInputNodeRepeatable(int n);

  /// Returns the events that must be observed to enable continuous updates for the current input.
  vtkIntArray* GetNthInputNodeEvents(int n);

  /// Returns the Nth input node specified by the surface editor node.
  vtkDRMLNode* GetNthInputNode(int n, vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Returns the name of the Nth output node.
  std::string GetNthOutputNodeName(int n);

  /// Returns the description of the Nth output node.
  std::string GetNthOutputNodeDescription(int n);

  /// Returns the class name of the Nth output node.
  vtkStringArray* GetNthOutputNodeClassNames(int n);

  /// Returns the reference role of the Nth output node.
  std::string GetNthOutputNodeReferenceRole(int n);

  /// Returns true if the output is required for the tool to be run.
  bool GetNthOutputNodeRequired(int n);

  /// Returns the events that must be observed to enable continuous updates for the current output.
  vtkDRMLNode* GetNthOutputNode(int n, vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Returns the name of the Nth input parameter.
  std::string GetNthInputParameterName(int n);

  /// Returns the description of the Nth input parameter.
  std::string GetNthInputParameterDescription(int n);

  /// Returns the attribute name of the Nth input parameter.
  std::string GetNthInputParameterAttributeName(int n);

  /// Returns the data type of the Nth input parameter.
  int GetNthInputParameterType(int n);

  /// Returns the value of the Nth input parameter from the parameter node.
  vtkVariant GetNthInputParameterValue(int n, vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Returns the possible values of the Nth input parameter.
  /// Only used for string enum types
  vtkStringArray* GetNthInputParameterPossibleValues(int n);

  /// Returns true if all of the required inputs have been specified for the surface editor node.
  virtual bool HasRequiredInputs(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Returns true if all of the required inputs have been specified for the surface editor node.
  virtual bool HasOutput(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Get a list of all input nodes from the tool node
  virtual void GetInputNodes(vtkDRMLDynamicModelerNode* surfaceEditorNode, std::vector<vtkDRMLNode*>& inputNodes);

  /// Get a list of all output nodes from the tool node
  virtual void GetOutputNodes(vtkDRMLDynamicModelerNode* surfaceEditorNode, std::vector<vtkDRMLNode*>& outputNodes);

  /// Creates display nodes for outputs if they do not exist
  /// If a display node is created, the display parameters are copied from the first node of the same type
  /// in the input.
  virtual void CreateOutputDisplayNodes(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  /// Run the surface editor tool.
  /// Checks to ensure that all of the required inputs have been set.
  bool Run(vtkDRMLDynamicModelerNode* surfaceEditorNode);

  enum ParameterType
  {
    PARAMETER_STRING,
    PARAMETER_STRING_ENUM,
    PARAMETER_BOOL,
    PARAMETER_INT,
    PARAMETER_DOUBLE,
  };

protected:
  vtkCjyxDynamicModelerTool();
  ~vtkCjyxDynamicModelerTool() override;
  void operator=(const vtkCjyxDynamicModelerTool&);

protected:

  /// Run the tool on the input nodes and apply the results to the output nodes
  virtual bool RunInternal(vtkDRMLDynamicModelerNode* surfaceEditorNode) = 0;

  /// Struct containing all of the relevant info for input and output nodes.
  struct StructNodeInfo
  {
    StructNodeInfo(std::string name, std::string description, vtkStringArray* classNames, std::string referenceRole, bool required, bool repeatable, vtkIntArray* events = nullptr)
      : Name(name)
      , Description(description)
      , ClassNames(classNames)
      , ReferenceRole(referenceRole)
      , Required(required)
      , Repeatable(repeatable)
      , Events(events)
    {
    }
    std::string                     Name;
    std::string                     Description;
    vtkSmartPointer<vtkStringArray> ClassNames;
    std::string                     ReferenceRole;
    bool                            Required;
    bool                            Repeatable;
    vtkSmartPointer<vtkIntArray>    Events;
  };
  using NodeInfo = struct StructNodeInfo;

  std::vector<NodeInfo> InputNodeInfo;
  std::vector<NodeInfo> OutputNodeInfo;
  
  struct StructParameterInfo
  {
    StructParameterInfo(std::string name, std::string description, std::string attributeName, int type, vtkVariant defaultValue)
      : Name(name)
      , Description(description)
      , AttributeName(attributeName)
      , Type(type)
      , DefaultValue(defaultValue)
    {
    }
    std::string Name;
    std::string Description;
    std::string AttributeName;
    int Type{ PARAMETER_STRING };
    vtkVariant DefaultValue;
    vtkSmartPointer<vtkStringArray> PossibleValues;
  };
  using ParameterInfo = struct StructParameterInfo;
  std::vector<ParameterInfo> InputParameterInfo;

private:
  vtkCjyxDynamicModelerTool(const vtkCjyxDynamicModelerTool&) = delete;
};

#endif // __vtkCjyxDynamicModelerTool_h
