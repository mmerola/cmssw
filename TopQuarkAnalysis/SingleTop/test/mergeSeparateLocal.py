#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms
import os,sys,re,shutil,commands


inputDir = "/tmp/mmerola/"
outputDir = "/tmp/mmerola/"

#Original config file
template = "copyFlavorSeparationTemplateSummer"
#fName = "copyFlavorSeparationTemplate.py"
#f = open(fName)


option = "None"
option = "cmsRun"
#option = "bsub"

nparts = 1
channels = [
#"Mu_2011A_08Nov",
#"Mu_2011B_19Nov",
#"TTBar",
#"TTBarQ2up",
#"TTBarQ2down",
#"WJetsQ2up",
#"WJetsQ2down",

#"TTBarMatchingup",
#"TTBarMatchingdown",
    
#"TChannel_Q2Up",
#"TbarChannel_Q2Up",
#"TChannel_Q2Down",
#"TbarChannel_Q2Down",
#"QCDMu",
#"QCD_Pt_30to80_EMEnriched",
#"QCD_Pt_30to80_BCtoE",
#"QCD_Pt_80to170_EMEnriched",
#"QCD_Pt_80to170_EMEnriched",
#"WJets",
#"W1Jet",
#"W2Jets"
#"W3Jets"
#"W4Jets"
#"ZJets",
#"TWChannel",
#"TbarWChannel",
#"TChannel",
#"TbarChannel",
#"SChannel",
#"SbarChannel",
#"TChannel",
#"Ele_v1_A",
#"Mu_v1_A",
#"Mu_v1_B2",
#"Mu_v1_B1",
"WW",
#"WZ",
#"ZZ",
    ]

for channel in channels: 
    command_ls = "ls " + inputDir + " | grep _"+channel+"_"
    print command_ls
    files = commands.getoutput(command_ls).split('\n')
    print "channel "+ channel +" n files " + str(len(files))

    templateFile= __import__(template)     

#    for file in files:
#        print file
    print "Removing doubles from list"
    for file in files :
        print file
        fileNameParts = file.split("_")
        print 'filenameparts: ', fileNameParts
        jobNumber = fileNameParts[len(fileNameParts)-3] 
  #      print jobNumber
        for checkFile in files:
            if checkFile == file: continue
            checkFileNameParts = checkFile.split("_")
#            print checkFileNameParts
            checkJobNumber = checkFileNameParts[len(checkFileNameParts)-3] 
            if jobNumber == checkJobNumber:
                print " double: " + str(file) +" vs " + str(checkFile) 
                files.remove(checkFile)
#            Break 
    nfiles = len(files)    
    nraws = nfiles/(nparts)
    
    part = 0

    print channel + " after removal: n files " + str(len(files))
    for file in files: print file
    
    while int(part) < int(nparts):
        templateFileCopy = templateFile 
        templateFileCopy.process.source.fileNames = cms.untracked.vstring([]) 

               
        part = part +1
        if int(nparts) ==1:
            templateFileCopy.process.skimwall.fileName = cms.untracked.string(outputDir+channel+'Merged.root')
            configFile = open(channel + "_part_" +str(part)+"_cfg.py","w")
        else:
            templateFileCopy.process.skimwall.fileName = cms.untracked.string(outputDir+channel+'_part_'+str(part)+'Merged.root')
            configFile = open(channel + "_part_" +str(part)+"_cfg.py","w")

        
        nr =0
        for file in files:
            nr = nr +1
            if part == nparts:
                if nr > nraws * (part -1):
                    templateFileCopy.process.source.fileNames.append("file:"+inputDir+str(file))
            elif  nr > nraws * (part -1) and  nr <= nraws *part:
    #            print "nr "+str( nr )+" part "+str( part) + " nraws "+str( nraws ) + " filename " + str(file)
                templateFileCopy.process.source.fileNames.append("file:"+inputDir+str(file))
               
        configFile.write(templateFileCopy.process.dumpPython())
        configFile.close()
        if option == "cmsRun":
            launchCommand = 'nohup cmsRun ./' + channel + "_part_" +str(part)+"_cfg.py" +' >  /tmp/mmerola/'+channel+"_part_"+str(part)+'_merge.log &'
            print launchCommand
            os.system(launchCommand)
        if option == "bsub":
            launchCommand = 'bsub -q1nd ./' + channel + "_part_" +str(part)+"_cfg.py" +' >  /tmp/mmerola/'+channel+"_part_"+str(part)+'_merge.log &'
            print launchCommand
            os.system(launchCommand)
                                        
        
