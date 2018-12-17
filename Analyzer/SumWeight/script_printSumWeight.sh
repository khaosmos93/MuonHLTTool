#!/bin/bash

root -b -q ROOTFile_SumWeight_ZMuMu_M50to120.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M120to200.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M200to400.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M400to800.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M800to1400.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M1400to2300.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M2300to3500.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M3500to4500.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M4500to6000.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ZMuMu_M6000toInf.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_WJetsToLNu.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_ttbar.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt15to20.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt20to30.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt30to50.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt50to80.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt80to120.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt120to170.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt170to300.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt300to470.root Print_SumWeight.cxx
root -b -q ROOTFile_SumWeight_MuEnrichedQCD_Pt470to600.root Print_SumWeight.cxx

echo "Done."