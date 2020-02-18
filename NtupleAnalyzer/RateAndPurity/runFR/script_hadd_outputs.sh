#!/bin/bash

mkdir Outputs


echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_TkMu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_TkMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_IsoTkMu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_IsoTkMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_TkMu50_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_TkMu50_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_Mu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_Mu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_IsoMu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_IsoMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-HLT_Mu50_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/HLT_Mu50_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-hltL1fL1sMu22L1Filtered0-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/hltL1fL1sMu22L1Filtered0/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep80X-v25-hltL2fL1sMu22L1f0L2Filtered10Q-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep80X/hltL2fL1sMu22L1f0L2Filtered10Q/Job*/Output*.root


echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep102X-v25-HLT_Mu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep102X/HLT_Mu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep102X-v25-HLT_IsoMu24_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep102X/HLT_IsoMu24_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep102X-v25-HLT_Mu50_v-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep102X/HLT_Mu50_v/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep102X-v25-hltL1fL1sMu22L1Filtered0-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep102X/hltL1fL1sMu22L1Filtered0/Job*/Output*.root

echo ""
hadd Outputs/Output-MuonTriggerPurity-TTSemiLep102X-v25-hltL2fL1sSingleMu22L1f0L2Filtered10Q-0.0-5.0.root \
/d3/scratch/msoh/BatchDir_v25/TTSemiLep102X/hltL2fL1sSingleMu22L1f0L2Filtered10Q/Job*/Output*.root
