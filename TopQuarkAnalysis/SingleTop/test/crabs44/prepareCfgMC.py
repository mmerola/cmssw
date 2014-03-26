#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Original config file
fileName = "TChannelFall11_crab.cfg"
fileName2 = "SingleTopMC_TChannelFall11_cfg.py"
#fileName = "SingleTopSystematics_cfg.py"
#fileName = "SingleTopSystematics_split_cfg.py"
#fileName = "SingleTopNEvents_cfg.py"

#Channels to include
channels = [
#"QCD_Pt_20to30_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
#"QCD_Pt_20to30_BCtoE",
#"QCD_Pt_30to80_BCtoE",
#"QCD_Pt_80to170_BCtoE",
#"QCD_HT_40_100_GJets",
#"QCD_HT_100_200_GJets",
#"QCD_HT_200_inf_GJets",
#"WW",
"WZ",
"ZZ",
#"TTBar",
#"ZJets",
#"WJets",
#"TChannel",
#"TbarChannel",
#"TWChannel",
#"TbarWChannel",
#"SChannel",
#"SbarChannel",
#"QCDMu",
#"W2Jets",
#"W3Jets",
#"W4Jets",
#"W1Jet",
#"TChannelQ2up",
#"TbarChannelQ2up",
#"TChannelQ2down",
#"TbarChannelQ2down",
#"WJetsQ2up",
#"WJetsQ2down",
#"TTBarQ2up",
#"TTBarQ2down",
#"TTBarMatchingup",
#"TTBarMatchingdown",
  ]

#Path to take data merged files
dataPath = "file:/tmp/mmerola/"

#Choose if you want to run or just prepare the configuration files
mode = ""
#mode = "cmsRun"



#Implementation:

def datasetmap(channel):
    if channel == "TChannel":
        return "/T_TuneZ2_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TbarChannel":
        return "/Tbar_TuneZ2_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "SChannel":
        return "/T_TuneZ2_s-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "SbarChannel":
        return "/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "SChannelCompHep":
        return "/TToBLNu_TuneZ2_s-channel_7TeV-comphep/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "TWChannel":
        return "/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TbarWChannel":
        return "/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    
    if channel == "TWChannelDS":
        return "/T_TuneZ2_tW-channel-DS_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TbarWChannelDS":
        return "/Tbar_TuneZ2_tW-channel-DS_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"


    if channel == "TTBar":
        return "/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "WJets":
        return "/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "W1Jet":
        return "/W1Jet_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "W2Jets":
        return "/W2Jets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "W3Jets":
        return "/W3Jets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v2/AODSIM"
    if channel == "W4Jets":
        return "/W4Jets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"    

    if channel == "ZJets":
        return "/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "QCDMu":   
        return "/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    
    if channel == "WW":
        return "/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    
    if channel == "WZ":
        return "/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    
    if channel == "ZZ":
        return "/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "QCD_Pt_20to30_EMEnriched":
        return "/QCD_Pt-20to30_EMEnriched_TuneZ2_7TeV-pythia6/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_Pt_30to80_EMEnriched":
        return "/QCD_Pt-30to80_EMEnriched_TuneZ2_7TeV-pythia/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_Pt_80to170_EMEnriched":
        return "/QCD_Pt-80to170_EMEnriched_TuneZ2_7TeV-pythia6/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "QCD_Pt_20to30_BCtoE":
        return "/QCD_Pt-20to30_BCtoE_TuneZ2_7TeV-pythia6/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_Pt_30to80_BCtoE":
        return "/QCD_Pt-30to80_BCtoE_TuneZ2_7TeV-pythia6/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_Pt_80to170_BCtoE":
        return "/QCD_Pt-80to170_BCtoE_TuneZ2_7TeV-pythia/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    
    if channel == "QCD_HT_40_100_GJets":
        return "/GJets_TuneZ2_40_HT_100_7TeV-madgraph/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_HT_100_200_GJets":
        return "/GJets_TuneZ2_100_HT_200_7TeV-madgraph/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "QCD_HT_200_inf_GJets":
        return "/GJets_TuneZ2_200_HT_inf_7TeV-madgraph/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "TChannelQ2up":
        return "/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TbarChannelQ2up":
        return "/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TChannelQ2down":
        return "/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TbarChannelQ2down":
        return "/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"

    if channel == "WJetsQ2up":
        return "/WJetsToLNu_TuneZ2_scaleup_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "WJetsQ2down":
        return "/WJetsToLNu_TuneZ2_scaledown_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v1/AODSIM"
    if channel == "TTBarQ2up":
        return "/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v3/AODSIM"
    if channel == "TTBarQ2down":
        return "/TTjets_TuneZ2_scaledown_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v3/AODSIM"
    if channel == "TTBarMatchingup":
        return "/TTjets_TuneZ2_matchingup_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v3/AODSIM"
    if channel == "TTBarMatchingdown":
        return "/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/Fall11-PU_S6_START44_V9B-v3/AODSIM"



    

    
    if channel == "Mu_v4":
        return "/SingleMu/Run2011A-PromptReco-v4/AOD"
    if channel == "Mu_May10":
        return "/SingleMu/Run2011A-May10ReReco-v4/AOD"
    if channel == "Mu_Aug05":
        return "/SingleMu/Run2011A-05Aug2011-v1/AOD"
    if channel == "MuHad_Aug05":
        return "/MuHad/Run2011A-05Aug2011-v1/AOD"
    if channel == "MuHad_Oct03":
        return "/MuHad/Run2011A-03Oct2011-v1/AOD"

    if channel == "Ele_May10":
        return "/SingleElectron/Run2011A-May10ReReco-v4/AOD"
    if channel == "EleHad_v4":
        return "/ElectronHad/Run2011A-PromptReco-v4/AOD"
    if channel == "EleHad_Aug05":
        return "/ElectronHad/Run2011A-05Aug2011-v1/AOD"
    if channel == "EleHad_Oct03":
        return "/ElectronHad/Run2011A-03Oct2011-v1/AOD"


    #        return "/W2Jets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"

