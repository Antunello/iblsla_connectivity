////////////////////////////////////////////////////
// Class developed for Stave RT result comparison //
// Developed by: J. Agricola, A. Cervelli         //
// V 0.1 Jul 2012                                 //
////////////////////////////////////////////////////

//#define OLD_DIR_DEFINE
#include <HistoReader.hh>
#include <TString.h>
#include <TFile.h>
#include <string>
#include <sstream>
#include <DbTools.hh>
#include <ScanDef.hh>
#include <IVMeasurementPoint.hh>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <TF1.h>
//ClassImp(HistoReader);

// chipnumber must be 0 or 1 for the Planar, 0 for the 3D
HistoReader::HistoReader(const std::string moduleid,
			 const ProcessPosition asource,
			 const int chipnumber,
			 const int Hvstatus,
			 const int FEposition):
  Digi_Mask_Mod(NULL),
  Digi_FEI4_Errors_Proc(NULL),
  Digi_Occupancy_Point_000(NULL),
  Anal_Mask_Mod(NULL),
  Anal_FEI4_Errors_Proc(NULL),
  Anal_Occupancy_Point_000(NULL),
  Thre_thresh2d(NULL),
  Thre_thresh1d(NULL),
  Thre_threshdist(NULL),
  Thre_sigma1d(NULL),
  Thre_sigmadist(NULL),
  Thre_BadPixels(NULL),
  Thre_HitsPerBin(NULL),
  Thre_ChiSquare(NULL),
  Thre_FEI4_Errors_Proc(NULL),
  Thre_Iter(NULL),
  Thre_Mean(NULL),
  Thre_Sigma(NULL),
  Thre_Occupancy(NULL),
  Cros_thresh2d(NULL),
  Cros_thresh1d(NULL),
  Cros_threshdist(NULL),
  Cros_sigma1d(NULL),
  Cros_sigmadist(NULL),
  Cros_crosstalk2d(NULL),
  Cros_crosstalk1d(NULL),
  Cros_crosstalkdist(NULL),
  Cros_ChiSquare(NULL),
  Cros_FEI4_Errors_Proc(NULL),
  Cros_Iter(NULL),
  Cros_Mean(NULL),
  Cros_Sigma(NULL),
  Cros_Occupancy(NULL),
  IV_Mod_Graph(NULL)
  //IV(NULL)
{
  std::vector<ScanDef> scans;
  DbTools::GetInstance()->GetScanList(moduleid, chipnumber, scans);
  TString hn_str;
  //create string for histogram naming
  if(asource == PP_StaveTestBeforeTC_AT || asource == PP_StaveTestAfterTC_AT || asource == PP_StaveTestBeforeTC_BT || asource == PP_StaveTestAfterTC_BT){
    std::ostringstream oss;
    oss << FEposition;
    
    // If we have moduleid+94-14-01, moduleid2 is 941401FEposition.
    std::string moduleid2;
    std::cout<<"MODULE ID SIZE IS: "<<moduleid.size()<<std::endl;
    if(moduleid.size()==9){
      moduleid2 = moduleid.substr(moduleid.size()-8,8);
    }
    else moduleid2 = moduleid;
    moduleid2.replace(2,1,"");
    moduleid2.replace(4,1,"");

    if(FEposition < 10){
      moduleid2 = moduleid2 + "0" + oss.str();
      std::cout<<"MODULE ID IS: "<<moduleid2<<std::endl; 
    }else{
      moduleid2 = moduleid2 + oss.str();
      std::cout<<"MODULE ID IS: "<<moduleid2<<std::endl; 
    }
    hn_str = moduleid2;
  }
  else if(asource == PP_UsbPixReceptionTest){
//    if(FEposition > 12){
//      hn_str = "1";
//    }else{
      if (chipnumber == 0 && DbTools::GetInstance()->IsDoubleChip(moduleid)==1) hn_str= "1";
      else if (chipnumber == 1 && DbTools::GetInstance()->IsDoubleChip(moduleid)==1)hn_str ="2";
      else if (chipnumber == 0 && DbTools::GetInstance()->IsDoubleChip(moduleid)==0) hn_str="1";
      
//    }
  }else if(asource == PP_RCEReceptionTest){
    if(FEposition > 12){
      hn_str = "0";
    }else{

  if (chipnumber == 0 && DbTools::GetInstance()->IsDoubleChip(moduleid)==1) hn_str= "1";
      else if (chipnumber == 1 && DbTools::GetInstance()->IsDoubleChip(moduleid)==1)hn_str ="2";
      else if (chipnumber == 0 && DbTools::GetInstance()->IsDoubleChip(moduleid)==0) hn_str="2";
      
    }
  }

  this->Reset();
  
  TDirectory* tempdir =gDirectory;
  tempdir->cd();

  //fill digital part
  for(std::vector<ScanDef>::iterator i=scans.begin(); i!=scans.end(); i++){
    if((*i).aType == DigitalTest  && asource == (*i).processPosition && Hvstatus == (*i).HvOn){
      Stat_Module_ID = moduleid;
      Stat_Name = (*i).Name;
      Stat_Path = (*i).Path;
      Stat_HistogramNumber = (*i).HistogramNumber;
      Stat_HvOn = (*i).HvOn;
      Stat_Source = (*i).Source;
      Stat_AfterTc = (*i).AfterTc;
      Stat_aType = (*i).aType;
      Stat_processPosition =(*i).processPosition;
     
      
      //--- loading digi test part

      
      //USBPIX has only histo file
      if(asource == PP_UsbPixReceptionTest){
	digiraw = new TFile(TString((*i).Path)+"/histos.root");
	digianalysis = digiraw;
      }else{ //RCE has analysis as well
	digiraw = new TFile(TString((*i).Path) + "/histos.root");
	digianalysis = new TFile(TString((*i).Path) + "/analysis.root");
      }
      
      if (asource != PP_UsbPixReceptionTest){
	Digi_Mask_Mod = (TH2D*) digianalysis->Get("Mask_Mod_"+hn_str);
	if(Digi_Mask_Mod == NULL){
	  digiraw->Close();  
	  delete digiraw;
	  digianalysis->Close();
	  delete digianalysis;
	  return;
	}
	TDirectory * digidir = new TDirectory();
	digidir = (TDirectory*)digiraw->Get("loop1_0");
	Digi_FEI4_Errors_Proc = new 
	  TH1I(*(TH1I*)digidir->Get("Mod_"+hn_str+"_FEI4_Errors_Proc"));
	Digi_Occupancy_Point_000 = 
	  (TH2C*)digidir->Get("Mod_"+hn_str+"_Occupancy_Point_000");
	Digi_FEI4_Errors_Proc->SetDirectory(0);
	Digi_Mask_Mod->SetDirectory(0);
	Digi_Occupancy_Point_000->SetDirectory(0);
	
	digiraw->Close();  
	  delete digiraw;
	  digianalysis->Close();
	  delete digianalysis;
      } 
      
      //--- USBPIX
      else {
	Digi_FEI4_Errors_Proc=NULL;
	int digicorrectvalue = 200;
	Digi_Occupancy_Point_000 = (TH2C*)digiraw->
	  Get("Mod_"+hn_str+"_Occupancy_Point_001");
	if(Digi_Occupancy_Point_000 == NULL){
	  digiraw->Close();  
	  delete digiraw;
	  
	  return;
	}
	Digi_Mask_Mod=MakeMask(Digi_Occupancy_Point_000, "Mask_Mod_"+
			       hn_str, "Digital Masked Pixel",200);
	Digi_Occupancy_Point_000->SetDirectory(0);
	Digi_Mask_Mod->SetDirectory(0);
	digiraw->Close();  
	  delete digiraw;
	  
      }
//      delete digiraw;
//      delete digianalysis;	
      break;
    }
  }

  //fill analog part
  for(std::vector<ScanDef>::iterator i=scans.begin(); i!=scans.end(); i++){
    if((*i).aType == AnalogTest  && asource == (*i).processPosition
       &&(*i).HvOn==Hvstatus){
      //--- loading anal test part
      
      if(asource == PP_UsbPixReceptionTest){
	analraw = new TFile(TString((*i).Path) +"/histos.root");
      }else{
	analraw = new TFile(TString((*i).Path) +"/histos.root");
	analanalysis = new TFile(TString((*i).Path) + "/analysis.root");
      }
      
      if (asource != PP_UsbPixReceptionTest){
	Anal_Mask_Mod = (TH2D*)analanalysis->Get("Mask_Mod_"+hn_str);
	if(Anal_Mask_Mod == NULL){
	  analanalysis->Close();
	  delete analanalysis;
	  analraw->Close();
	  delete analraw;
	  return;
	}
	Anal_FEI4_Errors_Proc = (TH1I*)analraw->Get("Mod_"+hn_str+
						    "_FEI4_Errors_Proc");
	Anal_Occupancy_Point_000 = (TH2C*)analraw->Get("Mod_"+hn_str+
						       "_Occupancy_Point_000");
	Anal_Occupancy_Point_000->SetDirectory(0);
	Anal_Mask_Mod->SetDirectory(0);
	Anal_FEI4_Errors_Proc ->SetDirectory(0);
	
	analanalysis->Close();
	  delete analanalysis;
	  analraw->Close();
	  delete analraw;
      }else{
	Anal_FEI4_Errors_Proc = NULL;
	Anal_Occupancy_Point_000 = (TH2C*)analraw->Get("Mod_"
						       +hn_str
						       +"_Occupancy_Point_001");
	if(Anal_Occupancy_Point_000 == NULL){
	  
	  analraw->Close();
	  delete analraw;
	  return;
	}
	Anal_Mask_Mod=MakeMask(Anal_Occupancy_Point_000, "Mask_Mod_"
			       +hn_str, "Analog Masked Pixel",200);
	Anal_Occupancy_Point_000->SetDirectory(0);
	Anal_Mask_Mod->SetDirectory(0);
	
	  analraw->Close();
	  delete analraw;
      }
      break;
    }
  }
  //#if 0
  //fill threshold scan
  for(std::vector<ScanDef>::iterator i=scans.begin(); i!=scans.end(); i++){
    if((*i).aType == ThresholdScan  && asource == (*i).processPosition && Hvstatus == (*i).HvOn){
      //--- loading threshold scan part

      if(asource == PP_UsbPixReceptionTest){
	thrraw = new TFile(TString((*i).Path) + "/histos.root");
      }else{
	thrraw = new TFile(TString((*i).Path) +"/histos.root");
	thranalysis = new TFile(TString((*i).Path) + "/analysis.root");
      }
      if (asource!= PP_UsbPixReceptionTest){
	Thre_FEI4_Errors_Proc= (TH1I*)thrraw->Get("Mod_"+hn_str+"_FEI4_Errors_Proc");
	if(Thre_FEI4_Errors_Proc == NULL) break;
	
	Thre_Iter= (TH2F*)thrraw->Get("Mod_"+hn_str+"_Iter");
	Thre_Sigma= (TH2F*)thrraw->Get("Mod_"+hn_str+"_Sigma");
	Thre_ChiSquare= (TH2F*)thrraw->Get("Mod_"+hn_str+"_ChiSquare");
	Thre_Mean= (TH2F*)thrraw->Get("Mod_"+hn_str+"_Mean");
	
	Thre_thresh2d= (TH2F*)thranalysis->Get("thresh2d_Mod_"+hn_str);
	Thre_thresh1d= (TH1F*)thranalysis->Get("thresh1d_Mod_"+hn_str);
	Thre_threshdist= (TH1F*)thranalysis->Get("threshdist_Mod_"+hn_str);

	Thre_sigma1d= (TH1F*)thranalysis->Get("sigma1d_Mod_"+hn_str);
	Thre_sigmadist= (TH1F*)thranalysis->Get("sigmadist_Mod_"+hn_str);
	Thre_BadPixels= (TH2F*)thranalysis->Get("BadPixels_Mod_"+hn_str);
	
	Thre_HitsPerBin= (TH1D*)thranalysis->Get("HitsPerBin_Mod_"+hn_str);
	
	Thre_thresh2d->SetDirectory(0);
	Thre_thresh1d->SetDirectory(0);
	Thre_threshdist->SetDirectory(0);
	Thre_sigma1d->SetDirectory(0);
	Thre_sigmadist->SetDirectory(0);
	Thre_BadPixels->SetDirectory(0);
	Thre_FEI4_Errors_Proc->SetDirectory(0);
	Thre_Iter->SetDirectory(0);
	Thre_Sigma->SetDirectory(0);
	Thre_ChiSquare->SetDirectory(0);
	Thre_Mean->SetDirectory(0);
	Thre_HitsPerBin->SetDirectory(0);

	thrraw->Close();
	delete thrraw;
	thranalysis->Close();
	delete thranalysis;
      } else {
	Thre_FEI4_Errors_Proc= NULL;
	Thre_Iter= NULL;
	//Thre_thresh2d= NULL;
	Thre_thresh1d= NULL;
	//Thre_threshdist= NULL;
	Thre_sigma1d= NULL;
	Thre_BadPixels= NULL;
	Thre_HitsPerBin= NULL;
	Thre_Mean= NULL;
	Thre_thresh2d= (TH2F*)thrraw->Get("Mod_"+hn_str+"_Mean");
	//	    Thre_Sigma= (TH2F*)thrraw->Get("Mod_1_SCURVE_SIGMA");
	Thre_Sigma= (TH2F*)thrraw->Get("Mod_"+hn_str+"_SCURVE_SIGMA");
	Thre_ChiSquare= (TH2F*)thrraw->Get("Mod_"+hn_str+"_ChiSquare");
	
	Thre_sigmadist= MakeThSigmaDistribution(Thre_Sigma,"sigmadist_Mod_"+hn_str, "Sigma Distribution");
	Thre_threshdist = MakeProjectionThr(Thre_thresh2d, "Mod_"+hn_str+"_Mean1d", "Threhsold mean");

	Thre_thresh2d->SetDirectory(0);
	Thre_Sigma->SetDirectory(0);
	Thre_ChiSquare->SetDirectory(0);
	Thre_threshdist->SetDirectory(0);
	Thre_sigmadist->SetDirectory(0);
	
	thrraw->Close();
	delete thrraw;
      }
      break;
    }
  }

  //fill xtalk part
  for(std::vector<ScanDef>::iterator i=scans.begin(); i!=scans.end(); i++)
    {
      if((*i).aType == CrosstalkScan  && asource == (*i).processPosition && Hvstatus == (*i).HvOn)
	{
	  //--- loading x-talk scan part

	  if(asource == PP_UsbPixReceptionTest){
	    xtlkraw = new TFile(TString((*i).Path) + "/histos.root");
	  }else{
	    xtlkraw = new TFile(TString((*i).Path) + "/histos.root");
	    xtlkanalysis = new TFile(TString((*i).Path) + "/analysis.root");
	  }
	  
	  if (asource!= PP_UsbPixReceptionTest){
	    Cros_thresh2d =(TH2F*)xtlkanalysis->Get("thresh2d_Mod_"+hn_str);
	    Cros_thresh1d=(TH1F*)xtlkanalysis->Get("thresh1d_Mod_"+hn_str);
	    Cros_threshdist=(TH1F*)xtlkanalysis->Get("threshdist_Mod_"+hn_str);
	    Cros_sigma1d=(TH1F*)xtlkanalysis->Get("sigma1d_Mod_"+hn_str);
	    Cros_sigmadist=(TH1F*)xtlkanalysis->Get("sigmadist_Mod_"+hn_str);
	    Cros_crosstalk2d=(TH2F*)xtlkanalysis->Get("crosstalk2d_Mod_"+hn_str);
	    Cros_crosstalk1d=(TH1F*)xtlkanalysis->Get("crosstalk1d_Mod_"+hn_str);
	    Cros_crosstalkdist=(TH1F*)xtlkanalysis->Get("crosstalkdist_Mod_"+hn_str);
				
	    Cros_FEI4_Errors_Proc= (TH1I*)xtlkraw->Get("Mod_"+hn_str+"_FEI4_Errors_Proc");
	    Cros_Iter= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_Iter");
	    Cros_Sigma= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_Sigma");
	    Cros_ChiSquare= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_ChiSquare");
	    Cros_Mean= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_Mean");
				
	    Cros_thresh2d->SetDirectory(0);
	    Cros_thresh1d->SetDirectory(0);
	    Cros_threshdist->SetDirectory(0);
	    Cros_sigma1d->SetDirectory(0);
	    Cros_sigmadist->SetDirectory(0);
	    Cros_crosstalk2d->SetDirectory(0);
	    Cros_crosstalk1d->SetDirectory(0);
	    Cros_crosstalkdist->SetDirectory(0);
	    Cros_ChiSquare->SetDirectory(0);
	    Cros_FEI4_Errors_Proc->SetDirectory(0);
	    Cros_Iter->SetDirectory(0);
	    Cros_Mean->SetDirectory(0);
	    Cros_Sigma->SetDirectory(0);
		
	    xtlkraw->Close();		
	    delete xtlkraw;
	    xtlkanalysis->Close();
	    delete xtlkanalysis;
	  }
	  else {
	    Cros_thresh2d = NULL;
	    Cros_thresh1d= NULL;
	    Cros_threshdist= NULL;
	    Cros_sigma1d= NULL;
	    Cros_sigmadist= NULL;
	    Cros_crosstalk1d= NULL;
	    Cros_crosstalkdist= NULL;
	    Cros_FEI4_Errors_Proc= NULL;
	    Cros_Iter= NULL;
	    Cros_crosstalk2d= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_Occupancy_Point_001");
	    Cros_Sigma= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_SCURVE_SIGMA");
	    Cros_ChiSquare= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_ChiSquare");
	    Cros_Mean= (TH2F*)xtlkraw->Get("Mod_"+hn_str+"_Mean");
				
	    Cros_crosstalkdist = MakeProjectionXtalk(Cros_crosstalk2d, "Mod_"+hn_str+"_Occupancy1d_Point_001", "Cross-talk occupancy");
				
	    Cros_crosstalk2d->SetDirectory(0);
	    Cros_ChiSquare->SetDirectory(0);
	    Cros_Mean->SetDirectory(0);
	    Cros_Sigma->SetDirectory(0);
	    Cros_crosstalkdist->SetDirectory(0);
		
	    xtlkraw->Close();		
	    delete xtlkraw;
	  }
			
	  break;
	}
    }

  //fill IV_usb part
  for(std::vector<ScanDef>::iterator i=scans.begin(); i!=scans.end(); i++)
    {
      //      std::cout << " PATH  " << (*i).Path << " HV " << (*i).HvOn << std::endl;    
      if((*i).aType == IVScan  && asource == (*i).processPosition && Hvstatus == (*i).HvOn && asource ==   PP_UsbPixReceptionTest )
	{
	  ivusbpix = new TFile(TString((*i).Path) +
				       "/histos.root");
	  std::cout << " PATH HR  " << (*i).Path << std::endl;

	  IV_Mod_Graph = (TGraph*)ivusbpix->Get("Mod_1_graph");
	  ivusbpix->Close();
	  delete ivusbpix;
	}
      /*      else if((*i).aType == IVScan  && asource == (*i).processPosition && Hvstatus == (*i).HvOn && asource ==   PP_StaveTestBeforeTC ){
	ivusbpix = new TFile(TString((*i).Path));
	std::cout << " PATH HR 1 " << (*i).Path << std::endl;
	
	IV_Mod_Graph = (TGraph*)ivusbpix->Get("Mod_1_graph");
	ivusbpix->Close();
	delete ivusbpix;
      }
      else if((*i).aType == IVScan  && asource == (*i).processPosition && Hvstatus == (*i).HvOn && asource ==   PP_StaveTestAfterTC ){
	ivusbpix = new TFile(TString((*i).Path));
	std::cout << " PATH HR 2 " << (*i).Path << std::endl;
	
	IV_Mod_Graph = (TGraph*)ivusbpix->Get("Mod_1_graph");
	ivusbpix->Close();
	delete ivusbpix;	
	}*/
	
    }



}

