#!/bin/bash

root -b -q SumWeight_ZMuMu_M50to120.cxx++ >&SumWeight_ZMuMu_M50to120.log&
root -b -q SumWeight_ZMuMu_M120to200.cxx++ >&SumWeight_ZMuMu_M120to200.log&
root -b -q SumWeight_ZMuMu_M200to400.cxx++ >&SumWeight_ZMuMu_M200to400.log&
root -b -q SumWeight_ZMuMu_M400to800.cxx++ >&SumWeight_ZMuMu_M400to800.log&
root -b -q SumWeight_ZMuMu_M800to1400.cxx++ >&SumWeight_ZMuMu_M800to1400.log&
root -b -q SumWeight_ZMuMu_M1400to2300.cxx++ >&SumWeight_ZMuMu_M1400to2300.log&
root -b -q SumWeight_ZMuMu_M2300to3500.cxx++ >&SumWeight_ZMuMu_M2300to3500.log&
root -b -q SumWeight_ZMuMu_M3500to4500.cxx++ >&SumWeight_ZMuMu_M3500to4500.log&
root -b -q SumWeight_ZMuMu_M4500to6000.cxx++ >&SumWeight_ZMuMu_M4500to6000.log&
root -b -q SumWeight_ZMuMu_M6000toInf.cxx++ >&SumWeight_ZMuMu_M6000toInf.log&
root -b -q SumWeight_WJetsToLNu.cxx++ >&SumWeight_WJetsToLNu.log&
root -b -q SumWeight_ttbar.cxx++ >&SumWeight_ttbar.log&
root -b -q SumWeight_MuEnrichedQCD_Pt15to20.cxx++ >&SumWeight_MuEnrichedQCD_Pt15to20.log&
root -b -q SumWeight_MuEnrichedQCD_Pt20to30.cxx++ >&SumWeight_MuEnrichedQCD_Pt20to30.log&
root -b -q SumWeight_MuEnrichedQCD_Pt30to50.cxx++ >&SumWeight_MuEnrichedQCD_Pt30to50.log&
root -b -q SumWeight_MuEnrichedQCD_Pt50to80.cxx++ >&SumWeight_MuEnrichedQCD_Pt50to80.log&
root -b -q SumWeight_MuEnrichedQCD_Pt80to120.cxx++ >&SumWeight_MuEnrichedQCD_Pt80to120.log&
root -b -q SumWeight_MuEnrichedQCD_Pt120to170.cxx++ >&SumWeight_MuEnrichedQCD_Pt120to170.log&
root -b -q SumWeight_MuEnrichedQCD_Pt170to300.cxx++ >&SumWeight_MuEnrichedQCD_Pt170to300.log&
root -b -q SumWeight_MuEnrichedQCD_Pt300to470.cxx++ >&SumWeight_MuEnrichedQCD_Pt300to470.log&
root -b -q SumWeight_MuEnrichedQCD_Pt470to600.cxx++ >&SumWeight_MuEnrichedQCD_Pt470to600.log&

echo "All jobs are submitted"

