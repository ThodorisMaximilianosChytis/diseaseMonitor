#include <iostream>
#include <string>
#include <cstdlib>
#include "VirusDataStructures.h"
using namespace std;

/////////////////////////////////////////////////////////////////////////////// General use//////////////////////////////////////////
int DateCompareEarlier(string* date1,string* date2){			//1 -> date1 is earlier || 2->date2 os earlier
		if(*date1=="-")					//- is always larger
			return 2;
		else if(*date2=="-")
			return 1;
		//sum of dd-mm-yyyy , giving the correct weights
		unsigned int sum1= atoi(date1->substr(0,2).c_str())*1 + atoi(date1->substr(3.2).c_str())*31 + atoi(date1->substr(6.4).c_str())*31*12;		
		unsigned int sum2= atoi(date2->substr(0,2).c_str())*1 + atoi(date2->substr(3.2).c_str())*31 + atoi(date2->substr(6.4).c_str())*31*12;
	
		if (sum1<sum2)
			return 1;
		else if(sum2<sum1)
			return 2;
		else
			return 0; 

}	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LLNode* LLNode::getNext(){
	return Next;
}

int LLNode::getid(){

	return Record_id;
}


string * LLNode::getDisease(){
	return Disease;
}

string* LLNode::getEntry(){
	return Entry;
}

string* LLNode::getCountry(){
	return Country;
}

void LLNode::setExit(string _Exit){
	*Exit = _Exit;
}

string* LLNode::getExit(){
	return Exit;
}

void LLNode::Print(void){
	cout << endl;
	cout << "------------------" << endl;
	cout << Record_id << endl;
	cout << *Fname << endl;
	cout << *Lname << endl;
	cout << *Disease << endl;
	cout << *Country << endl;
	cout << *Entry << endl;
	cout << *Exit << endl;
	cout << "------------------" << endl; 
}

void LLNode::setNext(LLNode* _Node){
	Next=_Node;
}

LLNode::LLNode(int _record_id,string _Fname, string _Lname, string _Disease, string _Country, string _Entry, string _Exit):Record_id(_record_id){
	//cout << "Listnode constructor" << endl;
	Fname = new string(_Fname);
	Lname = new string(_Lname);
	Disease = new string(_Disease);						//Listonode Constructor and memory allocation for record strings
	Country = new string(_Country);
	Entry = new string(_Entry);
	Exit = new string(_Exit); 
	Next = NULL;
};

LLNode::~LLNode(void){
	//cout << "deleting LLNode" << endl;
	delete Fname;
	delete Lname;							//Listonode destructor and memory free for record strings
	delete Disease;
	delete Country;
	delete Entry;
	delete Exit;
}


///////////////////////////////////////////////LList//////////////////////////////////////////////////////////////////////



LLNode* LList::getLLHead(){
	return LLHead;
}


void LList::Print(void){
	LLNode * temp = LLHead;
	while (temp!=NULL){
		temp->Print();				//print listnode
		temp=temp->getNext();
	}
}

void LList::Insert(int _record_id,string _Fname, string _Lname, string _Disease, string _Country, string _Entry, string _Exit){
	LLNode*  newNode= new LLNode(_record_id,_Fname,_Lname,_Disease,_Country,_Entry,_Exit);	//listonde memory allocation
	newNode->setNext(LLHead);			//and list insertion
	LLHead = newNode;

}

LLNode * LList::Search(int id){					//search for a node with specific id . return that node or NULL
	LLNode * temp = LLHead;
	while(temp!=NULL){
		if (temp->getid()==id){

			return temp;
		}
		// else if(temp->getid()<id){			//if we insert in ascending order
		// 	cout << "hey jo" << endl;			
		// 	break;
		// }
		temp=temp->getNext();
	}
	return NULL;
}


LList::LList(void):LLHead(NULL){
	//cout << "calling LList constructor" << endl;
}


