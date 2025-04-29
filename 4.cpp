#include<iostream>
#include<stack>
using namespace std;

class TreeNode{
    public:
        string key;
        string meaning;
        TreeNode* left;
        TreeNode* right;

        TreeNode(){
            key = " ";
            meaning = " ";
            left = NULL;
            right = NULL;
        }

        TreeNode(string k, string m):key(k),meaning(m),left(NULL),right(NULL){};

        ~TreeNode(){
            delete left;
            delete right;
        }

        friend class BST;
};

class BST{
    public:
        TreeNode* root;
        BST(){
            root = NULL;
        }
        ~BST(){
            delete root;
        }

        //CREATING NEW WORD
        void create(string key, string meaning){
            TreeNode* newword = new TreeNode(key,meaning);
            if(root==NULL){
                root = newword;
            }
            else{
                TreeNode* temp = root;
                while(temp!=NULL){
                    if(key<temp->key){
                        if(temp->left==NULL){
                            temp->left=newword; 
                            break;
                        }
                        else {
                            temp=temp->left;
                        }
                    }
                    else{
                        if(temp->right==NULL){
                            temp->right=newword;
                            break;
                        }
                        else{
                            temp=temp->right;
                        }
                    }

                }
            }
        }

        //DISPLAYING WORDS IN ASCENDING ORDER
        void display_ass(TreeNode* temp){
            if(temp==NULL) return;
            display_ass(temp->left);
            cout<<temp->key<<" : "<<temp->meaning<<endl;
            display_ass(temp->right);
        }

        //DISPLAYING WORDS IN DESCENDING ORDER
        void display_des(TreeNode* temp){
            if(temp==NULL) return;
            display_des(temp->right);
            cout<<temp->key<<" : "<<temp->meaning<<endl;
            display_des(temp->left);
        }

        //SEARCHING MEANING 
        void search(string word){
            TreeNode* temp = root;
            int comp = 1;
            while(temp!=NULL){
                if(word==temp->key){
                    cout<<temp->key<<" : "<<temp->meaning<<endl;
                    cout<<"Word found with "<<comp<<" comparisns"<<endl;
                    return;
                }
                if(word<temp->key){
                    temp = temp->left;
                    comp++;
                }
                else{
                    temp = temp->right;
                    comp++;
                }
            }
            cout<<"The word is not present!"<<endl;

        }
        
        //UPDATING MEANING
        void update(string word){
            TreeNode* temp = root;
            while(temp!=NULL){
                if(word==temp->key){
                    string newmeaning;
                    cout<<"Enter new meaning : ";
                    cin>>newmeaning;
                    temp->meaning = newmeaning;
                    return;
                }
                else{
                    if(word<temp->key){
                        temp = temp->left;
                    }
                    else{
                        temp = temp->right;
                    }
                }
            }
            cout<<"The word is not present!"<<endl;
            cout<<"Do you want to insert this in Dictionary?(y/n)";
            char ch;
            cin>>ch;
            if(ch=='y'){
                string meaning;
                cout<<"Enter meaning : ";
                cin>>meaning;
                create(word,meaning);
            }
        }

        //DELETE WORD IN DICTIONARY
        void deleteword(string word){
            TreeNode* current = root;
            TreeNode* parent = NULL;
            while(current!=NULL){
                if(current->key==word){
                    //case 1
                    if(current->left==NULL && current->right==NULL){
                        if(current==root){
                            root = NULL;
                        }
                        else{
                            deleteleaf(parent,current);
                        }
                    }
                    //case 2
                    else if(current->left!=NULL && current->right==NULL){
                        if(current==root){
                            root = current->left;
                        }
                        else{
                            deleteleftsingle(parent,current);
                        }
                    }
                    else if(current->left==NULL && current->right!=NULL){
                        if(current==root){
                            root = current->right;
                        }
                        else{
                            deleterightsingle(parent,current);
                        }
                    }
                    //case 3
                    else{
                        TreeNode* temp = current->left;
                        TreeNode* temp_parent = NULL;
                        //traverse to rightmost node in left subtree
                        while(temp->right!=NULL){
                            temp_parent = temp;
                            temp = temp->right;
                        }
                        current->key = temp->key;
                        current->meaning = temp->meaning;

                        //deleting the maximum node found
                        if(temp_parent !=NULL){
                            deleteleftsingle(parent,current);
                        }
                        else{
                            current->left = temp->left;
                        }
                    }
                    return;
                }
                else{
                    if(word<current->key){
                        parent = current;
                        current = current->left;
                    }
                    else{
                        parent = current;
                        current = current->right;
                    }
                }
            }
            cout<<"The word is not present"<<endl;
        }

