#include "Destination.h"
#include <iostream>

Destination::Destination() : name(""), country(""), date(""), days(0) {}

Destination::Destination(const string& name, const string& country, const string& date, int days)
    : name(name), country(country), date(date), days(days) {}

string Destination::getName() const { return name; }
string Destination::getCountry() const { return country; }
string Destination::getDate() const { return date; }
int Destination::getDays() const { return days; }

void Destination::setName(const string& name) { this->name = name; }
void Destination::setCountry(const string& country) { this->country = country; }
void Destination::setDate(const string& date) { this->date = date; }
void Destination::setDays(int days) { this->days = days; }

void Destination::display() const {
    cout << "Destination: " << name << " (" << country << ")\n";
    cout << "Date: " << date << ", Days: " << days << "\n";
}