LList::~LList(void){				//list constructor
	//cout << "deleting List" << endl; 
	LLNode* temp;
	while (LLHead!=NULL){
		temp=LLHead;
		LLHead=LLHead->getNext();
		delete temp;			//call listonode destructor and free listnode
	}

}
/////////////////////////////////////////////////////////////RBTreeNode/////////////////////////////////////////////////////////


RBTreeNode::RBTreeNode(LLNode* _Record):left(NULL),right(NULL),parent(NULL),color(0),Date(NULL),Record(_Record){
	Date=_Record->getEntry();		//use date in record
	//cout << "TreeNode constructed and Initilized succesfully" << endl;					//Treenode constructor
}


RBTreeNode::~RBTreeNode(){
	//cout << "treenode destroyed" << endl;					//treenode destructor
}


void RBTreeNode::setleft(RBTreeNode * _left){
	left = _left; 
}


void RBTreeNode::setright(RBTreeNode * _right){
	right = _right; 

}


void RBTreeNode::setparent(RBTreeNode* _parent){
	parent = _parent; 

}


void RBTreeNode::setColor(int _color){				//0==red 1==black
	color = _color;
}


RBTreeNode * RBTreeNode::getright(void){
	return right;
}


RBTreeNode * RBTreeNode::getleft(void){

	return left;
}


RBTreeNode * RBTreeNode::getparent(void){
	return parent;
}


int RBTreeNode::getColor(void){
	return color;
}


string* RBTreeNode::getDate(){
	return Date;
}


LLNode* RBTreeNode::getRecord(){			//the record is in the list I just return the pointer to it
	return Record;
}



//////////////////////////////////////////////////////////RBTree/////////////////////////////////////////////////////////////////////





RBTree::RBTree():Root(NULL),Nodecount(0){			//Rbtree constructor //Nodecount=number n of nodes

	//cout << "tree has been created" << endl;
}

RBTree::~RBTree(){					//Rbtree destructor
	Destroy(Root);					//use helper function to destroy(delete) the tree
	//cout << "tree hass been destoyed" << endl;
}


RBTreeNode * RBTree::getRoot(void){
	return Root;
}


void RBTree::setRoot(RBTreeNode* _Root){
	Root=_Root;
}


//Different traversals to print the tree data


void RBTree::Inorder(RBTreeNode* Root){			
	if (Root==NULL) return;
	Inorder(Root->getleft());
	cout << *Root->getDate() << endl;
	Inorder(Root->getright());
}


void RBTree::Postorder(RBTreeNode* Root){
	if (Root==NULL) return;
	Postorder(Root->getleft());
	Postorder(Root->getright());
	cout << *Root->getDate() << endl;
}


void RBTree::Preorder(RBTreeNode* Root){
	if (Root==NULL) return;
	cout << *Root->getDate() << endl;
	Preorder(Root->getleft());
	Preorder(Root->getright());

}

	



RBTreeNode * RBTree::BSTInsert(RBTreeNode *root, RBTreeNode *&newNode){			//Recursive Binary search Tree insert 
	if (root==NULL)
		return newNode;
	if (DateCompareEarlier(newNode->getDate(),root->getDate())==1){			//go left to insert if the date of new node is smaller than the date of the saved one
		root->setleft(BSTInsert(root->getleft(), newNode));
		root->getleft()->setparent(root);
	}else if (DateCompareEarlier(newNode->getDate(),root->getDate())==2 || DateCompareEarlier(newNode->getDate(),root->getDate())==0){   //go right to insert if the date of the new node
		root->setright(BSTInsert(root->getright(),newNode));																			//is larger or the same as the date of the saved one
		root->getright()->setparent(root);
	}
	return root;
}



