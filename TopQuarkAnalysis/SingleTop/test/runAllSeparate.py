#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil


#Original config file
fileName = "SingleTopSystematicsWithTrigger_cfg.py"
#fileName = "SingleTopPDFWithTrigger_cfg.py"
#fileName = "SingleTopSystematics_cfg.py"
#fileName = "SingleTopSystematics_split_cfg.py"
#fileName = "SingleTopNEvents_cfg.py"

nSimultaneous = 11


#Channels to include
channels = [
#  "Mu_2011A",
# "SChannel",
# "SbarChannel",
# "TWChannel",
# "TbarWChannel",
# "TbarChannel_Q2Up",
# "TbarChannel_Q2Down",
# "Ele_May10",
# "QCD_HT_40_100_GJets",
# "QCD_HT_100_200_GJets",
# "QCD_HT_200_inf_GJets",
#"QCD_Pt_30to80_BCtoE",
#"QCD_Pt_80to170_BCtoE",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
 "WW",
# "ZZ",
# "WZ",
#"ZJets_wbb_part_13",
#"ZJets_wlight_part_13",


#  "Mu_2011B_19Nov_part_1",
#  "Mu_2011B_19Nov_part_2",
#  "Mu_2011B_19Nov_part_3",
#  "Mu_2011B_19Nov_part_4",
#  "Mu_2011B_19Nov_part_5",
#  "Mu_2011B_19Nov_part_6",
#  "Mu_2011B_19Nov_part_7",
#  "Mu_2011B_19Nov_part_8",
#  "Mu_2011B_19Nov_part_9",
#  "Mu_2011B_19Nov_part_10",

#  "Mu_2011A_08Nov_part_1",
#  "Mu_2011A_08Nov_part_2",
#  "Mu_2011A_08Nov_part_3",
#  "Mu_2011A_08Nov_part_4",
#  "Mu_2011A_08Nov_part_5",
#  "Mu_2011A_08Nov_part_6",
#  "Mu_2011A_08Nov_part_7",
#  "Mu_2011A_08Nov_part_8",
#  "Mu_2011A_08Nov_part_9",
#  "Mu_2011A_08Nov_part_10",
#  "Mu_2011A_08Nov_part_11",
#  "Mu_2011A_08Nov_part_12",
#  "Mu_2011A_08Nov_part_13",
#  "Mu_2011A_08Nov_part_14",
#  "Mu_2011A_08Nov_part_15",
#  "Mu_2011A_08Nov_part_16",
#  "Mu_2011A_08Nov_part_17",
#  "Mu_2011A_08Nov_part_18",
#  "Mu_2011A_08Nov_part_19",
#  "Mu_2011A_08Nov_part_20",
  


#####
# "TChannel",
# "TbarChannel",
# "SChannel",
# "SbarChannel",
####
#"QCDMu_part_3",
#"QCDMu_part_4",
#"QCDMu_part_5",
#"QCDMu_part_6",
#"QCDMu_part_7",
######
#QCD_Pt_30to80_BCtoE",
## "QCD_Pt_20to30_BCtoE",
#QCD_Pt_80to170_BCtoE",
####cc###
# "QCD_Pt_20to30_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
#####
# "HT_100_200",
# "HT_40_100",
# "HT_200",
#####

#"QCDMu_part_1",
#"QCDMu_part_2",

# "TTBar_part_1",
# "TTBar_part_2",
# "TTBar_part_3",
# "TTBar_part_4",
# "TTBar_part_5",
 #"TTBar_part_6",
 #"TTBar_part_7",
 #"TTBar_part_8",
 #"TTBar_part_9",
 #"TTBar_part_10",

# "TChannel_part_1",
# "TChannel_part_2",
# "TChannel_part_3",
# "SChannel",
# "TbarChannel_part_1",
# "TbarChannel_part_2",
# "TbarChannel_part_3",
# "SbarChannel",
# "TWChannel",
# "TbarWChannel",

# "TTBarQ2up",
# "TTBarQ2down",

# "TTBarMatchingup_part_1",
# "TTBarMatchingup_part_2",
# "TTBarMatchingup_part_3",
# "TTBarMatchingup_part_4",
# "TTBarMatchingup_part_5",
# "TTBarMatchingdown_part_1",
# "TTBarMatchingdown_part_2",
# "TTBarMatchingdown_part_3",
# "TTBarMatchingdown_part_4",
# "TTBarMatchingdown_part_5",
 

#"WJetsQ2up_part_1",
#"WJetsQ2up_part_2",
#"WJetsQ2up_part_3",
#"WJetsQ2up_part_4",
#"WJetsQ2up_part_5",

#"WJetsQ2down_part_1",
#"WJetsQ2down_part_2",
#"WJetsQ2down_part_3",
#"WJetsQ2down_part_4",
#"WJetsQ2down_part_5",

#  "ZJets_part_1",
#  "ZJets_part_2",
#  "ZJets_part_3",
#  "ZJets_part_4",
#  "ZJets_part_5",
#  "ZJets_part_6",
#  "ZJets_part_7",
#  "ZJets_part_8",
#  "ZJets_part_9",
#  "ZJets_part_10",
#  "ZJets_part_11",
#  "ZJets_part_12",
#  "ZJets_part_13",
#  "ZJets_part_14",
#  "ZJets_part_15",
#  "ZJets_part_16",
#  "ZJets_part_17",
#  "ZJets_part_18",
#  "ZJets_part_19",
#  "ZJets_part_20",


    
#  "W1Jet_part_1",
#  "W1Jet_part_2",
#  "W1Jet_part_3",
#  "W1Jet_part_4",
#  "W1Jet_part_5",
#  "W1Jet_part_6",
#  "W1Jet_part_7",
#  "W1Jet_part_8",
#  "W1Jet_part_9",
#  "W1Jet_part_10",
#  "W1Jet_part_11",
#  "W1Jet_part_12",
#  "W1Jet_part_13",
#  "W1Jet_part_14",
#  "W1Jet_part_15",
#  "W1Jet_part_16",
#  "W1Jet_part_17",
#  "W1Jet_part_18",
#  "W1Jet_part_19",
#  "W1Jet_part_20",

#  "W2Jets_part_1",
#  "W2Jets_part_2",
#  "W2Jets_part_3",
#  "W2Jets_part_4",
#  "W2Jets_part_5",
#  "W2Jets_part_6",
#  "W2Jets_part_7",
#  "W2Jets_part_8",
#  "W2Jets_part_9",
#  "W2Jets_part_10",
#  "W2Jets_part_11",
#  "W2Jets_part_12",
#  "W2Jets_part_13",
#  "W2Jets_part_14",
#  "W2Jets_part_15",
#  "W2Jets_part_16",
#  "W2Jets_part_17",
#  "W2Jets_part_18",
#  "W2Jets_part_19",
#  "W2Jets_part_20",

#  "W3Jets_part_1",
#  "W3Jets_part_2",
#  "W3Jets_part_3",
#  "W3Jets_part_4",
#  "W3Jets_part_5",
#  "W3Jets_part_6",
#  "W3Jets_part_7",
#  "W3Jets_part_8",
#  "W3Jets_part_9",
#  "W3Jets_part_10",
#  "W3Jets_part_11",
#  "W3Jets_part_12",
#  "W3Jets_part_13",
#  "W3Jets_part_14",
#  "W3Jets_part_15",

#  "W4Jets_part_1",
#  "W4Jets_part_2",
#  "W4Jets_part_3",
#  "W4Jets_part_4",
#  "W4Jets_part_5",
#  "W4Jets_part_6",
#  "W4Jets_part_7",
#  "W4Jets_part_8",
#  "W4Jets_part_9",
#  "W4Jets_part_10",
#  "W4Jets_part_11",
#  "W4Jets_part_12",
#  "W4Jets_part_13",
#  "W4Jets_part_14",
#  "W4Jets_part_15",
 
  ### 
 ]

