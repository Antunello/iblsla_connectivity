#include "MainGui.hh"
#include "DbTools.hh"
#include "Analysis.hh"
#include "Astave.hh"
#include "Sr1_converter.hh"
#include <iostream>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>

MainGui::MainGui()
  : m_enable_stave_module_comparison(0)
{
  ResetMemberVariables();
  LoadModuleList();
  LoadStaveList();
  InitializeGui();
}

void MainGui::ResetMemberVariables()
{
  moduleComboBox = NULL;
  moduleComboBox2 = NULL;
  moduleHistoReader = NULL;
}

void MainGui::LoadModuleList()
{
  this->modules.clear();
  this->modules_complete.clear();
  DbTools::GetInstance()->GetModuleIdList2(this->modules);
  DbTools::GetInstance()->GetModuleIdList(this->modules_complete);
}

void MainGui::LoadStaveModuleList()
{
  this->stave_modules.clear();
  this->stave_modules = Astave::GetInstance()->GetModuleIdList(this->GetStaveId());
  this->stave_modules_posid = Astave::GetInstance()->GetModulePosIdList(this->GetStaveId());
}

void MainGui::LoadStaveList()
{
  this->staves.clear();
  DbTools::GetInstance()->GetStaveIdList(this->staves);
}

void MainGui::LoadModuleHistogramList()
{
  this->module_histograms.clear();
}

void MainGui::DoModuleSelected(int id)
{
  std::cerr << id << std::endl << std::flush;
  EnableModuleProcessPointRadioButtons();
  std::string module_id_2 = GetSelectedModule2();
  if(module_id_2!="")	EnableModuleProcessPointRadioButtons2();
}

void MainGui::DoStaveModuleSelected(int id)
{
  std::cerr << id << std::endl << std::flush;
  //EnableStaveModuleProcessPointRadioButtons();
  std::string module_id = GetSelectedStaveModule();
  if(module_id == "All") EnableStaveModuleComparison(0);
  else EnableStaveModuleComparison(1);
}

void MainGui::DoStaveSelected(int id)
{
  EnableStaveProcessPointRadioButtons();
  LoadStaveModuleList();
  FillStaveModuleComboBox(this->stave_moduleComboBox);
  this->stave_moduleComboBox->Select(0);
}

void MainGui::FillModuleComboBox(TGComboBox* box)
{
  int iij;
  iij=0;
  box->AddEntry("Select Module...",iij++);
  box->AddEntry("---",iij++);
  for (std::vector<string>::iterator iii = this->modules.begin(); iii != this->modules.end(); iii++)
    {
      box->AddEntry(iii->c_str(),iij++);
    }
}

void MainGui::FillStaveModuleComboBox(TGComboBox* box)
{
  int iij;
  iij=0;
  box->RemoveAll();
  box->AddEntry("All",iij++);
  box->AddEntry("---",iij++);
  std::vector<string>::iterator iii = this->stave_modules.begin();
  while(iii != this->stave_modules.end()){
    std::string list = this->stave_modules_posid.at(iij-2);
    list.append(": ");
    list.append((*iii).c_str());
    box->AddEntry(list.c_str(),iij++);
    iii++;
  }
}

void MainGui::EnableModuleProcessPointRadioButtons()
{
  std::string module = GetSelectedModule();
  int chipnumber = GetSelectedChip();
  int enusbpix = 0;
  int enrce = 0;
  int enchip_0 =0;
  int enchip_1 =0;
  int withHV=0;
  int withoutHV=0;

  int doublechipcheck = DbTools::GetInstance()->IsDoubleChip(module);
  /*
    if(GetSelectedSystemType() == PP_UsbPixReceptionTest){
    if(doublechipcheck == 0) doublechipcheck = 1;
    else if(doublechipcheck == 1) doublechipcheck = 0;
    }*/
  //  int doublechipcheck = DbTools::GetInstance()->IsDoubleChip(module);
  
  if (module != "")
    {
      std::vector<ProcessPosition> pps;
      
      DbTools::GetInstance()->GetAvailableProcessPrositions(module, chipnumber, pps);
      std::cerr << __FILE__ << ":" << __LINE__ << " " << pps.size() << std::endl << std::flush;
      
      for (std::vector<ProcessPosition>::iterator i = pps.begin(); i != pps.end(); i++){
	std::cerr << __FILE__ << ":" << __LINE__ << " " <<  ((int)(*i)) << std::endl << std::flush;
	enusbpix = enusbpix || ((*i) == PP_UsbPixReceptionTest);
	enrce = enrce || ((*i) == PP_RCEReceptionTest);
      }
      
      if( doublechipcheck ==1){
	enchip_0=1;
	enchip_1=1;
      }
      withHV=1;
      withoutHV=1;
    }
    
  radiobutton_hvon->SetEnabled(withHV);
  radiobutton_hvoff->SetEnabled(withoutHV);
  radiobutton_module_chip_0->SetEnabled(enchip_0);
  radiobutton_module_chip_1->SetEnabled(enchip_1);
  radiobutton_module_processpoint_rce->SetEnabled(enrce);
  radiobutton_module_processpoint_usbpix->SetEnabled(enusbpix);
}

void MainGui::EnableModuleProcessPointRadioButtons2()
{
  std::string module = GetSelectedModule2();
  int chipnumber = GetSelectedChipB();
  int enusbpix = 0;
  int enrce = 0;
  int enchip_0=0;
  int enchip_1 =0;
  int withHV=0;
  int withoutHV=0;
  int doublechipcheck = DbTools::GetInstance()->IsDoubleChip(module);
  if (module != ""){
    std::vector<ProcessPosition> pps;
    
    DbTools::GetInstance()->GetAvailableProcessPrositions(module, chipnumber, pps);
    std::cerr << __FILE__ << ":" << __LINE__ << " " << pps.size() << std::endl << std::flush;
    
    for (std::vector<ProcessPosition>::iterator i = pps.begin(); i != pps.end(); i++){
      std::cerr << __FILE__ << ":" << __LINE__ << " " <<  ((int)(*i)) << std::endl << std::flush;
      enusbpix = enusbpix || ((*i) == PP_UsbPixReceptionTest);
      enrce = enrce || ((*i) == PP_RCEReceptionTest);
    }
    if( doublechipcheck ==1){
      enchip_0=1;
      enchip_1=1;
    }
    
    withHV=1;
    withoutHV=1;
  }
  radiobutton_hvon_B->SetEnabled(withHV);
  radiobutton_hvoff_B->SetEnabled(withoutHV);
  radiobutton_module_chip_0_B->SetEnabled(enchip_0);
  radiobutton_module_chip_1_B->SetEnabled(enchip_1);
  radiobutton_module_processpoint_rce_->SetEnabled(enrce);
  radiobutton_module_processpoint_usbpix_->SetEnabled(enusbpix);
}

void MainGui::EnableStaveModuleComparison(int enable){
  m_enable_stave_module_comparison = enable;
}

std::string MainGui::GetStaveId()
{
  int staveid;
  std::string staveid_str;

  staveid = this->fNumberEntry747->GetNumber();

  std::ostringstream oss;
  oss << staveid;
  staveid_str=oss.str();

  return staveid_str;
}

int MainGui::GetSelectedCompTypeStave()
{
  int comp_type = 0;
  unsigned int BeforeTC_AT_state = 0;
  unsigned int AfterTC_AT_state = 0;
  unsigned int BeforeTC_BT_state = 0;
  unsigned int AfterTC_BT_state = 0;
  unsigned int CompRt_state = 0;
  unsigned int CompAll_state = 0;
  unsigned int RT_state = 0;

//  RT_state = this->radiobutton_stave_processpoint_RT->GetState();
  BeforeTC_AT_state = this->radiobutton_stave_processpoint_beforeTC_AT->GetState();
  AfterTC_AT_state = this->radiobutton_stave_processpoint_afterTC_AT->GetState();
  BeforeTC_BT_state = this->radiobutton_stave_processpoint_beforeTC_BT->GetState();
  AfterTC_BT_state = this->radiobutton_stave_processpoint_afterTC_BT->GetState();
  //CompRt_state = this->radiobutton_stave_compRT->GetState();
  //CompAll_state = this->radiobutton_stave_compAll->GetState();
  
  if(BeforeTC_AT_state == 1) comp_type = COMP_BEFORE_TC_AT;
  else if(BeforeTC_BT_state == 1) comp_type = COMP_BEFORE_TC_BT;
  else if(AfterTC_AT_state == 1) comp_type = COMP_AFTER_TC_AT;
  else if(AfterTC_BT_state == 1) comp_type = COMP_AFTER_TC_BT;
  else if(CompRt_state == 1) comp_type = COMP_RT;
  else if(CompAll_state == 1) comp_type = COMP_ALL_TC;
  else if(RT_state == 1) comp_type = RT;
  
  return comp_type;
}