void RBTree::LRot( RBTreeNode * &STRootNode){		//STRootNode = subtreerootnode	


	///Perform a left rotation on the BSTree to preserve BST attributes

	RBTreeNode * tbSTRootNode = STRootNode->getright();			


	STRootNode->setright(tbSTRootNode->getleft());		//the left child of the to be root node is now right child of the one that was root

	if(STRootNode->getright() != NULL)					
		STRootNode->getright()->setparent(STRootNode);

	tbSTRootNode->setparent(STRootNode->getparent());	//the parent of root is now parent of to be root

	if (STRootNode->getparent() == NULL)				
		Root = tbSTRootNode;					//root was RBTree Root so set RBTree Root to the to be root
	else if(STRootNode == STRootNode-> getparent()->getleft())		//else attach correctly to parent root
		STRootNode->getparent()->setleft(tbSTRootNode);
	else
		STRootNode->getparent()->setright(tbSTRootNode);

	tbSTRootNode->setleft(STRootNode);	//connect the nodes to complete the rotation
	STRootNode->setparent(tbSTRootNode);


}



void RBTree::RRot( RBTreeNode *   &STRootNode){

	//Perform a right rotation ont the BSTree to preserve BST attributes 

	RBTreeNode * tbSTRootNode = STRootNode->getleft();	


	STRootNode->setleft(tbSTRootNode->getright());			////the right child of the to be root node is now left child of the one that was root

	if(STRootNode->getleft() != NULL)
		STRootNode->getleft()->setparent(STRootNode);

	tbSTRootNode->setparent(STRootNode->getparent());		//the parent of root is now parent of to be root

	if (STRootNode->getparent() == NULL)
		Root = tbSTRootNode;								//root was RBTree Root so set RBTree Root to the to be root
	else if(STRootNode == STRootNode-> getparent()->getleft())
		STRootNode->getparent()->setleft(tbSTRootNode);		//else attach correctly to parent root
	else
		STRootNode->getparent()->setright(tbSTRootNode);

	tbSTRootNode->setright(STRootNode);			//connect the nodes to complete the rotation
	STRootNode->setparent(tbSTRootNode);


}



void RBTree::FixRBInsert(RBTreeNode *&newNode){		//RED=0 BLACK=1			//A function to detect and fix the RBTree violations that occured after BSTreee insertion
    RBTreeNode *parent = NULL;
    RBTreeNode *grandparent = NULL;

    while (newNode != Root && newNode->getColor() == 0 && newNode->getparent()->getColor() == 0) {
        parent = newNode->getparent();
        grandparent = parent->getparent();
        
        if (parent == grandparent->getleft()) {				//1)parent's uncle is also red -> so recolor
            RBTreeNode *uncle = grandparent->getright();
            if (uncle!=NULL && uncle->getColor()== 0) {
                uncle->setColor(1);
                parent->setColor(1);
                grandparent->setColor(0);
                newNode = grandparent;
            } else {				
                
                if (newNode == parent->getright()) {			//i)parent is right of parent -> LRot
                
                    LRot(parent);
                    newNode = parent;
                    parent = newNode->getparent();
                }
                RRot(grandparent);				//ii)parent is left of parent ->RRot
                int temp=parent->getColor();
                parent->setColor(grandparent->getColor());
               	grandparent->setColor(temp);
                newNode = parent;
            }
        } else {							//2)parent's parent is right of parent's grandparent

            RBTreeNode *uncle = grandparent->getleft();
            if(uncle!=NULL && uncle->getColor() == 0) {		//i)parent's uncle is also red -> recolor
                uncle->setColor(1);
                parent->setColor(1);
                grandparent->setColor(0);
                newNode = grandparent;
            }else {									//ii) parent is left of parent's parent -> RRot
                if (newNode == parent->getleft()) {
                    RRot(parent);
                    newNode = parent;
                    parent = newNode->getparent();
                }
                LRot(grandparent);				//iii)parent is right of parent's parent -> LRot
                int temp = parent->getColor();
                parent->setColor(grandparent->getColor());
                grandparent->setColor(temp);
                newNode = parent;
            }
        }
    }
    Root->setColor(1);
}