TString
HistoReader::outlinkno(const TString moduleid)
{
  if(!moduleid);
  TString a;
  a = "1";
  return a;
}

TString
HistoReader::runno(const TString moduleid, const TString testid)
{
  if(!moduleid);
  TString therun;
  if( testid == "Threshold") therun = "002012";
  if( testid == "Analog") therun = "002011";
  if( testid == "Digital") therun = "002010";
  if( testid == "Crosstalk") therun = "002013";
	
  return therun;
}




void HistoReader::HistoFill(const TString moduleid)
{
  if(!moduleid);
}
Double_t HistoReader::GetIV_temp(HistoReader *aReader){
  return aReader->temp_curve;
}

void HistoReader::Reset()
{

  temp_curve = 296.;

  //--- Digital Test
  Digi_Mask_Mod = NULL;
  Digi_FEI4_Errors_Proc=NULL;
  Digi_Occupancy_Point_000=NULL;
	
  //--- Analog Test
  Anal_Mask_Mod=NULL;
  Anal_FEI4_Errors_Proc=NULL;
  Anal_Occupancy_Point_000=NULL;
	
  //--- Threshold Scan
  Thre_thresh2d=NULL;
  Thre_thresh1d=NULL;
  Thre_threshdist=NULL;
  Thre_sigma1d=NULL;
  Thre_sigmadist=NULL;
  Thre_BadPixels=NULL;
  Thre_HitsPerBin=NULL;
  Thre_ChiSquare=NULL;
  Thre_FEI4_Errors_Proc=NULL;
  Thre_Iter=NULL;
  Thre_Mean=NULL;
  Thre_Sigma=NULL;
  for (unsigned i=0; i < Thre_Occupancy.size() ; i++)
    {
      Thre_Occupancy[i] = NULL;
    }
  //---CrossTalk Scans
  Cros_thresh2d=NULL;
  Cros_thresh1d=NULL;
  Cros_threshdist=NULL;
  Cros_sigma1d=NULL;
  Cros_sigmadist=NULL;
  Cros_crosstalk2d=NULL;
  Cros_crosstalk1d=NULL;
  Cros_crosstalkdist=NULL;
  Cros_ChiSquare=NULL;
  Cros_FEI4_Errors_Proc=NULL;
  Cros_Iter=NULL;
  Cros_Mean=NULL;
  Cros_Sigma=NULL;
  for (unsigned j=0; j < Cros_Occupancy.size() ; j++)
    {
      Cros_Occupancy[j] = NULL;
    }
	
}


