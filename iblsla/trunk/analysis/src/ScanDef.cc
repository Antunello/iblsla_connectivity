#include "ScanDef.hh"
ScanDef::ScanDef(
      std::string Name,
      std::string Path,
      int HistogramNumber,
      int HvOn,
      ScanSource Source,
      int AfterTc,
      ScanType aType,
      ProcessPosition processPosition
    )
{
  this->Name = Name;
  this->Path = Path;
  this->HistogramNumber = HistogramNumber;
  this->HvOn = HvOn;
  this->Source = Source;
  this->AfterTc = AfterTc;
  this->aType = aType;
  this->processPosition = processPosition;
}

ScanDef::ScanDef()
{

}

std::string ScanDef::ScanTypeToString(ScanType scantype)
{
  switch(scantype)
  {
    case ThresholdScan:
      return std::string("ThresholdScan");
    case AnalogTest:
      return std::string("AnalogTest");
    case DigitalTest:
      return std::string("DigitalTest");
    case CrosstalkScan:
      return std::string("CrosstalkScan");
    case IVScan:
      return std::string("IVScan");
    case Unknown:
      return std::string("Unknown");
    default:
      return std::string("<undefined>");
  }
}
 /* vim:set shiftwidth=2 tabstop=2 expandtab: */