void RBTree::Insert(LLNode* record){			//Insert into RBTRee
	RBTreeNode * nRBTNode =  new RBTreeNode(record);		//treenode allocation
	Root = BSTInsert(Root,nRBTNode);			//BSTinsert
	Nodecount++;			
	//Preorder(Root);
	FixRBInsert(nRBTNode);		//Fix the Insertion to preserve RBTree attributes
	//Preorder(Root);
	//Inorder(Root);
}


void RBTree::Destroy(RBTreeNode * Node){		//Postorder Recursive Destroy the RBTree 

	if(Node != NULL){
		Destroy(Node->getleft());
		Destroy(Node->getright());
		delete Node;
	}

}


/*The below recursive function is used to count nodes that fit the user's demands*/

int RBTree::BetweenDatesCount(RBTreeNode* _Root, string* date1,string* date2,string * searchfor,int type){

	int count=0;			
	if(_Root==NULL)			//Base condition
		return 0;



		if (type==2 && *searchfor==*_Root->getRecord()->getCountry()){	//type==2->		//Counting treenodes which match the country we are searching for
			
			if (*date1==""){
				count++;		//dont care about dates so count each node with correct country
			}else if(DateCompareEarlier(_Root->getDate(),date1)!=1 && DateCompareEarlier(_Root->getDate(),date2)!=2){
				count++;		//only count those nodes where the nodes's entry date e[date1,date2]
			}
		}

		if (type==3 && *searchfor==*_Root->getRecord()->getDisease()){	//type==3->	//Counting treenodes which match the diasease we are searching for
			if (*date1==""){
				count++;		//dont care about dates so count each node with correct disease
			}else if(DateCompareEarlier(_Root->getDate(),date1)!=1 && DateCompareEarlier(_Root->getDate(),date2)!=2){
				count++;	////only count those nodes where the nodes's entry date e[date1,date2]
			}
		}

		if (type==1){		//type==1-> //Counting withoyt searching for record attribute
			if(*date1==""){
				return Nodecount;		//return the number of nodes inside the tree
			}else if(DateCompareEarlier(_Root->getDate(),date1)!=1 && DateCompareEarlier(_Root->getDate(),date2)!=2){
				count ++;
					//////only count those nodes where the nodes's entry date e[date1,date2]
			}
		}
		if(*date1=="99-99-9999" && *(_Root->getRecord()->getExit())=="-"){ ///this is a trick to get the count required fot the application
				count++;	
				//_Root->getRecord()->Print();												///which counts people still being nursed
		}

	

	

	if(_Root->getleft()!=NULL ){
			if(*date1=="" || *date1=="99-99-9999"){
				count+=BetweenDatesCount(_Root->getleft(),date1,date2,searchfor,type);			//go left.recusrion babyyy
			}else if(DateCompareEarlier(_Root->getDate(),date1)!=1){
				count+=BetweenDatesCount(_Root->getleft(),date1,date2,searchfor,type);			//go left.recusrion babyyy
			
			}	
	}			//_Root->getRecord()->Print();												///which counts people still being nursed

	if(_Root->getright()!=NULL){
			if(*date1=="" || *date1=="99-99-9999"){
				count+=BetweenDatesCount(_Root->getright(),date1,date2,searchfor,type);			//go right. recursion babyy
			}else if(DateCompareEarlier(_Root->getDate(),date2)!=2){
				count+=BetweenDatesCount(_Root->getright(),date1,date2,searchfor,type);			//go left.recusrion babyyy
			} 
	}
	//cout << "Counting inside the tree " << count << endl;
	return count;

}





////////////////////////////////////////////////BEntry///////////////////////////////////////////////////////////////





void BEntry::Insert(LLNode* record,string key){		//Insert into the bucket Entry

		if (RBHead==NULL){
			Key = new string(key);
			RBHead = new RBTree();
		}
		RBHead->Insert(record);

}