std::string
HistoReader::Demonstrate()
{
  std::string failed_modules;
  //--- Digital Test
  if(!Digi_Mask_Mod) failed_modules.append("Digi_Mask_Mod - ");
  if(!Digi_FEI4_Errors_Proc) failed_modules.append("Digi_FEI4_Errors_Proc - ");
  if(!Digi_Occupancy_Point_000)failed_modules.append("Digi_Occupancy_Point - ");
	
  //--- Analog Test
  if(!Anal_Mask_Mod) failed_modules.append("Anal_Mask_Mod - ");
  if(!Anal_FEI4_Errors_Proc) failed_modules.append("Anal_FEI4_Errors_Proc - ");
  if(!Anal_Occupancy_Point_000) failed_modules.append("Anal_Occupancy_Point - ");
	
  //--- Threshold Scan
  if(!Thre_thresh2d) failed_modules.append("Thre_thresh2d - ");
  if(!Thre_thresh1d) failed_modules.append("Thre_thresh1d - ");
  if(!Thre_threshdist) failed_modules.append("Thre_threshdist - ");
  if(!Thre_sigma1d) failed_modules.append("Thre_sigma1d - ");
  if(!Thre_sigmadist) failed_modules.append("Thre_sigmadist - ");
  if(!Thre_BadPixels) failed_modules.append("Thre_BadPixels - ");
  if(!Thre_HitsPerBin) failed_modules.append("Thre_HitsPerBin - ");
  if(!Thre_ChiSquare) failed_modules.append("Thre_ChiSquare - ");
  if(!Thre_FEI4_Errors_Proc) failed_modules.append("Thre_FEI4_Errors_Proc - ");
  if(!Thre_Iter) failed_modules.append("Thre_Iter - ");
  if(!Thre_Mean) failed_modules.append("Thre_Mean - ");
  if(!Thre_Sigma) failed_modules.append("Thre_Sigma - ");
  if(Thre_Occupancy.size()==0) failed_modules.append("Thre_Occupancy - ");
	
  //---CrossTalk Scans
  if(!Cros_thresh2d)  failed_modules.append("Cros_thresh2d - ");
  if(!Cros_thresh1d)  failed_modules.append("Cros_thresh1d - ");
  if(!Cros_threshdist)  failed_modules.append("Cros_threshdist - ");
  if(!Cros_sigma1d)  failed_modules.append("Cros_sigma1d - ");
  if(!Cros_sigmadist)  failed_modules.append("Cros_sigmadist - ");
  if(!Cros_crosstalk2d)  failed_modules.append("Cros_crosstalk2d - ");
  if(!Cros_crosstalk1d)  failed_modules.append("Cros_crosstalk1d -");
  if(!Cros_crosstalkdist)  failed_modules.append("Cros_crosstalkdist - ");
  if(!Cros_ChiSquare)  failed_modules.append("Cros_ChiSquare - ");
  if(!Cros_FEI4_Errors_Proc) failed_modules.append("Cros_FEI4_Errors_Proc - ");
  if(!Cros_Iter)  failed_modules.append("Cros_Iter - ");
  if(!Cros_Mean)  failed_modules.append("Cros_Mean - ");
  if(!Cros_Sigma)  failed_modules.append("Cros_Sigma - ");
  if(Cros_Occupancy.size()==0) failed_modules.append("Cros_Occupancy - ");
  return failed_modules;
}