def entriesmap(channel):
    if channel == "TChannel" or channel == "TbarChannel" or channel == "TWChannel" or channel == "TbarWChannel" or channel == "SChannel" or channel == "SbarChannel" or channel == "W2Jets" or channel == "W3Jets" or channel == "W4Jets":
        return 100000 
    if channel == "WW" or channel == "WZ" or channel == "ZZ":
        return 10000
    if channel == "WJets"  or  channel == "ZJets" or channel == "QCDMu" or channel == "QCD_Pt_20to30_EMEnriched" or channel == "QCD_Pt_30to80_EMEnriched" or channel == "QCD_Pt_80to170_EMEnriched" :
        return 150000
    if "W1Jet" in channel:
        return 250000
    if "TTBar" in channel:
        return 200000
    else:
        return 100000

#Function to replace a sequence of characters channelOld to channelNew in a file 
def changeChannel(fileName,channelOld,channelNew): 
    print " Channel test " + channelNew
    channelToReplace = channelNew
    file = open(fileName)
    lines = file.readlines()
    #             channelNew+"_crab.cfg","w") 
    name = fileName.replace(channelOld,channelToReplace)
    print name
    o = open(name,"w")
    for line in lines:
        if "user_remote_dir" in line or "pset" in line or "output_file" in line or "ui_working_dir" or "ChannelName" in line:
            words = line.split()
            for word in words:
                if channelOld in word:  
                    line = line.replace(word,word.replace(channelOld,channelToReplace))
        if "datasetpath" in line and not "#datasetpath" in line:
            line = "datasetpath = " + datasetmap(channelNew) +"\n"
        if "events_per_job" in line and not "#events_per_job" in line :
            line = "events_per_job ="+ str(entriesmap(channelToReplace)) + "\n"
        if "lumis_per_job" in line and not "#lumis_per_job" in line :
            line = "lumis_per_job ="+ str(entriesmap(channelToReplace))
        o.write(line)   
    o.close()
    return o

#Implementation of the loop part:

#Channel in the original file
startChannel = "TChannel"#channels[0]

f= open(fileName)
f2= open(fileName2)

tmpName = "temp.py"
shutil.copy(fileName,tmpName)

for channel in channels:

    channelOld = startChannel
    
    cfg_file = changeChannel(fileName,channelOld,channel)
    pset_file = changeChannel(fileName2,channelOld,channel)

#    os.system("bg") 
#    os.system('rm '+channel+'_cfg.py' ) 

os.system('rm '+tmpName) 
#changeChannel(f,aChannel,startChannel)

#os.system(command)



