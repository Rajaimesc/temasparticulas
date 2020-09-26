void macroex3(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  UInt_t npv = -1;
  //Tfloat_t mu_average;
  vector<float> *tracks_pt=0;
  vector<float> *clusters_pt=0;

  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  tree->SetBranchAddress("NPV", &npv);
  //tree->SetBranchAddress("mu_average", &mu_average);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH2F *hist_npvtracks = new TH2F("NPV","plot: Primary Vertices per number of tracks ; NPV ;NTracks;Events",50,1,50,50,0,1200);
  TH2F *hist_npvclusters = new TH2F("NPV"," plot:Primary Vertices per number of clusters;NPV;Nclusters ; Events ",50,1,50,50,0,1200);
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      //hist_npvtracks->Fill(npv,tracks_pt->size());
      hist_npvclusters->Fill(npv,clusters_pt->size());
    }

  std::cout << "Done!" << std::endl;

  //hist_npvtracks->SetFillColor(44);
  //hist_npvtracks->Draw("Lego2");
  hist_npvclusters->Draw("Lego2");
  canvas->Draw();

}
