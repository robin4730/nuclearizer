/*
 * MGUIOptionsHitSideFilter.cxx
 *
 * Copyright (C) by Robin Anthony-Petersen.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
// MGUIOptionsHitSideFilter
//
////////////////////////////////////////////////////////////////////////////////


// Include the header:
#include "MGUIOptionsHitSideFilter.h"

// Standard libs:

// ROOT libs:
#include <TGLabel.h>
#include <TGLayout.h>

// MEGAlib libs:
#include "MModuleHitSideFilter.h"


////////////////////////////////////////////////////////////////////////////////


#ifdef ___CLING___
ClassImp(MGUIOptionsHitSideFilter)
#endif


////////////////////////////////////////////////////////////////////////////////

// Constructor argument changed from MModuleHitSideFilter* to generic MModule*
MGUIOptionsHitSideFilter::MGUIOptionsHitSideFilter(MModule* Module) : MGUIOptions(Module)
{
  // Construct an instance of MGUIOptionsHitSideFilter
}


////////////////////////////////////////////////////////////////////////////////


MGUIOptionsHitSideFilter::~MGUIOptionsHitSideFilter()
{
  // Delete this instance
}


////////////////////////////////////////////////////////////////////////////////


void MGUIOptionsHitSideFilter::Create()
{
  // Build the GUI window

  // setup the window frame and title
  PreCreate();

  // Use the standard frame layout from MGUIOptions
  TGLayoutHints* MainLayout = new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 20, 20, 5, 5);

  // Add a descriptive label
  TGLabel* Label = new TGLabel(m_OptionsFrame, "Select which side-triggered events to EXCLUDE:");
  m_OptionsFrame->AddFrame(Label, MainLayout);

  // Checkbox for LV-First
  m_ExcludeLVFirst = new TGCheckButton(m_OptionsFrame, "Exclude events where LV (p-side) hits first");
  if (dynamic_cast<MModuleHitSideFilter*>(m_Module)->GetExcludeLVFirst() == true) m_ExcludeLVFirst->SetState(kButtonDown);
  m_OptionsFrame->AddFrame(m_ExcludeLVFirst, MainLayout);

  // Checkbox for HV-First
  m_ExcludeHVFirst = new TGCheckButton(m_OptionsFrame, "Exclude events where HV (n-side) hits first");
  if (dynamic_cast<MModuleHitSideFilter*>(m_Module)->GetExcludeHVFirst() == true) m_ExcludeHVFirst->SetState(kButtonDown);
  m_OptionsFrame->AddFrame(m_ExcludeHVFirst, MainLayout);

  // Finalize the window
  PostCreate();
}


////////////////////////////////////////////////////////////////////////////////


bool MGUIOptionsHitSideFilter::OnApply()
{
  // Save the state of the checkboxes back to the module
  dynamic_cast<MModuleHitSideFilter*>(m_Module)->SetExcludeLVFirst(m_ExcludeLVFirst->IsDown());
  dynamic_cast<MModuleHitSideFilter*>(m_Module)->SetExcludeHVFirst(m_ExcludeHVFirst->IsDown());

  return true;
}


// MGUIOptionsHitSideFilter.cxx: the end...
////////////////////////////////////////////////////////////////////////////////