#Path to take data merged files
#dataPath = "rfio:/castor/cern.ch/user//m/mmerola/SingleTop_2012/MergedJune/"
dataPath = "file:/tmp/mmerola/"

#Choose if you want to run or just prepare the configuration files
#mode = ""
mode = "cmsRun"


#Use mu , ele or both

channel_instruction = "all"

#Implementation:

#Function to replace a sequence of characters channelOld to channelNew in a file 
def changeChannel(fileName,channelOld,channelNew,switch,isMC): 
    print " Channel test " + channelNew
    channelToReplace = channelNew
    if "Data" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "Data"
    if ("Mu" in channelNew or "Ele" in channelNew) and not "QCDMu" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "Data"
    if "WJets_wlight" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wlight"
    if "WJets_wcc" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wcc"
    if "WJets_wbb" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJets_wbb"
    if "WJetsQ2up" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJetsQ2up"
    if "WJetsQ2down" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "WJetsQ2down"
    if "W1Jet" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "W1Jet"
    if "W2Jets" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "W2Jets"
    if "W3Jets" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "W3Jets"
    if "W4Jets" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "W4Jets"                
    if "ZJets" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets"
    if "ZJets_wlight" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wlight"
    if "ZJets_wcc" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wcc"
    if "ZJets_wbb" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "ZJets_wbb"
    if "TTBar" in channelNew and not "Q2" in channelNew and not "Matching" in channelNew:  #=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar"
    if "TTBarQ2up" in channelNew : #=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBarQ2up"
    if "TTBarQ2down" in channelNew : #=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBarQ2down"
    if "TTBarMatchingup" in channelNew : #=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_MatchingUp"
    if "TTBarMatchingdown" in channelNew : #=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TTBar_MatchingDown"                
    if "TChannel" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TChannel"        
    if "TbarChannel" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "TbarChannel"        
    if "QCDMu" in channelNew:#=="DataMu" or channelNew == "DataEle" or channelNew == "DataMuQCD" or channelNew =="DataEleQCD":
        channelToReplace = "QCDMu"
          #if channelNew=="DataEle":
       # channelNew_2 = "Data"
    file = open(fileName)
    lines = file.readlines()
    o = open(channelNew+"_cfg.py","w") 
    for line in lines:
        if '"channel_instruction"' in line:
            print line
            line = line.replace('"channel_instruction"','"'+switch+'"')
            print line
        if "MC_instruction" in line and "False" in line:
       #     if "False" in line:
                print line
                line = line.replace("False",isMC)
                print line
        words = line.split()
        for word in words:
            if channelOld in word:  
                #                print " line old " + line
                if (not switch == "all") and ("process.TFileService" in line):
                    line = line.replace(word,word.replace(channelOld,channelNew))
                    print "process.TFileService in line,switch " + switch +" line: \n" +line
                    
                else:
                    line = line.replace(word,word.replace(channelOld,channelToReplace))
                
        o.write(line)   
    #if channel == "Data":#Temporary inelegant solution due to the separation of mu/e: will fix it at some point
        #        line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"DataMuMerged.root','"+dataPath+"DataEleMerged.root',)"
        #        line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"DataMuMerged.root',)"
        #       line = "process.source.fileNames = cms.untracked.vstring('"+dataPath+"Mu_v1Merged.root','"+dataPath+"Mu_v2Merged.root','"+dataPath+"Ele_v1Merged.root','"+dataPath+"Ele_v2Merged.root',)"
        #    if "WJets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        #        inputs = "process.source.fileNames = cms.untracked.vstring("
        #        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #        inputs = inputs.replace(channelToReplace,"WJets")
        #        inputs = inputs +")"
        #        o.write(inputs)
    if "QCDMu" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #        inputs = inputs.replace(channelToReplace,"QCDMu")
        inputs = inputs +")"
        o.write(inputs)        
    if "WJetsQ2up" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJetsQ2up")
        inputs = inputs +")"
        o.write(inputs)
    if "WJetsQ2down" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"WJetsQ2down")
        inputs = inputs +")"
        o.write(inputs)
    if "W1Jet" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W1Jet")
        inputs = inputs +")"
        o.write(inputs)
    if "W2Jets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W2Jets")
        inputs = inputs +")"
        o.write(inputs)
    if "W3Jets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W3Jets")
        inputs = inputs +")"
        o.write(inputs)
    if "W4Jets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"W4Jets")
        inputs = inputs +")"
        o.write(inputs)        
    if "ZJets" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        inputs = inputs.replace(channelToReplace,"ZJets")
        inputs = inputs +")"
        o.write(inputs)
    if "Mu" in channelNew or "Ele" in channelNew and not "QCD" in channelNew :# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p1Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p2Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4p3Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v4Merged.root',"
