#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Student {
private:
    int roll_no;
    string name;
    string division;
    string address;
    
public:
    Student() : roll_no(0), name(""), division(""), address("") {}

    Student(int r, string n, string d, string a)
        : roll_no(r), name(n), division(d), address(a) {}

    void insert() {
        ofstream file("student.txt", ios::app);
        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        file << roll_no << endl;
        file << name << endl;
        file << division << endl;
        file << address << endl;
        file.close();

        cout << "Student added" << endl;
    }

    bool read(ifstream &file) {
        string line;
        if (!getline(file, line))
            return false;
        roll_no = stoi(line);
        if (!getline(file, name))
            return false;
        if (!getline(file, division))
            return false;
        if (!getline(file, address))
            return false;
        return true;
    }

    static void display(int x) {
        ifstream file("student.txt");

        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }

        bool found = false;
        
        Student student;
        while (student.read(file)) {
            if (student.roll_no == x) {
                found = true;
                cout << "\nRoll Number: " << student.roll_no << endl;
                cout << "Name: " << student.name << endl;
                cout << "Division: " << student.division << endl;
                cout << "Address: " << student.address << endl;
            }
        }

        if(!found) cout << "Student not found" << endl;
    }

    static void erase(int x) {
        ifstream file("student.txt");
        ofstream temp("temp.txt");
        
        if (!file || !temp) {
            cerr << "Error opening file." << endl;
            return;
        }

        bool found = false;

        Student student;
        while(student.read(file)) {
            if(student.roll_no == x) {
                found = true;
                continue;
            }
            temp << student.roll_no << endl;
            temp << student.name << endl;
            temp << student.division << endl;
            temp << student.address << endl;
        }
        
        file.close();
        temp.close();

        remove("student.txt");
        rename("temp.txt", "student.txt");

        if(found) cout << "Student deleted" << endl;
        else cout << "Student not found" << endl;
    }
};

int main() {
    int k, roll_no;
    string name, div, address;

    do {
        cout << "\nEnter:";
        cout << "\n1 to add a student";
        cout << "\n2 to delete a student";
        cout << "\n3 to search for a student";
        cout << "\n4 to exit" << endl;
        cin >> k;

        cin.ignore();

        switch (k) {
            case 1:
                cout << "\nEnter roll number: ";
                cin >> roll_no;
                cin.ignore();
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter division: ";
                getline(cin, div);
                cout << "Enter address: ";
                getline(cin, address);
                {
                    Student s(roll_no, name, div, address);
                    s.insert();
                }
                break;

            case 2:
                cout << "\nEnter roll number to delete: ";
                cin >> roll_no;
                Student::erase(roll_no);
                break;

            case 3:
                cout << "\nEnter roll number to search: ";
                cin >> roll_no;
                Student::display(roll_no);
                break;

            case 4:
                break;

            default:
                cout << "\nInvalid choice" << endl;
        }
    } while (k != 4);
    return 0;
}