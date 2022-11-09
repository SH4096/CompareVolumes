/*==============================================================================

  Program: 3D Cjyx

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

// DynamicModeler DRML includes
#include "vtkDRMLDynamicModelerNode.h"

// DRML includes
#include <vtkDRMLScene.h>

// VTK includes
#include <vtkCommand.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

//----------------------------------------------------------------------------
vtkDRMLNodeNewMacro(vtkDRMLDynamicModelerNode);

//----------------------------------------------------------------------------
vtkDRMLDynamicModelerNode::vtkDRMLDynamicModelerNode()
= default;

//----------------------------------------------------------------------------
vtkDRMLDynamicModelerNode::~vtkDRMLDynamicModelerNode()
= default;

//----------------------------------------------------------------------------
void vtkDRMLDynamicModelerNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);
  vtkDRMLWriteXMLBeginMacro(of);
  vtkDRMLWriteXMLStringMacro(toolName, ToolName);
  vtkDRMLWriteXMLBooleanMacro(continuousUpdate, ContinuousUpdate);
  vtkDRMLWriteXMLEndMacro();
}

//----------------------------------------------------------------------------
void vtkDRMLDynamicModelerNode::ReadXMLAttributes(const char** atts)
{
  DRMLNodeModifyBlocker blocker(this);
  Superclass::ReadXMLAttributes(atts);
  vtkDRMLReadXMLBeginMacro(atts);
  vtkDRMLReadXMLStringMacro(toolName, ToolName);
  vtkDRMLReadXMLBooleanMacro(continuousUpdate, ContinuousUpdate);
  vtkDRMLReadXMLEndMacro();
}

//----------------------------------------------------------------------------
// Copy the node's attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, VolumeID
void vtkDRMLDynamicModelerNode::Copy(vtkDRMLNode *anode)
{
  DRMLNodeModifyBlocker blocker(this);
  Superclass::Copy(anode);
  vtkDRMLCopyBeginMacro(anode);
  vtkDRMLCopyStringMacro(ToolName);
  vtkDRMLCopyBooleanMacro(ContinuousUpdate);
  vtkDRMLCopyEndMacro();
}

//----------------------------------------------------------------------------
void vtkDRMLDynamicModelerNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);
  vtkDRMLPrintBeginMacro(os, indent);
  vtkDRMLPrintStringMacro(ToolName);
  vtkDRMLPrintBooleanMacro(ContinuousUpdate);
  vtkDRMLPrintEndMacro();
}

//----------------------------------------------------------------------------
void vtkDRMLDynamicModelerNode::ProcessDRMLEvents(vtkObject* caller, unsigned long eventID, void* callData)
{
  Superclass::ProcessDRMLEvents(caller, eventID, callData);
  if (!this->Scene)
    {
    vtkErrorMacro("ProcessDRMLEvents: Invalid DRML scene");
    return;
    }

  vtkDRMLNode* node = vtkDRMLNode::SafeDownCast(caller);
  if (!node)
    {
    return;
    }
  this->InvokeEvent(InputNodeModifiedEvent, caller);
}
