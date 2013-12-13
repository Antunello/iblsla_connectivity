// Mainframe macro generated from application: /Users/javierb/Downloads/root/bin/root.exe
// By ROOT version 5.34/00 on 2012-08-03 14:13:18

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
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
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
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
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

#include "Riostream.h"

void display_1()
{

   // main frame
   TGMainFrame *fMainFrame1024 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
   fMainFrame1024->SetName("fMainFrame1024");
   fMainFrame1024->SetLayoutBroken(kTRUE);

   // composite frame
   TGCompositeFrame *fMainFrame2040 = new TGCompositeFrame(fMainFrame1024,869,609,kVerticalFrame);
   fMainFrame2040->SetName("fMainFrame2040");
   fMainFrame2040->SetLayoutBroken(kTRUE);

   // composite frame
   TGCompositeFrame *fMainFrame1241 = new TGCompositeFrame(fMainFrame2040,867,607,kVerticalFrame);
   fMainFrame1241->SetName("fMainFrame1241");
   fMainFrame1241->SetLayoutBroken(kTRUE);

   // tab widget
   TGTab *fTab665 = new TGTab(fMainFrame1241,865,605);

   // container of "RT USBpix&RCE"
   TGCompositeFrame *fCompositeFrame668;
   fCompositeFrame668 = fTab665->AddTab("RT USBpix&RCE");
   fCompositeFrame668->SetLayoutManager(new TGVerticalLayout(fCompositeFrame668));

   // embedded canvas
   TRootEmbeddedCanvas *fRootEmbeddedCanvas669 = new TRootEmbeddedCanvas(0,fCompositeFrame668,660,444);
   Int_t wfRootEmbeddedCanvas669 = fRootEmbeddedCanvas669->GetCanvasWindowId();
   TCanvas *c124 = new TCanvas("c124", 10, 10, wfRootEmbeddedCanvas669);
   fRootEmbeddedCanvas669->AdoptCanvas(c124);
   fCompositeFrame668->AddFrame(fRootEmbeddedCanvas669, new TGLayoutHints(kLHintsRight | kLHintsBottom));

   ULong_t ucolor;        // will reflect user color changes
   gClient->GetColorByName("#d4cf87",ucolor);

   // "Root Files" group frame
   TGGroupFrame *fGroupFrame682 = new TGGroupFrame(fCompositeFrame668,"Root Files",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct(),ucolor);
   fGroupFrame682->SetLayoutBroken(kTRUE);
   TGRadioButton *fRadioButton683 = new TGRadioButton(fGroupFrame682,"USBpix RT.root");
   fRadioButton683->SetTextJustify(36);
   fRadioButton683->SetMargins(0,0,0,0);
   fRadioButton683->SetWrapLength(-1);
   fGroupFrame682->AddFrame(fRadioButton683, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsCenterY,2,2,2,2));
   fRadioButton683->MoveResize(18,24,111,17);
   TGRadioButton *fRadioButton684 = new TGRadioButton(fGroupFrame682,"RCE RT.root");
   fRadioButton684->SetTextJustify(36);
   fRadioButton684->SetMargins(0,0,0,0);
   fRadioButton684->SetWrapLength(-1);
   fGroupFrame682->AddFrame(fRadioButton684, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsCenterY,2,2,2,2));
   fRadioButton684->MoveResize(18,57,111,17);

   TGFont *ufont;         // will reflect user font changes
   ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   TGGC   *uGC;           // will reflect user GC changes
   // graphics context changes
   GCValues_t valEntry685;
   valEntry685.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry685.fForeground);
   gClient->GetColorByName("#e0e0e0",valEntry685.fBackground);
   valEntry685.fFillStyle = kFillSolid;
   valEntry685.fFont = ufont->GetFontHandle();
   valEntry685.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry685, kTRUE);
   TGTextEntry *fTextEntry685 = new TGTextEntry(fGroupFrame682, new TGTextBuffer(47),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
   fTextEntry685->SetMaxLength(4096);
   fTextEntry685->SetAlignment(kTextLeft);
   fTextEntry685->SetText("HERE IS WHERE YOU SHOULD SPECIFY THE PATH 1863");
   fTextEntry685->Resize(552,fTextEntry685->GetDefaultHeight());
   fGroupFrame682->AddFrame(fTextEntry685, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextEntry685->MoveResize(256,24,552,22);

   ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // graphics context changes
   GCValues_t valEntry686;
   valEntry686.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry686.fForeground);
   gClient->GetColorByName("#e0e0e0",valEntry686.fBackground);
   valEntry686.fFillStyle = kFillSolid;
   valEntry686.fFont = ufont->GetFontHandle();
   valEntry686.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry686, kTRUE);
   TGTextEntry *fTextEntry686 = new TGTextEntry(fGroupFrame682, new TGTextBuffer(47),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
   fTextEntry686->SetMaxLength(4096);
   fTextEntry686->SetAlignment(kTextLeft);
   fTextEntry686->SetText("HERE IS WHERE YOU SHOULD SPECIFY THE PATH 1870");
   fTextEntry686->Resize(552,fTextEntry686->GetDefaultHeight());
   fGroupFrame682->AddFrame(fTextEntry686, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextEntry686->MoveResize(256,56,552,22);

   fGroupFrame682->SetLayoutManager(new TGVerticalLayout(fGroupFrame682));
   fGroupFrame682->Resize(848,112);
   fCompositeFrame668->AddFrame(fGroupFrame682, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   gClient->GetColorByName("#deba87",ucolor);

   // "fGroupFrame891" group frame
   TGGroupFrame *fGroupFrame687 = new TGGroupFrame(fCompositeFrame668,"fGroupFrame891",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct(),ucolor);
   fGroupFrame687->SetLayoutBroken(kTRUE);
   TGCheckButton *fCheckButton688 = new TGCheckButton(fGroupFrame687,"IV_scan");
   fCheckButton688->SetTextJustify(36);
   fCheckButton688->SetMargins(0,0,0,0);
   fCheckButton688->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton688, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton688->MoveResize(18,18,107,17);
   TGCheckButton *fCheckButton689 = new TGCheckButton(fGroupFrame687,"Digital_Test");
   fCheckButton689->SetTextJustify(36);
   fCheckButton689->SetMargins(0,0,0,0);
   fCheckButton689->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton689, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton689->MoveResize(18,39,107,17);
   TGCheckButton *fCheckButton690 = new TGCheckButton(fGroupFrame687,"Analog_Test");
   fCheckButton690->SetTextJustify(36);
   fCheckButton690->SetMargins(0,0,0,0);
   fCheckButton690->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton690, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton690->MoveResize(18,60,107,17);
   TGCheckButton *fCheckButton691 = new TGCheckButton(fGroupFrame687,"Threshold_Scan_Mean");
   fCheckButton691->SetTextJustify(36);
   fCheckButton691->SetMargins(0,0,0,0);
   fCheckButton691->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton691, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton691->MoveResize(18,81,107,17);
   TGCheckButton *fCheckButton692 = new TGCheckButton(fGroupFrame687,"Threshold_Scan_Noise");
   fCheckButton692->SetTextJustify(36);
   fCheckButton692->SetMargins(0,0,0,0);
   fCheckButton692->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton692, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton692->MoveResize(18,102,107,17);
   TGCheckButton *fCheckButton693 = new TGCheckButton(fGroupFrame687,"CrossTalk_Scan");
   fCheckButton693->SetTextJustify(36);
   fCheckButton693->SetMargins(0,0,0,0);
   fCheckButton693->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton693, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton693->MoveResize(18,123,107,17);
   TGCheckButton *fCheckButton694 = new TGCheckButton(fGroupFrame687,"fTextButton946");
   fCheckButton694->SetTextJustify(36);
   fCheckButton694->SetMargins(0,0,0,0);
   fCheckButton694->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton694, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton694->MoveResize(18,144,107,17);
   TGCheckButton *fCheckButton695 = new TGCheckButton(fGroupFrame687,"fTextButton953");
   fCheckButton695->SetTextJustify(36);
   fCheckButton695->SetMargins(0,0,0,0);
   fCheckButton695->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton695, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton695->MoveResize(18,165,107,17);
   TGCheckButton *fCheckButton696 = new TGCheckButton(fGroupFrame687,"fTextButton960");
   fCheckButton696->SetTextJustify(36);
   fCheckButton696->SetMargins(0,0,0,0);
   fCheckButton696->SetWrapLength(-1);
   fGroupFrame687->AddFrame(fCheckButton696, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fCheckButton696->MoveResize(18,186,107,17);

   // list box
   TGListBox *fListBox705 = new TGListBox(fGroupFrame687);
   fListBox705->AddEntry("Entry 1",0);
   fListBox705->AddEntry("Entry 2",1);
   fListBox705->AddEntry("Entry 3",2);
   fListBox705->AddEntry("Entry 4",3);
   fListBox705->AddEntry("Entry 5",4);
   fListBox705->AddEntry("Entry 6",5);
   fListBox705->AddEntry("Entry 7",6);
   fListBox705->Resize(128,164);
   fGroupFrame687->AddFrame(fListBox705, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fListBox705->MoveResize(16,208,128,164);

   fGroupFrame687->SetLayoutManager(new TGVerticalLayout(fGroupFrame687));
   fGroupFrame687->Resize(184,449);
   fCompositeFrame668->AddFrame(fGroupFrame687, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));


   // container of "tab2"
   TGCompositeFrame *fCompositeFrame698;
   fCompositeFrame698 = fTab665->AddTab("tab2");
   fCompositeFrame698->SetLayoutManager(new TGVerticalLayout(fCompositeFrame698));


   // container of "tab3"
   TGCompositeFrame *fCompositeFrame700;
   fCompositeFrame700 = fTab665->AddTab("tab3");
   fCompositeFrame700->SetLayoutManager(new TGVerticalLayout(fCompositeFrame700));


   // container of "tab4"
   TGCompositeFrame *fCompositeFrame702;
   fCompositeFrame702 = fTab665->AddTab("tab4");
   fCompositeFrame702->SetLayoutManager(new TGVerticalLayout(fCompositeFrame702));


   fTab665->SetTab(0);

   fTab665->Resize(fTab665->GetDefaultSize());
   fMainFrame1241->AddFrame(fTab665, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTab665->MoveResize(0,0,865,605);

   fMainFrame2040->AddFrame(fMainFrame1241, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
   fMainFrame1241->MoveResize(0,0,867,607);

   fMainFrame1024->AddFrame(fMainFrame2040, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
   fMainFrame2040->MoveResize(0,0,869,609);

   fMainFrame1024->SetMWMHints(kMWMDecorAll,
                        kMWMFuncAll,
                        kMWMInputModeless);
   fMainFrame1024->MapSubwindows();

   fMainFrame1024->Resize(fMainFrame1024->GetDefaultSize());
   fMainFrame1024->MapWindow();
   fMainFrame1024->Resize(553,559);
}  
