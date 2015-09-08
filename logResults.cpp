//
//  logResults.cpp
//  rooFitTest
//
//  Created by Jesus Orduna on 11/8/12.
//  Copyright (c) 2012 Rice University. All rights reserved.
//

#include "logResults.hpp"
#include "printResults.hpp"

std::ostream& logPDF(std::ostream& out, double number)
{
    out << number << ' ' ;
    return out;
}

void logStatistics(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins)
{
    logStatisticsPar(out, dataSet, realVar, nBins, -1.0, RooArgList());
}

void logStatistics(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2)
{
    logStatisticsPar(out, dataSet, realVar, nBins, chi2, RooArgList());
}

void logStatisticsPar(std::ostream& out, RooDataSet *dataSet, RooRealVar *realVar, int nBins, double chi2, const RooArgList &variables)
{
    TH1 *histogram = dataSet->createHistogram(Form("h%s", dataSet->GetName()), *realVar, RooFit::Binning(nBins));
    
    // Create the TeX file
    out << "\\documentclass[10pt]{article}" << std::endl;
    out << "\\usepackage[usenames]{color} %used for font color" << std::endl;
    out << "\\usepackage{fontspec}" << std::endl;
    out << "\\usepackage{xunicode}" << std::endl;
    out << "\\usepackage{xltxtra}" << std::endl;
    out << "\\defaultfontfeatures{Scale=MatchLowercase}" << std::endl;
    out << "\\setromanfont[Mapping=tex-text]{Myriad Pro}" << std::endl;
    out << "\\setsansfont[Mapping=tex-text]{Myriad Pro}" << std::endl;
    out << "\\setmonofont{Monaco}" << std::endl;
    out << "\\begin{document}" << std::endl;
    out << "\\thispagestyle{empty}" << std::endl;
    out << "\\setlength{\\tabcolsep}{1ex}" << std::endl;
    out << "\\setlength{\\fboxsep}{0ex}" << std::endl;
    out << "{\\fontsize{7pt}{0.9em}\\selectfont" << std::endl;
    out << "\\framebox{\\begin{tabular*}{60pt}{l@{\\extracolsep{\\fill}}r}" << std::endl;
    
    // This is the particular info for the histogram
    out << "Entries & " ;
    formatNumber(histogram->GetEntries(), out) << " \\\\" << std::endl;
    out << "Mean & " ;
    formatNumber(histogram->GetMean(), out) << " \\\\" << std::endl;
    out << "RMS & " ;
    formatNumber(histogram->GetRMS(), out) << " \\\\" << std::endl;
    if (chi2 > 0.0) {
        out << "Fit $\\chi^{2}$ & " ;
        formatNumber(chi2, out) << " \\\\" << std::endl;
    }
    RooRealVar *theVariable;
    for (int index = 0; index < variables.getSize(); index++) {
        theVariable = dynamic_cast<RooRealVar*>(variables.find(variables[index].GetName()));
        out << theVariable->GetTitle() << " & $\\textrm{" ;
        formatNumber(theVariable->getValV(), out) << "} \\pm \\textrm{" ;
        formatNumber(theVariable->getError(), out) << "}$ \\\\" << std::endl;
    }
    out << "\\end{tabular*}}}" << std::endl;
    out << "\\end{document}" << std::endl;
    histogram->Delete();
}

void makePDF(std::string texInputFile)
{
    makePDF(texInputFile, texInputFile);
}

void makePDF(std::string texInputFile, std::string prefix)
{
    system(Form("xelatex %s.tex", texInputFile.c_str()));
    system(Form("pdfcrop --margins 0 %s.pdf %sStats.pdf", texInputFile.c_str(), prefix.c_str()));
    system(Form("rm -f %s.aux %s.pdf %s.log", texInputFile.c_str(), texInputFile.c_str(), texInputFile.c_str()));
}