ProcessPosition MainGui::GetSelectedSystemTypeStave(int comp_type)
{
  unsigned int BeforeTC_AT_state = 0;
  unsigned int AfterTC_AT_state = 0;
  unsigned int BeforeTC_BT_state = 0;
  unsigned int AfterTC_BT_state = 0;
  ProcessPosition system_type_stave = PP_StaveTestBeforeTC_BT;
  
  if(comp_type == COMP_BEFORE_TC_BT) system_type_stave = PP_StaveTestBeforeTC_BT;
  else if(comp_type == COMP_BEFORE_TC_AT) system_type_stave = PP_StaveTestBeforeTC_AT;
  else if(comp_type == COMP_AFTER_TC_BT) system_type_stave = PP_StaveTestAfterTC_BT;
  else if(comp_type == COMP_AFTER_TC_AT) system_type_stave = PP_StaveTestAfterTC_AT;
  else if(comp_type == RT) system_type_stave = PP_UsbPixReceptionTest;
  else system_type_stave = PP_StaveTestAfterTC_AT; 
  
  return system_type_stave;
}

ProcessPosition MainGui::GetSelectedSystemTypeStave()
{
  unsigned int BeforeTC_BT_state = 0;
  unsigned int AfterTC_BT_state = 0;
  unsigned int BeforeTC_AT_state = 0;
  unsigned int AfterTC_AT_state = 0;
  unsigned int RT_state = 0;

  ProcessPosition system_type_stave = PP_StaveTestBeforeTC_BT;
  BeforeTC_BT_state = this->radiobutton_stave_processpoint_beforeTC_BT->GetState();
  BeforeTC_AT_state = this->radiobutton_stave_processpoint_beforeTC_AT->GetState();
  AfterTC_BT_state = this->radiobutton_stave_processpoint_afterTC_BT->GetState();
  AfterTC_AT_state = this->radiobutton_stave_processpoint_afterTC_AT->GetState();
//  RT_state = this->radiobutton_stave_processpoint_RT->GetState();

  if(BeforeTC_BT_state == 1) system_type_stave = PP_StaveTestBeforeTC_BT;
  else if(BeforeTC_AT_state == 1) system_type_stave = PP_StaveTestBeforeTC_AT;
  else if(AfterTC_BT_state == 1) system_type_stave = PP_StaveTestAfterTC_BT;
  else if(AfterTC_AT_state == 1) system_type_stave = PP_StaveTestAfterTC_AT;
  else if(RT_state == 1) system_type_stave = PP_UsbPixReceptionTest;
  else system_type_stave = PP_StaveTestAfterTC_AT;

  
  return system_type_stave;
}


unsigned int MainGui::GetSelectedHVTypeTh()
{
  unsigned int hv_state = 0;
  unsigned int hvon_state = 0;
  unsigned int hvoff_state = 0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  hvon_state = this->radiobutton_hvon_th->GetState();
  hvoff_state = this->radiobutton_hvoff_th->GetState();
  
  if(hvoff_state == 1) hv_state = 0; //for HVoff
  else if(hvon_state == 1) hv_state = 1; // for HVon
  
  //std::cout << "HV type for TH: " << hv_state << std::endl;
  
  return hv_state;
}


void MainGui::EnableStaveProcessPointRadioButtons()
{
  std::string staveid = GetStaveId();
  //std::string staveid =	"1";

  int enubeforeTC_AT = 0;
  int enuafterTC_AT = 0;
  int enubeforeTC_BT = 0;
  int enuafterTC_BT = 0;
  int enuRt = 0;
  int enucompRt = 0;
  int enucompAll = 0;
  int withHV=0;
  int withoutHV=0;
  
  if (staveid != ""){
    std::vector<ProcessPosition> pps;
    /*    
	  for (std::vector<ProcessPosition>::iterator i = pps.begin(); i != pps.end(); i++){
	  std::cerr << __FILE__ << ":" << __LINE__ << " " <<  ((int)(*i)) << std::endl << std::flush;
	  enubeforeTC = enubeforeTC || ((*i) == PP_StaveTestBeforeTC);
	  enuafterTC = enuafterTC || ((*i) == PP_StaveTestAfterTC);
	  }*/
    enubeforeTC_BT = 1;
    enuafterTC_BT = 1;
    enubeforeTC_AT = 1;
    enuafterTC_AT = 1;
    enuRt =1;

    enucompRt = 1;
    enucompAll = 1;
    withHV=1;
    withoutHV=1;
  }
  
  radiobutton_hvon_th->SetEnabled(withHV);
  radiobutton_hvoff_th->SetEnabled(withoutHV);
  
  radiobutton_stave_processpoint_beforeTC_AT->SetEnabled(enubeforeTC_AT);
  radiobutton_stave_processpoint_afterTC_AT->SetEnabled(enuafterTC_AT);
  radiobutton_stave_processpoint_beforeTC_BT->SetEnabled(enubeforeTC_BT);
  radiobutton_stave_processpoint_afterTC_BT->SetEnabled(enuafterTC_BT);
//  radiobutton_stave_processpoint_RT->SetEnabled(enuRt);


//  radiobutton_stave_compRT->SetEnabled(enucompRt);
//  radiobutton_stave_compAll->SetEnabled(enucompAll);
}

std::string MainGui::GetSelectedModule()
{
  unsigned int module_list_index = 0;
	
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  module_list_index = this->moduleComboBox->GetSelected()-2;
  
  if (module_list_index < this->modules.size()){
    return this->modules.at(module_list_index);
  }else{
    return "";
  }
}

std::string MainGui::GetSelectedModule2()
{
  unsigned int module_list_index = 0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  module_list_index = this->moduleComboBox2->GetSelected()-2;
  
  if (module_list_index < this->modules.size()){
    return this->modules.at(module_list_index);
  }else{
    return "";
  }
}

std::string MainGui::GetSelectedStaveModule()
{
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  int module_list_index = this->stave_moduleComboBox->GetSelected()-2;
  m_stave_module_id =  module_list_index;

  if (module_list_index >=0 && module_list_index < this->stave_modules.size()){
    return this->stave_modules.at(module_list_index);
  }else{
    return "All";
  }
}

unsigned int MainGui::GetSelectedChip()
{
  unsigned int chip_index_0 = 0;
  unsigned int chip_index_1 =0;
  unsigned int chip=0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  chip_index_0 = this->radiobutton_module_chip_0->GetState();
  chip_index_1 = this->radiobutton_module_chip_1->GetState();
  
  if(chip_index_0 == 1) chip = 0; 
  else if(chip_index_1 == 1) chip = 1; 
  
  //  std::cout << "chip type: " << chip << std::endl;
  
  return chip;
}

unsigned int MainGui::GetSelectedChipB()
{
  unsigned int chip_index_0_B = 0;
  unsigned int chip_index_1_B =0;
  unsigned int chip_B=0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  chip_index_0_B = this->radiobutton_module_chip_0_B->GetState();
  chip_index_1_B = this->radiobutton_module_chip_1_B->GetState();
  
  if(chip_index_0_B == 1) chip_B = 0;
  else if(chip_index_1_B == 1) chip_B = 1;
  
  //  std::cout << "chip type: " << chip_B << std::endl;
  return chip_B;
}

ProcessPosition MainGui::GetSelectedSystemType()
{
  unsigned int usbpix_state = 0;
  //unsigned int usbpix_state_2 = 0;
  unsigned int rce_state = 0;
  ProcessPosition system_type = PP_RCEReceptionTest;
  
  //	unsigned int rce_state_2 = 0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  usbpix_state = this->radiobutton_module_processpoint_usbpix->GetState();
  rce_state = this->radiobutton_module_processpoint_rce->GetState();
  
  if(usbpix_state == 1) system_type = PP_UsbPixReceptionTest; //for usbpix
  else if(rce_state == 1) system_type = PP_RCEReceptionTest; // for rce
  
  return system_type;
}

ProcessPosition MainGui::GetSelectedSystemTypeB()
{
  unsigned int usbpix_state = 0;
  unsigned int rce_state = 0;
  ProcessPosition system_type = PP_RCEReceptionTest;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  usbpix_state = this->radiobutton_module_processpoint_usbpix_->GetState();
  rce_state = this->radiobutton_module_processpoint_rce_->GetState();
  
  if(usbpix_state == 1) system_type = PP_UsbPixReceptionTest; //for usbpix
  else if(rce_state == 1) system_type = PP_RCEReceptionTest; // for rce
  
  return system_type;
}

unsigned int MainGui::GetSelectedHVType()
{
  unsigned int hv_state = 0;
  unsigned int hvon_state = 0;
  unsigned int hvoff_state = 0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  hvon_state = this->radiobutton_hvon->GetState();
  hvoff_state = this->radiobutton_hvoff->GetState();
  
  if(hvoff_state == 1) hv_state = 0; //for HVoff
  else if(hvon_state == 1) hv_state = 1; // for HVon
  
  //  std::cout << "HV type: " << hv_state << std::endl;
  
  return hv_state;
}

unsigned int MainGui::GetSelectedHVTypeB()
{
  int hv_state = -1;
	
  unsigned int hvon_state = 0;
  unsigned int hvoff_state = 0;
  
  // The module index is -2 + the index of the selected combo box entry
  // as there are two non-module entries on top.
  hvon_state = this->radiobutton_hvon_B->GetState();
  hvoff_state = this->radiobutton_hvoff_B->GetState();
  
  if(hvoff_state == 1) hv_state = 0; //for HVoff
  else if(hvon_state == 1) hv_state = 1; // for HVon
  
  //  std::cout << "HV type for 2 module (-1 if no 2 module loaded): " << hv_state << std::endl;
  
  return hv_state;
}

