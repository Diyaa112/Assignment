/*Given sequence k = k1 <k2 < ... < kn of n sorted keys, with a search probability pi for each key ki. Build the Binary search tree that 
has the least search cost given the access probability for each key.*/

#include <bits/stdc++.h>

using namespace std;

struct node {
    int key;
    node* left;
    node* right;
    node(int k) : key(k), left(nullptr), right(nullptr) {};
};


class optimized_bst {
private:
    node* root;
    int n;
    int* keys;
    int* freq;
    int** cost;
    int** root_index;

    int sum_freq(int i, int j) {
        int sum = 0;
        for(int k=i ; k<=j ; ++k) sum += freq[k];
        return sum;
    }

    void optimal_bst() {
        for(int i=0 ; i<n ; ++i) {
            cost[i][i] = freq[i];
            root_index[i][i] = i;
        }
        for(int l=2 ; l<=n ; ++l) {
            for(int i=0 ; i<=n-l ; ++i) {
                int j = i+l-1;
                cost[i][j] = INT_MAX;
                for(int r=i ; r<=j ; ++r) {
                    int c = ((r > i) ? cost[i][r-1] : 0) + ((r < j) ? cost[r+1][j] : 0) + sum_freq(i, j);
                    if(c < cost[i][j]) {
                        cost[i][j] = c;
                        root_index[i][j] = r;
                    }
                }
            }
        }
    }

    node* build_tree(int i, int j) {
        if(i > j) return nullptr;
        node* newnode = new node(keys[root_index[i][j]]);
        newnode->left = build_tree(i, root_index[i][j]-1);
        newnode->right = build_tree(root_index[i][j]+1, j);
        return newnode;
    }

public:
    optimized_bst(int n, int* k, int* f) : n(n), keys(k), freq(f) {
        root = nullptr;
        cost = new int*[n];
        root_index = new int*[n];
        for(int i=0 ; i<n ; ++i) {
            cost[i] = new int[n];
            root_index[i] = new int[n];
        }
        optimal_bst();
        root = build_tree(0, n-1);
    }

    node* get_root() {
        return root;
    }

    int get_cost() {
        return cost[0][n-1];
    }

    void ascending(node* root, vector<int>& traversal) {
        if(!root) return;
        ascending(root->left, traversal);
        traversal.emplace_back(root->key);
        ascending(root->right, traversal);
    }
};


int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    int* keys = new int[n];
    int* freq = new int[n];
    for(int i=0 ; i<n ; ++i) {
        cout << "\nEnter key " << i+1 << ": ";
        cin >> keys[i];
        cout << "Enter frequency: ";
        cin >> freq[i];
    }

    optimized_bst tree(n, keys, freq);

    if(!tree.get_root()) cout << "\nTree is empty" << endl;
    else {
        cout << "\nOptimal Binary Search Tree: ";
        vector<int> traversal;
        tree.ascending(tree.get_root(), traversal);
        for(int i=0 ; i<traversal.size() ; ++i) cout << traversal[i] << " ";
    }

    cout << "\nCost: " << tree.get_cost() << endl;
}