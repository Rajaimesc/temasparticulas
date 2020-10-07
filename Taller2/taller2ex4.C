void taller2ex4(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;
  vector<float> *track_R4_pt=0;


  vector<float> *reco_R4_eta=0;
  vector<float> *reco_R4_phi=0;
  vector<float> *reco_R4_m=0;
  vector<float> *reco_R4_jvf=0;

  vector<float> *truth_R4_eta=0;
  vector<float> *truth_R4_phi=0;
  vector<float> *truth_R4_m=0;

  vector<float> *track_R4_eta=0;
  vector<float> *track_R4_phi=0;
  vector<float> *track_R4_m=0;
  

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("RecoJets_R4_eta", &reco_R4_eta);
  tree->SetBranchAddress("RecoJets_R4_phi", &reco_R4_phi);
  tree->SetBranchAddress("RecoJets_R4_m", &reco_R4_m);
  tree->SetBranchAddress("TruthJets_R4_eta", &truth_R4_eta);
  tree->SetBranchAddress("TruthJets_R4_phi", &truth_R4_phi);
  tree->SetBranchAddress("TruthJets_R4_m", &truth_R4_m);
  tree->SetBranchAddress("TrackJets_R4_eta", &track_R4_eta);
  tree->SetBranchAddress("TrackJets_R4_phi", &track_R4_phi);
  tree->SetBranchAddress("TrackJets_R4_m", &track_R4_m);
  tree->SetBranchAddress("TrackJets_R4_pt", &track_R4_pt);

  TCanvas *canvas = new TCanvas("Canvas","",800,600);
  TH1F *hist_DR_reco_truth = new TH1F("Delta R Track Without cut 500Gev","Delta R; #Delta R; Events",20,0,0.3);
  TH1F *hist_DR_track_truth = new TH1F("Delta R track"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth100 = new TH1F("Delta R truth with 100 Gev"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth20 = new TH1F("Delta R truth with 20 Gev"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth500 = new TH1F("Delta R truth with 500 Gev"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth500track = new TH1F("Delta R track with 500 Gev"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth100track = new TH1F("Delta R track with 500 Gev"," Delta R; #Delta R ; Events ",20,0,2);
  TH1F *hist_DR_truth20track = new TH1F("Delta R track with 500 Gev"," Delta R; #Delta R ; Events ",20,0,2);

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();
  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
    
      if(reco_R4_pt->size()!=0){
        TLorentzVector recoJet;
        recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_DR_truth20->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>100000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_DR_truth100->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>500000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_DR_truth500->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        
      }
      if(track_R4_pt->size()!=0){
        TLorentzVector trackJet;
        trackJet.SetPtEtaPhiM(track_R4_pt->at(0),track_R4_eta->at(0),track_R4_phi->at(0),track_R4_m->at(0));
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(trackJet))<0.3){
	    hist_DR_truth20track->Fill(track_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>100000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(trackJet))<0.3){
	    hist_DR_truth100track->Fill(track_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>500000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(trackJet))<0.3){
	    hist_DR_truth500track->Fill(track_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
        }
        
      }
    

    }

  std::cout << "Done!" << std::endl;

  
  //hist_DR_reco_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_truth500track->Scale(1/hist_DR_truth500track->Integral());
  hist_DR_truth100track->Scale(1/hist_DR_truth100track->Integral());
  hist_DR_truth20track->Scale(1/hist_DR_truth500track->Integral());
  hist_DR_truth20->Scale(1/hist_DR_truth20->Integral());
  hist_DR_truth100->Scale(1/hist_DR_truth100->Integral());
  hist_DR_truth500->Scale(1/hist_DR_truth500->Integral());
  //hist_DR_track_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_truth20->DrawNormalized("");
  hist_DR_truth500->DrawNormalized("");
  hist_DR_truth100->DrawNormalized("");
  hist_DR_truth20track->DrawNormalized("same");
  hist_DR_truth100track->DrawNormalized("");
  hist_DR_truth500track->DrawNormalized("");
  //hist_DR_track_truth->DrawNormalized("");
  canvas->Draw();
  canvas-> Print("DeltaR_Truth_Gev.pdf");
}
