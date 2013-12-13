////////////////////////////////////////////////////
// Class developed for Stave RT result comparison //
// Developed by: J. Agricola, A. Cervelli         //
// V 0.1 Jul 2012                                 //
////////////////////////////////////////////////////

#if !defined(_IBLSLA_HISTO_READER_H)
#define _IBLSLA_HISTO_READER_H

#include <math.h>
#include <vector>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <iostream>
#include <stdio.h>
#include <DbTools.hh>
#include <ScanDef.hh>
#include <TFile.h>
//////////////////////
// class definition //
//////////////////////

class HistoReader : public TObject
{
  
  //////////////////////////////
  // methods and constructors //
  //////////////////////////////
public :
  HistoReader(const std::string moduleid, 
	      const ProcessPosition asource =PP_RCEReceptionTest,
	      const int chipnumber=0,
	      const int Hvstatus =1,
	      const int FEposition =1);
  
  
  ~HistoReader();
  void subtract(const HistoReader& aReader); 
  HistoReader & operator = (const HistoReader& areader);
  void Normalize();
  std::string Demonstrate();
  //ClassDef(HistoReader, 1);
 Double_t GetIV_temp(HistoReader *aReader);
private:
  void HistoFill(const TString moduleid);
  void Reset();
  TString outlinkno(const TString moduleid);
  TString runno(const TString moduleid, const TString testid);
  TH1F* MakeProjectionThr(TH2F* hist, TString name, const char *title);
  TH1F* MakeProjectionXtalk(TH2F* hist, TString name, const char *title);
  TH1F* MakeThSigmaDistribution(TH2F* hist, TString name, const char *title);
  TH2D* MakeMask(TH2C* hist, TString name, const char* title, int digi_good_value=200);
 
  //  void AddRCE_info(HistoReader *aReader_usb);
  
  /////////////
  // members //
  /////////////
public:
  //--- HistoReader ModuleID
  /*static HistoReader* GetInstance();
    static HistoReader* instance;*/
  bool check_usbpix_measurement(HistoReader *aReader_HV_usbpix /*HistoReader *aReader_noHV_usbpix*/);
  HistoReader *AddRCE_info(HistoReader *aReader_usb,int isfrontendzero, int feid_int );   
 

  //--- HistoReaderStats
  std::string Stat_Module_ID;
  std::string Stat_Name;
  std::string Stat_Path;
  double temp_curve;


  int Stat_HistogramNumber;
  int Stat_HvOn;
  ScanSource Stat_Source;
  int Stat_AfterTc;
  ScanType Stat_aType;
  ProcessPosition Stat_processPosition;
  //--- Digital Test
  //--- analysis
  TH2D* Digi_Mask_Mod;
  //--- histos
  TH1I* Digi_FEI4_Errors_Proc;
  TH2C* Digi_Occupancy_Point_000;
  
  //--- Analog Test
  //--- analysis
  TH2D* Anal_Mask_Mod;
  //--- histo
  TH1I* Anal_FEI4_Errors_Proc;
  TH2C* Anal_Occupancy_Point_000;
  
  //--- Threshold Scan
  //--- analysis
  TH2F* Thre_thresh2d;
  TH1F* Thre_thresh1d;
  TH1F* Thre_threshdist;
  TH1F* Thre_sigma1d;
  TH1F* Thre_sigmadist;
  TH2F* Thre_BadPixels;
  TH1D* Thre_HitsPerBin;
  //--- histo
  TH2F* Thre_ChiSquare;
  TH1I* Thre_FEI4_Errors_Proc;
  TH2F* Thre_Iter;
  TH2F* Thre_Mean;
  TH2F* Thre_Sigma;
  std::vector<TH2C*> Thre_Occupancy;
  
  //---CrossTalk Scans
  //---analysis
  TH2F* Cros_thresh2d;
  TH1F* Cros_thresh1d;
  TH1F* Cros_threshdist;
  TH1F* Cros_sigma1d;
  TH1F* Cros_sigmadist;
  TH2F* Cros_crosstalk2d;
  TH1F* Cros_crosstalk1d;
  TH1F* Cros_crosstalkdist;
  //---histo
  TH2F* Cros_ChiSquare;
  TH1I* Cros_FEI4_Errors_Proc;
  TH2F* Cros_Iter;
  TH2F* Cros_Mean;
  TH2F* Cros_Sigma;
  std::vector<TH2C*> Cros_Occupancy;
  
  //---IV Scans
  TGraph* IV_Mod_Graph;
  //std::vector<TGraph*> IV;
  //---TFile
  TFile* analraw;
  TFile* analanalysis;
  TFile* thrraw;
  TFile* thranalysis;
  TFile* xtlkraw;
  TFile* xtlkanalysis;
  TFile* ivusbpix;
  TFile* digiraw;
  TFile* digianalysis;
};
#endif /* #if !defined(_IBLSLA_HISTO_READER_H)  */
/* vim:set shiftwidth=2 tabstop=2 expandtab: */
