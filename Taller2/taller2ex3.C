void taller2ex3(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  //UInt_t npv = -1;
  //tree->SetBranchAddress("NPV", &npv);
  //vector<float> *tracks_pt;
  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;
  vector<float> *reco_R4_jvf=0;

  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);

  //TH1F *hist_npv = new TH1F("NPV","Example plot: Number of primary vertices; NPV ; Events ",50,1,50);
  TH1F *hist_leadreco_pt = new TH1F("Lead Reco-jet","Leading jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_leadtruth_pt   = new TH1F("Lead Truth-jet","Leading jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_reco_pt = new TH1F("Reco-jet","Jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_reco_ptjvf = new TH1F("Reco-jet with JVF>0.5","Jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_truth_pt = new TH1F("Truth-jet","Jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_lead_track_pT = new TH1F("Lead_Track_pT","Track pT; pT (MeV) ; Events ",50,100,200);
  
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();


  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      
      if(truth_R4_pt->size()>0){
	hist_leadtruth_pt->Fill(truth_R4_pt->at(0)/1000., evtw);
	for(int j=0; j<truth_R4_pt->size(); j++){
	  hist_truth_pt->Fill(truth_R4_pt->at(j)/1000., evtw);
	}

      }

	for(int j=0; j<reco_R4_pt->size(); j++){
	  if(fabs(reco_R4_jvf->at(0))>0.5){hist_reco_ptjvf->Fill(reco_R4_pt->at(j)/1000., evtw);}
	}
    
      if(reco_R4_pt->size()>0){
	hist_leadreco_pt->Fill(reco_R4_pt->at(0)/1000., evtw);
	for(int j=0; j<reco_R4_pt->size(); j++){
	  hist_reco_pt->Fill(reco_R4_pt->at(j)/1000., evtw);
	}
      }

    }

  std::cout << "Done!" << std::endl;

  hist_leadreco_pt->SetMarkerStyle(20);
  hist_leadreco_pt->SetMarkerColor(kRed);
  hist_leadreco_pt->DrawNormalized("");
  
  hist_truth_pt->SetMarkerStyle(22);
  hist_truth_pt->SetMarkerColor(kBlue);
  hist_truth_pt->DrawNormalized("same");


  hist_reco_pt->SetMarkerStyle(22);
  hist_reco_pt->SetMarkerColor(kOrange);
  hist_reco_pt->DrawNormalized("same");
  
  hist_reco_ptjvf->SetMarkerStyle(22);
  hist_reco_ptjvf->SetMarkerColor(kGreen);
  hist_reco_ptjvf->DrawNormalized("same");



  //canvas->Print("leadtruthvsleadreco_withoutweights.pdf");

  // Build and Draw a legend
  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->SetHeader("Tranverse momentums","C"); // option "C" allows to center the header
  legend->AddEntry(hist_leadreco_pt," Lead Reco  jets without cut");
  legend->AddEntry(hist_truth_pt,"Truth Jets without the cut");
  legend->AddEntry(hist_reco_pt,"Reco Jets without the cut");
  legend->AddEntry(hist_reco_ptjvf,"Reco Jets with  cut JVF >0.5");
  legend->Draw();

  //canvas->SetLogy();
  canvas->Draw();
  //canvas->Print("leadtruthvsleadreco_withoutweights.pdf");
}