#        inputs = inputs +"'"+dataPath+"Mu_v2Merged.root',"
        inputs = inputs +")"
        o.write(inputs)
    if "TTBar" in channelNew and not "Q2" in channelNew and not "Matching" in channelNew: # == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #    inputs = inputs.replace(channelToReplace,"TTBar")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarQ2up" in channelNew : # == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #    inputs = inputs.replace(channelToReplace,"TTBarQ2up")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarQ2down" in channelNew : # == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #    inputs = inputs.replace(channelToReplace,"TTBarQ2down")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarMatchingup" in channelNew : # == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #        inputs = inputs.replace(channelToReplace,"TTBar_MatchingUp")
        inputs = inputs +")"
        o.write(inputs)
    if "TTBarMatchingdown" in channelNew : # == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #        inputs = inputs.replace(channelToReplace,"TTBar_MatchingDown")
        inputs = inputs +")"
        o.write(inputs)                        
    if "TChannel" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #    inputs = inputs.replace(channelToReplace,"TChannel")
        inputs = inputs +")"
        o.write(inputs)
    if "TbarChannel" in channelNew:# == "DataMu" or channelNew == "DataMuQCD":
        inputs = "process.source.fileNames = cms.untracked.vstring("
        inputs = inputs +"'"+dataPath+channel+"Merged.root',"
        #    inputs = inputs.replace(channelToReplace,"TbarChannel")
        inputs = inputs +")"
        o.write(inputs)                
