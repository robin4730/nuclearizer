/*
 * MModuleHitSideFilter.h
 *
 * Copyright (C) by Robin Anthony-Petersen.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MModuleHitSideFilter__
#define __MModuleHitSideFilter__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:

// ROOT libs:

// MEGAlib libs:
#include "MGlobal.h"
#include "MModule.h"

// Forward declarations:
class MReadOutAssembly;
class MXmlNode;


////////////////////////////////////////////////////////////////////////////////


class MModuleHitSideFilter : public MModule
{
  // public interface:
 public:
  MModuleHitSideFilter();
  virtual ~MModuleHitSideFilter();

  //! Initialize the module
  virtual bool Initialize();
  //! Analyze the event
  virtual bool AnalyzeEvent(MReadOutAssembly* Event);
  //! Be able to clone module
    virtual MModule* Clone() { return new MModuleHitSideFilter(*this); }
  //! Finalize the module
  virtual void Finalize();

  //! Show the options GUI for the filter toggles
  virtual void ShowOptionsGUI();

  //! Read the configuration from an XML file
  virtual bool ReadXmlConfiguration(MXmlNode* Node);
  //! Create an XML node for the configuration file
  virtual MXmlNode* CreateXmlConfiguration();
  
  //! GUI buttons
  void SetExcludeLVFirst(bool b) { m_ExcludeLVFirst = b; }
  bool GetExcludeLVFirst() { return m_ExcludeLVFirst; }
  void SetExcludeHVFirst(bool b) { m_ExcludeHVFirst = b; }
  bool GetExcludeHVFirst() { return m_ExcludeHVFirst; }


  // protected methods:
 protected:

  // private methods:
 private:
  MModuleHitSideFilter(const MModuleHitSideFilter& Filter);


  // protected members:
 protected:


  // private members:
 private:
  //! Toggle to exclude events where the Low Voltage side triggers first
  bool m_ExcludeLVFirst;
  //! Toggle to exclude events where the High Voltage side triggers first
  bool m_ExcludeHVFirst;


#ifdef ___CLING___
 public:
  ClassDef(MModuleHitSideFilter, 0) // Filter for side-timing coincidences
#endif

};

#endif


////////////////////////////////////////////////////////////////////////////////
