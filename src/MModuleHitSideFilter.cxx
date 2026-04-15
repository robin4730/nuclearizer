/*
 * MModuleHitSideFilter.cxx
 *
 *
 * Copyright (C) by Robin Anthony-Petersen.
 * All rights reserved.
 *
 *
 * This code implementation is the intellectual property of
 * Andreas Zoglauer.
 *
 * By copying, distributing or modifying the Program (or any work
 * based on the Program) you indicate your acceptance of this statement,
 * and all its terms.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
// MModuleHitSideFilter
//
////////////////////////////////////////////////////////////////////////////////


// Include the header:
#include "MModuleHitSideFilter.h"

// Standard libs:

// ROOT libs:
#include "TGClient.h"

// MEGAlib libs:
#include "MModule.h"
#include "MGUIOptionsHitSideFilter.h"


////////////////////////////////////////////////////////////////////////////////


#ifdef ___CLING___
ClassImp(MModuleHitSideFilter)
#endif


////////////////////////////////////////////////////////////////////////////////


MModuleHitSideFilter::MModuleHitSideFilter() : MModule()
{
  // Construct an instance of MModuleHitSideFilter

  // Set the module name --- has to be unique
  m_Name = "Side Hit Filter";

  // Set the XML tag --- has to be unique --- no spaces allowed
  m_XmlTag = "XmlTagHitSideFilter";
  
  // Official ID
  AddModuleType(MAssembly::c_HitSideFilter);

  // Set all modules, which have to be done before this module
  AddPreceedingModuleType(MAssembly::c_EventLoaderMeasurement);
  AddPreceedingModuleType(MAssembly::c_TACcut);
  
  // Set all modules that can come after
  // TODO: @RobinAnthonyPetersen, make sure there aren't other modules that should come after too 
  AddSucceedingModuleType(MAssembly::c_StripPairing);
  AddSucceedingModuleType(MAssembly::c_DepthCorrection);
  AddSucceedingModuleType(MAssembly::c_EventSaver);

  // Set if this module has an options GUI
  m_HasOptionsGUI = true;

  // Can the program be run multi-threaded
  m_AllowMultiThreading = true;

  // Can we use multiple instances of this class
  m_AllowMultipleInstances = true;

  m_ExcludeLVFirst = false;
  m_ExcludeHVFirst = false;
}


////////////////////////////////////////////////////////////////////////////////

MModuleHitSideFilter::MModuleHitSideFilter(const MModuleHitSideFilter& Filter) : MModule()
{
  m_Name = Filter.m_Name;
  m_XmlTag = Filter.m_XmlTag;
  m_HasOptionsGUI = Filter.m_HasOptionsGUI;
  m_AllowMultiThreading = Filter.m_AllowMultiThreading;
  m_AllowMultipleInstances = Filter.m_AllowMultipleInstances;

  // Copy your specific settings
  m_ExcludeLVFirst = Filter.m_ExcludeLVFirst;
  m_ExcludeHVFirst = Filter.m_ExcludeHVFirst;
}


////////////////////////////////////////////////////////////////////////////////


MModuleHitSideFilter::~MModuleHitSideFilter()
{
  // Delete this instance of MModuleHitSideFilter
}

////////////////////////////////////////////////////////////////////////////////


bool MModuleHitSideFilter::Initialize()
{
  // Initialize the module

  return MModule::Initialize();
}


////////////////////////////////////////////////////////////////////////////////


bool MModuleHitSideFilter::AnalyzeEvent(MReadOutAssembly* Event)
{
  // Can probably make these numbers smaller
  double MinTimeLV = 1e10;
  double MinTimeHV = 1e10;
  bool FoundLV = false;
  bool FoundHV = false;

  // Loop through all the hits in an event
  for (unsigned int i = 0; i < Event->GetNStripHits(); ++i) {
    MStripHit* SH = Event->GetStripHit(i);

    if (SH->HasCalibratedTiming() == false) {
      continue;
    }

    if (SH->IsLowVoltageStrip() == true) {
      if (SH->GetTiming() < MinTimeLV) {
        MinTimeLV = SH->GetTiming();
      }
      FoundLV = true;
    } else {
      if (SH->GetTiming() < MinTimeHV) {
        MinTimeHV = SH->GetTiming();
      }
      FoundHV = true;
    }
  }

  // If we don't have hits on BOTH sides, we don't know where the gamma came from
  // so we cut it out
  if (FoundLV == false || FoundHV == false) {
    return false;
  }

  // We have both sides. Now determine which side was hit first
  if (MinTimeLV < MinTimeHV) {
    // This event started on the LV side
    // If the user wants to exclude LV-first hits, delete it
    if (m_ExcludeLVFirst == true) return false;
  }
  else if (MinTimeHV < MinTimeLV) {
    // This event started on the HV side
    // If the user wants to exclude HV-first hits, delete it
    if (m_ExcludeHVFirst == true) return false;
  }

  // If it passes both the coincidence check and the timing check, keep it.
  return true;
}


////////////////////////////////////////////////////////////////////////////////


void MModuleHitSideFilter::Finalize()
{
  MModule::Finalize();
}


////////////////////////////////////////////////////////////////////////////////


void MModuleHitSideFilter::ShowOptionsGUI()
{
  //! Show the options GUI

  MGUIOptionsHitSideFilter* Options = new MGUIOptionsHitSideFilter(this);
  Options->Create();
  gClient->WaitForUnmap(Options);
}


////////////////////////////////////////////////////////////////////////////////


bool MModuleHitSideFilter::ReadXmlConfiguration(MXmlNode* Node)
{
  //! Read the configuration data from an XML node

  MXmlNode* ExcludeLVNode = Node->GetNode("ExcludeLVFirst");
  if (ExcludeLVNode != nullptr) {
    m_ExcludeLVFirst = ExcludeLVNode->GetValueAsBoolean();
  }

  MXmlNode* ExcludeHVNode = Node->GetNode("ExcludeHVFirst");
  if (ExcludeHVNode != nullptr) {
    m_ExcludeHVFirst = ExcludeHVNode->GetValueAsBoolean();
  }

  return true;
}


////////////////////////////////////////////////////////////////////////////////


MXmlNode* MModuleHitSideFilter::CreateXmlConfiguration()
{
  //! Create an XML node tree from the configuration

  MXmlNode* Node = new MXmlNode(0, m_XmlTag);
  
  new MXmlNode(Node, "ExcludeLVFirst", m_ExcludeLVFirst);
  new MXmlNode(Node, "ExcludeHVFirst", m_ExcludeHVFirst);

  return Node;
}

// MModuleHitSideFilter.cxx: the end...
////////////////////////////////////////////////////////////////////////////////
