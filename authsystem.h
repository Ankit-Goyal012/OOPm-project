#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>
using namespace std;

class AuthSystem {
public:
    bool adminLogin(const string& user, const string& pass) const;
    bool userLogin(const string& user, const string& pass) const;
    bool userSignup(const string& user, const string& pass);
    bool saveUserRecord(const string& user, const string& pass,
                        const string& selectedPlan, int persons) const;
    bool loadUserRecord(const string& user, string& outPass,
                        string& outSelectedPlan, int& outPersons) const;
};

#endif
