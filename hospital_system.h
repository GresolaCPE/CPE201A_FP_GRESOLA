#ifndef HOSPITAL_SYSTEM_H
#define HOSPITAL_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

// Struct
struct Account {
    string username;
    string password;
    string staffID;
};

struct Patient {
    string name, sex, room;
    int age, hospitalID;
    string dateTime;
    string nurseName, designation;

    // Vital signs
    float temperature;
    int pulse, respiratoryRate;
    string bloodPressure;
    int oxygenSaturation;
    float height, weight, bmi;

    // Nursing chart
    string subjective, objective, labResults;
    string evaluation, incidents;
    string doctor, family, orders;
    string nurseAttended;
};

extern vector<Account> accounts; // means that this variable is declared somewhere else
extern vector<Patient> patients;
extern string currentUser;

// Function declarations
void startMenu();
void signup();
bool verifyStaffID(string id);
void logout();

void login();
void menu();
void addRecord();
void searchPatient();
void deletePatient();
string currentDateTime();

void countdownClear();
void countdownExit();

#endif

