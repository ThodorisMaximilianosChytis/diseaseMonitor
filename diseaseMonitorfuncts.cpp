#include <iostream>
#include <string>
#include <cstdlib>
#include "diseaseMonitorfuncts.h"
using namespace std;





void recordPatientExit(LList* Rec, string recordID, string exitDate){
	LLNode* Node = Rec->Search(atoi( recordID.c_str() ));					//search for record id in list

	if (Node==NULL){		//not found
		cout << "record with id " << recordID << " not found" << endl;
		return; 
	}
	Node->Print();
	if(DateCompareEarlier(Node->getEntry(),&exitDate)==2){			
		cout << "to be exitDate error: earlier than Entry date" << endl;
		return;
	} 
	Node->setExit(exitDate);
	Node->Print();
}




void insertPatientRecord(LList* Rec,Hashtable * dHT,Hashtable * cHT,string record_id,string Fname,string Lname,string Disease,string Country,string Entry,string Exit){
	if (Rec->Search( atoi( record_id.c_str() ) )!=NULL){
		cout << "Error : There is already a record with number: " << record_id << endl;
		return; 
	}
	
	if(DateCompareEarlier(&Exit,&Entry)==1 ){
		cout << "Error : Entry date is later tha Exit date" << endl;
		return;
	}

	if (Entry=="-"){
		cout << "Error : Entry date cannot be of type -" << endl;
		return;
	}

	Rec->Insert(atoi(record_id.c_str()),Fname,Lname,Disease,Country,Entry,Exit);
	cout << "Insert record: Record_id "<< record_id <<"||"<<Fname << "||"  <<Lname<<  "||" << Disease << "||" << Country << "||" << Entry<< "||" << Exit << endl;
	dHT->Insert(Disease,Rec->getLLHead());
	cHT->Insert(Country,Rec->getLLHead());
}

void globalDiseaseStats(Hashtable* HT,string date1, string date2){
	cout << "The Stats are :" <<endl;
	 HT->PrintBetweenDatesCount(&date1,&date2);	
 return;
}

void diseaseFrequency(Hashtable * HT,string virusName,string country,string date1,string date2){
	cout << "Frequencies are :" << endl;
	HT->PrintdiseaseFrequency(&virusName,&country,&date1,&date2);
	return;
}



void numCurrentPatients(Hashtable* HT,string disease){
	string date1="99-99-9999"; 		///a trick to get the correct BetweenDatesCount option (counting - in as exit date)
	string date2="99-99-9999";

	cout << "Still being nursed : " << endl;
	if (disease==""){
		HT->PrintBetweenDatesCount(&date1,&date2);			//use the already constructed functions while giving the correct paremeters
	}														//that suit our use
	else{
		string country="";
		HT->PrintdiseaseFrequency(&disease,&country,&date1,&date2);
	}
}



void TopKDisease(Hashtable* dHT,int k,string country,string date1,string date2){

	dHT->TopK(k,&country,&date1,&date2,2); //2=choose to search for a country inside the RB tree 

}

void TopKCountries(Hashtable* cHT,int k,string disease,string date1,string date2){

	cHT->TopK(k,&disease,&date1,&date2,3);	//3=choose to search for a disease inside the  RB tree
}




void exit(LList* Rec,Hashtable* dHT,Hashtable* cHT){			//free the memory by calling the clas destrucotrs
	delete Rec;
	delete dHT; 
	delete cHT;
	cout <<"exiting" << endl;
}