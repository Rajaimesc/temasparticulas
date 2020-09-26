void macroex3b(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  Float_t mu_average;
  vector<float> *tracks_pt=0;
  vector<float> *clusters_pt=0;

  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  //tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_average);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH2F *hist_muavgtracks = new TH2F("mu average","plot:out of time pileup per number of tracks ; mu avg ;NTracks;Events",50,1,50,50,0,1200);
  TH2F *hist_muavgclusters = new TH2F("mu average"," plot: out of time pileup per number of clusters;mu avg;Nclusters ; Events ",50,1,50,50,0,1200);
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      //hist_muavgtracks->Fill(mu_average,tracks_pt->size());
      hist_muavgclusters->Fill(mu_average,clusters_pt->size());
    }

  std::cout << "Done!" << std::endl;

  //hist_npvtracks->SetFillColor(44);
  //hist_muavgtracks->Draw("Lego2");
  hist_muavgclusters->Draw("Lego2");
  canvas->Draw();

}
