#include "Itinerary.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void Itinerary::addDestination(const Destination& dest) {
    destinations.push_back(dest);
    cout << "Destination added successfully!\n";
}

void Itinerary::viewItinerary() const {
    if (destinations.empty()) {
        cout << "No destinations in itinerary.\n";
        return;
    }
    cout << "\n--- Travel Itinerary ---\n";
    for (size_t i = 0; i < destinations.size(); ++i) {
        cout << i + 1 << ". ";
        destinations[i].display();
        cout << "------------------------\n";
    }
}

void Itinerary::removeDestination(const string& name) {
    for (auto it = destinations.begin(); it != destinations.end(); ++it) {
        if (it->getName() == name) {
            destinations.erase(it);
            cout << "Destination removed successfully!\n";
            return;
        }
    }
    cout << "Destination not found.\n";
}

void Itinerary::editDestination(const string& name) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

    for (auto& dest : destinations) {
        if (dest.getName() == name) {
            string newName, newCountry, newDate;
            int newDays;

            cout << "Enter new name: ";
            getline(cin, newName);
            cout << "Enter new country: ";
            getline(cin, newCountry);
            cout << "Enter new date (YYYY-MM-DD): ";
            getline(cin, newDate);
            cout << "Enter number of days: ";
            while (!(cin >> newDays)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a valid number: ";
            }
            cin.ignore();

            dest.setName(newName);
            dest.setCountry(newCountry);
            dest.setDate(newDate);
            dest.setDays(newDays);

            cout << "Destination updated successfully!\n";
            return;
        }
    }
    cout << "Destination not found.\n";
}

void Itinerary::saveToFile(const string& filename) const {
    ofstream out(filename);
    for (const auto& dest : destinations) {
        out << dest.getName() << "," 
            << dest.getCountry() << ","
            << dest.getDate() << ","
            << dest.getDays() << "\n";
    }
    out.close();
    cout << "Itinerary saved to " << filename << endl;
}

void Itinerary::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) return;
    destinations.clear();
    string name, country, date;
    int days;
    while (getline(in, name, ',')) {
        if (!getline(in, country, ',')) break;
        if (!getline(in, date, ',')) break;
        if (!(in >> days)) break;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        destinations.emplace_back(name, country, date, days);
    }
    in.close();
}

vector<Destination> Itinerary::getDestinations() const {
    return destinations;
}
