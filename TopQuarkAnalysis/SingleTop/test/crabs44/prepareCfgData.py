#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Original config file
#fileName = "Mu_2011A_08Nov_crab.cfg"
#fileName2 = "SingleTopData_Mu_2011A_08Nov_cfg.py"

fileName = "Ele_2011A_08Nov_crab.cfg"
fileName2 = "SingleTopData_Ele_2011A_08Nov_cfg.py"

#Channels to include
channels = [
#"Mu_2011A_08Nov",
#"MuHad_2011A_08Nov",
#"Mu_2011B_19Nov",
#"MuHad_2011B_19Nov",
"Ele_2011A_08Nov",
#"ElectronHad_2011A_08Nov",
"Ele_2011B_19Nov",
#"ElectronHad_2011B_19Nov",
#"Mu_Aug05",
#"MuHad_Aug05",
#"MuHad_v6",
#"Mu_v6",
#"Mu_2011B",
#"Ele_2011B",
#"MuHad_2011B",
#"EleHad_2011B",    
#"MuHad_Oct03",
#"Ele_May10",
#"EleHad_v4",
#"EleHad_Aug05",
#"EleHad_v6",
#"Ele_v6",
#"EleHad_Oct03",
  ]

#Path to take data merged files
dataPath = "file:/tmp/mmerola/"

#Choose if you want to run or just prepare the configuration files
mode = ""
#mode = "cmsRun"



#Implementation:

def datasetmap(channel):
    if channel == "TChannel":
        return "/T_TuneZ2_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"
    if channel == "TbarChannel":
        return "/Tbar_TuneZ2_t-channel_7TeV-powheg-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"

    if channel == "SChannel":
        return "/T_TuneZ2_s-channel_7TeV-powheg-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"
    if channel == "SbarChannel":
        return "/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"

    if channel == "TWChannel":
        return "/T_TuneZ2_tW-channel_7TeV-powheg-tauola-DS/Fall11-PU_S6_START42_V14B-v1/AODSIM"
    if channel == "TbarWChannel":
        return "/Tbar_TuneZ2_tW-channel_7TeV-powheg-tauola-DS/Fall11-PU_S6_START42_V14B-v1/AODSIM"

    if channel == "TTBar":
        return "/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v2/AODSIM"
    if channel == "WJets":
        return "/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"

    if channel == "Mu_v4":
        return "/SingleMu/Run2011A-PromptReco-v4/AOD"
    if channel == "Mu_May10":
        return "/SingleMu/Run2011A-May10ReReco-v1/AOD"
    if channel == "Mu_Aug05":
        return "/SingleMu/Run2011A-05Aug2011-v1/AOD"
    if channel == "MuHad_Aug05":
        return "/MuHad/Run2011A-05Aug2011-v1/AOD"
    if channel == "MuHad_Oct03":
        return "/MuHad/Run2011A-03Oct2011-v1/AOD"
    if channel == "MuHad_v6":
        return "/MuHad/Run2011A-PromptReco-v6/AOD"
    if channel == "Mu_v6":
        return "/SingleMu/Run2011A-PromptReco-v6/AOD"
    if channel == "Mu_2011B":
        return "/SingleMu/Run2011B-PromptReco-v1/AOD"
    if channel == "MuHad_2011B":
        return "/MuHad/Run2011B-PromptReco-v1/AOD"

    if channel == "Mu_2011A_08Nov":
        return "/SingleMu/Run2011A-08Nov2011-v1/AOD"
    if channel == "Mu_2011B_19Nov":
        return "/SingleMu/Run2011B-19Nov2011-v1/AOD"
    if channel == "MuHad_2011A_08Nov":
        return "/MuHad/Run2011A-08Nov2011-v1/AOD"
    if channel == "MuHad_2011B_19Nov":
        return "/MuHad/Run2011B-19Nov2011-v1/AOD"



    if channel == "Ele_May10":
        return "/SingleElectron/Run2011A-May10ReReco-v1/AOD"
    if channel == "EleHad_v4":
        return "/ElectronHad/Run2011A-PromptReco-v4/AOD"
    if channel == "EleHad_Aug05":
        return "/ElectronHad/Run2011A-05Aug2011-v1/AOD"
    if channel == "EleHad_Oct03":
        return "/ElectronHad/Run2011A-03Oct2011-v1/AOD"
    if channel == "EleHad_v6":
        return "/ElectronHad/Run2011A-PromptReco-v6/AOD"
    if channel == "Ele_v6":
        return "/SingleElectron/Run2011A-PromptReco-v6/AOD"
    if channel == "Ele_2011B":
        return "/SingleElectron/Run2011B-PromptReco-v1/AOD"
    if channel == "EleHad_2011B":
        return "/ElectronHad/Run2011B-PromptReco-v1/AOD"


    if channel == "Ele_2011A_08Nov":
        return "/SingleElectron/Run2011A-08Nov2011-v1/AOD"
    if channel == "Ele_2011B_19Nov":
        return "/SingleElectron/Run2011B-19Nov2011-v1/AOD"
    if channel == "ElectronHad_2011A_08Nov":
        return "/ElectronHad/Run2011A-08Nov2011-v1/AOD"
    if channel == "ElectronHad_2011B_19Nov":
        return "/ElectronHad/Run2011B-19Nov2011-v1/AOD"
    
    
    #        return "/W2Jets_TuneZ2_7TeV-madgraph-tauola/Fall11-PU_S6_START42_V14B-v1/AODSIM"

def entriesmap(channel):
    if channel == "TChannel" or channel == "TbarChannel" or channel == "TTBar" or channel == "TWChannel" or channel == "TbarWChannel" or channel == "SChannel" or channel == "SbarChannel":
        return 100000
    if channel == "WJets":
        return 300000
    if "May10" in channel:
        return 50
    if "_v4" in channel:
        return 100
    if "Aug05" in channel or "Oct03" in channel:
        return 100
    if "_v6" in channel:
        return 200
    if "_08Nov" in channel:
        return 200
    if "_19Nov" in channel:
        return 150
    
    
#    if "_2011B" in channel:
#        return 150


    
def lumi_maskmap(channel):
    if "May10" in channel:
        return "Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.txt"
    if "_v4" in channel or "_v6" in channel:  ##or "_2011B" in channel:
        return "Cert_160404-180252_7TeV_PromptReco_Collisions11_JSON.txt"
    if "Aug05" in channel:
        return "Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v3.txt"
    if "Nov" in channel:
        return "Cert_160404-180252_7TeV_ReRecoNov08_Collisions11_JSON_v2.txt"
            
    
#Function to replace a sequence of characters channelOld to channelNew in a file 
def changeChannel(fileName,channelOld,channelNew): 
    print " Channel test " + channelNew
    channelToReplace = channelNew
    file = open(fileName)
    #    print " file name " + fileName + " ; channel old " +channelOld
    lines = file.readlines()
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
            line = "events_per_job ="+ str(entriesmap(channelToReplace))+ "\n"
        if "lumis_per_job" in line and not "#lumis_per_job" in line :
            line = "lumis_per_job ="+ str(entriesmap(channelToReplace)) + "\n"
        if "lumi_mask" in line and not "#lumi_mask" in line:
            line = "lumi_mask = " + str(lumi_maskmap(channelToReplace)) +"\n"
        o.write(line)   
    o.close()
    return o

#Implementation of the loop part:

#Channel in the original file
startChannel = "Mu_2011A_08Nov"#channels[0]

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



