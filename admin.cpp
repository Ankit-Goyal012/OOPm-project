#include "Admin.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Admin::Admin() {}

void Admin::loadPlans(const string& filename) {
    plans.clear();
    ifstream in(filename);
    if (!in) return;

    string line;
    while (getline(in, line)) {
        if (!line.empty()) {
            plans.push_back(Plan::deserialize(line));
        }
    }
    in.close();
}

void Admin::savePlans(const string& filename) const {
    ofstream out(filename);
    for (const auto& p : plans) {
        out << p.serialize() << "\n";
    }
    out.close();
}

void Admin::addPlan(const Plan& p) {
    plans.push_back(p);
    cout << "\nPlan added successfully!\n\n";
}

void Admin::viewPlans() const {
    if (plans.empty()) {
        cout << "No plans available.\n";
        return;
    }
    for (const auto& p : plans) {
        p.display();
    }
}

bool Admin::removePlan(const string& name) {
    for (auto it = plans.begin(); it != plans.end(); ++it) {
        if (it->getName() == name) {
            plans.erase(it);
            cout << "Plan removed.\n";
            return true;
        }
    }
    return false;
}

bool Admin::editPlanPrice(const string& name, int newPrice) {
    for (auto& p : plans) {
        if (p.getName() == name) {
            p = Plan(p.getCategory(), p.getName(), newPrice,
                     p.getDestination(), p.getCountry(),
                     p.getStartDate(), p.getDays(), p.getDescription());
            cout << "Plan price updated.\n";
            return true;
        }
    }
    return false;
}

bool Admin::planExists(const string& name) const {
    for (const auto& p : plans)
        if (p.getName() == name) return true;
    return false;
}

int Admin::getPlanPrice(const string& name) const {
    for (const auto& p : plans)
        if (p.getName() == name)
            return p.getPrice();
    return 0;
}

vector<Plan> Admin::getPlans() const {
    return plans;
}
