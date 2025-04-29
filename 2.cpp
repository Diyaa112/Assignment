#include<iostream>
using namespace std;

class Node{
   private:
   string key;
   string value;
   Node*link;
   
   public:
   Node(){
       key = " ";
       value = " ";
       link = NULL;
   }
   Node(string key, string value){
       this->key = key;
       this->value = value;
       link = NULL;
   }
   friend class Dictionary;
};

class Dictionary{
   private:
   Node **hashtable; 
   //array of pointers to node

   //FUNCTION TO COMPUTE INDEX
   int hashingfun(string &word){
       int count = 0;
       int len = word.length();
       for(int i = 0; i<len; i++){
           word[i]=char(tolower(word[i]));
           count+=word[i]-'a';
       }
       return (count%100);
   }
   public:
   Dictionary(){
       hashtable = new Node*[100]; //allocating memory for hash table
       for(int i=0; i<100; i++){
           hashtable[i] = NULL;
       }
   }
   
   //INSERT FUNCTION
   void insert(string &word,string &meaning){
       int index = hashingfun(word);
       Node *prev = NULL;
       Node *current = hashtable[index];
       Node *newWord = new Node(word,meaning);


       while(current!=NULL&&current->key!=word){
           prev = current;
           current = current->link;
       }
       //word doesnt exist
       if(current ==NULL){
           current = newWord;
           if(prev==NULL){
               hashtable[index] = current;
               cout<<"Word inserted in dictionary"<<endl;
           }
           else{
               prev->link = current;
           }
       }
       //word already exist
       else{
           cout<<"The word "<<word<<" already exists with meaning "<<current->value<<endl;
           char ch = 'n';
           cout<<"Do you want to update the meaning?(y/n): ";
           cin>>ch;
           if(ch=='y'){
               current->value = meaning;
               cout<<"Meaning updated successfully"<<endl;
           }
       }
   }

   //SEARCH FUNCTION
   void search(string &word){
       int index = hashingfun(word);
       Node* current = hashtable[index];


       if(current==NULL){
           cout<<"Word not present in Dictionary"<<endl;
           return;
       }
       else{
           while(current!=NULL){
               if(current->key==word){
                   cout<<"The meaning is : "<<current->value<<endl;
                   return;
               }
               current = current->link;
           }
           cout<<"Word not present in Dictionary"<<endl;
       }
   }

   //DELETE FUNCTION
   void deleteit(string &word){
       int index = hashingfun(word);
       Node* current = hashtable[index];
       Node *prev = NULL;


       if(current==NULL){
           cout<<"Word not present in Dictionary"<<endl;
           return;
       }
       else{
           while(current!=NULL){
               if(current->key==word){
                   if(current->link==NULL){
                       hashtable[index]=current->link;
                       current->link=NULL;
                       cout<<"Word Deleted"<<endl;
                       return;
                   }
                   else{
                       prev->link = current->link;
                       delete current;
                       cout<<"Word Deleted"<<endl;
                       return;
                   }
                  
               }
               prev = current;
               current = current->link;
           }
           cout<<"Word not present in Dictionary"<<endl;
       }
   }

   //DISPLAY FUNCTION
   void display(){
       bool flag = true;
       for(int i=0; i<100; i++){
           Node* current = hashtable[i];
           while(current!=NULL){
               flag = false;
               cout<<current->key<<" : "<<current->value<<endl;
               current = current->link;


           }
       }
       if(flag){
           cout<<"Dictionary is empty"<<endl;
       }
   }
};

int main(){
   Dictionary Dict;
   int choice;
   string word;
   do{
       cout<<"---------Menu----------"<<endl;
       cout<<"1.Insert new word"<<endl;
       cout<<"2.Search meaning"<<endl;
       cout<<"3.Delete word-meaning"<<endl;
       cout<<"4.Display Dictionary"<<endl;
       cout<<"5.EXIT"<<endl;
       cout<<"Enter choice : ";
       cin>>choice;
       switch(choice){
           case 1:{
               string meaning;
               cout<<"Enter word : ";
               cin>>word;
               cout<<"Enter meaning : ";
               cin.ignore();
               getline(cin,meaning);
               Dict.insert(word,meaning);
               break;
           }
           case 2:{
               cout<<"Enter word : ";
               cin>>word;
               Dict.search(word);
               break;
           }
           case 3:{
               cout<<"Enter word : ";
               cin>>word;
               Dict.deleteit(word);
               break;
           }
           case 4:{
               Dict.display();
               break;
           }
           case 5:{
               cout<<"Exiting the program..."<<endl;
               break;
           }
           default :{
               cout<<"Invalid choice!!!"<<endl;
               break;
           }
       }
   }while(choice!=5);
}

// OUTPUT
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 1
// Enter word : approach
// Enter meaning : move towards
// Word inserted in dictionary
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 1
// Enter word : explain
// Enter meaning : elaborate
// Word inserted in dictionary
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 4
// approach : move towards
// explain : elaborate
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 2
// Enter word : explain
// The meaning is : elaborate
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 2
// Enter word : happy
// Word not present in Dictionary
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 3
// Enter word : explain
// Word Deleted
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 4
// approach : move towards
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 3
// Enter word : happy
// Word not present in Dictionary
// ---------Menu----------
// 1.Insert new word
// 2.Search meaning
// 3.Delete word-meaning
// 4.Display Dictionary
// 5.EXIT
// Enter choice : 
// 5
// Exiting the program...
// === Code Execution Successful ===