HistoReader& HistoReader::operator = (const HistoReader& aReader)
{
  //--- Digital Test
  Digi_Mask_Mod = (TH2D*) (aReader.Digi_Mask_Mod)->Clone();
  Digi_FEI4_Errors_Proc= (TH1I*) (aReader.Digi_FEI4_Errors_Proc)->Clone();
  Digi_Occupancy_Point_000=(TH2C*)(aReader.Digi_Occupancy_Point_000)->Clone();
	
  //--- Analog Test
  Anal_Mask_Mod= (TH2D*) (aReader.Anal_Mask_Mod)->Clone();
  Anal_FEI4_Errors_Proc= (TH1I*) (aReader.Anal_FEI4_Errors_Proc)->Clone();
  Anal_Occupancy_Point_000= (TH2C*)(aReader.Anal_Occupancy_Point_000)->Clone();
	
  //--- Threshold Scan
  Thre_thresh2d= (TH2F*) (aReader.Thre_thresh2d)->Clone();
  Thre_thresh1d= (TH1F*) (aReader.Thre_thresh1d)->Clone();
  Thre_threshdist= (TH1F*) (aReader.Thre_threshdist)->Clone();
  Thre_sigma1d= (TH1F*) (aReader.Thre_sigma1d)->Clone();
  Thre_sigmadist= (TH1F*) (aReader.Thre_sigmadist)->Clone();
  Thre_BadPixels= (TH2F*) (aReader.Thre_BadPixels)->Clone();
  Thre_HitsPerBin=(TH1D*) (aReader.Thre_HitsPerBin)->Clone();
  Thre_ChiSquare=(TH2F*) (aReader.Thre_ChiSquare)->Clone();
  Thre_FEI4_Errors_Proc=(TH1I*)(aReader.Thre_FEI4_Errors_Proc)->Clone();
  Thre_Iter=(TH2F*)(aReader.Thre_Iter)->Clone();
  Thre_Mean=(TH2F*)(aReader.Thre_Mean)->Clone();
  Thre_Sigma=(TH2F*)(aReader.Thre_Sigma)->Clone();
  for (unsigned i=0; i < Thre_Occupancy.size() ; i++)
    {
      Thre_Occupancy[i] = (TH2C*)(aReader.Thre_Occupancy[i])->Clone();
    }
  //---CrossTalk Scans
  Cros_thresh2d= (TH2F*) (aReader.Cros_thresh2d)->Clone();
  Cros_thresh1d= (TH1F*) (aReader.Cros_thresh1d)->Clone();
  Cros_threshdist= (TH1F*) (aReader.Cros_threshdist)->Clone();
  Cros_sigma1d= (TH1F*) (aReader.Cros_sigma1d)->Clone();
  Cros_sigmadist= (TH1F*) (aReader.Cros_sigmadist)->Clone();
  Cros_crosstalk2d= (TH2F*) (aReader.Cros_crosstalk2d)->Clone();
  Cros_crosstalk1d= (TH1F*) (aReader.Cros_crosstalk1d)->Clone();
  Cros_crosstalkdist= (TH1F*) (aReader.Cros_crosstalkdist)->Clone();
  Cros_ChiSquare= (TH2F*) (aReader.Cros_ChiSquare)->Clone();
  Cros_FEI4_Errors_Proc= (TH1I*) (aReader.Cros_FEI4_Errors_Proc)->Clone();
  Cros_Iter= (TH2F*) (aReader.Cros_Iter)->Clone();
  Cros_Mean= (TH2F*) (aReader.Cros_Mean)->Clone();
  Cros_Sigma= (TH2F*) (aReader.Cros_Sigma)->Clone();
  for (unsigned j=0; j < Cros_Occupancy.size() ; j++)
    {
      Cros_Occupancy[j] = (TH2C*)(aReader.Cros_Occupancy[j])->Clone();
    }
  return *this;
}

