//
//  printResults.cpp
//  rooFitTest
//
//  Created by Jesus Orduna on 10/28/12.
//  Copyright (c) 2012 Rice University. All rights reserved.
//

#include "printResults.hpp"

void sigEvts(RooDataSet *dataSet, RooRealVar *fraction)
{
    int numEntries = dataSet->numEntries();
    std::cout << "printResults: " << fraction->GetTitle() << "*Entries(" << dataSet->GetName() << ") = " << numEntries*fraction->getValV() ;
    std::cout << " +/- " << numEntries*fraction->getError() ;
    std::cout << "  L(" << numEntries*fraction->getMin() << " - " << numEntries*fraction->getMax() << ")" << std::endl;
}

void decayLength(RooRealVar *realVar)
{
    std::cout << "printResults: -10,000 / " << realVar->GetName() << " = " << -10000.0/realVar->getValV() ;
    std::cout << " +/- " << 10000.0*realVar->getError()/(realVar->getValV()*realVar->getValV()) ;
    std::cout << "  L(" << -10000.0/realVar->getMin() << " - " << -10000.0/realVar->getMax() << ") {µm}. [ " ;
    std::cout << -10000.0/(299.792458*realVar->getValV()) << " +/- " << 10000.0*realVar->getError()/(299.792458*realVar->getValV()*realVar->getValV()) ;
    std::cout << "  L(" << -10000.0/(299.792458*realVar->getMin()) << " - " << -10000.0/(299.792458*realVar->getMax()) << ") {ps} ]" << std::endl;
}

void decayLengthMicrometer(RooRealVar *realVar)
{
    std::cout << "printResults: 10,000 * " << realVar->GetName() << " = " << 10000.0*realVar->getValV() ;
    std::cout << " +/- " << 10000.0*realVar->getError() ;
    std::cout << "  L(" << 10000.0*realVar->getMin() << " - " << 10000.0*realVar->getMax() << ") {µm}. [ " ;
    std::cout << 10000.0*realVar->getValV()/299.792458 << " +/- " << 10000.0*realVar->getError()/299.792458 ;
    std::cout << "  L(" << 10000.0*realVar->getMin()/299.792458 << " - " << 10000.0*realVar->getMax()/299.792458 << ") {ps} ]" << std::endl;
}

// For backwards compatibility. This one prints the mean of the variable
// range as the initial value which is not always the case. Its new ver-
// sion prints the true initial value taken from RooFitResult which sto-
// res all the relevant info.
void printTexLine(RooRealVar *realVar, std::string variableName)
{
    // Name
    std::cout << "& " << variableName << " & " ;
    if ( realVar->isConstant() ) {
        std::cout << "\\multicolumn{3}{c}{Fixed} & \\multicolumn{2}{c}{" ;
        // Parameter value
        formatNumber(realVar->getValV(), std::cout) << "} \\\\" << std::endl;
    } else {
        // Initial value
        formatNumber((realVar->getMin()+realVar->getMax())/2.0, std::cout) << " & " ;
        // Minimum limit
        formatNumber(realVar->getMin(), std::cout) << " & " ;
        // Maximum limit
        formatNumber(realVar->getMax(), std::cout) << " & " ;
        // Parameter value
        formatNumber(realVar->getValV(), std::cout) << " & " ;
        // Parameter error
        formatNumber(realVar->getError(), std::cout) << " \\\\" << std::endl;
    }
}

void printTexLine(RooRealVar *realVar, RooFitResult *theFitResult)
{
    // Name
    std::cout << "& " << realVar->GetTitle() << " & " ;
    if ( realVar->isConstant() ) {
        std::cout << "\\multicolumn{3}{c}{Fixed} & \\multicolumn{2}{c}{" ;
        // Parameter value
        formatNumber(realVar->getValV(), std::cout) << "} \\\\" << std::endl;
    } else {
        // Initial value
        const RooArgList &parsAtStart = theFitResult->floatParsInit();
        RooRealVar *variableAtStart = dynamic_cast<RooRealVar*>(parsAtStart.find(realVar->GetName()));
        formatNumber(variableAtStart->getValV(), std::cout) << " & " ;
        // Minimum limit
        formatNumber(realVar->getMin(), std::cout) << " & " ;
        // Maximum limit
        formatNumber(realVar->getMax(), std::cout) << " & " ;
        // Parameter value
        formatNumber(realVar->getValV(), std::cout) << " & " ;
        // Parameter error
        formatNumber(realVar->getError(), std::cout) << " \\\\" << std::endl;
    }
}

