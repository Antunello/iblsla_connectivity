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
#include <stdio.h>
#include <HistoReader.hh>

void make_nice_plot(TH1D *histo, TString TestID){
  const Int_t nmodules = 16;		
	
  Double_t min=0, max=0;
  if (TestID == "Thr_Mean") {
    histo->GetXaxis()->SetTitle("FE_ID");
    histo->GetYaxis()->SetTitle("Thr. Mean [e^{-}]");
    min=2500; max=3500;
  } 
  else if(TestID == "SigmaThr_Mean"){
    histo->GetXaxis()->SetTitle("FE_ID");
    histo->GetYaxis()->SetTitle("Sigma Thr. Mean [e^{-}]");
    min=90; max=300;
  }
  else "TestID unknown";

  histo->GetYaxis()->SetRangeUser(min,max);
  histo->GetXaxis()->SetTickLength(0);
  histo->GetYaxis()->SetTickLength(0.01);
  histo->GetYaxis()->SetTitleOffset(1.4);
  histo->SetMarkerColor(kRed);
  histo->SetMarkerStyle(21);
  histo->Draw("pe1x0");

  for(int i=0;i<nmodules;i++){
    TLine *line1= new TLine(i+1,min,i+1,max);
    line1->Draw("same");
  }

}

/*************************************************/
/************Threshold Mean Value*****************/
/*************************************************/


void ThresModMeanValue(vector <HistoReader*> aReader)
{
  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};
	
  TH1D *histo_thresModMeanValue = new TH1D( "histo_thresModMeanvalue","Threshold Mean Value",32,0,132);
  TString TestID = "Thr_Mean";   
  
  for(unsigned i=0;i<aReader.size();i++){
    histo_thresModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
    histo_thresModMeanValue->GetXaxis()->SetBinLabel(i+1,label[i]);
  }
  make_nice_plot(histo_thresModMeanValue,TestID);
}

