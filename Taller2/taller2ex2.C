void taller2ex2(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;
  UInt_t npv = -1;
  tree->SetBranchAddress("NPV", &npv);
  float mu = -1;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu);

  TCanvas *canvas = new TCanvas("Canvas","a first way to plot a variable",800,600);
  //TCanvas *canvas2 = new TCanvas("Canvas2","",800,600);

  
  TH1F *hist_leadreco_pt = new TH1F("Lead Reco-jet","Leading jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_leadtruth_pt   = new TH1F("Lead Truth-jet","Leading jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_reco_pt = new TH1F("Reco-jet","Jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_truth_pt = new TH1F("Truth-jet","Jet pT; pT(GeV);Events",50,10,200);
  TH1F *hist_lead_track_pT = new TH1F("Lead_Track_pT","Example plot: Track pT; pT (MeV) ; Events ",50,100,1000);
  //graficas
  TH2F *hist_jetpt_npv = new TH2F("Reco-jet pT vs. NPV",";NPV; jet pT",50,1,50, 20, 0, 200);
  TH2F *hist_jetpt_mu = new TH2F("Reco-jet pT vs. Pileup",";mu; jet pT",50,1,50, 20, 0, 200);
  TH2F *hist_truthjetpt_mu = new TH2F("Truth-jet pT vs. Pileup",";mu; jet pT",50,1,50, 20, 0, 200);
  TH2F *hist_truthjetpt_npv = new TH2F("Truth-jet pT vs. NPV",";NPV; jet pT",50,1,50, 20, 0, 200);
  //profiles
  TProfile *prof_jetpt_npv = new TProfile("Profile Reco-jet pT vs. NPV",";NPV; jet pT",50,1,50, 0, 200);
  TProfile *prof_jetpt_mu = new TProfile("Profile Reco-jet pT vs. Pileup",";mu; jet pT",50,1,50, 0, 200);
  TProfile *prof_truthjetpt_npv = new TProfile("Profile Truth-jet pT vs. NPV",";NPV; jet pT",50,1,50, 0, 200);
  TProfile *prof_truthjetpt_mu = new TProfile("Profile Truth-jet pT vs. Pileup",";mu; jet pT",50,1,50, 0, 200);
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      //if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
      //for(int j=0; j<reco_R4_pt->size(); j++){
      // hist_jetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
      //  prof_jetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
      //  }
      //}

      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
      for(int j=0; j<reco_R4_pt->size(); j++){
      hist_jetpt_mu->Fill(reco_R4_pt->at(j)/1000.,mu,evtw);
      prof_jetpt_mu->Fill(reco_R4_pt->at(j)/1000.,mu,evtw);
      }
      }
      

      //if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
      //for(int j=0; j<truth_R4_pt->size(); j++){
      //hist_truthjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
      //prof_truthjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
      //}
      //}
      
      //if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
      //for(int j=0; j<truth_R4_pt->size(); j++){
      //hist_truthjetpt_mu->Fill(truth_R4_pt->at(j)/1000.,mu,evtw);
      //prof_truthjetpt_mu->Fill(truth_R4_pt->at(j)/1000.,mu,evtw);
      //}
      //}
    }
  std::cout << "Done!" << std::endl;


  //hist_jetpt_npv->Draw("colz");
  //hist_jetpt_mu->Draw("colz");
  //hist_truthjetpt_mu->Draw("colz");
  //canvas->Draw();
  //canvas->Print("recovsmu.pdf");
  //prof_truthjetpt_npv->Draw("");
  
  prof_jetpt_mu->Draw("");
  canvas->Draw();
  canvas->Print("profilereco.pdf");
  //canvas->Print("recovsmu.pdf")
  //canvas2->Draw();
  //canvas2->Print("profilereco.pdf");
}
