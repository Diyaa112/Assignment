#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int roll;
    char name[50];
    char address[100];
};

// Insert a student record at a position based on roll number
void insertRecord(const string& filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        // If file doesn't exist, create a new one
        file.open(filename, ios::out | ios::binary);
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
    }

    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter name: ";
    cin.getline(s.name, 50);
    cout << "Enter address: ";
    cin.getline(s.address, 100);

    file.seekp(s.roll * sizeof(Student), ios::beg);
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();

    cout << "Record inserted.\n";
}

// Delete a student record by setting roll = 0 and clearing data
void deleteRecord(const string& filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read(reinterpret_cast<char*>(&s), sizeof(Student));

    if (file && s.roll != 0) {
        s.roll = 0;
        strcpy(s.name, "");
        strcpy(s.address, "");

        file.seekp(roll * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char*>(&s), sizeof(Student));

        cout << "Record deleted.\n";
    } else {
        cout << "Record not found.\n";
    }
    file.close();
}

// Display a student record by roll number
void displayRecord(const string& filename) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to display: ";
    cin >> roll;

    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read(reinterpret_cast<char*>(&s), sizeof(Student));

    if (file && s.roll != 0) {
        cout << "\nRecord Found:\n";
        cout << "Roll Number: " << s.roll << endl;
        cout << "Name: " << s.name << endl;
        cout << "Address: " << s.address << endl;
    } else {
        cout << "Record not found.\n";
    }

    file.close();
}

int main() {
    string filename = "student.dat";
    int choice;

    do {
        cout << "\n--- Direct Access File Operations ---\n";
        cout << "1. Insert Record\n2. Delete Record\n3. Display Record\n4. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: insertRecord(filename); break;
            case 2: deleteRecord(filename); break;
            case 3: displayRecord(filename); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
