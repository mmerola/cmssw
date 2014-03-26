#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/ESHandle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "RecoBTag/Records/interface/BTagPerformanceRecord.h"
#include "CondFormats/PhysicsToolsObjects/interface/BinningPointByMap.h"
#include "RecoBTag/PerformanceDB/interface/BtagPerformance.h"
#include "DataFormats/FWLite/interface/Record.h"
#include "DataFormats/FWLite/interface/EventSetup.h"
#include "Cintex/Cintex.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "PhysicsTools/CondLiteIO/interface/RecordWriter.h"
#include <iostream>
#include <algorithm>
#include <string.h>
#include <sstream> 
#include <stdio.h>
#include <fstream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TFile.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "RooDataHist.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooProdPdf.h"
#include "RooGenericPdf.h"
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooClassFactory.h>
#include <RooHistPdf.h>
#include <RooAddPdf.h>
#include <RooConstVar.h>
#include <RooRealVar.h>
#include <RooChi2Var.h>
#include <RooMinuit.h>
#include <RooFitResult.h>
#include <RooGlobalFunc.h>
#include <RooPlot.h>
#include <RooCBShape.h>
#include <RooNLLVar.h>
#include <RooFormulaVar.h>
#include "TMath.h"
#include <algorithm>
#include "TRandom3.h"
#include <Math/VectorUtil.h>
#include "DataFormats/Math/interface/deltaR.h"
#include "RooExtendPdf.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/HybridResult.h"
#include "RooStats/HybridPlot.h"
#include "RooStats/HypoTestResult.h"
#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HypoTestInverterPlot.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooProduct.h"
#include "RooAddition.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooIntegralMorph.h"
#include "RooNumIntConfig.h" 
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
//#include "TopQuarkAnalysis/SingleTop/src/RooHistoMorph.h"
//#include "TopQuarkAnalysis/SingleTop/src/RooHistoMorph.cc"
//#include "TopQuarkAnalysis/SingleTop/src/RooHistoMorphLinkDef.h"
//#include "TopQuarkAnalysis/SingleTop/src/RooHistoMorphLinkDef.cc"

//#include "../../../../tmp/slc5_amd64_gcc434/src/TopQuarkAnalysis/SingleTop/src/TopQuarkAnalysisSingleTop/RooHistoMorphLinkDef.cc"
//#include "RooHistoMorph.h"

using namespace RooStats;
using namespace RooFit;
using namespace std;