void ThresModMeanValue(vector <HistoReader*> aReader, vector <HistoReader*> bReader){
  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};
	

  TH1D *histo_thresModMeanValue = new TH1D( "histo_thresModMeanvalue","Threshold Mean Value",32,0,132);
  TH1D *histo_thresModMeanValue_1 = new TH1D( "histo_thresModMeanvalue_1","Threshold Mean Value",32,0,132);
  TString TestID = "Thr_Mean";   

  for(unsigned i=0;i<aReader.size();i++){
        
    histo_thresModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
    histo_thresModMeanValue->GetXaxis()->SetBinLabel(i+1,label[i]);
        
    histo_thresModMeanValue_1->SetBinContent(i+1,bReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue_1->SetBinError(i+1,bReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
             
  }
  make_nice_plot(histo_thresModMeanValue,TestID);
    
  histo_thresModMeanValue_1->SetMarkerColor(kBlue);
  histo_thresModMeanValue_1->SetMarkerStyle(21);
  histo_thresModMeanValue_1->Draw("pe1x0same");

}

void ThresModMeanValue(vector <HistoReader*> aReader,vector <HistoReader*> bReader, vector <HistoReader*> cReader){
  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};
	
	
  TH1D *histo_thresModMeanValue = new TH1D( "histo_thresModMeanvalue","Threshold Mean Value",32,0,132);
  TH1D *histo_thresModMeanValue_1 = new TH1D( "histo_thresModMeanvalue_1","Threshold Mean Value",32,0,132);
  TH1D *histo_thresModMeanValue_2 = new TH1D( "histo_thresModMeanvalue_2","Threshold Mean Value",32,0,132);
  TString TestID = "Thr_Mean";   
     
  for(unsigned i=0;i<aReader.size();i++){
        
    histo_thresModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
    histo_thresModMeanValue->GetXaxis()->SetBinLabel(i+1,label[i]);
        
    histo_thresModMeanValue_1->SetBinContent(i+1,bReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue_1->SetBinError(i+1,bReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
        
    histo_thresModMeanValue_2->SetBinContent(i+1,cReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(1));
    histo_thresModMeanValue_2->SetBinError(i+1,cReader.at(i)->Thre_threshdist->GetFunction("gauss")->GetParameter(2));
  }
    
  make_nice_plot(histo_thresModMeanValue,TestID);
   
  histo_thresModMeanValue_1->SetMarkerColor(kBlue);
  histo_thresModMeanValue_1->SetMarkerStyle(21);
  histo_thresModMeanValue_1->Draw("pe1x0same");

  histo_thresModMeanValue_2->SetMarkerColor(kOrange);
  histo_thresModMeanValue_2->SetMarkerStyle(21);
  histo_thresModMeanValue_2->Draw("pe1x0same");

}

/*************************************************/
/************Sigma Mean Value*********************/
/*************************************************/

void SigmaModMeanValue(vector <HistoReader*> aReader){
  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};
	
	
  TH1D *histo_sigmaModMeanValue = new TH1D("histo_sigmaModMeanvalue","Sigma Threshold Mean Value",32,0,132);
  TString TestID = "SigmaThr_Mean";   

  for(unsigned i=0;i<aReader.size();i++){
    histo_sigmaModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
    histo_sigmaModMeanValue->GetXaxis()->SetBinLabel(i+1,label[i]);
  }
  make_nice_plot(histo_sigmaModMeanValue,TestID);
}

void SigmaModMeanValue(vector <HistoReader*> aReader,vector <HistoReader*> bReader){

  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};

  TH1D *histo_sigmaModMeanValue = new TH1D( "histo_sigmaModMeanvalue","Sigma Threshold Mean Value",32,0,132);
  TH1D *histo_sigmaModMeanValue_1 = new TH1D( "histo_sigmaModMeanvalue_1","Sigma Threshold Mean Value",32,0,132);
  TString TestID = "SigmaThr_Mean";   
  
  for(unsigned i=0;i<aReader.size();i++){
        
    histo_sigmaModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
    histo_sigmaModMeanValue->GetXaxis()->SetBinLabel(i+1,label.at(i));
        
    histo_sigmaModMeanValue_1->SetBinContent(i+1,bReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue_1->SetBinError(i+1,bReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
        
  }
  
  make_nice_plot(histo_sigmaModMeanValue,TestID);
  
  histo_sigmaModMeanValue_1->SetMarkerColor(kBlue);
  histo_sigmaModMeanValue_1->SetMarkerStyle(21);
  histo_sigmaModMeanValue_1->Draw("pe1x0same");
    
}


void SigmaModMeanValue(vector <HistoReader*> aReader,vector <HistoReader*> bReader, vector <HistoReader*> cReader){

  gStyle->SetOptStat(0);
  const Int_t nmodules = 16; 
  TString label[nmodules]={"A8_2","A8_1","A7_2","A7_1","A6_2","A6_1","A5_2","A5_1","A4_2","A4_1","A3_2","A3_1","A2_2","A2_1","A1_2","A1_1"};
  //"C1_1","C1_2","C2_1","C2_2","C3_1","C3_2","C4_1","C4_2","C5_1","C5_2","C6_1","C6_2","C7_1","C7_2","C8_1","C8_2"};

	
  TH1D *histo_sigmaModMeanValue = new TH1D( "histo_sigmaModMeanvalue","Sigma Threshold Mean Value",32,0,132);
  TH1D *histo_sigmaModMeanValue_1 = new TH1D( "histo_sigmaModMeanvalue_1","Sigma Threshold Mean Value",32,0,132);
  TH1D *histo_sigmaModMeanValue_2 = new TH1D( "histo_sigmaModMeanvalue_2","Sigma Threshold Mean Value",32,0,132);
  TString TestID = "SigmaThr_Mean";   
    
  for(unsigned i=0;i<aReader.size();i++){
        
    histo_sigmaModMeanValue->SetBinContent(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue->SetBinError(i+1,aReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
    histo_sigmaModMeanValue->GetXaxis()->SetBinLabel(i+1,label[i]);
        
    histo_sigmaModMeanValue_1->SetBinContent(i+1,bReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue_1->SetBinError(i+1,bReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
        
    histo_sigmaModMeanValue_2->SetBinContent(i+1,cReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(1));
    histo_sigmaModMeanValue_2->SetBinError(i+1,cReader.at(i)->Thre_sigmadist->GetFunction("gaus")->GetParameter(2));
  }
   
  make_nice_plot(histo_sigmaModMeanValue,TestID);	
   
  histo_sigmaModMeanValue_1->SetMarkerColor(kBlue);
  histo_sigmaModMeanValue_1->SetMarkerStyle(21);
  histo_sigmaModMeanValue_1->Draw("pe1x0same");
    
  histo_sigmaModMeanValue_2->SetMarkerColor(kOrange);
  histo_sigmaModMeanValue_2->SetMarkerStyle(21);
  histo_sigmaModMeanValue_2->Draw("pe1x0same");
    
}

/*************************************************/
/************ 2D Threshold *********************/
/*************************************************/

void Thres2d(vector <HistoReader*> aReader){
	
  for(unsigned i=0;i<aReader.size();i++){
    aReader.at(i)->Thre_thresh2d->Draw("colz");
  }
}