#    if "Ele" in channelNew:#channelNew == "DataEle" or channelNew == "DataEleQCD":
#        inputs = "process.source.fileNames = cms.untracked.vstring("
#        inputs = inputs +"'"+dataPath+"Merged.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v4.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v2Merged.root',"
##        inputs = inputs +"'"+dataPath+"Ele_v1Merged.root',"
#        inputs = inputs +")"
#        o.write(inputs)
    o.close()
    return o

#Implementation of the loop part:

#Channel in the original file
startChannel = "TChannel"#channels[0]
nstart = 0;

f= open(fileName)

tmpName = "temp.py"
shutil.copy(fileName,tmpName)

for channel in channels:

    isMC = "False"
    if "Mu" in channel and not "QCD" in channel:
        channel_instruction = "mu"
    elif "Ele" in channel and not "QCD" in channel:
        channel_instruction = "ele"
    elif "Ele" in channel and not "QCD" in channel:
        channel_instruction = "ele"
    elif "Mu" in channel and ("QCD" in channel or "Had" in channel) and not "QCDMu" in channel:
        channel_instruction = "muqcd"
    elif "Ele" in channel and "QCD" in channel:
        channel_instruction = "eleqcd"
    else : 
        channel_instruction = "allmc"   
        isMC = "True"
    channelOld = startChannel
    
    cfg_file = changeChannel(tmpName,channelOld,channel,channel_instruction,isMC)
    command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log &'
    
    print command

    nstart = nstart +1
    if mode == "cmsRun":
        if nstart % nSimultaneous ==0 :
            command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log '
        else:
            command = 'nohup cmsRun ./' + channel+'_cfg.py > /tmp/mmerola/'+channel+'.log &'
            
        os.system(command)

                                               

#    if mode == "cmsRun":
#        os.system(command ) 
#    os.system("bg") 
#    os.system('rm '+channel+'_cfg.py' ) 

os.system('rm '+tmpName) 
#changeChannel(f,aChannel,startChannel)

#os.system(command)



