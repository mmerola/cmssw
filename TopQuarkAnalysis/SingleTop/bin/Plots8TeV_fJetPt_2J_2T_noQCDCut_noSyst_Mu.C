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
  TString lepton = "Mu";

  TString sample ="2J_2T";
  TString sampleqcd = sample + "_QCD_noSyst"; 
  //  TString sampleqcd = "2J_0T_QCD_noSyst"; 
  sample = sample+ "_noSyst";

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
  

TString observable = "fJetPt";   double observableMin = 40;   double observableMax = 200;  TString observableName = " p_{T,f}"; double nBins = 15; TString oTitle = "fJetPt";

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

  TString KinCut = TString("*(leptonRelIso<10.06)");
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-fJetPhi)**2+(leptonEta-fJetEta)**2)>0.3 && sqrt((leptonPhi-bJetPhi)**2+(leptonEta-bJetEta)**2)>0.3  )";
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)>-0.3 && sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)<50 && sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)>-0.3 && sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)<50 )";

  TString KinCutQCDDD = TString("(sqrt((leptonPhi-fJetPhi)**2+(leptonEta-fJetEta)**2)>0.3 && sqrt((leptonPhi-bJetPhi)**2+(leptonEta-bJetEta)**2)>0.3)");
  //  TString KinCutQCDDD="*(sqrt((leptonPhi-bJetFinPhi)**2+(leptonEta-bJetFinEta)**2)>0.3 && sqrt((leptonPhi-bJetDecPhi)**2+(leptonEta-bJetDecEta)**2)>0.3 )";
  
  //  TString cut = "weight*(890*leptonSF + (4428)*leptonSFB +(495.003+5109+1288)*leptonSFC)*bWeight*PUWeight";
  //  TString cut = "weight*leptonEff*bWeight*PUWeight*12100"; //12210.003;
  //  TString cut = "weight*(4428)*bWeight";

  TString cut = "(PUWeight*bWeight*weight*(3901.813*turnOnWeight+1197.261))"; //5099.074
  //  TString cut = "weight*(leptonSF*889.302 + leptonSFB*4423.061 + leptonSFC*7146.634 + leptonSFD*7319)*bWeight*PUWeight"; //19777.997;
  
  
  TString cutW = "*(1.0)";
  TString MCCut = "";
  TString cutData="1."; 
  
  cutW = cut + cutW + KinCut + MCCut;
  cut = cut + KinCut + MCCut;
  cutData = cutData + KinCut; 
  TString  cutDataQCD = KinCutQCDDD;
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
 QCDIntegral = 25.; WJetsScale = 1.; TTBarScale =1.;  
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


  if(scaleToData){
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
  
  double DataMC_ratio = (Data->Integral()/(MCtot));
   
  QCDMu->Scale(DataMC_ratio); 
  WJets->Scale(DataMC_ratio); 
  ZJets->Scale(DataMC_ratio); 
  WW->Scale(DataMC_ratio); 
  /*  WZ->Scale(DataMC_ratio); 
  ZZ->Scale(DataMC_ratio); 
  */
  TTBar->Scale(DataMC_ratio); 
  TChannel->Scale(DataMC_ratio);
  TbarChannel->Scale(DataMC_ratio); 
  SChannel->Scale(DataMC_ratio); 
  SbarChannel->Scale(DataMC_ratio); 
  TWChannel->Scale(DataMC_ratio); 
  TbarWChannel->Scale(DataMC_ratio); 
  }
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
  Data-> GetYaxis() -> SetRangeUser(0.,1.1*max(Data->GetMaximum(),hs1.GetMaximum())); 
  //	    Data-> GetYaxis() -> SetRangeUser(0,190);
	    
  Data->Draw("E1 same");
  Data->Draw("axissame");
	    
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

  leg->Draw();


  //  TLatex * tex = new TLatex(0.175, 0.97,"CMS Preliminary, 19.8 fb^{-1}, Muons, #sqrt{s} = 8 TeV");
  TLatex * tex = new TLatex(0.175, 0.97,"CMS Preliminary, 5.0 fb^{-1}, Muons, #sqrt{s} = 7 TeV");

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
  
   C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize.root");   
   C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize.png");  
   C3.SaveAs(sample+"_noQCDCut"+"_"+oTitle+"_MuStack_resize.pdf");
     
}
