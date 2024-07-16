#define GenParticleZ_cxx
//#include "GenParticleZ.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "GenParticleZ.C"


void Z_Nano(){


    gROOT->ProcessLine(".L ~/tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TFile* nano_file = new TFile("/Users/gbibim/Here/genparticleZ/Zto2Q-4Jets_HT-400to600.root");
    GenParticleZ* nano_t = new GenParticleZ((TTree*)nano_file->Get("Events"));

    char temp[100];
    
    TH1F *pt_nano = new TH1F("Z Pt", "; p_T [GeV];Events",100,0.0,500.0);
    //TH1F *pt_nano = new TH1F();
    pt_nano->SetLineWidth(2);
    pt_nano->SetLineStyle(2);
    pt_nano->SetLineColor(4);
    
    TH1F *pt_notrig = new TH1F("Z Pt no trigger", "; p_T [GeV];Events",100,0.0,500.0);
    //TH1F *pt_nano = new TH1F();
    pt_notrig->SetLineWidth(2);
    pt_notrig->SetLineStyle(2);
    pt_notrig->SetLineColor(4);

    int numEvents = nano_t->fChain->GetEntriesFast();
    //cout << numEvents << endl;
    for( int evt = 0 ; evt < numEvents ; evt++ ){
        nano_t->GetEntry(evt);
        for(int j=0; j < nano_t->nGenPart; j++ ){
            if (nano_t->GenPart_pdgId[j]==23){
                pt_notrig->Fill(nano_t->GenPart_pt[j]);
                if(nano_t->HLT_AK8PFJet230_SoftDropMass40!=0){//0:fail, 1:veto, 2:loose, 3:medium, 4:tight
                    pt_nano->Fill(nano_t->GenPart_pt[j]);
                    //cout << nano_t->GenPart_pt[j] << endl;
                }
            }
        }
    }

    TH1F *h3 = new TH1F("Z Pt", "; p_T [GeV];Events",100,0.0,500.0);
    h3->Divide(pt_nano,pt_notrig);

    TCanvas* can = new TCanvas("can","can",500,500);
    //can->SetLogy();
    h3->Draw();
    can->BuildLegend(0.4,0.9, 0.6, 0.9);
    can->SaveAs("Z_pt_final.pdf");
    //cout << e_pt_nano[j]->GetEntries() << endl;


   
}
    

