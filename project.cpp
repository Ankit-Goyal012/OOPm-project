#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to represent a single Trip
class Trip {
private:
    string destination;
    string date;
    double budget;
    string notes;
    string status;

public:
    // Constructor
    Trip(string dest, string dt, double bud, string nt) {
        destination = dest;
        date = dt;
        budget = bud;
        notes = nt;
        status = "Upcoming";
    }

    // Display trip details
    void display(int index) const {
        cout << "\nTrip #" << index + 1 << endl;
        cout << "Destination : " << destination << endl;
        cout << "Date        : " << date << endl;
        cout << "Budget      : ₹" << budget << endl;
        cout << "Status      : " << status << endl;
        cout << "Notes       : " << notes << endl;
    }

    // Mark the trip as completed
    void markCompleted() {
        status = "Completed";
    }

    // Return current status
    string getStatus() const {
        return status;
    }
};

// Class to manage all trips
class TripManager {
private:
    vector<Trip> trips;

public:
    // Add a new trip
    void addTrip() {
        string destination, date, notes;
        double budget;

        cin.ignore(); // clear input buffer
        cout << "\nEnter Destination: ";
        getline(cin, destination);

        cout << "Enter Date (dd-mm-yyyy): ";
        getline(cin, date);

        cout << "Enter Budget (₹): ";
        cin >> budget;

        cin.ignore();
        cout << "Enter Notes: ";
        getline(cin, notes);

        trips.push_back(Trip(destination, date, budget, notes));
        cout << "\n✅ Trip added successfully!\n";
    }

    // Show all trips
    void displayTrips() const {
        if (trips.empty()) {
            cout << "\nNo trips available yet!\n";
            return;
        }

        cout << "\n=== Your Trips ===\n";
        for (size_t i = 0; i < trips.size(); i++) {
            trips[i].display(i);
        }
    }

    // Mark a trip as completed
    void markTripCompleted() {
        if (trips.empty()) {
            cout << "\nNo trips to update!\n";
            return;
        }

        displayTrips();
        int index;
        cout << "\nEnter trip number to mark as completed: ";
        cin >> index;

        if (index < 1 || index > trips.size()) {
            cout << "\n❌ Invalid trip number!\n";
            return;
        }

        trips[index - 1].markCompleted();
        cout << "\n✅ Trip marked as completed!\n";
    }

    // Delete a trip
    void deleteTrip() {
        if (trips.empty()) {
            cout << "\nNo trips to delete!\n";
            return;
        }

        displayTrips();
        int index;
        cout << "\nEnter trip number to delete: ";
        cin >> index;

        if (index < 1 || index > trips.size()) {
            cout << "\n❌ Invalid trip number!\n";
            return;
        }

        trips.erase(trips.begin() + (index - 1));
        cout << "\n🗑 Trip deleted successfully!\n";
    }
};

// Main program
int main() {
    TripManager manager;
    int choice;

    do {
        cout << "\n========== Trip Management ==========\n";
        cout << "1. Add Trip\n";
        cout << "2. View All Trips\n";
        cout << "3. Mark Trip as Completed\n";
        cout << "4. Delete Trip\n";
        cout << "5. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addTrip(); break;
            case 2: manager.displayTrips(); break;
            case 3: manager.markTripCompleted(); break;
            case 4: manager.deleteTrip(); break;
            case 5: cout << "\nGoodbye! 👋 Have a nice trip!\n"; break;
            default: cout << "\n❌ Invalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