string* BEntry::getkey(void){	
	return Key;
}



BEntry::BEntry():Key(NULL),RBHead(NULL){
	//cout << "BucketEntry Constructor" << endl; 
}



int BEntry::BetweenDatesCount(string* date1,string* date2,string* searchfor,int type){		//call the counter function with the demanded type


	return RBHead->BetweenDatesCount(RBHead->getRoot(),date1,date2,searchfor,type);
}



BEntry::~BEntry(){
	//cout << "BucketEntry Destructor" << endl;
	if (Key!=NULL) delete Key;
	if (RBHead!=NULL) delete RBHead;
}




//////////////////////////////////////////////////////////////////Bucket//////////////////////////////////////////////////

Bucket * Bucket::getNext(void){
	return Next;
}


void Bucket::setNext(Bucket * _Next){
	Next = _Next;
}


Bucket::Bucket(int Bsize):B_Size(Bsize), count(0),Next(NULL){		//Bucket constructor
	//cout << "bucket constructorand Bsize is"  << B_Size << endl;
	Content = new BEntry*[B_Size];		//array of pointers to bucketentries
	for (int i=0;i<=B_Size-1;i++){
		Content[i]= new BEntry();		//fill the array with BEntrypointers
	}
}


Bucket::~Bucket(void){		//Bucket entry constructor
	//cout << "bucket destructor" << endl;
	for (int i=0 ; i<=B_Size-1 ; i++ ){
			delete Content[i];			//delte Bentries
	}
	delete[] Content;
}


int Bucket::Insert(LLNode * record,string key){			//Insert into the bucket
 	int i;


		for (i=0 ; i<=B_Size-1 ; i++){
			if (Content[i]->getkey()==NULL || *(Content[i]->getkey())==key){
				Content[i]->Insert(record,key);
				return 1;
			}	
		}
		return 0;
		
 }


void Bucket::PrintBetweenDatesCount(string* date1,string* date2){			//For every Bentry->print the count of nodes either between
																			//dates or not
	int i;
	string searchfor="";				//not search for any other attribute
	for (i=0;i<=B_Size-1;i++){
		if (Content[i]->getkey()!=NULL){
			cout << *Content[i]->getkey() << " :===: "<< Content[i]->BetweenDatesCount(date1,date2,&searchfor,1) <<" cases" <<endl;
			
		}
	}
}


void Bucket::PrintdiseaseFrequency(string * virusName,string * country, string* date1, string* date2){
	// Print the frequency of cases for a given virus either for some country or not between some dates
	int i;
	int count=-1;
	for(i=0;i<=B_Size-1;i++){
		if (Content[i]->getkey()!=NULL){
			if (*(Content[i]->getkey()) == *virusName){
				if (*country==""){
					count= Content[i]->BetweenDatesCount(date1,date2,country,1);
				}
				else{
					count= Content[i]->BetweenDatesCount(date1,date2,country,2);
				}	
				cout << *Content[i]->getkey() << " :==: " << count << endl;	//print for alla countries
				break;
			}
		}
	}
	if (count==-1){
		cout << *virusName << " not found frequency is 0" << endl;
	}
}


void Bucket::TopK(MaxHeap* OTFHeap,string* date1,string* date2,int choice){		//topK function used for both topk applications
	int i;
	int casenumber=0;

	//cout << *date1 << endl;
	//cout << *date2 << endl;
	for (i=0;i<=B_Size-1;i++){
		if (Content[i]->getkey()!=NULL){
			casenumber = Content[i]->BetweenDatesCount(date1,date2,OTFHeap->getkey(),choice); //count choice->decides what to count
			MaxHeapNode * Node  = new MaxHeapNode(*Content[i]->getkey(),casenumber);
			OTFHeap->Insert(Node);		//Insert the Node with its key eand number of cases into maxheap
		}
	}
}





//////////////////////////////////////////////////////Hashtable///////////////////////////////////////////////////////////// 
 



