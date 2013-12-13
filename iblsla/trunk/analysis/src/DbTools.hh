#if !defined(_DB_TOOLS_H)
#define _DB_TOOLS_H

#include <string>
#include <vector>
#include <stdio.h>
#include "ScanDef.hh"

class DbTools
{
  private:
 
   DbTools(){};
    DbTools(DbTools const&){};
    ~DbTools(){};


    static DbTools* instance;
    
    static int IsDir(std::string file);
    
    static int ReadHistoNumber(std::string globalconfigfile,  int chipnumber, std::string moduleid);
  
  public:
    static DbTools* GetInstance();
    static DbTools* configure(std::string path);
  	std::string database_path;


  public:
  int GetModuleIdList(std::vector<std::string> &list);
  int GetModuleIdList2(std::vector<std::string> &list);
  int GetStaveIdList(std::vector<std::string> &list);
  int GetScanList(std::string ModuleId, int chipnumber, std::vector<ScanDef> &list);
  std::vector<std::string> GetScanList_IV(std::string ModuleId, ProcessPosition asource);
    std::string ModuletoStave(std::string ModuleId);

    int IsDoubleChip(std::string module_id);
    int GetAvailableProcessPrositions(std::string module_id,int chipnumber, std::vector<ProcessPosition> &process_positions);
    std::string DatabasePath();
//	int GetAvailableProcessPrositionsStave(std::string module_id, std::vector<ProcessPosition> &process_positions);
    
  public:
    static ScanType GuessScanTypeFromName(std::string name);
    static ScanType GuessScanTypeFromPrimlistName(std::string name);
    static int GuessHVFlagFromPrimlistName(std::string name);
};

#endif /* #if !defined(_DB_TOOLS_H) */
 /* vim:set shiftwidth=2 tabstop=2 expandtab: */
