#include<iostream>
#include<climits>
using namespace std;

class Treenode{
    public:
    int data;
    Treenode* left;
    Treenode* right;
    bool left_t;
    bool right_t;

    Treenode():data(0),left(NULL),right(NULL),left_t(true),right_t(true){};

    Treenode(int d):data(d),left(NULL),right(NULL),left_t(true),right_t(true){};
};

class thread_BST{
    public:
    Treenode* root;
    Treenode* dummy;

    thread_BST():root(NULL),dummy(NULL){};

    //CREATE FUNCTION
    void create(){
        int ele;
        cout<<"Enter the data of TreeNode : ";
        cin>>ele;
        Treenode* newnode = new Treenode(ele);

        if(root==NULL){
            //Tree is empty
            root = newnode;
            dummy = new Treenode(INT_MIN);
            dummy->left = root;
            dummy->left_t = false;
            dummy->right = dummy;
            dummy->right_t = false;
            root->left = dummy;
            root->left_t = true;
            root->right = dummy;
            root->right_t = true;
        }
        else{
            //insert new node at correct postition
            Treenode* current = root;
            while(true){
                if(newnode->data<current->data){
                    if(current->left_t==false){
                        current = current->left;
                    }
                    else{
                        break;
                    }
                }
                else{
                    if(current->right_t==false){
                        current = current->right;
                    }
                    else{
                        break;
                    }
                }
            }
            //linking the new node to current node
            if(newnode->data<current->data){
                newnode->left = current->left;
                newnode->left_t = true;
                newnode->right = current;
                newnode->right_t = true;
                current->left = newnode;
                current->left_t = false;
            }
            else{
                newnode->left = current;
                newnode->left_t = true;
                newnode->right = current->right;
                newnode->right_t = true;
                current->right = newnode;
                current->right_t = false;
            }
        }
    }

    //FIND SUCCESSOR FUNCTION
    Treenode* find_successor(Treenode* current){
        if(current->right_t==true){
            return current->right;
        }
        else{
            current = current->right;
            while(current->left_t==false){
                current = current->left;
            }
            return current;
        }
    }

    //INORDER TRAVERSAL FUNCTION
    void inorder(Treenode* current){
        if(current==NULL){
            cout<<"There is no inordered threaded Binary Tree created"<<endl;
            return;
        }
        //move to the leftmost node
        while(current->left_t==false){
            current = current->left;
        }
        //traverse the tree using successor links
        while(current!=dummy){
            cout<<current->data<<" ";
            current = find_successor(current);
        }
    }
    //WRAPPER FUNCTION FOR INORDER
    void inorder(){
        Treenode* current = root;
        inorder(current);
    }

    //PREORDER TRAVERSAL FUNCTION
    void preorder(Treenode* current){
        if(current==NULL){
            cout<<"There is no threaded Binary tree created"<<endl;
            return;
        }
        cout<<current->data<<" ";
        bool flag = false;
        while(current!=dummy){
            while(current->left_t==false && flag==false){
                current = current->left;
                cout<<current->data<<" ";
            }
            if(current->right_t==false){
                current = current->right;
                cout<<current->data<<" ";
                flag = false;
            }
            else{
                current = current->right;
                flag = true;
            }
        }
    }
    //WRAPPER FUNCTION FOR PREORDER
    void preorder(){
        Treenode* current = root;
        preorder(current);
    }

};

int main(){
    thread_BST tbst;
    int choice;
    do{
        cout<<"------MENU-------"<<endl;
        cout<<"1.Create threaded BST"<<endl;
        cout<<"2.Inorder traversal"<<endl;
        cout<<"3.Preorder traversal"<<endl;
        cout<<"4.EXIT"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:{
                tbst.create ();
                break;
            }
            case 2:{
                tbst.inorder();
                cout<<endl;
                break;
            }
            case 3:{
                tbst.preorder();
                cout<<endl;
                break;
            }
            case 4:{
                cout<<"Exiting program"<<endl;
	    break;
            }
            default:{
                cout<<"Invalid choice"<<endl;
    break;
            }
        }
    }while(choice!=4);
    
}

// OUTPUT

// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 5
// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 2
// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 1
// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 3
// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 6
// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 1
// Enter the data of TreeNode : 8

// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 2
// 1 2 3 5 6 8 

// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 3
// 5 2 1 3 6 8 

// ------MENU-------
// 1.Create threaded BST
// 2.Inorder traversal
// 3.Preorder traversal
// 4.EXIT
// Enter your choice : 4
// Exiting program
// Terminal will be reused by tasks, press any key to close it. 

