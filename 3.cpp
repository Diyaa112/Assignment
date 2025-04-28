#include<iostream>
#include<stack>
using namespace std;

class TreeNode{
    public:
        int data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(){
            data = 0;
            left = NULL;
            right = NULL;
        }

        TreeNode(int d):data(d),left(NULL),right(NULL){};

        ~TreeNode(){
            delete left;
            delete right;
        }

        friend class BinaryTree;
};

class BinaryTree{
        
    public:
        TreeNode* root;
        BinaryTree(){
            root = NULL;
        }
        ~BinaryTree(){
            delete root;
        }

        //CREATE BINARY TREE
        void create(int element){
            TreeNode* newnode = new TreeNode(element);

            if(root==NULL){
                root = newnode;
            }
            else{
                TreeNode* temp = root;
                do{
                    char ch;
                    cout<<"Do you want to enter node at right/left for : "<< temp->data<<" ?"<<endl<<"Press l for left, r for right : ";
                    cin>>ch;
                    if(ch=='l'){
                        if(temp->left==NULL){
                            temp->left = newnode;
                            //newnode->data = element;
                            temp = newnode;
                        }
                        else{
                            temp = temp->left;
                        }
                    }
                    else if(ch=='r'){
                        if(temp->right==NULL){
                            temp->right = newnode;
                            temp = newnode;
                        }
                        else{
                            temp = temp->right;
                        }
                    }
                }while(temp!=newnode);
            }
        }

        //PREORDER (RECURSSIVE)
        void r_pre(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            cout<<temp->data<<" ";
            r_pre(temp->left);
            r_pre(temp->right);
        }
        //PREORDER (ITERATIVE)
        void i_pre(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            stack<TreeNode*>st;
            TreeNode* current = temp;
            while(current!=NULL || !st.empty()){
                while(current!=NULL){
                    cout<<current->data<<" ";
                    if(current->right!=NULL){
                        st.push(current->right);
                    }
                    current = current->left;
                }
                if(!st.empty()){
                    current = st.top();
                    st.pop();
                }
            }

        }

        //INORDER (RECURSSIVE)
        void r_in(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            r_in(temp->left);
            cout<<temp->data<<" ";
            r_in(temp->right);
        }
        //INORDER (ITERATIVE)
        void i_in(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            stack<TreeNode*>st;
            TreeNode* current = temp;
            while(current!=NULL || !st.empty()){
                while(current!=NULL){
                    st.push(current);
                    current = current->left;
                }
                current = st.top();
                st.pop();
                cout<<current->data<<" ";
                current = current->right;
            }
        }

        //POSTORDER (RECURSSIVE)
        void r_post(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            r_post(temp->left);
            r_post(temp->right);
            cout<<temp->data<<" ";
        }
        //POSTORDER (ITERATIVE)
        void i_post(TreeNode* temp){
            if(temp==NULL){
                return;
            }
            stack<TreeNode*>st1,st2;
            st1.push(temp);
            TreeNode* current = temp;
            while(!st1.empty()){
                current = st1.top();
                st1.pop();
                st2.push(current);
                if(current->left!=NULL){
                    st1.push(current->left);
                }
                if(current->right){
                    st1.push(current->right);
                }
            }
            while(!st2.empty()){
                current = st2.top();
                st2.pop();
                cout<<current->data<<" ";
            }
        }

        //COUNT LEAF NODES
        int leafnodes(TreeNode* temp){
            if(temp==NULL){
                return 0;
            }
            if(temp->left==NULL && temp->right==NULL){
                return 1;
            }
            return leafnodes(temp->left)+leafnodes(temp->right);
        }

        //COUNT INTERNAL NODES
        int internalnodes(TreeNode* temp){
            if(temp==NULL || (temp->left==NULL && temp->right==NULL)){
                return 0;
            }
            return 1+internalnodes(temp->left)+internalnodes(temp->right);
        }

        //COPY BINARY TREE
        TreeNode* copytree(TreeNode* temp){
            if(temp==NULL){
                return NULL;
            }
            TreeNode* root_copy = new TreeNode(temp->data);
            root_copy->left = copytree(temp->left);
            root_copy->right = copytree(temp->right);
            return root_copy;
        }
        BinaryTree& operator=(const BinaryTree obj){
            if(this ==&obj){
                return *this;
            }
            this->root = copytree(obj.root);
            return *this;
        }

        //HEIGHT OF TREE
        int height(TreeNode* temp){
            if(temp==NULL) return 0;
            int leftheight = height(temp->left);
            int rightheight = height(temp->right);
            return 1+max(leftheight,rightheight);
        }

