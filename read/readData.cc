#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TList.h>
#include <TKey.h>
#include "Event.h"

int main() {

// Open input file, get the TTrees, put into a vector

  TFile* inputFile = new TFile("../generate/testData.root");
  inputFile->ls();
  TTree* sig = dynamic_cast<TTree*>(inputFile->Get("sig"));
  TTree* bkg = dynamic_cast<TTree*>(inputFile->Get("bkg"));
  std::vector<TTree*> treeVec;
  treeVec.push_back(sig);
  treeVec.push_back(bkg);

// Loop over TTrees

  for (int i=0; i<treeVec.size(); i++){

    treeVec[i]->Print();
    Event evt;
    treeVec[i]->SetBranchAddress("evt", &evt);
    int numEntries = treeVec[i]->GetEntries();
    std::cout << "number of entries = " << numEntries << std::endl;

// Loop over events

    for (int j=0; j<numEntries; j++){

      treeVec[i]->GetEntry(j);                // sets evt
      std::cout << evt.x << "  " << evt.y << "  " << evt.z << std::endl;

    }

  }

  return 0;

}
