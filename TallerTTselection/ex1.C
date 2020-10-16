void ex1(){

  // Let's open the TFile
  TFile *file = TFile::Open("Data_8TeV.root"); 
  TTree *tree = (TTree*) file->Get("mini");
  tree->Print();
  
  Bool_t e_trig;
  Bool_t mu_trig;
  Bool_t good_vtx;
  UInt_t lep_n;
  UInt_t jet_n;
  Float_t MET;
  Float_t MET_phi;

  Float_t lep_pt[10];
  Float_t lep_eta[10];
  Float_t lep_phi[10];
  Float_t lep_E[10];
  Int_t lep_type[10];
  Float_t lep_ptcone30[10];
  Float_t lep_etcone20[10];

  Float_t jet_pt[10];
  Float_t jet_eta[10];
  Float_t jet_jvf[10];
  Float_t jet_MV1[10];
  float evtw = -1;
  
  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("trigE", &e_trig);
  tree->SetBranchAddress("trigM", &mu_trig);
  tree->SetBranchAddress("hasGoodVertex", &good_vtx);
  tree->SetBranchAddress("lep_n", &lep_n);
  tree->SetBranchAddress("jet_n", &jet_n);
  tree->SetBranchAddress("met_et", &MET);
  tree->SetBranchAddress("met_phi", &MET_phi);

  tree->SetBranchAddress("lep_pt", &lep_pt);
  tree->SetBranchAddress("lep_eta", &lep_eta);
  tree->SetBranchAddress("lep_phi", &lep_phi);
  tree->SetBranchAddress("lep_E", &lep_E);
  tree->SetBranchAddress("lep_type", &lep_type);
  tree->SetBranchAddress("lep_ptcone30", &lep_ptcone30);
  tree->SetBranchAddress("lep_etcone20", &lep_etcone20);

  tree->SetBranchAddress("jet_pt", &jet_pt);
  tree->SetBranchAddress("jet_pt", &jet_pt);
  tree->SetBranchAddress("jet_eta", &jet_eta);
  tree->SetBranchAddress("jet_jvf", &jet_jvf);
  tree->SetBranchAddress("jet_MV1", &jet_MV1);
  

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH1F *cutflow = new TH1F("Cutflow","Cutflow; Cut; Events",10,0,10);

  TH1F *hist_njets = new TH1F("Number of jets","n-jets; Jet multiplicity; Events",10,0,10);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
  int cut1 = 0;
  int cut2 = 0;
  int cut3 = 0;
  int cut4 = 0;
  int cut5 = 0;
  int cut6 = 0;
  int cut7 = 0;
  int cut8 = 0;
  

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      //First cut: Good vertex
      if(!good_vtx) continue;
      cut1++;
      cutflow->Fill(1);

      //Second cut: Trigger
      if(!e_trig && !mu_trig) continue;
      cut2++;
      cutflow->Fill(2);

      // Preselection of good leptons
      int n_mu=0;
      int n_el=0;
      int n_lep=0;
      //Loop over leptons
      for(unsigned int i=0; i<lep_n; i++){
	if( lep_pt[i] < 25000.) continue;
	if( lep_ptcone30[i]/lep_pt[i] > 0.15 ) continue;
	if( lep_etcone20[i]/lep_pt[i] > 0.15 ) continue;
	if( lep_type [i]==13 && TMath::Abs(lep_eta[i]) < 2.5 ){
	  n_mu++;}
        if( lep_type [i]==10 && TMath::Abs(lep_eta[i])< 2.47 &&(TMath::Abs(lep_eta[i])<1.37 || (TMath::Abs(lep_eta[i])>1.52))){n_mu++;} 
	/*
        To complete: Add electrons and extract the index for the good lepton
        */
	n_lep++;
      }
      int good_lep=0;
      //Select events with only 1 good lepton and fill the cutflow histogram
      //Example:
      //Third cut (one good lepton):
      if(n_lep!=1) continue;    
      cutflow->Fill(3);
      cut3++;
      good_lep++;


      int n_jets=0;
      int n_bjets=0;

      //Number of jets distribution
      hist_njets->Fill(jet_n,evtw);

      //Fourth cut: At least 4 jets
      if(jet_n<4) continue;
      cutflow->Fill(4);
      cut4++;

      for(unsigned int j=0; j<jet_n; j++){
	// To complete: apply jet cuts to find the good jets
	if(jet_pt[j] < 25000.) continue;
	//Eta cut
	if(TMath::Abs(jet_eta[j])>2.5) continue;
	
	// JVF cleaning
	if(TMath::Abs(jet_eta[j])<2.4 && jet_pt[j]<50000. && jet_jvf[j]<.5) continue;
	  n_jets++;
	// cut on 0.7892 MV1 and count the number of b-jets
	  if(TMath::Abs(jet_MV1[j])<.7892) continue;
	  n_bjets++;
      }						  
	  

      //Fifth cut: At least 4 good jets
      if(n_jets<4) continue;
      cutflow->Fill(5);
      cut5++;

      //Sixth cut: at least one b-jet
      if(n_bjets<2) continue;
      cutflow->Fill(6);
      cut6++;

      //Seventh cut: MET > 30 GeV
      if(MET<30000.) continue;
      cutflow->Fill(7);
      cut7++;
      // TLorentzVector definitions
      TLorentzVector Lepton  = TLorentzVector();
      TLorentzVector  MeT  = TLorentzVector();

      //To complete: Lorentz vectors for the lepton and MET. Use SetPtEtaPhiE().
      Lepton.SetPtEtaPhiE(lep_pt[n_lep],lep_eta[n_lep],lep_phi[n_lep],lep_E[n_lep]);
      MeT.SetPtEtaPhiE(MET,0,MET_phi,MET);
      //Calculation of the mTW using TLorentz vectors
       float mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));

      //Eight cut: mTW > 30 GeV
       if(mTW>30000){
	 cutflow->Fill(8);
	 cut8++;
       }
    }
  std::cout << "Done!" << std::endl;
  std::cout << "All events:" << nentries << std::endl;
  std::cout << "Cut1:" << cut1 << std::endl;
  std::cout << "Cut2:" << cut2 << std::endl;
  std::cout << "Cut3:" << cut3 << std::endl;
  std::cout << "Cut4:" << cut4 << std::endl;
  std::cout << "Cut5:" << cut5 << std::endl;
  std::cout << "Cut6:" << cut6 << std::endl;
  std::cout << "Cut7:" << cut7 << std::endl;
  std::cout << "Cut8:" << cut8 << std::endl;
    
    

  std::cout << "Done!" << std::endl;
  cutflow->Draw("");
  canvas->Draw();
}