int main(int argc,  char* argv[]){
  cout << " start " << endl;

  AutoLibraryLoader::enable();

  gStyle->SetFrameBorderMode(0);
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


  // Postscript options:                                                                                                                                       
  gStyle->SetPaperSize(20.,20.);



  TH1::AddDirectory(kFALSE);
  //  PSF_histo->SetDirectory(0);
  
  AutoLibraryLoader::enable();

  
  double setWeight(string channel, string syst, string lepton, string sample, double controlSampleLFactor ,double weight );
  double leptonWeight(string lepton, double eta , string channel, string syst );
  double lumiFormula(string lepton , double lumiA,double effA,double lumiB,double effB,double lumiC,double effC, double lumiD, double effD, string syst, double leptonPtV=30, double leptonEtaV=0.);


  stringstream folder_,leptonCase_,postfix_,LumiC_,LumiD_,useMET_,LumiB_,LumiA_,SystCase_,MinPDF_,MaxPDF_;
  folder_                  << argv[1];
  leptonCase_                << argv[2];
  postfix_                 << argv[3];
  LumiA_                  << argv[4];
  LumiB_                 << argv[5];
  LumiC_                  << argv[6];
  LumiD_                  << argv[7];
  useMET_                  << argv[8];
  SystCase_                << argv[9];
  MinPDF_                << argv[10];
  MaxPDF_                << argv[11];

  //Usage: fitsPlots1D . . "" 1154.453 1328.69 215.421 1 
  string postfix_file;
  postfix_ >> postfix_file; 

  string folder; // = "/tmp/oiorio";
  folder_ >> folder;

  string leptonCase; // = "/tmp/oiorio";
  leptonCase_ >> leptonCase;

  double LumiA;
  LumiA_>>LumiA;

  double LumiB;
  LumiB_>>LumiB;

  double LumiC;
  LumiC_ >> LumiC;

  double LumiD;
  LumiD_ >> LumiD;

  bool useMET = false;
  useMET_>>useMET;

  string systCase = "";
  SystCase_>>systCase;
  
  int MinPDF=0;
  MinPDF_ >> MinPDF;

  int MaxPDF=52;
  MaxPDF_ >> MaxPDF;

  bool useLL = false;
  //  useLL = true;
  cout <<" test spal"<< endl;
  double lumiA = LumiA;
  double lumiB = LumiB;
  double lumiC = LumiC;
  double lumiD = LumiD;

  int nbinsVarA =20,minVarA=0,maxVarA=5,nbinsVarB = 20 ,minVarB=100,maxVarB=300; 
  int nbinsMTWMass = 25; 

  //channels
  vector<string> channels;
  //systematics
  vector<string> systematics,systematicsDataDriven;
  //observables
  vector<string> observables;
  

 
  //channels involved in the likelihood
  vector<string> channels_fit,allchannels,channelsDataDriven,channelsplusqcd;
  //systematics, symmetrized 
  vector<string> systematics_total;


  //map channel-systematics-tree
  map<string, map< string, map < string, TTree *> > > trees;
  map<string, map< string, map < string, TTree *> > > treesWSample;
  map<string, map< string, map < string, TTree *> > > treesSampleB;
  map<string, map< string, map < string, TTree *> > > trees3J2T;

  map<string, map< string, map < string, TTree *> > > treesESB;
  map<string, map< string, map < string, TTree *> > > treesQCD;
  map<string, map< string, map < string, TTree *> > > treesWSampleQCD;
  map<string, map< string, map < string, TTree *> > > treesSampleBQCD;
  map<string, map< string, map < string, TTree *> > > treesESBQCD;
   //  map<string, map<string, map< string, TH1D *> > > HistosEta;
  //  map<string, map<string, map< string, TH1D *> > > HistosCos;
  //  map<string, map<string, map< string, TH1D *> > > HistosTopMass;
  map<string, map<string, map< string, TH2D *> > > Histos;
  map<string, map<string, map< string, TH2D *> > > HistosWSample;

  map<string, map<string, map< string, TH1D *> > > HistosMTW;
  map<string, map<string, map< string, TH1D *> > > HistosMTWWSample;



  map<string, map< string, map < string, TH3D * > > > PartialMorphedHistograms;//Histograms after morphing
  map<string, map< string, map < string, TH3D * > > > PartialMorphedHistogramsWSample;//Histograms after morphing w sample


  //map<string, map<string, map< string,TH2D *> > > Histos;
  
  /////////////////////////////////////////////////////////

  //Parameters & PDFs

  map< string , map < string, map< string, map<string, TH1D *> > > > HistoCollection;
  map< string , map < string, map< string, map<string, TH2D *> > > > Histo2DCollection;
  map< string , double > maxobs,minobs;
  map< string , int > nbins, nbinseleeta;

  map<string, map< string, map < string, RooHistPdf * > > > MTWHistoPDFs;//PDFs for lepton, mtw fit 

  map<string, map< string, map < string, RooHistPdf * > > > LeptonHistos;//PDFs for lepton and charge
  map<string, map< string, map < string, RooHistPdf * > > > LeptonHistosWSample;//PDFs for lepton and charge w sample

  map<string, RooRealVar * > SystParameters; //Systematics paramters: include both rate and shape

  map<string, map< string, RooFormulaVar *> > Yields; //Yields mu+e
  map<string, map< string, map< string, RooRealVar *> > > Rates; //MC Rates
  map<string, map< string, map< string, RooRealVar *> > > RatesMTW; //MC Rates
  map<string, map< string, map<string, RooFormulaVar *> > > Fraction;//mu/e +/- channel fraction
  map<string, map< string, map < string,RooFormulaVar *> > > PartialYields; //Yields divided in mu/e /+-
  map< string, map< string , RooFormulaVar *> > FractionLep;
  
  map<string, map <string , RooAddPdf *> > BackgroundContributions; //Background components for each systematics and for a given lepton/charge combination
  map<string, map <string , RooAddition *> > BackgroundRates; //Background components for each systematics and for a given lepton/charge combination
  map< string , map<string, RooFormulaVar * > >BackgroundYields; //Background components for each systematics 

  
  map<string, RooAddPdf * > Signal; //Signal for each systematics and for a given lepton/charge combination 
  map<string, RooAddition *> SignalRates; //Signal rate for each systematics and for a given lepton/charge Combination () 
  map<string, RooFormulaVar *>  SignalYields; //Signal yield for each systematics 
  
  map<string, map < string, RooAddPdf* > > SystematicsHistos;//PDFs which varies considering all systematics
  map<string, map < string, RooProduct* > > SystematicsYields;//Yield which varies considering all systematics
  map<string, map < string, RooFormulaVar* > > SystematicsFitYields;//Yield which varies considering all systematics

  
  RooRealVar * SignalStrengths; //Signal yield wrt sm yield for each for each systematics
  map<string, RooRealVar *  > BackgroundStrengths; //Background yields wrt sm yield for each systematics 
  
  //////////////////////////////////////////Functions
  
  map<string, RooAddPdf* > SystLikelihood;//Likelihood for all systematics and lepton/charge combination
  RooSimultaneous * CombinedLikelihood;//Function for Final Fit <------------------------
  

  map<string, map <string , RooRealVar *> > FitRates; //number of events for the fit
  map<string , map<string, RooFormulaVar *> > ChannelFraction;
  map< string ,map <string, RooFormulaVar* > >ChargeRatio;

  map<string , map<string, RooRealVar *> > ChannelFractionFit;
  map< string ,map <string, RooRealVar* > >ChargeRatioFit;
  
  
  map< string , map <string, RooRealVar*> > BG;

  

  //////////////////////////////////////////Not used but May be useful
  
  /*
    map<string, map<string, RooFormulaVar *> > SignalPartialYields; //Signal yield for each systematics and for a given lepton/charge combination 
    
    
    map<string, map< string, map<string, RooFormulaVar * > > > BackgroundPartialYields; //Background components yields for each systematics and lepton/charge combination 
    
    
    map< string ,RooSimultaneous *> CombinedLikelihoodSyst;//Combined LL for given syst(does not enter final fit)
  */
  
  //////////////////////////////////////////End RooFit Setup

  void HistoAdd(TH1D*,TH1D*,double,double,double);

  TH1D * LinearExtrapolation(TH1D * h1, TH1D* h2, double value);

  double qcdintegralmap (string , double integral = 1.  ) ;

  TH1D * remodel(TH1D * res, TH1D * h_A,TH1D* h_B, bool verbose = false, string postfix = "_remodel" );
  TH1D * remodelLimits(TH1D * res, TH1D * h_A,TH1D* h_B, bool verbose = false, string postfix = "_remodel", double m = -9999., double M =9999.);

  TH1D* getRemodelFunction(TH1D* preTag, TH1D* postTag, bool verbose =false, string postfix = "_remodeled");


  TH1D * makeproduct(TH1D * h_A,TH1D* h_B, int rebinA = 1, int rebinB=1,double integral = -1.);

  TH1D * makeproduct(TH2D * h);

  double renormalize(string observable,string channel,string sample,string syst,string lepton,string charge);

  double NormalizedIntegral(RooAbsPdf *, RooRealVar& , double, double);

  TH2D * make2D( TH1D*,TH1D*, double, string postfix = "");   
  
  TH2D * interpolate(TH1D*,TH1D*,unsigned int, double, double, bool);
  TH3D * interpolate(TH2D*,TH2D*,unsigned int, double, double, bool);
  //  TH2D * interpolatingFunction(TH1D *, TH1D *, unsigned int , double , double );
  TH2D * getUpDownHistogram(TH2D*,TH2D*);
  TH3D * getUpDownHistogram(TH3D*,TH3D*);
  //  map<string, map< string, RooRealVar * > > TotalYields; //Yields mu+e
  
  map<string, map< string, RooAddPdf *> > SystPDFs;
  
  //set the precision for the integral of the model here: 10^-6 should be fine, default is 10^-8.
  RooNumIntConfig* cfg = RooAbsReal::defaultIntegratorConfig();
  cfg->setEpsAbs(1E-6);
  cfg->setEpsRel(1E-6);
  cfg->method1D().setLabel("RooIntegrator1D") ;
  //cfg->method1D().setLabel("RooSegmentedIntegrator1D") ;
  //cfg->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D") ;
  
  //  method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D") ;
  //cfg->method1D().setLabel("RooGaussKronrodIntegrator1D") ;
  //cfg->method1D().setLabel("RooMCIntegrator") ;

  bool topMassvseta = false;
  bool useproduct = true;
  double fraction = -0.5; 
  double SampleBThr = -111.93;
  int seed =1;
  TRandom3 rand(seed);

  double factorTbar = 1.23;
  factorTbar = 1.;
  
  double factorT = 1.;

  double limit = 2.4; 
  double limit2 = 2.4; 
  //  limit = limit2; 

  bool useFull= true;
  //  useFull = false;

  bool useSyst = true;
  if(!(systCase=="standardSysts"))  useSyst = false;

  bool useSystRate = true;
  if(!(systCase=="rateSysts"))  useSystRate = false;

  bool useSystModel = true;
  if(!(systCase=="modelSysts"))  useSystModel = false;
   
  bool useSystPDF = true;
  if(!(systCase=="pdfSysts"))  useSystPDF = false;
   
  bool useDifferentModel =  true;
  if(!(systCase=="differentModelSysts"))  useDifferentModel = false;
   
  if(!useFull)useSyst = false;

  bool doTopRemodel = true; 
  doTopRemodel= false; 

  bool doMCStatUnc = true;
  //  doMCStatUnc = false;
  
  bool reweightTurnOn = true;
  reweightTurnOn = false;

  TH1D SFs_comp_pow_mu("sfsmu","sfsmu",20,0,5);
  TH1D SFs_comp_pow_ele("sfsele","sfsele",10,0,5);

  bool addSignalModel = true;
  addSignalModel = false;





  if(addSignalModel){
    TFile f_comp_pow( (folder+"/ch-over-pw-SF.root").c_str());
    SFs_comp_pow_mu.Add( ((TH1D*)(f_comp_pow.Get("mu")))) ;
    SFs_comp_pow_ele.Add( ((TH1D*)(f_comp_pow.Get("ele")))) ;
    
    for(int b =1; b <=20;++b ){
      ////      cout<< "mu sf "<< b<< " val "  << SFs_comp_pow_mu.GetBinContent(b);
      ;
    }
    for(int b =1; b <=10;++b ){
      ////      cout<< "ele sf "<< b<< " val " << SFs_comp_pow_ele.GetBinContent(b);
      ;
    }
  }
  //  reweightTurnOn = false;


  int npdfstorun = 52;
  float pdf_weights[52];
  float pdf_weights_full[52];
  string pdf_names[52];

  for(int p=1; p <=npdfstorun; ++p){
    stringstream w_n;
    w_n<<p;
    pdf_names [p-1] = "PDFWeight"+w_n.str();
  }


  //IMPORTANT KEEP THIS ORDER
  //channels
  channels_fit.push_back("EWK");
  channels_fit.push_back("EWKMC");
  channels_fit.push_back("EWKMCTop");
  channels_fit.push_back("EWKTop");
  channels_fit.push_back("Data_Fit");
  channels_fit.push_back("Top");
  channels_fit.push_back("TopDD");
  channels_fit.push_back("QCD");
  channels_fit.push_back("Signal");
  
  //
  systematics.push_back("noSyst");
    //  systematics.push_back("TWChannel_Q2");  

  //  systematics.push_back("WModel");


  

  bool addsignaltop = true;
  //addsignaltop = false;




  if(useSyst){
    
    systematics.push_back("JES");  systematics.push_back("JER");
    
    systematics.push_back("BTag");      systematics.push_back("MisTag");
    
    systematics.push_back("PU");  
    
    systematics.push_back("UnclusteredMET");
    
  }
  
  if(useSystPDF){
    for(int p=1; p <=npdfstorun; ++p){
      if (!(p >= MinPDF && p <=MaxPDF))continue;  
      systematics.push_back(pdf_names[p-1]);
      cout << " test syst " << pdf_names[p-1] << endl;
    }

  }
  if(useDifferentModel){
    systematics.push_back("NNPDF21");
    systematics.push_back("MSTW08");
  }
  if(useSystModel){
    systematics.push_back("TChannel_Q2");
    systematics.push_back("TTBar_Q2");
    systematics.push_back("Comp");
  }
  
  if(useSystRate){
    systematics.push_back("TTBar");
    
    
    systematics.push_back("MuonTrig");
    systematics.push_back("EleEff");
    systematics.push_back("EleMisId");
    
   
    
    //    systematics.push_back("QCD");
    //systematics.push_back("TWChannel");
    //systematics.push_back("SChannel");
    //systematics.push_back("VV");
    
    
    
    
  }
  
  systematicsDataDriven.push_back("noSyst");
  
  if(useSyst){ 
    systematicsDataDriven.push_back("QCD");
    //    systematicsDataDriven.push_back("RecoEle");
    //    systematicsDataDriven.push_back("TriggerEle");
    //    systematicsDataDriven.push_back("TriggerMu");
  }
  
  systematics_total.push_back("noSyst");
  //  systematics_total.push_back("WModel");
  
  
  if(addSignalModel) systematics_total.push_back("SignalModel");
  
  
  
  
  if(useSyst){ 
    
    systematics_total.push_back("JES");    systematics_total.push_back("JER");
    
    systematics_total.push_back("BTag");      systematics_total.push_back("MisTag");
    
    systematics_total.push_back("PU");
    
    systematics_total.push_back("UnclusteredMET");
  }

  if(useDifferentModel){
    systematics_total.push_back("NNPDF21");
    systematics_total.push_back("MSTW08");
  }

  if(useSystPDF){
    for(int p=1; p <=npdfstorun; ++p){
      if (!(p >= MinPDF && p <=MaxPDF))continue;  
      systematics_total.push_back(pdf_names[p-1]);
      cout << " test syst total" << pdf_names[p-1] << endl;
    }

  }

  if(useSystModel){
    systematics_total.push_back("TChannel_Q2"); 
    systematics_total.push_back("TTBar_Q2"); 
    systematics_total.push_back("Comp"); 
  }

  if(useSystRate){ 
    
    //    systematics_total.push_back("TTBar");
    
    //    systematics_total.push_back("MuonTrig"); //  systematics_total.push_back("EleEff");  
    //  systematics_total.push_back("EleEff"); //  systematics_total.push_back("EleEff");  
    systematics_total.push_back("EleMisId"); //  systematics_total.push_back("EleEff");  
    
    //    systematics_total.push_back("QCD");
    //systematics_total.push_back("TWChannel");
    //systematics_total.push_back("SChannel");
    //systematics_total.push_back("VV");
    
  }
  
  
  if(useSystModel){
    channels.push_back("TTBar_Q2Down");
    channels.push_back("TTBar_Q2Up");

    channels.push_back("TChannel_Q2Down");
    channels.push_back("TChannel_Q2Up");
    
    channels.push_back("TbarChannel_Q2Down");
    channels.push_back("TbarChannel_Q2Up");

    channels.push_back("TToBTauNu");

    if(leptonCase== "Mu")   channels.push_back("TToBMuNu");
    if(leptonCase== "Ele")   channels.push_back("TToBENu");

  }    
    
    channels.push_back("WJets");
    if(useFull) 
{    channels.push_back("ZJets");

    channels.push_back("TWChannel");
    channels.push_back("TbarWChannel");
    channels.push_back("SChannel");
    channels.push_back("SbarChannel");
    /*    channels.push_back("WW");
    channels.push_back("WZ");
    channels.push_back("ZZ");
    */   
 }
    //    channels.push_back("QCDMu");
    // channels.push_back("QCDEle");

  //  channels.push_back("TTBar_Q2Down");
  //channels.push_back("TTBar_Q2Up");

  //  channels.push_back("TTBar_MatchingDown");
  //channels.push_back("TTBar_MatchingUp");

  //  channels.push_back("TChannel_Q2Down");
  //channels.push_back("TChannel_Q2Up");
  
  //  channels.push_back("TbarChannel_Q2Down");
  //channels.push_back("TbarChannel_Q2Up");


  channels.push_back("Data");
  //  channels.push_back("DataEleQCD");
  //  channels.push_back("DataMuQCD");
  

  //if(addsignaltop) 
  channels.push_back("TChannel");
  channels.push_back("TbarChannel");
  channels.push_back("TTBar");

  
  
  channelsDataDriven.push_back("QCD");

  channelsplusqcd = channels; 


  //  channelsplusqcd.push_back("QCD_Pt_20to30_BCtoE");
  //channelsplusqcd.push_back("QCD_Pt_30to80_BCtoE");
  //channelsplusqcd.push_back("QCD_Pt_80to170_BCtoE");

//  channelsplusqcd.push_back("QCDMu");  channelsplusqcd.push_back("QCDEle");

  allchannels = channelsplusqcd;

  //  allchannels.push_back("WLight");
  allchannels.push_back("WHF");
  //allchannels.push_back("WHF_c");
  //allchannels.push_back("WHF_b");
  allchannels.push_back("QCD");
  
  allchannels.push_back("EWK");
  allchannels.push_back("EWKMC");
  allchannels.push_back("EWKTop");
  allchannels.push_back("EWKMCTop");
  allchannels.push_back("Data_Fit");
  allchannels.push_back("Top");
  allchannels.push_back("TopDD");
  allchannels.push_back("Signal");

  int etabins = 20;
  etabins = 10;

  int usualbins =20;
  int usualbinsmet =25;

  bool usePUSignal = true;
  //  usePUSignal = false;

  bool enlargeSample = true;
  enlargeSample = false;

  observables.push_back("costhetalj");
  minobs["costhetalj"]=-1;
  maxobs["costhetalj"]=1;
  nbins["costhetalj"]=usualbins;;

  observables.push_back("eta");
  minobs["eta"]=0;
  maxobs["eta"]=5;
  nbins["eta"]=etabins;;
  nbinseleeta["eta"]=etabins;

  observables.push_back("PUWeight");
  minobs["PUWeight"]=0;
  maxobs["PUWeight"]=50;
  nbins["PUWeight"]=500;
  nbinseleeta["PUWeight"]=500;


  observables.push_back("etaTUp");
  minobs["etaTUp"]=0;
  maxobs["etaTUp"]=5;
  nbins["etaTUp"]=etabins;;
  nbinseleeta["etaTUp"]=etabins;
 
  observables.push_back("etaTTDown");
  minobs["etaTTDown"]=0;
  maxobs["etaTTDown"]=5;
  nbins["etaTTDown"]=etabins;;
  nbinseleeta["etaTTDown"]=etabins;


  observables.push_back("etaTTUp");
  minobs["etaTTUp"]=0;
  maxobs["etaTTUp"]=5;
  nbins["etaTTUp"]=etabins;;
  nbinseleeta["etaTTUp"]=etabins;

  observables.push_back("etaTDown");
  minobs["etaTDown"]=0;
  maxobs["etaTDown"]=5;
  nbins["etaTDown"]=etabins;;
  nbinseleeta["etaTDown"]=etabins;

  observables.push_back("topMass");
  minobs["topMass"]=100;
  maxobs["topMass"]=300;
  nbins["topMass"]=usualbins;;

  observables.push_back("topMassWS");
  minobs["topMassWS"]=100;
  maxobs["topMassWS"]=300;
  nbins["topMassWS"]=usualbins;;

  observables.push_back("topMassQCD");
  minobs["topMassQCD"]=100;
  maxobs["topMassQCD"]=300;
  nbins["topMassQCD"]=usualbins;;

  observables.push_back("mtwMass");
  minobs["mtwMass"]=0;
  maxobs["mtwMass"]=200;
  nbins["mtwMass"]=usualbinsmet;

  observables.push_back("metPt");
  minobs["metPt"]=0;
  maxobs["metPt"]=200;
  nbins["metPt"]=usualbinsmet;
  
  //  observables.push_back("etaTopMass");
  //minobs["etaTopMass"]=minobs["eta"]*minobs["topMass"];
  //maxobs["etaTopMass"]=maxobs["eta"]*maxobs["topMass"];
  //nbins["etaTopMass"]=nbins["eta"]*nbins["topMass"];

  observables.push_back("etaCosthetalj");
  minobs["etaCosthetalj"]=minobs["eta"]*minobs["costhetalj"];
  maxobs["etaCosthetalj"]=maxobs["eta"]*maxobs["costhetalj"];
  nbins["etaCosthetalj"]=nbins["eta"]*nbins["costhetalj"];
  nbinseleeta["etaCosthetalj"]=nbinseleeta["eta"]*nbins["costhetalj"];

  observables.push_back("etaLow");
  minobs["etaLow"]=0;
  maxobs["etaLow"]=5;
  nbins["etaLow"]=20;
  
  
  observables.push_back("etaHigh");
  minobs["etaHigh"]=0;
  maxobs["etaHigh"]=5;
  nbins["etaHigh"]=20;

  observables.push_back("likelihood");
  minobs["likelihood"]=0;
  maxobs["likelihood"]=1;
  nbins["likelihood"]=20;
  
  
  std::string  leptons[2] = {"Mu","Ele"};
  std::string  charges[2] = {"Plus","Minus"};
  std::string  UpDown[2] = {"Up","Down"};
  
  
  //  int binsvar=20;  double first = 0;  double last = 5;
  int binsvar=20;  double first = 100;  double last = 500;
  //int binsvar=20;  double first = -1;  double last = 1;
 
  //initializing variables
  //Signal sample
  double leptonRelIsoCut =0.175;
  double leptonRelIsoThr =0.50;
  double leptonRelIsoThrEle =0.30;
  double fJetRMSCut = 10.025;
  double fJetPtCut = 0.;

  double eta =-999,costhetalj=-999,costhetalj_bJet=-999,weight=-999,mtwMass=-999,mtwCut=50,topMass= -999,leptonRelIso=-999, etaLow=-999,etaHigh =-999,highBTag=-999, lowBTag =-999,metPt =-999,likelihood=-999,metCut = 45,mtwCutEle=50,metPhi=-999, leptonPhi=-999, fJetPhi=-999,bJetPhi=-999, fJetEta = -999 , bJetEta=-999,leptonEta=-999, leptonPt = -999, fJetPt=-999,bJetPt=-999, fJetRMS=-999, leptonEff =-999, leptonEffB=-999, bJetRMS = -999, HT =-999,secondJetPt = -999, bJet1Phi=-999, bJet1Eta = -999 , bJet1Pt=-999, bJet2Phi=-999, bJet2Eta = -999 , bJet2Pt=-999,
    leptonSF = -999,    leptonSFB=-999,    leptonSFC=-999,    leptonSFD=-999,
    topMassLowCut = 130, topMassHighCut = 220,PUWeight=-999,bWeight=-999,turnOnWeight=-999, topPtReweightNorm=-999,
    turnOnWeightBTagTrig1Up=-999,
    turnOnWeightBTagTrig1Down=-999,
    turnOnWeightBTagTrig2Up=-999,
    turnOnWeightBTagTrig2Down=-999,
    turnOnWeightBTagTrig3Up=-999,
    turnOnWeightBTagTrig3Down=-999,
    turnOnWeightJetTrig1Up=-999,
    turnOnWeightJetTrig1Down=-999,
    turnOnWeightJetTrig2Up=-999,
    turnOnWeightJetTrig2Down=-999,
    turnOnWeightJetTrig3Up=-999,
    turnOnWeightJetTrig3Down=-999,
    bWeightBTagUp = -999.,
    bWeightBTagDown = -999.,
    bWeightMisTagUp = -999.,
    bWeightMisTagDown = -999.,
    PUWeightPUDown = -999.,
    PUWeightPUUp = -999.,
    turnOnReWeight =-999.
    ;
    
  float etaFloat =-999;
  float topMassFloat =-999;
  float costhetaljFloat =-999;
  float mstwweight=-999., nnpdfweight=-999.;
  
  int eleID =-999, eventFlavour=-999;
  
  //W Sample
  double etaWSampleLow =-999,etaWSampleHigh =-999,costhetaljWSample=-999,weightWSample=-999,mtwMassWSample=-999,mtwCutWSample=50,topMassWSample= -999,leptonRelIsoWSample=-999;
  
  //initializing variables
  //QCD Signal sample
  double QCDeta =-999,QCDetaLow = -999, QCDetaHigh=-999,QCDcosthetalj=-999,QCDweight=-999,QCDmtwMass=-999,QCDmtwCut=50,QCDtopMass= -999,QCDleptonRelIso=-999;
  
  //QCD W Sample
  double QCDetaWSampleLow =-999,QCDetaWSampleHigh =-999,QCDcosthetaljWSample=-999,QCDweightWSample=-999,QCDmtwMassWSample=-999,QCDmtwCutWSample=50,QCDtopMassWSample= -999,QCDleptonRelIsoWSample=-999;

  
  int chargeVal = -999; 
  int chargeWSample  = -999; 
  int QCDcharge = -999; 
  int QCDchargeWSample  = -999; 

  RooRealVar RelIso("leptonRelIso","lepton Relative isolation", 0.1, -1, 1);
  RooRealVar Eta("eta","Forward Jet Eta", 0.1, 0, 5);
  RooRealVar TopMass("topMass","TopMass", 170, 100, 300);
  //RooRealVar CosThetaLJ("costhetalj","CosThetaLJ", 0.1, -1, 1);
  RooRealVar Costhetalj("costhetalj","CosThetaLJ", 0.1, -1, 1);
  RooRealVar ChargeVal("charge","Lepton Charge", 0.1, -1, 1);
  RooRealVar MTWMass("mtwMass","W transverse mass", 0.1, 0, 500);
  RooRealVar MET("metPt","MET", 0.1, 0, 500);
  
  //Parameters for interpolation/ number of cpus
  //  int nbins = 20,nbins_alpha=3, order = 1,ncpu = 9;
  
  //  Eta.setBins(nbins,"cache");
  //  CosThetaLJ.setBins(nbins,"cache");

  RooCategory Lepton("Lepton","Lepton");
  Lepton.defineType("Mu");
  Lepton.defineType("Ele"); 
 
  RooCategory Charge("Charge","Charge");
  Charge.defineType("Plus");
  Charge.defineType("Minus");

  RooCategory LeptonCharge("LeptonCharge","LeptonCharge");
  Lepton.defineType("MuPlus");
  Lepton.defineType("ElePlus");
  Lepton.defineType("MuMinus");
  Lepton.defineType("EleMinus");
  
  //RooCategory Channel("Channel","Channel");
  //Channel.defineType("WJets");
  //Channel.defineType("TTBar");
  //Channel.defineType("QCD");
  //Channel.defineType("TChannel");

  TH1D * eta_Data_FitWSampleSR1_noSyst_Mu = new TH1D("eta_Data_FitWSampleSR1_noSyst_Mu","eta_Data_FitWSampleSR1_noSyst_Mu",
						     nbins["eta"],minobs["eta"],maxobs["eta"]);
  TH1D * eta_Data_FitWSampleSR1_noSyst_Ele = new TH1D("eta_Data_FitWSampleSR1_noSyst_Ele","eta_Data_FitWSampleSR1_noSyst_Ele",
						      nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_Data_FitWSampleSR2_noSyst_Mu = new TH1D("eta_Data_FitWSampleSR2_noSyst_Mu","eta_Data_FitWSampleSR2_noSyst_Mu",
						     nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_FitWSampleSR2_noSyst_Ele = new TH1D("eta_Data_FitWSampleSR2_noSyst_Ele","eta_Data_FitWSampleSR2_noSyst_Ele",
						      nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_Data_Fit_WModel_Mu = new TH1D("eta_Data_Fit_WModel_Mu","eta_Data_Fit_WModel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_Fit_WModel_Ele = new TH1D("eta_Data_Fit_WModel_Ele","eta_Data_Fit_WModel_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_SignalTop_Remodel_Mu = new TH1D("eta_SignalTop_Remodel_Mu","eta_SignalTop_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_SignalAntiTop_Remodel_Mu = new TH1D("eta_SignalAntiTop_Remodel_Mu","eta_SignalAntiTop_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_SignalSR1_Remodel_Mu = new TH1D("eta_SignalSR1_Remodel_Mu","eta_SignalSR1_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_TopSR1_Remodel_Func= new TH1D("eta_TopSR1_Remodel_Func","eta_TopSR1_Remodel_Func",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

 
  TH1D * eta_TopSR2_Remodel_Func= new TH1D("eta_TopSR1_Remodel_Func","eta_TopSR1_Remodel_Func",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR2_Remodel_Mu_noCharge = new TH1D("eta_TopSR1_Remodel_Func_NoCharge","eta_TopSR1_Remodel_Func_NoCharge",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR1_Remodel_Func3J1T= new TH1D("eta_TopSR1_Remodel_Func3J1T","eta_TopSR1_Remodel_Func3J1T",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_TopSR2_Remodel_Func3J1T= new TH1D("eta_TopSR1_Remodel_Func3J1T","eta_TopSR1_Remodel_Func3J1T",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR1_Remodel_Mu = new TH1D("eta_TopSR1_Remodel_Mu","eta_TopSR1_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR2_Remodel_Mu = new TH1D("eta_TopSR2_Remodel_Mu","eta_TopSR2_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR1_3J2T_Mu = new TH1D("eta_TopSR1_3J2T_Mu","eta_TopSR1_3J2T_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TopSR2_3J2T_Mu = new TH1D("eta_TopSR2_3J2T_Mu","eta_TopSR2_3J2T_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel  = new TH1D("eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel","eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel  = new TH1D("eta_EWKSR2_noSyst_Mu_3J2TSR1_remodel","eta_EWKSR2_noSyst_Mu_3J2TSR1_remodel",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_TTBarSR1_Remodel_Mu = new TH1D("eta_TTBarSR1_Remodel_Mu","eta_TTBarSR1_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_TTBarSR2_Remodel_Mu = new TH1D("eta_TTBarSR2_Remodel_Mu","eta_TTBarSR2_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);



  TH1D * eta_TopSR1_Extrap_3J2T = new TH1D("eta_TopSR1_Extrap_3J2T","eta_TopSR1_Extrap_3J2T",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_TopSR2_Extrap_3J2T = new TH1D("eta_TopSR2_Extrap_3J2T","eta_TopSR2_Extrap_3J2T",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);



  //Standard remodeling + uncertainties
  TH1D * eta_EWKSR1_Remodel_Mu = new TH1D("eta_EWKSR1_Remodel_Mu","eta_EWKSR1_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Remodel_Ele = new TH1D("eta_EWKSR1_Remodel_Ele","eta_EWKSR1_Remodel_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_EWKSR1_Remodel_Down_Mu = new TH1D("eta_EWKSR1_Remodel_Down_Mu","eta_EWKSR1_Remodel_Down_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Remodel_Down_Ele = new TH1D("eta_EWKSR1_Remodel_Down_Ele","eta_EWKSR1_Remodel_Down_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_EWKSR1_Remodel_Up_Mu = new TH1D("eta_EWKSR1_Remodel_Up_Mu","eta_EWKSR1_Remodel_Up_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Remodel_Up_Ele = new TH1D("eta_EWKSR1_Remodel_Up_Ele","eta_EWKSR1_Remodel_Up_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						



  TH1D * eta_EWKSR1_RemodelShape_Mu = new TH1D("eta_EWKSR1_RemodelShape_Mu","eta_EWKSR1_RemodelShape_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_RemodelShape_Ele = new TH1D("eta_EWKSR1_RemodelShape_Ele","eta_EWKSR1_RemodelShape_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						


  TH1D * eta_Data_Fit_Prediction_Mu = new TH1D("eta_EWKSR1_Prediction_Mu","eta_EWKSR1_Prediction_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_Fit_Prediction_Mu_Plus = new TH1D("eta_EWKSR1_Prediction_Mu_Plus","eta_EWKSR1_Prediction_Mu_Plus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_Fit_Prediction_Mu_Minus = new TH1D("eta_EWKSR1_Prediction_Mu_Minus","eta_EWKSR1_Prediction_Mu_Minus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_FitSR2_Prediction_Mu = new TH1D("eta_EWKSR2_Prediction_Mu","eta_EWKSR2_Prediction_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_FitSR2_Prediction_Mu_Plus = new TH1D("eta_EWKSR2_Prediction_Mu_Plus","eta_EWKSR2_Prediction_Mu_Plus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_FitSR2_Prediction_Mu_Minus = new TH1D("eta_EWKSR2_Prediction_Mu_Minus","eta_EWKSR2_Prediction_Mu_Minus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_Fit_Prediction_Ele = new TH1D("eta_EWKSR1_Prediction_Ele","eta_EWKSR1_Prediction_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						

  TH1D * eta_Data_Fit_PredictionVariated_Mu = new TH1D("eta_EWKSR1_PredictionVariated_Mu","eta_EWKSR1_PredictionVariated_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_Data_Fit_PredictionVariated_Ele = new TH1D("eta_EWKSR1_PredictionVariated_Ele","eta_EWKSR1_PredictionVariated_Ele",
					    nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);						


  //Part of separation

  TH1D * eta_WJets_wbbSR1_noSyst = new TH1D("eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"","eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR1_noSyst = new TH1D("eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"","eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR1_noSyst = new TH1D("eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"","eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_WJets_wbbSR1_noSyst_Plus = new TH1D("eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR1_noSyst_Plus = new TH1D("eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR1_noSyst_Plus = new TH1D("eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"_Plus",   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_WJets_wbbSR1_noSyst_Minus = new TH1D("eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wbbSR1_noSyst_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR1_noSyst_Minus = new TH1D("eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wccSR1_noSyst_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR1_noSyst_Minus = new TH1D("eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wlightSR1_noSyst_"+TString(leptonCase)+"_Minus", nbins["eta"],minobs["eta"],maxobs["eta"]);



  TH1D * eta_WJets_wbbSR2_noSyst = new TH1D("eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"","eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR2_noSyst = new TH1D("eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"","eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR2_noSyst = new TH1D("eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"","eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_WJets_wbbSR2_noSyst_Plus = new TH1D("eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR2_noSyst_Plus = new TH1D("eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR2_noSyst_Plus = new TH1D("eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"_Plus","eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"_Plus",   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_WJets_wbbSR2_noSyst_Minus = new TH1D("eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wbbSR2_noSyst_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wccSR2_noSyst_Minus = new TH1D("eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wccSR2_noSyst_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wlightSR2_noSyst_Minus = new TH1D("eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"_Minus","eta_WJets_wlightSR2_noSyst_"+TString(leptonCase)+"_Minus", nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Wbb_Remodeled = new TH1D("eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"","eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Wbb_Remodeled_Plus = new TH1D("eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"_Plus","eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Wbb_Remodeled_Minus = new TH1D("eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"_Minus","eta_EWKSR1_Wbb_Remodeled_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_EWKSR1_Wcc_Remodeled = new TH1D("eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"","eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Wcc_Remodeled_Plus = new TH1D("eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"_Plus","eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"_Plus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Wcc_Remodeled_Minus = new TH1D("eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"_Minus","eta_EWKSR1_Wcc_Remodeled_"+TString(leptonCase)+"_Minus",
					    nbins["eta"],minobs["eta"],maxobs["eta"]);





  //End of separation
  //Part of remodeled w+c/w+b
  TH1D * eta_WJets_wbb_Remodel_Ele = new TH1D("eta_WJets_wbb_Remodel_Ele","eta_WJets_wbb_Remodel_Ele",
				nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wcc_Remodel_Ele = new TH1D("eta_WJets_wcc_Remodel_Ele","eta_WJets_wcc_Remodel_Ele",
				nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wbbWSampleSR1_noSyst_Ele = new TH1D("eta_WJets_wbbWSampleSR1_noSyst_Ele","eta_WJets_wbbWSampleSR1_noSyst_Remodel_Ele",
					  nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wccWSampleSR1_noSyst_Ele = new TH1D("eta_WJets_wccWSampleSR1_noSyst_Remodel_Ele","eta_WJets_wccWSampleSR1_noSyst_Remodel_Ele",
					  nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wbbWSampleSR2_noSyst_Ele = new TH1D("eta_WJets_wbbWSampleSR2_noSyst_Ele","eta_WJets_wbbWSampleSR2_noSyst_Remodel_Ele",
					  nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wccWSampleSR2_noSyst_Ele = new TH1D("eta_WJets_wccWSampleSR2_noSyst_Remodel_Ele","eta_WJets_wccWSampleSR2_noSyst_Remodel_Ele",
					  nbinseleeta["eta"],minobs["eta"],maxobs["eta"]);
  
  
  
  
  TH1D * eta_WJets_wbb_Remodel_Mu = new TH1D("eta_WJets_wbb_Remodel_Mu","eta_WJets_wbb_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wcc_Remodel_Mu = new TH1D("eta_WJets_wcc_Remodel_Mu","eta_WJets_wcc_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_WJets_wbbWSampleSR1_noSyst_Mu = new TH1D("eta_WJets_wbbWSampleSR1_noSyst_Mu","eta_WJets_wbbWSampleSR1_noSyst_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wccWSampleSR1_noSyst_Mu = new TH1D("eta_WJets_wccWSampleSR1_noSyst_Remodel_Mu","eta_WJets_wccWSampleSR1_noSyst_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_WJets_wbbWSampleSR2_noSyst_Mu = new TH1D("eta_WJets_wbbWSampleSR2_noSyst_Mu","eta_WJets_wbbWSampleSR2_noSyst_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  TH1D * eta_WJets_wccWSampleSR2_noSyst_Mu = new TH1D("eta_WJets_wccWSampleSR2_noSyst_Remodel_Mu","eta_WJets_wccWSampleSR2_noSyst_Remodel_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);


  TH1D * eta_EWKSR1_Remodel_scaling_Mu = new TH1D("eta_EWKSR1_Remodel_scaling_Mu","eta_EWKSR1_Remodel_scaling_Mu",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Remodel_scaling_Mu_Plus = new TH1D("eta_EWKSR1_Remodel_scaling_Mu_Plus","eta_EWKSR1_Remodel_scaling_Mu_Plus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);

  TH1D * eta_EWKSR1_Remodel_scaling_Mu_Minus = new TH1D("eta_EWKSR1_Remodel_scaling_Mu_Minus","eta_EWKSR1_Remodel_scaling_Mu_Minus",
					   nbins["eta"],minobs["eta"],maxobs["eta"]);
  
  RooDataSet * CombinedDataSet = new RooDataSet;//("CombinedDataEleMu","CombinedDataEleMu",RooArgList(EtaMu,TopMassvarMu,EtaEle,TopMassvarEle),Index(SampleEleMu),Import(ele.c_str(),*datasetCosthetaljEtaEle),Import(mu.c_str(),*datasetCosthetaljEtaMu));
  
  RooDataSet * MTWDataSetMu = new RooDataSet;//("MTWMu","MTWMu",RooArgList(),);
  RooDataSet * MTWDataSetEle = new RooDataSet;


  string defaultcut = "mtwMass > 50 && topMass > 100 && topMass < 300 && leptonRelIso<0.1";
  //  string topcut = "topMass > 100 && topMass < 300 && leptonRelIso < 0.175";
  string topcut = "leptonRelIso < 0.1";
  
  std::vector<string> samples; 
  samples.push_back("AntiIso");
  samples.push_back("AntiIsoWSample");
  samples.push_back("AntiIsoSR1");
  samples.push_back("AntiIsoSR2");
  samples.push_back("WSample");
  samples.push_back("3J2TSR1");
  samples.push_back("3J2TSR2");
  //  samples.push_back("3J2T");
  //  samples.push_back("AntiIsoSampleB");
  //  samples.push_back("SampleB");
  //  samples.push_back("ESB");
  //  samples.push_back("AntiIsoESB");
  samples.push_back("");
  samples.push_back("SR1");
  samples.push_back("SR2");

  string pseudodatas[2] = {"","Pseudo"};
  
  ///LOOP 1 INITIALIZE CHANNEL BY CHANNEL AND SIG/BKGS HISTOGRAMS
  //MUST USE ALL CHANNELS AND SYSTEMATICS
  for(std::vector<string>::const_iterator it = allchannels.begin(); it != allchannels.end(); ++it){
    string channel = (*it);
    string filename = (folder + "/"+channel+".root");
    for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
      string syst = (*it_s);
      int n_syst_extremes=2;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	if(syst =="WModel")updown ="";
	string systUpDown = syst + updown;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	  for( int d =0; d< 2 ;++d){
	    string pseudodata = pseudodatas[d];
	    for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	      string sample = (*it_sam);
	      for (int lep = 0; lep <2;++lep){
		string lepton = leptons[lep]; if(lepton != leptonCase)continue;
		//Fill the histograms    
		for(int ch = 0; ch < 2; ++ch){
		  string charge = charges[ch];
		  string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+pseudodata+"_"+charge;
		  string histoname = name;
		  if((observable == "etaTUp" || observable == "etaTDown" || 
		      observable == "etaTTUp" || observable == "etaTTDown" 
		      ) && (sample != "SR1" && sample != "SR2" ))continue;
		  if(observable == "topMassQCD" && !(sample == "" || sample == "AntiIso") ) continue;
		  if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
				       observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh" 
				       )) {
		    HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge] = 
		      new TH1D( (histoname).c_str(), (histoname).c_str(),nbinseleeta[observable],minobs[observable],maxobs[observable]);
		  }  else  HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge] =    new TH1D( (histoname).c_str(), (histoname).c_str(),nbins[observable],minobs[observable],maxobs[observable]);
		  
		  if(channel == "Data" && syst == "noSyst" && observable == "etaTopMass"){
		    Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge] = 
		      new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbins["eta"],minobs["eta"],maxobs["eta"],nbins["topMass"],minobs["topMass"],maxobs["topMass"]);
		  }
		  
		  if(channel == "Data" && syst == "noSyst" && observable == "etaCosthetalj"){
		    if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
					 observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh" 
					 ))  {
		    Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge] = 
		      new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbinseleeta["eta"],minobs["eta"],maxobs["eta"],nbins["costhetalj"],minobs["costhetalj"],maxobs["costhetalj"]);
		    } else Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge] = new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbins["eta"],minobs["eta"],maxobs["eta"],nbins["costhetalj"],minobs["costhetalj"],maxobs["costhetalj"]);

		  }

		  
		  ////		  cout<< " name : " << name <<" integral "<< HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata+charge]->Integral()  <<endl;
		}
		string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+pseudodata;
		string histoname = name;
		if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
				     observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh" 
				     )) {
		  HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata] = 
		    new TH1D( (histoname).c_str(), (histoname).c_str(),nbinseleeta[observable],minobs[observable],maxobs[observable]);
		}
		else  HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata] =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbins[observable],minobs[observable],maxobs[observable]);
		

		cout<< " name : " << name << endl;
		
		if(channel == "Data" && syst == "noSyst" && observable == "etaTopMass"){
		  Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata] = 
		    new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbins["eta"],minobs["eta"],maxobs["eta"],nbins["topMass"],minobs["topMass"],maxobs["topMass"]);
		}
		if(channel == "Data" && syst == "noSyst" && observable == "etaCosthetalj"){
		  if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
				       observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh"   )) {  Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata] =    new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbinseleeta["eta"],minobs["eta"],maxobs["eta"],nbins["costhetalj"],minobs["costhetalj"],maxobs["costhetalj"]);
		  } else  Histo2DCollection[observable][channel+sample][systUpDown][lepton+pseudodata] =   new TH2D( (histoname+"2D").c_str(), (histoname+"2D").c_str(),nbins["eta"],minobs["eta"],maxobs["eta"],nbins["costhetalj"],minobs["costhetalj"],maxobs["costhetalj"]);
		}
	      }
	    }
	  }
	}
      }
    }
  }
    //  cout << " test data no syst mu plus mtwMass " << HistoCollection["mtwMass"]["Data"]["noSyst"]["MuPlus"]<<endl<< endl;
  //  cout<<" integral " << HistoCollection["mtwMass"]["Data"]["noSyst"]["MuPlus"]->Integral()<<endl;
  
  
  
  //LOOP 3
  //Reading and putting into a local tree for easier handling:
  //ONLY MC CHANNELS AND NON DATA DRIVEN SYSTEMATICS
  //cout <<"channelsplusqcd size " << channelsplusqcd.size()<<endl;
  for (int lep = 0; lep <2;++lep){ 
    string lepton = leptons[lep];
    if(lepton != leptonCase)continue;

    for(std::vector<string>::const_iterator it = channelsplusqcd.begin(); it != channelsplusqcd.end(); ++it){
    string channel = (*it);
    string filename = (folder + "/"+channel+".root");
    //cout << "channel plus qcd "<< channel << " filename "<< filename<<endl; 
    if (leptonCase== "Ele" && channel == "Data")filename= (folder + "/"+channel+"_Ele"+".root");
    TFile f(filename.c_str(),"OPEN");
    if( !f.IsOpen() ){
      cout<< " WARNING FILE " << filename << endl;
      continue;
    }
    for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
      string syst = (*it_s);
      
      cout << "channel "<<channel <<" syst "<<  syst << " 0 " << endl; 
      
      string prefix = channel+"_"+syst;
      cout << "channel BEFORE "<<channel <<" syst "<<  syst << " 0 " << endl; 
      string systUp = syst+"Up";
      string systDown = syst+"Down";
      
      if(syst == "noSyst")systUp=syst,systDown =syst;
      
      double integralTotUp =0;
      double integralTotDown =0;
      
	for(int ch = 0; ch < 2; ++ch){
	  string charge = charges[ch];
	  //Fill the histograms
	  int n_syst_extremes=2;
	  if(syst == "noSyst")n_syst_extremes=1; 
	  for (int ud = 0;ud<n_syst_extremes;++ud){
	    
	    string updown = UpDown[ud];
	    if(syst =="noSyst")updown ="";
	    
	    string systUpDown = syst+updown;
	    
	    bool isPDFsyst= false;
	    for(int p =1;p<=npdfstorun;++p){
	      if(syst == pdf_names[p-1])isPDFsyst=true;
	    }

	    string systUpDownTree = systUpDown;
	    bool usesNoSystTree=false;
	    if( ( syst == "WLight" && channel != "WJets_wlight") || 
		( syst == "TTBar" && channel != "TTBar") || 
		( syst == "VV" && channel != "VV") || 
		( syst == "SChannel" && channel != "SChannel" && channel != "SbarChannel") || 
		( syst == "TWChannel" && channel != "TWChannel" && channel !="TbarWChannel") || 
		( syst == "QCD" && channel == "QCD" ) || 
		(syst == "TTBar_Q2"&& channel != "TTBar_Q2Down" && channel != "TTBar_Q2Up")  ||
		(syst == "TTBar_Matching"&& channel != "TTBar_MatchingDown" && channel != "TTBar_MatchingUp")  ||
		(syst == "SignalModel"&& channel != "TChannel" && channel != "TbarChannel")  ||
		syst == "TWChannel_Q2" ||
		( syst == "WModel" ) ||
		(syst == "TChannel_Q2" && (channel != "TChannel_Q2Down" && channel != "TChannel_Q2Up" &&  
					   channel != "TbarChannel_Q2Down" && channel != "TbarChannel_Q2Up") ) || 
		(isPDFsyst && updown == "Down") ||
		(syst == "NNPDF21" && updown == "Down") ||
		(syst == "MSTW08" && updown == "Down") ||
		(syst == "Comp") ||
		(channel == "Data" && syst != "noSyst")
		){
	      usesNoSystTree = true;
	      systUpDownTree = "noSyst";
	    }
	    if( ( syst == "WLight" && channel == "WJets_wlight") || 
		( syst == "TTBar" && channel == "TTBar") || 
		( syst == "VV" && (channel == "WW" || channel == "WZ" || channel =="ZZ")) || 
		( syst == "SChannel" && (channel == "SChannel" || channel == "SbarChannel")) || 
		( syst == "TWChannel" && (channel == "TWChannel" || channel =="TbarWChannel")) || 
		( syst == "QCD" ) || 
		( syst == "PU") || 
		( syst == "BTag") || 
		( syst == "MisTag") || 
		( syst == "BTagTrig1") || 
		( syst == "BTagTrig2") || 
		( syst == "BTagTrig3") || 
		( syst == "JetTrig1") || 
		( syst == "JetTrig2") || 
		( syst == "JetTrig3") || 
		( syst == "BTagTrigSF") || 
 	       syst == "MuonTrig" ||
	       syst == "EleEff" || 
	       syst == "EleMisId" || 
		(isPDFsyst && updown == "Up") ||
		(syst == "NNPDF21" && updown == "Up") ||
		(syst == "MSTW08" && updown == "Up") ||
		(syst == "SignalModel"&& (channel == "TChannel" || channel == "TbarChannel"))  ||
		(channel == "Data") && syst != "noSyst"){
	      systUpDownTree = "noSyst";
	    }
	    


	    if(syst=="TTBar_Q2"){
	      if(channel == "TTBar") continue;
	      if(systUpDown == "TTBar_Q2Up" && channel == "TTBar_Q2Up"){
		systUpDownTree = "noSyst";
	      }
	      else if(systUpDown == "TTBar_Q2Down" && channel == "TTBar_Q2Down"){
		systUpDownTree = "noSyst";
	      }
	      
	    }


	    if(syst=="TTBar_Matching"){
	      if(channel == "TTBar") continue;
	      if(systUpDown == "TTBar_MatchingUp" && channel == "TTBar_MatchingUp"){
		systUpDownTree = "noSyst";
	      }
	      else if(systUpDown == "TTBar_MatchingDown" && channel == "TTBar_MatchingDown"){
		systUpDownTree = "noSyst";
	      }
	      
	    }
	  
	    if(syst=="TWChannel_Q2"){
	      if(channel == "TWChannel"|| channel == "TbarWChannel") continue;
	      if((systUpDown == "TWChannel_Q2Up") && (channel == "TWChannel_Q2Up" || channel == "TbarWChannel_Q2Up")){
		systUpDownTree = "noSyst";
	      }
	      else if((systUpDown == "TWChannel_Q2Down") && (channel == "TWChannel_Q2Down" || channel == "TbarWChannel_Q2Down")){
		systUpDownTree = "noSyst";
	      }
	    }

	    if(syst=="TChannel_Q2"){
	      if(channel == "TChannel" || channel == "TbarChannel") continue;
	      if((systUpDown == "TChannel_Q2Up") && (channel == "TChannel_Q2Up" || channel == "TbarChannel_Q2Up")){
		systUpDownTree = "noSyst";
	      }
	      else if((systUpDown == "TChannel_Q2Down") && (channel == "TChannel_Q2Down" || channel == "TbarChannel_Q2Down")){
		systUpDownTree = "noSyst";
	      }
	    }
	    
	    if(systUpDown!= "TTBar_Q2Down"  && (channel == "TTBar_Q2Down") )continue;
	    if(systUpDown!= "TTBar_Q2Up" && (channel == "TTBar_Q2Up") )continue;

	    if(systUpDown!= "TTBar_MatchingDown"  && (channel == "TTBar_MatchingDown") )continue;
	    if(systUpDown!= "TTBar_MatchingUp" && (channel == "TTBar_MatchingUp") )continue;
	    
	    if(syst != "TWChannel_Q2Down" && (channel == "TWChannel_Q2Down" || channel == "TbarWChannel_Q2Down"))continue;
	    if(syst != "TWChannel_Q2Up" && (channel == "TWChannel_Q2Up" || channel == "TbarWChannel_Q2Up"))continue;

	    if(systUpDown != "TChannel_Q2Down" && (channel == "TChannel_Q2Down" || channel == "TbarChannel_Q2Down"))continue;
	    if(systUpDown != "TChannel_Q2Up" && (channel == "TChannel_Q2Up" || channel == "TbarChannel_Q2Up"))continue;

	    
	    string path = "Trees"+lepton+"/"+channel+"_2J_2T_"+systUpDownTree;

	    int count=0;
	    
	    TMVA::Reader * reader = new TMVA::Reader( "!Color:!Silent" );
	    // book method as likelihood with the weights of the variables
	    
	  
	    cout << " channel syst lepton charge "<< channel<< systUpDown<< lepton<< charge << endl;
	    cout << " syst for tree "<< systUpDownTree<< endl;
	  
	    trees[channel][systUpDownTree][lepton] = new TTree();
	    trees[channel][systUpDownTree][lepton] = (TTree*)f.Get(path.c_str());
	    
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("eta",&eta);

	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("weight",&weight);

	    //if(systUpDown=="PUUp") 
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeightPUUp",&PUWeightPUUp);
	    //if(systUpDown=="PUDown")
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeightPUDown",&PUWeightPUDown);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);

	    if(systUpDown=="BTagUp")trees[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightBTagUp",&bWeightBTagUp);
	    if(systUpDown=="BTagDown")trees[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightBTagDown",&bWeightBTagDown);
	    if(systUpDown=="MisTagUp")trees[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightMisTagUp",&bWeightMisTagUp);
	    if(systUpDown=="MisTagDown")trees[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightMisTagDown",&bWeightMisTagDown);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bWeight",&bWeight);
	    //	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("topPtReweightNorm",&topPtReweightNorm);


	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeight",&turnOnWeight);
	    if(systUpDown=="BTagTrig1Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig1Up",&turnOnWeightBTagTrig1Up);
	    if(systUpDown=="BTagTrig1Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig1Down",&turnOnWeightBTagTrig1Down);
	    if(systUpDown=="BTagTrig2Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig2Up",&turnOnWeightBTagTrig2Up);
	    if(systUpDown=="BTagTrig2Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig2Down",&turnOnWeightBTagTrig2Down);
	    if(systUpDown=="BTagTrig3Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig3Up",&turnOnWeightBTagTrig3Up);
	    if(systUpDown=="BTagTrig3Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig3Down",&turnOnWeightBTagTrig3Down);

	    if(systUpDown=="JetTrig1Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig1Up",&turnOnWeightJetTrig1Up);
	    if(systUpDown=="JetTrig1Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig1Down",&turnOnWeightJetTrig1Down);
	    if(systUpDown=="JetTrig2Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig2Up",&turnOnWeightJetTrig2Up);
	    if(systUpDown=="JetTrig2Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig2Down",&turnOnWeightJetTrig2Down);
	    if(systUpDown=="JetTrig3Up")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig3Up",&turnOnWeightJetTrig3Up);
	    if(systUpDown=="JetTrig3Down")trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig3Down",&turnOnWeightJetTrig3Down);
	        
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnReWeight",&turnOnReWeight);
	
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("charge",&chargeVal);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("mtwMass",&mtwMass);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("metPt",&metPt);
	    
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("metPhi",&metPhi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPhi",&leptonPhi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPhi",&fJetPhi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPt",&fJetPt);
	    /*	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("fJetRMS",&fJetRMS);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJetRMS",&bJetRMS);
	    */
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEta",&leptonEta);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPt",&leptonPt);

	    //	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("eventFlavour",&eventFlavour);


	    //	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("HT",&HT);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("lowBTag",&lowBTag);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJetPt",&bJetPt);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJetPhi",&bJetPhi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&bJetEta);

	    /*	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Pt",&bJet1Pt);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Phi",&bJet1Phi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Eta",&bJet1Eta);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Pt",&bJet2Pt);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Phi",&bJet2Phi);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Eta",&bJet2Eta);
	    */
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj",&costhetalj);
	    //	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj_bJet",&costhetalj_bJet);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("topMass",&topMass);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("ID",&eleID);
	    if( lepton == "Mu")	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	    if( lepton == "Ele")	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);

	    /*	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEff",&leptonEff);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEffB",&leptonEffB);
	    */
	    /*	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSF",&leptonSF);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFB",&leptonSFB);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFC);
	    trees[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFD",&leptonSFD);
	    */
	      if(useDifferentModel){
		trees[channel][systUpDownTree][lepton]->SetBranchAddress("PDFWeight_MSTW",&mstwweight);
		trees[channel][systUpDownTree][lepton]->SetBranchAddress("PDFWeight_NNPDF21",&nnpdfweight);
	      }
	    
	    if(useSystPDF){
	      for(int p =1;p<=npdfstorun;++p){
		if (!(p >= MinPDF && p <=MaxPDF))continue;  
		if(syst == pdf_names[p-1]) trees[channel][systUpDownTree][lepton]->SetBranchAddress(pdf_names[p-1].c_str(),&pdf_weights[p-1]);
	      }
	    }
	    //cout << " test al"<<  endl;


	    treesWSample[channel][systUpDownTree][lepton] = new TTree();
	    string pathwsample = "Trees"+lepton+"/"+channel+"_"+systUpDownTree+"WSample";
	    cout << " pathwsample " << pathwsample << endl;
	    treesWSample[channel][systUpDownTree][lepton] = (TTree*)f.Get((pathwsample).c_str());
	    
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&etaLow);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&etaHigh);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("weight",&weight);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("bWeight",&bWeight);
	    //	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("topPtReweightNorm",&topPtReweightNorm);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeight",&turnOnWeight);

	    /*	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("fJetRMS",&fJetRMS);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("bJetRMS",&bJetRMS);
	    */
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPt",&fJetPt);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("bJetPt",&bJetPt);


	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEta",&leptonEta);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPt",&leptonPt);

	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("charge",&chargeVal);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("mtwMass",&mtwMass);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("metPt",&metPt);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj",&costhetalj);
	    //	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj_bJet",&costhetalj_bJet);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("topMass",&topMass);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("ID",&eleID);
	    if(lepton == "Mu")treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	    if(lepton == "Ele")treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("lowBTag",&lowBTag);/////
	    //	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&etaHigh);
	    //	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&etaLow);

	    /*	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEff",&leptonEff);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEffB",&leptonEffB);
	    
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSF",&leptonSF);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFB",&leptonSFB);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFC);
	    treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFD);
	    */

	    //	    map<string, map< string, map < string, TTree *> > > trees3J2T;


	    trees3J2T[channel][systUpDownTree][lepton] = new TTree();
	    string pathttsample = "Trees"+lepton+"/"+channel+"_"+systUpDownTree+"3J2T";
	    trees3J2T[channel][systUpDownTree][lepton] = (TTree*)f.Get((pathttsample).c_str());
	    
	    //	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("secondJetPt",&secondJetPt);
	    //	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("thirdJetPt",&secondJetPt);
	    //	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("secondJetPt",&secondJetPt);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&etaLow);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&etaHigh);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEta",&leptonEta);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPt",&leptonPt);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("weight",&weight);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeightPUUp",&PUWeightPUUp);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bWeight",&bWeight);
	    //	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("topPtReweightNorm",&topPtReweightNorm);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeight",&turnOnWeight);

	    /*	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("fJetRMS",&fJetRMS);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJetRMS",&bJetRMS);
	    */
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPhi",&fJetPhi);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPt",&fJetPt);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJetPt",&bJetPt);


	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("charge",&chargeVal);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("mtwMass",&mtwMass);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("metPt",&metPt);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj",&costhetalj);
	    //	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj_bJet",&costhetalj_bJet);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("topMass",&topMass);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("ID",&eleID);
	    if(lepton =="Mu")trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	    if( lepton == "Ele")trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("lowBTag",&lowBTag);/////

	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&etaHigh);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&etaLow);
	    /*	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Eta",&bJet1Eta);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Phi",&bJet1Phi);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Pt",&bJet1Pt);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Eta",&bJet2Eta);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Phi",&bJet2Phi);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Pt",&bJet2Pt);
	    */
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("eta",&eta);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);
	    /*	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEff",&leptonEff);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEffB",&leptonEffB);
	    */
	    /*	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSF",&leptonSF);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFB",&leptonSFB);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFC);
	    trees3J2T[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFD);
	    */

	    
	    if(syst == "noSyst"){
	      cout << "HERE 11.5" << endl;
	      string filenameQCD;
	      TFile *fQCD;
	      if (channel == "Data"){
		cout << "I'M HERE !!!!!!" << endl;
		filenameQCD = ("/afs/cern.ch/work/m/mmerola/TreesxCombination/event_trees_naples/"+channel+".root");
		cout << "channel plus qcd "<< channel << " filenameQCD "<< filenameQCD << endl;
		fQCD = TFile::Open(filenameQCD.c_str());
		if( !fQCD->IsOpen() ){
		  cout<< " WARNING FILE " << filenameQCD << endl;
		  continue;
		}
	      }
	    	    cout << "HERE 12" << endl;
	      treesQCD[channel][systUpDownTree][lepton] = new TTree();
	      string pathqcd = "Trees"+lepton+"/"+channel+"_2J_2T_QCD_"+systUpDownTree;
	      treesQCD[channel][systUpDownTree][lepton] = (TTree*)f.Get((pathqcd).c_str());
	      if (channel == "Data")
		treesQCD[channel][systUpDownTree][lepton] = (TTree*)fQCD->Get((pathqcd).c_str());
	      
	      //cout << " test gam"<<  endl;
	      
	      	    	    cout << "HERE 13" << endl;
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("weight",&weight);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("charge",&chargeVal);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("mtwMass",&mtwMass);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("metPt",&metPt);
	      	      	    	    cout << "HERE 14" << endl;
	      if(lepton == "Mu") treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	      if( lepton == "Ele")  treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	      
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("eta",&eta);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj",&costhetalj);
	      //	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj_bJet",&costhetalj_bJet);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("topMass",&topMass);
	      	      	    	    cout << "HERE 15" << endl;
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("metPhi",&metPhi);
	      
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPhi",&leptonPhi);
	      /*	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Phi",&bJet1Phi);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Phi",&bJet2Phi);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Eta",&bJet1Eta);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Eta",&bJet2Eta);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet1Pt",&bJet1Pt);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJet2Pt",&bJet2Pt);
	      */
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPhi",&fJetPhi);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&fJetEta);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("fJetPt",&fJetPt);
	      	    	    cout << "HERE 16" << endl;
	      /*	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("fJetRMS",&fJetRMS);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJetRMS",&bJetRMS);
	      */
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEta",&leptonEta);
	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPt",&leptonPt);
      
	      /*	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEff",&leptonEff);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEffB",&leptonEffB);
	      
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSF",&leptonSF);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFB",&leptonSFB);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFC);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFD",&leptonSFD);
	    */
	      	    	    cout << "HERE 17" << endl;
	    if(systUpDown=="PUUp") treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeightPUUp",&PUWeightPUUp);
	    if(systUpDown=="PUDown")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeightPUDown",&PUWeightPUDown);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);

	    if(systUpDown=="BTagUp")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightBTagUp",&bWeightBTagUp);
	    if(systUpDown=="BTagDown")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightBTagDown",&bWeightBTagDown);
	    if(systUpDown=="MisTagUp")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightMisTagUp",&bWeightMisTagUp);
	    if(systUpDown=="MisTagDown")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeightMisTagDown",&bWeightMisTagDown);
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeight",&bWeight);
	    //	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("topPtReweightNorm",&topPtReweightNorm);
	      	    	    cout << "HERE 18" << endl;
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeight",&turnOnWeight);
	    if(systUpDown=="BTagTrig1Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig1Up",&turnOnWeightBTagTrig1Up);
	    if(systUpDown=="BTagTrig1Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig1Down",&turnOnWeightBTagTrig1Down);
	    if(systUpDown=="BTagTrig2Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig2Up",&turnOnWeightBTagTrig2Up);
	    if(systUpDown=="BTagTrig2Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig2Down",&turnOnWeightBTagTrig2Down);
	    if(systUpDown=="BTagTrig3Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig3Up",&turnOnWeightBTagTrig3Up);
	    if(systUpDown=="BTagTrig3Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightBTagTrig3Down",&turnOnWeightBTagTrig3Down);

	    if(systUpDown=="JetTrig1Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig1Up",&turnOnWeightJetTrig1Up);
	    if(systUpDown=="JetTrig1Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig1Down",&turnOnWeightJetTrig1Down);
	    if(systUpDown=="JetTrig2Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig2Up",&turnOnWeightJetTrig2Up);
	    if(systUpDown=="JetTrig2Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig2Down",&turnOnWeightJetTrig2Down);
	    if(systUpDown=="JetTrig3Up")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig3Up",&turnOnWeightJetTrig3Up);
	    if(systUpDown=="JetTrig3Down")treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeightJetTrig3Down",&turnOnWeightJetTrig3Down);
	    
      
	    treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnReWeight",&turnOnReWeight);


	      treesQCD[channel][systUpDownTree][lepton]->SetBranchAddress("ID",&eleID);
	      
	      treesWSampleQCD[channel][systUpDownTree][lepton] = new TTree();
	      string pathwsampleqcd = "Trees"+lepton+"/"+channel+"_"+systUpDownTree+"WSampleQCD";
	      treesWSampleQCD[channel][systUpDownTree][lepton] = (TTree*)f.Get((pathwsampleqcd).c_str());
	      
	      	    	    cout << "HERE 19" << endl;
	      //cout << " test del"<<  endl;
	      
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("fJetEta",&etaLow);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bJetEta",&etaHigh);

	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("weight",&weight);
	      	    	    cout << "HERE 20" << endl;
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("PUWeight",&PUWeight);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("bWeight",&bWeight);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("turnOnWeight",&turnOnWeight);
	      //	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("topPtReweightNorm",&topPtReweightNorm);
	      	      	    	    cout << "HERE 21" << endl;
 	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEta",&leptonEta);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonPt",&leptonPt);

	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("charge",&chargeVal);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("mtwMass",&mtwMass);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("metPt",&metPt);
	      
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("costhetalj",&costhetalj);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("topMass",&topMass);
	      if(lepton =="Mu" )treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);
	      if( lepton == "Ele") treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonRelIso",&leptonRelIso);

	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("ID",&eleID);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("lowBTag",&lowBTag);/////
	      	    	    cout << "HERE 22" << endl;
	      
	      /*	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEff",&leptonEff);
	      treesWSampleQCD[channel][systUpDownTree][lepton]->SetBranchAddress("leptonEffB",&leptonEffB);
	      */
	      /*	      treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSF",&leptonSF);
	      treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFB",&leptonSFB);
	      treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFC);
	      treesWSample[channel][systUpDownTree][lepton]->SetBranchAddress("leptonSFC",&leptonSFD);
	      */
	      
	      int nentriesQCD = treesQCD[channel][systUpDownTree][lepton]->GetEntries();
	      int nentriesWSampleQCD = treesWSampleQCD[channel][systUpDownTree][lepton]->GetEntries();
	      //	      int nentriesSampleBQCD = treesSampleBQCD[channel][systUpDownTree][lepton]->GetEntries();
	      
	      //cout << " before first loop "<<endl;
	      
	      count =0;
	      
	      //cout << " test zet"<<  endl;
	      	      	    	    cout << "HERE 23" << endl;
	      
	      //Fill Anti Iso T-Channel Sample Histograms

	      //Part () for the reader
				    cout << "channel: " << channel << "   nentriesQCD: " << nentriesQCD << endl;
	      if(!usesNoSystTree) for(int e = 0; e < nentriesQCD; ++e){
		treesQCD[channel][systUpDownTree][lepton]->GetEntry(e);
		
		double r = (double)(r)/(double)(nentriesQCD);
		r = rand.Uniform(); 
		string pseudodata = "";



				
		if(r<fraction) pseudodata += "Pseudo";
		if( weight == 0 || fabs(weight) > 100) continue;
		//		if(costhetalj > 0.99) continue;		
		//		if(costhetalj_bJet > 0.99) continue;
		
				
		
		double B = bWeight; 
		double TurnOn = turnOnWeight; 
		double PU = PUWeight; 


		if(systUpDown=="PUUp") PU = PUWeightPUUp; 
		if(systUpDown=="PUDown") PU =PUWeightPUDown; 

		if(systUpDown=="BTagUp") B = bWeightBTagUp; 
		if(systUpDown=="BTagDown") B =bWeightBTagDown; 
		if(systUpDown=="MisTagUp") B = bWeightMisTagUp; 
		if(systUpDown=="MisTagDown") B =bWeightMisTagDown; 


		if(systUpDown=="BTagTrig1Up") TurnOn =turnOnWeightBTagTrig1Up; 
		if(systUpDown=="BTagTrig1Down") TurnOn =turnOnWeightBTagTrig1Down; 

		if(systUpDown=="BTagTrig2Up") TurnOn =turnOnWeightBTagTrig2Up; 
		if(systUpDown=="BTagTrig2Down") TurnOn =turnOnWeightBTagTrig2Down; 
		if(systUpDown=="BTagTrig3Up") TurnOn =turnOnWeightBTagTrig3Up; 
		if(systUpDown=="BTagTrig3Down") TurnOn =turnOnWeightBTagTrig3Down; 

		if(systUpDown=="JetTrig1Up") TurnOn =turnOnWeightJetTrig1Up; 
		if(systUpDown=="JetTrig1Down") TurnOn =turnOnWeightJetTrig1Down; 
		if(systUpDown=="JetTrig2Up") TurnOn =turnOnWeightJetTrig2Up; 
		if(systUpDown=="JetTrig2Down") TurnOn =turnOnWeightJetTrig2Down; 
		if(systUpDown=="JetTrig3Up") TurnOn =turnOnWeightJetTrig3Up; 
		if(systUpDown=="JetTrig3Down") TurnOn =turnOnWeightJetTrig3Down; 

		//		PU=1;
		if(channel !="Data")weight *= B;


		weight = setWeight( channel+"AntiIso", systUpDown, lepton,"AntiIso" ,LumiC, weight );
		//		weight *= leptonWeight(lepton,leptonEta,channel,systUpDown);
		if((channel == "TChannel" || channel == "TbarChannel") && syst == "SignalModel"){
		  
		    if(lepton == "Mu"){
		      //cout << "eta mu " << eta<< " bin "<<  SFs_comp_pow_mu.FindBin(eta)<< " content "<< SFs_comp_pow_mu.GetBinContent(SFs_comp_pow_mu.FindBin(eta))<<endl;
		      weight*=SFs_comp_pow_mu.GetBinContent( SFs_comp_pow_mu.FindBin(eta));
		    }
		    if(lepton == "Ele"){
		      //cout << "eta ele " << eta<< " bin "<<  SFs_comp_pow_ele.FindBin(eta)<< " content "<< SFs_comp_pow_ele.GetBinContent(SFs_comp_pow_ele.FindBin(eta))<<endl;
		      weight*=SFs_comp_pow_ele.GetBinContent( SFs_comp_pow_ele.FindBin(eta));
		    }
		  
		}
		if(channel !="Data"){

		  if(reweightTurnOn && lepton == "Ele") {
		    if(systUpDown == "BTagTrigSFUp")TurnOn*= (turnOnReWeight+0.08);
		    else if(systUpDown == "BTagTrigSFDown")TurnOn*= (turnOnReWeight-0.08);
		    else TurnOn*= turnOnReWeight;
		  }
		  else if(!reweightTurnOn && lepton == "Ele") {
		    if(systUpDown == "BTagTrigSFUp")TurnOn*= (1.05);
		    else if(systUpDown == "BTagTrigSFDown")TurnOn*= (1.05);
		    //else TurnOn*= turnOnReWeight;
		  }
		  //		  if(reweightTurnOn && lepton == "Ele"){cout <<" turn on before " << TurnOn;TurnOn*= 1.135; cout <<" turn on after " << TurnOn; }
		  //		  if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonEff,lumiB,leptonEffB,systUpDown);
		  if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown,leptonPt,leptonEta);

		}
		
		topMassFloat = topMass;
		costhetaljFloat = costhetalj;
		etaFloat = etaLow;
		
		if(useLL)likelihood =  reader->EvaluateMVA("Likelihood");
		
		//if( (lepton=="Mu" && useMET) && ( leptonRelIso < leptonRelIsoThr))continue;


		if(!(fJetPt > fJetPtCut && bJetPt > fJetPtCut && eta < 5.0 )) continue;
		//		if( lepton == "Mu" && ( leptonRelIso < leptonRelIsoThr))continue;
		//		if( lepton == "Ele" && ( leptonRelIso > leptonRelIsoThrEle))continue;
		//		if( lepton == "Ele" && ( eleID == 0))continue;
		
		if ( useMET && ( ( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) + (bJetEta-leptonEta)*(bJetEta-leptonEta))<0.3) 
				 || ( sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) + (fJetEta-leptonEta)*(fJetEta-leptonEta))<0.3))) continue;
		
		cout << "charge: " << chargeVal << " " << charge  << endl; 
		if(chargeVal>0 && charge == "Plus"){
		  ////cout << " is first histo there? "<<  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge] << endl;
		  ////cout << " first histo integral "<<  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Integral() << endl;
		  
		  HistoCollection["PUWeight"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(PU);
		  HistoCollection["metPt"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  
		  cout << "mtwMass data QCD: " << mtwMass << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    HistoCollection["PUWeight"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		    HistoCollection["PUWeight"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(PU);
		    
		    HistoCollection["mtwMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  else {	
		    HistoCollection["PUWeight"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		    HistoCollection["PUWeight"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(PU);
		    
		    HistoCollection["mtwMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  
		}
			
		if(chargeVal<0 && charge == "Minus"){
		  HistoCollection["PUWeight"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(PU);
		  ////cout << " is first histo there? "<<  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge] << endl;
		  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		  HistoCollection["PUWeight"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(PU);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  else {
		    HistoCollection["PUWeight"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		    HistoCollection["PUWeight"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(PU);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  
		}
		//		//cout << " is first histo there? "<<  HistoCollection["mtwMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge] << endl;


		if ( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) + (bJetEta-leptonEta)*(bJetEta-leptonEta))<0.3 )continue;
		if ( sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) + (fJetEta-leptonEta)*(fJetEta-leptonEta))<0.3 ) continue;
		
		if(chargeVal>0 && charge == "Plus"){
		  HistoCollection["costhetalj"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);

		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(eta,weight);

		  HistoCollection["topMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  HistoCollection["costhetalj"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);

		  //HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		  HistoCollection["topMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  
		  
		  if( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 &&
		      sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 &&
		      cos(leptonPhi - metPhi)<0.8 ){
		    HistoCollection["topMassQCD"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight); ;
		    HistoCollection["topMassQCD"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(topMass,weight); 
		  }
		  
		  HistoCollection["likelihood"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		  HistoCollection["likelihood"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    HistoCollection["costhetalj"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);

		    if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);

		    HistoCollection["topMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    HistoCollection["costhetalj"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);

		    //		    HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    
		    HistoCollection["likelihood"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		  else {
		    HistoCollection["costhetalj"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  //		    HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    HistoCollection["costhetalj"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		    //		    HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    
		    HistoCollection["likelihood"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		  
		}
		if(chargeVal<0 && charge == "Minus"){  
		  HistoCollection["costhetalj"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);

		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  
		  //		  HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  HistoCollection["topMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  HistoCollection["costhetalj"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		  //HistoCollection["eta"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		  HistoCollection["topMass"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  
		  if( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 &&
		      sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 &&
		      cos(leptonPhi - metPhi)<0.8 ){
		    HistoCollection["topMassQCD"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight); 
		    HistoCollection["topMassQCD"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(topMass,weight); 
		  }
		  
		  
		  HistoCollection["likelihood"][channel+"AntiIso"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		  HistoCollection["likelihood"][channel+"AntiIso"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    HistoCollection["costhetalj"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		  
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);

		    HistoCollection["topMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    HistoCollection["costhetalj"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    
		    HistoCollection["likelihood"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		  else {
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  if(sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3) HistoCollection["eta"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);		    //HistoCollection["eta"][channel+"AntiIsoSR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		  HistoCollection["costhetalj"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    HistoCollection["costhetalj"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		    HistoCollection["topMass"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoSR2"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		}
	      }
	      
	      cout << " passed t-sample anti iso"<< " int "<< HistoCollection["costhetalj"][channel+"AntiIso"][systUpDown][lepton]->Integral()<<endl;
	      
	      //Fill Anti Iso WSample Histograms
	      //part for the reader
	      
	      if(!usesNoSystTree){ for(int e = 0; e< nentriesWSampleQCD; ++e){
		  treesWSampleQCD[channel][systUpDownTree][lepton]->GetEntry(e);
		  
		  // double r = rand.Uniform(); 
		  double r = (double)(e)/(double)(nentriesWSampleQCD);
		  r = rand.Uniform(); 
		  string pseudodata = "";
		  if(r<fraction) pseudodata += "Pseudo";
		  
		  //		if(lepton == "Ele") if(eleID==4)continue;		
		  
		  //		  PUWeight=1.053;
		  if(channel !="Data")weight *= bWeight;
		  if( weight == 0 || fabs(weight) > 100) continue;
		  //		  if(costhetalj > 0.99) continue;		
		  //		  if(costhetalj_bJet > 0.99) continue;
		  

		  weight = setWeight( channel+"AntiIsoWSample", systUpDown, lepton, "AntiIsoWSample",LumiC, weight );
		  //weight*= leptonWeight(lepton,leptonEta,channel,systUpDown);
		  
		  //		  if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonEff,lumiB,leptonEffB,systUpDown);
		  if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown,leptonPt,leptonEta);

		  double PU = PUWeight;
		  
		  topMassFloat = topMass;
		  costhetaljFloat = costhetalj;
		  etaFloat = etaLow;
		  if(useLL)likelihood =  reader->EvaluateMVA("Likelihood");
		  
		  /////
		  //		if(lowBTag <= 0) continue;
		  /////
		  
		  if(chargeVal>0 && charge == "Plus"){
		  HistoCollection["PUWeight"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(PU);

		    HistoCollection["mtwMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  
		  if(chargeVal<0 && charge == "Minus"){
		  HistoCollection["PUWeight"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(PU);

		    HistoCollection["mtwMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		    HistoCollection["mtwMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		    HistoCollection["metPt"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		  }
		  
		  if(chargeVal>0 && charge == "Plus"){
		    HistoCollection["costhetalj"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		    HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		    HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaHigh,weight);
		    HistoCollection["topMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    
		    
		    HistoCollection["costhetalj"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		    HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);
		    HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(etaHigh,weight);
		    HistoCollection["topMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    
		    HistoCollection["likelihood"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		  if(chargeVal<0 && charge == "Minus"){  
		    HistoCollection["costhetalj"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		    HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		    HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaHigh,weight);
		    HistoCollection["topMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		    HistoCollection["costhetalj"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		    HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);
		    HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(etaHigh,weight);
		    HistoCollection["topMass"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		    
		    HistoCollection["likelihood"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		    HistoCollection["likelihood"][channel+"AntiIsoWSample"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  }
		}
		
		
		
		double etalowint = HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]->Integral();
		double etahighint = HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]->Integral();
		
		etalowint = HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton]->Integral();
		etahighint = HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton]->Integral();
	      
		
	      	
		HistoCollection["eta"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]->Add(HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]);
		HistoCollection["eta"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]->Add(HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]);
		//	    HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+charge]->Scale(highint/(etalowint+etahighint));
		
		HistoCollection["eta"][channel+"AntiIsoWSample"][systUpDown][lepton]->Add(HistoCollection["etaHigh"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]);
		HistoCollection["eta"][channel+"AntiIsoWSample"][systUpDown][lepton]->Add(HistoCollection["etaLow"][channel+"AntiIsoWSample"][systUpDown][lepton+charge]);
		//	    HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+""]->Scale(highint/(etalowint+etahighint));
	      }	      
	      cout << " passed w-sample anti iso"<< endl;
	      
	      
	    }	

	    //cout << " test et"<<  endl;
	    
	    int nentriesWCut = trees[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50");
	    int nentriesWCutWSample = treesWSample[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50");
	    //	    int nentriesWCutSampleB = treesSampleB[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50");
	    
	    if( lepton == "Ele" ){
	      nentriesWCut = trees[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50 ");
	      nentriesWCutWSample = treesWSample[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50 ");
	      //	      nentriesWCutSampleB = treesSampleB[channel][systUpDownTree][lepton]->GetEntries("mtwMass > 50 && ID ==7");
	    }
	  
	    int nentries = trees[channel][systUpDownTree][lepton]->GetEntries();
	    int nentriesWSample = treesWSample[channel][systUpDownTree][lepton]->GetEntries();
	    int nentries3J2T = trees3J2T[channel][systUpDownTree][lepton]->GetEntries();
	    //	    int nentriesSampleB = treesSampleB[channel][systUpDownTree][lepton]->GetEntries();
	    
	    //cout << " test thet"<<  endl;
	    
	    if (channel == "TChannel" && syst == "noSyst") cout << " nentries "<< nentries<< endl;
	    
	    count =0;
	    
	    //Fill T-Channel Sample Histograms
	    //part for the reader
	    double totweight = 0;
	    if(!usesNoSystTree) for(int e = 0; e< nentries; ++e){
	      trees[channel][systUpDownTree][lepton]->GetEntry(e);
	      
 //yst== "BTagTrig1" || syst == "JetTrig1") &&
		 //		 lepton == "Ele") cout <<"signal syst "<< syst<< " turn on: "<< turnOnWeight<<endl;
	      //if(lepton == "Ele") if(eleID!=7)continue;
	      
	      string pseudodata = "";
	      
	      //		cout << " entry "<< e << " charge "<< charge << " mtwMass "<< mtwMass<< " weight "<< weight << 
	      //	      " set weight " << setWeight( channel, systUpDown, lepton, weight )<<   endl; 


	      double lepEff = leptonEff; 

		double B = bWeight; 
		double TurnOn = turnOnWeight; 
		double PU = PUWeight; 

		if(systUpDown=="PUUp") PU = PUWeightPUUp; 
		if(systUpDown=="PUDown") PU =PUWeightPUDown; 

		if(systUpDown=="BTagUp") B = bWeightBTagUp; 
		if(systUpDown=="BTagDown") B =bWeightBTagDown; 
		if(systUpDown=="MisTagUp") B = bWeightMisTagUp; 
		if(systUpDown=="MisTagDown") B =bWeightMisTagDown; 


		if(systUpDown=="BTagTrig1Up") TurnOn =turnOnWeightBTagTrig1Up; 
		if(systUpDown=="BTagTrig1Down") TurnOn =turnOnWeightBTagTrig1Down; 

		if(systUpDown=="BTagTrig2Up") TurnOn =turnOnWeightBTagTrig2Up; 
		if(systUpDown=="BTagTrig2Down") TurnOn =turnOnWeightBTagTrig2Down; 

		if(systUpDown=="BTagTrig3Up") TurnOn =turnOnWeightBTagTrig3Up; 
		if(systUpDown=="BTagTrig3Down") TurnOn =turnOnWeightBTagTrig3Down; 

		if(systUpDown=="JetTrig1Up") TurnOn =turnOnWeightJetTrig1Up; 
		if(systUpDown=="JetTrig1Down") TurnOn =turnOnWeightJetTrig1Down; 
		if(systUpDown=="JetTrig2Up") TurnOn =turnOnWeightJetTrig2Up; 
		if(systUpDown=="JetTrig2Down") TurnOn =turnOnWeightJetTrig2Down; 
		if(systUpDown=="JetTrig3Up") TurnOn =turnOnWeightJetTrig3Up; 
		if(systUpDown=="JetTrig3Down") TurnOn =turnOnWeightJetTrig3Down; 


		if(channel !="Data")weight *= B;
		if(channel == "TTBar")weight*=PU;
		if(usePUSignal){if(channel == "TbarChannel")weight*=PU;			if(channel == "TChannel")weight*=PU;}
		
		if(channel == "TChannel" || channel == "TbarChannel") eta_SignalTop_Remodel_Mu->Fill(eta,weight*B*lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown));
		if(channel == "TbarChannel") eta_SignalAntiTop_Remodel_Mu->Fill(eta,weight*B*lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown));
		
		if((channel == "TChannel" || channel == "SChannel") && lepton == "Ele" && systUpDown == "EleMisIdUp" ){
		  weight*=0.9907963;
		}
		if((channel == "TbarChannel" || channel == "SbarChannel")&& lepton == "Ele" && systUpDown == "EleMisIdUp" ){
		  weight*=1.017607;
		}

		
		//	      if( !(fJetPt > fJetPtCut && bJetPt > fJetPtCut && fJetRMS < 10.025 )) continue;
		if( !(fJetPt > fJetPtCut && bJetPt > fJetPtCut && eta < 5.0 )) continue;
		// if( !(fJetPt > fJetPtCut && bJetPt > 0 && fJetRMS < fJetRMSCut && bJetRMS <10.025 && fJetRMS > -0.01 && eta < 5.0 )) continue;
		
		//		if (leptonRelIso > 0.06) continue;

		//cout << "w " << weight/(PU*B*leptonEff) << " pu " << PU << " B " << B <<" leptonEff " <<leptonEff << " leptonWeight "<< leptonWeight(lepton,leptonEta,channel,systUpDown) << "totWeight " << weight <<endl;
		if( weight == 0 || fabs(weight) > 100) continue;
		
		weight = setWeight( channel, systUpDown, lepton,"", LumiC, weight );
		if(useDifferentModel){
		  double pdfweight=1.;
		  if(syst == "NNPDF21" && updown == "Up")pdfweight = nnpdfweight;
		  if(syst == "MSTW08" && updown == "Up")pdfweight = mstwweight;
		  weight*=pdfweight;//pdf_weights[p-1];
		}
		if (useSystPDF){
		  //		  cout << " pdf syst " << syst<< " channel "<<channel<< " pdf weight "<<pdfweight<<endl;
		  double pdfweight=1.;
		  for(int p =1;p<=npdfstorun;++p){
		    if (!(p >= MinPDF && p <=MaxPDF))continue;  
		    if(updown=="Up")
		    if(syst == pdf_names[p-1]){
		      pdfweight*=pdf_weights[p-1];
		      weight*=pdfweight;//pdf_weights[p-1];
		    }
		  }
		  //		  cout << " pdf syst after " << syst<< " channel "<<channel<< " pdf weight "<<pdfweight<<endl;

		}

		//	      weight*= leptonWeight(lepton,leptonEta,channel,systUpDown);
		//if(channel == "TChannel" && syst == "noSyst") cout << " entry "<< e << " chargeVal " <<chargeVal<<" charge " << mtwMass << endl;
		if((channel == "TChannel" || channel == "TbarChannel") && syst == "SignalModel"){
		  
		  if(lepton == "Mu"){
		    //cout << "eta mu " << eta<< " bin "<<  SFs_comp_pow_mu.FindBin(eta)<< " content "<< SFs_comp_pow_mu.GetBinContent(SFs_comp_pow_mu.FindBin(eta))<<endl;
		    weight*=SFs_comp_pow_mu.GetBinContent( SFs_comp_pow_mu.FindBin(eta));
		  }
		  if(lepton == "Ele"){
		      //cout << "eta ele " << eta<< " bin "<<  SFs_comp_pow_ele.FindBin(eta)<< " content "<<  SFs_comp_pow_ele.GetBinContent(SFs_comp_pow_ele.FindBin(eta))<<endl;
		      weight*=SFs_comp_pow_ele.GetBinContent( SFs_comp_pow_ele.FindBin(eta));
		    }
		}
		if(channel !="Data"){
		if(reweightTurnOn && lepton == "Ele") {
		    if(systUpDown == "BTagTrigSFUp")TurnOn*= (turnOnReWeight+0.06);
		    else if(systUpDown == "BTagTrigSFDown")TurnOn*= (turnOnReWeight-0.06);
		    else TurnOn*= turnOnReWeight;
		}
		else if(!reweightTurnOn && lepton == "Ele") {
		  if(systUpDown == "BTagTrigSFUp")TurnOn*= (1.05);
		  else if(systUpDown == "BTagTrigSFDown")TurnOn*= (1.05);
		  //else TurnOn*= turnOnReWeight;
		}

		//		if(reweightTurnOn && lepton == "Ele"){cout <<" turn on before " << TurnOn;TurnOn*= 1.135; cout <<" turn on after " << TurnOn;}
		//		if(reweightTurnOn && lepton == "Ele")TurnOn*= 1.135;
		if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown,leptonPt,leptonEta);
		}
	      
	      topMassFloat = topMass;
	      costhetaljFloat = costhetalj;
	      etaFloat = eta;
	      if(useLL)likelihood =  reader->EvaluateMVA("Likelihood");
	      
	      	      if(chargeVal>0 && charge == "Plus"){
		HistoCollection["mtwMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		HistoCollection["mtwMass"][channel][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		HistoCollection["metPt"][channel][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		HistoCollection["metPt"][channel][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		
		if(topMass > topMassLowCut && topMass < topMassHighCut){
		  HistoCollection["mtwMass"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
		else {
		  HistoCollection["mtwMass"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
	      }
	      
	      if(chargeVal<0 && charge == "Minus"){
		HistoCollection["mtwMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		HistoCollection["mtwMass"][channel][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		HistoCollection["metPt"][channel][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		HistoCollection["metPt"][channel][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		
		if(topMass > topMassLowCut && topMass < topMassHighCut){
		  HistoCollection["mtwMass"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
		else {
		  HistoCollection["mtwMass"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["mtwMass"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
	      }
	    
	      if(useMET){
		if(channel == "WJets" && enlargeSample){
		  ;
		}
		else{
		  if(lepton == "Mu") if(metPt < metCut)continue;
		  if(lepton == "Ele") if(metPt < metCut)continue;
		}
	      }
	      else{
		if(channel == "WJets" && enlargeSample){
		  ;
		}
		else{
		  if(lepton == "Mu") if(mtwMass < mtwCut)continue;
		  if(lepton == "Ele") if(mtwMass < mtwCutEle)continue;
		}
	      }
	      double extraW = 1.;
	    
	      //	      if(lepton == ele"sampl")
	      //if(topMass < minobs["topMass"] || )continue;
	      
	      double r = (double)(count)/(double)(nentriesWCut);
	      r = rand.Uniform(); 
	      if(r<fraction) pseudodata += "Pseudo";
	      ++count;
	      
	      if(channel == "TChannel" && syst == "noSyst") ;//cout << " entry "<< e << " count "<< count << " nentries " <<nentries<< " r "<< r << " fraction " << fraction  <<" chargeVal " <<chargeVal << " suffix  " << pseudodata << endl;
	      
	      if(chargeVal>0 && charge == "Plus"){
		if(channel == "Data" && syst == "noSyst"){
		  ;//Histo2DCollection["etaTopMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,topMass,weight);
		  //Histo2DCollection["etaTopMass"][channel][systUpDown][lepton+pseudodata]->Fill(eta,topMass,weight);
		  
		  Histo2DCollection["etaCosthetalj"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,costhetalj,weight);
		  Histo2DCollection["etaCosthetalj"][channel][systUpDown][lepton+pseudodata]->Fill(eta,costhetalj,weight);
		}
		
		HistoCollection["PUWeight"][channel][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		HistoCollection["PUWeight"][channel][systUpDown][lepton+pseudodata]->Fill(PU);


		HistoCollection["costhetalj"][channel][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		HistoCollection["eta"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		HistoCollection["topMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		HistoCollection["costhetalj"][channel][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		HistoCollection["eta"][channel][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		HistoCollection["topMass"][channel][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		
		
		if( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 &&
		    sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 &&
		    cos(leptonPhi - metPhi)<0.8 ){
		  HistoCollection["topMassQCD"][channel][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight); ;
		  HistoCollection["topMassQCD"][channel][systUpDown][lepton+pseudodata]->Fill(topMass,weight); 
		}
		
		HistoCollection["likelihood"][channel+""][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		HistoCollection["likelihood"][channel+""][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		
		if(topMass > topMassLowCut && topMass < topMassHighCut){
		  //		  if(channel == "WJets" && enlargeSample){
		  //  extraW = 0.648;
		  //}

		  HistoCollection["PUWeight"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(PU);
	

		  HistoCollection["costhetalj"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight*extraW);
		  HistoCollection["costhetalj"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(topMass,weight*extraW);
		  
		  HistoCollection["likelihood"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight*extraW);
		  HistoCollection["likelihood"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight*extraW);
		}
		else {
		  //		  if(channel == "WJets" && enlargeSample){
		  //  extraW = 0.530;
		  // }

		  HistoCollection["PUWeight"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(PU);

		  HistoCollection["costhetalj"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight*extraW);
		  HistoCollection["costhetalj"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(topMass,weight*extraW);
		  
		  HistoCollection["likelihood"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight*extraW);
		  HistoCollection["likelihood"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight*extraW);
		}
	      
		if(channel == "WJets" && syst == "noSyst" && lepton == leptonCase){
		  //cout << "data lookhere entry "<< e << " lepton " << lepton << " etaHigh "<< etaHigh<< " etaLow "<< etaLow << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if (eventFlavour == 3)  eta_WJets_wbbSR1_noSyst->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR1_noSyst->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR1_noSyst->Fill(eta,weight);
		  }
		  else {
		    if (eventFlavour == 3)  eta_WJets_wbbSR2_noSyst->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR2_noSyst->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR2_noSyst->Fill(eta,weight);
		  }

		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if (eventFlavour == 3)  eta_WJets_wbbSR1_noSyst_Plus->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR1_noSyst_Plus->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR1_noSyst_Plus->Fill(eta,weight);
		  }
		  else {
		    if (eventFlavour == 3)  eta_WJets_wbbSR2_noSyst_Plus->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR2_noSyst_Plus->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR2_noSyst_Plus->Fill(eta,weight);
		  }
		}//\wjets

	      }
	     
 
	      if(chargeVal<0 && charge == "Minus"){
		if(channel == "Data" && syst == "noSyst"){
		  
		  Histo2DCollection["etaCosthetalj"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,costhetalj,weight);
		  Histo2DCollection["etaCosthetalj"][channel][systUpDown][lepton+pseudodata]->Fill(eta,costhetalj,weight);
		  //Histo2DCollection["etaTopMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,topMass,weight);
		  //Histo2DCollection["etaTopMass"][channel][systUpDown][lepton+pseudodata]->Fill(eta,topMass,weight);
		}
		
		
		if(topMass > topMassLowCut && topMass < topMassHighCut){
		  HistoCollection["PUWeight"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(PU);

		  HistoCollection["costhetalj"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight*extraW);
		  HistoCollection["costhetalj"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(topMass,weight*extraW);
		  
		  HistoCollection["likelihood"][channel+"SR1"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight*extraW);
		  HistoCollection["likelihood"][channel+"SR1"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight*extraW);
		}
		else {

		  HistoCollection["PUWeight"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(PU);

		  HistoCollection["costhetalj"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight*extraW);
		  HistoCollection["costhetalj"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight*extraW);
		  HistoCollection["eta"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(eta,weight*extraW);
		  HistoCollection["topMass"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(topMass,weight*extraW);
		  
		  HistoCollection["likelihood"][channel+"SR2"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight*extraW);
		  HistoCollection["likelihood"][channel+"SR2"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight*extraW);
		}
		
		HistoCollection["PUWeight"][channel][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		HistoCollection["PUWeight"][channel][systUpDown][lepton+pseudodata]->Fill(PU);

		HistoCollection["costhetalj"][channel][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		HistoCollection["eta"][channel][systUpDown][lepton+pseudodata+charge]->Fill(eta,weight);
		HistoCollection["topMass"][channel][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		HistoCollection["costhetalj"][channel][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		HistoCollection["eta"][channel][systUpDown][lepton+pseudodata]->Fill(eta,weight);
		HistoCollection["topMass"][channel][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		
		if( sqrt((bJetPhi-leptonPhi)*(bJetPhi-leptonPhi) +(bJetEta-leptonEta)*(bJetEta-leptonEta))>0.3 &&
		    sqrt((fJetPhi-leptonPhi)*(fJetPhi-leptonPhi) +(fJetEta-leptonEta)*(fJetEta-leptonEta))>0.3 &&
		    cos(leptonPhi - metPhi)<0.8 ){
		  HistoCollection["topMassQCD"][channel][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight); ;
		  HistoCollection["topMassQCD"][channel][systUpDown][lepton+pseudodata]->Fill(topMass,weight); 
		}
		
		

		HistoCollection["likelihood"][channel+""][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		HistoCollection["likelihood"][channel+""][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		
		if(channel == "WJets" && syst == "noSyst" && lepton == leptonCase){
		  //cout << "data lookhere entry "<< e << " lepton " << lepton << " etaHigh "<< etaHigh<< " etaLow "<< etaLow << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if (eventFlavour == 3)  eta_WJets_wbbSR1_noSyst->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR1_noSyst->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR1_noSyst->Fill(eta,weight);
		  }
		  else {
		    if (eventFlavour == 3)  eta_WJets_wbbSR2_noSyst->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR2_noSyst->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR2_noSyst->Fill(eta,weight);
		  }

		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if (eventFlavour == 3)  eta_WJets_wbbSR1_noSyst_Minus->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR1_noSyst_Minus->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR1_noSyst_Minus->Fill(eta,weight);
		  }
		  else {
		    if (eventFlavour == 3)  eta_WJets_wbbSR2_noSyst_Minus->Fill(eta,weight);
		    if (eventFlavour == 2)  eta_WJets_wccSR2_noSyst_Minus->Fill(eta,weight);
		    if (eventFlavour == 1)  eta_WJets_wlightSR2_noSyst_Minus->Fill(eta,weight);
		  }
		}//\wjets
		
	      }
	    }
	    
	    cout << " passed t-sample "<< endl;
	    
	    count =0;
	    
	    //Fill W Sample Histograms
	    if(!usesNoSystTree){ for(int e = 0; e< nentriesWSample; ++e){
		treesWSample[channel][systUpDownTree][lepton]->GetEntry(e);
		
		string pseudodata = "";
		if(channel !="Data")weight *= bWeight;
		
		double PU = PUWeight;

		if( weight == 0 || fabs(weight) > 100) continue;

		weight = setWeight( channel, systUpDown, lepton,"WSample", LumiC, weight );
		//		weight*= leptonWeight(lepton,leptonEta,channel,systUpDown);
		
		if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown,leptonPt,leptonEta);
		
		if( !(fJetPt > fJetPtCut && bJetPt > fJetPtCut && eta < 5.0)) continue;
		
		topMassFloat = topMass;
		costhetaljFloat = costhetalj;
		etaFloat = etaLow;
		if(useLL)likelihood =  reader->EvaluateMVA("Likelihood");
		
		if(chargeVal>0 && charge == "Plus"){
		  HistoCollection["mtwMass"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["mtwMass"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["metPt"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
		if(chargeVal<0 && charge == "Minus"){
		  HistoCollection["mtwMass"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(mtwMass,weight);
		  HistoCollection["mtwMass"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(mtwMass,weight);
		  HistoCollection["metPt"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(metPt,weight);
		  HistoCollection["metPt"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(metPt,weight);
		}
		
		if(useMET){
		  if(lepton == "Mu") if(metPt < metCut)continue;
		  if(lepton == "Ele") if(metPt < metCut)continue;
		}
		else{
		  if(lepton == "Mu") if(mtwMass < mtwCut)continue;
		  if(lepton == "Ele") if(mtwMass < mtwCutEle)continue;
		}
		
		//double r = rand.Uniform(); 
		double r = (double)(count)/(double)(nentriesWCutWSample);
		r = rand.Uniform(); 
		if(r<fraction) pseudodata += "Pseudo";
		++count;
		
		if(chargeVal>0 && charge == "Plus"){
		  HistoCollection["PUWeight"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(PU);

		  HistoCollection["costhetalj"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		  HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		  HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaHigh,weight);

		  HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		  HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);

		  if((lowBTag > 0))HistoCollection["topMass"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  HistoCollection["topMassWS"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  
		  HistoCollection["costhetalj"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		  HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);
		  HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaHigh,weight);
		  if((lowBTag > 0))HistoCollection["topMass"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  HistoCollection["topMassWS"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  
		  HistoCollection["likelihood"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		  HistoCollection["likelihood"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		  
		}
		if(chargeVal<0 && charge == "Minus"){  
		  HistoCollection["PUWeight"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(PU);
		  HistoCollection["PUWeight"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(PU);

		  HistoCollection["costhetalj"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(costhetalj,weight);
		  
		  HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		  HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);
		  
		  HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaLow,weight);
		  HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(etaHigh,weight);
		  if((lowBTag > 0))HistoCollection["topMass"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  HistoCollection["topMassWS"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(topMass,weight);
		  
		  HistoCollection["costhetalj"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(costhetalj,weight);
		  HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaLow,weight);
		  HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(etaHigh,weight);
		  if((lowBTag > 0))HistoCollection["topMass"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  HistoCollection["topMassWS"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(topMass,weight);
		  
		  HistoCollection["likelihood"][channel+"WSample"][systUpDown][lepton+pseudodata+charge]->Fill(likelihood,weight);
		  HistoCollection["likelihood"][channel+"WSample"][systUpDown][lepton+pseudodata]->Fill(likelihood,weight);
		}
	      


		if(channel == "Data" && syst == "noSyst"){
		  //cout << "data lookhere entry "<< e << " lepton " << lepton << " etaHigh "<< etaHigh<< " etaLow "<< etaLow << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if(lepton == "Mu")eta_Data_FitWSampleSR1_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_Data_FitWSampleSR1_noSyst_Mu->Fill(fabs(etaHigh));

		    if(lepton == "Ele")eta_Data_FitWSampleSR1_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_Data_FitWSampleSR1_noSyst_Ele->Fill(fabs(etaHigh));

		  }
		  else {
		    if(lepton == "Mu")eta_Data_FitWSampleSR2_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_Data_FitWSampleSR2_noSyst_Mu->Fill(fabs(etaHigh));

		    if(lepton == "Ele")eta_Data_FitWSampleSR2_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_Data_FitWSampleSR2_noSyst_Ele->Fill(fabs(etaHigh));

		  }
		}


		if(channel == "WJets" && syst == "noSyst"){
		  //cout << "data lookhere entry "<< e << " lepton " << lepton << " etaHigh "<< etaHigh<< " etaLow "<< etaLow << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if(lepton == "Mu")eta_WJets_wbbWSampleSR1_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_WJets_wbbWSampleSR1_noSyst_Mu->Fill(fabs(etaHigh));
		    if(lepton == "Ele")eta_WJets_wbbWSampleSR1_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_WJets_wbbWSampleSR1_noSyst_Ele->Fill(fabs(etaHigh));
		  }
		  else {
		    if(lepton == "Mu")eta_WJets_wbbWSampleSR2_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_WJets_wbbWSampleSR2_noSyst_Mu->Fill(fabs(etaHigh));
		    if(lepton == "Ele")eta_WJets_wbbWSampleSR2_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_WJets_wbbWSampleSR2_noSyst_Ele->Fill(fabs(etaHigh));
		  }
		}
		
		
		if(channel == "WJets_wcc" && syst == "noSyst"){
		  //cout << "data lookhere entry "<< e << " lepton " << lepton << " etaHigh "<< etaHigh<< " etaLow "<< etaLow << endl;
		  if(topMass > topMassLowCut && topMass < topMassHighCut){
		    if(lepton == "Mu")eta_WJets_wccWSampleSR1_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_WJets_wccWSampleSR1_noSyst_Mu->Fill(fabs(etaHigh));
		    if(lepton == "Ele")eta_WJets_wccWSampleSR1_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_WJets_wccWSampleSR1_noSyst_Ele->Fill(fabs(etaHigh));
		  }
		  else {
		    if(lepton == "Mu")eta_WJets_wccWSampleSR2_noSyst_Mu->Fill(fabs(etaLow));
		    if(lepton == "Mu")eta_WJets_wccWSampleSR2_noSyst_Mu->Fill(fabs(etaHigh));
		    if(lepton == "Ele")eta_WJets_wccWSampleSR2_noSyst_Ele->Fill(fabs(etaLow));
		    if(lepton == "Ele")eta_WJets_wccWSampleSR2_noSyst_Ele->Fill(fabs(etaHigh));
		  }
		}
		

		
	      }
	      
	      
	      double etalowint = HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+charge]->Integral();
	      double etahighint = HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+charge]->Integral();
	      
	      etalowint = HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton]->Integral();
	      etahighint = HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton]->Integral();
	      
	      //	      HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+charge]->Add(HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+charge]);
	      // HistoCollection["eta"][channel+"WSample"][systUpDown][lepton+charge]->Add(HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+charge]);
	      //HistoCollection["eta"][channel+"WSample"][systUpDown][lepton]->Add(HistoCollection["etaHigh"][channel+"WSample"][systUpDown][lepton+charge]);
	      //HistoCollection["eta"][channel+"WSample"][systUpDown][lepton]->Add(HistoCollection["etaLow"][channel+"WSample"][systUpDown][lepton+charge]);
	    }
	    //	    HistoCollection["eta"][channel+"WSample"][systUpDown][lepton]->Scale(highint/(etalowint+etahighint));
	    cout << " passed w-sample "<< endl;
	  
	    //Fill W Sample Histograms
	    if(!usesNoSystTree){ for(int e = 0; e< nentries3J2T; ++e){
		trees3J2T[channel][systUpDownTree][lepton]->GetEntry(e);
	

		string pseudodata = "";
		if(channel !="Data")weight *= bWeight;
		
		double PU = PUWeight;
		
		if( weight == 0 || fabs(weight) > 100) continue;

		weight = setWeight( channel, systUpDown, lepton,"3J2T", LumiC, weight );
		//		weight*= leptonWeight(lepton,leptonEta,channel,systUpDown);
	
		if(channel == "TTBar")weight*=PU;

		if(channel !="Data")weight *= lumiFormula(lepton,lumiA,leptonSF,lumiB,leptonSFB,lumiC,leptonSFC,lumiD,leptonSFD,systUpDown,leptonPt,leptonEta);
		
		//		if( !(secondJetPt > fJetPtCut && eta < 5.0)) continue;
		//		if( !(fJetPt > fJetPtCut && fJetRMS < fJetRMSCut && bJetRMS <10.025 && fJetRMS > -0.01 && eta < 5.0)) continue;

		if(useMET){
		  if(lepton == "Mu") if(metPt < metCut)continue;
		  if(lepton == "Ele") if(metPt < metCut)continue;
		}
		else{
		  if(lepton == "Mu") if(mtwMass < mtwCut)continue;
		  if(lepton == "Ele") if(mtwMass < mtwCutEle)continue;
		}
		
		if(topMass > topMassLowCut && topMass < topMassHighCut){
		  if(syst == "noSyst" && channel == "TTBar") ;//cout << " tt sample SR1, entry "<< e<< " eta "<< eta<< " weight "<< weight << " PUWeight "<<PUWeight <<endl;
		  if((chargeVal > 0 && charge == "Plus") || (chargeVal < 0 && charge == "Minus") ){
		    HistoCollection["eta"][channel+"3J2TSR1"][systUpDown][lepton]->Fill(eta,weight);
		    HistoCollection["PUWeight"][channel+"3J2TSR1"][systUpDown][lepton]->Fill(PU);
		    
		    HistoCollection["eta"][channel+"3J2TSR1"][systUpDown][lepton+charge]->Fill(eta,weight);
		    HistoCollection["PUWeight"][channel+"3J2TSR1"][systUpDown][lepton+charge]->Fill(PU);
		  }
		  
		}
		else{
		  if( (chargeVal > 0 && charge == "Plus") || (chargeVal < 0 && charge == "Minus") ){
		  
		    HistoCollection["eta"][channel+"3J2TSR2"][systUpDown][lepton]->Fill(eta,weight);
		    HistoCollection["PUWeight"][channel+"3J2TSR2"][systUpDown][lepton]->Fill(PU);

		    HistoCollection["eta"][channel+"3J2TSR2"][systUpDown][lepton+charge]->Fill(eta,weight);
		    HistoCollection["PUWeight"][channel+"3J2TSR2"][systUpDown][lepton+charge]->Fill(PU);
		  
		  }
		}
	      }
	    }
	    cout << " passed tt-sample "<< endl;
	    
	    count =0;
	    
	    if(usesNoSystTree){
	      for(size_t s=0; s<samples.size();++s){
		string sample= samples.at(s);
		for(size_t o=0; o<observables.size();++o){
		  string observable = observables.at(o);
		  if((observable == "etaTUp" || observable == "etaTDown" || 
		      observable == "etaTTUp" || observable == "etaTTDown" 
		      ) && (sample != "SR1" && sample != "SR2" ))continue;
		  if(observable == "topMassQCD" && !(sample == "" || sample == "AntiIso") ) continue;
		  HistoCollection[observable][channel+sample][systUpDown][lepton+"Plus"]->Add(HistoCollection[observable][channel+sample]["noSyst"][lepton+"Plus"],0.5);
		  HistoCollection[observable][channel+sample][systUpDown][lepton+"Minus"]->Add(HistoCollection[observable][channel+sample]["noSyst"][lepton+"Minus"],0.5);
		  HistoCollection[observable][channel+sample][systUpDown][lepton]->Add(HistoCollection[observable][channel+sample]["noSyst"][lepton],0.5);
		  //cout<< " test 7"<<endl;
		}
	      }
	    }
	  }
	}
      }
    f.Close();
    }
  }
  

  //LOOP 3.25 FIX Data Control Samples NORMALIZATION
  
  for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
    continue;
    string sample = (*it_sam);
    for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
      
      string observable = (*it_o);
      if (observable == "etaTopMass" || observable == "etaCosthetalj")continue;
      for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
	string syst = (*it_s);
	int n_syst_extremes=2;
	if(syst == "noSyst")n_syst_extremes=1; 
	for (int ud = 0;ud<n_syst_extremes;++ud){
	  string updown = UpDown[ud];
	  if(syst =="noSyst")updown ="";
	  string systUpDown = syst + updown;
	  
	  std::string  chargesAll[3] = {"","Plus","Minus"};
	  for (int cha = 0; cha < 3; ++cha){
	    string charge = chargesAll[cha];
	    double denEle = HistoCollection[observable]["DataEleQCD"+sample][systUpDown]["Ele"+charge]->Integral();
	    double denMu = HistoCollection[observable]["DataMuQCD"+sample][systUpDown]["Mu"+charge]->Integral();

	    double numEle = HistoCollection[observable]["DataEleQCD"+sample][systUpDown]["Ele"+charge]->Integral();
	    double numMu = HistoCollection[observable]["DataMuQCD"+sample][systUpDown]["Mu"+charge]->Integral();
	    
	    if(denEle!=0) HistoCollection[observable]["DataEleQCD"+sample][systUpDown]["Ele"+charge]->Scale(numEle/denEle);
	    if(denMu!=0) HistoCollection[observable]["DataMuQCD"+sample][systUpDown]["Mu"+charge]->Scale(numMu/denMu);
	  }	
	}
      }
    }
  }

  //LOOP 4  
  //Loop for the Data Driven QCD:
  //Loop on the samples
  for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
    string sample = (*it_sam);
    if(sample == "SampleB")cout << " debug " << sample<<endl;
    if(sample == "AntiIso" || sample == "AntiIsoWSample" || sample == "AntiIsoSampleB" 
       || sample == "AntiIsoSR1" || sample == "AntiIsoSR2" 
       || sample == "AntiIsoESB" )continue;
    if(sample =="3J2TSR1" || sample == "3J2TSR2") continue;
    
    for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
      string syst = (*it_s);
      if(sample == "SampleB")cout << " debug " << syst<<endl;
      //if (syst != "noSyst") continue;
      int n_syst_extremes=2;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	string systUpDown = syst + updown;
	if(sample == "SampleB")cout << " debug " << systUpDown<<endl;
	for (int lep = 0; lep <2;++lep){
	  string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	  if(sample == "SampleB")cout << " debug " << lepton <<endl;
	  //Take the qcd histogram
	  double qcdfraction=1.;


	  //bool isEleControl = ((sample == "WSample" ) && lepton == "Ele" );
	  bool isEleControl = ((sample == "WSample" || sample == "SampleB" ) && lepton == "Ele" );

	  string DataChannelToFit ="Data";
	  string DataChannelForModelFit ="Data";
	  //	  if(isEleControl)DataChannelToFit = "DataEleControl";
	  
	  //	  if(sample == "SampleB")cout << "sssstest" +syst + sample+lepton  << " integral dataantiiso "<< HistoCollection["mtwMass"][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton]->Integral()<< " integral histo "<< HistoCollection["mtwMass"][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton]->Integral()<< endl;
	  
	  //if(sample == "WSample" && lepton == "Ele"){
	  //  HistoCollection["mtwMass"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["mtwMass"]["DataEleQCDAntiIso"+sample]["noSyst"][lepton]);
	  //  HistoCollection["metPt"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["metPt"]["DataEleQCDAntiIso"+sample]["noSyst"][lepton]);
	  //}
	  //else {
	  
	  //	  if( lepton == "Mu" ) DataChannelForModelFit = "DataMuControl";
	  
	  HistoCollection["mtwMass"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["mtwMass"][DataChannelForModelFit+"AntiIso"+sample]["noSyst"][lepton]);
	  
	  //	  if( sample == "" && lepton == "Ele") HistoCollection["metPt"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["metPt"]["DataEleControlAntiIso"+sample]["noSyst"][lepton]);
	  // else
	  HistoCollection["metPt"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["metPt"][DataChannelForModelFit+"AntiIso"+sample]["noSyst"][lepton]);
	    //}
	  
	    if(sample == "SampleB")cout << "sssstest" +syst + sample+lepton  << " integral dataantiiso "<< HistoCollection["mtwMass"][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton]->Integral()<< " integral histoafter "<< HistoCollection["mtwMass"][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton]->Integral()<< endl;
	    
	    //Not necessary anymore
	    // if(sample == "WSample"){
	    //	    if(lepton == "Mu"){
	    //  HistoCollection["mtwMass"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["mtwMass"]["WJetsAntiIsoWSample"]["noSyst"][lepton],-1);
	    //  HistoCollection["metPt"]["QCD"+sample]["noSyst"][lepton]->Add(HistoCollection["metPt"]["WJetsAntiIsoWSample"]["noSyst"][lepton],-1);
	    //}
	  
	  string fitVariableName = "mtwMass";
	  if(useMET)fitVariableName= "metPt";
	  // if(lepton == "Mu" && useMET)fitVariableName= "metPt";
	  // if(lepton == "Ele" && sample == "")fitVariableName= "mtwMass";
	
	  //Define fit sig bkg

	  string mtwname = "signal_mtw_sum_"+sample+"_"+"noSyst"+"_"+lepton;
	  TH1D * WJetsSum = new TH1D( (mtwname+"wjets").c_str(), (mtwname+"wjets").c_str(), nbins[fitVariableName], minobs[fitVariableName], maxobs[fitVariableName] );
	  TH1D * SignalSum = new TH1D( mtwname.c_str(), mtwname.c_str(), nbins[fitVariableName], minobs[fitVariableName], maxobs[fitVariableName] );
	  TH1D * QCDBackground = new TH1D ((mtwname+"b_h").c_str(),(mtwname+"b_h").c_str(),nbins[fitVariableName], minobs[fitVariableName], maxobs[fitVariableName]);
	  
	  
	  //Take the mc/data channels
	  for(std::vector<string>::const_iterator it = channels.begin(); it != channels.end(); ++it){
	    string channel = (*it);
	    //Do the sum WSample
	    //	    
	    
	    bool isControlSample = (channel == "DataEleQCD" || channel == "DataMuQCD" || channel == "DataEleControl");
	    bool isSysts = channel == "TChannel_Q2Up" || 
	      channel == "TbarChannel_Q2Up" || 
	      channel == "TChannel_Q2Down" ||
	      channel == "TbarChannel_Q2Down" || 
	      channel == "TTBar_Q2Down" || 
	      channel == "TTBar_Q2Up" || 
	      channel == "TTBar_MatchingDown" || 
	      channel == "TTBar_MatchingUp" || 
	      //	      "SChannel_Q2Down" || 
	      //	      "SbarChannel_Q2Down" || 
	      //	      "SChannel_Q2Up" || 
	      //	      "SbarChannel_Q2Up"   ||
	      channel == "TWChannel_Q2Down" || 
	      channel == "TbarWChannel_Q2Down" || 
	      channel == "TWChannel_Q2Up" || 
	      channel == "TbarWChannel_Q2Up" ;
	    isSysts =false; 
	    bool isSyst = isSysts;
	    if (isControlSample)continue;
	    if  (channel == "QCDMu" || channel == "QCDEle") continue; 
	    
	    cout <<" channel mtwsum " << channel+sample <<" integral ith "<<HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]->Integral()<<endl;
	    
	    if(sample == "WSample"){
	      if( channel != "Data" && channel != "WJets" && !isSysts )
		SignalSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);
	      if( channel == "WJets" )
		WJetsSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);
	    
	    }
	    
	    if(sample == "SR1" || sample == "SR2" && !isSysts){
	      if(channel != "Data_Fit" && channel != "Data" && channel != "WJets_wlight"
              && channel != "Wc_wc" && channel != "WHF_c" && channel != "WHF" && channel != "WHF_b"  && channel != "WLight" && ! isSyst
		 && channel != "Wc_wc" && channel != "WLight" && !isSyst )
		SignalSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);
				
	      if(channel == "WJets")
		WJetsSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);

	    
	    }
	    
	    
	    if(sample == "" &&!isSysts){
	      if(channel != "Data_Fit" && channel != "Data" && channel != "WJets_wlight"
		 && channel != "Wc_wc" && channel != "WHF_c" && channel != "WHF" && channel != "WHF_b"  && channel != "WLight" && ! isSyst
		 && channel != "Wc_wc" && channel != "WLight" && !isSyst )
		SignalSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);
	      
	      if(channel == "WJets")
		WJetsSum->Add(HistoCollection[fitVariableName][channel+sample]["noSyst"][lepton]);

	    }
	    //               && channel != "WJets_wcc" && channel != "Vqq_wcc" 
	    cout <<"after channel mtwsum " << channel+sample <<" integral tot "<<SignalSum->Integral()<< "   WJets: " << WJetsSum->Integral() <<  endl;
	  }
	  //
	
	  //End sum 
	  
	  //Do the fit
	
	  //Parameters
	  RooRealVar * MTWSignalYield = new RooRealVar(("SignalMTWYield"+lepton).c_str(),("SignalMTWYield"+lepton).c_str(),
						       SignalSum->Integral(),0.5*SignalSum->Integral(),
						       SignalSum->Integral()*1.5);
	  RooRealVar * MTWWJetsYield = new RooRealVar(("WJetsMTWYield"+lepton).c_str(),("WJetsMTWYield"+lepton).c_str(),
						       HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton]->Integral()*0.5,0,
						       HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton]->Integral()*10);
	  RooRealVar *MTWQCDYield = new RooRealVar(("QCDMTWYield"+lepton).c_str(),("QCDMTWYield"+lepton).c_str(),
						   100,0,1000);
	  //						   HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton]->Integral()*10);

	  cout << "histopdf 1 "<< HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton] << 
	       " name 2 " << HistoCollection[fitVariableName]["QCD"+sample]["noSyst"][lepton] << endl;
	  
	  //Data
	  string namedata = "mtw_data_hist"+sample+"_"+"noSyst"+"_"+lepton;
	  RooDataHist * Data = new RooDataHist((namedata).c_str(),(namedata).c_str(),RooArgList(MTWMass),
					       HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton]);  

	  //Signal
	  RooDataHist * Signal = new RooDataHist((mtwname+"_signal_h").c_str(),(mtwname+"_signal_h").c_str(),RooArgList(MTWMass),
						 SignalSum);  
	  RooHistPdf *S = new RooHistPdf((mtwname+"_signal_pdf").c_str(),(mtwname+"_signal_pdf").c_str(),RooArgList(MTWMass),
					 *Signal);  

	  //WJets
	  RooDataHist * WJets = new RooDataHist((mtwname+"_wjets_h").c_str(),(mtwname+"_wjets_h").c_str(),RooArgList(MTWMass),
						 WJetsSum);  
	  RooHistPdf *W = new RooHistPdf((mtwname+"_wjets_pdf").c_str(),(mtwname+"_wjets_pdf").c_str(),RooArgList(MTWMass),
					 *WJets);  

	  
	  //QCD
	  
	  QCDBackground->Add(HistoCollection[fitVariableName]["QCD"+sample]["noSyst"][lepton]);  
	  //if(lepton == "Mu")QCDBackground->Add(HistoCollection[fitVariableName]["QCDMu"+sample]["noSyst"][lepton]);  
	  //if(lepton == "Ele")QCDBackground->Add(HistoCollection[fitVariableName]["QCDEle"+sample]["noSyst"][lepton]);  

	  //	  QCDBackground->Smooth(4);
	  RooDataHist * QCD = new RooDataHist((mtwname+"_qcd_h").c_str(),(mtwname+"_qcd_h").c_str(),RooArgList(MTWMass),
					      QCDBackground);
					      //     HistoCollection[fitVariableName]["QCD"+sample]["noSyst"][lepton]);  
	  
	  RooHistPdf * B = new RooHistPdf ((mtwname+"_qcd_pdf").c_str(),(mtwname+"_qcd_pdf").c_str(),RooArgList(MTWMass),
					    *QCD);
	  //Fit function
	  RooAddPdf * mtwFitFunction = new RooAddPdf((mtwname+"_fit_pdf").c_str() ,
						     (mtwname+"_fit_pdf").c_str() ,
						     RooArgList(*S,*B),
						     RooArgList(*MTWSignalYield,*MTWQCDYield)); 
	  cout <<"integral signal just before fit " << sample <<" integral tot "<<SignalSum->Integral()<<endl;
	  cout <<"integral wjets just before fit " << sample <<" integral tot "<<WJetsSum->Integral()<<endl;
	  cout <<"integral qcd just before fit " << sample <<" integral qcd "<<QCDBackground->Integral()<<endl;

	  //	  SignalSum->Scale(1);

	  // Construct a Gaussian constraint p.d.f 
	  RooGaussian fconstext("fconstext","fconstext",*MTWSignalYield,RooConst(SignalSum->Integral()),RooConst(SignalSum->Integral()/1.)) ;

	  // Multiply constraint with p.d.f
	  RooProdPdf model("model","model with constraint",RooArgSet(*mtwFitFunction,fconstext)) ;
  
	  // Fit modelc with constraint term on parameter f
          if (sample == ""){
	    RooFitResult* r = model.fitTo(*Data,Constrain(*MTWSignalYield),Save()) ;
	    cout << "HERE PRINT RESULTS WITH GAUSSIAN CONSTRAINT" << endl;
	    r->Print("v");	    
	  }
	    
	  /*	  
	  // Fit with external constraint
	  if (sample == ""){
	    RooFitResult* r;
	    r = mtwFitFunction->fitTo(*Data,ExternalConstraints(fconstext),Save());
	    cout << "HERE PRINT RESULTS WITH GAUSSIAN CONSTRAINT" << endl;
	    r->Print("v");	    
	  }
	  */

	  //if (sample == "")
	  //  mtwFitFunction->fitTo(*Data,Strategy(2),Minos(kTRUE));
	
	  double fitAfterThreshold = NormalizedIntegral(B, MTWMass, mtwCut, 0) ;
	  if(lepton == "Ele") fitAfterThreshold = NormalizedIntegral(B, MTWMass, metCut, 0) ;
	  if(lepton == "Ele" && fitVariableName == "mtwMass") fitAfterThreshold = NormalizedIntegral(B, MTWMass, mtwCutEle, 0) ;
	  if(lepton == "Mu" && fitVariableName == "metPt") fitAfterThreshold = NormalizedIntegral(B, MTWMass, metCut, 0) ;
	  //	  if(fitVariableName == "metPt" ) fitAfterThreshold = NormalizedIntegral(B, MTWMass, metCut, 0) ;
	  qcdfraction = fitAfterThreshold*MTWQCDYield->getVal();
	  double totalQCDRatioAfterThreshold = qcdfraction/HistoCollection[fitVariableName][DataChannelToFit+sample]["noSyst"][lepton]->Integral();
	  
	  cout << " hey fit to sample " << sample << " lepton "<< lepton << " lookhere val "<< MTWQCDYield->getVal()<<" signal "<<  MTWSignalYield->getVal() << "  wjets " << MTWWJetsYield->getVal() << " fraction " <<qcdfraction<< " error "<< fitAfterThreshold*MTWQCDYield->getError() <<endl;
	  
	  if(syst== "noSyst"){
	    RooPlot* fractionFrame = MTWMass.frame(Bins(nbins[fitVariableName]),Title(("mtw_Data_"+sample+"_"+lepton).c_str() ) ) ;
	    TCanvas* c = new TCanvas("test4","test4",400,400) ;
	    Data->Print();
	    Data->plotOn(fractionFrame,DataError(RooAbsData::SumW2));
	    mtwFitFunction->plotOn(fractionFrame,LineColor(kBlack),NumCPU(9));
	    mtwFitFunction->plotOn(fractionFrame,Components(S->GetName()),LineColor(kRed),NumCPU(9));
	    //	    mtwFitFunction->plotOn(fractionFrame,Components(W->GetName()),LineColor(kGreen),NumCPU(9));
	    mtwFitFunction->plotOn(fractionFrame,Components(B->GetName()),LineColor(kBlue),NumCPU(9));

            fractionFrame->SetTitle("");
            fractionFrame->GetXaxis()->SetTitle("m_{T} (GeV)");
            if (useMET)
              fractionFrame->GetXaxis()->SetTitle("E_{T,miss}(GeV)");
            fractionFrame->GetYaxis()->SetTitle("Events");
            fractionFrame->GetYaxis()->SetTitleOffset(1.4);
            fractionFrame->GetXaxis()->SetTitleOffset(1.);
            fractionFrame->GetXaxis()->SetTitleFont(42);
            fractionFrame->GetYaxis()->SetTitleFont(42);
            fractionFrame->Draw();

            TLegend * leg = new TLegend(0.71,0.65,0.9,0.85);
            leg->SetBorderSize(0);
            leg->SetLineStyle(0);
            leg->SetTextSize(0.03);
            leg->SetFillStyle(0);
            leg->SetFillColor(0);

            HistoCollection["mtwMass"][DataChannelToFit+sample]["noSyst"][lepton]->SetMarkerStyle(20);
            QCDBackground->SetLineColor(kBlue);
            SignalSum->SetLineColor(kRed);

            leg->AddEntry(HistoCollection["mtwMass"][DataChannelToFit+sample]["noSyst"][lepton],"data","pl");
            leg->AddEntry(SignalSum,"non-QCD","l");
            leg->AddEntry(QCDBackground,"QCD","l");
            leg->Draw();

	    //	    TLatex * tex = new TLatex(0.15, 0.95,"CMS Preliminary, 19.8 fb^{-1}, Muons, #sqrt{s} = 8 TeV");
	    TLatex * tex = new TLatex(0.15, 0.95,"CMS Preliminary, 19.3 fb^{-1}, Muons, #sqrt{s} = 8 TeV");
            tex->SetNDC();
            tex->SetTextAlign(13);
            tex->SetTextFont(42);
            tex->SetTextSize(0.04);
            tex->SetLineWidth(2);
            tex->Draw();

            string plotname;
            if (useMET)
              plotname = "testFitMETDataQCDAntiIso";
            else
              plotname = "testFitMTWDataQCDAntiIso";
	    
            c->SaveAs((plotname+sample+"_"+lepton+"_2j2t.png").c_str());
            c->SaveAs((plotname+sample+"_"+lepton+"_2j2t.pdf").c_str());
            c->SaveAs((plotname+sample+"_"+lepton+"_2j2t.gif").c_str());
            c->SaveAs((plotname+sample+"_"+lepton+"_2j2t.root").c_str());
            c->Close();

	  }
	  	  
	  std::string  chargesAll[3] = {"","Plus","Minus"};
	  for (int cha = 0; cha < 3; ++cha){
	    string charge = chargesAll[cha];
	    HistoCollection[fitVariableName]["QCD"+sample]["noSyst"][lepton+charge]->Scale(MTWQCDYield->getVal()/HistoCollection[fitVariableName]["QCD"+sample]["noSyst"][lepton+charge]->Integral());
	    
	    //Obtain the WLight estimation in the WSample
	    //Fit
	    //fit 
	    // 
	    //
	    //fit 	
	    //Get qcd distributions
	    
	    for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	      string observable = (*it_o);
	      if( observable == "etaTUp" || observable == "etaTDown" ||
		  observable == "etaTTUp" || observable == "etaTTDown" ||
		  observable == "topMassWS")continue;
	      
	      if(observable == "topMassQCD" && sample != "") continue;
	      
	      if (observable == fitVariableName )continue;
	      //	    if(sample == "WSample"){
	      //if(sample==""&&lepton =="Ele")DataChannelToFit=="DataEleControl";
	    
	      
	      
	      if(sample =="SR1" || sample == "SR2") {
		int binFitZero =   HistoCollection["topMassQCD"][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->GetXaxis()->FindBin(topMassLowCut);
		int binFitOne =   HistoCollection["topMassQCD"][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->GetXaxis()->FindBin(topMassHighCut);
		
		double tot =  HistoCollection["topMassQCD"][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral();
		totalQCDRatioAfterThreshold = HistoCollection["topMassQCD"][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral(binFitZero,binFitOne-1);
		
		if (sample == "SR1") totalQCDRatioAfterThreshold = totalQCDRatioAfterThreshold/tot ;//* HistoCollection[observable][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral();
		if (sample == "SR2") totalQCDRatioAfterThreshold = (tot-totalQCDRatioAfterThreshold)/tot;// * HistoCollection[observable][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral();
		
	      

		int binFitMin = HistoCollection[fitVariableName][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->GetXaxis()->FindBin(mtwCut);
		if( lepton == "Ele ") binFitMin = HistoCollection[fitVariableName][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->GetXaxis()->FindBin(metCut);
		if( lepton == "Ele " && fitVariableName == "mtwMass") binFitMin = HistoCollection[fitVariableName][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->GetXaxis()->FindBin(mtwCutEle);
		
		//		qcdfraction = HistoCollection[fitVariableName][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral();
		//		qcdfraction = HistoCollection[fitVariableName][DataChannelToFit+"AntiIso"]["noSyst"][lepton+charge]->Integral(binFitMin,200)/qcdfraction;
		//		qcdfraction = HistoCollection[fitVariableName]["QCD"]["noSyst"][lepton+charge]->Integral(binFitMin,200);
		
		//		qcdfraction = qcdfraction * totalQCDRatioAfterThreshold;
	      }
	      
	      cout <<" obs " <<observable    << " has int 0 "<< HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()  
		   << "sample "<< sample << " fraction " << qcdfraction  << " total "<< MTWQCDYield->getVal() << " integral is " << HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Integral()   <<endl;
	      
	      
	      double totQCD = HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral();
	      //	      HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Scale();
	      double histofactor =0;
	      if(totQCD !=0) histofactor = qcdfraction/totQCD;
	      

	      HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Add(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge],histofactor);

	      //	      if(observable =="eta" && sample =="WSample")histofactor = 2.;
	      /*      if(observable =="topMass" && sample =="WSample")histofactor = totalQCDRatioAfterThreshold*HistoCollection[observable][DataChannelToFit+sample]["noSyst"][lepton+charge]->Integral()/qcdfraction;

	      if(qcdfraction*histofactor>1){
	      if(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()>0) HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Add(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge],(qcdfraction*histofactor/HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()));

	      if(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()>0) HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Add(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge],(qcdfraction*histofactor/HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()));
	      }
	      else{
		if(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()>0) HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Add(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]);

		if(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]->Integral()>0) HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Add(HistoCollection[observable][DataChannelToFit+"AntiIso"+sample]["noSyst"][lepton+charge]);
		}*/
	      
	      cout << " obs " <<observable << " integral is" << HistoCollection[observable]["QCD"+sample][systUpDown][lepton+charge]->Integral()<< endl;
	      
	      
	      //else cout << "WSample " << observable <<" lepton+charge "<< lepton+charge<< " weample data anti iso has 0 histogram "<<endl;
	      //}
	    }
	    //Get w-enriched samples
	    /*	    for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	      string observable = (*it_o);
	      //Take the mc/data channels
	      //W Light Sample
	      if( observable == "etaTUp" || observable == "etaTDown" ||
		  observable == "etaTTUp" || observable == "etaTTDown"||
		  observable == "topMassQCD"		  
		  )continue;
	      if(sample == "WSample"){
		double factorQCD=1;
		double factorVQQ=1;
		double factorWC=1;
		cout << " test abcd 0 " << endl;
		
		//	      if(systUpDown == "WLightUp") {factorQCD = 0.5; factorWC =0.5;factorVQQ=0.5;}
		//if(systUpDown == "WLightDown") {factorQCD = 1.5; factorWC =2.;factorVQQ=1.5;}
		
	      }
	    */
	      //W HF Sample
	      

	  }
	}
      }
    }
  }
  
  for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
    string syst = (*it_s);
    //if (syst != "noSyst") continue;
    int n_syst_extremes=2;
    if(syst == "noSyst")n_syst_extremes=1; 
    for (int ud = 0;ud<n_syst_extremes;++ud){
      string updown = UpDown[ud];
      if(syst =="noSyst")updown ="";
      string systUpDown = syst + updown;
      for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	string sample = (*it_sam);
	for (int lep = 0; lep <2;++lep){
	  string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	  for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	    string observable = (*it_o);
	    std::string  chargesAll[3] = {"","Plus","Minus"};
	    for(int ch = 0; ch < 3; ++ch){
	      string charge = chargesAll[ch];
	      if(observable !="PUWeight"  && observable != "mtwMass" && enlargeSample){
		if(HistoCollection[observable]["WJets"+sample][systUpDown][lepton+charge]!=0){
		  double IInt = HistoCollection[observable]["WJets"+sample][systUpDown][lepton+charge]->Integral();
		  int IBin = HistoCollection["mtwMass"]["WJets"+sample][systUpDown][lepton+charge]->FindBin(mtwCut+0.1);
		  double ACInt = HistoCollection["mtwMass"]["WJets"+sample][systUpDown][lepton+charge]->Integral(IBin,999);
		  if (IInt!=0) HistoCollection[observable]["WJets"+sample][systUpDown][lepton+charge]->Scale(ACInt/IInt);
		}
	      }
	    }
	  }
	}
      }
    }
  }
				   
  
  //LOOP 5: Fit in the two different signal regions SR1 SR2 
  for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
    string syst = (*it_s);
    //if (syst != "noSyst") continue;
    int n_syst_extremes=2;
    if(syst == "noSyst")n_syst_extremes=1; 
    for (int ud = 0;ud<n_syst_extremes;++ud){
      string updown = UpDown[ud];
      if(syst =="noSyst")updown ="";
      string systUpDown = syst + updown;
      for (int lep = 0; lep <2;++lep){
	string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	  //if(observable == "topMass" || observable == "etaTopMass" || observable == "etaCosThetalj" )continue; 
	  if(observable == "etaTUp "|| observable == "etaTDown" ||
	     observable == "etaTTUp "|| observable == "etaTTDown" ||
	     observable == "topMassQCD"
	     )continue;
	  bool isInvariant = (observable == "eta");
	  std::string  chargesAll[3] = {"","Plus","Minus"};
	  for(int ch = 0; ch < 3; ++ch){
	    string charge = chargesAll[ch];
	  
	    cout << " test seg syst "<<systUpDown << " lep " << lepton << " observable "<< observable << " charge " << charge << endl; 
	    
	    double wbbsr1 =  HistoCollection[observable]["WJetsSR1"][systUpDown][lepton+charge]->Integral();
	    double wbbsr2 =  HistoCollection[observable]["WJetsSR2"][systUpDown][lepton+charge]->Integral();
	    
	    wbbsr1 +=  HistoCollection[observable]["ZJetsSR1"][systUpDown][lepton+charge]->Integral();
	    wbbsr2 +=  HistoCollection[observable]["ZJetsSR2"][systUpDown][lepton+charge]->Integral();
	    
	    double dibsr1 =   HistoCollection[observable]["WWSR1"][systUpDown][lepton+charge]->Integral();
	    dibsr1 +=   HistoCollection[observable]["WZSR1"][systUpDown][lepton+charge]->Integral();

	    double dibsr2 =  HistoCollection[observable]["WWSR2"][systUpDown][lepton+charge]->Integral();
	    dibsr2 +=   HistoCollection[observable]["WZSR2"][systUpDown][lepton+charge]->Integral();
	    //Modified HERE
	    //	    	    doube fs = HistoCollection[observable]["Wc_wc"][systUpDown][lepton+charge]->Integral()+
	    //	      HistoCollection[observable]["WJets_wcc"][systUpDown][lepton+charge]->Integral()+
	    //	      HistoCollection[observable]["Vqq_wcc"][systUpDown][lepton+charge]->Integral();
	    //	    double fb = 
	    //  HistoCollection[observable]["WJets_wccSampleB"][systUpDown][lepton+charge]->Integral()+
	    //  HistoCollection[observable]["Wc_wcSampleB"][systUpDown][lepton+charge]->Integral()+
	    //  HistoCollection[observable]["Vqq_wccSampleB"][systUpDown][lepton+charge]->Integral();;

	    //	    double vqq_wcc_over_wcc= HistoCollection[observable]["WJets_wcc"][systUpDown][lepton+charge]->Integral() / HistoCollection[observable]["Vqq_wcc"][systUpDown][lepton+charge]->Integral();

	    //End Modify HERE

	    

	    if(isInvariant){
	      
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["DataSR2"]["noSyst"][lepton+charge]);
	      if(lepton!= "aMu"){

		//		eta_EWKSR2_noSyst_Mu_3J2TSR1_remodel->Add(HistoCollection[observable]["TChannelSR2"]["noSyst"][lepton+charge]);
		eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Reset("ICES");	      
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Reset("ICES");	      
		
		eta_TopSR2_3J2T_Mu->Reset("ICES");
		eta_TopSR1_3J2T_Mu->Reset("ICES");
		  
		eta_TopSR1_Remodel_Mu->Reset("ICES");
		eta_TopSR2_Remodel_Mu->Reset("ICES");

		eta_TTBarSR1_Remodel_Mu->Reset("ICES");		
		eta_TTBarSR2_Remodel_Mu->Reset("ICES");		
		//Remodeling tt: reduces dependance for
		eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TTBar3J2TSR2"][systUpDown][lepton+charge]);
		if(addsignaltop) {eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TChannel3J2TSR2"][systUpDown][lepton+charge]);
		  eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR2"][systUpDown][lepton+charge],1);
		}
		else eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR2"][systUpDown][lepton+charge],3.32*factorTbar);
		
		eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TWChannel3J2TSR2"][systUpDown][lepton+charge]);
		eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarWChannel3J2TSR2"][systUpDown][lepton+charge]);
		
		//		eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["WJets3J2TSR2"][systUpDown][lepton+charge]);
	      
		eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TTBar3J2TSR1"][systUpDown][lepton+charge]);
		if(addsignaltop){eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TChannel3J2TSR1"][systUpDown][lepton+charge]);
		  eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR1"][systUpDown][lepton+charge],factorTbar);
		}		
		else eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR1"][systUpDown][lepton+charge],3.32*factorTbar);
		eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TWChannel3J2TSR1"][systUpDown][lepton+charge]);
		eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarWChannel3J2TSR1"][systUpDown][lepton+charge]);
		
		//		eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["WJets3J2TSR1"][systUpDown][lepton+charge]);

		
		//UTTER DESPAIR
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["DataSR2"]["noSyst"][lepton+charge]);
		
		eta_TTBarSR2_Remodel_Mu->Add(HistoCollection[observable]["TTBarSR2"][systUpDown][lepton+charge],1);
		
		eta_TTBarSR2_Remodel_Mu->Add(HistoCollection[observable]["TbarWChannelSR2"][systUpDown][lepton+charge],1);
		eta_TTBarSR2_Remodel_Mu->Add(HistoCollection[observable]["TWChannelSR2"][systUpDown][lepton+charge],1);
		eta_TTBarSR2_Remodel_Mu->Add(HistoCollection[observable]["SChannelSR2"][systUpDown][lepton+charge],1);
		eta_TTBarSR2_Remodel_Mu->Add(HistoCollection[observable]["SbarChannelSR2"][systUpDown][lepton+charge],1);

		eta_TTBarSR1_Remodel_Mu->Add(HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge],1);
		eta_TTBarSR1_Remodel_Mu->Add(HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge],1);
		eta_TTBarSR1_Remodel_Mu->Add(HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge],1);
		eta_TTBarSR1_Remodel_Mu->Add(HistoCollection[observable]["SChannelSR1"][systUpDown][lepton+charge],1);
		eta_TTBarSR1_Remodel_Mu->Add(HistoCollection[observable]["SbarChannelSR1"][systUpDown][lepton+charge],1);

		//eta_TTBarSR2_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TTBarSR2"][systUpDown][lepton+charge],
		//					 eta_TopSR2_3J2T_Mu,
		//					 HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][lepton+charge],
		//					 false,"_3J2TSR2_remodel",0,limit);

		eta_TopSR2_Remodel_Mu = remodelLimits( eta_TTBarSR2_Remodel_Mu,
						       eta_TopSR2_3J2T_Mu,
						       HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][lepton+charge],
						       false,"_3J2TSR2_remodel",0,limit2);

		if(charge == ""){
		  eta_TopSR2_Remodel_Mu_noCharge->Reset("ICES");		  
		  eta_TopSR2_Remodel_Mu_noCharge->Add(eta_TopSR2_Remodel_Mu); 
		}
		
		if(charge == "Plus" or charge == "Minus") {
		  double factorTT=0.5;
		  eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add( eta_TopSR2_Remodel_Mu_noCharge,-1*factorTT );
		}
		else eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(eta_TopSR2_Remodel_Mu,-1);
		/*eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(eta_TTBarSR2_Remodel_Mu,-1);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TbarWChannelSR2"][systUpDown][lepton+charge],-1);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TWChannelSR2"][systUpDown][lepton+charge],-1);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["SbarChannelSR2"][systUpDown][lepton+charge],-1);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["SChannelSR2"][systUpDown][lepton+charge],-1);
		*/		
		cout << "syst updown "<< systUpDown<< " lepCharge "<< lepton + charge<<" intglhf " <<eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Integral()<< endl; 
		if(addsignaltop){
		  if(syst!="Comp"){
		    eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],-1);
		    eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],-1);
		  }
		  else{
		    eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TToBMuNuSR2"][systUpDown][lepton+charge],-1);
		    eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TToBTauNuSR2"][systUpDown][lepton+charge],-1);
		    eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TToBMuESR2"][systUpDown][lepton+charge],-1);
		  }
		}
		else eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],-3.32);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["WWSR2"][systUpDown][lepton+charge],-1);
		eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["WZSR2"][systUpDown][lepton+charge],-1);


		cout << "syst updown "<< systUpDown<< " lepCharge "<< lepton + charge<<" intggwp " <<eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Integral()<< endl; 

		if(charge == "Plus" or charge == "Minus") {
		  double factorTT=0.5;
		  eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["QCDSR2"][systUpDown][lepton+charge],-1*factorTT );
		}
		else eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Add(HistoCollection[observable]["QCDSR2"][systUpDown][lepton+charge],-1);
		
		//      eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Scale();
		eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Add(eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel);
		eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Smooth();
		

		//		eta_TTBarSR1_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TTBarSR1"][systUpDown][lepton+charge],
		//					 eta_TopSR1_3J2T_Mu,
		//					 HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][lepton+charge],
		//					 false,"_3J2TSR2_remodel",0,limit);
		
		
		eta_TopSR1_Remodel_Mu = remodelLimits( eta_TTBarSR1_Remodel_Mu,
						       eta_TopSR1_3J2T_Mu,
						       HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][lepton+charge],
						       false,"_3J2TSR1_remodel",0,limit);
		
		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(eta_TopSR1_Remodel_Mu);
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(eta_TopSR2_Remodel_Mu);
		
		eta_TopSR1_Remodel_Mu->Scale(HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][lepton+charge]->Integral()/eta_TopSR1_3J2T_Mu->Integral());
		eta_TopSR2_Remodel_Mu->Scale(HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][lepton+charge]->Integral()/eta_TopSR2_3J2T_Mu->Integral());
		
		/*		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(eta_TTBarSR1_Remodel_Mu);
		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SbarChannelSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SChannelSR1"][systUpDown][lepton+charge]);
		
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(eta_TTBarSR2_Remodel_Mu);
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarWChannelSR2"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TWChannelSR2"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SbarChannelSR2"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["TopDDSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SChannelSR2"][systUpDown][lepton+charge]);
		*/

		HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Add(eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel);
		HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WWSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WZSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["EWKTopSR2"][systUpDown][lepton+charge]->Add(eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel);
		HistoCollection["eta"]["EWKMCTopSR1"][systUpDown][lepton+charge]->Add(HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]);
		HistoCollection["eta"]["EWKMCTopSR2"][systUpDown][lepton+charge]->Add(HistoCollection["eta"]["EWKTopSR2"][systUpDown][lepton+charge]);
		
		
		if(HistoCollection["eta"]["EWKMCTopSR1"][systUpDown][lepton+charge]->Integral()!=0){
		  HistoCollection["eta"]["EWKMCTopSR1"][systUpDown][lepton+charge]->Scale((wbbsr1+dibsr1)/HistoCollection["eta"]["EWKMCTopSR1"][systUpDown][lepton+charge]->Integral());

		}
		
		if(HistoCollection["eta"]["EWKMCTopSR2"][systUpDown][lepton+charge]->Integral()!=0){
		  HistoCollection["eta"]["EWKMCTopSR2"][systUpDown][lepton+charge]->Scale((wbbsr2+dibsr2)/HistoCollection["eta"]["EWKMCTopSR2"][systUpDown][lepton+charge]->Integral());
		}
	      }
	      
	      
	      if( charge == "" && doTopRemodel){ 
		cout <<  " eta to remodel " << eta_TTBarSR2_Remodel_Mu << "  def " << HistoCollection["eta"]["TTBarSR2"][systUpDown][lepton] << " mc "<< HistoCollection["eta"]["TTBar3J2TSR2"][systUpDown][lepton]<< " data "<< HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][lepton]<<endl;

		  eta_TTBarSR2_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TTBarSR2"][systUpDown][lepton],
						     eta_TopSR2_3J2T_Mu,
						   HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][lepton],
							  false,"_3J2TSR2_remodel",0,limit2);
		
		eta_TTBarSR1_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TTBarSR1"][systUpDown][lepton],
						   eta_TopSR1_3J2T_Mu,
						   HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][lepton],
							 false,"_3J2TSR1_remodel",0,limit);
		
		
		if(lepton == "Mu") HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(eta_TTBarSR2_Remodel_Mu,-1);
		if(lepton == "Ele") HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(eta_TTBarSR2_Remodel_Mu,-1);
	      }
	      else HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TTBarSR2"][systUpDown][lepton+charge],-1);

	      
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TWChannelSR2"][systUpDown][lepton+charge],-1);
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarWChannelSR2"][systUpDown][lepton+charge],-1);
	      
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WW"][systUpDown][lepton+charge],-1);
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WZ"][systUpDown][lepton+charge],-1);
	      //	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["ZZ"][systUpDown][lepton+charge],-1);
	      //	      if(lepton == "Mu") HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["QCDMu"][systUpDown][lepton+charge],-1);
	      

	      //	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],-1.);
	      if(addsignaltop){
		HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],-1.*factorT);
		HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],-1.*factorTbar);

	      }
	      else HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],-3.32*factorTbar);
	      
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SChannelSR2"][systUpDown][lepton+charge],-1);
	      HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["SbarChannelSR2"][systUpDown][lepton+charge],-1);
	      
	      

	    
	      //HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],1.);
	      //HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],1.);
	      
	      
	      		
			
		string obsup = observable + "TUp";
		
		HistoCollection[obsup]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge],1.);

		HistoCollection[obsup]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],-1.);
		HistoCollection[obsup]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],-1.);

		string obsttup = observable + "TTUp";
		

		HistoCollection[obsttup]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge],1.);

		HistoCollection[obsttup]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TTBarSR2"][systUpDown][lepton+charge],-0.1);
		
		string obsdown = observable + "TDown";
		
		HistoCollection[obsdown]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge],1.);

		HistoCollection[obsdown]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TChannelSR2"][systUpDown][lepton+charge],1.);
		HistoCollection[obsdown]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TbarChannelSR2"][systUpDown][lepton+charge],1.);
		

		string obsttdown = observable + "TTDown";
		
		HistoCollection[obsttdown]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge],1);

		HistoCollection[obsttdown]["WHFSR2"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["TTBarSR2"][systUpDown][lepton+charge],0.1);
		

		//In the signal region to fit the shapes
		HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Add(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]);


		HistoCollection[obsdown]["WHFSR1"][systUpDown][lepton+charge]->Add(HistoCollection[obsdown]["WHFSR2"][systUpDown][lepton+charge]);

		HistoCollection[obsup]["WHFSR1"][systUpDown][lepton+charge]->Add(HistoCollection[obsup]["WHFSR2"][systUpDown][lepton+charge]);

		HistoCollection[obsttdown]["WHFSR1"][systUpDown][lepton+charge]->Add(HistoCollection[obsdown]["WHFSR2"][systUpDown][lepton+charge]);

		HistoCollection[obsttup]["WHFSR1"][systUpDown][lepton+charge]->Add(HistoCollection[obsup]["WHFSR2"][systUpDown][lepton+charge]);

		
		//Fit shape only--> integral should be the same as with nominal signal

		

		double WHFSF = (wbbsr1)/(wbbsr2);
		
		if(lepton == "aEle"
		   //		   || lepton == "Mu"
		   ){
		  

		  HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR2"][systUpDown][lepton+charge]->Integral()/HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral());
		  
		  
		  //Add the Extended Side Band sample for 
		}

		HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Smooth();
		if(lepton == "Ele")HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Smooth();

		HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Scale(WHFSF);

		//		if(charge =="" && lepton == "Mu" )eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Integral());
		if(HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Integral()!=0)HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/HistoCollection["eta"]["EWKTopSR1"][systUpDown][lepton+charge]->Integral());

				

		HistoCollection[obsup]["WHFSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/
										     HistoCollection[obsup]["WHFSR1"][systUpDown][lepton+charge]->Integral());
		HistoCollection[obsdown]["WHFSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/
										     HistoCollection[obsdown]["WHFSR1"][systUpDown][lepton+charge]->Integral());
		

		HistoCollection[obsttup]["WHFSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/
										     HistoCollection[obsttup]["WHFSR1"][systUpDown][lepton+charge]->Integral());
				
		HistoCollection[obsttdown]["WHFSR1"][systUpDown][lepton+charge]->Scale(HistoCollection[observable]["WHFSR1"][systUpDown][lepton+charge]->Integral()/
										     HistoCollection[obsttdown]["WHFSR1"][systUpDown][lepton+charge]->Integral());

		
		
	    }

	    
	  }
	}
      }
    }
  }


  //  eta_TTBarSR2_Remodel_Mu = remodel( HistoCollection["eta"]["TTBarSR2"]["noSyst"]["Mu"],
  //			   HistoCollection["eta"]["TTBar3J2TSR2"]["noSyst"]["Mu"],
  //			   HistoCollection["eta"]["Data3J2TSR2"]["noSyst"]["Mu"],
  //			     false,"_3J2TSR2_remodel");

  eta_TTBarSR1_Remodel_Mu = remodel( HistoCollection["eta"]["TTBarSR1"]["noSyst"][leptonCase],
				   HistoCollection["eta"]["TTBar3J2TSR1"]["noSyst"][leptonCase],
				   HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][leptonCase],
				     false,"_3J2TSR1_remodel");

  
  //Subtract the qcd from Data Driven Samples
  //Filling fit functions: sum of single channels 
  //NEW USE WHF AND WLIGHT 
    
  channels.push_back("WHF");
  channels.push_back("QCD");
  for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
    string syst = (*it_s);
    int n_syst_extremes=2;
    if(syst == "noSyst")n_syst_extremes=1; 
    for (int ud = 0;ud<n_syst_extremes;++ud){
      string updown = UpDown[ud];
      if(syst =="noSyst")updown ="";
      string systUpDown = syst + updown;
      for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	string observable = (*it_o);
	for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	  string sample = (*it_sam);
	  for (int lep = 0; lep <2;++lep){
	    string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	    //Fill the histograms    
	    for(std::vector<string>::const_iterator it = channels.begin(); it != channels.end(); ++it){
	      

	      string channel = (*it);
	      string channelfit = "";
	      string samplefit = sample;
	      double renormfactor = 1.;
	      string channelsum = channel;
	      string samplesum = sample;
	      double integralsum =1. ;
	      string systfit = systUpDown;

	      if( (observable == "etaTUp" || observable == "etaTDown" ||
		   observable == "etaTTUp" || observable == "etaTTDown"
		   ) && 
		  (sample != "SR1" && sample != "SR2") 
		  )continue;
	      if( observable == "topMassQCD" && ! (sample == "" || sample == "AntiIso"))continue;

	    
	      //	      cout << " test debug syst/obs/sample/channel "<< systUpDown<<"/"<<observable<<"/"<< sample <<"/"<<channel <<endl;
	      
	      if(channel == "WW" || 
		 channel == "WZ" || 
		 channel == "ZZ")channelfit = "EWK"; 
	    
	      
	      //NEW USE WHF AND WLIGHT
	      if(channel == "WHF" ){
		if(sample =="ada") channelfit = "QCD";
		else channelfit = "EWK";
	      }
	      if(channel == "WJets_a" ){
		channelfit = "EWKMC";
	      }
	      if(channel == "ZJets_a" ){
		channelfit = "EWKMC";
	      }
	      //	      if( channel == "WLight" && sample !="")channelfit = "EWK";
	      //	       if(channel == "WHF" ) channelsum = "SampleB";
	      //	       if(channel == "WLight") channelsum = "WSample";
	      if(//channel == "TTBar" || 
		  channel == "TWChannel" || 
		  channel == "TbarWChannel" || 
		  channel == "SChannel" || 
		  channel == "SbarChannel" || 
		  channel == "TTBar_Q2Down" || 
		  channel == "TTBar_Q2Up" || 
		  channel == "TTBar_MatchingDown" || 
		  channel == "TTBar_MatchingUp" || 
		  channel == "TTBar" || 
		  channel == "TTBar" || 
		  channel == "TbarWChannel_Q2Down" || 
		  channel == "TbarWChannel_Q2Up" || 
		  channel == "TWChannel_Q2Down" || 
		  channel == "TWChannel_Q2Up"  
		 ){
		channelfit = "Top";
	      }
	      if(channel == "TChannel" && syst != "Comp")channelfit = "Signal";
	      if(channel == "TbarChannel" && syst != "Comp")channelfit = "Signal";
	      if(channel == "TToBENu" && syst == "Comp")channelfit = "Signal";
	      if(channel == "TToBMuNu" && syst == "Comp")channelfit = "Signal";
	      if(channel == "TToBTauNu" && syst == "Comp")channelfit = "Signal";
	      if(channel == "TChannel_Q2Down" || channel == "TChannel_Q2Up")channelfit = "Signal";
	      if(channel == "TbarChannel_Q2Down" || channel == "TbarChannel_Q2Up")channelfit = "Signal";

	      if(channel == "Data")channelfit = "Data_Fit";
	      if(channel == "QCD") { // && sample == "AntiIsoSampleB"){
		channelfit = "QCD";
		//samplefit = "";
	      }
	      if(channelfit == ""){
		cout<<" skipping channel "<<channel <<" no bkg/sig associated "<<endl;
		continue;}
	      if( channel == "WJets" || channel == "ZJets"){
		;//		channelsum = "Vqq_wbb";
		  }
	      //if(channelfit == "QCD" && observable != "etaTopMass" && observable != "etaCosthetalj") continue;
	      string pseudodata = "";
	      for(int ch = 0; ch < 2; ++ch){
		string charge = charges[ch];
		//FIXME INELEGANT
		if(channel == "QCD" && lepton == "Mu" && systUpDown == "QCDUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(1.5);
		if(channel == "QCD" && lepton == "Mu" && systUpDown == "QCDDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(0.5);

		if(channel == "QCD" && lepton == "Ele" && systUpDown == "QCDUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(2.);
		if(channel == "QCD" && lepton == "Ele" && systUpDown == "QCDDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(0.1);



		//		if(channel == "TTBar" && systUpDown == "TTBarUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(1.15);
		//		if(channel == "TTBar" && systUpDown == "TTBarDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(0.85);
		
		if(observable !="PUWeight" && channel != "Data" && channel != "WHF"){
		  if (HistoCollection["PUWeight"][channelsum+samplesum][systUpDown][lepton+charge] != 0){
		    if(!addsignaltop && (channel == "TChannel" || channel == "TbarChannel")){
		      ;
		      HistoCollection[observable][channel+samplesum][systUpDown][lepton+charge]->Scale(HistoCollection["PUWeight"]["TbarChannel"+samplesum][systUpDown][lepton+charge]->GetMean());
		    }
		    else {

		      if(channel != "TTBar"
			 )if(!(usePUSignal && (channel == "TChannel" || channel == "TbarChannel")))HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Scale(HistoCollection["PUWeight"][channelsum+samplesum][systUpDown][lepton+charge]->GetMean());
		      

		    }
		  }
		}
		
		


		//FIXME INELEGANT
		if(channelfit == "QCD" && observable == "etaTopMass")cout << " eta integral "  << 
		  HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton+charge]->Integral()<< " topMass integral "<<
		  HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton+charge]->Integral()<<endl;
		
		if(observable == "etaTopMass"){
		  if( channel == "WHF_c" && channelfit == "QCD")continue; 
		  if(channelfit != "Data_Fit" ){
		    HistoCollection[observable][channelfit+samplesum][systUpDown][lepton+charge]->Add(
                        makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton+charge],
			HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton+charge],
				5, 5,-1.));
		    cout << "etatopmass "<< HistoCollection[observable][channelfit+samplesum][systUpDown][lepton+charge]-> Integral()  
			 << "channel " << channel << " syst "<< systUpDown<< " sample "<< sample << " lepton+charge "<< lepton+charge <<  endl;
		    continue;
		  }
//		  else{
//		    HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge] = 
//		      makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton+charge],
//				  HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton+charge],
//				  5, 5,-1.);
//		  }
				  
		  if(channel == "Data" && syst == "noSyst" && sample == ""){
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge] =
		    makeproduct(Histo2DCollection[observable][channel+sample][systUpDown][lepton+charge]);
		  }

		}
		if(observable == "etaCosthetalj"){
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge] = 
		    makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton+charge],
				HistoCollection["costhetalj"][channelsum+samplesum][systUpDown][lepton+charge],
				5, 5,-1.);
		  
		  if(channel == "Data" && syst == "noSyst" && sample == ""){
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge] =
		    makeproduct(Histo2DCollection[observable][channel+sample][systUpDown][lepton+charge]);
		  }

		}
		
		//if(channelfit== "EWK") renormfactor = renormalize(observable,channel,sample,syst,lepton,charge);
		//		if(channelfit == "QCD")renormfactor = 0.5*qcdintegralmap(lepton,HistoCollection[observable][channel+sample][systUpDown][lepton+pseudodata]->Integral());
		//HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->cd();
		string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;
	      
		if(channelfit == "QCD" && observable == "etaTopMass")cout << " eta topmass integral "  << 
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Integral() <<endl;
		
		integralsum = HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->Integral()/HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Integral();
		
		if(HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Integral() == 0) integralsum =0; 
		
		if(!(channelfit == "QCD" && channel == "QCD") )HistoCollection[observable][channelfit+samplefit][systUpDown][lepton+charge]->Add(HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge] ) ; 
		
		cout<< " name : " << name << " added integral " << HistoCollection[observable][channelfit+samplefit][systUpDown][lepton+charge]->Integral()  <<endl;
	      cout <<" integral up" << HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->Integral() << " down "<< 
		HistoCollection[observable][channelsum+samplesum][systUpDown][lepton+charge]->Integral() <<" channelsum " << integralsum <<endl;
	      }
	    

	      
	      		//FIXME INELEGANT
    		if(channel == "QCD" && lepton == "Mu" && systUpDown == "QCDUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(1.5);
		if(channel == "QCD" && lepton == "Mu" && systUpDown == "QCDDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(0.5);

    		if(channel == "QCD" && lepton == "Ele" && systUpDown == "QCDUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(2.);
		if(channel == "QCD" && lepton == "Ele" && systUpDown == "QCDDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(0.1);


		//		if(channel == "TTBar" && systUpDown == "TTBarUp")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(1.2);
		//		if(channel == "TTBar" && systUpDown == "TTBarDown")HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(0.8);
		//FIXME INELEGANT

		if(observable !="PUWeight" && channel != "Data" && channel != "WHF"){
		  if (HistoCollection["PUWeight"][channelsum+samplesum][systUpDown][lepton] != 0){
		    cout << " pre-pureweighted "<< channel << " variable "<< observable<< " sample "<< samplesum <<" integral "<< HistoCollection[observable][channel+samplesum][systUpDown][lepton]->Integral()<<endl;

		    cout << " puweighting "<< channel<< " lep "<< lepton << " sample "<< samplesum << HistoCollection["PUWeight"]["TbarChannel"+samplesum][systUpDown][lepton]->GetMean();
		    
		    if(!addsignaltop && (channel == "TChannel" || channel == "TbarChannel")){
		      ;
		      HistoCollection[observable][channel+samplesum][systUpDown][lepton]->Scale(HistoCollection["PUWeight"]["TbarChannel"+samplesum][systUpDown][lepton]->GetMean());
		    }
		    else {
		      if(channel != "TTBar")if(!(usePUSignal && (channel == "TChannel" || channel == "TbarChannel")))HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(HistoCollection["PUWeight"][channelsum+samplesum][systUpDown][lepton]->GetMean());
		    }
		    cout << " pureweighted "<< HistoCollection[observable][channel+samplesum][systUpDown][lepton]->Integral()<<endl;
		  }
		}

		//		if(observable !="PUWeight" && channel == "WJets" && observable != "mtwMass" && enlargeSample){
		//  double IInt = HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Integral();
		//  int IBin = HistoCollection["mtwMass"][channelsum+samplesum][systUpDown][lepton]->FindBin(mtwCut+0.1);
		//  double ACInt = HistoCollection["mtwMass"][channelsum+samplesum][systUpDown][lepton]->Integral(IBin,999);
		//  if (IInt!=0) HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Scale(ACInt/IInt);
		//	}
	      
	      if(channelfit == "QCD" && observable == "etaTopMass")cout << " eta integral "  << 
		  HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton]->Integral()<< " topMass integral "<<
		  HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton]->Integral()<<endl;
	
		if(observable == "etaTopMass"){
		  if( channel == "WHF_c" && channelfit == "QCD")continue; 
		  if(channelfit != "Data_Fit"){
		    HistoCollection[observable][channelfit+samplesum][systUpDown][lepton]->Add( 
		    makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton],
				HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton],
				5, 5,-1.));
		    cout << "etatopmass "<< HistoCollection[observable][channelfit+samplesum][systUpDown][lepton]-> Integral()  
			 << "channel " << channel << " syst "<< systUpDown<< " sample "<< sample << " lepton "<< lepton <<  endl;
		    continue;
		  }
		  else{
		    HistoCollection[observable][channelsum+samplesum][systUpDown][lepton] = 
		    makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton],
				HistoCollection["topMass"][channelsum+samplesum][systUpDown][lepton],
				5, 5,-1.);
		  }
		  if(channel == "Data" && syst == "noSyst" && sample == ""){
		    HistoCollection[observable][channelsum+samplesum][systUpDown][lepton] =
		      makeproduct(Histo2DCollection[observable][channel+sample][systUpDown][lepton]);
		  }
		}
	    
		string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton;
		
		cout<< " name : " << name << " added integral " << HistoCollection[observable][channelfit+samplefit][systUpDown][lepton]->Integral()  <<endl;
		cout <<" integral up" << HistoCollection[observable][channel+sample][systUpDown][lepton]->Integral() << " down "<< 
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Integral() <<" channelsum " << integralsum <<endl;
		
		if(observable == "etaCosthetalj"){
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton] = 
		    makeproduct(HistoCollection["eta"][channelsum+samplesum][systUpDown][lepton],
				HistoCollection["costhetalj"][channelsum+samplesum][systUpDown][lepton],
				5, 5,-1.);

		  if(channel == "Data" && syst == "noSyst" && sample == ""){
		  HistoCollection[observable][channelsum+samplesum][systUpDown][lepton] =
		    makeproduct(Histo2DCollection[observable][channel+sample][systUpDown][lepton]);
		  }

		}
	    

		//	      if(channelfit== "EWK") renormfactor = renormalize(observable,channel,sample,syst,lepton,"");
	      //	      if(channelfit == "QCD")renormfactor = qcdintegralmap(lepton,HistoCollection[observable][channel+sample][systUpDown][lepton]->Integral());
	      
	      //      HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->SetCurrentDirectory("");
	      integralsum = HistoCollection[observable][channel+sample][systUpDown][lepton]->Integral()/HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Integral();

	      if(HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Integral() == 0) integralsum =0; 
	      
	      if(!(channelfit=="QCD"&& channel =="QCD"))HistoCollection[observable][channelfit+samplefit][systUpDown][lepton]->Add(
	      HistoCollection[observable][channelsum+samplesum][systUpDown][lepton],integralsum*renormfactor);
	      //	      string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton;
	      cout<< " name : " << name << " added integral " << HistoCollection[observable][channelfit+samplefit][systUpDown][lepton]->Integral()  <<endl;
	      cout <<" integral up" << HistoCollection[observable][channel+sample][systUpDown][lepton]->Integral() << " down "<< 
		HistoCollection[observable][channelsum+samplesum][systUpDown][lepton]->Integral() <<" channelsum " << integralsum <<endl;
	    }
	  }
	}
      }
    }
  }


  for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
    string syst = (*it_s);
    //if (syst != "noSyst") continue;
    int n_syst_extremes=2;
    if(syst == "noSyst")n_syst_extremes=1; 
    for (int ud = 0;ud<n_syst_extremes;++ud){
      string updown = UpDown[ud];
      if(syst =="noSyst")updown ="";
      string systUpDown = syst + updown;
      for (int lep = 0; lep <2;++lep){
	string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	std::string  chargesAll[3] = {"","Plus","Minus"};
	for(int ch = 0; ch < 3; ++ch){
	  string charge = chargesAll[ch];
	  
	  double WZInt =  HistoCollection["eta"]["ZJetsSR1"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WJetsSR1"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WWSR1"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WZSR1"][systUpDown][lepton+charge]->Integral(); 

	  HistoCollection["eta"]["EWKMCSR1"][systUpDown][lepton+charge]->Add(HistoCollection["eta"]["EWKSR1"][systUpDown][lepton+charge]);

	  if (HistoCollection["eta"]["EWKMCSR1"][systUpDown][lepton+charge]->Integral()!=0)HistoCollection["eta"]["EWKMCSR1"][systUpDown][lepton+charge]->Scale(WZInt/HistoCollection["eta"]["EWKMCSR1"][systUpDown][lepton+charge]->Integral());

	  WZInt =  HistoCollection["eta"]["ZJetsSR2"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WJetsSR2"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WWSR2"][systUpDown][lepton+charge]->Integral(); 
	  WZInt +=  HistoCollection["eta"]["WZSR2"][systUpDown][lepton+charge]->Integral(); 

	  HistoCollection["eta"]["EWKMCSR2"][systUpDown][lepton+charge]->Add(HistoCollection["eta"]["EWKSR2"][systUpDown][lepton+charge]);
	  
	  if (HistoCollection["eta"]["EWKMCSR2"][systUpDown][lepton+charge]->Integral()!=0)HistoCollection["eta"]["EWKMCSR2"][systUpDown][lepton+charge]->Scale(WZInt/HistoCollection["eta"]["EWKMCSR2"][systUpDown][lepton+charge]->Integral());

	}
      }
    }
  }
  
  eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase]);
  eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"][leptonCase]);

  eta_Data_FitSR2_Prediction_Mu->Add(HistoCollection["eta"]["WJetsSR2"]["noSyst"][leptonCase]);
  eta_Data_FitSR2_Prediction_Mu->Add(HistoCollection["eta"]["ZJetsSR2"]["noSyst"][leptonCase]);

  eta_Data_Fit_Prediction_Mu_Plus->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase+"Plus"]);
  eta_Data_Fit_Prediction_Mu_Plus->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"][leptonCase+"Plus"]);

  eta_Data_FitSR2_Prediction_Mu_Plus->Add(HistoCollection["eta"]["WJetsSR2"]["noSyst"][leptonCase+"Plus"]);
  eta_Data_FitSR2_Prediction_Mu_Plus->Add(HistoCollection["eta"]["ZJetsSR2"]["noSyst"][leptonCase+"Plus"]);

  eta_Data_Fit_Prediction_Mu_Minus->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase+"Minus"]);
  eta_Data_Fit_Prediction_Mu_Minus->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"][leptonCase+"Minus"]);

  eta_Data_FitSR2_Prediction_Mu_Minus->Add(HistoCollection["eta"]["WJetsSR2"]["noSyst"][leptonCase+"Minus"]);
  eta_Data_FitSR2_Prediction_Mu_Minus->Add(HistoCollection["eta"]["ZJetsSR2"]["noSyst"][leptonCase+"Minus"]);



  cout << "test a" << endl;



  eta_Data_Fit_Prediction_Ele->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"]["Ele"]);
  eta_Data_Fit_Prediction_Ele->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"]["Ele"]);
  
  cout << "test c" << endl;

  eta_Data_Fit_PredictionVariated_Mu->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase]);//,1.18);
  eta_Data_Fit_PredictionVariated_Mu->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"][leptonCase]);

  cout << "test b" << endl;



  eta_Data_Fit_PredictionVariated_Ele->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"]["Ele"]);//,0.965);
  eta_Data_Fit_PredictionVariated_Ele->Add(HistoCollection["eta"]["ZJetsSR1"]["noSyst"]["Ele"]);

  cout << "test d" << endl;


  //  eta_Data_Fit_WModel_Ele =  remodel( HistoCollection["eta"]["EWKSR1"]["noSyst"]["Ele"],
  //			      eta_Data_Fit_Prediction_Ele,
  //			      eta_Data_Fit_PredictionVariated_Ele,false,"SR2_remodel");


  cout << "test e" << endl;

  //  eta_Data_Fit_WModel_Mu =  remodel( HistoCollection["eta"]["EWKSR1"]["noSyst"]["Mu"],
  //			      eta_Data_Fit_Prediction_Mu,
  //			     eta_Data_Fit_PredictionVariated_Mu,false,"SR2_remodel");


  cout << "test f" << endl;
  //  eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["WJetsSR2"]["noSyst"]["Mu"],-1+1/1.18);
  // eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["WJets_wccSR2"]["noSyst"]["Mu"],-1+1/1.38);
  
  cout << "test a" << endl;


  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Ele->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase],0.2);
  eta_Data_Fit_Prediction_Ele->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase],0.2);

  eta_EWKSR1_Remodel_scaling_Mu->Reset("ICES");

  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Ele->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase]);
  eta_Data_Fit_Prediction_Ele->Add(HistoCollection["eta"]["WJetsSR1"]["noSyst"][leptonCase]);


  cout << "integral mc sr1 " << eta_Data_Fit_Prediction_Mu->Integral() <<" sr2 " << eta_Data_FitSR2_Prediction_Mu->Integral();

  eta_EWKSR1_Remodel_scaling_Mu_Plus->Reset("ICES");
  eta_EWKSR1_Remodel_scaling_Mu_Minus->Reset("ICES");


  eta_EWKSR1_Remodel_scaling_Mu = remodel( eta_Data_Fit_Prediction_Mu,
					   eta_Data_FitSR2_Prediction_Mu,
					   HistoCollection["eta"]["EWKSR2"]["noSyst"][leptonCase],
					   true,"ScaleRemodel");

  eta_EWKSR1_Remodel_scaling_Mu_Plus = remodel( eta_Data_Fit_Prediction_Mu_Plus,
					   eta_Data_FitSR2_Prediction_Mu_Plus,
					   HistoCollection["eta"]["EWKSR2"]["noSyst"][leptonCase+"Plus"],
					   true,"ScaleRemodel");

  eta_EWKSR1_Remodel_scaling_Mu_Minus = remodel( eta_Data_Fit_Prediction_Mu_Minus,
					   eta_Data_FitSR2_Prediction_Mu_Minus,
					   HistoCollection["eta"]["EWKSR2"]["noSyst"][leptonCase+"Minus"],
					   true,"ScaleRemodel");

  
  cout << "test f" << endl;
  
  eta_WJets_wbb_Remodel_Mu = remodel ( HistoCollection["eta"]["EWKSR1"]["noSyst"][leptonCase],
				       eta_WJets_wbbWSampleSR2_noSyst_Mu,
				       eta_WJets_wbbWSampleSR1_noSyst_Mu,"_remodel_MC");
  
  
  //  eta_WJets_wbbSR2_noSyst_Minus
  
  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wbbSR1_noSyst,0.3);
  
  eta_EWKSR1_Wbb_Remodeled->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  

  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst_Plus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst_Plus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst_Plus);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wbbSR1_noSyst_Plus,0.3);
  
  eta_EWKSR1_Wbb_Remodeled_Plus->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase+"Plus"],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  

  
  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst_Minus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst_Minus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst_Minus);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wbbSR1_noSyst_Minus,0.3);
  
  eta_EWKSR1_Wbb_Remodeled_Minus->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase+"Minus"],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  




  //Wcc

  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wccSR1_noSyst,0.3);
  
  eta_EWKSR1_Wcc_Remodeled->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  

  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst_Plus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst_Plus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst_Plus);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wccSR1_noSyst_Plus,0.3);
  
  eta_EWKSR1_Wcc_Remodeled_Plus->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  

  
  eta_Data_Fit_Prediction_Mu->Reset("ICES");
  eta_Data_Fit_PredictionVariated_Mu->Reset("ICES");
  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wbbSR1_noSyst_Minus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wccSR1_noSyst_Minus);  eta_Data_Fit_Prediction_Mu->Add(eta_WJets_wlightSR1_noSyst_Minus);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_Data_Fit_Prediction_Mu);
  eta_Data_Fit_PredictionVariated_Mu->Add(eta_WJets_wccSR1_noSyst_Minus,0.3);
  
  eta_EWKSR1_Wcc_Remodeled_Minus->Add((TH1D*)remodel( HistoCollection["eta"]["EWKTopSR1"]["noSyst"][leptonCase],
			       eta_Data_Fit_PredictionVariated_Mu,
						eta_Data_Fit_Prediction_Mu));  


  //Remodel systs
  for(std::vector<string>::const_iterator it_s = systematics.begin(); it_s != systematics.end(); ++it_s){
    string syst = (*it_s);
    int n_syst_extremes=2;
    //if (syst != "noSyst") continue;                                        
    if(syst == "noSyst")n_syst_extremes=1; 
    for (int ud = 0;ud<n_syst_extremes;++ud){
      string updown = UpDown[ud];
      if(syst =="noSyst")updown ="";
      string systUpDown = syst + updown;
      
      //Remodel top systs
      eta_TopSR1_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TopSR1"][systUpDown][leptonCase],
					     HistoCollection["eta"]["TTBar3J2TSR1"][systUpDown][leptonCase],
					     HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][leptonCase],
					     false,"",0, limit);
      
      if(doTopRemodel)HistoCollection["eta"]["TopSR1"][systUpDown][leptonCase] = eta_TopSR1_Remodel_Mu;
      
      
      
      
      
      
      //FIXME: doi t again if neessary
      if(!addsignaltop){
	
	eta_SignalSR1_Remodel_Mu = remodel( HistoCollection["eta"]["TbarChannelSR1"][systUpDown][leptonCase],
					    eta_SignalAntiTop_Remodel_Mu,
					    eta_SignalTop_Remodel_Mu,false,""); 
	
	double total=	 HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->Integral();
	string title =  HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->GetTitle();
	string name =  HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->GetName();
	
	
	HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase] = eta_SignalSR1_Remodel_Mu;
	
	double tmpInt = HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->Integral();
	
	HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->Scale(total/tmpInt);
	
	HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->SetTitle(title.c_str());
	HistoCollection["eta"]["SignalSR1"][systUpDown][leptonCase]->SetName(name.c_str());
      }
      //Remodel signal systs
      
    }	
  }    
  
  if(!doTopRemodel){
    eta_TopSR2_3J2T_Mu->Reset("ICES");
    eta_TopSR1_3J2T_Mu->Reset("ICES");
    
    eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TTBar3J2TSR2"]["noSyst"][leptonCase]);
    eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TWChannel3J2TSR2"]["noSyst"][leptonCase]);
    eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarWChannel3J2TSR2"]["noSyst"][leptonCase]);
    
    eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TTBar3J2TSR1"]["noSyst"][leptonCase]);
    eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TWChannel3J2TSR1"]["noSyst"][leptonCase]);
    eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarWChannel3J2TSR1"]["noSyst"][leptonCase]);
    
    eta_TopSR1_Extrap_3J2T->Add(eta_TopSR1_3J2T_Mu);
    double intmpt2 = eta_TopSR1_Extrap_3J2T->Integral();
    double intmpts2 =  HistoCollection["eta"]["TopSR1"]["noSyst"][leptonCase]->Integral();
    eta_TopSR1_Extrap_3J2T->Scale(intmpts2/intmpt2);
    
    eta_TopSR2_Extrap_3J2T->Add(eta_TopSR2_3J2T_Mu);
    intmpt2 = eta_TopSR2_Extrap_3J2T->Integral();
    intmpts2 =  HistoCollection["eta"]["TopSR2"]["noSyst"][leptonCase]->Integral();
    eta_TopSR2_Extrap_3J2T->Scale(intmpts2/intmpt2);
    
    
    if(addsignaltop){eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TChannel3J2TSR1"]["noSyst"][leptonCase]);
      eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR1"]["noSyst"][leptonCase],factorTbar);
    }		
    else eta_TopSR1_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR1"]["noSyst"][leptonCase],3.32*factorTbar);
    
    if(addsignaltop) {eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TChannel3J2TSR2"]["noSyst"][leptonCase]);
      eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR2"]["noSyst"][leptonCase],1);
    }
    else eta_TopSR2_3J2T_Mu->Add(HistoCollection["eta"]["TbarChannel3J2TSR2"]["noSyst"][leptonCase],3.32*factorTbar);      
    
    eta_TopSR2_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TopSR2"]["noSyst"][leptonCase],
					   eta_TopSR2_3J2T_Mu,
					   HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][leptonCase],
					   false,"_3J2TSR2_remodel",0,limit2);
    
    
    eta_TopSR1_Remodel_Mu = remodelLimits( HistoCollection["eta"]["TopSR1"]["noSyst"][leptonCase],
					   eta_TopSR1_3J2T_Mu,
					   HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][leptonCase],
					   false,"_3J2TSR1_remodel",0,limit);
    
  }
  
  eta_TopSR1_Remodel_Func= getRemodelFunction( eta_TopSR1_3J2T_Mu,
					       HistoCollection["eta"]["Data3J2TSR1"]["noSyst"][leptonCase],
					       false,"_3J2TSR1_remodel");
  
  eta_TopSR2_Remodel_Func= getRemodelFunction( eta_TopSR2_3J2T_Mu,
					       HistoCollection["eta"]["Data3J2TSR2"]["noSyst"][leptonCase],
					       false,"_3J2TSR2_remodel");
  
  TFile output(("Test_File_All"+postfix_file+".root").c_str(),"RECREATE");
  
  for(std::vector<string>::const_iterator it = allchannels.begin(); it != allchannels.end(); ++it){
    string channel = (*it);
    for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
      string syst = (*it_s);
      int n_syst_extremes=2;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	string systUpDown = syst + updown;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	    for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	      string sample = (*it_sam);
	      if(  sample != "WSample" &&
		   ( observable == "etaLow"  || observable =="etaHigh" || observable == "topMassWS")
		   ) continue;
	      if(  ( sample != "SR1" && sample !=  "SR2") &&
		   ( observable == "etaTUp" || observable == "etaTDown" ||
		     observable == "etaTTUp" || observable == "etaTTDown"
		     )
		   ) continue;
	      if( observable == "topMassQCD" && ! (sample == "" || sample == "AntiIso"))continue;
	      
	      if(observable == "etaCosthetalj")continue; 
	      if(observable == "etaTopMass" && sample != "")continue; 
	      for (int lep = 0; lep <2;++lep){
		string lepton = leptons[lep]; if(lepton != leptonCase )continue;
		//Fill the histograms    
		for(int ch = 0; ch < 2; ++ch){
		  string charge = charges[ch];
		  string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;
		  string histoname = name;
		  //HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->cd();
		  //		  if(lepton== "Ele" && (sample == "SR1" || sample == "" || sample == "SR2") ) HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->Rebin();
		  HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->Write(); 
		}
		string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton;
		string histoname = name;
		if(channel == "QCD" && observable == "etaTopMass")cout << " etatopmass here test"  <<  HistoCollection[observable][channel+sample][systUpDown][lepton]<< " integral "<< HistoCollection[observable][channel+sample][systUpDown][lepton]->Integral() <<endl;
		//		HistoCollection[observable][channel+sample][systUpDown][lepton]->SetDirectory( output.GetDirectory(""));
		
		//if(lepton== "Ele" && (sample == "SR1" || sample == "" || sample == "SR2") ) HistoCollection[observable][channel+sample][systUpDown][lepton]->Rebin();
		HistoCollection[observable][channel+sample][systUpDown][lepton]->Write();
		cout<< " name : " << name << " written " <<endl;
	      }
	    }
	}
      }
    }
  } 
  
  //Make extra cross-check systs:

  eta_Data_FitWSampleSR1_noSyst_Mu->Write();
  eta_Data_FitWSampleSR2_noSyst_Mu->Write();

  eta_TTBarSR1_Remodel_Mu->Write();
  eta_TTBarSR2_Remodel_Mu->Write();

  eta_TopSR1_Remodel_Mu->Write();
  eta_TopSR2_Remodel_Mu->Write();

  eta_TopSR1_Remodel_Func->Write();
  eta_TopSR2_Remodel_Func->Write();

  eta_Data_FitWSampleSR1_noSyst_Ele->Write();
  eta_Data_FitWSampleSR2_noSyst_Ele->Write();

  eta_TopSR2_3J2T_Mu->Write();
  eta_TopSR1_3J2T_Mu->Write();

  eta_TopSR1_Extrap_3J2T->Write();
  eta_TopSR2_Extrap_3J2T->Write();

  eta_EWKSR1_Remodel_Ele->Write();
  eta_EWKSR1_Remodel_Mu->Write();

  eta_EWKSR1_RemodelShape_Mu->Write();
  eta_EWKSR1_RemodelShape_Ele->Write();

  eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Write();
  eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Write();

  eta_SignalSR1_Remodel_Mu->Write();
  eta_SignalTop_Remodel_Mu->Write();
  eta_SignalAntiTop_Remodel_Mu->Write();

  eta_WJets_wbb_Remodel_Mu->Write();  
  
  eta_Data_Fit_Prediction_Ele->Write();
  eta_Data_Fit_Prediction_Mu->Write();
  eta_Data_Fit_PredictionVariated_Ele->Write();
  eta_Data_Fit_PredictionVariated_Mu->Write();
  eta_Data_Fit_WModel_Mu->Write();
  eta_Data_Fit_WModel_Ele->Write();

  eta_Data_FitSR2_Prediction_Mu->Write();
  eta_EWKSR1_Remodel_scaling_Mu->Write();
  eta_EWKSR1_Remodel_scaling_Mu_Minus->Write();
  eta_EWKSR1_Remodel_scaling_Mu_Plus->Write();

  eta_WJets_wbbSR2_noSyst_Minus->Write();
  eta_WJets_wccSR2_noSyst_Minus->Write();
  eta_WJets_wlightSR2_noSyst_Minus->Write();

  eta_WJets_wbbSR2_noSyst_Plus->Write();
  eta_WJets_wccSR2_noSyst_Plus->Write();
  eta_WJets_wlightSR2_noSyst_Plus->Write();

  eta_WJets_wbbSR2_noSyst->Write();
  eta_WJets_wccSR2_noSyst->Write();
  eta_WJets_wlightSR2_noSyst->Write();


  eta_WJets_wbbSR1_noSyst_Minus->Write();
  eta_WJets_wccSR1_noSyst_Minus->Write();
  eta_WJets_wlightSR1_noSyst_Minus->Write();

  eta_WJets_wbbSR1_noSyst_Plus->Write();
  eta_WJets_wccSR1_noSyst_Plus->Write();
  eta_WJets_wlightSR1_noSyst_Plus->Write();

  eta_WJets_wbbSR1_noSyst->Write();
  eta_WJets_wccSR1_noSyst->Write();
  eta_WJets_wlightSR1_noSyst->Write();

  eta_EWKSR1_Wbb_Remodeled->Write();
  eta_EWKSR1_Wbb_Remodeled_Plus->Write();
  eta_EWKSR1_Wbb_Remodeled_Minus->Write();

  eta_EWKSR1_Wcc_Remodeled->Write();
  eta_EWKSR1_Wcc_Remodeled_Plus->Write();
  eta_EWKSR1_Wcc_Remodeled_Minus->Write();

  output.Write();
  output.Close();

  TFile outputfit(("Test_File_Fit"+postfix_file+".root").c_str(),"RECREATE");
  

  for(std::vector<string>::const_iterator it = channels_fit.begin(); it != channels_fit.end(); ++it){
    string channel = (*it);
    for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
      string syst = (*it_s);
      int n_syst_extremes=2;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	string systUpDown = syst + updown;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	  for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	      string sample = (*it_sam);
	      if(  ( sample != "SR1" && sample !=  "SR2") &&
		   ( observable == "etaTUp" || observable == "etaTDown" ||
		     observable == "etaTTUp" || observable == "etaTTDown"
		     )
		   ) continue;
	      if( observable == "topMassQCD" && ! (sample == "" || sample == "AntiIso"))continue;
	      if(observable == "etaCosthetalj")continue; 
	      if(observable == "etaTopMass" && sample != "")continue; 
	      for (int lep = 0; lep <2;++lep){
		string lepton = leptons[lep]; if(lepton != leptonCase)continue;
		//Fill the histograms    
		for(int ch = 0; ch < 2; ++ch){
		  string charge = charges[ch];
		  string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;
		  string histoname = name;
		  //HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->cd();
		  HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->Write(); 
		}
		string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton;
		string histoname = name;
		//      HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->SetCurrentDirectory("");
		HistoCollection[observable][channel+sample][systUpDown][lepton]->Write();
		cout<< " name : " << name << " written " <<endl;
	      }
	  }
	}
      }
    }
  } 

  eta_Data_Fit_Prediction_Ele->Write();
  eta_Data_Fit_Prediction_Mu->Write();

  eta_TTBarSR1_Remodel_Mu->Write();
  eta_TTBarSR2_Remodel_Mu->Write();

  eta_TopSR1_Remodel_Mu->Write();
  eta_TopSR2_Remodel_Mu->Write();

  eta_EWKSR1_noSyst_Mu_3J2TSR1_remodel->Write();
  eta_EWKSR2_noSyst_Mu_3J2TSR2_remodel->Write();

  eta_TopSR1_Remodel_Func->Write();
  eta_TopSR2_Remodel_Func->Write();

  eta_Data_Fit_PredictionVariated_Ele->Write();
  eta_Data_Fit_PredictionVariated_Mu->Write();

  eta_EWKSR1_RemodelShape_Mu->Write();
  eta_EWKSR1_RemodelShape_Ele->Write();

  eta_TopSR2_3J2T_Mu->Write();
  eta_TopSR1_3J2T_Mu->Write();

  eta_TopSR1_Extrap_3J2T->Write();
  eta_TopSR2_Extrap_3J2T->Write();

  eta_SignalSR1_Remodel_Mu->Write();
  eta_SignalTop_Remodel_Mu->Write();
  eta_SignalAntiTop_Remodel_Mu->Write();


  eta_Data_FitWSampleSR1_noSyst_Mu->Write();
  eta_Data_FitWSampleSR2_noSyst_Mu->Write();

  eta_Data_FitWSampleSR1_noSyst_Ele->Write();
  eta_Data_FitWSampleSR2_noSyst_Ele->Write();
  
  eta_EWKSR1_Remodel_Ele->Write();
  eta_EWKSR1_Remodel_Mu->Write();

  eta_WJets_wbb_Remodel_Mu->Write();  

  eta_Data_FitSR2_Prediction_Mu->Write();
  eta_EWKSR1_Remodel_scaling_Mu->Write();
  eta_EWKSR1_Remodel_scaling_Mu_Minus->Write();
  eta_EWKSR1_Remodel_scaling_Mu_Plus->Write();

  eta_Data_Fit_WModel_Mu->Write();
  eta_Data_Fit_WModel_Ele->Write();

  eta_WJets_wbbSR2_noSyst_Minus->Write();
  eta_WJets_wccSR2_noSyst_Minus->Write();
  eta_WJets_wlightSR2_noSyst_Minus->Write();

  eta_WJets_wbbSR2_noSyst_Plus->Write();
  eta_WJets_wccSR2_noSyst_Plus->Write();
  eta_WJets_wlightSR2_noSyst_Plus->Write();

  eta_WJets_wbbSR2_noSyst->Write();
  eta_WJets_wccSR2_noSyst->Write();
  eta_WJets_wlightSR2_noSyst->Write();


  eta_WJets_wbbSR1_noSyst_Minus->Write();
  eta_WJets_wccSR1_noSyst_Minus->Write();
  eta_WJets_wlightSR1_noSyst_Minus->Write();

  eta_WJets_wbbSR1_noSyst_Plus->Write();
  eta_WJets_wccSR1_noSyst_Plus->Write();
  eta_WJets_wlightSR1_noSyst_Plus->Write();

  eta_WJets_wbbSR1_noSyst->Write();
  eta_WJets_wccSR1_noSyst->Write();
  eta_WJets_wlightSR1_noSyst->Write();

  eta_EWKSR1_Wbb_Remodeled->Write();
  eta_EWKSR1_Wbb_Remodeled_Plus->Write();
  eta_EWKSR1_Wbb_Remodeled_Minus->Write();

  eta_EWKSR1_Wcc_Remodeled->Write();
  eta_EWKSR1_Wcc_Remodeled_Plus->Write();
  eta_EWKSR1_Wcc_Remodeled_Minus->Write();


  outputfit.Close();

  cout << " ended systs writing, starting part for PEs "<<endl;

  if(doMCStatUnc){
    TFile outputkstests(("Test_File_KSTests"+postfix_file+".root").c_str(),"RECREATE");

    std::string  chargesAll[3] = {"","Plus","Minus"};

    
    for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
      string syst = (*it_s);
      int n_syst_extremes=2;
      if(syst != "noSyst" )continue;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	string systUpDown = syst + updown;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	  if(observable != "eta" ) continue;
	  for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	    string sample = (*it_sam);
	    if(sample != "SR1") continue;

	    //	  if(  ( sample != "SR1" && sample !=  "SR2") &&
	    //  ( observable == "etaTUp" || observable == "etaTDown" ||
	    //	 observable == "etaTTUp" || observable == "etaTTDown"
	    //	 )
	    //  ) continue;
	    //if(observable == "etaCosthetalj")continue; 
	    //if(observable == "etaTopMass" && sample != "")continue; 
	    for (int lep = 0; lep <2;++lep){
	      string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	      
	      std::string  chargesAll[3] = {"","Plus","Minus"};
	      for (int cha = 0; cha < 3; ++cha){
		string charge = chargesAll[cha];

		//Fill the histograms    
		//		  string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;
	      //string histoname = name;
	      //HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->cd();
	      string channel = "Signal";
	      string histoname ="";
	      
	      int nbinstemp = nbins[observable];
	      
	      double scaleWJets = HistoCollection[observable]["Signal"][systUpDown][lepton+charge]->Integral()+
		HistoCollection[observable]["Top"][systUpDown][lepton+charge]->Integral()+
		HistoCollection[observable]["WW"][systUpDown][lepton+charge]->Integral()+
		HistoCollection[observable]["WZ"][systUpDown][lepton+charge]->Integral();
	      
	      double WInt = HistoCollection[observable]["WJets"][systUpDown][lepton+charge]->Integral()+
		HistoCollection[observable]["ZJets"][systUpDown][lepton+charge]->Integral();
	      
	      scaleWJets = (HistoCollection[observable]["Data"][systUpDown][lepton+charge]->Integral()-scaleWJets)/WInt;
	      scaleWJets = 1.;//      scaleWJets = (HistoCollection[observable]["Data"][systUpDown][lepton+charge]->Integral()-scaleWJets)/WInt;

	      //WJETS MODELING
	      // Part 1: create pseudoData histogram
	      channel = "DataModelSR2";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DataModelSR2 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);

	      // Part 1: create pseudoData histogram
	      channel = "EWKMCSR2Model";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * EWKMCSR2 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);

	      EWKMCSR2 ->Add( HistoCollection[observable]["WJetsSR2"][systUpDown][lepton+charge],scaleWJets);
	      EWKMCSR2 ->Add( HistoCollection[observable]["ZJetsSR2"][systUpDown][lepton+charge],scaleWJets);
	      EWKMCSR2 -> Smooth();
	      
	      channel = "EWKMCSR1Model";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * EWKMCSR1 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
	      
	      EWKMCSR1 ->Add( HistoCollection[observable]["WJetsSR1"][systUpDown][lepton+charge],scaleWJets);
	      EWKMCSR1 ->Add( HistoCollection[observable]["ZJetsSR1"][systUpDown][lepton+charge],scaleWJets);
	      EWKMCSR1 ->Smooth();
	      
	      DataModelSR2 ->Add( HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge]);
	      DataModelSR2 ->Add( HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge]);
	      
	      //	      DataModelSR2 ->Add( HistoCollection[observable]["WWSR2"][systUpDown][lepton+charge]);
	      //	      DataModelSR2 ->Add( HistoCollection[observable]["WZSR2"][systUpDown][lepton+charge]);
	      
	      DataModelSR2 ->Add( EWKMCSR2);
	      
	      
	      channel = "DataModelSR1";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DataModelSR1 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
	      
	      
	      DataModelSR1 ->Add( HistoCollection[observable]["SignalSR1"][systUpDown][lepton+charge]);
	      DataModelSR1 ->Add( HistoCollection[observable]["TopSR1"][systUpDown][lepton+charge]);
	      

	      //DataModelSR1 ->Add( HistoCollection[observable]["WWSR1"][systUpDown][lepton+charge]);
	      //DataModelSR1 ->Add( HistoCollection[observable]["WZSR1"][systUpDown][lepton+charge]);

	      DataModelSR1 ->Add( EWKMCSR1);


	      channel = "DataModelIsoSR1";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DataModelIsoSR1 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
	      
	      DataModelIsoSR1 ->Add( HistoCollection[observable]["SignalSR1"][systUpDown][lepton+charge]);
	      DataModelIsoSR1 ->Add( HistoCollection[observable]["TopSR1"][systUpDown][lepton+charge]);

	      DataModelIsoSR1 ->Add( EWKMCSR2,EWKMCSR1->Integral()/EWKMCSR2->Integral());
	      
	      
	      if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
				   observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh") ){
		nbinstemp = nbinseleeta[observable];
	      }
	      
	      
	    
	      channel = "TmpModel";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * TmpModel =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
	      TmpModel->Sumw2();
	      
	      double nentriesSR2 = DataModelSR2->Integral();
	      double nentriesSR1 = DataModelSR1->Integral();
	      
	      channel = "KSDistribution";
	      

	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * KSDistribution =  new TH1D( (histoname).c_str(), (histoname).c_str(),200,0,1);
	      
	      channel = "DiffDistribution";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DiffDistribution =  new TH1D( (histoname).c_str(), (histoname).c_str(),200,0,100);
	      DiffDistribution->Sumw2();
	      
	      ///TTBAR MODELING
	      channel = "DataModel3J2TSR2";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DataModel3J2TSR2 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);

	      DataModel3J2TSR2 ->Add( HistoCollection[observable]["TTBar3J2TSR2"][systUpDown][lepton+charge]);
	      if(addsignaltop){
		DataModel3J2TSR2 ->Add( HistoCollection[observable]["TChannel3J2TSR2"][systUpDown][lepton+charge]);
		DataModel3J2TSR2 ->Add( HistoCollection[observable]["TbarChannel3J2TSR2"][systUpDown][lepton+charge]);
	      }
	      else DataModel3J2TSR2 ->Add( HistoCollection[observable]["TbarChannel3J2TSR2"][systUpDown][lepton+charge],3.32);
	      DataModel3J2TSR2 ->Add( HistoCollection[observable]["TWChannel3J2TSR2"][systUpDown][lepton+charge]);
	      DataModel3J2TSR2 ->Add( HistoCollection[observable]["TbarWChannel3J2TSR2"][systUpDown][lepton+charge]);
	      
	      channel = "DataModel3J2TSR1";
	      histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
	      TH1D * DataModel3J2TSR1 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);

	      DataModel3J2TSR1 ->Add( HistoCollection[observable]["TTBar3J2TSR1"][systUpDown][lepton+charge]);
	      if(addsignaltop){
		DataModel3J2TSR1 ->Add( HistoCollection[observable]["TChannel3J2TSR1"][systUpDown][lepton+charge],1.);
	        DataModel3J2TSR1 ->Add( HistoCollection[observable]["TbarChannel3J2TSR1"][systUpDown][lepton+charge],1.);
	      }
	      else DataModel3J2TSR1 ->Add( HistoCollection[observable]["TbarChannel3J2TSR1"][systUpDown][lepton+charge],3.32);
	      DataModel3J2TSR1 ->Add( HistoCollection[observable]["TbarWChannel3J2TSR1"][systUpDown][lepton+charge]);
	      DataModel3J2TSR1 ->Add( HistoCollection[observable]["TWChannel3J2TSR1"][systUpDown][lepton+charge]);
	      
	      double lumiMult = 1.;
	      
	      //for (int ps =0; ps< 10 ;++ps){
	      for (int ps =0; ps< 3500;++ps){
		
		
		stringstream number;
		number << ps;
		string numberstring;
		number >> numberstring; 
		
		channel = "ModelEwk"+numberstring;
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
		TH1D * ModelEWK =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		ModelEWK->Sumw2();
		bool isInvariant = observable == "eta";

		cout << " iteration # "<< ps << " file: " << histoname<<endl;
		  
		TmpModel->Reset("ICES");
		
		
		TmpModel->FillRandom(EWKMCSR2,
				     EWKMCSR2->Integral()
				     *lumiMult);
		
		TmpModel->FillRandom(HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge],
				     HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge]->Integral()
				     *lumiMult);
		
		TmpModel->FillRandom(HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge],
				     HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge]->Integral()
				     *lumiMult);
		
		
		ModelEWK->Add(TmpModel);
		HistoAdd(ModelEWK,HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge],-1*lumiMult,0,5);
		HistoAdd(ModelEWK,HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge],-1*lumiMult,0,5);
		
		ModelEWK->Scale(EWKMCSR1->Integral()/ModelEWK->Integral());
		
		
		ModelEWK->Smooth();
		ModelEWK->Write();
		
		delete ModelEWK;

		TmpModel->Reset("ICES");

		channel = "TmpTopSR1"+numberstring;
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
		TH1D * TmpTopSR1 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		TmpTopSR1->Sumw2();
		TmpTopSR1->Add( HistoCollection[observable]["TopSR1"][systUpDown][lepton+charge]);		
		

		channel = "TmpTopSR2"+numberstring;
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
		TH1D * TmpTopSR2 =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		TmpTopSR2->Sumw2();
		TmpTopSR2 ->Add( HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge]);		

		channel = "ModelTop"+numberstring;
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
		TH1D * ModelTop =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		ModelTop->Sumw2();

		

		channel = "ModelEwkTop"+numberstring;
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;	      
		TH1D * ModelEwkTop =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		ModelEwkTop->Sumw2();
		
		TmpModel->FillRandom(DataModel3J2TSR1,DataModel3J2TSR1->Integral());
		ModelTop->Add((TH1D*)(remodelLimits(TmpTopSR1,
						    DataModel3J2TSR1,
						    TmpModel,false,"tmp",0, limit))
			      );
		ModelTop->Write();  
		//		cout << "test loop 1" << endl;
		TmpModel->Reset("ICES");
		TmpModel->FillRandom(DataModel3J2TSR2,DataModel3J2TSR2->Integral());
		ModelEwkTop->FillRandom(DataModelSR2,DataModelSR2->Integral()); 
		//		ModelEwkTop->Add(DataModelSR2); 
		ModelEwkTop->Add((TH1D*)(remodelLimits(TmpTopSR2,
						       DataModel3J2TSR2,
						       TmpModel,false,"tmp",0, limit2)),-1);
		//		cout << "test loop 1" << endl;
		ModelEwkTop->Add(HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge],-1);
				 

		//		cout << "test loop 1" << endl;
		
		ModelEwkTop->Scale(EWKMCSR1->Integral()/ModelEwkTop->Integral());

		//		cout << "test loop 1" << endl;
		
		ModelEwkTop->Smooth();
		ModelEwkTop->Write();

		//KSDistribution->Write();
		//DiffDistribution->Write();
	      }
	      

	      DataModelSR1->Write();
	      DataModelSR2->Write();
	      DataModelIsoSR1->Write();

	      HistoCollection[observable]["SignalSR2"][systUpDown][lepton+charge]->Write();
	      HistoCollection[observable]["TopSR2"][systUpDown][lepton+charge]->Write();
	      HistoCollection[observable]["SignalSR1"][systUpDown][lepton+charge]->Write();
	      HistoCollection[observable]["TopSR1"][systUpDown][lepton+charge]->Write();
	      EWKMCSR2->Write();
	      EWKMCSR1->Write();

	    }
	    }
	    
	    
	  }
	}
      }
    }
    outputkstests.Close();

  }
  
  
  





  if(doMCStatUnc){
    TFile outputmcstats(("Test_File_MCStats"+postfix_file+".root").c_str(),"RECREATE");
    
    
    for(std::vector<string>::const_iterator it_s = systematics_total.begin(); it_s != systematics_total.end(); ++it_s){
      string syst = (*it_s);
      int n_syst_extremes=2;
      if(syst != "noSyst" )continue;
      if(syst == "noSyst")n_syst_extremes=1; 
      for (int ud = 0;ud<n_syst_extremes;++ud){
	string updown = UpDown[ud];
	if(syst =="noSyst")updown ="";
	string systUpDown = syst + updown;
	for(std::vector<string>::const_iterator it_o = observables.begin(); it_o != observables.end(); ++it_o){
	  string observable = (*it_o);
	  if(observable != "eta" ) continue;
	  for(std::vector<string>::const_iterator it_sam = samples.begin(); it_sam != samples.end(); ++it_sam){
	    string sample = (*it_sam);
	    if(sample != "SR1") continue;
	    //	  if(  ( sample != "SR1" && sample !=  "SR2") &&
	    //  ( observable == "etaTUp" || observable == "etaTDown" ||
	    //	 observable == "etaTTUp" || observable == "etaTTDown"
	    //	 )
	    //  ) continue;
	    //if(observable == "etaCosthetalj")continue; 
	    //if(observable == "etaTopMass" && sample != "")continue; 
	    for (int lep = 0; lep <2;++lep){
	      string lepton = leptons[lep]; if(lepton != leptonCase)continue;
	      //Fill the histograms    
	      //		  string name = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+"_"+charge;
	      //string histoname = name;
	      //HistoCollection[observable][channel+sample][systUpDown][lepton+charge]->cd();
	      std::string  chargesAll[3] = {"","Plus","Minus"};
	      for (int cha = 0; cha < 3; ++cha){
		string charge = chargesAll[cha];
		
		string channel = "Signal";
		string histoname ="";
		
		int nbinstemp = nbins[observable];
		
		if(lepton=="Ele" && (observable == "eta" || observable == "etaTUp" || observable == "etaTDown" ||
				     observable == "etaCosthetalj" || observable == "etaTTUp" || observable == "etaTTDown" || observable == "etaLow" || observable == "etaHigh") ){
		  nbinstemp = nbinseleeta[observable];
		}
		
		channel = "TmpModel";
		histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+charge;	      
		TH1D * TmpModel =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		TmpModel->Sumw2();
		
		double nentriesSR2 =   HistoCollection[observable]["DataSR2"][systUpDown][lepton+charge]->Integral(); 
		double nentriesSR1 =   HistoCollection[observable]["DataSR1"][systUpDown][lepton+charge]->Integral(); 
		
		
		double lumiMult = 1.;
	      
		//for (int ps =0; ps< 10 ;++ps){
		for (int ps =0; ps< 10000;++ps){
		  
		  stringstream number;
		  number << ps;
		  string numberstring;
		  number >> numberstring; 
		  
		  
		  //TTBar Top MC Stats:
		  channel = "ModelTopTTBar"+numberstring;
		  histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+charge;	      
		  TH1D * ModelTopTTBar =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		  ModelTopTTBar->Sumw2();
		  
		  TmpModel->Reset("ICES");
		  
		  
		  TmpModel->Reset("ICES");
		  TmpModel->FillRandom(HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge],
				       rand.Poisson(HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  TmpModel->Scale((HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge]->Integral()/
				   HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  ModelTopTTBar->Add(TmpModel);
		  ModelTopTTBar->Add(HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["SChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["SbarChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["WWSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["WZSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Add(HistoCollection[observable]["ZZSR1"][systUpDown][lepton+charge]);
		  ModelTopTTBar->Write();
		  
		  //TWChannel Top MC Stats:
		  
		  channel = "ModelTopTWChannel"+numberstring;
		  histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+charge;	      
		  TH1D * ModelTopTWChannel =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		  ModelTopTWChannel->Sumw2();
		  
		  TmpModel->Reset("ICES");
		  TmpModel->FillRandom(HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge],
				       rand.Poisson(HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  TmpModel->FillRandom(HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge],
				       rand.Poisson(HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  TmpModel->Scale((HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge]->Integral()+
				   HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge]->Integral())/
				  (HistoCollection[observable]["TWChannelSR1"][systUpDown][lepton+charge]->GetEntries()+
				   HistoCollection[observable]["TbarWChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  ModelTopTWChannel->Add(TmpModel);
		  ModelTopTWChannel->Add(HistoCollection[observable]["TTBarSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Add(HistoCollection[observable]["SChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Add(HistoCollection[observable]["SbarChannelSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Add(HistoCollection[observable]["WWSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Add(HistoCollection[observable]["WZSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Add(HistoCollection[observable]["ZZSR1"][systUpDown][lepton+charge]);
		  ModelTopTWChannel->Write();
		
		  //Signal MC Stats:
		  
		  channel = "ModelSignal"+numberstring;
		  histoname = observable+"_"+channel+sample+"_"+systUpDown+"_"+lepton+charge;	      
		  TH1D * ModelSignal =  new TH1D( (histoname).c_str(), (histoname).c_str(),nbinstemp,minobs[observable],maxobs[observable]);
		  ModelSignal->Sumw2();
		  
		  TmpModel->Reset("ICES");
		  TmpModel->FillRandom(HistoCollection[observable]["TChannelSR1"][systUpDown][lepton+charge],
				       rand.Poisson(HistoCollection[observable]["TChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  TmpModel->FillRandom(HistoCollection[observable]["TbarChannelSR1"][systUpDown][lepton+charge],
				       rand.Poisson(HistoCollection[observable]["TbarChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  TmpModel->Scale((HistoCollection[observable]["TChannelSR1"][systUpDown][lepton+charge]->Integral()+
				   HistoCollection[observable]["TbarChannelSR1"][systUpDown][lepton+charge]->Integral())/
				  (HistoCollection[observable]["TChannelSR1"][systUpDown][lepton+charge]->GetEntries()+
				   HistoCollection[observable]["TbarChannelSR1"][systUpDown][lepton+charge]->GetEntries()));
		  
		  ModelSignal->Add(TmpModel);
		  ModelSignal->Write();
		  
		}	      
	      }
	      
	    }
	  }
	}
      }
    }
    
    
    outputmcstats.Close();
  }
}

TH1D * makeproduct(TH1D * hA,TH1D* hB, int rebinA = 1, int rebinB=1,double integral = -1.){

  //Make temporary histos to rebin
  //  TH1D *hA = (TH1D*)h_A->Clone("hA");
  // TH1D *hB = (TH1D*)h_B->Clone("hB");

  //  hA->Rebin(rebinA);
  // hB->Rebin(rebinB);
  
  //get nbins from new histos
  int nbinsA = hA->GetNbinsX();
  int nbinsB = hA->GetNbinsX();
  double min = hA->GetBinLowEdge(1)*hB->GetBinLowEdge(1);
  double max = hA->GetBinLowEdge(nbinsA+1)*hB->GetBinLowEdge(nbinsB+1);
  //Get the actual name from the original histograms 
  string name =(string)(hA->GetName()) +"_vs_"+ (string)(hB->GetName());
  
  //Initialize histogram 
  TH1D * result = new TH1D(name.c_str(),name.c_str(),nbinsA*nbinsB,min,max);
  //Fill histogram
  for(int i =1; i<= nbinsA;++i){
    for(int j =1; j<= nbinsB;++j){
      double value = hA->GetBinContent(i)*hB->GetBinContent(j);
      int k = ((i-1)*nbinsB)+j;
      result->SetBinContent(k,value);
    }
  }
  if( integral <= 0.)integral = hB->Integral()/result->Integral();
  else integral = integral / result->Integral();
  result->Scale(integral);
  return result;

}



TH1D * makeproduct(TH2D * h){

  //Make temporary histos to rebin
  //  TH1D *hA = (TH1D*)h_A->Clone("hA");
  // TH1D *hB = (TH1D*)h_B->Clone("hB");

  //  hA->Rebin(rebinA);
  // hB->Rebin(rebinB);
  
  //get nbins from new histos
  int nbinsA = h->GetNbinsX();
  int nbinsB = h->GetNbinsY();
  double min = h->GetXaxis()->GetBinLowEdge(1)*h->GetYaxis()->GetBinLowEdge(1);
  double max = h->GetXaxis()->GetBinLowEdge(nbinsA+1)*h->GetYaxis()->GetBinLowEdge(nbinsB+1);
  //Get the actual name from the original histograms 
  string name = (string)(h->GetName()) + "_1D";
  
  //Initialize histogram 
  TH1D * result = new TH1D(name.c_str(),name.c_str(),nbinsA*nbinsB,min,max);
  //Fill histogram
  for(int i =1; i<= nbinsA;++i){
    for(int j =1; j<= nbinsB;++j){
      double value = h->GetBinContent(i,j);
      int k = ((i-1)*nbinsB)+j;
      result->SetBinContent(k,value);
    }
  }
  //  if( integral <= 0.)integral = hA->Integral()/result->Integral();
  //else integral = integral / result->Integral();
  //result->Scale(integral);
  return result;

}

double lumiFormula(string lepton , double lumiA,double effA,double lumiB,double effB,double lumiC, double effC, double lumiD, double effD, string syst, double  leptonPtV=30, double leptonEtaV = 0)
{ 
  double errA=0.,errB=0.,errC=0., errD=0., effEle=1.;  
  if (syst == "MuonTrigUp"){
    if ( leptonEtaV > -2.1 && leptonEtaV < -1.2) {errA = 0.0014; errB = 0.0006;}
    if ( leptonEtaV > -1.2 && leptonEtaV < -.9) {errA = 0.002; errB = 0.0008;}
    if ( leptonEtaV > -.9 && leptonEtaV < .9) {errA = 0.0008; errB = 0.0003;}
    if ( leptonEtaV > .9 && leptonEtaV < 1.2) {errA = 0.002; errB = 0.0008;}
    if ( leptonEtaV > 1.2 && leptonEtaV < 2.1) {errA = 0.0014; errB = 0.0006;}
    //    errA += 0.05;
    //errB += 0.05;
  }
  if (syst == "MuonTrigDown"){
    if ( leptonEtaV > -2.1 && leptonEtaV < -1.2) {errA = 0.0014; errB = 0.0006;}
    if ( leptonEtaV > -1.2 && leptonEtaV < -.9) {errA = 0.002; errB = 0.0008;}
    if ( leptonEtaV > -.9 && leptonEtaV < .9) {errA = 0.0008; errB = 0.0003;}
    if ( leptonEtaV > .9 && leptonEtaV < 1.2) {errA = 0.002; errB = 0.0008;}
    if ( leptonEtaV > 1.2 && leptonEtaV < 2.1) {errA = 0.0014; errB = 0.0006;}
    //    errA += 0.05;
    // errB += 0.05;
    errA*=-1.;
    errB*=-1.;
  }

  double effEleFunc(double ptV,double etaV,string systV);

  if(lepton == "Ele")  {
    effEle = effEleFunc (leptonPtV,leptonEtaV,syst);

    errA = 0.; 
    errB = 0.; 
    errC = 0.; 
    errD = 0.; 
    if(syst=="EleEffUp" ){
    errA = 0.05; 
    errB = 0.05; 
    errC = 0.05; 
    errD = 0.05; 
    }
    if(syst=="EleEffDown" ){
    errA = -0.05; 
    errB = -0.05; 
    errC = -0.05; 
    errD = -0.05; 
    }
    return lumiA*(effEle+errA)+lumiB*(effEle+errB)+lumiC*(effEle+errC)+lumiD*(effEle+errD);
  }
 if(lepton == "Mu")  {
   //    errA = 0.; 
   // errB = 0.; 
   // errC = 0.; 
   //   return lumiA*(effA+errA)+lumiB*(effB+errB)+lumiC*(effC+errC)+lumiD*(effD+errD);
   return lumiA*(1.)+lumiB*(1.)+lumiC*(1.)+lumiD*(1.);
 }
 return lumiA*(1.)+lumiB*(1.)+lumiC*(1.)+lumiD*(1.);
}

double effEleFunc(double pt,double eta,string syst){
 double sftrig= 0.99;
 double sfid= 0.98;
 double sfreco= 1.0;
 double sftriger= 0.0;
 double sfider= 0.0;
 double sfrecoer= 0.0;
 if(pt >=30 && pt < 35){
   if(-2.1<=eta && eta <-1.6){sftrig = 0.989062;sftriger =0.00141368   ; }
   if(-1.6<=eta && eta <-1.1){sftrig = 0.987835;sftriger =0.00121059   ; }
   if(-1.1<=eta && eta <-0.6){sftrig = 0.984765;sftriger =0.00117522   ; }
   if(-0.6<=eta && eta <-0.0){sftrig = 0.981268;sftriger =0.000988635  ; }
   if( 0.0<=eta && eta < 0.6){sftrig = 0.983171;sftriger =0.000997546  ; }
   if( 0.6<=eta && eta < 1.1){sftrig = 0.983146;sftriger =0.00118751   ; }
   if( 1.1<=eta && eta < 1.6){sftrig = 0.986583;sftriger =0.00123939   ; }
   if( 1.6<=eta && eta < 2.1){sftrig = 0.993016;sftriger =0.00122839   ; }
 }
 if(pt >=35 && pt < 40){
   if(-2.1<=eta && eta <-1.6){sftrig = 0.988702;sftriger =0.00114603   ; }
   if(-1.6<=eta && eta <-1.1){sftrig = 0.990297;sftriger =0.000956127  ; }
   if(-1.1<=eta && eta <-0.6){sftrig = 0.986939;sftriger =0.000855906  ; }
   if(-0.6<=eta && eta <-0.0){sftrig = 0.982691;sftriger =0.000741062  ; }
   if( 0.0<=eta && eta < 0.6){sftrig = 0.984768;sftriger =0.000753641  ; }
   if( 0.6<=eta && eta < 1.1){sftrig = 0.984567;sftriger =0.000861764  ; }
   if( 1.1<=eta && eta < 1.6){sftrig = 0.986809;sftriger =0.000967982  ; }
   if( 1.6<=eta && eta < 2.1){sftrig = 0.995036;sftriger =0.00101816   ; }
 }
 if(pt >=40 && pt < 45){
  if(-2.1<=eta && eta <-1.6){sftrig = 0.991409;sftriger =0.000947468  ; }
   if(-1.6<=eta && eta <-1.1){sftrig = 0.989089;sftriger =0.000705058  ; }
   if(-1.1<=eta && eta <-0.6){sftrig = 0.987819;sftriger =0.000663464  ; }
   if(-0.6<=eta && eta <-0.0){sftrig = 0.985332;sftriger =0.000600541  ; }
   if( 0.0<=eta && eta < 0.6){sftrig = 0.985551;sftriger =0.000615471  ; }
   if( 0.6<=eta && eta < 1.1){sftrig = 0.987195;sftriger =0.000673514  ; }
   if( 1.1<=eta && eta < 1.6){sftrig = 0.989049;sftriger =0.000733722  ; }
   if( 1.6<=eta && eta < 2.1){sftrig = 0.9951;sftriger =0.000838775  ; }
 }
 if(pt >=45 && pt < 50){
   if(-2.1<=eta && eta <-1.6){sftrig = 0.991881;sftriger =0.00109244   ; }
   if(-1.6<=eta && eta <-1.1){sftrig = 0.989007;sftriger =0.000812227  ; }
   if(-1.1<=eta && eta <-0.6){sftrig = 0.987216;sftriger =0.000770513  ; }
   if(-0.6<=eta && eta <-0.0){sftrig = 0.984945;sftriger =0.00071185  ; }
   if( 0.0<=eta && eta < 0.6){sftrig = 0.985056;sftriger =0.000723386  ; }
   if( 0.6<=eta && eta < 1.1){sftrig = 0.986666;sftriger =0.000789165  ; }
   if( 1.1<=eta && eta < 1.6){sftrig = 0.990323;sftriger =0.000847027  ; }
   if( 1.6<=eta && eta < 2.1){sftrig = 0.994158;sftriger =0.000958576  ; }

 }
 if(pt >=50){
  if(-2.1<=eta && eta <-1.6){sftrig = 0.988035;sftriger =0.00124571  ; }
   if(-1.6<=eta && eta <-1.1){sftrig = 0.988703;sftriger =0.000921444  ; }
   if(-1.1<=eta && eta <-0.6){sftrig = 0.985338;sftriger =0.000839093  ; }
   if(-0.6<=eta && eta <-0.0){sftrig = 0.983292;sftriger =0.000742061  ; }
   if( 0.0<=eta && eta < 0.6){sftrig = 0.985067;sftriger =0.000760872  ; }
   if( 0.6<=eta && eta < 1.1){sftrig = 0.986415;sftriger =0.000872319  ; }
   if( 1.1<=eta && eta < 1.6){sftrig = 0.989783;sftriger =0.000959948  ; }
   if( 1.6<=eta && eta < 2.1){sftrig = 0.991867;sftriger =0.00111345   ; }
 }

 if(pt >=30 && pt < 35){
  if(-2.5<=eta && eta <-1.5){sfreco = 0.999844;sfrecoer =0.00147098  ; }
  if(-1.5<=eta && eta <-0.0){sfreco = 1.0047;sfrecoer =0.00221326  ; }
  if( 0.0<=eta && eta < 1.5){sfreco = 1.00116;sfrecoer =0.000697562 ; }
  if( 1.5<=eta && eta < 2.5){sfreco = 1.00109;sfrecoer =0.00165322  ; }
 }
if(pt >=35 && pt < 40){
  if(-2.5<=eta && eta <-1.5){sfreco = 0.998171;sfrecoer =0.00151629  ; }
  if(-1.5<=eta && eta <-0.0){sfreco = 1.00047;sfrecoer =0.00024166  ; }
  if( 0.0<=eta && eta < 1.5){sfreco = 1.00086;sfrecoer =0.00030787  ; }
  if( 1.5<=eta && eta < 2.5){sfreco = 1.00219;sfrecoer =0.000784212 ; }
 }
 if(pt >=40 && pt < 45){
  if(-2.5<=eta && eta <-1.5){sfreco = 1.00278;sfrecoer =0.000638076 ; }
  if(-1.5<=eta && eta <-0.0){sfreco = 1.00027;sfrecoer =0.000111238 ; }
  if( 0.0<=eta && eta < 1.5){sfreco = 1.00104;sfrecoer =0.00121071  ; }
  if( 1.5<=eta && eta < 2.5){sfreco = 1.00091;sfrecoer =0.000732568 ; }
 }
 if(pt >=45 && pt < 50){
  if(-2.5<=eta && eta <-1.5){sfreco = 0.999239;sfrecoer =0.00177911  ; }
  if(-1.5<=eta && eta <-0.0){sfreco = 0.999929;sfrecoer =0.000148737 ; }
  if( 0.0<=eta && eta < 1.5){sfreco = 0.999773;sfrecoer =0.00053074  ; }
  if( 1.5<=eta && eta < 2.5){sfreco = 0.999630;sfrecoer =0.00062831  ; }
 }
 if(pt >=50 ){
  if(-2.5<=eta && eta <-1.5){sfreco = 1.00287 ; sfrecoer =0.00136664  ; }
  if(-1.5<=eta && eta <-0.0){sfreco = 0.999662; sfrecoer =0.000263808 ; }
  if( 0.0<=eta && eta < 1.5){sfreco = 1.0009 ; sfrecoer =0.000269709 ; }
  if( 1.5<=eta && eta < 2.5){sfreco = 0.999731; sfrecoer =0.0010418  ; }
 }
 
 if(pt >=30 && pt < 35){
  if(-2.5<=eta && eta <-1.5){sfid = 0.986469;sfider =0.00552111  ; }
  if(-1.5<=eta && eta <-0.0){sfid = 0.985757;sfider =0.00273467  ; }
  if( 0.0<=eta && eta < 1.5){sfid = 0.981332;sfider =0.00268003  ; }
  if( 1.5<=eta && eta < 2.5){sfid = 0.994782;sfider =0.00533201  ; }
 }
if(pt >=35 && pt < 40){
  if(-2.5<=eta && eta <-1.5){sfid = 0.983237;sfider =0.00365561  ; }
  if(-1.5<=eta && eta <-0.0){sfid = 0.985202;sfider =0.00165374  ; }
  if( 0.0<=eta && eta < 1.5){sfid = 0.987386;sfider =0.00165259  ; }
  if( 1.5<=eta && eta < 2.5){sfid = 0.993525;sfider =0.00361726  ; }
 }
 if(pt >=40 && pt < 45){
  if(-2.5<=eta && eta <-1.5){sfid = 0.978068;sfider =0.00164489  ; }
  if(-1.5<=eta && eta <-0.0){sfid = 0.988808;sfider =0.00121822  ; }
  if( 0.0<=eta && eta < 1.5){sfid = 0.987912;sfider =0.0297814   ; }
  if( 1.5<=eta && eta < 2.5){sfid = 0.984448;sfider =0.00104415  ; }
 }
 if(pt >=45 && pt < 50){
  if(-2.5<=eta && eta <-1.5){sfid = 0.995568;sfider =0.00321129  ; }
  if(-1.5<=eta && eta <-0.0){sfid = 0.995925;sfider =0.00144179  ; }
  if( 0.0<=eta && eta < 1.5){sfid = 0.993887;sfider =0.00137198  ; }
  if( 1.5<=eta && eta < 2.5){sfid = 0.989103;sfider =0.00312459  ; }
 }
 if(pt >=50 ){
  if(-2.5<=eta && eta <-1.5){sfid = 0.984346; sfider =0.00361527  ; }
  if(-1.5<=eta && eta <-0.0){sfid = 1.00066 ; sfider =0.00163875  ; }
  if( 0.0<=eta && eta < 1.5){sfid = 0.992773; sfider =0.0015875   ; }
  if( 1.5<=eta && eta < 2.5){sfid = 0.995026; sfider =0.00375975  ; }
 }
 
 double sign =1.0;
 
 if(syst=="EleEffUp" || syst == "EleEffDown"){
   if (syst == "EleEffDown") sign = -1.0;
   sftrig += sftriger*sign;
   sfid+= sfider*sign;
   sfreco += sfrecoer*sign;
   }
 
 return sftrig*sfid*sfreco;
 
}
//double lumiFormula(double Mu,double Ele,double ControlEle,double turnon,string lep){
//  if(lep==leptonCase)return Mu; 
//  if(lep=="Ele")return (turnon*Ele+ControlEle );//(Ele+ControlEle); 
//  return Mu;
//}

double setWeight(string channel, string syst, string lepton, string sample, double LumiC , double weight ){
  //  double scale =100000.;
  //  double scale =43.5/14.5;

    //  double reweight = 1;  
  
  
  double scale =1.;
  //  cout << " setweight xhannel "<< channel <<" _ "; 
    if (channel == "ZJets"){
      ;//      scale *= 6.28361204711711807e-02;
  }


  /*  if(lepton == "Ele" && channel != "Data"){
        
    
    //Selection eff SF
    scale*=1.;

    //Trigger eff SF
    scale *= 1.;

    //Lumi
    scale *= 1020;
      
  }
  if(lepton == leptonCase && channel != "Data"){
    //Lumi
    scale *= 1299;
  }
  */
  if(channel == "WW" || channel == "ZZ" || channel == "WZ"){
    if(syst== "VVUp")scale*=1.3;
    if(syst== "VVDown")scale*=0.7;
  }
  
  //  if(channel == "TTBar_Q2Down")scale*= 3701947./967055.;
  //if(channel == "TTBar_Q2Up")scale*= 3701947./930483.;

  if(channel == "TWChannel" || channel == "TbarWChannel"){
    if(syst== "TWChannelUp")scale*=1.3;
    if(syst== "TWChannelDown")scale*=0.7;
  }

  if(channel == "TTBar"){
    if(syst== "TTBarUp")scale*=1.1;
    if(syst== "TTBarDown")scale*=0.9;

  }
  
  if(channel == "SChannel" || channel == "SbarChannel"){
    if(syst== "SChannelUp")scale*=1.3;
    if(syst== "SChannelDown")scale*=0.7;
  }

  /*  if (channel == "WJets_wlight" || channel == "ZJets_wlight"){
    if (syst == "WLightUp")scale *= 1.2;
    else if (syst == "WLightDown")scale *=0.8;
    else scale *=1.;
    }*/
  
  //  cout<< "scale " << scale<< endl;
  double reweight = 1.;
  
  //  if( lepton == leptonCase) reweight = 0.936;//Trigger Eff
  if( lepton == "Mu") reweight = 1.;// - (368.88-179.35)/1496.275;//1.0e-06;
  //  if( lepton == "Ele") reweight =887.239/(887.239+191.091);

  //  if( channel == "WJets" )reweight*=148./143.;
  
  bool isData = (channel == "Data" || channel == "DataEleQCD" || channel == "DataEleControl" || channel == "DataMuControl");
    bool isControlRegion = (!isData && lepton == "Ele" && 
			  (sample == "WSample"      || sample == "AntiIsoWSample" 
			   || sample == "SampleB"   || sample == "AntiIsoSampleB"
			   ) );
    if( !isData
      )scale*=reweight*0.996;
  //   if( isControlRegion ) scale*=LumiC;
  

  return weight*scale;
}

double leptonWeight(string lepton, double eta , string channel, string syst ){
  double w =1;
  return w;
  if(channel == "Data")return w;
  if(lepton =="Mu" ) {
    w*= 0.9990;
    if (eta < 2.5 && eta >= 2.1) w*= 1.10386;
    if (eta < 2.1 && eta >= 1.65) w*= 1.05473;
    if (eta < 1.65 && eta >= 1.2) w*= 0.98812;
    if (eta < 1.2 && eta >= 0.9) w*= 0.98434;
    if (eta < 0.9 && eta >= 0.45) w*= 0.98242;
    if (eta < 0.45 && eta >= 0.0) w*= 0.97655;
    if (eta < 0.0 && eta >= -0.45) w*= 0.97456;
    if (eta < -0.45 && eta >= -0.9) w*= 0.97995;
    if (eta < -0.9 && eta >= -1.2) w*= 0.98055;
    if (eta < -1.2 && eta >= -1.65) w*= 0.99863;
    if (eta < -1.65 && eta >= -2.1) w*= 1.02777;
    if (eta < -2.1 && eta >= -2.5) w*= 1.04431;


    if(syst== "MuonTrigUp" || syst == "MuonTrigDown"){
      
      
      float signtrig = +1;
      float trigratio= (178.)/1299.;
      if(syst== "MuonTrigDown")signtrig=-1;
      w+=signtrig*0.03;
      if (eta < 2.5 && eta >= 2.1) w+= signtrig*0.15*(trigratio);
      if (eta < 2.1 && eta >= 1.65) w+= signtrig*0.01*trigratio;
      if (eta < 1.65 && eta >= 0.9) w+= signtrig*0.05*trigratio;
      if (eta < 0.9 && eta >= -0.9) w+= -signtrig*0.01*trigratio;
      if (eta < -0.9 && eta >= -1.65) w+= signtrig*0.05*trigratio;
      if (eta < -1.65 && eta >= -2.1) w+= signtrig*0.01*trigratio;
      if (eta < -2.1 && eta >= -2.5) w+= signtrig*0.15*trigratio;
    }
  }
  if(lepton == "Ele"){
    w*=1.;
    if(syst== "EleEffUp" || syst == "EleEffDown"){
      float signtrig = +1;
      if(syst== "EleEffDown")signtrig=-1;
      w+=signtrig*0.03;
    }
  }
    return w;
}

  //Old version: for refernce
  /*  TH2D * result = new TH2D;

  TH2D * interpolate(TH1D * ,TH1D * , unsigned int , double , double );
  
  result = interpolate(h1,h2,nbinsAlpha,min,max); 
  double integral = h1->Integral();
  if(integral == 0){
    cout<< "Warning! " << h1->GetTitle()<<" is a 0-integral histogram!!! Is it by purpose?  "<<endl; //Technically, one could want to morph the constant function = 0,s so I leave this option open, but of course no normalization is done.
    //return new TH2D("dummy","dummy",100,-1,1,nbinsAlpha,min, max);
    return result;
  }
  return  result;
}
  */

double renormalize(string observable,string channel,string sample,string syst,string lepton,string charge){
    return 1.
      ;  }



TH2D * interpolate(TH1D *h1,TH1D *h2, unsigned int nbinsAlpha, double min, double max, bool fraction = true) {
  
  //  cout << "interpolate 0 "<< h1->GetNbinsX()<<" - " << h2->GetNbinsX()<< endl;  

  if (h1->GetNbinsX() != h2->GetNbinsX()){
    cout<< "Error! histograms: " << h1->GetTitle()<<" and "<<h2->GetTitle()<<" have different number of bins! returning void histo "<<endl;
    return new TH2D("dummy","dummy",100,-1,1,nbinsAlpha,min, max);
  }

  unsigned int nbins = h1->GetNbinsX();
  //  double binwidth = (max-min)/(double)nbinsAlpha;
  double minX = h1->GetBinLowEdge(1);
  double maxX = h1->GetBinLowEdge(nbins+1);


  string title1 = h1->GetTitle();
  string title2 = h2->GetTitle();
  string title = title1+"_morph_" + title2;
  double y1 =-1,y2=-1, alpha = -1;
  double yextrap = -1; 


  TH2D *result = new TH2D(title.c_str(),title.c_str(),nbins,minX,maxX,nbinsAlpha,min,max);

  for(unsigned int i = 1; i <= nbins;++i){
    y1=h1->GetBinContent(i);
    y2=h2->GetBinContent(i);
    for(unsigned int j = 1; j<=nbinsAlpha; ++j){
      alpha = (double)(nbinsAlpha +1 - j)/(double)(nbinsAlpha);
      yextrap = alpha*y1+(1-alpha)*y2;
      
      if (fraction){//Return bias wrt y2 normalized to h2 integral. 
	yextrap -= y2;
	yextrap = yextrap/h2->Integral();
      }
      //alpha = j * (binwidth/2->);
      result->SetBinContent(i,j,yextrap);
    }
  }
  
  return result; 

}

TH3D * interpolate(TH2D *h1,TH2D *h2, unsigned int nbinsAlpha, double min, double max, bool fraction = true) {
  
  //  cout << "interpolate 0 "<< h1->GetNbinsX()<<" - " << h2->GetNbinsX()<< endl;  

  if (h1->GetNbinsX() != h2->GetNbinsX()){
    cout<< "Error! histograms: " << h1->GetTitle()<<" and "<<h2->GetTitle()<<" have different number of bins! returning void histo "<<endl;
    return new TH3D("dummy","dummy",100,-1,1,100,-1,1,nbinsAlpha,min, max);
  }

  unsigned int nbinsX = h1->GetNbinsX(),nbinsY=h1->GetNbinsY();
  //  double binwidth = (max-min)/(double)nbinsAlpha;
  double minX = h1->GetXaxis()->GetBinLowEdge(1);
  double maxX = h1->GetXaxis()->GetBinLowEdge(nbinsX+1);
  
  double minY = h1->GetYaxis()->GetBinLowEdge(1);
  double maxY = h1->GetYaxis()->GetBinLowEdge(nbinsY+1);
  

  string title1 = h1->GetTitle();
  string title2 = h2->GetTitle();
  string title = title1+"_morph_" + title2;
  double y1 =-1,y2=-1, alpha = -1;
  double yextrap = -1; 
  
  
  TH3D *result = new TH3D(title.c_str(),title.c_str(),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsAlpha,min,max);

  for(unsigned int i = 1; i <= nbinsX;++i){
    for(unsigned int k = 1; k <= nbinsY;++k){
      y1=h1->GetBinContent(i,k);
      y2=h2->GetBinContent(i,k);
      for(unsigned int j = 1; j<=nbinsAlpha; ++j){
	//	alpha = min + (max-min)*(double)(nbinsAlpha - j)/(double)(nbinsAlpha-1);
	alpha = (double)(nbinsAlpha +1 - j)/(double)(nbinsAlpha);
	yextrap = alpha*y1+(1-alpha)*y2;
	//yextrap = y2;//Debugging purposes
	
	if (fraction){//Return bias wrt y2 normalized to h2 integral. 
	  yextrap -= y2;
	  yextrap = yextrap/h2->Integral();
	}
	//alpha = j * (binwidth/2->);
	result->SetBinContent(i,k,j,yextrap);
      }
    }
  }
  
  return result; 

}


TH2D * getUpDownHistogram(TH2D* down,TH2D* up){

  if (down->GetNbinsX() != up->GetNbinsX()){
    cout<< "Error! histograms: " << down->GetTitle()<<" and "<<up->GetTitle()<<" have different number of bins! returning void histo "<<endl;
    return new TH2D("dummy","dummy",100,-1,1,100,-1,1);
  }
  
  string title = down->GetTitle();
  title = title + "_up_down";
  double y=-1;
  
  unsigned int nbinsdown = down->GetNbinsY(); 
  unsigned int nbinsup = up->GetNbinsY(); 
  double minAlpha = down->GetYaxis()->GetBinLowEdge(1);
  double maxAlpha = up->GetYaxis()->GetBinLowEdge(nbinsup+1);
  unsigned int nbinsAlpha = nbinsdown+nbinsup-1;//We do not want to double the central histogram, which is bin 0 for both!!! 
  //  cout << title << " min alpha " << minAlpha << " max alpha "  << maxAlpha<<endl;

  unsigned int nbinsX = up->GetNbinsX();
  double minX = down->GetXaxis()->GetBinLowEdge(1);
  double maxX = up->GetXaxis()->GetBinLowEdge(nbinsX+1);
  
  TH2D *result = new TH2D(title.c_str(),title.c_str(),nbinsX,minX,maxX,nbinsAlpha,minAlpha,maxAlpha);
  
  
  for(unsigned int i = 1; i <= nbinsX;++i){
    for(unsigned int j = 1; j<=nbinsAlpha; ++j){
      if(j<nbinsdown){//Don't take the last bin from the down histogram
	y=down->GetBinContent(i,j);
      }
      else{
	y=up->GetBinContent(i,j-nbinsdown+1);//Take the first bin from up histogram
      }
	//alpha = j * (binwidth/2->);
      result->SetBinContent(i,j,y);
    }
  }
      
  return result;
  
}


TH3D * getUpDownHistogram(TH3D* down,TH3D* up){
  
  if (down->GetNbinsX() != up->GetNbinsX()){
    cout<< "Error! histograms: " << down->GetTitle()<<" and "<<up->GetTitle()<<" have different number of bins! returning void histo "<<endl;
    return new TH3D("dummy","dummy",100,-1,1,100,-1,1,100,-1,1);
  }

  string title = down->GetTitle();
  title = title + "_up_down";
  double y=-1;
  
  
  unsigned int nbinsdown = down->GetNbinsZ(); 
  unsigned int nbinsup = up->GetNbinsZ(); 
  double minAlpha = down->GetZaxis()->GetBinLowEdge(1);
  double maxAlpha = up->GetZaxis()->GetBinLowEdge(nbinsup+1);
  unsigned int nbinsAlpha = nbinsdown+nbinsup-1;//We do not want to double the central histogram, which is bin 0 for both!!! 
  //  cout << title << " min alpha " << minAlpha << " max alpha "  << maxAlpha<<endl;

  unsigned int nbinsX = up->GetNbinsX();
  double minX = down->GetXaxis()->GetBinLowEdge(1);
  double maxX = up->GetXaxis()->GetBinLowEdge(nbinsX+1);

  unsigned int nbinsY = up->GetNbinsY();
  double minY = down->GetYaxis()->GetBinLowEdge(1);
  double maxY = up->GetYaxis()->GetBinLowEdge(nbinsY+1);
  
  TH3D *result = new TH3D(title.c_str(),title.c_str(),nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsAlpha,minAlpha,maxAlpha);
  
    
  for(unsigned int i = 1; i <= nbinsX;++i){
    for(unsigned int k = 1; k <= nbinsY;++k){
      for(unsigned int j = 1; j<=nbinsAlpha; ++j){
	if(j<nbinsdown){//Don't take the last bin from the down histogram
	  y=down->GetBinContent(i,k,j);
	}
	else{
	  y=up->GetBinContent(i,k,j-nbinsdown+1);//Take the first bin from up histogram
	}
	//alpha = j * (binwidth/2->);
	result->SetBinContent(i,k,j,y);
      }
    }
  }
      
  return result;
  
}

TH2D * make2D( TH1D* histoX,TH1D* histoY, double integral, string postfix = ""){

  //  cout<< "test 0"<<   endl;

  int nbinsX = histoX->GetNbinsX();
  float minX = histoX->GetBinLowEdge(1);
  float maxX = histoX->GetBinLowEdge(nbinsX+1);

  int nbinsY = histoY->GetNbinsX();
  float minY = histoY->GetBinLowEdge(1);
  float maxY = histoY->GetBinLowEdge(nbinsY+1);

  //  cout<< "test 1"<< endl;


  //int titleXSize = histoX->GetTitleSize(); 
  //int titleYSize = histoY->GetTitleSize(); 

  // char title[titleXSize+titleYSize] ;

  //  string title = *histoX->GetTitle()+*histoY->GetTitle();

  //  const char titleX[] = histoX->GetTitle(); 
  //  const char titleY[] = histoY->GetTitle(); 
  string titleX( histoX->GetTitle()); 
  string titleY( histoY->GetTitle()); 
  
  string title = titleX + titleY + postfix;
  
  //  sprintf(title,"%c_%c",*titleX,*titleY);
  
  //  cout<< "test title"<< title  << endl;
  //Product->SetTitle(title);
  //  Product->SetName(title);

  if(histoX->GetEntries()==0 || histoY->GetEntries()==0) return new TH2D(title.c_str(),"",nbinsX,minX,maxX,nbinsY,minY,maxY);
  
  TH2D * Product = new TH2D(title.c_str(),title.c_str(),nbinsX,minX,maxX,nbinsY,minY,maxY);
  
  float value =0;
 
  for (int i =1 ; i <= nbinsX; ++i){
    for (int j =1 ; j <= nbinsY; ++j){
      value = histoX->GetBinContent(i)*histoY->GetBinContent(j); 
      Product->SetBinContent(i,j,value);
    }
  } 
  //  cout<< "test integral before "<< Product->Integral()  << endl;
  Product->Scale(integral/Product->Integral());
  //  cout<< "test integral inside "<< integral  << endl;
  return Product;
}



double NormalizedIntegral(RooAbsPdf * function, RooRealVar& integrationVar, double lowerLimit, double upperLimit) {
  integrationVar.setRange("integralRange", lowerLimit, upperLimit) ;
  RooAbsReal* integral = (*function).createIntegral(integrationVar,NormSet(integrationVar), Range("integralRange")) ;
  double normalizedIntegralValue = integral->getVal();
  //printf("\nIntegrating %s from %f to %f\n", (*function).GetName(),lowerLimit, upperLimit);
  //printf("Integral value: %f\n", normalizedIntegralValue);
  return normalizedIntegralValue;
  }

//FIXME:to automatize 
double qcdintegralmap(string lepton, double integral=1.){
  double result=0.;
  if (lepton == "Mu" && integral !=0)return 20.2/integral;
  if (lepton == "Ele" && integral !=0)return 29.7/integral;

  return result;
}



TH1D* remodel(TH1D* histo, TH1D* preTag, TH1D* postTag, bool verbose =false, string postfix = "_remodeled"){
  //vector<float> binScale; 

  int nbins = histo->GetNbinsX();
  if(preTag->GetNbinsX() !=nbins || postTag->GetNbinsX() != nbins){ 
    cout<< " trying to remodel histograms with different number of bins ! will give random result! " << endl;
  }
  double integpre = preTag->Integral();
  double integpost = postTag->Integral();
  double valuepre = 1.;
  double valuepost = 1.;
  double valuetemp =0;
  double scale=1.;
  double min = histo->GetBinLowEdge(1);
  double max = histo->GetBinLowEdge(nbins+1);
  //  TCanvas *ctmp = new TCanvas("ctmp","ctmp");
  string a = (string)(histo->GetTitle()) + postfix;
  
  TH1D * result = new TH1D(a.c_str(),a.c_str(),nbins,min,max);
    
  //  histo->Draw();
    //  histo->SetLineColor(kGreen);
  //  if(verbose)  ctmp->SaveAs( (a+".eps").c_str());

  for (int i =1 ; i <= nbins; ++i){
    valuepre = preTag->GetBinContent(i)/integpre; 
    valuepost = postTag->GetBinContent(i)/integpost; 
    valuetemp = histo->GetBinContent(i);
    if( valuepre == 0 )  scale = 1; 
    else{ 
      if( valuepost == 0 )  scale = 1; 
      else scale = valuepost/valuepre;}
    if(valuepost/valuepre > 4){scale =1;cout<< " warning! bin " " one histogram had almost 0 content! using scale 1"<<endl;}
    //    if(valuepre!=0 && valuepost !=0)if(postTag->GetBinError(i)/postTag->GetBinContent(i)>0.3){scale =1;cout<< " warning! bin " " one histogram had almost 0 content! using scale 1"<<endl;}
    if(verbose)    cout << " bin " << i << " value " << valuetemp << " scale "<< scale << " finalvalue "<<scale*valuetemp<<  endl; 
    result->SetBinContent(i,scale*valuetemp);
  }
  return result;
  //  histo->Draw();
  //  histo->SetLineColor(kBlack);
  //  if(verbose)ctmp->SaveAs( (a+"_after_Modeling.eps").c_str());
  //  delete ctmp;
}




TH1D* remodelLimits(TH1D* histo, TH1D* preTag, TH1D* postTag, bool verbose =false, string postfix = "_remodeled",double m=-9999., double M=9999.){
  //vector<float> binScale; 

  int nbins = histo->GetNbinsX();
  if(preTag->GetNbinsX() !=nbins || postTag->GetNbinsX() != nbins){ 
    cout<< " trying to remodel histograms with different number of bins ! will give random result! " << endl;
  }
  
  int minBin = preTag->FindBin(m);
  int maxBin = preTag->FindBin(M);
  
  //double integpre = preTag->Integral(minBin,maxBin);  double integpost = postTag->Integral(minBin,maxBin);
  double integpre = preTag->Integral();  double integpost = postTag->Integral();

  double valuepre = 1.;
  double valuepost = 1.;
  double valuetemp =0;
  double scale=1.;
  double minH = histo->GetBinLowEdge(1);
  double maxH = histo->GetBinLowEdge(nbins+1);
  //  TCanvas *ctmp = new TCanvas("ctmp","ctmp");
  string a = (string)(histo->GetTitle()) + postfix;
  
  TH1D * result = new TH1D(a.c_str(),a.c_str(),nbins,minH,maxH);
    
  //  histo->Draw();
    //  histo->SetLineColor(kGreen);
  //  if(verbose)  ctmp->SaveAs( (a+".eps").c_str());

  for (int i =1 ; i <= nbins; ++i){
    valuepre = preTag->GetBinContent(i)/integpre; 
    valuepost = postTag->GetBinContent(i)/integpost; 
    //    valuepre = preTag->GetBinContent(i); 
    //valuepost = postTag->GetBinContent(i); 
    valuetemp = histo->GetBinContent(i);
    if (i < minBin || i> maxBin )scale=1;
    else{
    if( valuepre == 0 )  scale = 1; 
    else{ 
      if( valuepost == 0 )  scale = 1; 
      else scale = valuepost/valuepre;}
    if(valuepost/valuepre > 3){scale =1;cout<< " warning! bin " " one histogram had almost 0 content! using scale 1"<<endl;}
    if(valuepre!=0 && valuepost !=0)if(postTag->GetBinError(i)/postTag->GetBinContent(i)>1.1){scale =1;cout<< " warning! bin " " one histogram had almost 0 content! using scale 1"<<endl;}
    if(verbose)    cout << " bin " << i << " value " << valuetemp << " scale "<< scale << " finalvalue "<<scale*valuetemp<<  endl; 
    }
    result->SetBinContent(i,scale*valuetemp);
  }
  //  result->Scale(integpost/integpre);
  return result;
  //  histo->Draw();
  //  histo->SetLineColor(kBlack);
  //  if(verbose)ctmp->SaveAs( (a+"_after_Modeling.eps").c_str());
  //  delete ctmp;
}




TH1D* getRemodelFunction(TH1D* preTag, TH1D* postTag, bool verbose =false, string postfix = "_remodeled"){
  //vector<float> binScale; 

  int nbins = preTag->GetNbinsX();
  if(preTag->GetNbinsX() !=nbins || postTag->GetNbinsX() != nbins){ 
    cout<< " trying to remodel histograms with different number of bins ! will give random result! " << endl;
  }
  double integpre = preTag->Integral();
  double integpost = postTag->Integral();
  double valuepre = 1.;
  double valuepost = 1.;
  double valuetemp =0;
  double scale=1.;
  double min = preTag->GetBinLowEdge(1);
  double max = preTag->GetBinLowEdge(nbins+1);
  //  TCanvas *ctmp = new TCanvas("ctmp","ctmp");
  string a = (string)(preTag->GetTitle() )+ "_vs_" +(string)(postTag->GetTitle() ) + postfix;
  
  TH1D * result = new TH1D(a.c_str(),a.c_str(),nbins,min,max);
    
  //  histo->Draw();
    //  histo->SetLineColor(kGreen);
  //  if(verbose)  ctmp->SaveAs( (a+".eps").c_str());

  for (int i =1 ; i <= nbins; ++i){
    valuepre = preTag->GetBinContent(i)/integpre; 
    valuepost = postTag->GetBinContent(i)/integpost; 
    valuetemp = 1;//histo->GetBinContent(i);
    if( valuepre == 0 )  scale = 1; 
    else{ 
      if( valuepost == 0 )  scale = 1; 
      else scale = valuepost/valuepre;}
    if(valuepost/valuepre > 3){scale =1;cout<< " warning! bin " " one histogram had almost 0 content! using scale 1"<<endl;}
    if(verbose)    cout << " bin " << i << " value " << valuetemp << " scale "<< scale << " finalvalue "<<scale*valuetemp<<  endl; 
    result->SetBinContent(i,scale*valuetemp);
    //    result->SetBinError(i,scale*valuetemp*integpost*(sqrt(valuepost)*(1/integpost-valuepost/(integpost*integpost))*(1/integpost-valuepost/(integpost*integpost)))) ;
    if(postTag->GetBinContent(i)!=0)result->SetBinError(i,scale*valuetemp*( postTag->GetBinError(i)/postTag->GetBinContent(i) ));
  }
  return result;
  //  histo->Draw();
  //  histo->SetLineColor(kBlack);
  //  if(verbose)ctmp->SaveAs( (a+"_after_Modeling.eps").c_str());
  //  delete ctmp;
}


//Extrapolates bin by bin to shape to bincontent = b1 + value*(b2 -b1);
TH1D * LinearExtrapolation(TH1D * h1, TH1D* h2, double value){
  TH1D * result = new TH1D("linearextrap","linearextrap",h1->GetNbinsX(),h1->GetBinLowEdge(1),h1->GetBinLowEdge(h1->GetNbinsX()+1));
  
  for( int n =1; n <= h1->GetNbinsX();++n){
    double bin1 = h1->GetBinContent(n)/h1->Integral();
    double bin2 = h2->GetBinContent(n)/h2->Integral();
    
    double bincontent = bin1 + value*(bin2-bin1);
    //    If(h1->GetBinContent(n) < 5  || h2->GetBinContent(n)< 5) relativeFraction=1;

    //( verbose )cout << "value1 " << h1->GetBinContent(n) <<  " Integral1 "<< h1->Integral()<< 
    //  "value2 " << h2->GetBinContent(n) <<  " Integral2 "<< h2->Integral()<< 
    //  endl;

    result->SetBinContent(n,bincontent);
  }
  
  return result ;
}


void HistoAdd(TH1D* a,TH1D* b,double sf,double min,double max){
  //Add histogram "b" to histogram "a", between "min" and "max", with scale factor "sf".
    for(int i =1;i <= a->GetNbinsX();++i){
      if(a->GetBinLowEdge(i)>=min && a->GetBinLowEdge(i)<max){
	a->SetBinContent(i,a->GetBinContent(i)+b->GetBinContent(i)*sf);
	if(a->GetBinContent(i)<0.) a->SetBinContent(i,0.);
      }
    }
}


//  LocalWords:  systUpDown
