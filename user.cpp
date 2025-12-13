#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>   // <-- FIXED (required for vector<string>)
using namespace std;

User::User() 
    : username(""), selectedPlan(""), persons(0),
      bookedPlan(""), bookedPersons(0), bookedAmount(0) {}

User::User(const string& username) 
    : username(username), selectedPlan(""), persons(0),
      bookedPlan(""), bookedPersons(0), bookedAmount(0) {}

string User::getUsername() const { return username; }
string User::getSelectedPlan() const { return selectedPlan; }
int User::getPersons() const { return persons; }


// ===============================
//     PLAN SELECTION SYSTEM
// ===============================

void User::selectPlan(const string& planName, int persons) {
    selectedPlan = planName;
    this->persons = persons;

    cout << "Plan \"" << planName << "\" selected for "
         << persons << " person(s).\n";
}

void User::cancelPlan() {
    if (selectedPlan.empty()) {
        cout << "No plan selected to cancel.\n";
        return;
    }

    cout << "Selection cancelled: " << selectedPlan << "\n";
    selectedPlan = "";
    persons = 0;
}

void User::displayBudget(int planPrice) const {
    if (selectedPlan.empty()) {
        cout << "No plan selected.\n";
        return;
    }

    cout << "\n=== Budget Information ===\n";
    cout << "Plan Name: " << selectedPlan << "\n";
    cout << "Persons: " << persons << "\n";
    cout << "Price per Person: " << planPrice << "\n";
    cout << "Total Amount: " << (planPrice * persons) << "\n";
}


// ===============================
//           BOOKING SYSTEM
// ===============================

void User::bookTrip(const string& planName, int persons, int price) {
    bookedPlan = planName;
    bookedPersons = persons;
    bookedAmount = price * persons;

    cout << "\n🎉 Trip Booked Successfully! 🎉\n";
    cout << "Plan: " << bookedPlan << "\n";
    cout << "Persons: " << bookedPersons << "\n";
    cout << "Total Price: " << bookedAmount << "\n";

    saveBookingToFile(username);  // SAVE BOOKING
}

void User::viewBooking() const {
    if (bookedPlan.empty()) {
        cout << "\nNo bookings found.\n";
        return;
    }

    cout << "\n===== Your Booking =====\n";
    cout << "Plan: " << bookedPlan << "\n";
    cout << "Persons: " << bookedPersons << "\n";
    cout << "Total Amount: " << bookedAmount << "\n";
}

void User::cancelBooking() {
    if (bookedPlan.empty()) {
        cout << "No booking to cancel.\n";
        return;
    }

    cout << "\nBooking cancelled: " << bookedPlan << "\n";

    bookedPlan = "";
    bookedPersons = 0;
    bookedAmount = 0;

    saveBookingToFile(username); // UPDATE FILE
}


// ===============================
// SAVE / LOAD BOOKING TO FILE
// ===============================

void User::saveBookingToFile(const string& username) const {
    ifstream in("bookings.txt");
    vector<string> lines;   // <-- FIXED (vector included)
    string line;
    bool updated = false;

    if (in) {
        while (getline(in, line)) {
            if (line.empty()) continue;

            string uname;
            istringstream iss(line);
            getline(iss, uname, '|');

            if (uname == username) {
                // replace existing booking
                ostringstream oss;
                oss << username << "|" << bookedPlan << "|" 
                    << bookedPersons << "|" << bookedAmount;
                lines.push_back(oss.str());
                updated = true;
            } else {
                lines.push_back(line);
            }
        }
        in.close();
    }

    if (!updated) {
        ostringstream oss;
        oss << username << "|" << bookedPlan << "|" 
            << bookedPersons << "|" << bookedAmount;
        lines.push_back(oss.str());
    }

    ofstream out("bookings.txt");
    for (auto &l : lines) out << l << "\n";
    out.close();
}

void User::loadBookingFromFile(const string& username) {
    ifstream in("bookings.txt");
    if (!in) return;

    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string uname, plan, personsStr, amountStr;

        getline(iss, uname, '|');
        getline(iss, plan, '|');
        getline(iss, personsStr, '|');
        getline(iss, amountStr);

        if (uname == username) {
            bookedPlan = plan;
            bookedPersons = stoi(personsStr);
            bookedAmount = stoi(amountStr);
        }
    }

    in.close();
}
