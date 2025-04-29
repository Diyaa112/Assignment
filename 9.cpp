
#include <bits/stdc++.h>

using namespace std;

struct node {
    string keyword;
    string meaning;
    node* left;
    node* right;
    int height;
    node(string key, string mean) : keyword(key), meaning(mean), left(nullptr), right(nullptr), height(0) {};
};


class avl_bst {
private:
    node* root;

    int height(node* temp) {
        return temp ? temp->height : -1;
    }

    int balance_factor(node* temp) {
        return temp ? height(temp->left) - height(temp->right) : 0;
    }

    node* right_rotate(node* temp) {
        node* new_root = temp->left;
        temp->left = new_root->right;
        new_root->right = temp;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
        return new_root;
    }

    node* left_rotate(node* temp) {
        node* new_root = temp->right;
        temp->right = new_root->left;
        new_root->left = temp;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
        return new_root;
    }

    node* insert(node* temp, string key, string mean) {
        if(!temp) return new node(key, mean);
        if(key < temp->keyword) {
            temp->left = insert(temp->left, key, mean);
        } else if(key > temp->keyword) {
            temp->right = insert(temp->right, key, mean);
        } else {
            temp->meaning = mean; 
            return temp;
        }

        temp->height = max(height(temp->left), height(temp->right)) + 1;

        int balance = balance_factor(temp);

        if(balance > 1 && key < temp->left->keyword) {
            return right_rotate(temp);
        }
        if(balance < -1 && key > temp->right->keyword) {
            return left_rotate(temp);
        }
        if(balance > 1 && key > temp->left->keyword) {
            temp->left = left_rotate(temp->left);
            return right_rotate(temp);
        }
        if(balance < -1 && key < temp->right->keyword) {
            temp->right = right_rotate(temp->right);
            return left_rotate(temp);
        }

        return temp;
    }

    node* min_value_node(node* temp) {
        while(temp->left) {
            temp = temp->left;
        }
        return temp;
    }

    node* delete_node(node* temp, string key) {
        if(!temp) return nullptr;
        if(key < temp->keyword) {
            temp->left = delete_node(temp->left, key);
        } else if(key > temp->keyword) {
            temp->right = delete_node(temp->right, key);
        } else {
            if(!temp->left || !temp->right) {
                node* new_temp = temp->left ? temp->left : temp->right;
                delete temp;
                return new_temp;
            } else {
                node* new_temp = min_value_node(temp->right);
                temp->keyword = new_temp->keyword;
                temp->meaning = new_temp->meaning;
                temp->right = delete_node(temp->right, new_temp->keyword);
            }
        }

        if(!temp) return nullptr;

        temp->height = max(height(temp->left), height(temp->right)) + 1;

        int balance = balance_factor(temp);

        if(balance > 1 && balance_factor(temp->left) >= 0) {
            return right_rotate(temp);
        }
        if(balance < -1 && balance_factor(temp->right) <= 0) {
            return left_rotate(temp);
        }
        if(balance > 1 && balance_factor(temp->left) < 0) {
            temp->left = left_rotate(temp->left);
            return right_rotate(temp);
        }
        if(balance < -1 && balance_factor(temp->right) > 0) {
            temp->right = right_rotate(temp->right);
            return left_rotate(temp);
        }

        return temp;
    }

    void ascending(node* root, vector<pair<string, string>>& traversal) {
        if(!root) return;
        ascending(root->left, traversal);
        traversal.emplace_back(root->keyword, root->meaning);
        ascending(root->right, traversal);
    }

    void descending(node* root, vector<pair<string, string>>& traversal) {
        if(!root) return;
        descending(root->right, traversal);
        traversal.emplace_back(root->keyword, root->meaning);
        descending(root->left, traversal);
    }

    node* search(node* temp, string key, int& comparisions) {
        if(!temp) return nullptr;

        ++comparisions;
        if(key < temp->keyword) return search(temp->left, key, comparisions);
        else if(key > temp->keyword) return search(temp->right, key, comparisions);
        else return temp;
    }

public:
    avl_bst() : root(nullptr) {}

    node* get_root() {
        return root;
    }

    void insert(string key, string mean) {
        root = insert(root, key, mean);
    }

    void delete_key(string key) {
        root = delete_node(root, key);
    }

    void display_ascending() {
        vector<pair<string, string>> traversal;
        ascending(root, traversal);
        cout << "\nAscending order: " << endl;
        for(auto& pair : traversal) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void display_descending() {
        vector<pair<string, string>> traversal;
        descending(root, traversal);
        cout << "\nDescending order: " << endl;
        for(auto& pair : traversal) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    int update(string key, string new_mean) {
        int comparisions = 0;
        node* result = search(root, key, comparisions);
        if(result) {
            result->meaning = new_mean;
            return 1; 
        } else {
            return -1;
        }
    }

    string search_keyword(string key) {
        int comparisions = 0;
        node* result = search(root, key, comparisions);
        return result->meaning;
    }

    int get_comparisions(string key) {
        int comparisions = 0;
        node* result = search(root, key, comparisions);
        return result ? comparisions : -1;
    }
};


int main() {
	int k;
    string key, meaning;

	avl_bst dict;

	do {
		cout << "\nEnter: ";
		cout << "\n1 to insert a keyword in the dictionary";
        cout << "\n2 to delete a a keyword from the dictionary";
        cout << "\n3 to update meaning of a keyword";
        cout << "\n4 to display dictionary in ascending order";
		cout << "\n5 to display dictionary in descending order";
        cout << "\n6 to find keyword in dictionary";
		cout << "\n7 to exit" << endl;
		cin >> k;
        cin.ignore();

		switch(k) {
			case 1: {
                cout << "\nEnter '-1' to exit";
                while(true) {
				    cout << "\nKey: ";
				    getline(cin, key);
                    if(key == "-1") break;
                    cout << "Meaning: ";
                    getline(cin, meaning);
                    dict.insert(key, meaning);
				    cout << "Data inserted" << endl;
                }
				break;
			}

            case 2: {
                cout << "\nEnter keyword to delete: ";
                getline(cin, key);
                dict.delete_key(key);
                cout << "Keyword deleted" << endl;
                break;
			}

            case 3: {
                cout << "\nEnter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.update(key, meaning);
                cout << "Keyword updated" << endl;
                break;
			}

			case 4: {
				dict.display_ascending();
                break;
			}

            case 5: {
				dict.display_descending();
                break;
			}

            case 6: {
                cout << "\nEnter keyword to search: ";
                getline(cin, key);
                cout << "Meaning: " << dict.search_keyword(key) << endl;
                cout << "Comparisions: " << dict.get_comparisions(key) << endl;
                break;
            }

            case 7:
                break;

			default:
				cout << "Invalid Choice" << endl;
		}
	} while(k != 7);
}