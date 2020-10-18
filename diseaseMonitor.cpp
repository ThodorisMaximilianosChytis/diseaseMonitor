#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "diseaseMonitorfuncts.h"


using namespace std;


int main(int argc, char **argv){


		char patientrecordfile[50];
		int diseaseHashtableNumOfEntries;
		int countryHashtableNumOfEntries;
		int BBucketsize;



	if (argc!=9){
		cout << "Input error" << endl;
		exit(1);
	}else{			
		int i;
		for(i=1;i<=7;i+=2){
			if(strcmp(argv[i],"-p")==0){
				strcpy(patientrecordfile,argv[i+1]);
			}else if(strcmp(argv[i],"-h1")==0){
				diseaseHashtableNumOfEntries = atoi(argv[i+1]);
			}else if(strcmp(argv[i],"-h2")==0){
				countryHashtableNumOfEntries = atoi(argv[i+1]);
			}else if(strcmp(argv[i],"-b")==0){
				BBucketsize = atoi(argv[i+1]);
			}else exit(1);			
		}
	// cout << patientrecordfile << endl;
	// cout << diseaseHashtableNumOfEntries << endl;
	// cout << countryHashtableNumOfEntries << endl;
	// cout << BBucketsize << endl;		

		 if(diseaseHashtableNumOfEntries<1) exit(1);
		 if(countryHashtableNumOfEntries<1) exit(1);
		 if (BBucketsize<32) exit(1);


													//Convert and save commmand line arguments
		// strcpy(patientrecordfile,argv[2]);
		// diseaseHashtableNumOfEntries = atoi(argv[4]);
		// if(diseaseHashtableNumOfEntries<1) exit(1);
		// countryHashtableNumOfEntries = atoi(argv[6]);
		// if(countryHashtableNumOfEntries<1) exit(1);
		// BBucketsize = atoi(argv[8]);
		// if (BBucketsize<32) exit(1);
	}





	string record_id,Fname,Lname,Disease,Country,Entry,Exit;
	//int number_of_records=13;
	 // string date1 = "01-02-2019";
	 // string date2 = "31-11-2019";




	ifstream infile;						
	infile.open(patientrecordfile);						// open the file selcted 
	if(infile.fail()) exit(1);


	LList *  Records = new LList();		//create List of records
	Hashtable * diseasehashtable = new Hashtable(diseaseHashtableNumOfEntries,((BBucketsize-16)/8));	//create hashtable for diseases	
	Hashtable * countryhashtable = new Hashtable(countryHashtableNumOfEntries,((BBucketsize-16)/8));	//create hashtable for countries

	
	while(infile>>record_id){		//import the data from the file

	infile >> Fname;
	infile >> Lname;
	infile >> Disease;
	infile >> Country;
	infile >> Entry;
	infile >> Exit;
	insertPatientRecord(Records,diseasehashtable,countryhashtable,record_id,Fname,Lname,Disease,Country,Entry,Exit); 	//Insert record into LList and connect the the data structures

	}


	infile.close();	//close file

		
	 string Request,disease,country,date1,date2;
	 int k;
	 	while(1){					///Start the user interface
	 		cout << "____________________________________________________________________________________________________" << endl;
			cout << "|Please Choose Between Applications:																 " << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			cout << "|1)  /globalDiseaseStats [date1 date2]                                                              " << endl;
			cout << "|2)  /diseaseFrequency virusName date1 date2 [country]											 " << endl;
			cout << "|3)  /topk-Diseases k country [date1 date2]														 " << endl;
			cout << "|4)  /topk-Countries k disease [date1 date2]														 " << endl;
			cout << "|5)  /insertPatientRecord recordID patientFirstName patientLastName diseaseID country entryDate [exitDate]" << endl;
			cout << "|6)  /recordPatientExit recordID exitDate															 " << endl;
			cout << "|7)  /numCurrentPatients [disease]																	 " << endl;
			cout << "|8)  /exit 																						 " << endl;
			cout << "| Note: Dates entered must follow the format dd-mm-yyyy and date1 must be earlier than date2        " << endl;
			cout << "____________________________________________________________________________________________________"	<< endl;
				

				getline(cin,Request);			//get choice from user
				cout << "You chose: " << Request << endl;
				stringstream wordcount(Request);
				stringstream srequest(Request);

				int count = 0;
				string temp;
				while(wordcount>>temp)			//count number of words given
					count++;
				
				 string app;
				 srequest>>app;				//get app name
				
				//cout << count << endl;
				 ////Use the num of words given to choose how to call each function (optional arguments)

				if (app=="/globalDiseaseStats"){
					
					if (count==3){			
						srequest >> date1;
						srequest >> date2;
					}
					else if (count==1){
						date1.assign("");
						date2.assign("");
					}
					else{
						cout << "Wrong input, try again" << endl;
						continue;
					}
					globalDiseaseStats(diseasehashtable,date1,date2);
				
				}else if(app=="/diseaseFrequency"){
					srequest >> disease;
					srequest >> date1;
					srequest >> date2;
					if (count==5){
						srequest >> country;
					}else if (count==4){
						country.assign("");
					}else{
						cout << "Wrong input, try again" << endl;
						continue;
					}
					diseaseFrequency(diseasehashtable,disease,country,date1,date2);

				}else if(app=="/topk-Diseases"){
					srequest >> k;
					srequest >> country;
					if (count==5){
						srequest>>date1;
						srequest>>date2;
					}else if(count==3){
						date1.assign("");
						date2.assign("");
					}else{
						cout << "Wrong input, try again" << endl;
						continue;
					}
					TopKDisease(diseasehashtable,k,country,date1,date2);					

				}else if(app=="/topk-Countries"){
					srequest >> k;
					srequest >> disease;
					if (count==5){
						srequest>>date1;
						srequest>>date2;
					}else if(count==3){
						date1.assign("");
						date2.assign("");
					}else{
						cout << "Wrong input, try again" << endl;
						continue;
					}
					TopKCountries(countryhashtable,k,disease,date1,date2);

				}else if(app=="/insertPatientRecord"){
					srequest >> record_id;
					srequest >> Fname;
					srequest >> Lname;
					srequest >> Disease;
					srequest >> Country;
					srequest >> Entry;
					if (count==8){
						srequest >> Exit;
					}else if(count==7){
						Exit.assign("-");
					}else{
						cout << "Wrong input,try again" << endl;
						continue;
					}
					insertPatientRecord(Records,diseasehashtable,countryhashtable,record_id,Fname,Lname,Disease,Country,Entry,Exit);
				
				}else if(app=="/recordPatientExit"){
					if (count==3){
						srequest >> record_id;
						srequest >> Exit;
					}else{
						cout << "Wrong input ,try again" << endl;
						continue;
					}
					recordPatientExit(Records,record_id,Exit);

				}else if(app=="/numCurrentPatients"){
					if (count==2){
						srequest >> disease;
					}else if(count==1){
						disease.assign("");
					}
					else{
						cout << "Wrong input try again" << endl;
						continue;
					}
					numCurrentPatients(diseasehashtable,disease);

				}else if (app=="/exit"){
					exit(Records,diseasehashtable,countryhashtable);
					break;							//exit loop and user interface
				}

	
	 	}


	return 0;
}