void MainGui::PrintCanvas(){

  std::string module_id = "__"+GetSelectedModule();
  std::string module_id2 = "__"+GetSelectedModule2();

  std::string hv_status = "";
  std::string hv_status_2 = "";

  std::string systemtype = "";
  std::string systemtype2 = "";

  std::string chipnumber = "_0";
  std::string chipnumber2 = "_0";
	

  if(GetSelectedHVType()==0)
    hv_status="_hvOFF";
  else
    hv_status="_hvON";

  if(GetSelectedHVTypeB()==0)
    hv_status_2="_hvOFF";
  else
    hv_status_2="_hvON";

  if(GetSelectedSystemType()==PP_UsbPixReceptionTest)
    systemtype = "_USBpix-RT";
  else if(GetSelectedSystemType()==PP_RCEReceptionTest)
    systemtype = "_RCE-RT";
  
  if(GetSelectedSystemTypeB()==PP_UsbPixReceptionTest)
    systemtype2 = "_USBpix-RT";
  else if(GetSelectedSystemTypeB()==PP_RCEReceptionTest)
    systemtype2 = "_RCE-RT";
  
  if(GetSelectedChip()==0)
    chipnumber = "_0";
  else if(GetSelectedChip()==1)
    chipnumber = "_1";
  
  if(GetSelectedChipB()==0)
    chipnumber2 = "_0";
  else if(GetSelectedChip()==1)
    chipnumber2 = "_1";
  
  for (std::vector<TGCheckButton*>::iterator iii = module_analysis_checkbuttons.begin(); iii != module_analysis_checkbuttons.end(); iii++){
    std::string scanname((*iii)->GetText()->Data());
    if((*iii)->GetState() != 1)continue;
    else{
      std::string printstring;
      if(module_id2=="")
	printstring = "~/IBLdata/QAtemp/"+scanname+module_id+chipnumber+hv_status+systemtype+".png";
      else
	printstring = "~/IBLdata/QAtemp/"+scanname+module_id+chipnumber+hv_status+systemtype+module_id2+chipnumber2+hv_status_2+systemtype2+".png";
      
      char *printcharstring;
      
      printcharstring = new char [printstring.size()+1];
      strcpy (printcharstring, printstring.c_str());    
      
      module_canvas->SaveAs(printcharstring);
      std::cout<<"Image printed at:\t"<<printcharstring<<std::endl;   
    }
  }
}