void HistoReader::subtract(const HistoReader& aReader)
{
  //--- Digital Test
  Digi_Mask_Mod->Add((aReader.Digi_Mask_Mod ), -1);
  Digi_FEI4_Errors_Proc->Add((aReader.Digi_FEI4_Errors_Proc), -1);
  Digi_Occupancy_Point_000->Add((aReader.Digi_Occupancy_Point_000), -1);
	
  //--- Analog Test
  Anal_Mask_Mod->Add((aReader.Anal_Mask_Mod ), -1);
  Anal_FEI4_Errors_Proc->Add((aReader.Anal_FEI4_Errors_Proc), -1);
  Anal_Occupancy_Point_000->Add((aReader.Anal_Occupancy_Point_000), -1);
	
  //--- Threshold Scan
  Thre_thresh2d->Add((aReader.Thre_thresh2d),-1);
  Thre_thresh1d->Add((aReader.Thre_thresh1d),-1);
  Thre_threshdist->Add((aReader.Thre_threshdist),-1);
  Thre_sigma1d->Add((aReader.Thre_sigma1d),-1);
  Thre_sigmadist->Add((aReader.Thre_sigmadist),-1);
  Thre_BadPixels->Add((aReader.Thre_BadPixels),-1);
  Thre_HitsPerBin->Add((aReader.Thre_HitsPerBin),-1);
  Thre_ChiSquare->Add((aReader.Thre_ChiSquare),-1);
  Thre_FEI4_Errors_Proc->Add((aReader.Thre_FEI4_Errors_Proc),-1);
  Thre_Iter->Add((aReader.Thre_Iter),-1);
  Thre_Mean->Add((aReader.Thre_Mean),-1);
  Thre_Sigma->Add((aReader.Thre_Sigma),-1);
  for (unsigned i=0; i < Thre_Occupancy.size() ; i++)
    {
      Thre_Occupancy[i] -> Add((aReader.Thre_Occupancy[i]),-1);
    }
	
  //---CrossTalk Scans
  Cros_thresh2d->Add((aReader.Cros_thresh2d),-1);
  Cros_thresh1d->Add((aReader.Cros_thresh1d),-1);
  Cros_threshdist->Add((aReader.Cros_threshdist),-1);
  Cros_sigma1d->Add((aReader.Cros_sigma1d),-1);
  Cros_sigmadist->Add((aReader.Cros_sigmadist),-1);
  Cros_crosstalk2d->Add((aReader.Cros_crosstalk2d),-1);
  Cros_crosstalk1d->Add((aReader.Cros_crosstalk1d),-1);
  Cros_crosstalkdist->Add((aReader.Cros_crosstalkdist),-1);
  Cros_ChiSquare->Add((aReader.Cros_ChiSquare),-1);
  Cros_FEI4_Errors_Proc->Add((aReader.Cros_FEI4_Errors_Proc),-1);
  Cros_Iter->Add((aReader.Cros_Iter),-1);
  Cros_Mean->Add((aReader.Cros_Mean),-1);
  Cros_Sigma->Add((aReader.Cros_Sigma),-1);
  for (unsigned j=0; j < Cros_Occupancy.size() ; j++)
    {
      Cros_Occupancy[j]->Add((aReader.Cros_Occupancy[j]),-1);
    }
}

