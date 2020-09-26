void  ejercicio4(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);
  //vectores para las variables del track
  vector<float> *tracks_pt=0;
  vector<float> *tracks_eta=0;
  vector<float> *tracks_phi=0;
  vector<float> *tracks_m=0;
  vector<float> *tracks_vtx=0;
  //vectores para las variables del cluster
  vector<float> *clusters_pt=0;
  vector<float> *clusters_eta=0;
  vector<float> *clusters_phi=0;
  vector<float> *clusters_m=0;
  //vectores para las variables de las particulas
  vector<float> *particles_pt=0;
  vector<float> *particles_eta=0;
  vector<float> *particles_phi=0;
  vector<float> *particles_m=0;
  vector<float> *particles_pdgID=0;
  //direcciones en el tree para los tracks
  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Tracks_eta", &tracks_eta);
  tree->SetBranchAddress("Tracks_phi", &tracks_phi);
  tree->SetBranchAddress("Tracks_m", &tracks_m);
  tree->SetBranchAddress("Tracks_vtx", &tracks_vtx);
  //direcciones en el tree para los cluster
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  tree->SetBranchAddress("Clusters_eta", &clusters_eta);
  tree->SetBranchAddress("Clusters_phi", &clusters_phi);
  tree->SetBranchAddress("Clusters_m", &clusters_m);
  //direcciones para las particulas
  tree->SetBranchAddress("Particles_pt", &particles_pt);
  tree->SetBranchAddress("Particles_eta", &particles_eta);
  tree->SetBranchAddress("Particles_phi", &particles_phi);
  tree->SetBranchAddress("Particles_m", &particles_m);
  tree->SetBranchAddress("Particles_pdgID", &particles_pdgID);
  

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  //histograma tracks:
  TH1F *hist_tracks_pT = new TH1F("Tracks_pT","plot: Track pT; pT (MeV) ; Events ",50,100,2000);
  TH1F *hist_tracks_eta = new TH1F("Tracks_eta","plot: Track eta angle; eta (Rad) ; Events ",50,-6,6);
  TH1F *hist_tracks_phi = new TH1F("Tracks_phi","plot: Track phi angle; phi (Rad) ; Events ",50,-6,6);
  TH1F *hist_tracks_m = new TH1F("Tracks_m","plot: Track m; m (MeV) ; Events ",50,0,2000);
  TH1F *hist_tracks_vtx = new TH1F("Tracks_vtx","plot: Track VTX; m (MeV) ; Events ",50,0,50);
  //histogramas clusters:
  TH1F *hist_clusters_pt = new TH1F("Clusters_pT","plot: cluster pT(Mev); pT(MeV) ; Events ",50,100,2000);
  TH1F *hist_clusters_eta = new TH1F("Clusters_eta","plot: clusters eta angle; eta(Rad) ; Events ",50,-6,6);
  TH1F *hist_clusters_phi = new TH1F("Clusters_phi","  clusters phi angle; phi(Rad) ; Events ",50,-6,6);
  TH1F *hist_clusters_m = new TH1F("Clusters_m","plot: clusters m; m ; Events ",50,0,2000);
  //histogramas particulas
  TH1F *hist_particles_pt = new TH1F("Particles_pT","plot: particles pT(MeV); pT(MeV) ; Events ",50,100,2000);
  TH1F *hist_particles_eta = new TH1F("Particles_eta","plot: particles angle eta(Rad); eta(Rad) ; Events ",50,-6,6);
  TH1F *hist_particles_phi = new TH1F("Particles_phi","plot:particles angle phi(Rad); phi(Rad) ; Events ",50,-6,6);
  TH1F *hist_particles_m = new TH1F("Particles_m","plot:particles m; m ; Events ",50,0,2000);
  TH1F *hist_particles_pdgID = new TH1F("Particles_pdgID","particle identification in events ; pdgID ; Events ",50,-3000,3000);
  
  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Eventss ",50,1,50);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      for(int tr=0; tr<particles_m->size(); tr++)
	{
	  hist_particles_m->Fill(particles_m->at(tr));
	}

    }

  std::cout << "Done!" << std::endl;

  hist_particles_m->SetFillColor(35);
  hist_particles_m->Draw();
  canvas->Draw();

}