void Hashtable::PrintBetweenDatesCount(string* date1,string* date2){		//Acess the architecture-wise deeper structures to print the case count 
	 int i;																	//of all viruses

	 for (i=0;i<=HTSize-1;i++){
	 	Bucket* temp = HTHead [i];
	 	while(temp!=NULL){
			temp->PrintBetweenDatesCount(date1,date2);
			temp = temp->getNext();
		}	 	
	 }

}


void Hashtable::PrintdiseaseFrequency(string * virusName,string* country,string* date1,string* date2){ 	//Acess  structures to print frequency of a specific virus between dates [ for a country]
	int index;
	index = Hashfunction(*virusName);
	Bucket * temp = HTHead [index];
	while (temp!=NULL){

		temp->PrintdiseaseFrequency(virusName,country,date1,date2);
		temp = temp->getNext();
	} 
	
}


void Hashtable::TopK(int k,string* key,string* date1,string* date2,int choice){		//topk
	int i;
	MaxHeap * OTFHeap = new MaxHeap(*key);					//create max heap

	for (i=0;i<=HTSize-1;i++){
		Bucket * temp = HTHead [i];
		while (temp!=NULL){
			temp->TopK(OTFHeap,date1,date2,choice);		//Insert the Nodes into the Maxheap with the correct key and casecount
			temp = temp->getNext();
		}
	}	
	int  max;
	i=0;
	cout << "For " << *key << " the top " << k << " cases are: " << endl;
	if (OTFHeap->getMax()->getcount()==0) cout << "No cases at all" << endl;
	

	while (i<k && OTFHeap->getMax()->getcount()>0){			//start extracting k or more(if the casecount is the same) from MaxHeap
		

		max = OTFHeap->getMax()->getcount();		

		cout << *OTFHeap->getMax()->getstr() << " :==: "  << max << endl;
		
		OTFHeap->RemoveRoot();			//cheakily "removing-deactivating a node oof the on the fly heap"

		// if(max==OTFHeap->getMax()->getcount()){		//more than one node with the same casecount
		// 	k++;
		// 	//cout << "another one with the same cases" << endl;
		// }
		i++;
	}
		//OTFHeap->Preorder(OTFHeap->getMax());	//print the heap after

	delete OTFHeap;
}


int Hashtable::Hashfunction(string key){				//hashfunction to get index of the hashtable for key
	int a=HTSize+1;
	int hash=0;
	for(int i=0 ; i<=key.size(); i++){
		hash = (a*hash + (unsigned int) key[i])% HTSize;		//each character of string works into a creating a sum thas is moded(%)
	}
	int hashcode = (hash % HTSize); 
	return hashcode;
}


void Hashtable::Insert(string key,LLNode * record){		//Insert a record pointer into hash......treenode

	int index = Hashfunction(key);

	if(HTHead[index]==NULL)
		HTHead[index] = new Bucket(B_Size);
	//cout <<" key is " << key << " hashcode is " <<index << endl;

	Bucket* temp = HTHead[index];
	while(temp->Insert(record,key)==0){		//only insert if key not found in some bucket
		if (temp->getNext()==NULL){
			temp->setNext(new Bucket(B_Size));
		}
		temp=temp->getNext();
	}
	count++;
}


Hashtable::Hashtable(int _HTSize, int BSize):HTSize(_HTSize),B_Size(BSize){
	//cout << "construct hashtable" << endl;
	
	HTHead = new Bucket*[HTSize];
	for (int i=0;i<=HTSize-1;i++){
		HTHead[i]=NULL;			//inistialize with null. Only gets an address a record is to be inserted 
	}
}


Hashtable::~Hashtable(){			//Hashtable destructor
	
	//cout << "destroy hashtable" << endl;
	
	for (int i=0;i<=HTSize-1;i++){
		Bucket * temp;
		while (HTHead[i]!=NULL){
			temp=HTHead[i];
			HTHead[i]=HTHead[i]->getNext();
			delete temp;
		}
	}
	delete[] HTHead;
}



