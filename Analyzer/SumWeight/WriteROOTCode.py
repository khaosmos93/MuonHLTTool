import os, json

class ROOTCodeProducer:
    def __init(self):
        self.sampleType = ""
        self.list_ntuplePath = []

    def Write(self):
        ROOTCodeName = "SumWeight_%s.cxx" % self.sampleType
        f = open(ROOTCodeName, "w");

        str_addntuplePath = ""
        for ntuplePath in self.list_ntuplePath:
            str_temp = 'producer->AddNtuplePath("%s");\n  ' % ntuplePath
            str_addntuplePath = str_addntuplePath + str_temp

        str_ROOTCode = \
"""#include "CalcSumWeight.h"

void SumWeight_{sampleType_}()
{{
  SumWeightProducer* producer = new SumWeightProducer();

  {str_addntuplePath_}
  producer->sampleType_ = "{sampleType_}";

  producer->Run();  
}}

""".format(sampleType_=self.sampleType, str_addntuplePath_=str_addntuplePath)
        
        f.write(str_ROOTCode)
        f.close()

        print "ROOT code: %s is produced" % ROOTCodeName

        return ROOTCodeName

if __name__ == '__main__':
    f_script = open("script_runAll.sh", "w")
    f_script.write("#!/bin/bash\n\n")

    f_print = open("script_printSumWeight.sh", "w")
    f_print.write("#!/bin/bash\n\n")

    analyzerPath = os.getenv("MUONHLT_ANALYZER_PATH")
    jsonPath = "%s/Include/MCSampleInfo.json" % analyzerPath

    with open(jsonPath) as fullSampleInfo_file:
        fullSampleInfo = json.load(fullSampleInfo_file)

    for sample in fullSampleInfo["Sample"]:
        if "asdf" in sample["list_ntuplePath"]: continue

        producer = ROOTCodeProducer()
        producer.sampleType      = sample["tag"]
        producer.list_ntuplePath = sample["list_ntuplePath"]
        ROOTCodeName = producer.Write()

        cmd_run = "root -b -q %s++ >&%s.log&" % (ROOTCodeName, ROOTCodeName.split(".cxx")[0])
        f_script.write(cmd_run + "\n")

        cmd_print = "root -b -q ROOTFile_SumWeight_%s.root Print_SumWeight.cxx" % sample["tag"]
        f_print.write(cmd_print + "\n")

    f_script.write('\necho "All jobs are submitted"\n\n')
    f_script.close()
    print "script_runAll.sh is produced"

    f_print.write('\necho "Done."')
    f_print.close()
    print "script_printSumWeight.sh is produced"

    