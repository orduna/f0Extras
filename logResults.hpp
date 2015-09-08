//
//  logResults.h
//  rooFitTest
//
//  Created by Jesus Orduna on 11/8/12.
//  Copyright (c) 2012 Rice University. All rights reserved.
//

#ifndef __rooFitTest__logResults__
#define __rooFitTest__logResults__

#include <iostream>
#include <fstream>

#ifndef __CINT__
#define __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooRealVar.h"
#include "TH1.h"

std::ostream& logPDF(std::ostream& out, double number);
void logStatistics(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins);
void logStatistics(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2);
void logStatisticsPar(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2, const RooArgList &variables);
void makePDF(std::string texInputFile);
void makePDF(std::string texInputFile, std::string prefix);
#endif /* defined(__rooFitTest__logResults__) */
