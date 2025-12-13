#ifndef ITINERARY_H
#define ITINERARY_H

#include <vector>
#include <string>
#include "Destination.h"
using namespace std;

class Itinerary {
private:
    vector<Destination> destinations;

public:
    void addDestination(const Destination& dest);
    void viewItinerary() const;
    void removeDestination(const string& name);
    void editDestination(const string& name);
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    vector<Destination> getDestinations() const;
};

#endif