////////////////////////////////////////Q to help with some Heap operations///////////////////////////


/////////////////////////////////////////QNode///////////////////////////////////////////////////////

QNode::QNode(MaxHeapNode* _data):next(NULL),data(_data){} 	


QNode::~QNode(){}		//Maxheapnode is not freed beacuse it is still neeeded in the heap


MaxHeapNode * QNode::getdata(void){
	return data;
}


void QNode::setdata(MaxHeapNode* _data){
	data = _data;
}


QNode* QNode::getnext(){
	return next;
}


void QNode::setnext(QNode* _next){
	next= _next;
}


///////////////////////////////////////////////Queue//////////////////////////////////////////////////////////////



Queue::Queue():front(NULL),back(NULL){	
	//cout << "Q is created" <<endl;
}


void Queue::Destroy(){	//destroy queue free qnodes
	QNode * temp=front;
	while(front!=NULL){
		temp = front;
		front = front->getnext();
		delete temp;
	}
	back=NULL;
	//cout << "Q is destroyed" << endl;
}


Queue::~Queue(){
	Destroy();
}


QNode* Queue::getfront(){
	return front;
}


QNode* Queue::getback(){
	return back;
}


void Queue::enQ(MaxHeapNode* Node){			//push into back
	QNode * tbinserted = new QNode(Node);

	if (back==NULL){
		front=tbinserted;
		back=tbinserted;
		return;
	}
	back->setnext(tbinserted);
	back = tbinserted;
}


void Queue::deQ(void){			//pop from front
	if (front==NULL){
		return;
	}
	QNode * temp = front;
	front = front->getnext();
 
	if (front==NULL){
		back=NULL;
	}
	delete temp;
}


int Queue::QEmpty(void){		//check if q is empty
	return (front==NULL && back==NULL);
}




//////////////////////////////////////MaxHeapNode///////////////////////////////////////////////////////////




MaxHeapNode::MaxHeapNode(string _str,int _count):count(_count),left(NULL),right(NULL){
	str = new string(_str);
}


MaxHeapNode::~MaxHeapNode(){
	delete str;
	//cout <<"MaxHeapNode deleting" << endl;
}



MaxHeapNode*  MaxHeapNode::getleft(){
	return left;
}


MaxHeapNode* MaxHeapNode::getright(){
	return right;
}


void MaxHeapNode::setleft(MaxHeapNode* _left){
	left = _left;
}


void MaxHeapNode::setright(MaxHeapNode* _right){
	right = _right;
}


int MaxHeapNode::getcount(){
	return count;
}


void MaxHeapNode::setcount(int _count){
	count = _count;
}

void MaxHeapNode::Incount(){	//increment the count (number of nodes)
	count++;
}

string * MaxHeapNode::getstr(){
	return str;
}


void  MaxHeapNode::setstr(string* _str){
	 str = _str;
}




////////////////////////////////////////////////MaxHeap/////////////////////////////////////////////////////////////////


MaxHeap::MaxHeap(string _key):Root(NULL),count(0){
	//cout << "create heap" << endl;
	key = new string(_key);
	Q = new Queue();
}

MaxHeap::~MaxHeap(){
	//cout  << "destroy heap " << endl;
		Destroy(Root);
	delete key;
	delete Q;
}

void MaxHeap::Destroy(MaxHeapNode * Node){	//postorder recursive destroy of heap

	if(Node != NULL){
		Destroy(Node->getleft());
		Destroy(Node->getright());
		delete Node;
	}

}

string * MaxHeap::getkey(){
	return key;
}


MaxHeapNode* MaxHeap::getMax(){			//return max which is root inside a maxheap beacuse of max heap attributes
	return Root;
}

