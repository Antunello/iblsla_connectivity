//! @file Example1.cxx
//! @brief USBPix to RCE converter
//! @author Johannes Agricola <jagricol@cern.ch>

// Pixlib includes
#include <DataContainer/PixDBData.h>
#include "PixConfDBInterface/PixConfDBInterface.h"
#include "PixConfDBInterface/RootDB.h"
#include "PixController/PixScan.h"
#include "GeneralDBfunctions.h"

// Root stuff
#include <TH2F.h>
#include <TGraph.h> 
#include <TTree.h> 
#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>

// STL stuff
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

// Windows stuff
#include <direct.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <typeinfo>

using namespace PixLib;
using namespace std;

/*! Checks if a directory does already exist (using Microsoft's posix emulation)
 * @param absolutePath The absolute path to the directory 
 * @return true iff directory exists
 */
bool DirectoryExists( const char* absolutePath )
{
	if( _access( absolutePath, 0 ) == 0 )
	{
		struct stat status;
		stat( absolutePath, &status );

		return (status.st_mode & S_IFDIR) != 0;
	}
	return false;
}

/*! A class that contains the description of one scan.
 */
class scandef{
	public:
		/*! The file name containing the scan */
		string FileName;
		
		/*! The scan name */
		string ScanName;

		/*! The name of the module group */
		string GroupName;

		/*! The actual module identifier */
		string ModuleName;
};

/*! The list of scans accumulated by listScans */
list<scandef*> *scans;

/*! -1 if no data has been read (or it was empty), 
 * 0 if we are dealing with single chip modules, 
 * 1 if we are dealing with double chip modules 
 */
int double_chips = -1;

/*! -1 if no data has been read (or it was empty), else
 * the number of modules enabled.
 */
int module_count = -1;

/*! Searches for a duplicate module name
 * @param ModuleName The module name to search for
 * @return 1 if the module is already in the *scans list
 */
int moduleNameDuplicate(string ModuleName)
{
	list<scandef *>::iterator lit;
	for (lit = scans->begin(); lit != scans->end(); lit++)
	{
		if ((*lit)->ModuleName == ModuleName)
		{
			return 1;
		}
	}
	return 0;
}

/*! Searches for a duplicate scan name
 * @param ScanName The scan name to search for
 * @return 1 if the scan is already in the *scans list
 */
int scanNameDuplicate(string ScanName)
{
	list<scandef *>::iterator lit;
	for (lit = scans->begin(); lit != scans->end(); lit++)
	{
		if ((*lit)->ScanName == ScanName)
		{
			return 1;
		}
	}
	return 0;
}

/*! Lists all scans contained in a USBPix db file. The result will be written to *scans.
 * @param fname The filename of the USBPix db file to be analyzed
 */
void listScans(string fname){
	string sname, gname, mname;
	scandef * scd;

	int temporary_module_count = 0;

	// Open the rootdb defined by fname and search for records of name "PixScanResult":
	RootDB *db = new RootDB(fname.c_str());
	DBInquire *root = db->readRootRecord(1);
	for(recordIterator i = root->recordBegin(); i!=root->recordEnd();i++){
		if((*i)->getName()=="PixScanResult"){
			
			// Retrieve the decorated name of the record and remove decorations
			// to get the scan name:	
			sname = (*i)->getDecName();
			getDecNameCore(sname);

			cerr << "NEW SCAN: \"" << sname << "\"" << endl;
			
			// Now search for "PixModuleGroup" records within the scan record.
			for(recordIterator ii = (*i)->recordBegin(); ii!=(*i)->recordEnd();ii++){
				if((*ii)->getName()=="PixModuleGroup"){
					// Retrieve the decorated name of the record and remove decorations
					// to get the module group name:
					gname = (*ii)->getDecName();
					getDecNameCore(gname);
					cerr << "  with module group: " <<  gname << endl;
					
					// Iterate over all records within the module group and search for
					// PixModule records:
					for(recordIterator iii = (*ii)->recordBegin(); iii!=(*ii)->recordEnd();iii++){
						if((*iii)->getName()=="PixModule"){
							
							// Retrieve the decorated name of the record and remove decorations
							// to get the module group name:
							mname = (*iii)->getDecName();
							getDecNameCore(mname);
							
							cerr << "     with module: " <<  mname << endl;

							// Count number of modules
							if (module_count == -1)
							{
								temporary_module_count++;
							}

							// Check if the module has multiple scans with the same name. If
							// this is the case, we are probably dealing with double chip modules
							//if (double_chips == -1)
							//{
							//	if (moduleNameDuplicate(mname))
							//	{
							//		double_chips = 1;
							//	}
							//}
							
							// create a new scandef record and put in all information
							// needed to retrieve the scan later on. Then add this
							// scandef to the *scans list.
							scd = new scandef(); 
							if (scd != NULL)
							{
								scd->ScanName = sname;
								scd->GroupName = gname;
								scd->ModuleName = mname;
								scd->FileName = fname;
								scans->push_back(scd);
							}
							else
							{
								// todo: throw exception
							}
						}
					}
					// We are only scanning for double chip modules in the first scan and first module
					// group. So disallow any scans afterwards.
					//double_chips = double_chips == 1;
					
					// Transfer temporary chip count if we did not count until now.
					if (module_count == -1)
					{
						module_count = temporary_module_count;
					}
				}
			}
		}
	}
	delete db;
}


