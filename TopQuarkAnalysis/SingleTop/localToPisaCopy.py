#!/usr/bin/python
import os
import re
import sys
import commands
#import xmlrpclib

#os.command("grid-proxy-init")

#in_se = "cmsse02.na.infn.it"
out_se = "stormfe1.pi.infn.it"
#in_port = "8446"
out_port = "8444"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jun24/"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jul15/"
#path = "/dpm/na.infn.it/home/cms/store/user/oiorio/2012/Summer12/Jun22/"
in_path = "/tmp/mmerola/"
out_path = "/cms/store/user/mmerola/SingleTop/Analysis/44XNEW/Merged/"
#path = "/dpm/na.infn.it/home/cms/store/user/merola/SingleTop/DQM/"


#localdir = "/tmp/mmerola/"

nSimultaneous = 20

channels = [
"Merged",
#"Mu_v6_part_Merged",
#"Mu_Aug05_part_Merged",
#"MuHad_2011B_part_Merged",
#"MuHad_v6_part_Merged",
#"MuHad_Aug05_part_Merged",
#"Ele_v6_part_Merged",
#"EleHad_v6_part_Merged",
#"TesiDottorato",
#"QCD_Pt_80to170_BCtoE",
#"QCD_Pt_80to170_EMEnriched",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_30to80_BCtoE",
#"TChannel",
#"TbarChannel",
#"WJets",
#"TWChannelNew",
#"SChannelNew",
#"SbarChannel",
#"TTBar",
#"QCDMu",
#"Ele_v1_A",
#"Mu_v1_A",
#"Mu_v1_B1",
#"Mu_v1_B2",
#"Ele_v1_B2",
#"WJets",
#"TbarWChannel",
#"TWChannel",
#"ZJets",
#"WW",
#"WZ",
#"ZZ",
#"MergedJun27"
#"topDQM_SingleMu2012B_195948_196531_trigger"
#"topDQM_SingleMu2012B_195948_196531_RelIso"
    ]

dir = in_path 
command_ls = 'ls -ltr '+ dir

nstart = 0;

for channel in channels:
    if "Merged" in channel:
        command_ls_channel = command_ls[:] + '*' + channel + '*'
    else:    
        command_ls_channel = command_ls[:-1] + channel +'"'
    files = commands.getoutput(command_ls_channel).split('\n')
    print command_ls_channel
    print "channel " + channel + " files: "
    for file in files:
        if "Merged" in channel:
            #filename = str(re.findall(path + "*\.root" , file))[(int(len(path))+2):-2]
            filename = str(re.findall(".*\.root" , file))[(int(len(in_path))+int(len(channel))+44):-2]
            print "filenames: " + filename
        else: filename = str(re.findall("edmntuple.*\.root" , file))[2:-2]
        #else: filename = str(re.findall("topDQM_production.*\.root" , file))[2:-2]
        file = file[48:]
        nstart = nstart +1
        if "Merged" in channel:
            if nstart % nSimultaneous ==0 :
                command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "' + file + '" "'+ 'srm://'+out_se + ":" + out_port + "/srm/managerv2?SFN=" + out_path + '/' + filename +'"'
            else:
                command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "' + file + '" "'+ 'srm://'+out_se + ":" + out_port +"/srm/managerv2?SFN=" + out_path + '/'  + filename +'" &'

        else:
            if nstart % nSimultaneous ==0 :
                command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "' + file + '" "'+ 'srm://'+out_se + ":"+ out_port + "/srm/managerv2?SFN=" + out_path + '/' + channel + '/' + filename +'"'
            else:
                command_cp = 'lcg-cp -b -D srmv2 -T srmv2 "' + file + '" "'+ 'srm://'+out_se + ":" + out_port +"/srm/managerv2?SFN=" + out_path + '/' + channel + '/' + filename +'" &'
           
        os.system(command_cp)
        print command_cp
        #print file
        #print filename

    

#print dir
#print command_ls