        //MIRRORING OF TREE
        void mirror(TreeNode* temp){
            if(temp==NULL) return;
            TreeNode* current = temp->left;
            temp->left = temp->right;
            temp->right = current;
            mirror(temp->left);
            mirror(temp->right);
        }

        //DELETE TREE
        void deletebt(){
            delete root;
            root = NULL;
        }
};

int main(){
    BinaryTree bt;
    int choice;
    int element;
    do{
        cout<<"---MENU---"<<endl;
        cout<<"1.Create Binary tree"<<endl;
        cout<<"2.Recursive Traversals"<<endl;
        cout<<"3.Iterative Traversals"<<endl;
        cout<<"4.Count of nodes"<<endl;
        cout<<"5.Copy Binary Tree"<<endl;
        cout<<"6.Height of Tree"<<endl;
        cout<<"7.Mirror of Tree"<<endl;
        cout<<"8.Delete Tree"<<endl;
        cout<<"9.EXIT"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;

        switch(choice){
            case 1:{
                cout<<"Enter node : ";
                cin>>element;
                
                bt.create(element);
                break;
            }
            case 2:{
                cout<<"Preorder : ";
                bt.r_pre(bt.root);
                cout<<endl<<"Inorder : ";
                bt.r_in(bt.root);
                cout<<endl<<"Postorder : ";
                bt.r_post(bt.root);
                cout<<endl;
                break;
            }
            case 3:{
                cout<<"Preorder : ";
                bt.i_pre(bt.root);
                cout<<endl<<"Inorder : ";
                bt.i_in(bt.root);
                cout<<endl<<"Postorder : ";
                bt.i_post(bt.root);
                cout<<endl;
                break;
            }
            case 4:{
                cout<<"Leaf nodes : "<<bt.leafnodes(bt.root);
                cout<<endl<<"Internal nodes : "<<bt.internalnodes(bt.root);
                cout<<endl;
                break;
            }
            case 5:{
                TreeNode* copy = bt.copytree(bt.root);
                cout<<"Tree Copied.."<<endl;
                cout<<"Memory of original tree"<<&bt.root<<endl;
                cout<<"Memory of copied tree"<<&copy<<endl;
                //bt.copytree(bt.root);
                break;
            }
            case 6:{
                int h = bt.height(bt.root);
                cout<<"Height of Tree : "<<h;
                cout<<endl;
                break;
            }
            case 7:{
                cout<<"Mirroring of Tree Done.."<<endl;
                bt.mirror(bt.root);
                break;
            }
            case 8:{
                cout<<"Binary Tree Deleted.."<<endl;
                bt.deletebt();
                break;
            }
            case 9:{
                cout<<"Exiting program..."<<endl;
                break;
            }
            default:{
                cout<<"Invalid Choice..."<<endl;
            }
        }
    }while(choice!=9);
}



// OUTPUT
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 1
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 2
// Do you want to enter node at right/left for : 1 ?
// Press l for left, r for right : l
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 3
// Do you want to enter node at right/left for : 1 ?
// Press l for left, r for right : r
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 4
// Do you want to enter node at right/left for : 1 ?
// Press l for left, r for right : l
// Do you want to enter node at right/left for : 2 ?
// Press l for left, r for right : l
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 5
// Do you want to enter node at right/left for : 1 ?
// Press l for left, r for right : l
// Do you want to enter node at right/left for : 2 ?
// Press l for left, r for right : r
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 1
// Enter node : 6
// Do you want to enter node at right/left for : 1 ?
// Press l for left, r for right : r
// Do you want to enter node at right/left for : 3 ?
// Press l for left, r for right : l

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 2
// Preorder : 1 2 4 5 3 6 
// Inorder : 4 2 5 1 6 3 
// Postorder : 4 5 2 6 3 1 

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 3
// Preorder : 1 2 4 5 3 6 
// Inorder : 4 2 5 1 6 3 
// Postorder : 4 5 2 6 3 1 
// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 4
// Leaf nodes : 3
// Internal nodes : 3

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 5
// Tree Copied..
// Memory of original tree0x7ffc29577bd8
// Memory of copied tree0x7ffc29577be0

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 6
// Height of Tree : 3

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 7
// Mirroring of Tree Done..

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 2
// Preorder : 1 3 6 2 5 4 
// Inorder : 3 6 1 5 2 4 
// Postorder : 6 3 5 4 2 1 

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 8
// Binary Tree Deleted..

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 2
// Preorder : 
// Inorder : 
// Postorder : 

// ---MENU---
// 1.Create Binary tree
// 2.Recursive Traversals
// 3.Iterative Traversals
// 4.Count of nodes
// 5.Copy Binary Tree
// 6.Height of Tree
// 7.Mirror of Tree
// 8.Delete Tree
// 9.EXIT
// Enter choice : 9
// Exiting program...
