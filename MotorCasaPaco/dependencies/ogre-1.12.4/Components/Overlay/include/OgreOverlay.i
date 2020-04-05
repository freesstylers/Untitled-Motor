#ifdef SWIGPYTHON
%module(package="Ogre", directors="1") Overlay
#else
%module OgreOverlay
#endif
%{
/* Includes the header in the wrapper code */
#include "Ogre.h"
#include "OgreUnifiedHighLevelGpuProgram.h"

#include "OgreOverlayPrerequisites.h"
#include "OgreFont.h"
#include "OgreFontManager.h"
#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayElement.h"
#include "OgreOverlayElementFactory.h"
#include "OgreOverlayManager.h"
#include "OgrePanelOverlayElement.h"
#include "OgreTextAreaOverlayElement.h"

#include "imgui.h"
#include "OgreImGuiOverlay.h"
%}

%include std_string.i
%include exception.i 
%import "Ogre.i"

#define _OgreOverlayExport

#ifdef SWIGCSHARP
%csmethodmodifiers Ogre::OverlaySystem::eventOccurred "public";
#endif

%include "OgreOverlayPrerequisites.h"
%shared_ptr(Ogre::Font);
%include "OgreFont.h"
%include "OgreFontManager.h"
%ignore Ogre::Overlay::get2DElementsIterator;
%include "OgreOverlay.h"
%shared_ptr(Ogre::OverlayElement);
%include "OgreOverlayElement.h"
%include "OgreOverlayElementFactory.h"
%shared_ptr(Ogre::OverlayContainer);
%include "OgreOverlayContainer.h"
%include "OgreOverlayManager.h"
%shared_ptr(Ogre::OverlaySystem);
%include "OgreOverlaySystem.h"
%shared_ptr(Ogre::PanelOverlayElement);
%include "OgrePanelOverlayElement.h"
%ignore Ogre::TextAreaOverlayElement::getFontName;
%shared_ptr(Ogre::TextAreaOverlayElement);
%include "OgreTextAreaOverlayElement.h"

#ifdef HAVE_IMGUI
%include stdint.i
%include typemaps.i

%include "OgreImGuiOverlay.h"

/// Imgui
// ignore va list methods
%ignore ImGui::TextV;
%ignore ImGui::TextColoredV;
%ignore ImGui::TextDisabledV;
%ignore ImGui::TextWrappedV;
%ignore ImGui::LabelTextV;
%ignore ImGui::BulletTextV;
%ignore ImGui::TreeNodeV;
%ignore ImGui::TreeNodeExV;
%ignore ImGui::SetTooltipV;
%ignore ImGuiTextBuffer::appendfv;

%apply bool* INOUT { bool* p_open };
%apply float* INOUT { float* v };
%apply int* INOUT { int* v };
%include "imgui.h"
#endif