#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include "DbTools.hh"
#include "ScanDef.hh"
#include <iterator>



DbTools* DbTools::instance = NULL;

DbTools* DbTools::GetInstance()
{
  if (!instance) instance = new DbTools();
  return instance;
}

DbTools* DbTools::configure(std::string path)
{
  DbTools* tools = GetInstance();
  tools->database_path = path;
  return tools;
}
int DbTools::IsDoubleChip(std::string module_id)
{
  std::vector<ScanDef> scandefs;
  GetScanList(module_id, 1, scandefs);
  for (std::vector<ScanDef>::iterator i = scandefs.begin(); i != scandefs.end(); i++)
    {
      if ((*i).HistogramNumber == 2)

	return 1;
    }
  
  return 0;
}

int DbTools::IsDir(std::string file)
{
  struct stat stb;
  int res = stat(file.c_str(), &stb);
  if (res == 0)
    {
      return S_ISDIR(stb.st_mode);
    }
  else
    {
      std::cerr << __FILE__ << ":" << __LINE__ << " " << "stat() failed for " << file << " errno=" << errno << std::endl << std::flush;
    }
  return 0;
}

int DbTools::GetModuleIdList(std::vector<std::string> &list)
{
  std::string dir = this->database_path + "/modules/";
 
  DIR *dp;
  struct dirent *dirp;

  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << dir << std::endl << std::flush;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    std::string dn(dirp->d_name);
    if (dn.compare(".") and dn.compare("..") and IsDir(dir + dn)){
      list.push_back(dn);
    }
  }
  
  closedir(dp);
  return 0;
}
int DbTools::GetModuleIdList2(std::vector<std::string> &list)
{
  std::string dir = this->database_path + "/modules/";

  std::string staveloading_dir = this->database_path;
  std::vector <std::string> staveloading_filename;
 // std::string st_name;
  std::ostringstream sname;  
  std::string sdir;
  //std::cout<<sdir<<std::endl;
  
  std::string line;
  bool check=false;	


  
 
  DIR *dp;
  struct dirent *dirp;

   if((dp  = opendir(dir.c_str())) == NULL) {
    std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << dir << std::endl << std::flush;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    std::string dn(dirp->d_name);
    //std::cout<<"Module name: "<<dn<<std::endl;
      //staveloading_files.open("stave0_loading.txt");
      check=false;
      for(int i=0;i<25;i++){
	int j = i-1;
	sname.str("");
	sname << "/stave" << j <<"_loading.txt";
	sdir = staveloading_dir + sname.str();
	//std::cout<<sdir<<std::endl;
	//std::cout<<"stave file is: "<<staveloading_filename[i]<<std::endl;
	
      

        std::ifstream staveloading_files(sdir.c_str());
        
        //if(!staveloading_files)std::cout<<"file not loaded"<<std::endl;
        while(std::getline(staveloading_files, line))  // remember this idiom!!
  	 	{
	     
	 	    //std::cout<<"Checking the module"<<dn<<std::endl;
	 	    if (line.substr(0, dn.length()) == dn){  // not so efficient
     //if (line.length() >= dn.length() && std::equal(dn.begin(), dn.end(), line.begin())) // better
     //if (std::search(line.begin(), line.end(), dn.begin(), dn.end()) != line.end())  // for arbitrary position
     			check=true;
			//std::cout<<"Found the module: "<<dn<<std::endl;
	 		}
    
  		}
	}

    if (dn.compare(".") and dn.compare("..") and IsDir(dir + dn)){

	if(check==false)list.push_back(dn);
    }
  }
  
  closedir(dp);
  return 0;
}
int DbTools::GetStaveIdList(std::vector<std::string> &list)
{
  std::string dir = this->database_path + "/staves/";

  DIR *dp;
  struct dirent *dirp;
  
  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << dir << std::endl << std::flush;
    return errno;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    std::string dn(dirp->d_name);
    if (dn.compare(".") and dn.compare("..") and IsDir(dir + dn)){
      list.push_back(dn);
    }
  }
  
  closedir(dp);
  return 0;
}

