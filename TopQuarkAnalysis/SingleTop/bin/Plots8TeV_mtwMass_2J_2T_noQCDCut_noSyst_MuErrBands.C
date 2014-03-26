{
#include <string>;

  /*  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.03, "XYZ");


  // For the axis:

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame                                                                          
  gStyle->SetPadTickY(1);

// Change for log plots:                                                                                                                                     
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);

// Postscript options:                                                                                                                                       
  gStyle->SetPaperSize(20.,20.);
  */


  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  //tdrStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.02);
  //tdrStyle->SetPadRightMargin(0.2);



  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleX(0.22); // Set the position of the title box
  gStyle->SetTitleY(1.02); // Set the position of the title box

  // For the axis labels:
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);

  gStyle->SetCanvasBorderMode(0);

  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.008, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");


  // For the axis:                                                                                                                                             

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame                                                                          
  gStyle->SetPadTickY(1);

  // Change for log plots:                                                                                                                                     
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);

  // Postscript options:                                                                                                                                       
  gStyle->SetPaperSize(20.,20.);

  double lumi = 5006.;
  lumi = 1.;
  
  TString folder = "/tmp/mmerola/";
  TString channel = "Data";
  TString channelup = "Data";
  TString channeldown = "Data";
  TString lepton = "Mu";

  TString sample ="2J_2T";
  TString samplejes = sample +"_JES";
  TString sampleqcd = sample + "_QCD_noSyst"; 
  //  TString sampleqcd = "2J_0T_QCD_noSyst"; 
  sample = sample+ "_noSyst";
  TString Wsample = "noSystWSample";  
  
  double WJetsScale = 1.0;
  double QCDIntegral = -1.0;
  double TTBarScale = 1.0;
 QCDIntegral = 25.; WJetsScale = 1.; TTBarScale =1.;  


  bool scaleToData = true; //  scaleToData = true;
  bool nosig = false;
  bool dorescale = false;
  bool dolog = false;

  TString postfix_file = "";
  TString postfix = "PU";
  

