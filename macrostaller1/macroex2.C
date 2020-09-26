void macroex2(){
  
  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
  
  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);
  
  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
  
  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH1F *hist_lead_track_pT = new TH1F("Lead_Track_pT","Example plot: Track pT; pT (MeV) ; Events ",50,100,1000);
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
  
  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      for(int tr=0; tr<tracks_pt->size(); tr++)
	{
	  hist_lead_track_pT->Fill(tracks_pt->at(tr));
	}
      
    }
  
  std::cout << "Done!" << std::endl;
  
  hist_lead_track_pT->SetFillColor(kGreen);
  hist_lead_track_pT->Draw();
  canvas->Draw();

}