int DbTools::GetScanList(std::string ModuleId, int chipnumber, std::vector<ScanDef> &list)
{
  // Stave-based scans:
  for (int tced = 0; tced < 4; tced++){
    for (int hvon = 0; hvon < 2; hvon++){
      ProcessPosition pp;
      std::string ls_path(this->database_path);
      //ls_path.append("/modules/");
      //ls_path.append(ModuleId);
      ls_path.append("/staves/");
        ls_path.append("stave");
        std::cout<<"  GetScanList  "<<std::endl;
        ls_path.append(ModuletoStave(ModuleId));
        ls_path.append("/");
        
        /*if (tced){
        ls_path.append("after_tc/");
        pp = PP_StaveTestAfterTC;
      }else{
        ls_path.append("before_tc/");
        pp = PP_StaveTestBeforeTC;
      }*/
      switch(tced){
	case 0:
	ls_path.append("after_tc/after_tuning/");
	pp = PP_StaveTestAfterTC_AT;
	break;

	case 1:
	ls_path.append("after_tc/before_tuning/");
	pp = PP_StaveTestAfterTC_BT;
	break;

	case 2:
	ls_path.append("before_tc/after_tuning/");
	pp = PP_StaveTestBeforeTC_AT;
	break;

	case 3:
	ls_path.append("before_tc/before_tuning/");
	pp = PP_StaveTestBeforeTC_BT;
	break;
       
      }

      if (hvon){
        ls_path.append("with_hv/");
      }else{
        ls_path.append("without_hv/");
      }
      
      DIR *dp;
      struct dirent *dirp;
      
      if((dp  = opendir(ls_path.c_str())) == NULL) {
	//std::cerr << __FILE__ << ":" << __LINE__ << " " <<  "Error(" << errno << ") opening " << ls_path << std::endl << std::flush;
      }else{
        while ((dirp = readdir(dp)) != NULL) {
          std::string dn(dirp->d_name);
          if (dn.compare(".") and dn.compare("..") and IsDir(ls_path + dn)){
            ScanType st = GuessScanTypeFromName(dn);
            int histonumber = ReadHistoNumber(ls_path + dn + "/globalconfig.txt", chipnumber, ModuleId);
            if (histonumber != -1){
	      //  std::cout<<"LS_PATH + DN:\t"<<ls_path+dn<<std::endl;
              list.push_back(ScanDef(dn, ls_path + dn, histonumber, hvon, StaveTest, tced, st, pp));
	    }
	  }
        }
        closedir(dp);
      }
    }
  }
  for (int hvon = 0; hvon < 2; hvon++){
    int tced = 0;
    std::string ls_path(this->database_path);
    ls_path.append("/modules/");
    ls_path.append(ModuleId);
    ls_path.append("/rce_rt/");
    if (hvon){
      ls_path.append("with_hv/");
    }else{
      ls_path.append("without_hv/");
    }
    
    DIR *dp;
    struct dirent *dirp;
    
    if((dp  = opendir(ls_path.c_str())) == NULL) {
//      std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << ls_path << std::endl << std::flush;
    }else{
      while ((dirp = readdir(dp)) != NULL) {
        std::string dn(dirp->d_name);
        if (dn.compare(".") and dn.compare("..") and IsDir(ls_path + dn)){
          ScanType st = GuessScanTypeFromName(dn);
	  
          int histonumber = ReadHistoNumber(ls_path + dn + "/globalconfig.txt", chipnumber, ModuleId);
          if (histonumber != -1){ 
            list.push_back(ScanDef(dn, ls_path + dn, histonumber, hvon, StaveTest, tced, st, PP_RCEReceptionTest));
          }
        }
      }
      closedir(dp);
    }
  }
  // IV Scans
  /*    for (int tced = 0; tced < 2; tced++){
    std::string ls_path(this->database_path);
    ls_path.append("/modules/");
    ls_path.append(ModuleId);
    ls_path.append("/stave/");
    ProcessPosition pp;
    if (tced){
      ls_path.append("after_tc/");
      pp = PP_StaveTestAfterTC;
    }else{
      ls_path.append("before_tc/");
      pp = PP_StaveTestBeforeTC;
    }
    ls_path.append("IV/");
    
    DIR *dp;
    struct dirent *dirp;
    
    int DC =  IsDoubleChip(ModuleId);
    std::cout << " DC " << DC << std::endl;
    if((dp  = opendir(ls_path.c_str())) == NULL) {
      std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << ls_path << std::endl << std::flush;
    }else{
      while ((dirp = readdir(dp)) != NULL) {
        std::string dn(dirp->d_name);
        if (dn.compare(".") and dn.compare("..")){
	  if(dn.substr(0,4)=="IV_3" && IsdoubleChip(moduleid) == 0){
	    if (IsDir(ls_path + dn)){
	      list.push_back(ScanDef(dn, ls_path + dn, -1, 1, UsbPixIV, tced, IVScan, pp));
     	    }else{
	      list.push_back(ScanDef(dn, ls_path + dn, -1, 1, LabViewIV, tced, IVScan, pp));
	    }
	  }
	  else if(dn.substr(0,4)=="IV_P" && chipnumber == 1){
	    if (IsDir(ls_path + dn)){
	      list.push_back(ScanDef(dn, ls_path + dn, -1, 1, UsbPixIV, tced, IVScan, pp));
	    }else{
	      list.push_back(ScanDef(dn, ls_path + dn, -1, 1, LabViewIV, tced, IVScan, pp));
	    }
	  }
        }
      }
      
      closedir(dp);
    }
  }
  */
  // Enumerate all USBPix convertet scans
  {
    std::string ls_path(this->database_path);
    ls_path.append("/modules/");
    ls_path.append(ModuleId);
    ls_path.append("/usb_rt/");
    
    DIR *dp;
    struct dirent *dirp;
    
    if((dp  = opendir(ls_path.c_str())) == NULL) {
//      std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << ls_path << std::endl << std::flush;
    }else{
      while ((dirp = readdir(dp)) != NULL) {
        std::string dn(dirp->d_name);
        if (dn.compare(".") and dn.compare("..")){
          if (IsDir(ls_path + dn)){
            std::string ls_path2(ls_path);
	    //ls_path2.append("/");
            ls_path2.append(dn);
            ls_path2.append("/");
	    
	  

            DIR *dp2;
            struct dirent *dirp2;
	    //std::cout<<"stave1 check:"<<ls_path2.c_str()<<std::endl;
            if((dp2  = opendir(ls_path2.c_str())) == NULL) {
	      std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << ls_path2 << std::endl << std::flush;
            }else{
		//std::cout<<"stave1 check:"<<ls_path2.c_str()<<std::endl;
              while ((dirp2 = readdir(dp2)) != NULL) {
                std::string dn2(dirp2->d_name);
		
                if (dn2.compare(".") and dn2.compare("..")){
                  if (IsDir(ls_path2 + dn2)){
		    //std::cout<<"PATH IS: "<<dn2<<std::endl;
		    //         WORK IN PROGRESS
		    //                    int histonumber = -1; // @todo
                    int histonumber = ReadHistoNumber(ls_path2 + dn2 + "/globalconfig.txt", chipnumber, ModuleId);
		   
		    int hvon = GuessHVFlagFromPrimlistName(dn2);
		    ScanType scantype = GuessScanTypeFromPrimlistName(dn2);
		   
		    list.push_back(ScanDef(dn2, ls_path2 + dn2, histonumber, hvon, UsbPixReceptionTest, 0, scantype, PP_UsbPixReceptionTest));
                  }
                }
              }
              closedir(dp2);
            }
          }
        }
      }
      closedir(dp);
    }
  }
  return 0;
}
   