void addPlotToFile(TH2F * plot, string name, string target_filename)
{
	std::cerr << "." << std::flush;
	TFile *tgt = new TFile(target_filename.c_str(), "UPDATE");
	std::cerr << "." << std::flush;
	tgt->cd();
	std::cerr << "." << std::flush;
	plot->Write(name.c_str());
	std::cerr << "." << std::flush;
	tgt->Close();
	std::cerr << "." << std::flush;
	delete tgt;
	std::cerr << "." << std::flush;
}

void addPlotToFile(TGraph * plot, string name, string target_filename)
{
	std::cerr << "." << std::flush;
	TFile *tgt = new TFile(target_filename.c_str(), "UPDATE");
	std::cerr << "." << std::flush;
	tgt->cd();
	std::cerr << "." << std::flush;
	plot->Write(name.c_str());
	std::cerr << "." << std::flush;
	tgt->Close();
	std::cerr << "." << std::flush;
	delete tgt;
	std::cerr << "." << std::flush;
}

/*! Gets the RCE-like histogram name for a scan.
 * @param data Any arbitrary PixDBData object
 * @param histotype The histogram type 
 * @return If known, a RCE-like Histogram name, otherweise the histotype as string.
 */
string getRCEHistoName(PixDBData &data, PixScan::HistogramType histotype)
{
	switch(histotype)
	{
		case PixScan::OCCUPANCY:
			return string("Occupancy_Point_001");
			break;
		case PixScan::SCURVE_MEAN:
			return string("Mean");
			break;
		case PixScan::SCURVE_CHI2:
			return string("ChiSquare");
			break;
		default:
			return string(data.getHistoName(histotype));
			break;
	}
}

/*! Plots one Graph associated with a scan and adds them to the 'target_filename' root file
 * @param scd A scan definition
 * @param data The PixDBData object containing the scan result
 * @param target_filename The name of the root file the scan should be stored in.
 * @param scanprefix The prefix to be prepended to the object name in the root file.
 * @param graphid The id of the Graph.
 */
void plotGraph(scandef *scd, PixDBData &data, string target_filename, string scanprefix, int graphid)
{
	TGraph * myData;
	TGraph * myPlot; 
	std::cerr << "> > 0" << std::flush;
	myData = data.GetGraph(graphid);
	std::cerr << "." << std::flush;
	
	if (!myData)
	{
		std::cerr << " no data :( " << std::flush;
	}
	else
	{
		myPlot = new TGraph(*(myData));
		std::cerr << "." << std::flush;
		addPlotToFile(myPlot, scanprefix + "graph", target_filename);
		std::cerr << "." << std::flush;
	}
	std::cerr << std::endl << std::flush;
}

