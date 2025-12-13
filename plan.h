#ifndef PLAN_H
#define PLAN_H

#include <string>
using namespace std;

class Plan {
private:
    string category;   // Basic / Premium
    string name;
    int pricePerPerson;

    // Trip Details
    string destination;
    string country;
    string startDate;
    int days;
    string description;

public:
    Plan();
    Plan(const string& category, const string& name, int price,
         const string& destination, const string& country,
         const string& startDate, int days, const string& description);

    void display() const;

    string serialize() const;
    static Plan deserialize(const string& line);

    string getCategory() const;
    string getName() const;
    int getPrice() const;
    string getDestination() const;
    string getCountry() const;
    string getStartDate() const;
    int getDays() const;
    string getDescription() const;
};

#endif
