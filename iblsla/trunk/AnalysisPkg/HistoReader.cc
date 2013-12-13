////////////////////////////////////////////////////
// Class developed for Stave RT result comparison //
// Developed by: J. Agricola, A. Cervelli         //
// V 0.1 Jul 2012                                 //
////////////////////////////////////////////////////


#include <HistoReader.hh>
#include <TString.h>
#include <TFile.h>
#include <string>
#include <sstream>
ClassImp(HistoReader);


HistoReader::HistoReader(const TString moduleid)
{
  if(!moduleid) {Int_t i; i=1;}
  
  this->Reset();
  TString digirun = runno(moduleid, "Digital");
  TString analrun = runno(moduleid, "Analog");
  TString thrrun = runno(moduleid, "Threshold");
  TString xtlkrun = runno(moduleid, "Crosstalk");
  TString outl = outlinkno(moduleid);

  //--- loading digi test part
  TFile* digiraw = new TFile("Digital_Test_"+digirun+"/histos.root");
  TFile* digianalysis = new TFile("Digital_Test_"+digirun+"/analysis.root");
  //--- analysis
  Digi_Mask_Mod = (TH2D*)digianalysis->Get("Mask_Mod_"+outl);
  //--- histos
  TDirectory * digidir = new TDirectory();
  digidir = (TDirectory*)digiraw->Get("loop1_0"); 
  Digi_FEI4_Errors_Proc = (TH1I*)digidir->Get("Mod_"+outl+
					      "_FEI4_Errors_Proc");


  Digi_Occupancy_Point_000 = (TH2C*)digidir->Get("Mod_"+outl+
						 "_Occupancy_Point_000");


  //--- loading anal test part
  TFile * analraw = new TFile("Analog_Test_"+analrun+"/histos.root");
  TFile * analanalysis = new TFile("Analog_Test_"+analrun+"/analysis.root");
  //--- analysis
  Anal_Mask_Mod = (TH2D*)analanalysis->Get("Mask_Mod_"+outl);
  //--- histos
  Anal_FEI4_Errors_Proc = (TH1I*)analraw->Get("Mod_"+outl+
					      "_FEI4_Errors_Proc");
  Anal_Occupancy_Point_000 = (TH2C*)analraw->Get("Mod_"+outl+
						 "_Occupancy_Point_000");

  //--- loading threshold scan part
  TFile * thrraw = new TFile("Threshold_Scan_"+thrrun+"/histos.root");
  TFile * thranalysis = new TFile("Threshold_Scan_"+thrrun+"/analysis.root");

  //--- analysis
  Thre_thresh2d= (TH2F*)thranalysis->Get("thresh2d_Mod_"+outl); 
  Thre_thresh1d= (TH1F*)thranalysis->Get("thresh1d_Mod_"+outl);
  Thre_threshdist= (TH1F*)thranalysis->Get("threshdist_Mod_"+outl);
  Thre_sigma1d= (TH1F*)thranalysis->Get("sigma1d_Mod_"+outl);
  Thre_sigmadist= (TH1F*)thranalysis->Get("sigmadist_Mod_"+outl);
  Thre_BadPixels= (TH2F*)thranalysis->Get("BadPixels_Mod_"+outl);
  Thre_HitsPerBin= (TH1D*)thranalysis->Get("HitsPerBin_Mod_"+outl);

  //--- histo
  Thre_ChiSquare= (TH2F*)thrraw->Get("Mod_"+outl+"_ChiSquare");
  Thre_FEI4_Errors_Proc= (TH1I*)thrraw->Get("Mod_"+outl+"_FEI4_Errors_Proc");
  Thre_Iter= (TH2F*)thrraw->Get("Mod_"+outl+"_Iter");
  Thre_Mean= (TH2F*)thrraw->Get("Mod_"+outl+"_Mean");
  Thre_Sigma= (TH2F*)thrraw->Get("Mod_"+outl+"_Sigma");
  TString point;
  for (Int_t thriter = 0; thriter < 101 ; thriter++)
    {
      
      ostringstream o;
      o << thriter;
      if (thriter<10) point = "00"+ o.str();
      if (thriter>9 && thriter<100) point = "0"+o.str();
      if (thriter>99) point = o.str();
      Thre_Occupancy.push_back ((TH2C*)thrraw->Get("Mod_"+outl+
						   "_Occupancy_Point_"+
						   point));
    }



  //--- loading x-talk scan part
  TFile * xtlkraw = new TFile("Crosstalk_Scan_"+xtlkrun+"/histos.root");
  TFile * xtlkanalysis = new TFile("Crosstalk_Scan_"+xtlkrun+"/analysis.root");
  //---analysis
  Cros_thresh2d =(TH2F*)xtlkanalysis->Get("thresh2d_Mod_"+outl);
  Cros_thresh1d=(TH1F*)xtlkanalysis->Get("thresh1d_Mod_"+outl);
  Cros_threshdist=(TH1F*)xtlkanalysis->Get("threshdist_Mod_"+outl);
  Cros_sigma1d=(TH1F*)xtlkanalysis->Get("sigma1d_Mod_"+outl);
  Cros_sigmadist=(TH1F*)xtlkanalysis->Get("sigmadist_Mod_"+outl);
  Cros_crosstalk2d=(TH2F*)xtlkanalysis->Get("crosstalk2d_Mod_"+outl);
  Cros_crosstalk1d=(TH1F*)xtlkanalysis->Get("crosstalk1d_Mod_"+outl);
  Cros_crosstalkdist=(TH1F*)xtlkanalysis->Get("crosstalkdist_Mod_"+outl);
  //---histo
  Cros_ChiSquare= (TH2F*)xtlkraw->Get("Mod_"+outl+"_ChiSquare");
  Cros_FEI4_Errors_Proc= (TH1I*)xtlkraw->Get("Mod_"+outl+"_FEI4_Errors_Proc");
  Cros_Iter= (TH2F*)xtlkraw->Get("Mod_"+outl+"_Iter");
  Cros_Mean= (TH2F*)xtlkraw->Get("Mod_"+outl+"_Mean");
  Cros_Sigma= (TH2F*)xtlkraw->Get("Mod_"+outl+"_Sigma");
  for (Int_t xtlkiter = 0; xtlkiter < 101 ; xtlkiter++)
    {
      ostringstream o;
      o << xtlkiter;
      if (xtlkiter<10) point = "00"+o.str();
      if (xtlkiter>9 && xtlkiter<100) point = "0"+o.str();
      if (xtlkiter>99) point = o.str();
      Cros_Occupancy.push_back ((TH2C*)xtlkraw->Get("Mod_"+outl+
						    "_Occupancy_Point_00"+
						    point));
    }
#if 0  
#endif
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

void HistoReader::Reset()
{
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
}

void HistoReader::Normalize()
{
}