void MaxHeap::ShiftUP(MaxHeapNode* Node){		//Bubble the node up into correcto position (helper of heapify)
	if(Node==NULL)
		return;
	MaxHeapNode* max=Node;
	if(Node->getleft() !=NULL && max->getcount() < Node->getleft()->getcount()){
		max = Node->getleft();
	}


	if(Node->getright() !=NULL && max->getcount() < Node->getright()->getcount()){
		max = Node->getright();
	}

	if(max==Node)
		return;
	int temp=Node->getcount();				//swaps
	Node->setcount(max->getcount());
	max->setcount(temp);
	string* _temp = Node->getstr();
	Node->setstr(max->getstr());
	max->setstr(_temp);


}


void MaxHeap::Heapify(MaxHeapNode* R){		//recurisve heapify from root to leafs

	if(R==NULL)	//base condition
		return;
	if(R->getleft()!=NULL){

		Heapify(R->getleft());
	}
	if(R->getright()!=NULL){

		Heapify(R->getright());
	}

	ShiftUP(R);		//call helperr

}

 void MaxHeap::Preorder(MaxHeapNode* Node){			//Preorder print of Maxheap
	if (Node==NULL)
		return;
	cout << *Node->getstr() <<"||" <<Node->getcount() << endl;
	Preorder(Node->getleft());
	Preorder(Node->getright());
}








void MaxHeap::Insert(MaxHeapNode * newNode){		//Insert a node into the max heap with the help of a Q
													//Q is used to manage level order travelsal and insertion
													// and then heapify iis called to preserve Maxheap attributes
	if (Root==NULL){
		Root = newNode;
		return;
	}
	Q->enQ(Root);			//push Root

	while(Q->QEmpty()==0){			

		MaxHeapNode * Node = Q->getfront()->getdata();			//start looking for space from the correct(level order) node
	
		Q->deQ();

		if (Node->getleft()==NULL){		//space left
			Node->setleft(newNode);
			Heapify(Root);
			break;
		
		}else if(Node->getright()==NULL){		//space right
			Node->setright(newNode);
			Heapify(Root);				
			break;
		
		}else{
			Q->enQ(Node->getleft());		//no space add den children to Q
			Q->enQ(Node->getright());
		}
	}
	Q->Destroy();	//node inserted so Q is no longer needed

}

void MaxHeap::RemoveRootHelper(MaxHeapNode* Root,MaxHeapNode* Node,Queue* Q){ 		//cheecky removal-deactivation of a node
	
	string*	tempstr = Root->getstr();
	int tempcount = Root ->getcount();
		if (Node!=Root){

			Node =Q->getback()->getdata();		//this is the correct heapnode which you wanna swap into being the root 
			Root->setstr(Node->getstr());		//swap the data between the root and the node
			Root->setcount(Node->getcount());
			Node->setstr(tempstr);
		}
		Node->setcount(-1*tempcount);			//trick to deactivate  node 
		//cout << Node->getcount() << endl;

		Heapify(Root);	//Essential to heapify after removing a node to keep maxheapnode attributes
}

void MaxHeap::RemoveRoot(void){

	if (Root==NULL || Root->getcount()<0){	//either no rootnode or no more positive casecounts
		return;
	}
	Q->enQ(Root);

	while(Q->QEmpty()==0){

		MaxHeapNode * Node = Q->getfront()->getdata();		
		Q->deQ();

		if (Node->getleft()==NULL || Node->getleft()->getcount()<0){			//watch for a node which is either followed by null or negative
			RemoveRootHelper(Root,Node,Q);
			break;
		}
		else
			Q->enQ(Node->getleft()); //this will allow me to pick the correct node to be inserted into root later

		if(Node->getright()==NULL || Node->getright()->getcount()<0){
			RemoveRootHelper(Root,Node,Q);		
			break;
		}	
		else
			Q->enQ(Node->getright()); ////this will allow me to pick the correct node to be inserted into root later
	}

	Q->Destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////