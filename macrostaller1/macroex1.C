void macroex1(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
  
  //UInt_t npv = -1;
  //tree->SetBranchAddress("NPV", &npv);
  vector<float> *tracks_pt;
  vector<float> *clusters_pt;
  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  
  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
  
  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH1F *hist_nTrks = new TH1F("NTracks","Example plot: Number of tracks; NTracks ; Events ",50,0,1000);
  TH1F *hist_nCltrs = new TH1F("NClusters","Example plot: Number of clusters; NClusters ; Events ",50,0,1000);
  
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
  
  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_nTrks->Fill(tracks_pt->size());
      hist_nCltrs->Fill(clusters_pt->size());
    }

  std::cout << "Done!" << std::endl;

  hist_nTrks->SetFillColor(kBlue);
  hist_nTrks->Draw();
  canvas->Draw();
  
  hist_nCltrs->SetFillColor(kYellow);
  hist_nCltrs->Draw();
  canvas->Draw();
  

}