HistoReader::~HistoReader()
{

//  std::cout<<"\n\n\n\n\n\n\n-----------------------\n\nDESTRUCT HISTOREADER!!!!!!!\n\n-----------------------\n\n\n\n";
  //--- Digital Test
  if(Digi_Mask_Mod) delete(Digi_Mask_Mod);
  if(Digi_FEI4_Errors_Proc) delete(Digi_FEI4_Errors_Proc);
  if(Digi_Occupancy_Point_000) delete(Digi_Occupancy_Point_000);
	
  //--- Analog Test
  if(Anal_Mask_Mod) delete(Anal_Mask_Mod);
  if(Anal_FEI4_Errors_Proc) delete (Anal_FEI4_Errors_Proc);
  if(Anal_Occupancy_Point_000) delete(Anal_Occupancy_Point_000);
	
  //--- Threshold Scan
  if(Thre_thresh2d) delete(Thre_thresh2d);
  if(Thre_thresh1d) delete(Thre_thresh1d);
  if(Thre_threshdist) delete(Thre_threshdist);
  if(Thre_sigma1d) delete(Thre_sigma1d);
  if(Thre_sigmadist) delete(Thre_sigmadist);
  if(Thre_BadPixels) delete(Thre_BadPixels);
  if(Thre_HitsPerBin) delete(Thre_HitsPerBin);
  if(Thre_ChiSquare) delete(Thre_ChiSquare);
  if(Thre_FEI4_Errors_Proc) delete(Thre_FEI4_Errors_Proc);
  if(Thre_Iter) delete(Thre_Iter);
  if(Thre_Mean) delete(Thre_Mean);
  if(Thre_Sigma) delete(Thre_Sigma);
  //if(Thre_Occupancy) delete(Thre_Occupancy);
  for (unsigned i=0; i < Thre_Occupancy.size() ; i++)
    {
      delete(Thre_Occupancy[i]);
    }
  //---CrossTalk Scans
  if(Cros_thresh2d) delete(Cros_thresh2d);
  if(Cros_thresh1d) delete(Cros_thresh1d);
  if(Cros_threshdist) delete(Cros_threshdist);
  if(Cros_sigma1d) delete(Cros_sigma1d);
  if(Cros_sigmadist) delete(Cros_sigmadist);
  if(Cros_crosstalk2d) delete(Cros_crosstalk2d);
  if(Cros_crosstalk1d) delete(Cros_crosstalk1d);
  if(Cros_crosstalkdist) delete(Cros_crosstalkdist);
  if(Cros_ChiSquare) delete(Cros_ChiSquare);
  if(Cros_FEI4_Errors_Proc) delete(Cros_FEI4_Errors_Proc);
  if(Cros_Iter) delete(Cros_Iter);
  if(Cros_Mean) delete(Cros_Mean);
  if(Cros_Sigma) delete(Cros_Sigma);
  //if(Cros_Occupancy) delete(Cros_Occupancy);
  for (unsigned j=0; j < Cros_Occupancy.size() ; j++)
    {
      delete(Cros_Occupancy[j]);
    }
/*
  if(analraw) analraw->Delete();
  if(analanalysis) analanalysis->Delete();
  if(thrraw) thrraw->Delete();
  if(thranalysis) thranalysis->Delete();
  if(xtlkraw) xtlkraw->Delete();
  if(xtlkanalysis) xtlkanalysis->Delete();
  if(ivusbpix) ivusbpix->Delete();
  if(digiraw) digiraw->Delete();
  if(digianalysis) digianalysis->Delete();
*/
}

