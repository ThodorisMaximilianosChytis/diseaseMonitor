objects= diseaseMonitor.o VirusDataStructuresfuncts.o diseaseMonitorfuncts.o

diseaseMonitor :$(objects)
	g++ -o diseaseMonitor $(objects)

VirusDataStructuresfuncts.o :VirusDataStructuresfuncts.cpp
	g++ -c VirusDataStructuresfuncts.cpp VirusDataStructures.h

diseaseMonitorfuncts.o :diseaseMonitorfuncts.cpp
	g++ -c diseaseMonitorfuncts.cpp VirusDataStructures.h diseaseMonitorfuncts.h

diseaseMonitor.o :diseaseMonitor.cpp
	g++ -c diseaseMonitor.cpp VirusDataStructures.h diseaseMonitorfuncts.h

clean  :
	rm diseaseMonitor $(objects) diseaseMonitorfuncts.h.gch VirusDataStructures.h.gch
