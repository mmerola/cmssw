


void doPlot(TString sample, TString observable, TString lepton, bool normToData, bool table)
{
#include <string>;
//#include <map>;
  gStyle->SetHistMinimumZero();
//  gStyle->SetPalette(1);
//  gStyle->SetOptStat(1111);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
//  gStyle->SetFillColor(0);
  gStyle->SetOptStat(0);
//  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");
  gStyle->SetTitleSize(0.055,"xyz");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleOffset(1.15,"x");
  gStyle->SetTitleOffset(1.5,"y");



// For the axis:

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

  gStyle->SetPaperSize(20.,20.);
  gStyle->SetTextSize(0.045);




TString folder = "/afs/cern.ch/work/m/mmerola/TreesxCombination/event_trees_naples/";
TString channel = "Data";
//TString postfix_file = "_newBTag";
TString postfix_file = "";


// using std::TString;

// TString sample ="";
// TString sample ="3J2T";
// TString sample ="WSample";
 // TString sample ="_step_0";

 cout << "sample:   " << sample << "  observable: " << observable << "  lepton: " << lepton << endl;

 bool qcdcut = true;

 if ( observable =="costhetalj")  { double observableMin = -1;   double observableMax = 1;   TString observableName = "cos#theta^{*}"; double nBins = 10;}
 if ( observable == "topMass")    { double observableMin = 100;   double observableMax = 300;  TString observableName = "m_{lb#nu} (GeV)"; double nBins = 20;}
 if ( observable == "bJetPt")     { double observableMin = 30;   double observableMax = 200;  TString observableName = "b jet p_{T}"; double nBins = 17;}
 if ( observable == "fJetPt")     { double observableMin = 30;   double observableMax = 200;  TString observableName = "light jet p_{T}"; double nBins = 17;}
 if ( observable == "bJetEta")    { double observableMin = -5;   double observableMax = 5;  TString observableName = "b jet #eta"; double nBins = 20;}
 if ( observable == "fJetEta")    { double observableMin = -5;   double observableMax = 5;  TString observableName = "light jet #eta"; double nBins = 20;}
 if ( observable == "eta" ) 	  { double observableMin = 0;   double observableMax = 5; TString observableName = "|#eta_{j'}|"; double nBins = 20;} 
 if ( observable == "leptonPt")   { double observableMin = 20;   double observableMax = 150;  TString observableName = "lepton p_{T}"; double nBins = 13;}
 if ( observable == "leptonEta")  { double observableMin = -3;   double observableMax = 3;  TString observableName = "lepton #eta"; double nBins = 15;}
 if ( observable == "mtwMass")    { double observableMin = 0;   double observableMax = 200;  TString observableName = "m_{T}(GeV)"; double nBins = 15; qcdcut=false;}
 if ( observable == "metPt")      { double observableMin = 0;   double observableMax = 200;  TString observableName = "E_{T}^{miss} (GeV)"; double nBins = 30; qcdcut=false;}
 if ( observable == "DeltaPhi_lepmet")  { double observableMin = -6.28;   double observableMax = 6.28;  TString observableName = "#Delta#phi_{l,#nu}"; double nBins = 20; 
                                          TString observable2 = "leptonPhi-metPhi";}
 if ( observable == "DeltaPhi_j1j2")    { double observableMin = -6.28;   double observableMax = 6.28;  TString observableName = "#Delta#phi_{j1,j2}"; double nBins = 20;
                                          TString observable2 = "fJetPhi-bJetPhi";}
 if ( observable == "DeltaPhi_fjettop") { double observableMin = -6.28; double observableMax = 6.28;  TString observableName = "#Delta#phi_{light jet,top}"; double nBins = 30;
                                          TString observable2 = "fJetPhi-topPhi";}
 if ( observable == "DeltaEta_j1j2")    { double observableMin = -5.;   double observableMax = 5.;  TString observableName = "#Delta#eta_{j1,j2}"; double nBins = 30;
                                          TString observable2 = "fJetEta-bJetEta";}



 TString cutMuSR   = "totalWeight*(mtwMass>40. && (topMass < 220 && topMass > 130 )  )"; 
 TString cutMuSB   = "totalWeight*(mtwMass>40. && (topMass > 220 || topMass < 130 )  )"; 
 TString cutEleSR  = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794*(metPt>35. && (topMass < 220 && topMass > 130 )  )"; 
 TString cutEleSB  = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794*(metPt>35. && (topMass > 220 || topMass < 130 )  )"; 

 TString cutMuSRData   = "(mtwMass>40. && (topMass < 220 && topMass > 130 )  )"; 
 TString cutMuSBData   = "(mtwMass>40. && (topMass > 220 || topMass < 130 )  )"; 
 TString cutEleSRData  = "(metPt>35. && (topMass < 220 && topMass > 130 )  )"; 
 TString cutEleSBData  = "(metPt>35. && (topMass > 220 || topMass < 130 )  )"; 



  if (lepton == "Ele"){
//    TString cut = "totalWeight*( metPt>35.)";
//    TString cutQCD = "( metPt>35.)";
//    TString cutData = cutQCD;

    if (table == false && normToData == true){
      TString cutQCD = "(costhetalj<0.98 && metPt>35. && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 )";
//      TString cutQCD = "(metPt>35.)";
      TString cut = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794 *( costhetalj<1. && metPt>35. && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
      TString cutData = "(metPt>35. )";
    }
   
    if (table == false && normToData == false){
//      TString cut = "(totalWeight*705 + (totalWeight/turnOnWeight)*214 )/920 * ( metPt>35.)";
      TString cut = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794 *  ( metPt>35.)";
      TString cutQCD = "( metPt>35.)";
      TString cutData = cutQCD;


    }

    if (table == true){
     // TString cut = "(totalWeight*1297. + (totalWeight/turnOnWeight)*216 )/1513. * (  metPt>35. )";
      TString cut = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794* (  metPt>35. )";
      TString cutQCD = "(  metPt>35. )";
      TString cutData = "(  metPt>35. )";
    }

  }

  else if (lepton == "Mu"){
//    TString cut = "totalWeight*( mtwMass>40.)";
//    TString cutQCD = "(mtwMass>40.)";
//    TString cutData = cutQCD;

    if ( table == false){
      TString cutQCD = "(costhetalj<0.98 && mtwMass>40. && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 )";
      TString cut = "totalWeight*(costhetalj<1. && mtwMass>40. && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
      TString cutData = "(mtwMass>40.)";

    }

    if (table == true){
//      TString cut = "totalWeight*( mtwMass>40. )";
//      TString cutQCD = "( mtwMass>40. )";
//      TString cutData = "( mtwMass>40. )";
      TString cut = "totalWeight";
      TString cutQCD = "totalWeight";
      TString cutData = "";
    }


  }


 if (table == true){
    observable = "costhetalj";
    normToData = false;
//    cut = cutEleSB;
//    cutData = cutEleSBData; 
//    cutQCD = cutData;
}

 if ((observable == "metPt" || observable == "mtwMass") && (lepton == "Ele" )){
     TString cutQCD = "( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.&& sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.) ";
     TString cut = "(PUWeight*bWeight*weight*(1347.736*turnOnWeight+216.058))/1563.794 * ( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
     TString cutData = "( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
  }

 if ((observable == "metPt" || observable == "mtwMass") && (lepton == "Mu")){
     TString cutQCD = "totalWeight*( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.&& sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.) ";
     TString cut = "totalWeight*( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
     TString cutData = "( costhetalj<0.99 && sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0. && sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0. )";
  }

 
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * Data =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "TChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * TChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "TbarChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * TbarChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "SChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * SChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "SbarChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * SbarChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "TWChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * TWChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "TbarWChannel";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * TbarWChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "TTBar";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * TTBar =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "WJets_wlight";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * WJets_wlight =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "WJets_wbb";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * WJets_wbb =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "WJets_wcc";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * WJets_wcc =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "ZJets_wlight";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * ZJets_wlight =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "ZJets_wbb";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * ZJets_wbb =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "ZJets_wcc";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * ZJets_wcc =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

 channel = "QCD";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * QCD =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 

 channel = "WW";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * WW =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "WZ";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * WZ =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 
 channel = "ZZ";
 TString histoname = observable+TString("_")+channel+sample+TString("_noSyst_")+lepton;
 TH1D * ZZ =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
 

TString plotName = "";
if (observable.Contains("Delta")){
  TString plotName = observable;
  observable = observable2;
  cout << "observable: " << observable << "   plot name: " << plotName  << endl;
}


channel = "Data";
 TString filename = (folder + "/"+channel+postfix_file+".root");
 TFile f(filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f.Get(path))->Project("t",observable,cutData);
cout << " test <"<<endl;
 Data->Add(tmp);
delete tmp;
f.Close();


channel = "TTBar";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 TTBar->Add(tmp,1.);
delete tmp;
f.Close();


channel = "TChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 TChannel->Add(tmp,1.);
delete tmp;
f.Close();


channel = "TbarChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 TbarChannel->Add(tmp,1.);
delete tmp;
f.Close();




channel = "SChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 SChannel->Add(tmp,1.);
delete tmp;
f.Close();


channel = "SbarChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 SbarChannel->Add(tmp,1.);
delete tmp;
f.Close();


channel = "TWChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 TWChannel->Add(tmp);
delete tmp;
f.Close();


channel = "TbarWChannel";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 TbarWChannel->Add(tmp);
delete tmp;
f.Close();


channel = "WJets_wlight";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f(filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 WJets_wlight->Add(tmp,1);
delete tmp;
f.Close();


channel = "WJets_wcc";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 WJets_wcc->Add(tmp,1.);
delete tmp;
f.Close();


channel = "WJets_wbb";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 WJets_wbb->Add(tmp,1.);
delete tmp;
f.Close();


channel = "ZJets_wlight";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 ZJets_wlight->Add(tmp,1.);
delete tmp;
f.Close();

channel = "ZJets_wcc";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 ZJets_wcc->Add(tmp,1.);
delete tmp;
f.Close();


channel = "ZJets_wbb";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 ZJets_wbb->Add(tmp,1.);
delete tmp;
f.Close();



channel = "WW";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 WW->Add(tmp,1.);
delete tmp;
f.Close();

channel = "WZ";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 WZ->Add(tmp,1.);
delete tmp;
f.Close();

channel = "ZZ";
 filename = (folder + "/"+channel+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  
 TString path = "Trees"+lepton+"/"+channel+"_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cut);
cout << " test <<"<<endl;
 ZZ->Add(tmp,1.);
delete tmp;
f.Close();


channel = "QCD";
 filename = (folder + "/"+channel+"Mu"+postfix_file+".root");
//filename = (folder + "/Data"+postfix_file+".root");
 TFile f (filename,"OPEN");
 if( !f.IsOpen() ){
   cout<< " WARNING FILE " << filename << endl;
   continue;
 }  

 TString path = "Trees"+lepton+"/Data_"+sample+"_"+channel+"_noSyst"; 

//QCDMu_2J_2T_noSyst
// TString mupath = "TreesMu/Data_noSystQCD";
// TString mupath = "TreesMu/Data_noSystWSampleQCD";
 TString path = "TreesMu/"+channel+"Mu_"+sample+"_noSyst";
TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
 ((TTree*)f.Get(path))->Project("t",observable,cutQCD);
cout << " test <<"<<endl;
 QCD->Add(tmp);
delete tmp;
f.Close();

cout<< "QCD int: " << QCD->Integral() << endl;

	    THStack hs1("hs1","topmass distribution");
	    QCD->SetFillColor(kGray); 

double Wcorr;
double lumi;
double MCtot_noQCD = WJets_wcc->Integral()+
WJets_wbb->Integral()+
WJets_wlight->Integral()+
ZJets_wcc->Integral()+
ZJets_wbb->Integral()+
ZJets_wlight->Integral()+
TTBar->Integral()+
TChannel->Integral()+
TWChannel->Integral()+
TbarChannel->Integral()+
TbarWChannel->Integral()+
SChannel->Integral()+
SbarChannel->Integral()+
WW->Integral()+
WZ->Integral()+
ZZ->Integral();


double NSIG ;
double NQCD; 
if (lepton=="Mu"){
   lumi = 1170.307;
   
   if ((sample == "") && (qcdcut==true)){
     NQCD = 108.366;
     NSIG = 4531.14;
   }

   if ((sample == "WSample") && (qcdcut==true)){
     NQCD = 2204.29;
     NSIG = 93405.4;
   }

   if ((sample == "") && (qcdcut==false)){
     NQCD = 1550.51;
     NSIG = 5862.71;
//     NQCD = 1414.39;           // MET fit
//     NSIG = 6090.8;           // MET fit


   }

   if ((sample == "WSample") && (qcdcut==false)){
     NQCD = 18770.6;
     NSIG = 120122. ;
   }

}


if (lepton == "Ele"){
  lumi = 1563.794;

   if ((sample == "") && (qcdcut==true)){
     NQCD = 86.2164;
     NSIG = 2586.5;
   }

   if ((sample == "WSample") && (qcdcut==true)){
     NQCD = 206.522;
     NSIG = 8387.6;
   }

   if ((sample == "") && (qcdcut==false)){
     NQCD = 1285.02;
     NSIG = 4670.86;
//     NQCD = 1101.7;         // MTW fit
//     NSIG = 4814.3;         // MTW fit 

   }


   if ((sample == "WSample") && (qcdcut==false)){
     NQCD = 6166.71;
     NSIG = 18932.;
   }

}





MCtot_noQCD *= lumi;
double MCtot = MCtot_noQCD + NQCD;
double QCDscale = NQCD/QCD->Integral();

//double DataMC_ratio = (Data->Integral()/(MCtot));
double DataMC_ratio = NSIG/MCtot_noQCD * (Data->Integral()/(NSIG+NQCD));
QCDscale *= (Data->Integral()/(NSIG+NQCD)); 



if (normToData == false ){
  double DataMC_ratio = 1.;
  QCDscale = NQCD/QCD->Integral();
  if ( sample == "" && lepton == "Ele")
    double DataMC_ratio = 0.97;
  if ( sample == "" && lepton == "Mu")
    double DataMC_ratio = 0.9999;

}

QCD->Scale(lumi); // 2J_2T SAMPLE
//QCD->Scale(QCDscale); // SR + SB or OTHER
//QCD->Scale(QCDscale*0.708745); // SR  Mu
//QCD->Scale(QCDscale*0.291254); // SB  Mu 
//QCD->Scale(QCDscale*0.7243017); // SR  Ele
//QCD->Scale(QCDscale*0.275698); // SB  Ele 
WJets_wcc->Scale(lumi*DataMC_ratio);
WJets_wbb->Scale(lumi*DataMC_ratio);
WJets_wlight->Scale(lumi*DataMC_ratio);
ZJets_wcc->Scale(lumi*DataMC_ratio);
ZJets_wbb->Scale(lumi*DataMC_ratio);
ZJets_wlight->Scale(lumi*DataMC_ratio);
TTBar->Scale(lumi*DataMC_ratio);
TChannel->Scale(lumi*DataMC_ratio);
TbarChannel->Scale(lumi*DataMC_ratio);
SChannel->Scale(lumi*DataMC_ratio*1.9345089);
SbarChannel->Scale(lumi*DataMC_ratio);
TWChannel->Scale(lumi*DataMC_ratio);
TbarWChannel->Scale(lumi*DataMC_ratio);
WW->Scale(lumi*DataMC_ratio);
WZ->Scale(lumi*DataMC_ratio);
ZZ->Scale(lumi*DataMC_ratio);

cout << "QCD integral: " <<  QCD->Integral() << endl;


if (normToData == true){

TH1D * ALLMC =  new TH1D( "ALLMC", "ALLMC", nBins,observableMin,observableMax);

ALLMC->Add(QCD);
ALLMC->Add(WJets_wcc);
ALLMC->Add(WJets_wbb);
ALLMC->Add(WJets_wlight);
ALLMC->Add(ZJets_wlight);
ALLMC->Add(ZJets_wcc);
ALLMC->Add(ZJets_wbb);
ALLMC->Add(TTBar);
ALLMC->Add(TChannel);
ALLMC->Add(TbarChannel);
ALLMC->Add(SChannel);
ALLMC->Add(SbarChannel);
ALLMC->Add(TWChannel);
ALLMC->Add(TbarWChannel);
ALLMC->Add(WW);
ALLMC->Add(WZ);
ALLMC->Add(ZZ);
cout << "KOLMOGOROV:   " << ALLMC->KolmogorovTest(Data,"SumW2") << endl;
cout << "CHI2:         " << ALLMC->Chi2Test(Data,"UW") << endl;
cout << "MC yield:     " << ALLMC->Integral() << "   Data yield: "  << Data->Integral() << endl;

}

	    

            hs1.Add(QCD);

	    WW->Add(WZ);
	    ZZ->Add(WW);
	    ZZ->SetFillColor(kAzure); 
	    hs1.Add(ZZ);
	    
	   
	    ZJets_wcc->Add(ZJets_wbb);
            ZJets_wlight->Add(ZJets_wcc);

	    ZJets_wlight->SetFillColor(kBlue-1); 
	    hs1.Add(ZJets_wlight);

	    WJets_wcc->SetFillColor(kGreen+4); 
	    hs1.Add(WJets_wcc);

	    WJets_wbb->SetFillColor(kGreen+3); 
	    hs1.Add(WJets_wbb);

	    WJets_wlight->SetFillColor(kGreen+1); 
	    hs1.Add(WJets_wlight);

	    TTBar->SetFillColor(kOrange-3); 
	    hs1.Add(TTBar);

	    TWChannel->Add(TbarWChannel);
	    TWChannel->SetFillColor(kOrange); 
	    hs1.Add(TWChannel);
	    

            TChannel->Add(TbarChannel);
	    TChannel->SetFillColor(kRed); 
	    hs1.Add(TChannel);
 	    
	    SChannel->Add(SbarChannel);
	    SChannel->SetFillColor(kYellow); 
	    hs1.Add(SChannel);
   
	    
if (table == true){

ofstream texFile("Table_"+sample+lepton+".txt");

double total = ZZ->Integral()+
WJets_wcc->Integral()+
WJets_wbb->Integral()+
WJets_wlight->Integral()+
ZJets_wlight->Integral()+
TTBar->Integral()+
TChannel->Integral()+
TWChannel->Integral()+
SChannel->Integral()+
QCD->Integral();



texFile << endl;
texFile << "\\hline " << endl;
texFile << "Process & entries \\\\ "	<<  endl;
texFile << "\\hline" << endl;
texFile << "$t$-channel & "         << TChannel->Integral() << " \\\\ " << endl;
texFile << "tW channel & "        << TWChannel->Integral() << " \\\\ " << endl;
texFile << "$s$-channel & "         << SChannel->Integral() << " \\\\ " << endl;
texFile << "$\\ttbar$ & "          << TTBar->Integral() << " \\\\ " << endl;
texFile << "W + light partons & " << WJets_wlight->Integral() << " \\\\ " << endl;
texFile << "Z + jets & "          << ZJets_wlight->Integral() << " \\\\ " << endl;
texFile << "Wc($\\bar{\\mathrm{c}}$) & "     << WJets_wcc->Integral() << " \\\\ " << endl;
texFile << "Wb($\\bar{\\mathrm{b}}$) & "     << WJets_wbb->Integral() << " \\\\ " << endl;
texFile << "Diboson & "             <<  ZZ->Integral()  << " \\\\ " << endl;
texFile << "QCD & "                 << QCD->Integral() << " \\\\ " << endl;
texFile << "\\hline" << endl;
texFile << "Total & "               << total << " \\\\ " << endl;
texFile << "\\hline" << endl;
texFile << "Data & "                << Data->Integral() << " \\\\ " << endl;

 
}

if (table == false ){

	    TCanvas C3("c3","c3"); 
//	    C3.cd()->SetRightMargin(0.04);
	    C3.SetLeftMargin(0.16);
	    C3.SetRightMargin(0.2);
            C3.SetBottomMargin(0.15);
	    Data->Draw("E1");
	    hs1.Draw("hist same");
	    hs1.Draw("axissame");
	    Data->SetMarkerStyle(20);
	    Data->Draw("E1 same");
	    
	    hs1.SetTitle(observableName);
	    Data -> SetTitle(observableName);
	    hs1.SetTitle("");
	    Data -> SetTitle("");
//            Data -> GetXaxis() -> SetTitleOffset(0.9);
//            Data -> GetYaxis() -> SetTitleOffset(1.);
	    hs1.GetXaxis() -> SetTitle(observableName);
	    Data -> GetXaxis() -> SetTitle(observableName);
	    hs1.GetYaxis() -> SetTitle("Events");
	    Data -> GetYaxis() -> SetTitle("Events");
//            Data -> GetXaxis() -> SetTitleSize(0.05);
//   	      Data -> GetYaxis() -> SetTitleSize(0.05);

cout << "test <<<" <<endl;
	    //	    Data -> GetXaxis() -> SetTitle("title");
	    

	Data -> GetYaxis() -> SetRangeUser(0.,1.25* (Data->GetMaximum()));
	    
	    Data->Draw("E1 same");
	    Data->Draw("axissame");
	    
	    // hs1.GetXaxis() -> SetTitle("cos#theta* ");
	    // hs1.GetYaxis() -> SetTitle("Events / 0.2 ");
	    //Data -> GetXaxis() -> SetTitle((name+"stack").c_str());
	    //	    Data -> GetYaxis() -> SetTitle("Events / 0.2 ");
	    

cout << "test <<<<" <<endl;

	    TLegend * leg = new TLegend(0.81,0.35,0.95,0.90);
	    leg->SetBorderSize(0);
	    leg->SetLineStyle(0);
	    //  leg->SetTextFont(42);
	    leg->SetTextSize(0.037);
	    leg->SetFillStyle(0);
	    leg->SetFillColor(0);
	    
	    leg->AddEntry(Data,"data","pl");
	    leg->AddEntry(SChannel,"s-channel","f");
	    leg->AddEntry(TChannel,"t-channel","f");
	    leg->AddEntry(TWChannel,"tW-channel","f");
	    leg->AddEntry(TTBar,"t#bar{t}","f");
	    leg->AddEntry(WJets_wlight,"W+light","f");
	    leg->AddEntry(WJets_wbb,"W+b(#bar{b})","f");
	    leg->AddEntry(WJets_wcc,"W+c(#bar{c})","f");
	    leg->AddEntry(ZJets_wlight,"Z+Jets","f");
	    leg->AddEntry(ZZ,"Diboson ","f");
	    leg->AddEntry(QCD,"QCD ","f");
	    leg->Draw();
	    
cout << "test <<<<<" <<endl;

// 	    TLatex * tex = new TLatex(0.15,0.97,"muons");
	    if (lepton == "Ele")
 	     TLatex * tex = new TLatex(0.17,0.96,"CMS Preliminary, 1.56 fb^{-1}, Electrons, #sqrt{s} = 7 TeV");
	    if (lepton == "Mu")
 	     TLatex * tex = new TLatex(0.188,0.96,"CMS Preliminary, 1.17 fb^{-1}, Muons, #sqrt{s} = 7 TeV");
	    tex->SetNDC();
            tex->SetTextAlign(13);
 	    tex->SetTextFont(42);
//	    tex->SetLineWidth(1.8);
 	    tex->Draw();

if (plotName.Contains("Delta"))
   observable = plotName;

//	    C3.SaveAs(sample+observable+lepton+"Stack.gif");
//            C3.SaveAs(sample+observable+lepton+"Stack.pdf");
//            C3.SaveAs(sample+observable+lepton+"Stack.png");
//	    C3.SaveAs(sample+observable+lepton+"Stack.root");
	    C3.SaveAs(sample+observable+lepton+"Stack.C");

}

}
