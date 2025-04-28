#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

class Student {
private:
    int roll_no;
    string name;
    string division;
    string address;
    static const int NAME_SIZE = 30;
    static const int DIV_SIZE = 5;
    static const int ADDR_SIZE = 50;
    static const int RECORD_SIZE = sizeof(int) + NAME_SIZE + DIV_SIZE + ADDR_SIZE;
    
public:
    Student() : roll_no(0), name(""), division(""), address("") {}

    Student(int r, string n, string d, string a)
        : roll_no(r), name(n), division(d), address(a) {}

    void insert() {
        fstream file("student.txt", ios::in | ios::out | ios::binary);
        if (!file) {
            file.open("student.txt", ios::out | ios::binary);
            file.close();
            file.open("student.txt", ios::in | ios::out | ios::binary);
        }

        streampos pos = (roll_no - 1) * RECORD_SIZE;
        file.seekp(pos, ios::beg);
        file.write(reinterpret_cast<char*>(&roll_no), sizeof(int));

        char nameArr[NAME_SIZE] = {0};
        strncpy(nameArr, name.c_str(), NAME_SIZE);
        file.write(nameArr, NAME_SIZE);

        char divArr[DIV_SIZE] = {0};
        strncpy(divArr, division.c_str(), DIV_SIZE);
        file.write(divArr, DIV_SIZE);

        char addrArr[ADDR_SIZE] = {0};
        strncpy(addrArr, address.c_str(), ADDR_SIZE);
        file.write(addrArr, ADDR_SIZE);

        file.close();
        cout << "Student added" << endl;
    }

    static void display(int x) {
        fstream file("student.txt", ios::in | ios::binary);
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }

        streampos pos = (x - 1) * RECORD_SIZE;
        file.seekg(0, ios::end);
        if (file.tellg() < pos + RECORD_SIZE) {
            cout << "Student not found" << endl;
            return;
        }

        file.seekg(pos, ios::beg);
        int r;

        file.read(reinterpret_cast<char*>(&r), sizeof(int));
        if (r == 0) {
            cout << "Student not found" << endl;
            return;
        }

        char nameArr[NAME_SIZE + 1] = {0};
        char divArr[DIV_SIZE + 1] = {0};
        char addrArr[ADDR_SIZE + 1] = {0};

        file.read(nameArr, NAME_SIZE);
        file.read(divArr, DIV_SIZE);
        file.read(addrArr, ADDR_SIZE);

        cout << "\nRoll Number: " << r << endl;
        cout << "Name: " << nameArr << endl;
        cout << "Division: " << divArr << endl;
        cout << "Address: " << addrArr << endl;
        file.close();
    }

    static void erase(int x) {
        fstream file("student.txt", ios::in | ios::out | ios::binary);
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }
        
        streampos pos = (x - 1) * RECORD_SIZE;
        file.seekg(0, ios::end);
        if (file.tellg() < pos + RECORD_SIZE) {
            cout << "Student not found" << endl;
            return;
        }

        file.seekg(pos, ios::beg);
        int r;

        file.read(reinterpret_cast<char*>(&r), sizeof(int));
        if (r == 0) {
            cout << "Student not found" << endl;
            return;
        }

        int zero = 0;
        file.seekp(pos, ios::beg);
        file.write(reinterpret_cast<char*>(&zero), sizeof(int));
        file.close();
        cout << "Student deleted" << endl;
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