void HistoReader::Normalize()
{
}
/* vim:set shiftwidth=2 tabstop=2 expandtab: */

TH1F* HistoReader::MakeProjectionThr(TH2F* hist, TString name, const char *title)
{
  TH1F* hist1d = new TH1F(name, title, 100, 0., 10000.);
  int nbinx = hist->GetNbinsX();
  int nbiny = hist->GetNbinsY();
  for(int i=0; i<nbinx; i++){
    for(int j=0; j<nbiny; j++){
      if(hist->GetBinContent(i+1,j+1)>0)
	hist1d->Fill(hist->GetBinContent(i+1,j+1));
    }
  }
  double rms = hist1d->GetRMS();
  double min = hist1d->GetMean() - 5*rms;
  double max = hist1d->GetMean() + 5*rms;
  delete hist1d;
	
  hist1d = new TH1F(name, title, 100, min, max);
  for(int i=0; i<nbinx; i++){
    for(int j=0; j<nbiny; j++){
      if(hist->GetBinContent(i+1,j+1)>0)
	hist1d->Fill(hist->GetBinContent(i+1,j+1));
    }
  }
  TF1* gauss = new TF1("gauss","gaus",0,100000);
  hist1d->Fit("gauss", "Q");

  return hist1d;
}

TH1F* HistoReader::MakeProjectionXtalk(TH2F* hist, TString name, const char *title)
{
  double min_tmp = hist->GetMinimum();
  double max_tmp = hist->GetMaximum();
	
  TH1F* hist1d = new TH1F(name, title, 100, min_tmp, max_tmp);
  int nbinx = hist->GetNbinsX();
  int nbiny = hist->GetNbinsY();
  for(int i=0; i<nbinx; i++){
    for(int j=0; j<nbiny; j++){
      if(hist->GetBinContent(i+1,j+1)>0)
	hist1d->Fill(hist->GetBinContent(i+1,j+1));
    }
  }
  return hist1d;
}

TH1F* HistoReader::MakeThSigmaDistribution(TH2F* hist, TString name, const char *title){
    
  //	TH1F* thdist = new TH1F(name,title,1000,0,1000);
  //	TF1 *gauss_sigma = new TF1("gauss_sigma","gaus",0,1000);
       
  TH1F* hist1d = new TH1F(name, title, 200, 0, 1000);
  int nbinx = hist->GetNbinsX();
  int nbiny = hist->GetNbinsY();
  for(int i=0; i<nbinx; i++){
    for(int j=0; j<nbiny; j++){
      if(hist->GetBinContent(i+1,j+1)>0)
	hist1d->Fill(hist->GetBinContent(i+1,j+1));
    }
  }
   
  hist1d->Fit("gaus", "Q");
  //	int max = 2*(int)(thdist->GetFunction("gauss_sigma")->GetParameter(1));
  //	thdist->GetXaxis()->SetRangeUser(0,max);
  return hist1d;
}

