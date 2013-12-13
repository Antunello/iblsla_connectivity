//
//  File.cpp
//  
//
//  Created by Antu on 06/12/12.
//
//

#include <Sr1_converter.hh>
#include <Astave.hh>
#include <TObject.h>
#include <stdio.h>
#include <HistoReader.hh>
#include <TGraph.h>
#include <ScanDef.hh>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <IVMeasurementPoint.hh>
#include <TDirectory.h>
#include <DbTools.hh>



void Sr1_converter_main(Astave *stave_info_withHV, Astave *stave_info_withoutHV, ProcessPosition asource){
    //TFile* SR1;
    
    //--- Digital Test
    TH2C* Sr1_Digi_Occupancy_Point_000;
    //--- Analog Test
    TH2C* Sr1_Anal_Occupancy_Point_000;
    
    //--- Threshold Scan
    TH2F* Sr1_Thre_thresh2d;
    TH1F* Sr1_Thre_thresh1d;
    TH1F* Sr1_Thre_threshdist;
    TH1F* Sr1_Thre_sigma1d;
    TH1F* Sr1_Thre_sigmadist;
    TH2F* Sr1_Thre_Sigma;
    
    //--- X-talk
    TH2F* Sr1_Cros_crosstalk2d;
    
    
    
    //---IV Scans
    //TGraph* Sr1_IV_Mod_Graph;
    //std::vector<TGraph*> IV;
    
    Sr1_Digi_Occupancy_Point_000=NULL;
    Sr1_Anal_Occupancy_Point_000=NULL;
    Sr1_Thre_thresh2d=NULL;
    Sr1_Thre_thresh1d=NULL;
    Sr1_Thre_threshdist=NULL;
    Sr1_Thre_sigma1d=NULL;
    Sr1_Thre_sigmadist=NULL;
    Sr1_Thre_Sigma=NULL;
    Sr1_Cros_crosstalk2d=NULL;
    
    
    
    std::string stave_name = stave_info_withHV->STAVEID;
    std::vector <HistoReader*> module_histograms_HV = stave_info_withHV->StaveReaderModule();
    std::vector <HistoReader*> module_histograms_noHV = stave_info_withoutHV->StaveReaderModule();
//    TString module_fold, FE_fold;
    
    std::string FE_folders[]={"A8-2","A8-1","A7-2", "A7-1","A6-2","A6-1", "A5-2", "A5-1", "A4-2", "A4-1", "A3-2", "A3-1", "A2-2", "A2-1", "A1-2", "A1-1","C1-1", "C1-2","C2-1","C2-2","C3-1","C3-2","C4-1","C4-2","C5-1","C5-2","C6-1","C6-2","C7-1","C7-2","C8-1","C8-2"};
    
    std::string scan_name_hv[]={"Digital_Scan","Analog_Scan","Threshold_2D","Threshold_1D","Threshold","Noise_1D","Noise","Noise_2D","Crosstalk_2D"};
    std::string scan_name_nohv[]={"Digital_Scan_No_Hv","Analog_Scan_No_Hv","Threshold_2D_No_Hv","Threshold_1D_No_Hv","Threshold_No_Hv","Noise_1D_No_Hv","Noise_No_Hv","Noise_2D_No_Hv","Crosstalk_2D_No_Hv"};
    std::string histogram_name;
    std::cout<<stave_name<<std::endl;
    std::string Sr1_filename;
    Sr1_filename.append(DbTools::GetInstance()->DatabasePath()+"/QAtemp/");
    Sr1_filename.append("stave");
    Sr1_filename.append(stave_name);
    switch(asource){
	case PP_UsbPixReceptionTest:
	Sr1_filename.append("_RT");
	break;

	case PP_StaveTestBeforeTC_AT:
	Sr1_filename.append("_BTC");
	break;

	case PP_StaveTestAfterTC_AT:
	Sr1_filename.append("_ATC");
	break;
            
    case PP_StaveTestAfterTC_BT:
    Sr1_filename.append("_ATC_BT");
    break;
            

	default:
	break;
    }

    Sr1_filename.append("_Unige.root");
    
    
  //  strcpy(Sr1_filename_char, Sr1_filename.c_str());
    
    TFile *SR1 = new TFile(Sr1_filename.c_str(),"RECREATE");

    
    TDirectory *Unige_fold = SR1->mkdir("Unige_Measurement");
    Unige_fold->cd();

    int i=0;
    TDirectory *FE_folder_dir[32],*withHV_dir[32], *withoutHV_dir[32];
    for(std::vector<HistoReader*>::iterator iii=module_histograms_HV.begin(); iii!=module_histograms_HV.end(); iii++){
    if(i<=31){
        std::cout<<"FE_folder: "<<FE_folders[i].c_str()<<"\t counter: "<<i<<"\t vector size:"<<module_histograms_HV.size()<<std::endl;
	FE_folder_dir[i] = Unige_fold->mkdir(FE_folders[i].c_str());
	FE_folder_dir[i]->cd();
	//withHV_dir[i]=FE_folder_dir[i]->mkdir("with_HV");
	//withHV_dir[i]->cd();
                Sr1_Digi_Occupancy_Point_000 = (*iii)->Digi_Occupancy_Point_000;
	if(Sr1_Digi_Occupancy_Point_000!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[0]);
		Sr1_Digi_Occupancy_Point_000->SetName(histogram_name.c_str());	
		Sr1_Digi_Occupancy_Point_000->Write();
	}
        Sr1_Anal_Occupancy_Point_000 = (*iii)->Anal_Occupancy_Point_000;
	if(Sr1_Anal_Occupancy_Point_000!=NULL){	
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[1]);
		Sr1_Anal_Occupancy_Point_000->SetName(histogram_name.c_str());
		Sr1_Anal_Occupancy_Point_000->Write();
	}
        Sr1_Thre_thresh2d = (*iii)->Thre_thresh2d;
	if(Sr1_Thre_thresh2d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[2]);
		Sr1_Thre_thresh2d->SetName(histogram_name.c_str());
		Sr1_Thre_thresh2d->Write();
	}        
	Sr1_Thre_thresh1d = (*iii)->Thre_thresh1d;
	if(Sr1_Thre_thresh1d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[3]);
		Sr1_Thre_thresh1d->SetName(histogram_name.c_str());
		Sr1_Thre_thresh1d->Write();
	}
        Sr1_Thre_threshdist = (*iii)->Thre_threshdist;
	if(Sr1_Thre_threshdist!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[4]);
        	Sr1_Thre_threshdist->SetName(histogram_name.c_str());
		Sr1_Thre_threshdist->Write();
	}
	Sr1_Thre_sigma1d = (*iii)->Thre_sigma1d;
	if(Sr1_Thre_sigma1d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[5]);
		Sr1_Thre_sigma1d->SetName(histogram_name.c_str());
		Sr1_Thre_sigma1d->Write();
	}
        Sr1_Thre_sigmadist = (*iii)->Thre_sigmadist;
	if(Sr1_Thre_sigmadist!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[6]);
		Sr1_Thre_sigmadist->SetName(histogram_name.c_str());
        	Sr1_Thre_sigmadist->Write();
	}
	Sr1_Thre_Sigma = (*iii)->Thre_Sigma;
	if(Sr1_Thre_Sigma!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_hv[7]);
		Sr1_Thre_Sigma->SetName(histogram_name.c_str());
		Sr1_Thre_Sigma->Write();
	}
    Sr1_Cros_crosstalk2d = (*iii)->Cros_crosstalk2d;
    if(Sr1_Thre_Sigma!=NULL){
        histogram_name.clear();
        histogram_name.append(FE_folders[i]);
        histogram_name.append(scan_name_hv[8]);
        Sr1_Cros_crosstalk2d->SetName(histogram_name.c_str());
        Sr1_Cros_crosstalk2d->Write();
    }
    Unige_fold->cd();
}
	i++;
    }
    
    i=0;

    for(std::vector<HistoReader*>::iterator iii=module_histograms_noHV.begin(); iii!=module_histograms_noHV.end(); iii++){
//	FE_folder_dir[i] = Unige_fold->mkdir(FE_folders[i].c_str());
	if(i<=31){	
	FE_folder_dir[i]->cd();
	//withoutHV_dir[i]=FE_folder_dir[i]->mkdir("without_HV");
	//withoutHV_dir[i]->cd();
        Sr1_Digi_Occupancy_Point_000 = (*iii)->Digi_Occupancy_Point_000;
	if(Sr1_Digi_Occupancy_Point_000!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[0]);
		Sr1_Digi_Occupancy_Point_000->SetName(histogram_name.c_str());	
		Sr1_Digi_Occupancy_Point_000->Write();
	}
        Sr1_Anal_Occupancy_Point_000 = (*iii)->Anal_Occupancy_Point_000;
	if(Sr1_Anal_Occupancy_Point_000!=NULL){	
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[1]);
		Sr1_Anal_Occupancy_Point_000->SetName(histogram_name.c_str());
		Sr1_Anal_Occupancy_Point_000->Write();
	}
        Sr1_Thre_thresh2d = (*iii)->Thre_thresh2d;
	if(Sr1_Thre_thresh2d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[2]);
		Sr1_Thre_thresh2d->SetName(histogram_name.c_str());
		Sr1_Thre_thresh2d->Write();
	}        
	Sr1_Thre_thresh1d = (*iii)->Thre_thresh1d;
	if(Sr1_Thre_thresh1d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[3]);
		Sr1_Thre_thresh1d->SetName(histogram_name.c_str());
		Sr1_Thre_thresh1d->Write();
	}
        Sr1_Thre_threshdist = (*iii)->Thre_threshdist;
	if(Sr1_Thre_threshdist!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[4]);
        	Sr1_Thre_threshdist->SetName(histogram_name.c_str());
		Sr1_Thre_threshdist->Write();
	}
	Sr1_Thre_sigma1d = (*iii)->Thre_sigma1d;
	if(Sr1_Thre_sigma1d!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[5]);
		Sr1_Thre_sigma1d->SetName(histogram_name.c_str());
		Sr1_Thre_sigma1d->Write();
	}
        Sr1_Thre_sigmadist = (*iii)->Thre_sigmadist;
	if(Sr1_Thre_sigmadist!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[6]);
		Sr1_Thre_sigmadist->SetName(histogram_name.c_str());
        	Sr1_Thre_sigmadist->Write();
	}
	Sr1_Thre_Sigma = (*iii)->Thre_Sigma;
	if(Sr1_Thre_Sigma!=NULL){
		histogram_name.clear();
		histogram_name.append(FE_folders[i]);
		histogram_name.append(scan_name_nohv[7]);
		Sr1_Thre_Sigma->SetName(histogram_name.c_str());
		Sr1_Thre_Sigma->Write();
	}
    Sr1_Cros_crosstalk2d = (*iii)->Cros_crosstalk2d;
    if(Sr1_Thre_Sigma!=NULL){
        histogram_name.clear();
        histogram_name.append(FE_folders[i]);
        histogram_name.append(scan_name_hv[8]);
        Sr1_Cros_crosstalk2d->SetName(histogram_name.c_str());
        Sr1_Cros_crosstalk2d->Write();
    }
	Unige_fold->cd();
	}
	i++;
    }

    
    SR1->Close();
    delete Sr1_Digi_Occupancy_Point_000;
    delete Sr1_Anal_Occupancy_Point_000;
    delete Sr1_Thre_thresh2d;
    delete Sr1_Thre_thresh1d;
    delete Sr1_Thre_threshdist;
    delete Sr1_Thre_sigma1d;
    delete Sr1_Thre_sigmadist;
    delete Sr1_Thre_Sigma;
    delete Sr1_Cros_crosstalk2d;

}

