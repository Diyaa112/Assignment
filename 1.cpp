#include <iostream>
using namespace std;

class client {
public:
    string name;
    long phone;

    client() : name(" "), phone(0) {}
    client(string n, long p) : name(n), phone(p) {}
};

class hashtable {
public:
    client table[10];
    int size;
    int count;

    hashtable(int s) {
        size = s;
        count = 0;
        for (int i = 0; i < size; i++) {
            table[i] = client();
        }
    }

    int hashfunction(string name) {
        return (name[0]) % size;

    }

    // Insert function
    int insert(client cl, bool withrep) {
        if (count >= size) {
            cout << "Hash table is full" << endl;
            return -1;
        }

        int index = hashfunction(cl.name);
        int comp = 0;

        while (table[index].name != " ") {
            comp += 1;

            if (withrep) {
                // Check if the current entry matches the new client's name
                if (table[index].name == cl.name) {
                    table[index] = cl;
                    return comp;
                }
            }

            // Handle displacement of existing client
            if (hashfunction(table[index].name) != index) {
                client existingcl = table[index];
                table[index] = cl;

                int newindex = hashfunction(existingcl.name);
                while (table[newindex].name != " ") {
                    comp += 1;
                    newindex = (newindex + 1) % size;
                }
                table[newindex] = existingcl;
                return comp;
            }

            // Linear probing
            index = (index + 1) % size;
        }

        // Insert new client
        table[index] = cl;
        count++;
        return comp;
    }

    // Search function
    void searchv(string name) {
        int index = hashfunction(name);
        int comparisons = 0;

        while (table[index].name != " ") {
            comparisons++;
            if (table[index].name == name) {
                cout << "Found Phone no: " << table[index].phone << " with " << comparisons << " comparisons." << endl;
                return;
            }

            // Linear probing
            index = (index + 1) % size;
        }

        cout << "Record not found." << endl;
    }

    // Display function
    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i].name != " ") {
                cout<<table[i].name << " - " << table[i].phone << endl;
            } 
        }
    }
};

int main() {
    hashtable h(10);
    int n;
    do{
        cout<<"-------Menu-------"<<endl;
        cout<<"1.Insert Entry"<<endl;
        cout<<"2.Display Entry"<<endl;
        cout<<"3.Search for Phone no"<<endl;
        cout<<"4.EXIT"<<endl;
        cout<<"Enter your Choice : ";
        cin>>n;

        switch (n) {
            case 1 : {
                int strategy;
                cout<<"Press 1 for WithReplacement"<<endl<<"Press 0 for WithoutReplacement"<<endl;
                cout<<"Enter number : ";
                cin>>strategy;
                string name;
                int phoneno;
                cout<<"Enter name : ";
                cin>>name;
                cout<<"Enter phone no : ";
                cin>>phoneno;
                if(strategy==1){
                    h.insert(client(name, phoneno), true);
                }
                else if(strategy==0){
                    h.insert(client(name, phoneno), false);
                }
                else{
                    cout<<"Invalid Choice";
                    break;
                }
                
                break;
            }
                

            case 2 : {
                h.display();
                break;
            }
                
            case 3: {
                string sname;
                cout<<"Enter name : ";
                cin>>sname;
                h.searchv(sname); 
                break;
            }
            
            case 4:{
                cout<<"Program Exited";
            }

            default:{
                cout<<"Invalid choice"<<endl;
                break;
            }
            
        }
        
    }while(n!=4);
    return 0;
}

// OUTPUT
// -------Menu-------
// 1.Insert Entry
// 2.Display Entry
// 3.Search for Phone no
// 4.EXIT
// Enter your Choice : 1
// Press 1 for WithReplacement
// Press 0 for WithoutReplacement
// Enter number : 1
// Enter name : Diya
// Enter phone no : 968523

// -------Menu-------
// 1.Insert Entry
// 2.Display Entry
// 3.Search for Phone no
// 4.EXIT
// Enter your Choice : 1
// Press 1 for WithReplacement
// Press 0 for WithoutReplacement
// Enter number : 1
// Enter name : Aarya
// Enter phone no : 123587

// -------Menu-------
// 1.Insert Entry
// 2.Display Entry
// 3.Search for Phone no
// 4.EXIT
// Enter your Choice : 2
// Aarya - 123587
// Diya - 968523

// -------Menu-------
// 1.Insert Entry
// 2.Display Entry
// 3.Search for Phone no
// 4.EXIT
// Enter your Choice : 3
// Enter name : Diya
// Found Phone no: 968523 with 1 comparisons.

// -------Menu-------
// 1.Insert Entry
// 2.Display Entry
// 3.Search for Phone no
// 4.EXIT
// Enter your Choice : 4
// Program ExitedInvalid choice




