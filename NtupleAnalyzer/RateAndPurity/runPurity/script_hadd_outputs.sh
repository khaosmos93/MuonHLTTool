#!/bin/bash

mkdir Outputs

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2016H-v23-HLT_IsoMu24_v.root \
/d3/scratch/msoh/BatchDir_v23/Data2016H/HLT_IsoMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2016H-v23-HLT_Mu50_v.root \
/d3/scratch/msoh/BatchDir_v23/Data2016H/HLT_Mu50_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2016H-v23-hltL1fL1sMu22L1Filtered0.root \
/d3/scratch/msoh/BatchDir_v23/Data2016H/hltL1fL1sMu22L1Filtered0/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2016H-v23-hltL2fL1sMu22L1f0L2Filtered10Q.root \
/d3/scratch/msoh/BatchDir_v23/Data2016H/hltL2fL1sMu22L1f0L2Filtered10Q/Job*/Output*.root



echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2018D-v23-HLT_IsoMu24_v.root \
/d3/scratch/msoh/BatchDir_v23/Data2018D/HLT_IsoMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2018D-v23-HLT_Mu50_v.root \
/d3/scratch/msoh/BatchDir_v23/Data2018D/HLT_Mu50_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2018D-v23-hltL1fL1sMu22L1Filtered0.root \
/d3/scratch/msoh/BatchDir_v23/Data2018D/hltL1fL1sMu22L1Filtered0/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-Data2018D-v23-hltL2fL1sSingleMu22L1f0L2Filtered10Q.root \
/d3/scratch/msoh/BatchDir_v23/Data2018D/hltL2fL1sSingleMu22L1f0L2Filtered10Q/Job*/Output*.root