ScanType DbTools::GuessScanTypeFromName(std::string name)
{
  const struct {
    const ScanType tp;
    const char* prefix;
  } 

  prefices [] = {
    // Old definition
    {ThresholdScan, "Threshold_Scan_"}, 
    {AnalogTest, "Analog_Test_"}, 
    {DigitalTest, "Digital_Test_"}, 
    {CrosstalkScan, "Crosstalk_Scan_"}, 
    {IVScan, "IV_Scan_"},
    // New definition
    {ThresholdScan, "THRESHOLD_SCAN_"}, 
    {AnalogTest, "ANALOG_TEST_"}, 
    {DigitalTest, "DIGITAL_TEST_"}, 
    {CrosstalkScan, "CROSSTALK_SCAN_"}, 
    {IVScan, "IV_Scan_"}, 
  };
  int nent = sizeof(prefices)/sizeof(prefices[0]); 
  for (int iii = 0; iii < nent; iii++){
    if (!name.compare(0, strlen(prefices[iii].prefix), prefices[iii].prefix)){
      return prefices[iii].tp;
    }
  }
  return Unknown;
}

ScanType DbTools::GuessScanTypeFromPrimlistName(std::string name)
{
  const struct {
    const ScanType tp;
    const char* prefix;
  } prefices [] = {
    {ThresholdScan, "Threshold"}, 
    {AnalogTest, "Analog"}, 
    {DigitalTest, "Digital"}, 
    {CrosstalkScan, "X-Talk"}, 
    {IVScan, "IV"}, 
    // If you add a line here, remember to increase the upper limit for the
    // next for loop!
  };

  int nent = sizeof(prefices)/sizeof(prefices[0]); 
  for (int iii = 0; iii < nent; iii++)
    {
      if (!name.compare(0, strlen(prefices[iii].prefix), prefices[iii].prefix))
	{
	  return prefices[iii].tp;
	}
    }
  return Unknown;
}

