//
//  File.h
//  
//
//  Created by Antu on 06/12/12.
//
//

#ifndef _IBLSLA_SR1CONVERTER_H
#define _IBLSLA_SR1CONVERTER_H

#include <TObject.h>
#include <stdio.h>
#include <HistoReader.hh>
#include <TGraph.h>
#include <ScanDef.hh>
#include <Astave.hh>

void Sr1_converter_main(Astave *stave_info_withHV, Astave *stave_info_withoutHV, ProcessPosition asource);



#endif