void printTexLineSigEvts(RooDataSet *dataSet, RooRealVar *fraction)
{
    int numEntries = dataSet->numEntries();
    // Name, no initial value.
    std::cout << "& $\\textrm{N}_\\textrm{sig}$ & -- & " ;
    // Computed minimum limit
    formatNumber(numEntries*fraction->getMin(), std::cout) << " & " ;
    // Computed maximum limit
    formatNumber(numEntries*fraction->getMax(), std::cout) << " & " ;
    // Computed value
    formatNumber(numEntries*fraction->getValV(), std::cout) << " & " ;
    // Computed error
    formatNumber(numEntries*fraction->getError(), std::cout) << " \\\\" << std::endl;
}

// For backwards compatibility. This one prints the mean of the variable
// range as the initial value which is not always the case. Its new ver-
// sion prints the true initial value taken from RooFitResult which sto-
// res all the relevant info.
void printTexLineDecayLength(RooRealVar *realVar, std::string variableName)
{
    // Name
    std::cout << "& " << variableName << " & " ;
    if ( realVar->isConstant() ) {
        std::cout << "\\multicolumn{3}{c}{Fixed} & \\multicolumn{2}{c}{" ;
        // Parameter value
        formatNumber(-10000.0/realVar->getValV(), std::cout) << "} \\\\" << std::endl;
    } else {
        // Initial value
        formatNumber(-10000.0/((realVar->getMin() + realVar->getMax())/2.0), std::cout) << " & " ;
        // Minimum limit
        formatNumber(-10000.0/realVar->getMin(), std::cout) << " & " ;
        // Maximum limit
        formatNumber(-10000.0/realVar->getMax(), std::cout) << " & " ;
        // Parameter value
        formatNumber(-10000.0/realVar->getValV(), std::cout) << " & " ;
        // Parameter error
        formatNumber(10000.0*realVar->getError()/(realVar->getValV()*realVar->getValV()), std::cout) << " \\\\" << std::endl;
    }
}

void printTexLineDecayLength(RooRealVar *realVar, std::string variableName, RooFitResult *theFitResult)
{
    // Name
    std::cout << "& " << variableName << " & " ;
    if ( realVar->isConstant() ) {
        std::cout << "\\multicolumn{3}{c}{Fixed} & \\multicolumn{2}{c}{" ;
        // Parameter value
        formatNumber(-10000.0/realVar->getValV(), std::cout) << "} \\\\" << std::endl;
    } else {
        // Initial value
        const RooArgList &parsAtStart = theFitResult->floatParsInit();
        RooRealVar *variableAtStart = dynamic_cast<RooRealVar*>(parsAtStart.find(realVar->GetName()));
        formatNumber(-10000.0/variableAtStart->getValV(), std::cout) << " & " ;
        // Minimum limit
        formatNumber(-10000.0/realVar->getMin(), std::cout) << " & " ;
        // Maximum limit
        formatNumber(-10000.0/realVar->getMax(), std::cout) << " & " ;
        // Parameter value
        formatNumber(-10000.0/realVar->getValV(), std::cout) << " & " ;
        // Parameter error
        formatNumber(10000.0*realVar->getError()/(realVar->getValV()*realVar->getValV()), std::cout) << " \\\\" << std::endl;
    }
}

// For backwards compatibility. This one prints the mean of the variable
// range as the initial value which is not always the case. Its new ver-
// sion prints the true initial value taken from RooFitResult which sto-
// res all the relevant info.
void printTexLineDecayLengthMicrometer(RooRealVar *realVar, std::string variableName)
{
    // Name
    std::cout << "& " << variableName << " & " ;
    // Initial value
    formatNumber(10000.0*((realVar->getMin() + realVar->getMax())/2.0), std::cout) << " & " ;
    // Minimum limit
    formatNumber(10000.0*realVar->getMin(), std::cout) << " & " ;
    // Maximum limit
    formatNumber(10000.0*realVar->getMax(), std::cout) << " & " ;
    // Parameter value
    formatNumber(10000.0*realVar->getValV(), std::cout) << " & " ;
    // Parameter error
    formatNumber(10000.0*realVar->getError(), std::cout) << " \\\\" << std::endl;
}

