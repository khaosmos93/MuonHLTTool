import os, json

class ROOTCodeProducer:
    def __init(self):
        self.sampleType = ""
        self.list_ntuplePath = []
        self.xSec = -999
        self.sumWeight = -999

    def Write(self):
        className = "MCRateTool"
        ROOTCodeName = "%s_%s.cxx" % (className, self.sampleType)

        f = open(ROOTCodeName, "w");

        str_addntuplePath = ""
        for ntuplePath in self.list_ntuplePath:
            str_temp = 'producer->AddNtuplePath("%s");\n  ' % ntuplePath
            str_addntuplePath = str_addntuplePath + str_temp

        str_ROOTCode = \
"""#include "{className_}.h"

void {rootFuncName_}()
{{
  {className_}* producer = new {className_}();

  {str_addntuplePath_}
  producer->sampleType_ = "{sampleType_}";
  producer->xSec_ = {xSec_};
  producer->sumWeight_ = {sumWeight_};

  producer->Run();  
}}

""".format(className_=className, rootFuncName_=ROOTCodeName.split(".cxx")[0], 
           sampleType_=self.sampleType, str_addntuplePath_=str_addntuplePath,
           xSec_=self.xSec, sumWeight_=self.sumWeight)
        
        f.write(str_ROOTCode)
        f.close()

        print "ROOT code: %s is produced" % ROOTCodeName

        return ROOTCodeName

if __name__ == '__main__':
    f_script = open("script_runAll.sh", "w")
    f_script.write("#!/bin/bash\n\n")

    analyzerPath = os.getenv("MUONHLT_ANALYZER_PATH")
    jsonPath = "%s/Include/MCSampleInfo.json" % analyzerPath

    with open(jsonPath) as fullSampleInfo_file:
        fullSampleInfo = json.load(fullSampleInfo_file)

    for sample in fullSampleInfo["Sample"]:
        if "asdf" in sample["list_ntuplePath"]: continue

        producer = ROOTCodeProducer()
        producer.sampleType      = sample["tag"]
        producer.list_ntuplePath = sample["list_ntuplePath"]
        producer.xSec            = sample["xSec"]
        producer.sumWeight       = sample["sumWeight"]
        ROOTCodeName = producer.Write()

        cmd_run = "root -b -q %s++ >&%s.log&" % (ROOTCodeName, ROOTCodeName.split(".cxx")[0])
        f_script.write(cmd_run + "\n")

        break

    f_script.write('\necho "All jobs are submitted"\n\n')
    f_script.close()

    print "script_runAll.sh is produced"
    