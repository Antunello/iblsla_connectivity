// Mainframe macro generated from application: /Users/javierb/Downloads/root/bin/root.exe
// By ROOT version 5.34/00 on 2012-08-14 10:35:17

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

void display_ja()
{

// main frame
TGMainFrame *fMainFrame929 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
fMainFrame929->SetName("fMainFrame929");
TGTab *fTab670 = new TGTab(fMainFrame929,865,605);

// container of "RT USBpix&RCE"
TGCompositeFrame *fCompositeFrame673;
fCompositeFrame673 = fTab670->AddTab("RT USBpix&RCE");
fCompositeFrame673->SetLayoutManager(new TGVerticalLayout(fCompositeFrame673));

// "Root Files" group frame
TGGroupFrame *fGroupFrame687 = new TGGroupFrame(fCompositeFrame673,"Root Files",kHorizontalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());

TGHorizontalFrame *hframe000 = new TGHorizontalFrame(fGroupFrame687);
TGHorizontalFrame *hframe001 = new TGHorizontalFrame(fGroupFrame687);

TGCheckButton *fCheckButton688 = new TGCheckButton(hframe000,"USBpix RT.root");
fCheckButton688->SetState(kButtonDown);
fCheckButton688->SetTextJustify(36);
fCheckButton688->SetMargins(0,0,0,0);
fCheckButton688->SetWrapLength(-1);
hframe000->AddFrame(fCheckButton688, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsCenterY, 2, 2, 2, 2));
TGCheckButton *fCheckButton689 = new TGCheckButton(hframe001, "RCE RT.root");
fCheckButton689->SetTextJustify(36);
fCheckButton689->SetMargins(0,0,0,0);
fCheckButton689->SetWrapLength(-1);
hframe001->AddFrame(fCheckButton689, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsCenterY,2,2,2,2));
fGroupFrame687->AddFrame(hframe000, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
fGroupFrame687->AddFrame(hframe001, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
   
TGComboBox *fComboBox560 = new TGComboBox(hframe000,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
fComboBox560->SetName("fComboBox560");
fComboBox560->AddEntry("Select Module...",0);
fComboBox560->AddEntry("Custom Module Path",1);
fComboBox560->AddEntry("---",2);
fComboBox560->AddEntry("Dummy Entry 4 ",3);
fComboBox560->AddEntry("Dummy Entry 5 ",4);
fComboBox560->AddEntry("Dummy Entry 6 ",5);
fComboBox560->AddEntry("Dummy Entry 7 ",6);
fComboBox560->Resize(200,22);
fComboBox560->Select(0);
hframe000->AddFrame(fComboBox560, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

TGComboBox *fComboBox561 = new TGComboBox(hframe001,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
fComboBox561->SetName("fComboBox561");
fComboBox561->AddEntry("Select Module...",0);
fComboBox561->AddEntry("Custom Module Path",1);
fComboBox561->AddEntry("---",2);
fComboBox561->AddEntry("Dummy Entry 4 ",3);
fComboBox561->AddEntry("Dummy Entry 5 ",4);
fComboBox561->AddEntry("Dummy Entry 6 ",5);
fComboBox561->AddEntry("Dummy Entry 7 ",6);
fComboBox561->Resize(200,22);
fComboBox561->Select(0);
hframe001->AddFrame(fComboBox561, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

TGFont *ufont;         // will reflect user font changes
ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

TGGC   *uGC;           // will reflect user GC changes
// graphics context changes
GCValues_t valEntry690;
valEntry690.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
gClient->GetColorByName("#000000",valEntry690.fForeground);
gClient->GetColorByName("#e0e0e0",valEntry690.fBackground);
valEntry690.fFillStyle = kFillSolid;
valEntry690.fFont = ufont->GetFontHandle();
valEntry690.fGraphicsExposures = kFALSE;
uGC = gClient->GetGC(&valEntry690, kTRUE);
TGTextEntry *fTextEntry690 = new TGTextEntry(hframe000, new TGTextBuffer(47),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
fTextEntry690->SetMaxLength(4096);
fTextEntry690->SetAlignment(kTextLeft);
fTextEntry690->SetText("HERE IS WHERE YOU SHOULD SPECIFY THE PATH 1863");
fTextEntry690->Resize(552,fTextEntry690->GetDefaultHeight());
hframe000->AddFrame(fTextEntry690, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fTextEntry690->MoveResize(286,24,552,22);

ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

// graphics context changes
GCValues_t valEntry691;
valEntry691.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
gClient->GetColorByName("#000000",valEntry691.fForeground);
gClient->GetColorByName("#e0e0e0",valEntry691.fBackground);
valEntry691.fFillStyle = kFillSolid;
valEntry691.fFont = ufont->GetFontHandle();
valEntry691.fGraphicsExposures = kFALSE;
uGC = gClient->GetGC(&valEntry691, kTRUE);
TGTextEntry *fTextEntry691 = new TGTextEntry(hframe001, new TGTextBuffer(47),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
fTextEntry691->SetMaxLength(4096);
fTextEntry691->SetAlignment(kTextLeft);
fTextEntry691->SetText("HERE IS WHERE YOU SHOULD SPECIFY THE PATH 1870");
fTextEntry691->Resize(552,fTextEntry691->GetDefaultHeight());
hframe001->AddFrame(fTextEntry691, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fTextEntry691->MoveResize(286,56,552,22);

fGroupFrame687->SetLayoutManager(new TGVerticalLayout(fGroupFrame687));
//fGroupFrame687->Resize(848,112);
fCompositeFrame673->AddFrame(fGroupFrame687, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));

// Horizontal frame for the sidebar and tcanvas
TGHorizontalFrame *vframe0 = new TGHorizontalFrame(fCompositeFrame673);

// "fGroupFrame891" group frame
TGGroupFrame *fGroupFrame716 = new TGGroupFrame(vframe0,"fGroupFrame891",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
fGroupFrame716->SetLayoutBroken(kTRUE);
TGCheckButton *fCheckButton717 = new TGCheckButton(fGroupFrame716,"IV_scan");
fCheckButton717->SetTextJustify(36);
fCheckButton717->SetMargins(0,0,0,0);
fCheckButton717->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton717, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton717->MoveResize(18,18,107,17);
TGCheckButton *fCheckButton718 = new TGCheckButton(fGroupFrame716,"Digital_Test");
fCheckButton718->SetTextJustify(36);
fCheckButton718->SetMargins(0,0,0,0);
fCheckButton718->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton718, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton718->MoveResize(18,39,107,17);
TGCheckButton *fCheckButton719 = new TGCheckButton(fGroupFrame716,"Analog_Test");
fCheckButton719->SetTextJustify(36);
fCheckButton719->SetMargins(0,0,0,0);
fCheckButton719->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton719, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton719->MoveResize(18,60,107,17);
TGCheckButton *fCheckButton720 = new TGCheckButton(fGroupFrame716,"Threshold_Scan_Mean");
fCheckButton720->SetTextJustify(36);
fCheckButton720->SetMargins(0,0,0,0);
fCheckButton720->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton720, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton720->MoveResize(18,81,152,17);
TGCheckButton *fCheckButton721 = new TGCheckButton(fGroupFrame716,"Threshold_Scan_Noise");
fCheckButton721->SetTextJustify(36);
fCheckButton721->SetMargins(0,0,0,0);
fCheckButton721->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton721, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton721->MoveResize(18,102,152,17);
TGCheckButton *fCheckButton722 = new TGCheckButton(fGroupFrame716,"CrossTalk_Scan");
fCheckButton722->SetTextJustify(36);
fCheckButton722->SetMargins(0,0,0,0);
fCheckButton722->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton722, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton722->MoveResize(18,123,112,17);
TGCheckButton *fCheckButton723 = new TGCheckButton(fGroupFrame716,"fTextButton946");
fCheckButton723->SetTextJustify(36);
fCheckButton723->SetMargins(0,0,0,0);
fCheckButton723->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton723, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton723->MoveResize(18,144,107,17);
TGCheckButton *fCheckButton724 = new TGCheckButton(fGroupFrame716,"fTextButton953");
fCheckButton724->SetTextJustify(36);
fCheckButton724->SetMargins(0,0,0,0);
fCheckButton724->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton724, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton724->MoveResize(18,165,107,17);
TGCheckButton *fCheckButton725 = new TGCheckButton(fGroupFrame716,"fTextButton960");
fCheckButton725->SetTextJustify(36);
fCheckButton725->SetMargins(0,0,0,0);
fCheckButton725->SetWrapLength(-1);
fGroupFrame716->AddFrame(fCheckButton725, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fCheckButton725->MoveResize(18,186,107,17);

// list box
TGListBox *fListBox726 = new TGListBox(fGroupFrame716);
fListBox726->AddEntry("Entry 1",0);
fListBox726->AddEntry("Entry 2",1);
fListBox726->AddEntry("Entry 3",2);
fListBox726->AddEntry("Entry 4",3);
fListBox726->AddEntry("Entry 5",4);
fListBox726->AddEntry("Entry 6",5);
fListBox726->AddEntry("Entry 7",6);
fListBox726->Resize(128,164);
fGroupFrame716->AddFrame(fListBox726, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fListBox726->MoveResize(16,208,128,164);
TGRadioButton *fRadioButton740 = new TGRadioButton(fGroupFrame716,"Without HV");
fRadioButton740->SetTextJustify(36);
fRadioButton740->SetMargins(0,0,0,0);
fRadioButton740->SetWrapLength(-1);
fGroupFrame716->AddFrame(fRadioButton740, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton740->MoveResize(16,376,106,19);
TGRadioButton *fRadioButton741 = new TGRadioButton(fGroupFrame716,"With HV");
fRadioButton741->SetTextJustify(36);
fRadioButton741->SetMargins(0,0,0,0);
fRadioButton741->SetWrapLength(-1);
fGroupFrame716->AddFrame(fRadioButton741, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton741->MoveResize(16,400,106,19);

fGroupFrame716->SetLayoutManager(new TGVerticalLayout(fGroupFrame716));
fGroupFrame716->Resize(184,449);
vframe0->AddFrame(fGroupFrame716, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY,2,2,2,2));

// embedded canvas
TRootEmbeddedCanvas *fRootEmbeddedCanvas674 = new TRootEmbeddedCanvas(0,vframe0,660,444);
Int_t wfRootEmbeddedCanvas674 = fRootEmbeddedCanvas674->GetCanvasWindowId();
TCanvas *c123 = new TCanvas("c123", 10, 10, wfRootEmbeddedCanvas674);
fRootEmbeddedCanvas674->AdoptCanvas(c123);
vframe0->AddFrame(fRootEmbeddedCanvas674, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY));


fCompositeFrame673->AddFrame(vframe0, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));


// container of "Stave Comp"
TGCompositeFrame *fCompositeFrame743;
fCompositeFrame743 = fTab670->AddTab("Stave Comp");
fCompositeFrame743->SetLayoutManager(new TGVerticalLayout(fCompositeFrame743));


// "fGroupFrame811" group frame
TGGroupFrame *fGroupFrame744 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame811",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
fGroupFrame744->SetLayoutBroken(kTRUE);
TGRadioButton *fRadioButton745 = new TGRadioButton(fGroupFrame744,"Stave 1.root");
fRadioButton745->SetTextJustify(36);
fRadioButton745->SetMargins(0,0,0,0);
fRadioButton745->SetWrapLength(-1);
fGroupFrame744->AddFrame(fRadioButton745, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton745->MoveResize(8,24,113,19);
TGRadioButton *fRadioButton746 = new TGRadioButton(fGroupFrame744,"Stave 2.root");
fRadioButton746->SetTextJustify(36);
fRadioButton746->SetMargins(0,0,0,0);
fRadioButton746->SetWrapLength(-1);
fGroupFrame744->AddFrame(fRadioButton746, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton746->MoveResize(8,56,113,19);
TGNumberEntry *fNumberEntry747 = new TGNumberEntry(fGroupFrame744, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5);
fGroupFrame744->AddFrame(fNumberEntry747, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fNumberEntry747->MoveResize(136,24,59,22);
TGNumberEntry *fNumberEntry751 = new TGNumberEntry(fGroupFrame744, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5);
fGroupFrame744->AddFrame(fNumberEntry751, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fNumberEntry751->MoveResize(136,55,59,22);

ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

// graphics context changes
GCValues_t valEntry755;
valEntry755.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
gClient->GetColorByName("#000000",valEntry755.fForeground);
gClient->GetColorByName("#e0e0e0",valEntry755.fBackground);
valEntry755.fFillStyle = kFillSolid;
valEntry755.fFont = ufont->GetFontHandle();
valEntry755.fGraphicsExposures = kFALSE;
uGC = gClient->GetGC(&valEntry755, kTRUE);
TGTextEntry *fTextEntry755 = new TGTextEntry(fGroupFrame744, new TGTextBuffer(31),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
fTextEntry755->SetMaxLength(4096);
fTextEntry755->SetAlignment(kTextLeft);
fTextEntry755->SetText("root file path for stave 1");
fTextEntry755->Resize(592,fTextEntry755->GetDefaultHeight());
fGroupFrame744->AddFrame(fTextEntry755, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fTextEntry755->MoveResize(208,24,592,22);

ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

// graphics context changes
GCValues_t valEntry756;
valEntry756.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
gClient->GetColorByName("#000000",valEntry756.fForeground);
gClient->GetColorByName("#e0e0e0",valEntry756.fBackground);
valEntry756.fFillStyle = kFillSolid;
valEntry756.fFont = ufont->GetFontHandle();
valEntry756.fGraphicsExposures = kFALSE;
uGC = gClient->GetGC(&valEntry756, kTRUE);
TGTextEntry *fTextEntry756 = new TGTextEntry(fGroupFrame744, new TGTextBuffer(31),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
fTextEntry756->SetMaxLength(4096);
fTextEntry756->SetAlignment(kTextLeft);
fTextEntry756->SetText("root file path for stave 2");
fTextEntry756->Resize(592,fTextEntry756->GetDefaultHeight());
fGroupFrame744->AddFrame(fTextEntry756, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fTextEntry756->MoveResize(208,56,592,22);

fGroupFrame744->SetLayoutManager(new TGVerticalLayout(fGroupFrame744));
fGroupFrame744->Resize(856,112);
fCompositeFrame743->AddFrame(fGroupFrame744, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));


// "fGroupFrame828" group frame
TGGroupFrame *fGroupFrame757 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame828",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
fGroupFrame757->SetLayoutBroken(kTRUE);
TGLabel *fLabel758 = new TGLabel(fGroupFrame757,"List of modules");
fLabel758->SetTextJustify(36);
fLabel758->SetMargins(0,0,0,0);
fLabel758->SetWrapLength(-1);
fGroupFrame757->AddFrame(fLabel758, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fLabel758->MoveResize(16,17,88,18);

// list box
TGListBox *fListBox759 = new TGListBox(fGroupFrame757);
fListBox759->AddEntry("Entry 1",0);
fListBox759->AddEntry("Entry 2",1);
fListBox759->AddEntry("Entry 3",2);
fListBox759->AddEntry("Entry 4",3);
fListBox759->AddEntry("Entry 5",4);
fListBox759->AddEntry("Entry 6",5);
fListBox759->AddEntry("Entry 7",6);
fListBox759->Resize(120,292);
fGroupFrame757->AddFrame(fListBox759, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fListBox759->MoveResize(16,40,120,292);

fGroupFrame757->SetLayoutManager(new TGVerticalLayout(fGroupFrame757));
fGroupFrame757->Resize(152,344);
fCompositeFrame743->AddFrame(fGroupFrame757, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

// "fGroupFrame1019" group frame
TGGroupFrame *fGroupFrame773 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame1019");
fGroupFrame773->SetLayoutBroken(kTRUE);

// combo box
TGComboBox *fComboBox774 = new TGComboBox(fGroupFrame773,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
fComboBox774->AddEntry("Entry 1 ",0);
fComboBox774->AddEntry("Entry 2 ",1);
fComboBox774->AddEntry("Entry 3 ",2);
fComboBox774->AddEntry("Entry 4 ",3);
fComboBox774->AddEntry("Entry 5 ",4);
fComboBox774->AddEntry("Entry 6 ",5);
fComboBox774->AddEntry("Entry 7 ",6);
fComboBox774->Resize(136,22);
fComboBox774->Select(-1);
fGroupFrame773->AddFrame(fComboBox774, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fComboBox774->MoveResize(8,24,136,22);
TGRadioButton *fRadioButton792 = new TGRadioButton(fGroupFrame773,"Without HV");
fRadioButton792->SetTextJustify(36);
fRadioButton792->SetMargins(0,0,0,0);
fRadioButton792->SetWrapLength(-1);
fGroupFrame773->AddFrame(fRadioButton792, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton792->MoveResize(16,56,113,19);
TGRadioButton *fRadioButton793 = new TGRadioButton(fGroupFrame773,"With HV");
fRadioButton793->SetTextJustify(36);
fRadioButton793->SetMargins(0,0,0,0);
fRadioButton793->SetWrapLength(-1);
fGroupFrame773->AddFrame(fRadioButton793, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
fRadioButton793->MoveResize(16,80,113,19);

fGroupFrame773->SetLayoutManager(new TGVerticalLayout(fGroupFrame773));
fGroupFrame773->Resize(152,120);
fCompositeFrame743->AddFrame(fGroupFrame773, new TGLayoutHints(kLHintsNormal));

// "fGroupFrame1433" group frame
TGGroupFrame *fGroupFrame794 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame1433");
fGroupFrame794->SetLayoutBroken(kTRUE);

fGroupFrame794->SetLayoutManager(new TGVerticalLayout(fGroupFrame794));
fGroupFrame794->Resize(126,34);
fCompositeFrame743->AddFrame(fGroupFrame794, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

// "fGroupFrame1440" group frame
TGGroupFrame *fGroupFrame795 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame1440");
fGroupFrame795->SetLayoutBroken(kTRUE);

fGroupFrame795->SetLayoutManager(new TGVerticalLayout(fGroupFrame795));
fGroupFrame795->Resize(126,34);
fCompositeFrame743->AddFrame(fGroupFrame795, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

// "fGroupFrame1447" group frame
TGGroupFrame *fGroupFrame796 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame1447");
fGroupFrame796->SetLayoutBroken(kTRUE);

fGroupFrame796->SetLayoutManager(new TGVerticalLayout(fGroupFrame796));
fGroupFrame796->Resize(126,34);
fCompositeFrame743->AddFrame(fGroupFrame796, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

// "fGroupFrame1555" group frame
TGGroupFrame *fGroupFrame797 = new TGGroupFrame(fCompositeFrame743,"fGroupFrame1555");
fGroupFrame797->SetLayoutBroken(kTRUE);

fGroupFrame797->SetLayoutManager(new TGVerticalLayout(fGroupFrame797));
fGroupFrame797->Resize(126,34);
fCompositeFrame743->AddFrame(fGroupFrame797, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));


// container of "tab3"
TGCompositeFrame *fCompositeFrame799;
fCompositeFrame799 = fTab670->AddTab("tab3");
fCompositeFrame799->SetLayoutManager(new TGVerticalLayout(fCompositeFrame799));


// container of "tab4"
TGCompositeFrame *fCompositeFrame801;
fCompositeFrame801 = fTab670->AddTab("tab4");
fCompositeFrame801->SetLayoutManager(new TGVerticalLayout(fCompositeFrame801));


fTab670->SetTab(0);

fTab670->Resize(fTab670->GetDefaultSize());
fMainFrame929->AddFrame(fTab670, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));

fMainFrame929->SetMWMHints(kMWMDecorAll,
kMWMFuncAll,
kMWMInputModeless);
fMainFrame929->MapSubwindows();

fMainFrame929->Resize(fMainFrame929->GetDefaultSize());
fMainFrame929->MapWindow();
fMainFrame929->Resize(1000,1000);
}  
