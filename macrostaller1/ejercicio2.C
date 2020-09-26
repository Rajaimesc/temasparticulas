void ejercicio2(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  UInt_t npv = -1;
  Float_t mu_average;
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_average);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  TH2F *hist_muavg = new TH2F("mu_average","Exercise plot: average mu with respect of NPV ; NPV ; mu average;Events ",50,1,50,50,0,100);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      hist_muavg->Fill(npv,mu_average);
    }

  std::cout << "Done!" << std::endl;

  hist_muavg->SetFillColor(44);
  hist_muavg->Draw("Lego2");
  canvas->Draw();

}
