#include "Plan.h"
#include <iostream>
#include <sstream>
using namespace std;

Plan::Plan()
    : category(""), name(""), pricePerPerson(0),
      destination(""), country(""), startDate(""), days(0), description("") {}

Plan::Plan(const string& category, const string& name, int price,
           const string& destination, const string& country,
           const string& startDate, int days, const string& description)
    : category(category), name(name), pricePerPerson(price),
      destination(destination), country(country),
      startDate(startDate), days(days), description(description) {}

string Plan::getCategory() const { return category; }
string Plan::getName() const { return name; }
int Plan::getPrice() const { return pricePerPerson; }
string Plan::getDestination() const { return destination; }
string Plan::getCountry() const { return country; }
string Plan::getStartDate() const { return startDate; }
int Plan::getDays() const { return days; }
string Plan::getDescription() const { return description; }

void Plan::display() const {
    cout << "\n========== TRIP PLAN ==========\n";
    cout << "Category      : " << category << "\n";
    cout << "Plan Name     : " << name << "\n";
    cout << "Price/Person  : " << pricePerPerson << "\n";
    cout << "Destination   : " << destination << ", " << country << "\n";
    cout << "Start Date    : " << startDate << "\n";
    cout << "Days          : " << days << "\n";
    cout << "Description   : " << description << "\n";
    cout << "================================\n";
}

string Plan::serialize() const {
    ostringstream oss;
    oss << category << "|" << name << "|" << pricePerPerson << "|"
        << destination << "|" << country << "|" << startDate << "|"
        << days << "|" << description;
    return oss.str();
}

Plan Plan::deserialize(const string& line) {
    istringstream iss(line);
    string cat, name, priceStr, dest, country, start, daysStr, desc;

    getline(iss, cat, '|');
    getline(iss, name, '|');
    getline(iss, priceStr, '|');
    getline(iss, dest, '|');
    getline(iss, country, '|');
    getline(iss, start, '|');
    getline(iss, daysStr, '|');
    getline(iss, desc);

    int price = 0;
    int d = 0;
    try { price = stoi(priceStr); } catch(...) { price = 0; }
    try { d = stoi(daysStr); } catch(...) { d = 0; }

    return Plan(cat, name, price, dest, country, start, d, desc);
}
