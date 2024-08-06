#include <iostream>                                                
#include <TFile.h>                                                
#include <TH1D.h>
#include <boost/log/trivial.hpp>
#include "TTree.h"          
#include "TCanvas.h"                                      
#include "B2Reader.hh"
#include <vector>                                                  
#include "B2Writer.hh" 
#include "B2EventSummary.hh"                               
#include "B2VertexSummary.hh"                                     
#include "B2ClusterSummary.hh"                                    
#include "B2HitSummary.hh"
#include "B2TrackSummary.hh"
#include <TRandom.h>
#include <TRandom3.h>
#include "TStyle.h"

int main(int argc, char *argv[]) {
//  if (argc != 2) {
//    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
//    return EXIT_SUCCESS;
//  }

  int c = -1, start_number = 0, end_number = 0;
  TString input_file_path, output_file_name;
  while ((c = getopt(argc, argv, "i:o:s:e:")) != -1) {
    switch (c) {
    case 'i':
      input_file_path = optarg;
      break;
    case 'o':
      output_file_name = optarg;
      break;
    case 's':
      start_number = atoi(optarg);
      break;
    case 'e':
      end_number = atoi(optarg);
      break;
    }
  }


    auto *ofile = new TFile(output_file_name, "recreate");
    auto *out_seltree = new TTree("seltree", "seltree");
    auto *out_trutree = new TTree("trutree", "trutree");
    const float mu_mass = 105.658374;
    //make branches
    std::vector<int> nutype;
    std::vector<int> nutype_true;
    std::vector<int> reaction;
    std::vector<int> reaction_true;
    std::vector<int> topology;
    std::vector<int> topology_true;
    std::vector<int> target;
    std::vector<int> target_true;
    std::vector<int> cut_branch;
    std::vector<double> D1True; // True Muon momentum
    std::vector<double> D1Reco; // Reco Muon momentum
    std::vector<double> D2True; // True Muon angle
    std::vector<double> D2Reco; // Reco Muon angle
    std::vector<double> enu_true; // True neutrino energy
    std::vector<double> enu_reco; // Reco neutrino energy
    std::vector<double> q2_true; // True q2
    std::vector<double> q2_reco; //Reco q2
    std::vector<double> weight;
    std::vector<double> weight_true;
    std::vector<double> angle;
    std::vector<double> angle_r;
    double NU_E, NU_E_R; // True and Reco neutrino energy
    double mup, nue;

//Make histograms
   TH1D h_e_nu("e_nu", "Nu energy;nu energy (GeV);number of neutrinos", 200,0,5);
   TH1D hr_e_nu("e_nur", "Reconstructed Nu energy;nu enegrgy (GeV);number of neutrinos", 200,0,5);
   TH1D h_p_mu("p_mu", "D1 - Mu momentum;muon momentum (GeV);number of muons", 200,0,5);
   TH1D hr_p_mu("p_mur", "Reconstructed D1 -  Mu momentum;muon momentum (GeV);number of muons", 200,0,5);
   TH1D h_q2("q2", "Q2; q2 (GeV^2) ",100,0,3);
   TH1D hr_q2("q2r", "Reconstructed Q2; q2 (GeV^2)",100,0,3);
   TH1D h_cos("cos0", "D2 - Cos(theta)",200,-1,1);
   TH1D hr_cos("cos0r", "D2 - Reconstructed Cos(theta)",200,-1,1);
   TH1D h_a("theta", "Angle muon; Angle (Degrees)",180,0,180);
   TH1D hr_a("thetar", "Reconstructed angle muon; Angle (Degrees)",180,0,180);

    out_seltree -> Branch("nutype", &nutype);
    out_seltree -> Branch("reaction", &reaction);
    out_seltree -> Branch("topology", &topology);
    out_seltree -> Branch("target", &target);
    out_seltree -> Branch("cut_branch", &cut_branch);
    out_seltree -> Branch("enu_true", &enu_true);
    out_seltree -> Branch("enu_reco", &enu_reco);
    out_seltree -> Branch("q2_true", &q2_true);
    out_seltree -> Branch("q2_reco", &q2_reco);
    out_seltree -> Branch("D1True", &D1True);
    out_seltree -> Branch("D1Reco", &D1Reco);
    out_seltree -> Branch("D2True", &D2True);
    out_seltree -> Branch("D2Reco", &D2Reco);
    out_seltree -> Branch("weight", &weight);
	out_seltree->Branch("angle", &angle);
	out_seltree->Branch("angle_r", &angle_r);

    out_trutree -> Branch("nutype", &nutype);
    out_trutree -> Branch("reaction", &reaction);
    out_trutree -> Branch("topology", &topology);
    out_trutree -> Branch("target", &target);
    out_trutree -> Branch("cut_branch", &cut_branch);
    out_trutree -> Branch("enu_true", &enu_true);
    out_trutree -> Branch("q2_true", &q2_true);
    out_trutree -> Branch("D1True", &D1True);
    out_trutree -> Branch("D2True", &D2True);
    out_trutree -> Branch("weight", &weight);

    Float_t px,py,pz;
    gRandom->Rannor(px,py);
    pz = px*px + py*py;

bool coincidence = false;

 for (int run_number = start_number; run_number <= end_number; run_number++) {
   TString input_file_name;
   input_file_name.Form("%s_%04d.root", input_file_path.Data(), run_number);
 try {
    B2Reader reader(input_file_name);
    while (reader.ReadNextSpill() > 0) {
      auto &spill_summary = reader.GetSpillSummary();
      auto it = spill_summary.BeginHit();
      std::vector<const B2HitSummary *> my_hits;
      while (const auto *hit = it.Next()) {
        if (hit->GetDetectorId() == B2Detector::kBabyMind)
          my_hits.push_back(hit);
        else continue;
	}
// Get nutype, reaction, topology, weight, true and reconstructed neutrino energy from EventSummary
      auto it_event = spill_summary.BeginTrueEvent();
	while (const auto *event = it_event.Next()) {
// A random number sampled from a gaussian is added to each  nu_energy value to create reconstructed energy
	double random_enu = gRandom->Gaus(0,100);  //reco e_nu 
	const auto &vertex = event->GetPrimaryVertex();
	  coincidence = true;
	  reaction.push_back(event->GetInteractionType());
	  nutype.push_back(event->GetPrimaryParticlePdg());
	  topology.push_back(event->GetInteractionType());
	  cut_branch.push_back(1);
	  weight.push_back(event->GetNormalization());
   	  enu_true.push_back(event->GetPrimaryParticleEnergy().GetValue());
// Reconstructed energy values smaller than 0 (not physical) are set to 0
		if((event->GetPrimaryParticleEnergy().GetValue())+random_enu<0){
		nue = 0;}
		else{
		nue = (event->GetPrimaryParticleEnergy().GetValue())+random_enu;}
	  enu_reco.push_back(nue);
	  NU_E = event->GetPrimaryParticleEnergy().GetValue();
	  NU_E_R = nue;
	  h_e_nu.Fill(NU_E/1000);
	  hr_e_nu.Fill(NU_E_R/1000);
	}

// Get target from vertex summary    
// B2VertexSummary::GetInteractionMaterial
    auto it_vertex = spill_summary.BeginTrueVertex();
    while(const auto *vertex = it_vertex.Next()){
    coincidence = true;
    target.push_back(vertex->GetInteractionMaterial());
	}
   
// Get muon momentum and angle and q2 from Track summary
    auto it_track = spill_summary.BeginTrueTrack();
    while(const auto *track =it_track.Next()){
	coincidence = true;
// A random number sampled from a gaussian is added to each  mu_momentum and mu_energy value to create reconstructed mu momentum and angle (D1 and D2)
        double random_mu_mom = gRandom->Gaus(0,100);  //D1 reco mu momentum
	double random_mu_ang = gRandom->Gaus(0,5); //D2 reco angle
      if (track->GetParticlePdg() == 13){	//muon negative
	D1True.push_back(track->GetInitialAbsoluteMomentum().GetValue());
// Reconstructed energy values smaller than 0 (not physical) are set to 0
	if ((track->GetInitialAbsoluteMomentum().GetValue()+random_mu_mom)<0){
		mup = 0;}
	else{
		mup = (track->GetInitialAbsoluteMomentum().GetValue()+random_mu_mom);}
	D1Reco.push_back(mup);
	h_p_mu.Fill((track->GetInitialAbsoluteMomentum().GetValue())/1000);
	hr_p_mu.Fill((mup)/1000); 
	
	angle.push_back(track->GetAngle().GetValue());
	angle_r.push_back((track->GetAngle().GetValue())+random_mu_ang);
	D2True.push_back(cos(track->GetAngle().GetValue()));
        D2Reco.push_back(cos((track->GetAngle().GetValue())+random_mu_ang));
	h_cos.Fill(cos(track->GetAngle().GetValue()));
	hr_cos.Fill(cos((track->GetAngle().GetValue())+random_mu_ang));
	h_a.Fill(track->GetAngle().GetValue());
	hr_a.Fill((track->GetAngle().GetValue())+random_mu_ang);	
	
// Calculate muon energy and Q2 and fill histogram for Q2 
// Muon energy can be directly obtained using track->GetTotalEnergy().GetValue() , but is calculated to be consistent with fitter
	double MU_E = sqrt((track->GetInitialAbsoluteMomentum().GetValue())*(track->GetInitialAbsoluteMomentum().GetValue())+mu_mass*mu_mass);
	double Q2 = 2*NU_E*(MU_E-(track->GetInitialAbsoluteMomentum().GetValue())*cos((track->GetAngle().GetValue())))-mu_mass*mu_mass; //MeV
	double MU_E_R = sqrt(mup*mup+mu_mass*mu_mass);
	double Q2_R = 2*NU_E_R*(MU_E_R-mup*(cos((track->GetAngle().GetValue())+random_mu_ang)))-mu_mass*mu_mass; //MeV
        q2_true.push_back(Q2);
	q2_reco.push_back(Q2_R);
	h_q2.Fill(Q2/1000000);
	hr_q2.Fill(Q2_R/1000000);
	}
//      }  

	
    if (coincidence){
	 out_trutree->Fill();
 	 out_seltree->Fill();
	}	 
	nutype.clear();
	nutype_true.clear();
	reaction.clear();
	reaction_true.clear();
	topology.clear();
	topology_true.clear();
	target.clear();
	target_true.clear();
	cut_branch.clear();
	D1True.clear();
	D1Reco.clear();
	D2True.clear();
	D2Reco.clear();
	enu_true.clear();
	enu_reco.clear();
	q2_true.clear();	
	q2_reco.clear();
	weight.clear();
	weight_true.clear();
	angle.clear();
	angle_r.clear();

	}      
      }     
    } catch (const std::exception &error) {    
      BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what(); 
      return EXIT_FAILURE;
    }
  }
      
 TCanvas *plots = new TCanvas("plots","Plots");
 plots-> SetCanvasSize(60,50);
 plots-> SetWindowSize(300,200);
 plots->SetBottomMargin(0.12);
 plots->SetLeftMargin(0.17);
// plots->SetLabelSize(size = 0.02, * axis = "XY");
// TStyle.SetTitleSize(size = 0.2, * axis = "XY");
// TStyle::SetTitleFontSize(size = 0.03);
// plots->cd();

 h_e_nu.GetXaxis()->SetLabelSize(0.05);
 h_e_nu.GetYaxis()->SetLabelSize(0.05);
 h_e_nu.GetXaxis()->SetLabelOffset(0.01);
 h_e_nu.GetXaxis()->SetTitleSize(0.05);
 h_e_nu.GetYaxis()->SetTitleSize(0.05);
 h_e_nu.GetXaxis()->SetRangeUser(0,3);
 h_e_nu.Draw();
 plots->Update();
 plots->Print("True_neutrino_energy.pdf");

// h_e_mu.Draw();
// plots->Update();
// plots->Print("Energy_muon.pdf");
 
 h_q2.GetXaxis()->SetLabelSize(0.05);
 h_q2.GetYaxis()->SetLabelSize(0.05);
 h_q2.GetXaxis()->SetLabelOffset(0.01);
 h_q2.GetXaxis()->SetTitleSize(0.05);
 h_q2.GetYaxis()->SetTitleSize(0.05);
 h_q2.Draw();
 plots->Update();
 plots->Print("True_Q2.pdf");

 h_p_mu.GetXaxis()->SetLabelSize(0.05);
 h_p_mu.GetYaxis()->SetLabelSize(0.05);
 h_p_mu.GetXaxis()->SetLabelOffset(0.01);
 h_p_mu.GetXaxis()->SetTitleSize(0.05);
 h_p_mu.GetYaxis()->SetTitleSize(0.05);
 h_p_mu.GetXaxis()->SetRangeUser(0,3);
 h_p_mu.Draw();
 plots->Update();
 plots->Print("True_mu_momentum.pdf");

 h_a.GetXaxis()->SetLabelSize(0.05);
 h_a.GetYaxis()->SetLabelSize(0.05);
 h_a.GetXaxis()->SetLabelOffset(0.01);
 h_a.GetXaxis()->SetTitleSize(0.05);
 h_a.GetYaxis()->SetTitleSize(0.05);
 h_a.Draw();
 plots->Update();
 plots->Print("True_mu_angle.pdf");


 hr_e_nu.GetXaxis()->SetLabelSize(0.05);
 hr_e_nu.GetYaxis()->SetLabelSize(0.05);
 hr_e_nu.GetXaxis()->SetLabelOffset(0.01);
 hr_e_nu.GetXaxis()->SetTitleSize(0.05);
 hr_e_nu.GetYaxis()->SetTitleSize(0.05);
 hr_e_nu.GetXaxis()->SetRangeUser(0,3);
 hr_e_nu.Draw();
 plots->Update();
 plots->Print("Reco_neutrino_energy.pdf");

 hr_q2.GetXaxis()->SetLabelSize(0.05);
 hr_q2.GetYaxis()->SetLabelSize(0.05);
 hr_q2.GetXaxis()->SetLabelOffset(0.01);
 hr_q2.GetXaxis()->SetTitleSize(0.05);
 hr_q2.GetYaxis()->SetTitleSize(0.05);
 hr_q2.Draw();
 plots->Update();
 plots->Print("Reco_Q2.pdf");


 hr_p_mu.GetXaxis()->SetLabelSize(0.05);
 hr_p_mu.GetYaxis()->SetLabelSize(0.05);
 hr_p_mu.GetXaxis()->SetLabelOffset(0.01);
 hr_p_mu.GetXaxis()->SetTitleSize(0.05);
 hr_p_mu.GetYaxis()->SetTitleSize(0.05);
 hr_p_mu.GetXaxis()->SetRangeUser(0,3);
 hr_p_mu.Draw();
 plots->Update();
 plots->Print("Reco_mu_momentum.pdf");

 hr_a.GetXaxis()->SetLabelSize(0.05);
 hr_a.GetYaxis()->SetLabelSize(0.05);
 hr_a.GetXaxis()->SetLabelOffset(0.01);
 hr_a.GetXaxis()->SetTitleSize(0.05);
 hr_a.GetYaxis()->SetTitleSize(0.05);
 hr_a.Draw();
 plots->Update();
 plots->Print("Reco_mu_angle.pdf");

 h_cos.GetXaxis()->SetLabelSize(0.05);
 h_cos.GetYaxis()->SetLabelSize(0.05);
 h_cos.GetXaxis()->SetLabelOffset(0.01);
 h_cos.GetXaxis()->SetTitleSize(0.05);
 h_cos.GetYaxis()->SetTitleSize(0.05);
 h_cos.Draw();
 plots->Update();
 plots->Print("True_cos_angle.pdf");

 hr_cos.GetXaxis()->SetLabelSize(0.05);
 hr_cos.GetYaxis()->SetLabelSize(0.05);
 hr_cos.GetXaxis()->SetLabelOffset(0.01);
 hr_cos.GetXaxis()->SetTitleSize(0.05);
 hr_cos.GetYaxis()->SetTitleSize(0.05);
 hr_cos.Draw();
 plots->Update();
 plots->Print("Reco_cos_angle.pdf");

 out_trutree->Draw("nutype");
 plots->Update();
 plots->Print("NuType.pdf");

 out_trutree->Draw("topology");
 plots->Update();
 plots->Print("Topology.pdf");

 out_trutree->Draw("reaction");
 plots->Update();
 plots->Print("Reaction.pdf");

 out_trutree->Draw("cut_branch");
 plots->Update();
 plots->Print("cut_branch.pdf");


 out_trutree->Draw("target");
 plots->Update();
 plots->Print("Target.pdf");

 out_trutree->Draw("weight");
 plots->Update();
 plots->Print("Weight.pdf");


ofile->cd();
out_trutree->Write();
out_seltree->Write();
ofile->Close();


 BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
 return EXIT_SUCCESS;
}