        //DELETE LEAF NODE
        void deleteleaf(TreeNode* parent,TreeNode* current){
            if(parent->left==current){
                parent->left=NULL;
            }
            else{
                parent->right=NULL;
            }
            delete current;
        }

        //DELETE SINGLE LEFT NODE
        void deleteleftsingle(TreeNode* parent,TreeNode* current){
            if(parent->left==current){
                parent->left=current->left;
            }
            else{
                parent->right=current->left;
            }
            delete current;
        }

        //DELETE SINGLE RIGHT NODE
        void deleterightsingle(TreeNode* parent,TreeNode* current){
            if(parent->left==current){
                parent->left=current->right;
            }
            else{
                parent->right=current->right;
            }
            delete current;
        }

};

int main(){
    BST bst;
    int choice;
    string w,m;
    do{
        cout<<"-----MENU------"<<endl;
        cout<<"1.Create/Insert words"<<endl;
        cout<<"2.Display - Ascending order"<<endl;
        cout<<"3.Display - Descending order"<<endl;
        cout<<"4.Update meaning"<<endl;
        cout<<"5.Search meaning"<<endl;
        cout<<"6.Delete word-meaning"<<endl;
        cout<<"7.EXIT"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"Enter word : ";
                cin>>w;
                cout<<"Enter meaning : ";
                cin>>m;
                bst.create(w,m);
                cout<<"Word inserted in Dictionary"<<endl;
                break;
            }
            case 2:{
                bst.display_ass(bst.root);
                break;
            }
            case 3:{
                bst.display_des(bst.root);
                break;
            }
            case 4:{
                cout<<"Enter word : ";
                cin>>w;
                bst.update(w);
                break;
            }
            case 5:{
                cout<<"Enter word : ";
                cin>>w;
                bst.search(w);
                break;
            }
            case 6:{
                cout<<"Enter word : ";
                cin>>w;
                bst.deleteword(w);
                break;
            }
            case 7:{
                cout<<"Exiting program"<<endl;
                break;
            }
            default:{
                cout<<"Invalid choice"<<endl;
            }
        }
    }while(choice!=7);
}


// OUTPUT
// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 1
// Enter word : halo
// Enter meaning : hello
// Word inserted in Dictionary
// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 1
// Enter word : cat
// Enter meaning : animal
// Word inserted in Dictionary
// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 1
// Enter word : parrot
// Enter meaning : bird
// Word inserted in Dictionary

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 2
// cat : animal
// halo : hello
// parrot : bird

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 3
// parrot : bird
// halo : hello
// cat : animal

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 4
// Enter word : cat
// Enter new meaning : anima

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 4
// Enter word : ball
// The word is not present!
// Do you want to insert this in Dictionary?(y/n)y
// Enter meaning : thing

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 5
// Enter word : ball
// ball : thing
// Word found with 3 comparisns

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 6
// Enter word : cat
// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 6
// Enter word : parrot

// -----MENU------
// 1.Create/Insert words
// 2.Display - Ascending order
// 3.Display - Descending order
// 4.Update meaning
// 5.Search meaning
// 6.Delete word-meaning
// 7.EXIT
// Enter choice : 7
// Terminal will be reused by tasks, press any key to close it. 


