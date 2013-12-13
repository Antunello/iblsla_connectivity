////////////////////////////////////////////////////
// Class developed for Stave RT result comparison //
// Developed by: J. Agricola, J. Bilbao           //
// V 0.1 Jul 2012                                 //
////////////////////////////////////////////////////


#if !defined(_IV_MEASUREMENT_H)
#define _IV_MEASUREMENT_H

class IVMeasurementPoint {
public:
	double voltage;
	double current;
	
	
	IVMeasurementPoint (double voltage,double current){this->voltage=voltage;this->current=current;}
	
};

//std::vector<IVMeasurementPoint> foo[8];

#endif /* #if !defined(_IV_MEASUREMENT_H) */
 /* vim:set shiftwidth=2 tabstop=2 expandtab: */
