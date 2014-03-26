#!/usr/bin/python
import os
import re
import sys
import commands
#import xmlrpclib

#os.command("grid-proxy-init")

#"srm://stormfe1.pi.infn.it:8444/srm/managerv2?SFN=/cms/store/user/mmerola/SingleTop/DQM/topDQM_SingleMu2012B_195948_196531_Wtrans
se = "stormfe1.pi.infn.it"
port = "8444"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jun24/"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jul15/"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jun22/"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/"
#path = "/cms/store/user/mmerola/SingleTop/DQM/"
#path = "/cms/store/user/mmerola/SingleTop/Analysis/MC/Fall11/Merged/"
path = "/cms/store/user/mmerola/SingleTop/Analysis/44XNEW/Fall11/"
#path = "/cms/store/user/mmerola/SingleTop/Analysis/44XNEW/Merged/"
#path = "/cms/store/user/mmerola/SingleTop/Analysis/44XNEW/Merged/WJetsBig/"
#path = "/cms/store/user/mmerola/SingleTop/Analysis/44XNEW/Merged/ZJetsBig/"

dir ='"srm://'+se + ":" + port + "/srm/managerv2?SFN=" + path +'"'
command_ls = 'lcg-ls -b -D srmv2 -T srmv2 '+ dir
localdir = "/tmp/mmerola/"

nSimultaneous = 10

channels = [
#"Mu_2011A_08Nov",
#"Mu_2011B_19Nov",
#"topDQM_SingleMu2012B_195948_196531_final",
#"QCD_Pt_80to170_BCtoE",
#"QCD_Pt_80to170_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_30to80_BCtoE",

#"TChannel",
#"TbarChannel",

#"W1Jet",
#"W2Jets",
#"W3Jets",
#"W4Jets",
#"WJetsQ2up",
#"WJetsQ2down",

#"TTBarMatchingdown",
#"TTBarMatchingup",

#"SChannel",
#"SbarChannel",

#"TTBarQ2up",
#"TTBarQ2down",

#"TTBar",
#"QCDMu",

#"Ele_v1_A",
#"Mu_v1_A",
#"Mu_v1_B1",
#"Mu_v1_B2",
#"Mu_May10"
#"Ele_v1_B2",
#"WJets",

#"TbarWChannel",
#"TWChannel",

#"ZJets",
"WW",
#"WZ",
#"ZZ",
#"MergedJun27"
#"topDQM_SingleMu2012B_195948_196531_trigger"
#"topDQM_SingleMu2012B_195948_196531_RelIso"
    ]

nstart = 0;

for channel in channels:
    if "Merged" in path:
        command_ls_channel = command_ls[:-1] + '"' + ' | grep ' + channel
    else:
        command_ls_channel = command_ls[:-1] + channel +'"'
    files = commands.getoutput(command_ls_channel).split('\n')
    print command_ls_channel
    print "channel " + channel + " files: "
    for file in files:
        if "Merged" in path:
            #            filename = str(re.findall(".*\.root" , file))[(int(len(path))+int(len(channel))-3):-2]
            #            filename = str(re.findall(".*\.root" , file))[(int(len(path))+int(len(channel))-12):-2]
            filename = str(re.findall(".*\.root" , file))[(int(len(path))+2):-2]
        else: filename = str(re.findall("edmntuple.*\.root" , file))[2:-2]
        #else: filename = str(re.findall("topDQM_production.*\.root" , file))[2:-2]
        nstart = nstart +1
        if nstart % nSimultaneous ==0 :
            #print " is multiple " +str(nstart)  
            command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "srm://'+se + ":" + port + "/srm/managerv2?SFN=" + file + '" "'+ localdir + filename +'"'
        else: command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "srm://'+se + ":" + port + "/srm/managerv2?SFN=" + file + '" "'+ localdir + filename +'" &'
        #        command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "srm://'+se + ":" + port + "/srm/managerv2?SFN=" + file + '" "'+ localdir + filename +'" &'
        os.system(command_cp)
        print command_cp
        #print file
        #print filename

    

#print dir
#print command_ls