void MainGui::DoStaveLoad()
{
  //from the buttom
  std::string staveid = GetStaveId();
  int comp_type = GetSelectedCompTypeStave();
  int HVstatus = GetSelectedHVTypeTh();
  Astave *stave_RT = new Astave();
  Astave *stave_beforeTC_AT = new Astave();
  Astave *stave_afterTC_AT = new Astave();
  Astave *stave_beforeTC_BT = new Astave();
  Astave *stave_afterTC_BT = new Astave();
  
  if(comp_type == COMP_BEFORE_TC_AT){
    ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
    if(stave_beforeTC_AT->mountmodules(staveid, asource, HVstatus) == -1){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }else if(comp_type == COMP_BEFORE_TC_BT){
    ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
    if(stave_beforeTC_BT->mountmodules(staveid, asource, HVstatus) == -1){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }else if(comp_type == COMP_AFTER_TC_AT){
    ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
    if(stave_afterTC_AT->mountmodules(staveid, asource, HVstatus) == -1){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }else if(comp_type == COMP_AFTER_TC_BT){
    ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
    if(stave_afterTC_BT->mountmodules(staveid, asource, HVstatus) == -1){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }else if(comp_type == COMP_RT){
    ProcessPosition asource = GetSelectedSystemTypeStave(COMP_RT);
    ProcessPosition asource2 = GetSelectedSystemTypeStave(COMP_BEFORE_TC_AT);
    if(stave_RT->mountmodules(staveid, asource, HVstatus) == -1 ||
       stave_beforeTC_AT->mountmodules(staveid, asource2, HVstatus) == -1 ){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }else if(comp_type == RT){
      ProcessPosition asource = GetSelectedSystemTypeStave(RT);
      if(stave_RT->mountmodules(staveid, asource, HVstatus) == -1){
          std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
          return;
      }
  }else if(comp_type == COMP_ALL_TC){
    ProcessPosition asource = GetSelectedSystemTypeStave(COMP_RT);
    ProcessPosition asource2 = GetSelectedSystemTypeStave(COMP_BEFORE_TC_AT);
    ProcessPosition asource3 = GetSelectedSystemTypeStave(COMP_AFTER_TC_AT);
    if(stave_RT->mountmodules(staveid, asource, HVstatus) == -1 ||
       stave_beforeTC_AT->mountmodules(staveid, asource2, HVstatus) == -1 ||
       stave_afterTC_AT->mountmodules(staveid, asource3, HVstatus) == -1 ){
      std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
      return; 
    }
  }

  for (std::vector<TGCheckButton*>::iterator iii = stave_analysis_checkbuttons.begin(); iii != stave_analysis_checkbuttons.end(); iii++){
    std::string scanname((*iii)->GetText()->Data());
    if((*iii)->GetState() != 1)continue;
    
    //std::cout << "Stave scan name: " << scanname << std::endl; 


    module_canvas_s->Clear();
    module_canvas_s->cd();
    if(m_enable_stave_module_comparison == 0){
      if (scanname == "Digital test"){
          Astave *stave_HV = new Astave();
          Astave *stave_NO_HV = new Astave();	  
          ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	
	  //ProcessPosition asource = PP_StaveTestAfterTC_AT;

          if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT ){
              int a = stave_HV->mountmodules(staveid, asource,1);
              int b = stave_NO_HV->mountmodules(staveid, asource,0);
              
              DigitalBad_Stave(stave_HV->GetModules(),stave_NO_HV->GetModules());
              
              
          }
	  else if(comp_type == COMP_RT){
	    int a = stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
	    int b = stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
	    Astave *stave2_HV = new Astave();
	    Astave *stave2_NO_HV = new Astave();
	    int c = stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
	    int d = stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);
	    
	    DigitalBad_Stave2(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule());
          }
	  else if(comp_type == RT){
	    stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
	    stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
	    DigitalBad_Stave(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule());
          }
	  else if(comp_type == COMP_ALL_TC){
	    int a = stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
	    int b = stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
	    Astave *stave2_HV = new Astave();
	    Astave *stave2_NO_HV = new Astave();
	    int c = stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
	    int d = stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);
	    Astave *stave3_HV = new Astave();
	    Astave *stave3_NO_HV = new Astave();
	    int e = stave3_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,1);
	    int f = stave3_NO_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,0);
	    
	    DigitalBad_Stave3(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule(),stave3_HV->StaveReaderModule(), stave3_NO_HV->StaveReaderModule());
          }
	  
      }
      else if (scanname == "Analog test"){
	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	//ProcessPosition asource = PP_StaveTestAfterTC_AT;
	
          if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT ){
	    int a = stave_HV->mountmodules(staveid, asource,1);
	    int b = stave_NO_HV->mountmodules(staveid, asource,0);
            
	    AnalogBad_Stave(stave_HV->GetModules(),stave_NO_HV->GetModules());
            
            
          }else if(comp_type == COMP_RT){ 
	    stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
	    stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
	    Astave *stave2_HV = new Astave();
	    Astave *stave2_NO_HV = new Astave();
	    stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
	    stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);
	    
	    AnalogBad_Stave2(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule());
          }else if(comp_type == RT){
              stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
              stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
              AnalogBad_Stave(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule());
          }
	  else if(comp_type == COMP_ALL_TC){
	    int a = stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
	    int b = stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
	    Astave *stave2_HV = new Astave();
	    Astave *stave2_NO_HV = new Astave();
	    int c = stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
	    int d = stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);
	    Astave *stave3_HV = new Astave();
	    Astave *stave3_NO_HV = new Astave();
	    int e = stave3_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,1);
	    int f = stave3_NO_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,0);
	    
	    
	    AnalogBad_Stave3(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule(),stave3_HV->StaveReaderModule(), stave3_NO_HV->StaveReaderModule());
          }
	  
      }else if (scanname == "Disconnected Bumps"){
          Astave *stave_HV = new Astave();
          Astave *stave_NO_HV = new Astave();
          ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
          //ProcessPosition asource = PP_StaveTestAfterTC_AT;

          if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT ){
              int a = stave_HV->mountmodules(staveid, asource,1);
              int b = stave_NO_HV->mountmodules(staveid, asource,0);
              
              DisconnectedStave(stave_HV->GetModules(),stave_NO_HV->GetModules());
              
              
          }else if(comp_type == COMP_RT){
              int a = stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
              int b = stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
              Astave *stave2_HV = new Astave();
              Astave *stave2_NO_HV = new Astave();
              int c = stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
              int d = stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);

              DisconnectedStave2(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule());
          }else if(comp_type == RT){
              stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
              stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
              DisconnectedStave(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule());
          }/*
	else if(comp_type == COMP_ALL_TC){
              int a = stave_HV->mountmodules(staveid, PP_UsbPixReceptionTest,1);
              int b = stave_NO_HV->mountmodules(staveid, PP_UsbPixReceptionTest,0);
              Astave *stave2_HV = new Astave();
              Astave *stave2_NO_HV = new Astave();
              int c = stave2_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,1);
              int d = stave2_NO_HV->mountmodules(staveid, PP_StaveTestBeforeTC_AT,0);
              Astave *stave3_HV = new Astave();
              Astave *stave3_NO_HV = new Astave();
              int e = stave3_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,1);
              int f = stave3_NO_HV->mountmodules(staveid, PP_StaveTestAfterTC_AT,0);


              AnalogBad_Stave3(stave_HV->StaveReaderModule(), stave_NO_HV->StaveReaderModule(),stave2_HV->StaveReaderModule(), stave2_NO_HV->StaveReaderModule(),stave3_HV->StaveReaderModule(), stave3_NO_HV->StaveReaderModule());
          }*/

      }else if(scanname == "BadDistribution" ){

	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);

	if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT  || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
          
	  BadDistribution(stave_HV->GetModules(),stave_NO_HV->GetModules());
	}
      }
      else if(scanname == "BadDistribution_disco" ){

	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);

	if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT  || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
          
	  BadDistribution_disco(stave_HV->GetModules(),stave_NO_HV->GetModules());
	}
      }
      else if(scanname == "BP_J" ){

	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);

	if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
          
	  BP_J(stave_HV->GetModules(),stave_NO_HV->GetModules());
	}
      }
      else if(scanname == "BP_J_disco" ){
	
	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	
	if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
          
	  BP_J_disco(stave_HV->GetModules(),stave_NO_HV->GetModules());
	}
      }
      
      else if(scanname == "Stave Table" ){
	
      ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
    	Astave *stave_HV = new Astave();
  	  stave_HV->mountmodules(staveid, asource,1);
      AvailableModulesSummaryTable(asource, stave_HV->GetModuleIdList(staveid));


      }else if (scanname == "ThresModMeanValue"){
          if(comp_type == COMP_BEFORE_TC_AT) ThresModMeanValue(stave_beforeTC_AT->StaveReaderModule());
          else if(comp_type == COMP_BEFORE_TC_BT) ThresModMeanValue(stave_beforeTC_BT->StaveReaderModule());
          else if(comp_type == COMP_AFTER_TC_AT) ThresModMeanValue(stave_afterTC_AT->StaveReaderModule());
          else if(comp_type == COMP_AFTER_TC_BT) ThresModMeanValue(stave_afterTC_BT->StaveReaderModule());
          else if(comp_type == COMP_RT) ThresModMeanValue(stave_RT->StaveReaderModule(), stave_beforeTC_AT->StaveReaderModule());
          else if(comp_type == COMP_ALL_TC) ThresModMeanValue(stave_RT->StaveReaderModule(), stave_beforeTC_AT->StaveReaderModule(), stave_afterTC_AT->StaveReaderModule());
          else if(comp_type == RT) ThresModMeanValue(stave_RT->StaveReaderModule());
          
      }
      else if (scanname == "SigmaModMeanValue"){
	if(comp_type == COMP_BEFORE_TC_AT) SigmaModMeanValue(stave_beforeTC_AT->StaveReaderModule());
	else if(comp_type == COMP_BEFORE_TC_BT) SigmaModMeanValue(stave_beforeTC_BT->StaveReaderModule());
	else if(comp_type == COMP_AFTER_TC_AT) SigmaModMeanValue(stave_afterTC_AT->StaveReaderModule());
	else if(comp_type == COMP_AFTER_TC_BT) SigmaModMeanValue(stave_afterTC_BT->StaveReaderModule());
  else if(comp_type == COMP_RT) SigmaModMeanValue(stave_RT->StaveReaderModule(), stave_beforeTC_AT->StaveReaderModule());
	else if(comp_type == COMP_ALL_TC) SigmaModMeanValue(stave_RT->StaveReaderModule(), stave_beforeTC_AT->StaveReaderModule(), stave_afterTC_AT->StaveReaderModule());
    else if(comp_type == RT) SigmaModMeanValue(stave_RT->StaveReaderModule());
      }else if(scanname == "Export_RT"){
	Astave *stave_HV = new Astave();
	Astave *stave_noHV = new Astave();

	ProcessPosition asource = GetSelectedSystemTypeStave(COMP_RT);
	if(stave_noHV->mountmodules(staveid, asource, 0) == -1 || stave_HV->mountmodules(staveid, asource, 1) == -1){
	  std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
	  return;
	}
	else{
	  stave_noHV->mountmodules(staveid, asource, 0);
	  stave_HV->mountmodules(staveid, asource, 1);

	  Sr1_converter_main(stave_HV,stave_noHV,asource);
	}
      }else if(scanname == "Export_AftTC"){
	Astave *stave_HV = new Astave();
	Astave *stave_noHV = new Astave();

	ProcessPosition asource = GetSelectedSystemTypeStave(COMP_AFTER_TC_AT);
	if(stave_noHV->mountmodules(staveid, asource, 0) == -1 || stave_HV->mountmodules(staveid, asource, 1) == -1){
	  std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
	  return;
	}
	else{
	  stave_noHV->mountmodules(staveid, asource, 0);
	  stave_HV->mountmodules(staveid, asource, 1);

	  Sr1_converter_main(stave_HV,stave_noHV,asource);
	}
      }else if(scanname == "Export_BefTC"){
	Astave *stave_HV = new Astave();
	Astave *stave_noHV = new Astave();

	ProcessPosition asource = GetSelectedSystemTypeStave(COMP_BEFORE_TC_AT);
	if(stave_noHV->mountmodules(staveid, asource, 0) == -1 || stave_HV->mountmodules(staveid, asource, 1) == -1){
	  std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
	  return;
	}
	else{
	  stave_noHV->mountmodules(staveid, asource, 0);
	  stave_HV->mountmodules(staveid, asource, 1);

	  Sr1_converter_main(stave_HV,stave_noHV,asource);
	}
      }else if(scanname == "Export_AftTC_BefTun"){
          Astave *stave_HV = new Astave();
          Astave *stave_noHV = new Astave();
          
          ProcessPosition asource = GetSelectedSystemTypeStave(COMP_AFTER_TC_BT);
          if(stave_noHV->mountmodules(staveid, asource, 0) == -1 || stave_HV->mountmodules(staveid, asource, 1) == -1){
              std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
              return;
          }
          else{
              stave_noHV->mountmodules(staveid, asource, 0);
              stave_HV->mountmodules(staveid, asource, 1);
              
              Sr1_converter_main(stave_HV,stave_noHV,asource);
          }
      }
      else if(scanname == "IV stave"){
	
	if(comp_type == COMP_BEFORE_TC_AT){

	  Astave *aStave_bTC = new Astave();
	  ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	  aStave_bTC->mountmodules(staveid,asource,HVstatus);
          module_canvas_s->Clear();
	  module_canvas_s->Divide(2,1);
	  module_canvas_s->cd(1);
	  IV_3D(aStave_bTC,staveid,asource);
	  module_canvas_s->cd(2);
	  IV_Planar(aStave_bTC,staveid,asource);
	}
	else if(comp_type == COMP_AFTER_TC_AT){
	  Astave *aStave_aTC = new Astave();
	  ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	  aStave_aTC->mountmodules(staveid,asource,HVstatus);
	  module_canvas_s->Clear();
	  module_canvas_s->Divide(2,1);
	  module_canvas_s->cd(1);
	  IV_3D(aStave_aTC,staveid,asource);
	  module_canvas_s->cd(2);
	  IV_Planar(aStave_aTC,staveid,asource);
	}
  else if(comp_type == COMP_BEFORE_TC_BT){

	  Astave *aStave_bTC = new Astave();
	  ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	  aStave_bTC->mountmodules(staveid,asource,HVstatus);
          module_canvas_s->Clear();
	  module_canvas_s->Divide(2,1);
	  module_canvas_s->cd(1);
	  IV_3D(aStave_bTC,staveid,asource);
	  module_canvas_s->cd(2);
	  IV_Planar(aStave_bTC,staveid,asource);
	}
	else if(comp_type == COMP_AFTER_TC_BT){
	  Astave *aStave_aTC = new Astave();
	  ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	  aStave_aTC->mountmodules(staveid,asource,HVstatus);
	  module_canvas_s->Clear();
	  module_canvas_s->Divide(2,1);
	  module_canvas_s->cd(1);
	  IV_3D(aStave_aTC,staveid,asource);
	  module_canvas_s->cd(2);
	  IV_Planar(aStave_aTC,staveid,asource);
	}
      }
    
    }
    else
      {
	if (scanname == "Digital test"){
	  if(comp_type == COMP_BEFORE_TC_AT){
      std::cout<<"DIGI DIGI DIGI\n";
	    DigitalOccupancy(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    DigitalOccupancy(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_AT){
	    DigitalOccupancy(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_BT){
	    DigitalOccupancy(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT)
	    {
	      //	      stave_RT->mountmodules(staveid,PP_UsbPixReceptionTest,HVstatus);
	      DigitalOccupancy(stave_RT->StaveReaderModule().at(m_stave_module_id));
	    }
	  else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); DigitalOccupancy((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); DigitalOccupancy((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
      module_canvas_s->cd(3); DigiCorrelationPlotModules((stave_RT->StaveReaderModule()).at(m_stave_module_id),(stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(2,2);
	    module_canvas_s->cd(1); DigitalOccupancy((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); DigitalOccupancy((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); DigitalOccupancy((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
      module_canvas_s->cd(4); DigiCorrelationPlotModules((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id),(stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }
}else if(scanname == "BadDistribution"){
 	Astave *stave_HV = new Astave();
	Astave *stave_NO_HV = new Astave();
	ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);

if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT  || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
          
	  BadDistribution_Module((stave_HV->StaveReaderModule()).at(m_stave_module_id),(stave_NO_HV->StaveReaderModule()).at(m_stave_module_id));
	}

	

}/*else if (scanname == "CorrelationPlot"){
	    Astave *stave_before = new Astave();
    	Astave *stave_after = new Astave();
	if(stave_before->mountmodules(staveid, PP_StaveTestBeforeTC_AT, 1) == -1 || stave_after->mountmodules(staveid, PP_StaveTestAfterTC_AT, 1) == -1){
	  std::cout << "Error in MainGui::LoadStave no module data!" << std::endl;
	  return;
	}
	else{
	  stave_before->mountmodules(staveid, PP_StaveTestBeforeTC_AT, 1);
	  stave_after->mountmodules(staveid, PP_StaveTestAfterTC_AT, 1);
    HistoReader* before = stave_before->StaveReaderModule().at(m_stave_module_id);
    HistoReader* after = stave_after->StaveReaderModule().at(m_stave_module_id);
	  DigiCorrelationPlotModules(before,after);
}
	    
	}*/else if(scanname == "Disconnected Bumps"){

	  Astave *stave_HV = new Astave();
	  Astave *stave_NO_HV = new Astave();
	  ProcessPosition asource = GetSelectedSystemTypeStave(comp_type);
	  
	  if(comp_type == COMP_BEFORE_TC_AT || comp_type == COMP_BEFORE_TC_BT || comp_type == COMP_AFTER_TC_AT || comp_type == COMP_AFTER_TC_BT  || comp_type == RT){
	  stave_HV->mountmodules(staveid, asource,1);
	  stave_NO_HV->mountmodules(staveid, asource,0);
	  } 
	  if(comp_type == COMP_BEFORE_TC_AT){
	    ThresholdDisconnectedBumps(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    ThresholdDisconnectedBumps(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT){
	 //   std::cout<<"GENOVA DISCONNECTED"<<std::endl;
	   // ThresholdDisconnectedBumps_2(stave_NO_HV->StaveReaderModule().at(m_stave_module_id),stave_HV->StaveReaderModule().at(m_stave_module_id));
	    ThresholdDisconnectedBumps((stave_RT->StaveReaderModule()).at(m_stave_module_id));
    }else if(comp_type == COMP_AFTER_TC_AT){
      ThresholdDisconnectedBumps(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
    }else if(comp_type == COMP_AFTER_TC_BT){
      ThresholdDisconnectedBumps(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); ThresholdDisconnectedBumps((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); ThresholdDisconnectedBumps((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
      
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); ThresholdDisconnectedBumps((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); ThresholdDisconnectedBumps((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); ThresholdDisconnectedBumps((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
      
	  }
  }else if(scanname == "Analog test"){
	  if(comp_type == COMP_BEFORE_TC_AT){
	    AnalOccupancy(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    AnalOccupancy(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_AT){
	    AnalOccupancy(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_BT){
	    AnalOccupancy(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT){
          AnalOccupancy((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); AnalOccupancy((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); AnalOccupancy((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
      module_canvas_s->cd(3); AnalCorrelationPlotModules((stave_RT->StaveReaderModule()).at(m_stave_module_id),(stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(2,2);
	    module_canvas_s->cd(1); AnalOccupancy((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); AnalOccupancy((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); AnalOccupancy((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
      module_canvas_s->cd(4); AnalCorrelationPlotModules((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id),(stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }
	}else if(scanname == "ThresModMeanValue"){
	  if(comp_type == COMP_BEFORE_TC_AT){
	    Threshold_thres_dist(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    Threshold_thres_dist(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_AT){
	    Threshold_thres_dist(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_BT){
	    Threshold_thres_dist(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT){
          Threshold_thres_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(2,1);
	    module_canvas_s->cd(1); Threshold_thres_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Threshold_thres_dist((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); Threshold_thres_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Threshold_thres_dist((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); Threshold_thres_dist((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }
	}else if(scanname == "Thresh_2D"){
          if(comp_type == COMP_BEFORE_TC_AT){
	    Thres2d(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_BEFORE_TC_BT){
	    Thres2d(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == RT){
              Thres2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
          }else if(comp_type == COMP_AFTER_TC_AT){
	    Thres2d(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_AFTER_TC_BT){
	    Thres2d(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(2,1);
	    module_canvas_s->cd(1); Thres2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Thres2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
          }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); Thres2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Thres2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); Thres2d((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
          }
	}
	else if (scanname == "SigmaModMeanValue"){
	  if(comp_type == COMP_BEFORE_TC_AT){
	    Threshold_sigma_dist(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    Threshold_sigma_dist(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT){
          Threshold_sigma_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_AT){
	    Threshold_sigma_dist(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_BT){
	    Threshold_sigma_dist(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(2,1);
	    module_canvas_s->cd(1); Threshold_sigma_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Threshold_sigma_dist((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); Threshold_sigma_dist((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); Threshold_sigma_dist((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); Threshold_sigma_dist((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }
	}else if (scanname == "Sigma_2D"){
          if(comp_type == COMP_BEFORE_TC_AT){
	    ThresholdSigma2d(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_BEFORE_TC_BT){
	    ThresholdSigma2d(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == RT){
           ThresholdSigma2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
          }else if(comp_type == COMP_AFTER_TC_AT){
	    ThresholdSigma2d(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_AFTER_TC_BT){
	    ThresholdSigma2d(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
          }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(2,1);
	    module_canvas_s->cd(1); ThresholdSigma2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); ThresholdSigma2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
          }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); ThresholdSigma2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); ThresholdSigma2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); ThresholdSigma2d((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
          }
	}else if(scanname == "IV stave"){
      int sector;

      if(m_stave_module_id >= 0 && m_stave_module_id <= 3) sector = M4A;
      else if(m_stave_module_id >= 4 && m_stave_module_id <= 7) sector = M3A;
      else if(m_stave_module_id >= 8 && m_stave_module_id <= 11) sector = M2A;
      else if(m_stave_module_id >= 12 && m_stave_module_id <= 15) sector = M1A;
      else if(m_stave_module_id >= 16 && m_stave_module_id <= 19) sector = M1C;
      else if(m_stave_module_id >= 20 && m_stave_module_id <= 23) sector = M2C;
      else if(m_stave_module_id >= 24 && m_stave_module_id <= 27) sector = M3C;
      else if(m_stave_module_id >= 28 && m_stave_module_id <= 31) sector = M4C;

      IV_sector(sector, stave_beforeTC_BT,stave_afterTC_BT);


  }
	else if(scanname == "Cross-talk"){

	  if(comp_type == COMP_BEFORE_TC_AT){
	    CrossTalk2d(stave_beforeTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_BEFORE_TC_BT){
	    CrossTalk2d(stave_beforeTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == RT){
         CrossTalk2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_AT){
	    CrossTalk2d(stave_afterTC_AT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_AFTER_TC_BT){
	    CrossTalk2d(stave_afterTC_BT->StaveReaderModule().at(m_stave_module_id));
	  }else if(comp_type == COMP_RT){
	    module_canvas_s->Divide(2,1);
	    module_canvas_s->cd(1); CrossTalk2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); CrossTalk2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }else if(comp_type == COMP_ALL_TC){
	    module_canvas_s->Divide(3,1);
	    module_canvas_s->cd(1); CrossTalk2d((stave_RT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(2); CrossTalk2d((stave_beforeTC_AT->StaveReaderModule()).at(m_stave_module_id));
	    module_canvas_s->cd(3); CrossTalk2d((stave_afterTC_AT->StaveReaderModule()).at(m_stave_module_id));
	  }
	}
      }
  }
  
  module_canvas_s->Update();

  delete stave_RT;
  delete stave_beforeTC_AT;
  delete stave_afterTC_AT;
  delete stave_beforeTC_BT;
  delete stave_afterTC_BT;
}


void MainGui::DoModuleLoad()
{
  HistoReader* hr;
  HistoReader* hr2;
  std::string module_id;
  std::string module_id_2;
  const int chipnumber= GetSelectedChip();
  const int chipnumberB = GetSelectedChipB();
  
  module_id = GetSelectedModule();
  module_id_2 = GetSelectedModule2();
  
  ProcessPosition system_type = GetSelectedSystemType();
  ProcessPosition system_type_B = GetSelectedSystemTypeB();
  unsigned int hv_type = GetSelectedHVType();
  unsigned int hv_type_B = GetSelectedHVTypeB();
  
  if (module_id == ""){
    std::cerr << "No module selected." << std::endl << std::flush;
    new TGMsgBox(gClient->GetRoot(), mainFrame, "No Module Selected", "You did not select a module before pressing the \"load\" button.", 0, kMBDismiss, 0, kVerticalFrame, kTextCenterX|kTextCenterY);
  }else{
    std::cerr << "Loading Module Data: " << module_id << std::endl << std::flush;
    //hr
    hr = new HistoReader(module_id.c_str(),system_type,chipnumber,hv_type);
    this->moduleHistoReader = hr;
    std::string fail_histo = hr->Demonstrate();
    if(module_id_2 == ""){ std::cout << "Only one module selected " << std::endl; 
    }else {
      std::cerr << "Loading Module Data 2: " << module_id_2 << std::endl << std::flush;
      hr2 = new HistoReader(module_id_2.c_str(), system_type_B, chipnumberB,hv_type_B);
      this->moduleHistoReader = hr2;
      std::string fail_histo2 = hr2->Demonstrate();
    }
    
    module_canvas->cd();
    for (std::vector<TGCheckButton*>::iterator iii = module_analysis_checkbuttons.begin(); iii != module_analysis_checkbuttons.end(); iii++){
      std::string scanname((*iii)->GetText()->Data());

      if((*iii)->GetState() != 1)continue;
      else if (scanname == "Threshold 2d"){
      	if(module_id_2=="") Thres2d(hr);
      	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  Thres2d(hr);
	  module_canvas->cd(2);
	  Thres2d(hr2);
	}
      }
      else if (scanname == "Threshold 2d Diff"){
	Thres2d_Diff(hr,hr2);
      }else if (scanname == "Threshold Dist"){
	if(module_id_2=="") Threshold_thres_dist(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  Threshold_thres_dist(hr);
	  module_canvas->cd(2);
	  Threshold_thres_dist(hr2);
	}
      }else if (scanname == "Threshold Sigma Dist"){
	if(module_id_2=="")Threshold_sigma_dist(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  Threshold_sigma_dist(hr);
	  module_canvas->cd(2);
	  Threshold_sigma_dist(hr2);
	}
      }else if (scanname == "Bad Pixel"){
        HistoReader *hr_, *hr_noHV;
        hr_ = new HistoReader(module_id.c_str(),GetSelectedSystemType(),chipnumber,1);      
        hr_noHV = new HistoReader(module_id.c_str(),GetSelectedSystemType(),chipnumber,0);  
  if(module_id_2=="") BadPixelsMap(hr,hr_noHV);
	else{
    HistoReader *hr_2, *hr_noHV2;
    hr_2 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,1);      
    hr_noHV2 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,0); 
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  BadPixelsMap(hr_,hr_noHV);
	  module_canvas->cd(2);
	  BadPixelsMap(hr_2,hr_noHV2);
	}
      }else if (scanname == "Anal Occupancy"){
	if(module_id_2=="") AnalOccupancy(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  AnalOccupancy(hr);
	  module_canvas->cd(2);
	  AnalOccupancy(hr2);
	}
      }else if (scanname == "Digital Occupancy"){
	if(module_id_2=="") DigitalOccupancy(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  DigitalOccupancy(hr);
	  module_canvas->cd(2);
	  DigitalOccupancy(hr2);
	}
      }else if (scanname == "Cross Talk 2d"){
	if(module_id_2=="") CrossTalk2d(hr);
        else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  CrossTalk2d(hr);
	  module_canvas->cd(2);
	  CrossTalk2d(hr2);
        }
      }else if (scanname == "Cross Talk Dist"){
	if(module_id_2=="") CrossTalkdist(hr);
        else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  CrossTalkdist(hr);
	  module_canvas->cd(2);
	  CrossTalkdist(hr2);
        }
      }else if(scanname == "Disconnected Bumps"){
  HistoReader* hr_noHV = new HistoReader(module_id.c_str(),GetSelectedSystemType(),chipnumber,0);
	if(module_id_2==""){
    
    ThresholdDisconnectedBumps(hr_noHV);
  }
	else{
    HistoReader* hr_noHV2 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,0);
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  ThresholdDisconnectedBumps(hr_noHV);
	  module_canvas->cd(2);
	  ThresholdDisconnectedBumps(hr_noHV2);
	}
      }else if(scanname == "Noise Greater Gaussian"){
	if(module_id_2=="") NoiseGreaterThanGaussian(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  NoiseGreaterThanGaussian(hr);
	  module_canvas->cd(2);
	  NoiseGreaterThanGaussian(hr2);
	}
      }else if(scanname == "Digital and Analog bad history"){
        HistoReader *hrUSBpix, *hrRCE_rt, *hrRCE_BefThCycle, *hrRCE_AftThCycle;
        hrUSBpix = new HistoReader(module_id.c_str(),PP_UsbPixReceptionTest,chipnumber,hv_type);      
        hrRCE_rt = new HistoReader(module_id.c_str(),PP_RCEReceptionTest,chipnumber,hv_type);
        hrRCE_BefThCycle = new HistoReader(module_id.c_str(),PP_StaveTestBeforeTC_AT,chipnumber,hv_type);      
        hrRCE_AftThCycle = new HistoReader(module_id.c_str(),PP_StaveTestAfterTC_AT,chipnumber,hv_type);
        if(module_id_2=="") DigitalAnalogDeadHistory(hrUSBpix, hrRCE_rt, hrRCE_BefThCycle, hrRCE_AftThCycle);
        else{
	  HistoReader *hrUSBpix_2, *hrRCE_rt_2, *hrRCE_BefThCycle_2, *hrRCE_AftThCycle_2;
	  hrUSBpix_2 = new HistoReader(module_id_2.c_str(), PP_UsbPixReceptionTest, chipnumberB,hv_type_B);      
	  hrRCE_rt_2 = new HistoReader(module_id_2.c_str(), PP_RCEReceptionTest, chipnumberB,hv_type_B);
	  hrRCE_BefThCycle_2 = new HistoReader(module_id_2.c_str(),PP_StaveTestBeforeTC_AT,chipnumberB,hv_type_B);      
	  hrRCE_AftThCycle_2 = new HistoReader(module_id_2.c_str(),PP_StaveTestAfterTC_AT,chipnumberB,hv_type_B);
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  DigitalAnalogDeadHistory(hrUSBpix, hrRCE_rt, hrRCE_BefThCycle, hrRCE_AftThCycle);
	  module_canvas->cd(2);
	  DigitalAnalogDeadHistory(hrUSBpix_2, hrRCE_rt_2, hrRCE_BefThCycle_2, hrRCE_AftThCycle_2);
        }  

      
      }else if(scanname == "Bad Pixel Distribution"){
        HistoReader *hr_, *hr_noHV;
        hr_ = new HistoReader(module_id.c_str(),GetSelectedSystemType(),chipnumber,1);      
        hr_noHV = new HistoReader(module_id.c_str(),GetSelectedSystemType(),chipnumber,0);
        if(module_id_2=="") BadDistribution_Module(hr_,hr_noHV);
        else{
	  HistoReader *hr_2, *hr_noHV2;
        hr_2 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,1);      
        hr_noHV2 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,0);
        module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  BadDistribution_Module(hr_,hr_noHV);
	  module_canvas->cd(2);
	  BadDistribution_Module(hr_2,hr_noHV2);
        }  

      
      }else if(scanname == "Analog Diff"){
        module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
  	AnalDiff(hr,hr2);
    module_canvas->cd(2);
    
    HistoReader *hr3 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,hv_type_B);

    AnalCorrelationPlotModules(hr, hr3);
      }else if(scanname == "Digital Diff"){
	     module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
  	DigiDiff(hr,hr2);
    module_canvas->cd(2);
    
    HistoReader *hr3 = new HistoReader(module_id_2.c_str(),GetSelectedSystemTypeB(),chipnumberB,hv_type_B);
    DigiCorrelationPlotModules(hr, hr3);
    
  }	else if(scanname == "Thresh Diff"){
	Threshold_thres_dist_diff(hr,hr2);
      }else if(scanname == "Thresh Sigma Diff"){
	Threshold_sigma_dist_diff(hr,hr2);
      }else if(scanname== "Thresh Sigma 2d"){
	if(module_id_2=="") ThresholdSigma2d(hr);
	else{
	  module_canvas->Clear();
	  module_canvas->Divide(2,1);
	  module_canvas->cd(1);
	  ThresholdSigma2d(hr);
	  module_canvas->cd(2);
	  ThresholdSigma2d(hr2);
	}
  
      }else if(scanname=="Summary Plot"){

	SummaryPlot(GetSelectedSystemType(), this->modules_complete);
//  TGMainFrame* frame = AvailableModulesSummaryTable(GetSelectedSystemType(), this->modules);

      }else if(scanname=="Summary Table"){
      TGMainFrame* frame = AvailableModulesSummaryTable(GetSelectedSystemType(), this->modules);


      }else if(scanname=="IV curve"){
  /*if(module_id.c_str() == "D92-09-03"){
    std::cout<<"ECCOMI ECCOMI ECCOMI"<<std::endl;
    IV_all_modules(PP_UsbPixReceptionTest, this->modules_complete);
  }
  else{*/

	HistoReader* hr_IV = new HistoReader(module_id.c_str(),system_type,0,0); // FE OFF
	HistoReader* hr2_IV = new HistoReader(module_id.c_str(),system_type,0,1); // FE ON
	
	module_canvas->Clear();
	module_canvas->Divide(2,1);
	module_canvas->cd(1);
	IV_Mod(hr_IV,hr2_IV);
	module_canvas->cd(2);
	IV_Mod_Norm(hr_IV,hr2_IV);
      //}     
    }else if(scanname=="IV for disponsable modules"){
    IV_all_modules(PP_UsbPixReceptionTest, this->modules);
    module_canvas->SetGridx();
    module_canvas->SetGridy();
    }else if(scanname=="IV for all modules"){
    IV_all_modules(PP_UsbPixReceptionTest, this->modules_complete);
    module_canvas->SetGridx();
    module_canvas->SetGridy();
    }
    module_canvas->Update();
  }
 }
}

void MainGui::InitializeGui()
{
  // main frame
  TGMainFrame *mainFrame = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
  mainFrame->SetName("mainFrame");
  TGTab *fTab670 = new TGTab(mainFrame,865,605);
  
  //---- FRONT END PART
  // container of "RT USBpix&RCE"
/*  TGCompositeFrame *fCompositeFrame673;
  fCompositeFrame673 = fTab670->AddTab("Reception Test Analysis");
  fCompositeFrame673->SetLayoutManager(new TGVerticalLayout(fCompositeFrame673));
  
  // "Root Files" group frame
  TGGroupFrame *fGroupFrame687 = new TGGroupFrame(fCompositeFrame673,"Root Files",
						  kHorizontalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
  
  TGHorizontalFrame *hframe000 = new TGHorizontalFrame(fGroupFrame687);
  fGroupFrame687->AddFrame(hframe000, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
  
  this->moduleComboBox = new TGComboBox(hframe000,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
  this->moduleComboBox->SetName("moduleComboBox");
  FillModuleComboBox(this->moduleComboBox);
  this->moduleComboBox->Resize(200,22);
  this->moduleComboBox->Select(0);
  this->moduleComboBox->Connect("Selected(Int_t)", "MainGui", this, "DoModuleSelected(Int_t)");
  hframe000->AddFrame(this->moduleComboBox, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    
  TGButtonGroup *buttongroup000 = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_module_processpoint_usbpix = new TGRadioButton(buttongroup000,"USBPix", 1);
  radiobutton_module_processpoint_usbpix->SetTextJustify(36);
  radiobutton_module_processpoint_usbpix->SetMargins(0,0,0,0);
  radiobutton_module_processpoint_usbpix->SetWrapLength(-1);
  buttongroup000->AddFrame(radiobutton_module_processpoint_usbpix, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  radiobutton_module_processpoint_rce = new TGRadioButton(buttongroup000,"RCE", 1);
  radiobutton_module_processpoint_rce->SetTextJustify(36);
  radiobutton_module_processpoint_rce->SetMargins(0,0,0,0);
  radiobutton_module_processpoint_rce->SetWrapLength(-1);
  buttongroup000->AddFrame(radiobutton_module_processpoint_rce, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup000, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
  
  TGButtonGroup *buttongroup001 = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_module_chip_0 = new TGRadioButton(buttongroup001,"FE_0", 1);
  radiobutton_module_chip_0->SetTextJustify(36);
  radiobutton_module_chip_0->SetMargins(0,0,0,0);
  radiobutton_module_chip_0->SetWrapLength(-1);
  buttongroup001->AddFrame(radiobutton_module_chip_0, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  radiobutton_module_chip_1 = new TGRadioButton(buttongroup001,"FE_1", 1);
  radiobutton_module_chip_1->SetTextJustify(36);
  radiobutton_module_chip_1->SetMargins(0,0,0,0);
  radiobutton_module_chip_1->SetWrapLength(-1);
  buttongroup001->AddFrame(radiobutton_module_chip_1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup001, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
  
  TGButtonGroup *buttongroup002 = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_hvoff = new TGRadioButton(buttongroup002,"Without HV");
  radiobutton_hvoff->SetTextJustify(36);
  radiobutton_hvoff->SetMargins(0,0,0,0);
  radiobutton_hvoff->SetWrapLength(-1);
  buttongroup002->AddFrame(radiobutton_hvoff, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  radiobutton_hvon = new TGRadioButton(buttongroup002,"With HV");
  radiobutton_hvon->SetTextJustify(36);
  radiobutton_hvon->SetMargins(0,0,0,0);
  radiobutton_hvon->SetWrapLength(-1);
  buttongroup002->AddFrame(radiobutton_hvon, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup002, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
	
  //  BUTTONS FOR USBpix/RCE choise, MODULE 2
  this->moduleComboBox2 = new TGComboBox(hframe000,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
  this->moduleComboBox2->SetName("moduleComboBox2");
  FillModuleComboBox(this->moduleComboBox2);
  this->moduleComboBox2->Resize(200,22);
  this->moduleComboBox2->Select(0);
  this->moduleComboBox2->Connect("Selected(Int_t)", "MainGui", this, "DoModuleSelected(Int_t)");
  hframe000->AddFrame(this->moduleComboBox2, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  TGButtonGroup *buttongroup000_ = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_module_processpoint_usbpix_ = new TGRadioButton(buttongroup000_,"USBPix", 1);
  radiobutton_module_processpoint_usbpix_->SetTextJustify(36);
  radiobutton_module_processpoint_usbpix_->SetMargins(0,0,0,0);
  radiobutton_module_processpoint_usbpix_->SetWrapLength(-1);
  buttongroup000_->AddFrame(radiobutton_module_processpoint_usbpix_, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  radiobutton_module_processpoint_rce_ = new TGRadioButton(buttongroup000_,"RCE", 1);
  radiobutton_module_processpoint_rce_->SetTextJustify(36);
  radiobutton_module_processpoint_rce_->SetMargins(0,0,0,0);
  radiobutton_module_processpoint_rce_->SetWrapLength(-1);
  buttongroup000_->AddFrame(radiobutton_module_processpoint_rce_, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup000_, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
  
  TGButtonGroup *buttongroup001_ = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_module_chip_0_B = new TGRadioButton(buttongroup001_,"FE_0", 1);
  radiobutton_module_chip_0_B->SetTextJustify(36);
  radiobutton_module_chip_0_B->SetMargins(0,0,0,0);
  radiobutton_module_chip_0_B->SetWrapLength(-1);
  buttongroup001_->AddFrame(radiobutton_module_chip_0_B, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  radiobutton_module_chip_1_B = new TGRadioButton(buttongroup001_,"FE_1", 1);
  radiobutton_module_chip_1_B->SetTextJustify(36);
  radiobutton_module_chip_1_B->SetMargins(0,0,0,0);
  radiobutton_module_chip_1_B->SetWrapLength(-1);
  buttongroup001_->AddFrame(radiobutton_module_chip_1_B, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup001_, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
  
  TGButtonGroup *buttongroup002_ = new TGButtonGroup(hframe000, 2, 1);
  radiobutton_hvoff_B = new TGRadioButton(buttongroup002_,"Without HV");
  radiobutton_hvoff_B->SetTextJustify(36);
  radiobutton_hvoff_B->SetMargins(0,0,0,0);
  radiobutton_hvoff_B->SetWrapLength(-1);
  buttongroup002_->AddFrame(radiobutton_hvoff, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  
  radiobutton_hvon_B = new TGRadioButton(buttongroup002_,"With HV");
  radiobutton_hvon_B->SetTextJustify(36);
  radiobutton_hvon_B->SetMargins(0,0,0,0);
  radiobutton_hvon_B->SetWrapLength(-1);
  buttongroup002->AddFrame(radiobutton_hvon_B, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  hframe000->AddFrame(buttongroup002_, new TGLayoutHints(kLHintsTop | kLHintsTop, 2, 2, 2, 2));
	
  TGTextButton *button000 = new TGTextButton(hframe000, "load");
  hframe000->AddFrame(button000, new TGLayoutHints(kLHintsLeft| kLHintsTop,2,2,2,2));
  button000->Connect("Clicked()", "MainGui", this, "DoModuleLoad()");
	
  TGFont *ufont;         // will reflect user font changes
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");
	
  TGGC   *uGC;           // will reflect user GC changes
	
  fGroupFrame687->SetLayoutManager(new TGVerticalLayout(fGroupFrame687));
  fCompositeFrame673->AddFrame(fGroupFrame687, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
	
  // Horizontal frame for the sidebar and tcanvas
  TGHorizontalFrame *hframe003 = new TGHorizontalFrame(fCompositeFrame673);
  
  // "fGroupFrame891" group frame
  TGGroupFrame *fGroupFrame716 = new TGGroupFrame(hframe003,"Analysis Functions",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
  TGCheckButton *tb;
  
  tb = new TGCheckButton(fGroupFrame716, "Anal Occupancy");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Analog Diff");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Digital Occupancy");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Digital Diff");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Threshold Dist");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Threshold Sigma Dist");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Threshold 2d");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Thresh Diff");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Thresh Sigma 2d");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);	
  
  tb = new TGCheckButton(fGroupFrame716, "Thresh Sigma Diff");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Threshold 2d Diff");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Cross Talk 2d");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Cross Talk Dist");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Bad Pixel");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "Bad Pixel Distribution");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "Disconnected Bumps");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "Noise Greater Gaussian");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "Digital and Analog bad history");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "IV curve");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);
  
  tb = new TGCheckButton(fGroupFrame716, "IV for disponsable modules");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "IV for all modules");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "Summary Plot");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

  tb = new TGCheckButton(fGroupFrame716, "Summary Table");
  fGroupFrame716->AddFrame(tb, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  module_analysis_checkbuttons.push_back(tb);

    
  TGTextButton *button_print = new TGTextButton(fGroupFrame716, "Print Canvas");
  fGroupFrame716->AddFrame(button_print, new TGLayoutHints(kLHintsLeft| kLHintsTop,2,2,2,2));
  button_print->Connect("Clicked()", "MainGui", this, "PrintCanvas()");
  
  fGroupFrame716->SetLayoutManager(new TGVerticalLayout(fGroupFrame716));
  fGroupFrame716->Resize(184,449);
  hframe003->AddFrame(fGroupFrame716, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY,2,2,2,2));
  
  // embedded canvas
  TRootEmbeddedCanvas *fRootEmbeddedCanvas675 = new TRootEmbeddedCanvas(0,hframe003,660,444);
  Int_t wfRootEmbeddedCanvas675 = fRootEmbeddedCanvas675->GetCanvasWindowId();
  module_canvas = new TCanvas("module_canvas", 10, 10, wfRootEmbeddedCanvas675);
  module_canvas->cd();
  fRootEmbeddedCanvas675->AdoptCanvas(module_canvas);
  hframe003->AddFrame(fRootEmbeddedCanvas675, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY));
  fCompositeFrame673->AddFrame(hframe003, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));
*/
  //---- STAVE PART
  // container of "Stave Comp"
  TGCompositeFrame *fCompositeFrame743;
  fCompositeFrame743 = fTab670->AddTab("Stave Comparison");
  fCompositeFrame743->SetLayoutManager(new TGVerticalLayout(fCompositeFrame743));
  
  // "fGroupFrame811" group frame
  TGGroupFrame *fGroupFrame744 = new TGGroupFrame(fCompositeFrame743,"Root Files",
						  kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());
  fGroupFrame744->SetLayoutBroken(kTRUE);
  //fCompositeFrame743->Resize(450,780);
  //this->fNumberEntry747 = new TGNumberEntry(fGroupFrame744, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5,TGNumberFormat::kNEANonNegative);
  this->fNumberEntry747 = new TGNumberEntry(fGroupFrame744, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5,TGNumberFormat::kNEAAnyNumber, TGNumberFormat::kNELLimitMinMax, 0, 100);
  fGroupFrame744->AddFrame(this->fNumberEntry747, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  this->fNumberEntry747->Connect("ValueSet(Long_t)", "MainGui", this, "DoStaveSelected(Int_t)");
  //  (this->fNumberEntry747->GetNumberEntry())->Connect("ReturnPressed()", "MainGui", this, "DoStaveSelected(Int_t)");
  this->fNumberEntry747->MoveResize(36,45,59,22);

  LoadStaveModuleList();

  /*
    this->fNumberEntry751 = new TGNumberEntry(fGroupFrame744, (Double_t) 0,6,-1,(TGNumberFormat::EStyle) 5, TGNumberFormat::kNEANonNegative);
    fGroupFrame744->AddFrame(this->fNumberEntry751, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    this->fNumberEntry751->MoveResize(36,55,59,22);
  */
  TGFont *ufont;         // will reflect user font changes
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");
  
  // Selection of FEs on stave 
  this->stave_moduleComboBox = new TGComboBox(fGroupFrame744,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
  this->stave_moduleComboBox->SetName("stave_moduleComboBox");
  FillStaveModuleComboBox(this->stave_moduleComboBox);
  this->stave_moduleComboBox->MoveResize(120, 45, 113, 19);
  this->stave_moduleComboBox->Select(0);
  this->stave_moduleComboBox->Connect("Selected(Int_t)", "MainGui", this, "DoStaveModuleSelected(Int_t)");
  fGroupFrame744->AddFrame(this->stave_moduleComboBox, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

  // graphics context changes
  GCValues_t valEntry755;
  valEntry755.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
  gClient->GetColorByName("#000000",valEntry755.fForeground);
  gClient->GetColorByName("#e0e0e0",valEntry755.fBackground);
  valEntry755.fFillStyle = kFillSolid;
  valEntry755.fFont = ufont->GetFontHandle();
  valEntry755.fGraphicsExposures = kFALSE;
  TGGC   *uGC;           // will reflect user GC changes
  uGC = gClient->GetGC(&valEntry755, kTRUE);
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");
  
  // asource for stave
  TGButtonGroup *buttongroup001s = new TGButtonGroup(fGroupFrame744, 3, 2);
  buttongroup001s->MoveResize(270,5,113,29); 
//  radiobutton_stave_processpoint_RT = new TGRadioButton(buttongroup001s,"Reception Tests");
  radiobutton_stave_processpoint_beforeTC_BT = new TGRadioButton(buttongroup001s, "Bef TC, Bef Tun");
  radiobutton_stave_processpoint_afterTC_BT = new TGRadioButton(buttongroup001s,"Aft TC, Bef Tun");
  radiobutton_stave_processpoint_beforeTC_AT = new TGRadioButton(buttongroup001s, "Bef TC, Aft Tun");
  radiobutton_stave_processpoint_afterTC_AT = new TGRadioButton(buttongroup001s,"Aft TC, Aft Tun");
//  radiobutton_stave_compRT = new TGRadioButton(buttongroup001s,"RT v.s. Before TC");
//  radiobutton_stave_compAll= new TGRadioButton(buttongroup001s,"RT v.s. stave all");
  buttongroup001s->Show();

  // hv for stave
  TGButtonGroup *buttongroup002s = new TGButtonGroup(fGroupFrame744, 2, 1);
  buttongroup002s->MoveResize(550,5,113,19);
  radiobutton_hvoff_th = new TGRadioButton(buttongroup002s, "Without HV");
  radiobutton_hvon_th = new TGRadioButton(buttongroup002s, "With HV");
  buttongroup002s->Show();

  TGTextButton *button010 = new TGTextButton(fGroupFrame744, "load");
  fGroupFrame744->AddFrame(button010, new TGLayoutHints(kLHintsLeft| kLHintsTop,2,2,2,2));
  button010->Connect("Clicked()", "MainGui", this, "DoStaveLoad()");
  button010->MoveResize(650,35,113,19);

  // graphics context changes
  GCValues_t valEntry756;
  valEntry756.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
  gClient->GetColorByName("#000000",valEntry756.fForeground);
  gClient->GetColorByName("#e0e0e0",valEntry756.fBackground);
  valEntry756.fFillStyle = kFillSolid;
  valEntry756.fFont = ufont->GetFontHandle();
  valEntry756.fGraphicsExposures = kFALSE;
  uGC = gClient->GetGC(&valEntry756, kTRUE);
  
  fGroupFrame744->SetLayoutManager(new TGVerticalLayout(fGroupFrame744));
  fGroupFrame744->Resize(800,98);
  fCompositeFrame743->AddFrame(fGroupFrame744, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  
  // "fGroupFrame828" group frame
  TGHorizontalFrame *hframe004 = new TGHorizontalFrame(fCompositeFrame743);
  TGGroupFrame *fGroupFrame757 = new TGGroupFrame(hframe004,"Analysis functions",kVerticalFrame,TGGroupFrame::GetDefaultGC()(),TGGroupFrame::GetDefaultFontStruct());

  TGCheckButton *tbS;
  tbS = new TGCheckButton(fGroupFrame757, "Digital test");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "Analog test");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "ThresModMeanValue");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
  
  tbS = new TGCheckButton(fGroupFrame757, "Thresh_2D");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
    
  tbS = new TGCheckButton(fGroupFrame757, "SigmaModMeanValue");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
  
  tbS = new TGCheckButton(fGroupFrame757, "Sigma_2D");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
 
  tbS = new TGCheckButton(fGroupFrame757, "Disconnected Bumps");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);   
    
  tbS = new TGCheckButton(fGroupFrame757, "Cross-talk");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "IV stave");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
    
  tbS = new TGCheckButton(fGroupFrame757, "BP_J");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "BP_J_disco");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "BadDistribution");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "BadDistribution_disco");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);



//  tbS = new TGCheckButton(fGroupFrame757, "Stave Table");
//  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
//  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "Export_RT");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "Export_AftTC");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  tbS = new TGCheckButton(fGroupFrame757, "Export_BefTC");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);
  
  tbS = new TGCheckButton(fGroupFrame757, "Export_AftTC_BefTun");
  fGroupFrame757->AddFrame(tbS, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
  stave_analysis_checkbuttons.push_back(tbS);

  fGroupFrame757->SetLayoutManager(new TGVerticalLayout(fGroupFrame757));
  fGroupFrame757->Resize(184,449);
  hframe004->AddFrame(fGroupFrame757, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

  // canvas for stave
  TRootEmbeddedCanvas *fRootEmbeddedCanvas674 = new TRootEmbeddedCanvas(0,hframe004,660,444);
  Int_t wfRootEmbeddedCanvas674 = fRootEmbeddedCanvas674->GetCanvasWindowId();
  module_canvas_s = new TCanvas("module_canvas_s", 10, 10, wfRootEmbeddedCanvas674);
  module_canvas_s->cd();
  fRootEmbeddedCanvas674->AdoptCanvas(module_canvas_s);
  hframe004->AddFrame(fRootEmbeddedCanvas674, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY));
  
  fCompositeFrame743->AddFrame(hframe004, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));
  fTab670->SetTab(0);
  fTab670->Resize(fTab670->GetDefaultSize());
  mainFrame->AddFrame(fTab670, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,2,2,2,2));

  mainFrame->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
  mainFrame->MapSubwindows();
  mainFrame->Connect("CloseWindow()", "MainGui", this, "DoMainFrameClose()");
  mainFrame->Resize(mainFrame->GetDefaultSize());
  mainFrame->MapWindow();
  mainFrame->Resize(1200,700);
  
  //EnableModuleProcessPointRadioButtons();
  //EnableModuleProcessPointRadioButtons2();
  EnableStaveProcessPointRadioButtons();
}

void MainGui::DoMainFrameClose()
{
  delete this;
  exit(0);
}
/* vim:set shiftwidth=2 tabstop=2 expandtab: */