/*! Plots all Graphs associated with a scan and adds them to the 'target_filename' root file
 * @param scd A scan definition
 * @param data The PixDBData object containing the scan result
 * @param target_filename The name of the root file the scan should be stored in.
 * @param scanprefix The prefix to be prepended to the object name in the root file.
 */
void plotGraphs(scandef *scd, PixDBData &data, string target_filename, string scanprefix)
{
	int i;
	int ngraphs;
	const int NGRAPH = 1;
	
	std::cerr << "> > Counting: " << std::flush;
	for(i = 0; i < NGRAPH; i++)
	{
		if(data.GetGraph(i)==NULL) break;
		std::cerr << "." << std::flush;
	}
	ngraphs = i;
	std::cerr << " " << ngraphs << std::endl;
	
	for (i = 0; i < ngraphs; i++)
	{
		plotGraph(scd, data, target_filename, scanprefix, i);
	}
}

/*! Plots all Graphs associated with a scan and adds them to the 'target_filename' root file
 * @param scd A scan definition
 * @param int The chip id (-1 for all chips, 0, 1, ... for specific chips)
 * @param data The PixDBData object containing the scan result
 * @param target_filename The name of the root file the scan should be stored in.
 * @param scanprefix The prefix to be prepended to the object name in the root file.
 */
int plotHisto(scandef *scd, int chip, PixDBData &data, PixScan::HistogramType histotype, string target_filename, string scanprefix, int find_module_width)
{
	TH2F * myData;
	TH2F * myPlot; 
	std::cerr << "0" << std::flush;
	myData = data.GetMap(chip, histotype, -1);
	std::cerr << "." << std::flush;
	if (!myData) 
	{
		std::cerr << "1" << std::flush;
		myData = data.GetMap(chip, histotype, 0);
		std::cerr << "." << std::flush;
	}	
	if (!myData) 
	{
		std::cerr << "2" << std::flush;
		myData = data.GetMap(-1, histotype, -1);
		std::cerr << "." << std::flush;
	}	
	if (!myData) 
	{
		std::cerr << "3" << std::flush;
		myData = data.GetMap(-1, histotype, 0);
		std::cerr << "." << std::flush;
	}	
	
	if (!myData)
	{
		std::cerr << " no data " << std::endl << std::flush;
		return 0;
	}
	else
	{
		myPlot = new TH2F(*(myData));
		std::cerr << "." << std::flush;
		if (find_module_width)
		{
			std::cerr << "Found a histogram with width: " << myPlot->GetNbinsY();
			if (myPlot->GetNbinsY() == 160)
			{
				double_chips = 1;
			}
			else if(myPlot->GetNbinsY() == 80)
			{
				double_chips = -1;
			}
		}
		else
		{
			addPlotToFile(myPlot, scanprefix + getRCEHistoName(data, histotype), target_filename);
		}
		std::cerr << "." << std::flush;
		myData->Reset();
		myPlot->Reset();
	}
	std::cerr << std::endl << std::flush;
	return 1;
}

void detectDoubleChips(scandef *scd)
{
	PixDBData data("scan", (scd->FileName + ":/" + scd->ScanName+"/"+scd->GroupName).c_str(), scd->ModuleName.c_str());
	Config &cfg = data.getModConfig().subConfig("PixFe_1/PixFe");
	std::cerr << cfg.type() << std::endl << std::flush;
	double_chips = !(std::string(cfg.type()) == "__TrashConfig__");
}


/*! Plots a single scan given a scandef and a target filename.
 * @param scd pointer to a scandef scan definition.
 * @param target_filename the output root file.
 */
