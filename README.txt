K24: System Programming Project1
Thodoris Maximilianos Chytis 
1115201700197


*********I tried using the validation script and had some issues I did not have the time to resolve due to the last minute announcemenet( after the initial deadline). Though I eye-checked the results and contentwise they are exactly the same. I also did a lot of tests on my own and the Project worked unerrigly. I invested a lot of time so please feel free to note any observations so that I can resolve any questions. Thank you*************** 


	This project successfully tackles the task of building and  linking the required data structures in order to accomplish creating an architecture suitable for saving, and accessing data, about patient records. Furthermore, through a user interface it  provides some applications-queries for the user to choose from. The programming language used is C++.
	Files:
    1) source : diseaseMonitor.cpp VirusDataStructuresfuncts.cpp diseaseMonitorfuncts.cpp
    2) header : VirusDataStructures.h diseaseMonitorfuncts.
    3) makefile : 	Makefile
    4) text : ***.txt	

-The text file contains information about the each patient :
-Record_id,  FirstName, LastName,  Disease, Country, Entrydate, Exitdate
-The VirusDataStructures.h consists of all the declarations of the classes that form the used data structures.
-The VirusDataStructures.cpp consists of all written class-data structure functions that are declared in VirusDataStructure.h , and a compareDate function for general use.
-The diseaseMonitor.cpp contains the command line arguments processing and usage, the storing of the patient information into the data structures, and the user interface. It is the main driver functions file.
-The diseaseMonitorfuncts.cpp file represesents the linker between the user interface and the data structures as it contains the functions to tackle the user's queries by accessing the information inside the data structures.  

Data Structures:
	In order to store the information from the patient record file a singly linked list is used (LList). Each LLNode allocates memory to contain the required information about one patient when it is inserted into the LList. It is important   we note that this is the only case where  memory is allocated to store the data, in order to avoid data duplication. In most later cases, a pointer to the LLNode is used to reference information about a patient.
	In order to access the data, a complex data structure design is formed into which pointers to  LLNodes are inserted. We create a diseasehashtable(and a countryhashtable), which cointains pointers to a 'BucketList' consisting of buckets. Each Bucket consists of an array to pointers to a specified number of BucketEntries. If after insertion the above number of Entries is reached, at the next insertion, a new Bucket is created therefore creating the 'BucketList'. Each bucket entry contains its key being  a disease (or country) that is exclusive to this BEntry and a pointer to a Balanced Binary Search Tree. The BBST used is a Red Black Balanced Binary Search Tree . The RBTree is the programmers choice because when inserting data, it requires less rotations than other balanced search trees because of the ability to recolor its nodes in order fix any balanced tree violations. The RBTree is sorted by the EntryDate of each patient having the key of the BEntry pointing to that Tree. Each RBTreeNode points to an LLNode of LList. If a LLNode pointer wich is inserted into the RBTree  has the same EntryDate as an already existing RBTreeNode, a dublicate RBTreeNode is created and inserted to the right of  the samedate RBTreeNode. This way each RBTreeNode existing in this complex data structure architecture points to exactly one LLNode.
	In order to tackle two of the applications that the user can choose from, named topk-Diseases (and topk-Countries), a Max Heap data structure is build on the fly using the tree implementation. In order to accomplish Insertion of MaxHeapNodes into the MaxHeap, and Root removal,  a Queue that is build on the fly is used. The Q of pointers to MaxHeapNodes allows to perform Level order insertion and to find  the correct MaxHeapNode to  be inserted into the Root after a Root Removal. Heapify functions are later applied to  preserve MaxHeapAttributes.

Program Flow:
	First some parameters are passed to the program: 
-patientrecordfile: name of the text file containing the patient information
-diseaseHashtableNumOfEntries: number entries the diseasehashtable consists of
-countryHashtableNumOfEntries: number entries the country hashtable consists of
-BBucketsize: number of bytes the bucket consists of including the pointer to the next bucket and some Bucket variables (8 bytes for that address ,8 bytes for variables). The rest of the bytes  is referring to the number of bucket entries that are to be created inside the bucket.
After that,the textx file is opened, the LList, the two hashtables are created, and the data is inserted into them from the text file as described above.
Then the user interface is run giving the user different options to choose from. It is assumed that the user does not enter any inappropriate arguments. The dates entered follow the format dd/mm/yyyy and date1 < date2.



The applications that the user can choose from are:
    1. /globalDiseaseStats [date1 date2] : If the dates are given ->prints for each virus the number of cases found of which the patient’s entry date is between date1 and date2 . If the dates are not given ->prints for each virus the number of cases found.
    2. /diseaseFrequency virusName date1 date2 [country]. : if the country is given -> prints the number of cases of virusName in country, of which the patient’s entry date is between date1 and date2. If  the country is not given-> prints the number of all cases of virusName,of which the patient’s entry date is between date1 and date2.
    3. /topk-Diseases k country [date1 date2] : if the dates are not given-> prints the top k diseases and their number of cases in country. If the dates are given -> prints the top k diseases and their number of cases in a country  of which  the patient’s entry date is between date1 and date2.
    4. /topk-Countries k disease [date1 date2] : if the dates are not given-> for one disease, prints the top k countries and their number of cases regarding disease. If the dates are not given -> prints the top k countries and their number of cases regarding disease, of which the patient’s entry date is between date1 and date2.
//In both 3. 4. we print disease,countries until we have k of them having different counts of cases.//(This was the initial implementation which was changed due to the validation script. Now no more than k are printed)
    5. /recordPatientExit recordID exitDate: finds the LLNode with record_id and if the exitDate given is later than the Entry date of the LLNode  the exit date of LLNode is updated.
    6. /NumCurrentPatients [disease] : if disease is given->  prints all patients records information  that are still being nursed with disease. If disease is not given -> print all patients records information that are still being nursed with any disease.
    7. /insertPatientRecord recordID patientFirstName patientLastName diseaseID country entryDate [exitDate]: If exitDate is given -> insert a new LLNode patient record into the LList with the above information and link the data strucures. If exitDate is not given -> to the above just insert - as exitDate.
    8. /exit: calling class destructors in order to deallocate the memory of the data structures and the data that was stored in tha main memory. The exit the user interface.

Compilation: 
	make
	./diseaseMonitor -p small.txt -h1 5 -h2 5 -b 50
	make clean


	make
	./diseaseMonitor -h1 8 -h2 8 -b 64 -p small.txt
	make clean
