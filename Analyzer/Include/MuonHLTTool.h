#include <Include/Object.h>
#include <iostream>

namespace MuonHLT
{
// -- some useful variables, functions, classes ...

vector<MuonHLT::L1Muon> GetAllL1Muon(NtupleHandle* ntuple, Double_t minPt = -1 )
{
  vector<MuonHLT::L1Muon> vec_L1Muon;
  for(Int_t i_L1=0; i_L1<ntuple->nL1Muon; i_L1++)
  {
    MuonHLT::L1Muon l1mu(ntuple, i_L1);
    if( l1mu.pt > minPt )
      vec_L1Muon.push_back( l1mu );
  }

  return vec_L1Muon;
}

vector<MuonHLT::HLTObject> GetAllHLTObject(NtupleHandle *ntuple, Double_t minPt = -1)
{
  vector<MuonHLT::HLTObject> vec_HLTObj;
  Int_t nHLTObj = (Int_t)ntuple->vec_filterName->size();
  for(Int_t i_obj=0; i_obj<nHLTObj; i_obj++)
  {
    MuonHLT::HLTObject hltObject(ntuple, i_obj);
    if( hltObject.pt > minPt )
      vec_HLTObj.push_back( hltObject );
  }

  return vec_HLTObj;
}

vector<MuonHLT::MYHLTObject> GetAllMYHLTObject(NtupleHandle *ntuple, Double_t minPt = -1)
{
  vector<MuonHLT::MYHLTObject> vec_MYHLTObj;
  Int_t nHLTObj = (Int_t)ntuple->vec_myFilterName->size();
  for(Int_t i_obj=0; i_obj<nHLTObj; i_obj++)
  {
    MuonHLT::MYHLTObject myHLTObject(ntuple, i_obj);
    if( myHLTObject.pt > minPt )
      vec_MYHLTObj.push_back( myHLTObject );
  }

  return vec_MYHLTObj;
}

static inline void loadBar(int x, int n, int r, int w)
{
    // Only update r times.
    if( x == n )
      cout << endl;

    if ( x % (n/r +1) != 0 ) return;

 
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
 
    // Show the load bar.
    for (int x=0; x<c; x++) cout << "=";
 
    for (int x=c; x<w; x++) cout << " ";
 
    // ANSI Control codes to go back to the
    // previous line and clear it.
  cout << "]\r" << flush;

}


}; // -- end of namespace