TString observable = "mtwMass";   double observableMin = 0;   double observableMax = 250;  TString observableName = "m_{T}(GeV)"; Int_t nBins = 20;TString oTitle = observable;

  double FracTTBar = 1;
  double FracTbarChannel = 1;
  double FracTChannel = 1;
  double FracTbarWChannel = 1;
  double FracTWChannel = 1;
  double FracSbarChannel = 1;
  double FracSChannel = 1;
  double FracWJets = 373./373./1.0*1.0;
  double FracZJets = 1;
  
  //  double nBins = ;  

  TString KinCut = TString("*(leptonRelIso<10.06 && bJetPt>40 && fJetPt>40)");
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-fJetPhi)**2+(leptonEta-fJetEta)**2)>0.3 && sqrt((leptonPhi-bJetPhi)**2+(leptonEta-bJetEta)**2)>0.3  )";
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)>-0.3 && sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)<50 && sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)>-0.3 && sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)<50 )";

  TString KinCutQCDDD = TString("(sqrt((leptonPhi-fJetPhi)**2+(leptonEta-fJetEta)**2)>0.3 && sqrt((leptonPhi-bJetPhi)**2+(leptonEta-bJetEta)**2)>0.3)");
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)>0.3 && sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)>0.3 )";
  
  //  TString cut = "weight*(890*leptonSF + (4428)*leptonSFB +(495.003+5109+1288)*leptonSFC)*bWeight*PUWeight";
  //  TString cut = "weight*leptonEff*bWeight*PUWeight*12100"; //12210.003;
  //  TString cut = "weight*(4428)*bWeight";

  TString cut = "(PUWeight*bWeight*weight*(3901.813*turnOnWeight+1197.261))"; //5099.074
  TString cut_bWeightUp = "(PUWeight*bWeightBTagUp*weight*(3901.813*turnOnWeight+1197.261))"; //5099.074
  TString cut_bWeightDown = "(PUWeight*bWeightBTagDown*weight*(3901.813*turnOnWeight+1197.261))"; //5099.074

  
  
  TString cutW = "*(1.0)";
  TString MCCut = "";
  TString cutData="1."; 
  TString cutDataQCD;

  cutW = cut + cutW + KinCut + MCCut;
  cut = cut + KinCut + MCCut;
  cut_bWeightUp = cut_bWeightUp + KinCut + MCCut;
  cut_bWeightDown = cut_bWeightDown + KinCut + MCCut;
  cutData = cutData + KinCut; 
  cutDataQCD = KinCutQCDDD;
  cout << "CUTSTRING " << cutDataQCD << endl;
  //  cutDataQCD = "(secondJetPt > 0. && bJetDecRMS < 10.025 && bJetFinRMS < 10.025 && thirdJetPt>40)*(0.995*0.995)"+ KinCutQCDDD;
  //  cutDataQCD = "(secondJetPt > 0. && bJetDecRMS < 10.025 && bJetFinRMS < 10.025 )*(0.995*0.995)"+ KinCutQCDDD;
  //  cutDataQCD = "(secondJetPt > 0. && bJetRMS < 10.025 && fJetRMS < 10.025 )*(0.995*0.995)"+ KinCutQCDDD;
  //  cutDataQCD = "(secondJetPt > 0. && bJetRMS < 10.025 && fJetRMS < 0.025 && bJetPt>60  && fJetPt>60  )*(0.995*0.995)"+ KinCutQCDDD;
  //  cutDataQCD = "(secondJetPt > 0. )*(0.995*0.995)"+ KinCutQCDDD;

  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * Data =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBar";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBar =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBarQ2up";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarQ2up =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBarQ2down";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarQ2down =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
   
  channel = "TTBar_MatchingUp";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBar_MatchingUp =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBar_MatchingDown";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBar_MatchingDown =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
   
  channel = "TTBarJESup";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarJESup =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBarJESdown";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarJESdown =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
   
  channel = "TTBarBTagup";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarBTagup =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TTBarBTagdown";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TTBarBTagdown =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "TChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "TbarChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TbarChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "SChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * SChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "SbarChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * SbarChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "TWChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TWChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "TbarWChannel";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * TbarWChannel =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "WJets";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * WJets =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsWsample";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsWsample =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsQ2up";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsQ2up =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsQ2down";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsQ2down =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsJESup";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsJESup =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsJESdown";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsJESdown =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "WJetsBTagup";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsBTagup =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "WJetsBTagdown";
  TString histoname = observable+TString("_")+channel+Wsample+TString("")+lepton;
  TH1D * WJetsBTagdown =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);

  channel = "ZJets";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * ZJets =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "QCDMu";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * QCDMu =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "WW";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * WW =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  /*  
  channel = "WZ";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * WZ =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  channel = "ZZ";
  TString histoname = observable+TString("_")+channel+sample+TString("")+lepton;
  TH1D * ZZ =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);
  
  */
  
  channel = "Data";
  TString filename = (folder + "/Data"+postfix_file+".root");
  TFile * f = new TFile (filename,"OPEN");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  cout << mupath << endl;
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutData);
  Data->Add(tmp);
  delete tmp;
  f->Close("R");delete f;
  
  channel = "TTBar";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBar->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  channel = "TTBarQ2up";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBarQ2up->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  channel = "TTBarQ2down";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBarQ2down->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  // TTBar Matching

  channel = "TTBarMatchingup";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/TTBar_MatchingUp_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBar_MatchingUp->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  channel = "TTBarMatchingdown";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/TTBar_MatchingDown_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBar_MatchingDown->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  //TTBAR JES

  channel = "TTBar";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+samplejes+"Up";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBarJESup->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;

  channel = "TTBar";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+samplejes+"Down";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TTBarJESdown->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  // TTBAR BTag

  channel = "TTBar";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut_bWeightUp);
  TTBarBTagup->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;


  channel = "TTBar";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  cout << filename<<endl;
  TFile *f = new TFile (filename,"Open");
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut_bWeightDown);
  TTBarBTagdown->Add(tmp,TTBarScale);
  delete tmp;
  f->Close("R");  
  delete f;
  

  channel = "TChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TChannel->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

  channel = "TbarChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TbarChannel->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

  channel = "SChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  SChannel->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

    channel = "SbarChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  SbarChannel->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;
  
  channel = "TWChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TWChannel->Add(tmp);
  delete tmp;
  f->Close("R");delete f;

  channel = "TbarWChannel";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  TbarWChannel->Add(tmp);
  delete tmp;
  f->Close("R");delete f;

  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJets->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;


  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+Wsample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJetsWsample->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;


  channel = "WJetsQ2up";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+Wsample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJetsQ2up->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;

  channel = "WJetsQ2down";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+Wsample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJetsQ2down->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;


  //WJETS JES

  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+samplejes+"Up";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJetsJESup->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;

  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+samplejes+"Down";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cutW);
  WJetsJESdown->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;


  // WJETS BTag

  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut_bWeightUp);
  WJetsBTagup->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;

  channel = "WJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut_bWeightDown);
  WJetsBTagdown->Add(tmp,WJetsScale);
  delete tmp;
  f->Close("R");delete f;


  channel = "ZJets";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  //  ZJets->Add(tmp,.062);
  ZJets->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

  channel = "WW";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  WW->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;
  /*
  channel = "WZ";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  WZ->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

  channel = "ZZ";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/"+channel+"_"+sample+"";
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  ZZ->Add(tmp,1.);
  delete tmp;
  f->Close("R");delete f;

  */
  channel = "QCDMu";
  //  TString filename = (folder + "/Data"+postfix_file+".root");
  TString filename = ("../../../../../TreesxCombination/event_trees_naples/Data"+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;
  }  
  TString mupath = "TreesMu/"+channel+"_"+sampleqcd+"";
  TString elepath = "TreesMu/Data_"+sampleqcd;
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  ((TTree*)f->Get(elepath))->Project("t",observable,cutDataQCD);
  //((TTree*)f->Get(mupath))->Project("t",observable,cutDataQCD);
  QCDMu->Add(tmp,1.);  
  cout << "QCDdata integral: " << QCDMu->Integral() << endl;
  cout << "filename: " <<  filename << "  treename: " << elepath << endl; 
  
  delete tmp;
  f->Close("R");delete f;


  channel = "QCDMu";
  filename = (folder + "/"+channel+""+postfix_file+".root");
  f = TFile::Open(filename);
  if( !f->IsOpen() ){
    cout<< " WARNING FILE " << filename << endl;
    continue;

  }  
  TString mupath = "TreesMu/"+channel+"_"+sample+"";
  TString elepath = "TreesMu/Data_"+sampleqcd;
  TH1D * tmp  = new TH1D("t","t",nBins,observableMin,observableMax);
  //((TTree*)f->Get(elepath))->Project("t",observable,cutData);
  ((TTree*)f->Get(mupath))->Project("t",observable,cut);
  if (QCDIntegral > 0 ) QCDMu->Scale(QCDIntegral/QCDMu->Integral());
  else QCDMu->Scale(tmp->Integral()/QCDMu->Integral());
  cout << "QCDdata scaled integral: " << QCDMu->Integral() << endl;
  //QCDMu->Scale(10000/QCDMu->Integral());
  delete tmp;
  f->Close("R");delete f;

  //  QCDMu->Add(tmp,1.);


  THStack hs1("hs1","topmass distribution");
  QCDMu->SetFillColor(kGray); 
  //  QCDMu->Smooth(2);
  double sc = 1;


  if(nosig){
    TbarChannel->Reset("ICES");
    TChannel->Reset("ICES");
  }