void printTexLineDecayLengthMicrometer(RooRealVar *realVar, RooFitResult *theFitResult)
{
    // Name
    std::cout << "& " << realVar->GetTitle() << " & " ;
    // Initial value
    const RooArgList &parsAtStart = theFitResult->floatParsInit();
    RooRealVar *variableAtStart = dynamic_cast<RooRealVar*>(parsAtStart.find(realVar->GetName()));
    formatNumber(10000.0*variableAtStart->getValV(), std::cout) << " & " ;
    // Minimum limit
    formatNumber(10000.0*realVar->getMin(), std::cout) << " & " ;
    // Maximum limit
    formatNumber(10000.0*realVar->getMax(), std::cout) << " & " ;
    // Parameter value
    formatNumber(10000.0*realVar->getValV(), std::cout) << " & " ;
    // Parameter error
    formatNumber(10000.0*realVar->getError(), std::cout) << " \\\\" << std::endl;
}

void printStatistics(RooDataSet *dataSet, RooRealVar *realVar, int nBins)
{
    printStatisticsPar(dataSet, realVar, nBins, -1.0, RooArgList());
}

void printStatistics(RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2)
{
    printStatisticsPar(dataSet, realVar, nBins, chi2, RooArgList());
}

void printStatisticsPar(RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2, const RooArgList &variables)
{
    TH1 *histogram = dataSet->createHistogram(Form("h%s", dataSet->GetName()), *realVar, RooFit::Binning(nBins));
    std::cout << "Statistics for " << histogram->GetName() << std::endl << std::endl;
    std::cout << "\\begin{tabular}{|lr|}\\hline" << std::endl;
    std::cout << "Entries & " ;
    formatNumber(histogram->GetEntries(), std::cout) << " \\\\" << std::endl;
    std::cout << "Mean & " ;
    formatNumber(histogram->GetMean(), std::cout) << " \\\\" << std::endl;
    std::cout << "RMS & " ;
    formatNumber(histogram->GetRMS(), std::cout) << " \\\\" << std::endl;
    if (chi2 > 0.0) {
        std::cout << "Fit $\\chi^{2}$ & " ;
        formatNumber(chi2, std::cout) << " \\\\" << std::endl;
    }
    RooRealVar *theVariable;
    for (int index = 0; index < variables.getSize(); index++) {
        theVariable = dynamic_cast<RooRealVar*>(variables.find(variables[index].GetName()));
        std::cout << theVariable->GetTitle() << " & $\\textrm{" ;
        formatNumber(theVariable->getValV(), std::cout) << "} \\pm \\textrm{" ;
        formatNumber(theVariable->getError(), std::cout) << "}$ \\\\" << std::endl;
    }
    std::cout << "\\hline\\end{tabular}" << std::endl;
    histogram->Delete();
}

std::ostream& formatNumber(double number, std::ostream& out)
{
    if (number < 0.0) {
        out << '-' ;
        number *= -1.0;
    }
    int exponent = int(log10(number));
    if (exponent < -15) {
        out << "0" ;
    } else if (exponent < -2) {
        out << "$\\textrm{" << number/pow(10.0, exponent) << "} \\times \\textrm{10}^{-\\textrm{" << abs(exponent) << "}}$" ;
    } else if (exponent < 3) {
        out << number;
    } else if (exponent < 6) {
        double arg0 = number - 1000.0*int(number/1000);
        double arg1 = (number - arg0)/1000;
        out << arg1 << ',' ;
        if (arg0 == 0) {
            out << "000" ;
        } else {
            if (arg0 < 100) out << "0" ;
            if (arg0 < 10) out << "0" ;
            out << arg0 ;
        }
    } else {
        double arg0 = number - 1000.0*int(number/1000);
        double arg1 = (number - arg0)/1000;
        formatNumber(arg1, std::cout);
        out << "," << arg0 ;
    }
    return out;
}
