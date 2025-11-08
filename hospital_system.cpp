#include "hospital_system.h"

// Global variable definitions
vector<Account> accounts;
vector<Patient> patients;
string currentUser = " ";

void countdownClear() {
    for (int i = 3; i > 0; i--) {
        cout << "\rClearing screen in " << i << "... ";
        this_thread::sleep_for(chrono::seconds(1));
    }
    system("cls");
}

void countdownExit() {
    for (int i = 3; i > 0; i--) {
        cout << "\rExiting in " << i << "... ";
        this_thread::sleep_for(chrono::seconds(1));
    }
    exit(0);
}

void startMenu() {
    int choice;
    do {
        cout << "\n ===== ACCOUNT =====\n";
        cout << "1. Login\n";
        cout << "2. Sign up\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        system("cls");

        if (choice == 1) login();
        else if (choice == 2) signup();
        else if (choice == 3) {
            countdownExit();
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

// SIGN UP FUNCTION
void signup() {
    Account newAcc;
    string verifyID;

    cout << "===== STAFF SIGN UP =====\n";
    cout << "Enter hospital staff ID for verification: ";
    cin >> verifyID;

    if (!verifyStaffID(verifyID)) {
        cout << "Invalid Staff ID. You are not authorized to make an account.\n";
        countdownClear();
        return;
    }

    cout << "Staff ID verified.\n";
    cout << "Create username: ";
    cin >> newAcc.username;
    cout << "Create password: ";
    cin >> newAcc.password;
    newAcc.staffID = verifyID;

    // prevent duplicate usernames
    for (auto &acc : accounts) {
        if (acc.username == newAcc.username) {
            cout << "Username already taken. Try again.\n";
            countdownClear();
            return;
        }
    }

    accounts.push_back(newAcc);
    cout << "Account successfully created! You can now log in.\n";
    countdownClear();
}

bool verifyStaffID(string ID) {
    string validIDs[] = {"RN001", "RN002", "RN003", "DOC001", "DOC002", "DOC003"};
    for (string valid : validIDs) {
        if (ID == valid) return true;
    }
    return false;
}

// LOGIN FUNCTION
void login() {
    string username, password;
    bool found = false;

    cout << "===== LOGIN =====\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto &acc : accounts) {
        if (acc.username == username && acc.password == password) {
            found = true;
            currentUser = username;
            cout << "Login successful! Welcome, " << username << ".\n";
            countdownClear();
            menu();
            break;
        }
    }

    if (!found) {
        cout << "Invalid credentials. Please try again or sign up.\n";
        system("pause");
        system("cls");
    }
}

void logout() {
    cout << "Logging out...\n";
    currentUser = " ";
    countdownClear();
}

void menu() {
    int choice;
    do {
        cout << "\n===== PATIENT RECORD SYSTEM =====\n";
        cout << "Logged in as: " << currentUser << endl;
        cout << "1. Add Patient Record\n";
        cout << "2. Search Patient by Hospital ID\n";
        cout << "3. Delete a Patient Record\n";
        cout << "4. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;
        system("cls");

        if (choice == 1) addRecord();
        else if (choice == 2) searchPatient();
        else if (choice == 3) deletePatient();
        else if (choice == 4) logout();
        else cout << "Invalid choice. Try again.\n";

    } while (choice != 4 && currentUser != " ");
}

// ADD RECORD FUNCTION
void addRecord() {
    Patient p;
    cout << "\n--- Add New Patient Record ---\n";
    cin.ignore();

    cout << "Full Name: ";
    getline(cin, p.name);
    cout << "Age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Sex: ";
    getline(cin, p.sex);
    cout << "Room/Bed Number: ";
    getline(cin, p.room);
    cout << "Hospital ID: ";
    cin >> p.hospitalID;
    cin.ignore();
    p.dateTime = currentDateTime();
    cout << "Nurse Name: ";
    getline(cin, p.nurseName);
    cout << "Designation (e.g. RN, LPN): ";
    getline(cin, p.designation);

    cout << "\n--- Vital Signs ---\n";
    cout << "Temperature (°C): ";
    cin >> p.temperature;
    cout << "Pulse: ";
    cin >> p.pulse;
    cout << "Respiratory Rate: ";
    cin >> p.respiratoryRate;
    cin.ignore();
    cout << "Blood Pressure: ";
    getline(cin, p.bloodPressure);
    cout << "Oxygen Saturation (SpO2): ";
    cin >> p.oxygenSaturation;
    cout << "Height (m): ";
    cin >> p.height;
    cout << "Weight (kg): ";
    cin >> p.weight;
    p.bmi = p.weight / (p.height * p.height);
    cin.ignore();

    cout << "\n--- Subjective Data ---\n";
    getline(cin, p.subjective);
    cout << "\n--- Objective Data ---\n";
    getline(cin, p.objective);
    cout << "\n--- Lab / Test Results ---\n";
    getline(cin, p.labResults);
    cout << "\n--- Evaluation ---\n";
    getline(cin, p.evaluation);
    cout << "\n--- Unusual Incidents ---\n";
    getline(cin, p.incidents);
    cout << "\n--- Communication ---\n";
    cout << "Doctor Assigned: ";
    getline(cin, p.doctor);
    cout << "Family Notes: ";
    getline(cin, p.family);
    cout << "Orders and Follow-up: ";
    getline(cin, p.orders);
    p.nurseAttended = currentDateTime();

    patients.push_back(p);
    cout << "\nRecord added successfully!\n";
    countdownClear();
}

// SEARCH FUNCTION
void searchPatient() {
    if (patients.empty()) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n===== SEARCH PATIENT RECORD =====\n";
    cout << "Hospital ID     Name\n";
    cout << "--------------------------------\n";

    vector<Patient> sortedPatients = patients;

    for (int i = 0; i < sortedPatients.size() - 1; i++) {
        for (int j = i + 1; j < sortedPatients.size(); j++) {
            if (sortedPatients[i].hospitalID > sortedPatients[j].hospitalID) {
                swap(sortedPatients[i], sortedPatients[j]);
            }
        }
    }

    for (auto &p : sortedPatients)
        cout << p.hospitalID << "\t\t" << p.name << endl;

    cout << "--------------------------------\n";

    int id;
    cout << "\nEnter Hospital ID to view details: ";
    cin >> id;
    cin.ignore();

    bool found = false;

    for (auto &p : patients) {
        if (p.hospitalID == id) {
            found = true;
            cout << "\n--- PATIENT FOUND ---\n";
            cout << "Name: " << p.name << endl;
            cout << "Age: " << p.age << " | Sex: " << p.sex << endl;
            cout << "Room: " << p.room << endl;
            cout << "Hospital ID: " << p.hospitalID << endl;
            cout << "Date/Time: " << p.dateTime << endl;
            cout << "Nurse: " << p.nurseName << " " << p.designation << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    if (!found) {
        cout << "\nNo patient found with Hospital ID: " << id << endl;
        countdownClear();
    }
}

// DELETE FUNCTION
void deletePatient() {
    if (patients.empty()) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n===== DELETE PATIENT RECORD =====\n";
    cout << "Hospital ID     Name\n";
    cout << "--------------------------------\n";

    for (auto &p : patients)
        cout << p.hospitalID << "\t\t" << p.name << endl;

    cout << "--------------------------------\n";

    int id;
    cout << "\nEnter Hospital ID to delete: ";
    cin >> id;
    cin.ignore();

    bool found = false;
    for (int i = 0; i < patients.size(); i++) {
        if (patients[i].hospitalID == id) {
            found = true;
            cout << "Are you sure you want to delete this record? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                patients.erase(patients.begin() + i);
                cout << "Record deleted successfully!\n";
            } else {
                cout << "Deletion cancelled.\n";
            }
            countdownClear();
            return;
        }
    }

    if (!found) {
        cout << "No patient found with Hospital ID: " << id << endl;
        countdownClear();
    }
}

string currentDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}