//   TTBar->Scale(FracTTBar*lumi);
//   TChannel->Scale(FracTChannel*lumi);
//   TbarChannel->Scale(FracTbarChannel*lumi);
//   SChannel->Scale(FracSChannel*lumi);
//   SbarChannel->Scale(FracSbarChannel*lumi);
//   TWChannel->Scale(FracTWChannel*lumi);
//   TbarWChannel->Scale(FracTbarWChannel*lumi);
//   WJets->Scale(FracWJets*lumi);
//   ZJets->Scale(FracZJets*lumi);
//  WJets->Smooth(2);

  double MCtot = QCDMu->Integral()+ 
    WJets->Integral()+ 
    ZJets->Integral()+ 
    WW->Integral()+ 
    /*    WZ->Integral()+ 
	  ZZ->Integral()+ 
    */
    TTBar->Integral()+ 
    TWChannel->Integral()+
    TbarWChannel->Integral()+
    TChannel->Integral()+ 
    TbarChannel->Integral()+ 
    SChannel->Integral()+ 
    SbarChannel->Integral(); 
  
  if(scaleToData){
    double DataMC_ratio = (Data->Integral()/(MCtot));
    
    QCDMu->Scale(DataMC_ratio); 
    WJets->Scale(DataMC_ratio); 
    WJetsWsample->Scale(DataMC_ratio); 
    WJetsQ2up->Scale(DataMC_ratio); 
    WJetsQ2down->Scale(DataMC_ratio); 
    WJetsJESup->Scale(DataMC_ratio); 
    WJetsJESdown->Scale(DataMC_ratio); 
    WJetsBTagup->Scale(DataMC_ratio); 
    WJetsBTagdown->Scale(DataMC_ratio); 
    ZJets->Scale(DataMC_ratio); 
    WW->Scale(DataMC_ratio); 
    /*  WZ->Scale(DataMC_ratio); 
	ZZ->Scale(DataMC_ratio); 
    */
    TTBar->Scale(DataMC_ratio); 
    TTBarQ2up->Scale(DataMC_ratio); 
    TTBarQ2down->Scale(DataMC_ratio); 
    TTBar_MatchingUp->Scale(DataMC_ratio); 
    TTBar_MatchingDown->Scale(DataMC_ratio); 
    TTBarJESup->Scale(DataMC_ratio); 
    TTBarJESdown->Scale(DataMC_ratio); 
    TTBarBTagup->Scale(DataMC_ratio); 
    TTBarBTagdown->Scale(DataMC_ratio); 
    TChannel->Scale(DataMC_ratio);
    TbarChannel->Scale(DataMC_ratio); 
    SChannel->Scale(DataMC_ratio); 
    SbarChannel->Scale(DataMC_ratio); 
    TWChannel->Scale(DataMC_ratio); 
    TbarWChannel->Scale(DataMC_ratio); 
  }

  
  //  nBins += 1 ;
  Float_t TTBar_jesplus[nBins] ;
  Float_t TTBar_jesminus[nBins] ;
  Float_t TTBar_btagplus[nBins] ;
  Float_t TTBar_btagminus[nBins] ;
  Float_t TTBar_uncplus[nBins] ;
  Float_t TTBar_uncminus[nBins] ;
  Float_t TTBar_matchplus[nBins] ;
  Float_t TTBar_matchminus[nBins] ;

  Float_t TTBar_Q2tot = 0. ;

  Float_t WJets_jesplus[nBins] ;
  Float_t WJets_jesminus[nBins] ;
  Float_t WJets_btagplus[nBins] ;
  Float_t WJets_btagminus[nBins] ;
  Float_t WJets_uncplus[nBins] ;
  Float_t WJets_uncminus[nBins] ;

  Float_t WJets_Q2tot = 0. ;

  Float_t Matching_tot = 0.;
  Float_t Q2_tot = 0.;
  Float_t JES_tot = 0.;
  Float_t BTag_tot = 0.;

  Float_t Matching_uncplus[nBins];
  Float_t Matching_uncminus[nBins];
  Float_t Q2_uncplus[nBins];
  Float_t Q2_uncminus[nBins];
  Float_t JES_uncplus[nBins];
  Float_t JES_uncminus[nBins];
  Float_t BTag_uncplus[nBins];
  Float_t BTag_uncminus[nBins];

  Float_t MCtot_vec[nBins] ;

  Float_t Unc_plus[nBins] ;
  Float_t Unc_minus[nBins] ;
  Float_t Unc_tot = 0.;

  Float_t binx[nBins] ;
  Float_t binx_plus[nBins] ;
  Float_t binx_minus[nBins] ;
  for (int i = 1; i <= nBins; ++i ){
    TAxis *xaxis = TTBar->GetXaxis();
    binx[i-1] = xaxis->GetBinCenter(i) ;
    binx_minus[i-1]=(xaxis->GetBinCenter(2)-xaxis->GetBinCenter(1))/2;
    binx_plus[i-1]= (xaxis->GetBinCenter(2)-xaxis->GetBinCenter(1))/2;
    MCtot_vec[i-1] = QCDMu->GetBinContent(i)+
      WJets->GetBinContent(i)+
      ZJets->GetBinContent(i)+
      WW->GetBinContent(i)+
      TTBar->GetBinContent(i)+
      TWChannel->GetBinContent(i)+
      TbarWChannel->GetBinContent(i)+
      TChannel->GetBinContent(i)+
      TbarChannel->GetBinContent(i)+
      SChannel->GetBinContent(i)+
      SbarChannel->GetBinContent(i);

    //    cout << endl;
    //    cout << "bin number i" << endl;
    
    
    WJets_uncminus[i-1] = ((WJetsQ2up->GetBinContent(i) - WJetsWsample->GetBinContent(i))/WJetsWsample->GetBinContent(i))*WJets->GetBinContent(i);
    WJets_uncplus[i-1] =  ((-WJetsQ2down->GetBinContent(i) + WJetsWsample->GetBinContent(i))/WJetsWsample->GetBinContent(i))*WJets->GetBinContent(i);
    
    WJets_Q2tot += (TMath::Abs(WJets_uncminus[i-1]) + TMath::Abs(WJets_uncplus[i-1]))/2.; 
    
    WJets_jesminus[i-1] = WJetsJESup->GetBinContent(i) - WJets->GetBinContent(i);
    WJets_jesplus[i-1] =  -WJetsJESdown->GetBinContent(i) + WJets->GetBinContent(i);

    WJets_btagminus[i-1] = WJetsBTagup->GetBinContent(i) - WJets->GetBinContent(i);
    WJets_btagplus[i-1] =  -WJetsBTagdown->GetBinContent(i) + WJets->GetBinContent(i);
    
    
    //    cout << " Q2 ONLY  WJets_uncminus[i-1]: " << WJets_uncminus[i-1] << "  WJets_uncplus[i-1]: " <<  WJets_uncplus[i-1] << endl;
    //    cout << " JES ONLY WJets_jesminus[i-1]: " << WJets_jesminus[i-1] << "  WJets_jesplus[i-1]: " <<  WJets_jesplus[i-1] << endl;
    //    cout << " BTAG ONLY WJets_btagminus[i-1]: " << WJets_btagminus[i-1] << "  WJets_btagplus[i-1]: " <<  WJets_btagplus[i-1] << endl;
    
    
    TTBar_uncminus[i-1] = TTBarQ2up->GetBinContent(i) - TTBar->GetBinContent(i);
    TTBar_uncplus[i-1] =  -TTBarQ2down->GetBinContent(i) + TTBar->GetBinContent(i);
    
    TTBar_Q2tot += (TMath::Abs(TTBar_uncminus[i-1]) + TMath::Abs(TTBar_uncplus[i-1]))/2.; 

    TTBar_matchminus[i-1] = TTBar_MatchingUp->GetBinContent(i) - TTBar->GetBinContent(i);
    TTBar_matchplus[i-1] =  -TTBar_MatchingDown->GetBinContent(i) + TTBar->GetBinContent(i);

    TTBar_jesminus[i-1] = TTBarJESup->GetBinContent(i) - TTBar->GetBinContent(i);
    TTBar_jesplus[i-1] = -TTBarJESdown->GetBinContent(i) + TTBar->GetBinContent(i);

    TTBar_btagminus[i-1] = TTBarBTagup->GetBinContent(i) - TTBar->GetBinContent(i);
    TTBar_btagplus[i-1] = -TTBarBTagdown->GetBinContent(i) + TTBar->GetBinContent(i);
    
    //    cout << " Q2 ONLY  TTBar_uncminus[i-1]: " << TTBar_uncminus[i-1] << "  TTBar_uncplus[i-1]: " <<  TTBar_uncplus[i-1] << endl;
    //    cout << " JES ONLY TTBar_jesminus[i-1]: " << TTBar_jesminus[i-1] << "  TTBar_jesplus[i-1]: " <<  TTBar_jesplus[i-1] << endl;
    //    cout << " BTAG ONLY TTBar_btagminus[i-1]: "<< TTBar_btagminus[i-1]<< "  TTBar_btagplus[i-1]: " <<  TTBar_btagplus[i-1] << endl;
    
    
    Matching_uncplus[i-1] = TTBar_matchplus[i-1];
    Matching_uncminus[i-1] = TTBar_matchminus[i-1];

    Q2_uncplus[i-1] = WJets_uncplus[i-1] + TTBar_uncplus[i-1];
    Q2_uncminus[i-1] = WJets_uncminus[i-1] + TTBar_uncminus[i-1];
    
    JES_uncplus[i-1] = WJets_jesplus[i-1] + TTBar_jesplus[i-1];
    JES_uncminus[i-1] = WJets_jesminus[i-1] + TTBar_jesminus[i-1];

    BTag_uncplus[i-1] = WJets_btagplus[i-1] + TTBar_btagplus[i-1];
    BTag_uncminus[i-1] = WJets_btagminus[i-1] + TTBar_btagminus[i-1];
    
    Matching_tot += (TMath::Abs(Matching_uncminus[i-1]) + TMath::Abs(Matching_uncplus[i-1]))/2.;
    Q2_tot += (TMath::Abs(Q2_uncminus[i-1]) + TMath::Abs(Q2_uncplus[i-1]))/2.;
    JES_tot += (TMath::Abs(JES_uncminus[i-1]) + TMath::Abs(JES_uncplus[i-1]))/2.;
    BTag_tot += (TMath::Abs(BTag_uncminus[i-1]) + TMath::Abs(BTag_uncplus[i-1]))/2.;
    

    
    //      tot-totsys(ttbarq2d,wjetsq2) = ttbar + wjets - ttbarq2d - wjetsq2d = (ttbar-ttbarq2d) + (wjets-wjetsq2d) = unc_ttbar + unc_wjets;
    
    
    Unc_plus[i-1] = TMath::Sqrt(Q2_uncplus[i-1]*Q2_uncplus[i-1] + JES_uncplus[i-1]*JES_uncplus[i-1] + BTag_uncplus[i-1]*BTag_uncplus[i-1] 
				+ Matching_uncplus[i-1]*Matching_uncplus[i-1]); 
    Unc_minus[i-1] = TMath::Sqrt(Q2_uncminus[i-1]*Q2_uncminus[i-1] + JES_uncminus[i-1]*JES_uncminus[i-1] + BTag_uncminus[i-1]*BTag_uncminus[i-1]
				 + Matching_uncminus[i-1]*Matching_uncminus[i-1]); 
    
    
    Unc_tot += (Unc_plus[i-1]+Unc_minus[i-1])/2.;
    
    //    cout << "nBins: " << nBins << "  binx[i-1]: " << binx[i-1] << "  MCtot_vec[i-1]: "  << MCtot_vec[i-1] << "  binx_minus[i-1]: " 
    //	 << binx_minus[i-1] << "  binx_plus[i-1]: " << binx_plus[i-1]  << endl;
    //    cout << "  Unc_minus[i-1]: " << Unc_minus[i-1] << "  Unc_plus[i-1]: " <<  Unc_plus[i-1] << endl; 
    //    cout << "  Q2 TTBar_uncminus[i-1]: " << TTBar_uncminus[i-1] << "  TTBar_uncplus[i-1]: " <<  TTBar_uncplus[i-1] << endl;
    //    cout << "  Q2 WJets_uncminus[i-1]: " << WJets_uncminus[i-1] << "  WJets_uncplus[i-1]: " <<  WJets_uncplus[i-1] << endl; 
    //    cout << "  Q2_uncplus[i-1]: " << Q2_uncplus[i-1] << " Q2_uncminus[i-1]: " <<  Q2_uncminus[i-1] << endl; 
    cout << "  Matching_uncplus[i-1]: " << Matching_uncplus[i-1] << " Matching_uncminus[i-1]: " <<  Matching_uncminus[i-1] << endl; 
    

  }

  cout << "WJets_Q2tot: " << WJets_Q2tot << endl;
  cout << "TTBar_Q2tot: " << TTBar_Q2tot << endl;

  cout << "Matching_tot: " << Matching_tot << endl;
  cout << "Q2_tot: " << Q2_tot << endl;
  cout << "JES_tot: " << JES_tot << endl;
  cout << "BTag_tot: " << BTag_tot << endl;
  cout << "Unc_tot: " << Unc_tot << endl;

  TGraphAsymmErrors* gae = new TGraphAsymmErrors(nBins, binx, MCtot_vec, binx_minus, binx_plus, Unc_minus, Unc_plus);

  gae->SetFillStyle(3003);
  gae->SetTitle("");
  gae->GetXaxis()->SetTitle("m_{T}(GeV/c^{2})");


  
  //   QCDMu->Scale(2.); 
  
  double ttott= 0.;
  THStack hs1("hs1","hs1");
  Data->SetLineColor(kBlack);
  //QCD
  QCDMu->SetFillColor(kGray);
  QCDMu->SetLineColor(kBlack);
  hs1.Add(QCDMu) ;
  ttott += QCDMu->Integral();
  cout<< " qcd " << QCDMu->Integral() << " tot + qcd " << ttott <<endl;
  //wjets
  WJets->SetFillColor(kGreen-2);
  WJets->SetLineColor(kBlack);
  //  WJets->Smooth(2);
  hs1.Add(WJets);
  ttott += WJets->Integral();
  cout<< " wjets " << WJets->Integral() << " tot + wjets " << ttott <<endl;
  //zjets
  ZJets->SetFillColor(kBlue-1);
  ZJets->SetLineColor(kBlack);
  //  ZJets->Smooth(4);
  hs1.Add(ZJets);
  ttott += ZJets->Integral();
  cout<< " zjets " << ZJets->Integral() << " tot + zjets " << ttott <<endl;
  //diboson
  /*  WW->Add(WZ);
  WW->Add(ZZ);
  */
  WW->SetFillColor(kAzure);
  WW->SetLineColor(kBlack);
  ttott += WW->Integral();
  cout<< " vv " << WW->Integral() << " tot + vv " << ttott <<endl;
  hs1.Add(WW);
  
  //ttbar
  TTBar->SetFillColor(kOrange-3);
  TTBar->SetLineColor(kBlack);
  hs1.Add(TTBar);
  ttott += TTBar->Integral();
  cout<< " ttbar " << TTBar->Integral() << " tot + ttbar " << ttott <<endl;
  //tW-channel
  TWChannel->Add(TbarWChannel);
  TWChannel->SetFillColor(kOrange);
  TWChannel->SetLineColor(kBlack);
  hs1.Add(TWChannel);
  ttott += TWChannel->Integral();
  cout<< " tw-ch " << TWChannel->Integral() << " tot + twchannel " << ttott <<endl;
  //t-channel
  //  TbarChannel->Scale(1+(TChannel->Integral()/TbarChannel->Integral()));   TChannel->Add(TChannel,-1);
  TChannel->Add(TbarChannel);
  TChannel->SetFillColor(kRed);
  TChannel->SetLineColor(kBlack);
  hs1.Add(TChannel);
  ttott += TChannel->Integral();
  cout<< " t-ch " << TChannel->Integral() << " tot + tchannel " << ttott <<endl;
  //s-channel
  SChannel->Add(SbarChannel);
  SChannel->SetFillColor(kYellow);
  SChannel->SetLineColor(kBlack);
  hs1.Add(SChannel);
  ttott += SChannel->Integral();
  cout<< " s-ch " << SChannel->Integral() << " tot + schannel " << ttott <<endl;
  cout << " data tot "<< Data->Integral()<< " mc tot "<< ttott<< endl;

 
 
  TCanvas C3("c3","c3"); 
  C3.cd()->SetRightMargin(0.04);
	
  if(dolog){
    C3.SetLogy();
  }	
  C3.SetLeftMargin(1);
  C3.SetRightMargin(0.2);
      
  gae->Draw("a20");
  Data->Draw("E1");
  hs1.Draw("hist same");
  hs1.Draw("axissame");
  Data->SetMarkerStyle(20);
  Data->Draw("E1 same");
      
  hs1.SetTitle(observableName);
  Data->SetTitle(observableName);
  hs1.SetTitle("");
  Data->SetTitle("");
  hs1.GetXaxis()->SetTitle(observableName);
  Data->GetXaxis()->SetTitle(observableName);
  Data->GetYaxis()->SetTitleOffset(1.2);
  Data->GetXaxis()->SetTitleFont(42);
  Data->GetXaxis()->SetTitleSize(0.05);

  /*C3.SetLeftMargin(1);
  C3.SetRightMargin(0.2);
	    
  Data->Draw("E1");
  hs1.Draw("hist same");
  hs1.Draw("axissame");
  Data->SetMarkerStyle(20);
  Data->Draw("E1 same");
	    
  hs1.SetTitle(observableName);
  Data->SetTitle(observableName);
  hs1.SetTitle("");
  Data->SetTitle("");
  hs1.GetXaxis()->SetTitle(observableName);
  Data->GetXaxis()->SetTitle(observableName);
  Data->GetYaxis()->SetTitleFont(42);
  Data->GetYaxis()->SetTitleOffset(1.);
  Data->GetXaxis()->SetTitleFont(42);
  */
  cout << "test <<<" <<endl;
  
  if(dolog)Data-> GetYaxis() -> SetRangeUser(0.8*Data->GetMinimum(),1.4* (Data->GetMaximum())); 
