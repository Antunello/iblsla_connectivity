/**
 * Check if we are interpreting right now. If we are, include the
 * whole class definition, otherwise the declaration suffices
 */
#ifdef __CINT__ 
  #include "MainGui.cc"
  #include "HistoReader.cc"
  #include "DbTools.cc"
  #include "ScanDef.cc"
  #include "Astave.cc"
#else
  #include "MainGui.hh"
  #include "HistoReader.hh"
  #include "DbTools.hh"
  #include "ScanDef.hh"
  #include "Astave.hh"
#endif


#include "TApplication.h"
#include <string>
#include <iostream>

int main(int argc, char ** argv)
{
  std::string db_path = "/RAID/samba/IBLdata";
  if (argc > 1)
  {
    db_path.assign(argv[1]);
  }
  std::cout << "Using database path: " << db_path << std::endl << std::flush;
  DbTools::configure(db_path);

//Test module list
//  std::vector<string> foo;
//  DbTools::GetInstance()->GetModuleIdList(foo); 
//  for (std::vector<string>::iterator i = foo.begin(); i != foo.end(); i++)
//  {
//    std::cerr << *i << std::endl << std::flush;
//  }
    
//Test stave list
//  std::vector<string> foo;
//  DbTools::GetInstance()->GetStaveIdList(foo); 
//  for (std::vector<string>::iterator i = foo.begin(); i != foo.end(); i++)
//  {
//    std::cerr << *i << std::endl << std::flush;
//  }
  
// Test Scan list generation
//  std::vector<ScanDef> foo;
//  
//  DbTools::GetInstance()->GetScanList(std::string("66-11-02"), 0, foo);
//  for (std::vector<ScanDef>::iterator i = foo.begin(); i != foo.end(); i++)
//  {
//    std::cerr << "Scan: " << (*i).Name << " at " << (*i).Path << " hv: " << (*i).HvOn << " Histogram Number: " << i->HistogramNumber << std::endl << std::flush;
//  }
//  
//  foo.clear();
//  DbTools::GetInstance()->GetScanList(std::string("66-11-02"), 1, foo);
//  for (std::vector<ScanDef>::iterator i = foo.begin(); i != foo.end(); i++)
//  {
//    std::cerr << "Scan: " << (*i).Name << " at " << (*i).Path << " hv: " << (*i).HvOn << " Histogram Number: " << i->HistogramNumber << std::endl << std::flush;
//  }

//Test double chip detection
//  cout << "Double chip: " << DbTools::GetInstance()->IsDoubleChip(std::string("17-4-28")) << std::endl << std::flush;

  TApplication theApp("App", &argc, argv);
  new MainGui();
  theApp.Run();
}
 /* vim:set shiftwidth=2 tabstop=2 expandtab: */