void plotScan(scandef *scd, string target_filename, int find_module_width)
{
	string modprefix = "Mod_";
	// Iterate over all chips on the module
	// @todo: Try to guess the actual number of chips per module. 
	for (int i = (find_module_width ? -1 : 0); i < (find_module_width ? 0 : (double_chips + 1); i++)
	{
		// Construct the prefix for each scan, which will be something like "Mod_1_", ...
		std::stringstream scanprefix_ss;
		scanprefix_ss << modprefix << (i + 1) << "_";
		string scanprefix = scanprefix_ss.str();
		
		std::cerr << "Data from " << scd->FileName << " scan " << scd->ScanName << " module group " << scd->GroupName << " module " << scd->ModuleName << std::endl;
		
		// Get the scan PixDBData object from the file using the data from the scan definiton
		PixDBData data("scan", (scd->FileName + ":/" + scd->ScanName+"/"+scd->GroupName).c_str(), scd->ModuleName.c_str());
		
		// Extract the parameter over which the scan was performed.
		// Depending on that parameter, different plots will be performed.
		string scanpar;
		scanpar = data.getScanPar(0);
		std::cerr << "> Scan par: " << scanpar << std::endl;
		
		std::cerr << "> Plotting histos: " << std::endl << std::flush;
		for (PixScan::HistogramType histotype = PixScan::OCCUPANCY; histotype != PixScan::MAX_HISTO_TYPES; histotype = static_cast<PixScan::HistogramType>(histotype+1))
		{
			if (data.haveHistoType(histotype))
			{
				std::cerr << "> > Type: " << data.getHistoName(histotype) << " " << std::flush;
				plotHisto(scd, i, data, histotype, target_filename, scanprefix, find_module_width);
			}
		}
		if (!(find_module_width) && (i == 0))
		{
			std::cerr << "> Plotting graphs: " << std::endl << std::flush;
			plotGraphs(scd, data, target_filename, scanprefix);
		}
	}
}

void writeRCEConfig(scandef *scd, string filename)
{
	std::cerr << "> Creating config: " << filename << std::endl;
	ofstream f(filename.c_str(), ios::out);
	f << scd->ModuleName.c_str() << "__fe0.cfg" << std::endl;
	f << "1" << std::endl;
	f << "0" << std::endl;
	f << "0" << std::endl;
	f << "0" << std::endl;
	f << "0" << std::endl;
	if (double_chips)
	{
		f << scd->ModuleName.c_str() << "__fe1.cfg" << std::endl;
		f << "1" << std::endl;
		f << "0" << std::endl;
		f << "0" << std::endl;
		f << "0" << std::endl;
		f << "0" << std::endl;
	}
}

void main(int argc, char ** argv)
{
	string usbpixsrcfile, rcetargetdir;
	TROOT root("myroot","myroot");
	TApplication MonApp("myapp",0,0);
	list<scandef *>::iterator lit;

	if (argc < 3)
	{
		std::cerr << "Usage: " << std::endl << "  " << argv[0] << " <USBPix scan result file> <target directory>" << std::endl;
		exit(1);
	}

	usbpixsrcfile = argv[1];
	rcetargetdir = argv[2];

	try {
		scans = new list<scandef *>();
		listScans(usbpixsrcfile);
		std::cerr << "Number of modules involved in this scan: " << module_count << std::endl << std::flush;
		for (lit = scans->begin(); (double_chips == -1) && (lit != scans->end()); lit++)
		{
			detectDoubleChips(*lit);
			//plotScan(*lit, rcetargetdir + "/" + (*lit)->ScanName + "/histos.root", 1);
		}	
		std::cerr << "Double chips: " << double_chips << std::endl << std::flush;
		for (lit = scans->begin(); lit != scans->end(); lit++)
		{
			if (!DirectoryExists((rcetargetdir + "/" + (*lit)->ScanName).c_str()))
			{
				if (-1 == _mkdir((rcetargetdir + "/" + (*lit)->ScanName).c_str()))
				{
					std::cerr << "Could not create target directory." << std::endl << std::flush;
					exit(1);
				}
			}
			plotScan(*lit, rcetargetdir + "/" + (*lit)->ScanName + "/histos.root", 0);
		}	
		for (lit = scans->begin(); lit != scans->end(); lit++)
		{
			writeRCEConfig(*lit, rcetargetdir + "/" + (*lit)->ScanName + "/globalconfig.txt");
		}	
		for (lit = scans->begin(); lit != scans->end(); lit++)
		{
			delete *lit;
		}	
		delete scans;
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl << std::flush;
	}
	catch (...) {
		std::cerr << "Caught unknown exception." << std::endl << std::flush;
	}
	std::cerr << "Finished successfully :) (who would have thought it...)" << std::endl << std::flush;
}