int DbTools::GuessHVFlagFromPrimlistName(std::string name)
{
  const struct {
    const int hvon; 
    const char* part;
  } parts [] = {
    {1, "with HV"}, 
    {0, "no HV"}, 
    {1, "with_HV"}, 
    {0, "no_HV"}, 
    {1, "Digital_HV"}, 
    {1, "Digtal HV"}, 
    {1, "IV-Measurement ON"}, 
    {0, "IV-Measurement"},    
    // If you add a line here, remember to increase the upper limit for the
    // next for loop!
  };

  int nent = sizeof(parts)/sizeof(parts[0]); 


  for (int iii = 0; iii < nent; iii++)
    {
   
      if (name.find(parts[iii].part) != std::string::npos)
	{
    
	  return parts[iii].hvon;
	}
    
    }
  return -1;
}


int DbTools::ReadHistoNumber(std::string globalconfigfile,  int chipnumber, std::string moduleid)
{
  // Will contain the currently processed line
  std::string line;
  
  // The input file stream for reading the globalconfig.txt
  std::ifstream gc(globalconfigfile.c_str());
  //std::cout<<"MODULE ID Before CORRECTION FOR DC: "<<moduleid<<std::endl;
  
  if(moduleid[0]=='D'){
	
	moduleid = moduleid.substr(1,moduleid.size()-1);
  //      std::cout<<"MODULE ID CORRECTION FOR DC: "<<moduleid<<std::endl;
  }  
  int nchip = 0;
  if (gc.is_open()) {
    while(gc >> line){
      if(line.compare(moduleid) > 0) nchip++;
    }
  }
  gc.close();

  if(nchip == 1) nchip = 2;
  else if(nchip == 2) nchip = 1;
  return nchip;
}


int DbTools::GetAvailableProcessPrositions(std::string module_id, int chipnumber, std::vector<ProcessPosition> &process_positions)
{
  std::vector<ScanDef> scandefs;
  GetScanList(module_id, chipnumber, scandefs);
  for (std::vector<ScanDef>::iterator i = scandefs.begin(); i != scandefs.end(); i++)
    {
      int found = 0;
      for (std::vector<ProcessPosition>::iterator j = process_positions.begin(); j != process_positions.end(); j++)
	{
	  if ((*i).processPosition == (*j))
	    {
	      found = 1;
	      break;
	    }
	}
      if (!found)
	{
	  std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl << std::flush;
	  process_positions.push_back((*i).processPosition);
	}
    }
  return 0;
}

std::string DbTools::DatabasePath(){
  std::cout <<this->database_path<<std::endl;
  return this->database_path;
}
std::vector<std::string> DbTools::GetScanList_IV(std::string ModuleId, ProcessPosition asource)
{
  std::vector <std::string> list;

    std::string ls_path(this->database_path);
//    ls_path.append("/modules/");
//    ls_path.append(ModuleId);
    ls_path.append("/staves/");
    ls_path.append("stave");
    ls_path.append(ModuletoStave(ModuleId));
    ls_path.append("/");

//    ProcessPosition pp;
    if (asource ==   PP_StaveTestAfterTC_AT || asource ==   PP_StaveTestAfterTC_BT){
      ls_path.append("after_tc/");
    }else{
      ls_path.append("before_tc/");
    }
    ls_path.append("IV/");
    
    DIR *dp;
    struct dirent *dirp;
    
    if((dp  = opendir(ls_path.c_str())) == NULL) {
      std::cerr << __FILE__ << ":" << __LINE__ << " " << "Error(" << errno << ") opening " << ls_path << std::endl << std::flush;
    }else{
      while ((dirp = readdir(dp)) != NULL) {
        std::string dn(dirp->d_name);
        if (dn.compare(".") and dn.compare("..")){
	  if(dn.find("IV_3") != std::string::npos || dn.find("IV_P")!= std::string::npos )
	    list.push_back(ls_path+dn);
	}
      }
      closedir(dp);
    }
  
  return list; 
}
std::string DbTools::ModuletoStave(std::string ModuleId){

    std::string staveloading_dir = this->database_path;
    std::vector <std::string> staveloading_filename;
    std::ostringstream sname, stavenum;
    std::string sdir;
    
    std::string line;
    bool check=false;
    
    std::string dn(ModuleId);
    check=false;
    for(int i=0;i<25;i++){
        int j = i-1;
        sname.str("");
        sname << "/stave" << j <<"_loading.txt";
        sdir = staveloading_dir + sname.str();
        std::ifstream staveloading_files(sdir.c_str());
            
        while(std::getline(staveloading_files, line))  // remember this idiom!!
            {
                if (line.substr(0, dn.length()) == dn){  // not so efficient
                    check=true;
                    stavenum<<j;
                    std::cout<<"STAVE NUMBER: "<<stavenum.str()<<std::endl;
                    return stavenum.str();
                }
                
            }
        }
        
    return NULL;



}
/*twidth=2 tabstop=2 expandtab: */
