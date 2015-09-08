//
//  printResults.h
//  rooFitTest
//
//  Created by Jesus Orduna on 10/28/12.
//  Copyright (c) 2012 Rice University. All rights reserved.
//

#ifndef __rooFitTest__printResults__
#define __rooFitTest__printResults__

#include <iostream>

#include <cmath> // to use: double abs (double x);
#include <math.h> // to use: pow and log10


#ifndef __CINT__
#define __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "TH1.h"

void sigEvts(RooDataSet *dataSet, RooRealVar *fraction);
void decayLength(RooRealVar *realVar);
void decayLengthMicrometer(RooRealVar *realVar);

// To print results in LaTeX code
// --- Left here for backward compatibility (begin) ---
void printTexLine(RooRealVar *realVar, std::string variableName);
void printTexLineDecayLength(RooRealVar *realVar, std::string variableName);
void printTexLineDecayLengthMicrometer(RooRealVar *realVar, std::string variableName);
// --- Left here for backward compatibility (end) ---

void printTexLine(RooRealVar *realVar, RooFitResult *theFitResult);
void printTexLineSigEvts(RooDataSet *dataSet, RooRealVar *fraction);
void printTexLineDecayLength(RooRealVar *realVar, std::string variableName, RooFitResult *theFitResult);
void printTexLineDecayLengthMicrometer(RooRealVar *realVar, std::string variableName, RooFitResult *theFitResult);
void printStatistics(RooDataSet *dataSet, RooRealVar *realVar, int nBins);
void printStatistics(RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2);
void printStatisticsPar(RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2, const RooArgList &variables);

// To format numbers for LaTeX use
std::ostream& formatNumber(double number, std::ostream& out);

#endif /* defined(__rooFitTest__printResults__) */
