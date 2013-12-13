#define M4C 7
#define M3C 6
#define M2C 5
#define M1C 4
#define M1A 3
#define M2A 2
#define M3A 1
#define M4A 0
#if !defined(_IBLSLA_ANALYSIS_H)
#define _IBLSLA_ANALYSIS_H

#include <TString.h>
#include <TFile.h>
#include <string>
#include <sstream>
#include <TStyle.h>
#include <TLine.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <HistoReader.hh>
#include <THStack.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TLegend.h>
#include <TColor.h>
#include <DbTools.hh>
#include <ScanDef.hh>
#include <Astave.hh>
#include <TGFrame.h>
#include <TTreePlayer.h>

void FicoDraw(TH2* histo);
void FicoPlot();
void make_nice_plot(TH1D *histo, TString TestID);
void ThresModMeanValue(std::vector <HistoReader*> aReader);
void ThresModMeanValue(std::vector <HistoReader*> aReader, std::vector <HistoReader*> bReader);
void ThresModMeanValue(std::vector <HistoReader*> aReader,std::vector <HistoReader*> bReader, std::vector <HistoReader*> cReader);
void SigmaModMeanValue(std::vector <HistoReader*> aReader);
void SigmaModMeanValue(std::vector <HistoReader*> aReader,std::vector <HistoReader*> bReader);
void SigmaModMeanValue(std::vector <HistoReader*> aReader,std::vector <HistoReader*> bReader, std::vector <HistoReader*> cReader);
void Thres2d(HistoReader* aReader);
void Thres2d_Diff(HistoReader* aReader,HistoReader* bReader);
void BadPixelsMap(HistoReader *aReader, HistoReader *aReader_noHV);
void AnalOccupancy(HistoReader *aReader);
void DigitalOccupancy(HistoReader *aReader);
void CrossTalk2d(HistoReader *aReader);
void CrossTalkdist(HistoReader *aReader);
TH2I* TDB(HistoReader* aReader_withoutHV);
TH2I* TDB_diff(HistoReader* aReader_withoutHV,HistoReader* aReader_HV);
TH1I* TH_SIGMA_DIST(HistoReader* aReader_withoutHV);
void ThresholdDisconnectedBumps(HistoReader* aReader);
void ThresholdDisconnectedBumps_2(HistoReader* aReader_withoutHV, HistoReader *aReader_HV);
void Threshold_sigma_dist(HistoReader* aReader);
void Threshold_thres_dist(HistoReader* aReader);
void AnalDiff(HistoReader* aReader,HistoReader* bReader);
void DigiDiff(HistoReader* aReader,HistoReader* bReader);
void Threshold_thres_dist_diff(HistoReader* aReader,HistoReader* bReader);
void Threshold_sigma_dist_diff(HistoReader* aReader,HistoReader* bReader);
void ThresholdSigma2d(HistoReader *aReader);
TH1F* GetIVhisto(TGraph* IV_graph);
void IV_3D(Astave* aStave, const std::string staveid,const ProcessPosition asource);
void IV_Planar(Astave* aStave, const std::string staveid,const ProcessPosition asource);
std::string IV_Mod(HistoReader* aReader,HistoReader* bReader);
void IV_Mod_Norm(HistoReader* aReader,HistoReader* bReader);
// additional function //
void Thre_thresh1d(HistoReader* aReader);
void Thre_sigma1d(HistoReader* aReader);
void Thre_BadPixels(HistoReader* aReader);
void Cros_thresh1d(HistoReader* aReader);
void Cros_sigma1d(HistoReader* aReader);
void Cros_thresh2d(HistoReader* aReader);
void Cros_threshdist(HistoReader* aReader);
void Cros_sigmadist(HistoReader* aReader);
void Cros_crosstalk1d(HistoReader* aReader);
void DigitalAnalogDeadHistory(HistoReader *hrUSBpix, HistoReader *hrRCE_rt, HistoReader *hrRCE_BefThCycle, HistoReader *hrRCE_AftThCycle);
int* BadPixelMonster(HistoReader *aReader_HV,HistoReader *aReader_NO_HV);
std::vector <int> BadPixelMonster2(HistoReader *aReader_HV,HistoReader *aReader_NO_HV);
std::vector <int> BadPixelMonsterHierarchy(HistoReader *aReader_HV,HistoReader *aReader_NO_HV);
void BadPixelTXT(ProcessPosition PP, std::vector<std::string> modules);
void BP_J(std::vector <HistoReader*> stave_hv,std::vector <HistoReader*> stave_nohv);
void BP_J_disco(std::vector <HistoReader*> stave_hv,std::vector <HistoReader*> stave_nohv);
int TotalAmountBadPixel(HistoReader *aReader_HV,HistoReader *aReader_NO_HV);
void SummaryPlot(ProcessPosition PP, std::vector<std::string> modules);
//void AnalogDeadHistory(HistoReader *hrUSBpix, HistoReader *hrRCE_rt, HistoReader *hrRCE_BefThCycle, HistoReader *hrRCE_AftThCycle);
//TH1* thdist;
// for the stave

void DigitalBad_Stave(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV);
void DigitalBad_Stave2(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV,std::vector <HistoReader*> stavevector2,std::vector <HistoReader*> stavevector2_noHV);
void DigitalBad_Stave3(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV,std::vector <HistoReader*> stavevector2,std::vector <HistoReader*> stavevector2_noHV, std::vector <HistoReader*> stavevector3,std::vector <HistoReader*> stavevector3_noHV);
void AnalogBad_Stave(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV);
void AnalogBad_Stave2(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV,std::vector <HistoReader*> stavevector2,std::vector <HistoReader*> stavevector2_noHV);
void AnalogBad_Stave3(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV,std::vector <HistoReader*> stavevector2,std::vector <HistoReader*> stavevector2_noHV, std::vector <HistoReader*> stavevector3,std::vector <HistoReader*> stavevector3_noHV);
void Fit_noisedistro(TH1* histo);
void BadDistribution(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV);
void BadDistribution_disco(std::vector <HistoReader*> stavevector,std::vector <HistoReader*> stavevector_noHV);
void DisconnectedStave(std::vector <HistoReader*> stave_hv, std::vector <HistoReader*> stave_nohv);
void DisconnectedStave2(std::vector <HistoReader*> stave_hv, std::vector <HistoReader*> stave_nohv,std::vector <HistoReader*> stave_hv2, std::vector <HistoReader*> stave_nohv2);
void DigiCorrelationPlotModules(HistoReader* before, HistoReader* after);
void AnalCorrelationPlotModules(HistoReader* before, HistoReader* after);
void BadDistribution_Module(HistoReader* aReader,HistoReader* aReader_noHV);
void NoiseGreaterThanGaussian(HistoReader* aReader);
TGMainFrame* AvailableModulesSummaryTable(ProcessPosition PP, std::vector<std::string> modules);
void IV_all_modules(ProcessPosition PP, std::vector<std::string> modules);
void IV_sector(int sector, Astave* stave_BTC,Astave* stave_AFTC);
TH1D* IVGraph_HistoConverter(TGraph *graph);
double IV_TempScalingFactor(double T_duringTest, double T_projected);
//bool check_usbpix_measurement(HistoReader *aReader_HV_usbpix, HistoReader *aReader_noHV_usbpix);
#endif /* #if !defined(_IBLSLA_ANALYSIS_H) */
