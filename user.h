#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string username;

    // Trip selection
    string selectedPlan;
    int persons;

    // Booking data
    string bookedPlan;
    int bookedPersons;
    int bookedAmount;

public:
    User();
    User(const string& username);

    // Getters
    string getUsername() const;
    string getSelectedPlan() const;
    int getPersons() const;

    // Trip selection
    void selectPlan(const string& planName, int persons);
    void cancelPlan();
    void displayBudget(int planPrice) const;

    // Booking features
    void bookTrip(const string& planName, int persons, int price);
    void viewBooking() const;
    void cancelBooking();

    // Save / Load booking to file
    void saveBookingToFile(const string& username) const;
    void loadBookingFromFile(const string& username);
};

#endif
