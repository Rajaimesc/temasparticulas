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
  TH1F *hist_lep_pt = new TH1F("Leptons_pt","Lepton_pt; Lep_pt; Events",20,1000,1000000);
  TH1F *hist_lep_pt30 = new TH1F("Leptons_ptcone30","Lepton ptcone30; Lep_ptcone30; Events",20,0,1);
  TH1F *hist_lep_et20 = new TH1F("Leptons_etcone20","Lepton etcone20; Lep_etcone20; Events",20,-1,1);
  TH1F *hist_lep_eta = new TH1F("Leptons_eta","Lepton eta; Lep_eta; Events",20,-4,4);
  TH1F *hist_jets_pt = new TH1F("Jets_pt","Jets pt; Jets_pt; Events",20,0,1000000);
  TH1F *hist_jets_eta = new TH1F("Jets_eta","Jets_eta; Jets_eta; Events",20,-4,4);
  TH1F *hist_jets_JVF = new TH1F("Jets_JVF","Jets_JVF; Jets JVF; Events",50,0,1);
  TH1F *hist_jets_MV1 = new TH1F("Jets_MV1","Jets_MV1; Jets MV1; Events",10,0,1);
  TH1F *hist_bjets_n = new TH1F("b-jets_n","b-jets_number;b-jets number; Events",200,0,10);
  TH1F *hist_MET = new TH1F("MET","MET; MET; Events",200,0,100000);
  TH1F *hist_MTW = new TH1F("MTW","MTW; MTW; Events",200,0,100000);

  //TH1F *hist_njets = new TH1F("Number of jets","n-jets; Jet multiplicity; Events",10,0,10);

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
      int good_lep=0;
      //Loop over leptons
      for(unsigned int i=0; i<lep_n; i++){
	//histos
	//hist_lep_pt->Fill(lep_pt[i]);
	//hist_lep_pt30->Fill(lep_ptcone30[i]/lep_pt[i]);
	//hist_lep_et20->Fill(lep_etcone20[i]/lep_pt[i]);
	//hist_lep_eta->Fill(lep_eta[i]);
	//cut
	if( lep_pt[i] < 25000.) continue;
	if( lep_ptcone30[i]/lep_pt[i] > 0.15 ) continue;
	if( lep_etcone20[i]/lep_pt[i] > 0.15 ) continue;
	if( lep_type [i]==13 && TMath::Abs(lep_eta[i]) < 2.5 ){
	  n_mu++;
	  good_lep=i;}
        if( lep_type [i]==11 && TMath::Abs(lep_eta[i]) < 2.47 ){
	  if(TMath::Abs(lep_eta[i]) < 1.37 || TMath::Abs(lep_eta[i]) > 1.52){
	    n_el++;
	    good_lep=i;}
	}
	//Histos despues de los if
	hist_lep_pt->Fill(lep_pt[i]);
	hist_lep_pt30->Fill(lep_ptcone30[i]/lep_pt[i]);
	hist_lep_et20->Fill(lep_etcone20[i]/lep_pt[i]);
	hist_lep_eta->Fill(lep_eta[i]);
	
      }  
	/*
        To complete: Add electrons and extract the index for the good lepton
        */
      n_lep=n_el+n_mu;
    
      //int good_lep=0;
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
      //hist_njets->Fill(jet_n,evtw);

      //Fourth cut: At least 4 jets
      if(jet_n<4) continue;
      cutflow->Fill(4);
      cut4++;
      //njets post cut
      //hist_njets->Fill(jet_n,evtw);
      for(unsigned int j=0; j<jet_n; j++){
	//hist_jets_pt->Fill(jet_pt[j]);
	//hist_MET->Fill(MET);hist_jets_eta->Fill(jet_eta[j]);
	//hist_jets_JVF->Fill(jet_jvf[j]);
	//hist_jets_MV1->Fill(jet_MV1[j]);
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

	  //histos después de los cortes para los jets
	  hist_jets_pt->Fill(jet_pt[j]);
	  hist_MET->Fill(MET);hist_jets_eta->Fill(jet_eta[j]);
	  //hist_jets_JVF->Fill(jet_jvf[j]);
	  hist_jets_MV1->Fill(jet_MV1[j]);
      }					  
	  

      //Fifth cut: At least 4 good jets
      if(n_jets<4) continue;
      cutflow->Fill(5);
      cut5++;
      //histo b-jets
      //hist_bjets_n->Fill(n_bjets);

      //Sixth cut: at least one b-jet
      if(n_bjets<2) continue;
      cutflow->Fill(6);
      cut6++;
      //histo b-jet después del cut
      hist_bjets_n->Fill(n_bjets);
      
      //histo met before cut
      //hist_MET->Fill(MET);
      //Seventh cut: MET > 30 GeV
      if(MET<30000.) continue;
      //hist_MET->Fill(MET);
      cutflow->Fill(7);
      cut7++;
      //MET despues del cut
       hist_MET->Fill(MET);
      // TLorentzVector definitions
      TLorentzVector Lepton  = TLorentzVector();
      TLorentzVector  MeT  = TLorentzVector();

      //To complete: Lorentz vectors for the lepton and MET. Use SetPtEtaPhiE().
      Lepton.SetPtEtaPhiE(lep_pt[good_lep],lep_eta[good_lep],lep_phi[good_lep],lep_E[good_lep]);
      MeT.SetPtEtaPhiE(MET,0,MET_phi,MET);
      //Calculation of the mTW using TLorentz vectors
       float mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));
       //histo MTW before cut
       //hist_MTW->Fill(mTW);
      //Eight cut: mTW > 30 GeV
       if(mTW>30000){
	 cutflow->Fill(8);
	 cut8++;
       }
       //mTW despues dle cut
       hist_MTW->Fill(mTW);
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
 
  //hist_njets->Draw();
  //canvas->Print("n_jets_final.pdf");
  
  //cutflow->Draw("");

  //canvas->SetLogy();
  //canvas->Print("cutflow_postcut.pdf");

  //hist_lep_pt->Draw("");
  //canvas->SetLogy();
  //canvas->Print("lep_pt_postcut.pdf");

  //hist_lep_pt30->Draw("");
  //canvas->SetLogy();
  //canvas->Print("lep_pt30_postcut.pdf");

  //hist_lep_et20->Draw("");
  //canvas->SetLogy();
  //canvas->Print("lep_pt_et20.pdf");

  //hist_lep_eta->Draw("");
  //canvas->Print("lep_eta.pdf");

  //hist_jets_pt->Draw("");
  //canvas->SetLogy();
  //canvas->Print("jets_pt_postcut.pdf");

  //hist_jets_eta->Draw("");
  //canvas->Print("jets_eta_postcut.pdf");

  //hist_jets_JVF->Draw("");
  //canvas->Print("jets_JVF_precut.pdf");

  //hist_jets_MV1->Draw("");
  //canvas->Print("jets_MV1_postcut.pdf");

  //hist_bjets_n->Draw("");
  //canvas->Print("bjets_postcut.pdf");

  hist_MET->Draw("");
  canvas->Print("MET_postcut.pdf");


  //hist_MTW->Draw("");
  //canvas->Print("MTW_postcut.pdf");
    
    
    
    
    
  
 canvas->Draw();
    
}
