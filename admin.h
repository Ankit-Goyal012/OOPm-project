#ifndef ADMIN_H
#define ADMIN_H

#include "Plan.h"
#include <vector>
#include <string>
using namespace std;

class Admin {
private:
    vector<Plan> plans;

public:
    Admin();

    void loadPlans(const string& filename);
    void savePlans(const string& filename) const;

    void addPlan(const Plan& p);
    void viewPlans() const;
    bool removePlan(const string& name);
    bool editPlanPrice(const string& name, int newPrice);

    bool planExists(const string& name) const;
    int getPlanPrice(const string& name) const;

    vector<Plan> getPlans() const;
};

#endif
