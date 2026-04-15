/*
 * MGUIOptionsHitSideFilter.h
 *
 * Copyright (C) by Robin Anthony-Petersen.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MGUIOptionsHitSideFilter__
#define __MGUIOptionsHitSideFilter__


////////////////////////////////////////////////////////////////////////////////


// ROOT libs:
#include <TGFrame.h>
#include <TGButton.h>

// MEGAlib libs:
#include "MGlobal.h"
#include "MGUIOptions.h"

// Forward declarations:
class MModuleHitSideFilter;


////////////////////////////////////////////////////////////////////////////////


class MGUIOptionsHitSideFilter : public MGUIOptions
{
  // public interface:
 public:
  //! Standard constructor
  MGUIOptionsHitSideFilter(MModule* Module);
  //! Default destructor
  virtual ~MGUIOptionsHitSideFilter();

  //! GUI is built
  virtual void Create();
  //! This is called when the "OK" or "Apply" button is pressed
  virtual bool OnApply();


  // private methods:
 private:


  // private members:
 private:

  //! Checkbutton for LV exclusion
  TGCheckButton* m_ExcludeLVFirst;
  //! Checkbutton for HV exclusion
  TGCheckButton* m_ExcludeHVFirst;


#ifdef ___CLING___
 public:
  ClassDef(MGUIOptionsHitSideFilter, 0) // GUI for the side hit timing filter
#endif

};

#endif


////////////////////////////////////////////////////////////////////////////////
