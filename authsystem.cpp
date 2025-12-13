#include "AuthSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

static const string ADMIN_USER = "admin";
static const string ADMIN_PASS = "1234";
static const string USERS_FILE = "users.txt";

bool AuthSystem::adminLogin(const string& user, const string& pass) const {
    return (user == ADMIN_USER && pass == ADMIN_PASS);
}

bool AuthSystem::userLogin(const string& user, const string& pass) const {
    string storedPass, selPlan;
    int persons;
    if (!loadUserRecord(user, storedPass, selPlan, persons)) return false;
    return (storedPass == pass);
}

bool AuthSystem::userSignup(const string& user, const string& pass) {
    string sp, plan;
    int p;
    if (loadUserRecord(user, sp, plan, p)) {
        cout << "User already exists.\n";
        return false;
    }
    return saveUserRecord(user, pass, "", 0);
}

bool AuthSystem::saveUserRecord(const string& user, const string& pass,
                                const string& selectedPlan, int persons) const {
    ifstream in(USERS_FILE);
    vector<string> lines;
    string line;
    bool replaced = false;
    if (in) {
        while (getline(in, line)) {
            if (line.empty()) continue;
            istringstream iss(line);
            string uname;
            if (getline(iss, uname, '|')) {
                if (uname == user) {
                    ostringstream oss;
                    oss << user << "|" << pass << "|" << selectedPlan << "|" << persons;
                    lines.push_back(oss.str());
                    replaced = true;
                    continue;
                }
            }
            lines.push_back(line);
        }
        in.close();
    }
    if (!replaced) {
        ostringstream oss;
        oss << user << "|" << pass << "|" << selectedPlan << "|" << persons;
        lines.push_back(oss.str());
    }
    ofstream out(USERS_FILE);
    for (const auto& l : lines) out << l << "\n";
    out.close();
    return true;
}

bool AuthSystem::loadUserRecord(const string& user, string& outPass,
                                string& outSelectedPlan, int& outPersons) const {
    ifstream in(USERS_FILE);
    if (!in) return false;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string uname, pass, selPlan, personsStr;
        if (!getline(iss, uname, '|')) continue;
        if (!getline(iss, pass, '|')) continue;
        if (!getline(iss, selPlan, '|')) selPlan = "";
        if (!getline(iss, personsStr)) personsStr = "0";
        if (uname == user) {
            outPass = pass;
            outSelectedPlan = selPlan;
            try { outPersons = stoi(personsStr); } catch (...) { outPersons = 0; }
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}
