////////////////////////////////////////////////////
// Class developed for Stave RT result comparison //
// Developed by: J. Agricola, A. Cervelli         //
// V 0.1 Jul 2012                                 //
////////////////////////////////////////////////////


#include <math.h>
#include <vector>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>
#include <iostream>
#include <stdio.h>
//////////////////////
// class definition //
//////////////////////

class HistoReader : public TObject
{

  //////////////////////////////
  // methods and constructors //
  //////////////////////////////
public :
  HistoReader(const TString moduleid);
  ~HistoReader();
  void subtract(const HistoReader& aReader); 
  HistoReader & operator = (const HistoReader& areader);
  void Normalize();
  ClassDef(HistoReader, 1);
private:
  void HistoFill(const TString moduleid);
  void Reset();
  TString outlinkno(const TString moduleid);
  TString runno(const TString moduleid, const TString testid);
  /////////////
  // members //
  /////////////
public:

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
  vector<TH2C*> Thre_Occupancy;
  
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
  vector<TH2C*> Cros_Occupancy;

};
