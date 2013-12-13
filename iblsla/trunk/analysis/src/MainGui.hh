#if !defined(_IBLSLA_MAIN_GUI_H)
#define _IBLSLA_MAIN_GUI_H

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGTextEdit
#include "TGTextEdit.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGTextEntry
#include "TGTextEntry.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGView
#include "TGView.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif
#ifndef ROOT_TGObject
#include "TGObject.h"
#endif

#include "Riostream.h"

#include "HistoReader.hh"
#include "Astave.hh"
#include "Sr1_converter.hh"

enum CompType
{
  COMP_BEFORE_TC_AT,
  COMP_BEFORE_TC_BT,
  COMP_AFTER_TC_AT,
  COMP_AFTER_TC_BT,
  COMP_RT,
  COMP_ALL_TC,
  RT
};

class MainGui {
public:
  MainGui();
  
  void PrintCanvas();
  void DoModuleLoad();
  void DoStaveLoad();
  void DoMainFrameClose();
  void DoModuleSelected(int id);
  void DoStaveModuleSelected(int id);
  void DoStaveSelected(int id);
  vector<std::string> modules;
  vector<std::string> modules_complete;
protected:
  TGMainFrame *mainFrame;
  
  void LoadModuleList();
  void LoadStaveModuleList();
  
  vector<std::string> stave_modules;
  vector<std::string> stave_modules_posid;
  std::string GetSelectedModule();
  std::string GetSelectedModule2();
  std::string GetSelectedStaveModule();
  std::string GetStaveId();
  int GetSelectedCompTypeStave();
  ProcessPosition GetSelectedSystemType();
  ProcessPosition GetSelectedSystemTypeStave(int comp_type);
  ProcessPosition GetSelectedSystemTypeB();
  ProcessPosition GetSelectedSystemTypeStave();
  unsigned int GetSelectedChip();
  unsigned int GetSelectedChipB();
  unsigned int GetSelectedHVType();
  unsigned int GetSelectedHVTypeB();
  
  unsigned int GetSelectedHVTypeTh();
  void EnableModuleProcessPointRadioButtons();
  void EnableModuleProcessPointRadioButtons2();
  void EnableHVRadioButtons();
  void EnableStaveProcessPointRadioButtons();
  void EnableStaveModuleComparison(int enable);
  TGComboBox *moduleComboBox, *moduleComboBox2, *stave_moduleComboBox;
  TGRadioButton *radiobutton_module_processpoint_usbpix;
  TGRadioButton *radiobutton_module_processpoint_rce;
  TGRadioButton *radiobutton_module_processpoint_usbpix_;
  TGRadioButton *radiobutton_module_processpoint_rce_;
  TGRadioButton *radiobutton_module_processpoint_usbpix_2;
  TGRadioButton *radiobutton_module_processpoint_rce_2;
  TGRadioButton *radiobutton_module_chip_0;
  TGRadioButton *radiobutton_module_chip_1;
  TGRadioButton *radiobutton_module_chip_0_B;
  TGRadioButton *radiobutton_module_chip_1_B;

  TGRadioButton *radiobutton_stave_processpoint_afterTC_BT;
  TGRadioButton *radiobutton_stave_processpoint_beforeTC_BT;
  TGRadioButton *radiobutton_stave_processpoint_RT;
  TGRadioButton *radiobutton_stave_processpoint_afterTC_AT;
  TGRadioButton *radiobutton_stave_processpoint_beforeTC_AT;


  TGRadioButton *radiobutton_stave_compRT;
  TGRadioButton *radiobutton_stave_compAll;

  std::vector<TGCheckButton*> module_analysis_checkbuttons;	
  std::vector<TGCheckButton*> stave_analysis_checkbuttons;
  
  TGRadioButton *radiobutton_hvon;
  TGRadioButton *radiobutton_hvoff;
  TGRadioButton *radiobutton_hvon_B;
  TGRadioButton *radiobutton_hvoff_B;
  TGRadioButton *radiobutton_hvon_th;
  TGRadioButton *radiobutton_hvoff_th;
  TGNumberEntry *fNumberEntry747;
  //  TGNumberEntry *fNumberEntry751;
  HistoReader *moduleHistoReader;
  
  void LoadStaveList();
  vector<std::string> staves;
  
  void LoadModuleHistogramList();
  vector<std::string> module_histograms;
  
  void InitializeGui();
  void FillModuleComboBox(TGComboBox* box);
  void FillStaveModuleComboBox(TGComboBox* box);
  
  void ResetMemberVariables();
  TCanvas *module_canvas;
  TCanvas *module_canvas_s;

  int m_enable_stave_module_comparison;
  int m_stave_module_id;
};

#if defined(__CINT__)
#pragma link C++ class MainGui;
#endif


#endif /* #if !defined(_IBLSLA_MAIN_GUI_H)  */
/* vim:set shiftwidth=2 tabstop=2 expandtab: */
