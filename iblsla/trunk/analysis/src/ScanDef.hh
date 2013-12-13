#if !defined(_IBLSLA_SCANDEF_H)
#define _IBLSLA_SCANDEF_H

#include <string>
enum ScanSource
{
  RCEReceptionTest, 
  UsbPixReceptionTest, 
  StaveTest,
  UsbPixIV,
  LabViewIV
};

enum ScanType
{
  ThresholdScan,
  AnalogTest,
  DigitalTest,
  CrosstalkScan,
  IVScan,

  Unknown
};

enum ProcessPosition
{
  PP_RCEReceptionTest, 
  PP_UsbPixReceptionTest, 
  PP_StaveTestBeforeTC_AT,
  PP_StaveTestAfterTC_AT,
  PP_StaveTestBeforeTC_BT,
  PP_StaveTestAfterTC_BT,
  PP_Unknown
};

class ScanDef
{
  public:
    ScanDef(
      std::string Name,
      std::string Path,
      int HistogramNumber,
      int HvOn,
      ScanSource Source,
      int AfterTc,
      ScanType aType,
      ProcessPosition processPosition
    );
    ScanDef();

    std::string Name;
    std::string Path;
    int HistogramNumber;
    int HvOn;
    ScanSource Source;
    int AfterTc;
    ScanType aType;
    ProcessPosition processPosition;

    static std::string ScanTypeToString(ScanType scantype);
};

#endif /* #if !defined(_IBLSLA_SCANDEF_H) */
 /* vim:set shiftwidth=2 tabstop=2 expandtab: */