#include<algorithm>
  Data-> GetYaxis() -> SetRangeUser(0.,1.2*max(Data->GetMaximum(),hs1.GetMaximum())); 

  gae -> GetYaxis() -> SetTitleOffset(1.4);
  gae -> GetYaxis() -> SetTitleSize(0.03);


  Data->Draw("E1 same");
  Data->Draw("axissame");
  gae->Draw("20")    ;
	    
  cout << "test <<<<" <<endl;


	    
  /*  TLegend * leg = new TLegend(0.81,0.27,0.93,0.90);
  leg = new TLegend(0.81,0.27,0.93,0.90);
  leg->SetTextSize(0.037);
  leg->SetBorderSize(0);
  leg->SetLineStyle(0);
  leg->SetTextSize(0.027);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  */

  TLegend * leg = new TLegend(0.81,0.27,0.93,0.90);
  leg->SetFillColor(0);    
  leg = new TLegend(0.81,0.2,0.94,0.88);
  leg->SetTextSize(0.037);
  leg->SetBorderSize(0);
  leg->SetLineStyle(0);
  //  leg->SetTextSize(0.027);
  leg->SetTextSize(0.05);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);

  leg->AddEntry(Data,"data","pl");	
  leg->AddEntry(SChannel,"s-channel","f");
  leg->AddEntry(TChannel,"t-channel","f");
  leg->AddEntry(TWChannel,"tW-channel","f");
  leg->AddEntry(TTBar,"t#bar{t}","f");
  leg->AddEntry(ZJets,"Z+jets","f");
  leg->AddEntry(WJets,"W+jets","f");
  leg->AddEntry(WW,"Diboson ","f");
  leg->AddEntry(QCDMu,"QCD ","f");
  leg->AddEntry(gae,"Syst. unc.","f");

  leg->Draw();


  //  TLatex * tex = new TLatex(0.175, 0.97,"CMS Preliminary, 19.8 fb^{-1}, Muons, #sqrt{s} = 8 TeV");
  TLatex * tex = new TLatex(0.175, 0.97,"CMS Preliminary, 5.1 fb^{-1}, Muons, #sqrt{s} = 7 TeV");

  tex->SetNDC();
  tex->SetTextAlign(13);
  tex->SetTextFont(42);
  tex->SetLineWidth(3.5);
  tex->Draw();	
  TString histoname = oTitle+TString("_")+channel+sample+TString("")+lepton;  
  TH1D * ALLMC =  new TH1D( histoname, histoname,nBins,observableMin,observableMax);  
  ALLMC->Add(TChannel);
  ALLMC->Add(TTBar);
  ALLMC->Add(WJets);
  ALLMC->Add(SChannel);
  ALLMC->Add(TWChannel);
  ALLMC->Add(WJets);
  ALLMC->Add(ZJets);
  ALLMC->Add(WW);
  ALLMC->Add(QCDMu);
  cout<< "ks test for " << oTitle << "  " << ALLMC->KolmogorovTest(Data)<<" chi2 "<< ALLMC->Chi2Test(Data) <<endl;
  
  cout << "test <<<<<" <<endl;
  
  //  C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize_Errbands_norm.root");   
  C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize_Errbands_norm.png");  
  C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize_Errbands_norm.pdf");
   
}
