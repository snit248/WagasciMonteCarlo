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

int main(int argc, char *argv[]) {
//  if (argc != 2) {
//    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
//    return EXIT_SUCCESS;
//  }

//  try {
//    B2Reader reader(argv[1]);
//    B2Writer writer("test_output.root", reader);
//    auto *ofile = new TFile(output_file_name, "recreate");
//    auto *tree = new TTree("tree","tree");

TFile* out_file = TFile::Open("~/WagasciMC/data/e_nu.root", "RECREATE");
TTree* tree = new TTree("tree","tree");
TTree* out_seltree = new TTree("seltree", "seltree");
TTree* out_trutree = new TTree("trutree", "trutree");


    const float mu_mass = 105.658374;
    int nutype, nutype_true;
    int reaction, reaction_true;
    int topology, topology_true;
    int target, target_true;
    int cut_branch;
    float enu_true, enu_reco, e_nu;
    float q2_true, q2_reco;
    float D1True, D1Reco;
    float D2True, D2Reco;
    float weight, weight_true;

    out_seltree -> Branch("nutype", &nutype, "nutype/I");
    out_seltree -> Branch("reaction", &reaction, "reaction/I");
    out_seltree -> Branch("topology", &topology, "topology/I");
    out_seltree -> Branch("target", &target, "target/I");
    out_seltree -> Branch("cut_branch", &cut_branch, "cut_branch/I");
    out_seltree -> Branch("enu_true", &enu_true, "enu_true/F");
    out_seltree -> Branch("enu_reco", &enu_reco, "enu_reco/F");
    out_seltree -> Branch("q2_true", &q2_true, "q2_true/F");
    out_seltree -> Branch("q2_reco", &q2_reco, "q2_reco/F");
    out_seltree -> Branch("D1True", &D1True, "D1True/F");
    out_seltree -> Branch("D1Reco", &D1Reco, "D1Reco/F");
    out_seltree -> Branch("D2True", &D2True, "D2True/F");
    out_seltree -> Branch("D2Reco", &D2Reco, "D2Reco/F");
    out_seltree -> Branch("weight", &weight, "weight/F");

    out_trutree -> Branch("nutype", &nutype_true, "nutype/I");
    out_trutree -> Branch("reaction", &reaction_true, "reaction/I");
    out_trutree -> Branch("topology", &topology_true, "topology/I");
    out_trutree -> Branch("target", &target_true, "target/I");
    out_trutree -> Branch("cut_branch", &cut_branch, "cut_branch/I");
    out_trutree -> Branch("enu_true", &enu_true, "enu_true/F");
    out_trutree -> Branch("q2_true", &q2_true, "q2_true/F");
    out_trutree -> Branch("D1True", &D1True, "D1True/F");
    out_trutree -> Branch("D2True", &D2True, "D2True/F");
    out_trutree -> Branch("weight", &weight_true, "weight/F");

    tree -> Branch("Enu",&e_nu, "e_nu/F");


// Get the Ne energy from the NEUT file and put it in a histogram with bin width 50MeV
TFile* file_input = TFile::Open("~/WagasciMC/data/sample_neut_files/13a_nd7_posi250_numu_h2o_1.root", "READ");
TH1D h_e_nu("e_nu", "Nu energy from NEUT file;nu energy (MeV);number of nu", 200,0,10000);

TTree* hl2_tree = (TTree*)file_input -> Get("h10");


	hl2_tree -> SetBranchAddress("Enu", &e_nu);

        int nevents = hl2_tree -> GetEntries();
        std::cout << "nevents = " << nevents << std::endl;
	for(int i = 0; i < nevents; ++i)
        {
            hl2_tree -> GetEntry(i);
            tree -> Fill();
            if(e_nu>0.050){
	    h_e_nu.Fill(e_nu*1000);	    	    
            }
	}
// Get true momentum and angle of muon, nu energy and q2 and introduce smearing to fill reconstructed parameters (D1Reco, D2Reco, enu_reco, q2_reco)
TFile* input = TFile::Open("/home/t2k/adocheva/WagasciMC/data/WagD/output_0000.root","READ");
//TTree




 file_input -> Close();
  
      
 TCanvas *plots = new TCanvas("plots","Plots");
 plots->cd();

 h_e_nu.Draw();
 plots->Update();
 plots->Print("Energy_NU.pdf");
 
out_file -> cd();
out_file -> Write();
out_file -> Close();


 BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
 return EXIT_SUCCESS;
}