TH2D* HistoReader::MakeMask(TH2C* hist, TString name, const char* title, int digi_good_value){
	
  int nbinx = hist->GetNbinsX();
  int nbiny = hist->GetNbinsY();
  TH2D* hist2d = new TH2D(name, title, nbinx,0,nbinx,nbiny,0,nbiny);
  for(int i=0; i<nbinx; i++){
    for(int j=0; j<nbiny; j++){
      if(hist->GetBinContent(i+1,j+1)!= digi_good_value)
	hist2d->SetBinContent(i+1,j+1,1);
    }
  }

  return hist2d;
}
bool HistoReader::check_usbpix_measurement(HistoReader *aReader_HV_usbpix)
{
   if(aReader_HV_usbpix->Digi_Occupancy_Point_000 == NULL || aReader_HV_usbpix->Anal_Occupancy_Point_000 == NULL || 
     aReader_HV_usbpix->Thre_thresh2d == NULL || aReader_HV_usbpix->Thre_Sigma == NULL || aReader_HV_usbpix->Thre_threshdist == NULL || 
     aReader_HV_usbpix->Thre_sigmadist == NULL || aReader_HV_usbpix->Cros_crosstalk2d == NULL)
    {
      std::cout << " NULL SCAN " << aReader_HV_usbpix->Stat_Module_ID.c_str() <<std::endl;
      return true;  
      }
  
  /*  else if (aReader_noHV_usbpix->Digi_Occupancy_Point_000 == NULL || aReader_noHV_usbpix->Anal_Occupancy_Point_000 == NULL || 
	   aReader_noHV_usbpix->Thre_thresh2d == NULL || aReader_noHV_usbpix->Thre_Sigma == NULL || aReader_noHV_usbpix->Thre_threshdist == NULL || 
	   aReader_noHV_usbpix->Thre_sigmadist == NULL || aReader_noHV_usbpix->Cros_thresh2d == NULL || aReader_noHV_usbpix->Cros_thresh1d == NULL || 
	   aReader_noHV_usbpix->Cros_threshdist == NULL ||  aReader_noHV_usbpix->Cros_sigma1d == NULL ||  aReader_noHV_usbpix->Cros_sigmadist == NULL ||  
	   aReader_noHV_usbpix->Cros_crosstalk1d == NULL || aReader_noHV_usbpix->Cros_crosstalk2d == NULL ||  aReader_noHV_usbpix->Sigma == NULL ||  
	   aReader_noHV_usbpix->Cros_ChiSquare == NULL ||  aReader_noHV_usbpix->Cros_Mean == NULL )
    {
      std::cout << " NULL SCAN " << std::endl;
      return true;  
      }*/

   else if (aReader_HV_usbpix->Digi_Occupancy_Point_000->Integral()== 0 || aReader_HV_usbpix->Anal_Occupancy_Point_000->Integral() == 0|| 
	   aReader_HV_usbpix->Thre_thresh2d->Integral() == 0 || aReader_HV_usbpix->Thre_Sigma->Integral() == 0 || 
	   aReader_HV_usbpix->Thre_threshdist->Integral() == 0 || aReader_HV_usbpix->Thre_sigmadist->Integral() == 0 )
    {
    std::cout << " EMPTY SCAN " << std::endl;
    return true;  
    }

  /*  else if (aReader_noHV_usbpix->Digi_Occupancy_Point_000->Integral()== 0 || aReader_noHV_usbpix->Anal_Occupancy_Point_000->Integral() == 0|| 
	   aReader_noHV_usbpix->Thre_thresh2d->Integral() == 0 || aReader_noHV_usbpix->Thre_Sigma->Integral() == 0 || 
	   aReader_noHV_usbpix->Thre_threshdist->Integral() == 0 || aReader_noHV_usbpix->Thre_sigmadist->Integral() == 0 || 
	   aReader_noHV_usbpix->Cros_thresh2d->Integral() == 0 || aReader_noHV_usbpix->Cros_thresh1d->Integral() == 0 || 
	   aReader_noHV_usbpix->Cros_threshdist->Integral() == 0 || aReader_noHV_usbpix->Cros_sigma1d->Integral() == 0 ||  
	   aReader_noHV_usbpix->Cros_sigmadist->Integral() == 0 || aReader_noHV_usbpix->Cros_crosstalk1d->Integral() == 0 ||  
	   aReader_noHV_usbpix->Cros_crosstalk2d->Integral() == 0 || aReader_noHV_usbpix->Sigma->Integral() == 0 ||  
	   aReader_noHV_usbpix->Cros_ChiSquare->Integral() == 0 || aReader_noHV_usbpix->Cros_Mean->Integral() == 0)
    
    {
    std::cout << " EMPTY SCAN " << std::endl;
    return true;  
    }*/
   return false;


}
/*HistoReader* HistoReader::instance = NULL;
HistoReader* HistoReader::GetInstance(){
  if (!instance) instance = new HistoReader(moduleid, asource);
  return instance;
  }*/
HistoReader *HistoReader::AddRCE_info(HistoReader *aReader_usb,int isfrontendzero, int feid_int )
{
  std::string moduleid = aReader_usb->Stat_Module_ID;
  int Hv = aReader_usb->Stat_HvOn;
  HistoReader *aReader_rce = new HistoReader(moduleid,PP_RCEReceptionTest,isfrontendzero,Hv,feid_int);
  //aReader_usb = aReader_rce;
  
  return aReader_rce;
}

