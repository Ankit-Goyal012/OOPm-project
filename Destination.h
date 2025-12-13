#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
using namespace std;

class Destination {
private:
    string name;
    string country;
    string date; // e.g. "2025-11-07"
    int days;

public:
    Destination();
    Destination(const string& name, const string& country, const string& date, int days);

    // Getters
    string getName() const;
    string getCountry() const;
    string getDate() const;
    int getDays() const;

    // Setters
    void setName(const string& name);
    void setCountry(const string& country);
    void setDate(const string& date);
    void setDays(int days);

    void display() const;
};

#endif
