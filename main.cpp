#include <iostream>
#include <string>
#include <limits>

#include "Itinerary.h"
#include "Admin.h"
#include "AuthSystem.h"
#include "User.h"
#include "Plan.h"

using namespace std;

int readIntSafe() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

string readLineSafe(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void adminMenu(Admin& admin) {
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View Plans\n";
        cout << "2. Add Plan\n";
        cout << "3. Remove Plan\n";
        cout << "4. Edit Plan Price\n";
        cout << "5. Save Plans\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        int ch = readIntSafe();

        if (ch == 1) admin.viewPlans();

        else if (ch == 2) {
            string cat;
            while (true) {
                cat = readLineSafe("Category (Basic/Premium): ");
                if (cat == "Basic" || cat == "Premium") break;
                cout << "Type Basic or Premium.\n";
            }

            string name = readLineSafe("Plan name: ");
            cout << "Price per person: ";
            int price = readIntSafe();

            string dest = readLineSafe("Trip destination: ");
            string country = readLineSafe("Country: ");
            string start = readLineSafe("Start date (YYYY-MM-DD): ");
            cout << "Trip days: ";
            int d = readIntSafe();
            string desc = readLineSafe("Trip description: ");

            admin.addPlan(Plan(cat, name, price, dest, country, start, d, desc));
        }

        else if (ch == 3) {
            string name = readLineSafe("Name of plan to remove: ");
            if (!admin.removePlan(name)) cout << "Plan not found.\n";
        }

        else if (ch == 4) {
            string name = readLineSafe("Name of plan to edit: ");
            cout << "New price: ";
            int price = readIntSafe();
            if (!admin.editPlanPrice(name, price)) cout << "Plan not found.\n";
        }

        else if (ch == 5) {
            admin.savePlans("plans.txt");
            cout << "Plans saved.\n";
        }

        else if (ch == 0) {
            admin.savePlans("plans.txt");
            cout << "Logging out admin.\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }
}

void userMenu(Admin& admin, AuthSystem& auth, const string& username) {
    string pass, selPlan;
    int persons;

    auth.loadUserRecord(username, pass, selPlan, persons);
    User user(username);

    if (!selPlan.empty())
        user.selectPlan(selPlan, persons);

    while (true) {
        cout << "\n--- User Menu (" << username << ") ---\n";
        cout << "1. View Available Plans\n";
        cout << "2. Select a Plan\n";
        cout << "3. Cancel Selected Plan\n";
        cout << "4. View My Budget\n";
        cout << "5. View Plan Details\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        int ch = readIntSafe();

        if (ch == 1) {
            admin.viewPlans();
        }

        else if (ch == 2) {
            string name = readLineSafe("Enter plan name to select: ");

            if (!admin.planExists(name)) {
                cout << "Plan does not exist.\n";
            } 
            else {
                cout << "Enter number of persons: ";
                int p = readIntSafe();
                user.selectPlan(name, p);
                auth.saveUserRecord(username, pass,
                    user.getSelectedPlan(), user.getPersons());
            }
        }

        else if (ch == 3) {
            user.cancelPlan();
            auth.saveUserRecord(username, pass,
                user.getSelectedPlan(), user.getPersons());
        }

        else if (ch == 4) {
            if (user.getSelectedPlan().empty())
                cout << "No plan selected.\n";
            else {
                int price = admin.getPlanPrice(user.getSelectedPlan());
                user.displayBudget(price);
            }
        }

        else if (ch == 5) {
            string name = readLineSafe("Enter plan name to view details: ");
            bool found = false;
            auto plans = admin.getPlans();
            for (const auto& p : plans) {
                if (p.getName() == name) {
                    p.display();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Plan not found.\n";
        }

        else if (ch == 0) {
            cout << "Logging out user.\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    Admin admin;
    admin.loadPlans("plans.txt");

    Itinerary trip;
    trip.loadFromFile("itinerary.txt");

    AuthSystem auth;

    while (true) {
        cout << "\n===== Travel Itinerary Management =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Signup\n";
        cout << "3. User Login\n";
        cout << "4. Manage Itinerary (Add/View/Save)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        int choice = readIntSafe();

        if (choice == 1) {
            string user = readLineSafe("Admin username: ");
            string pass = readLineSafe("Admin password: ");

            if (auth.adminLogin(user, pass)) {
                cout << "Admin logged in.\n";
                adminMenu(admin);
            } else {
                cout << "Invalid admin credentials.\n";
            }
        }

        else if (choice == 2) {
            string user = readLineSafe("Choose username: ");
            string pass = readLineSafe("Choose password: ");

            if (auth.userSignup(user, pass))
                cout << "Signup successful. You can now login.\n";
            else
                cout << "Signup failed (user exists).\n";
        }

        else if (choice == 3) {
            string user = readLineSafe("Username: ");
            string pass = readLineSafe("Password: ");

            if (auth.userLogin(user, pass)) {
                cout << "Login successful.\n";
                userMenu(admin, auth, user);
            } else {
                cout << "Invalid username/password.\n";
            }
        }

        else if (choice == 4) {
            cout << "\nItinerary Menu\n";
            cout << "1. Add Destination\n";
            cout << "2. View Itinerary\n";
            cout << "3. Save Itinerary\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";
            int ch = readIntSafe();

            if (ch == 1) {
                string name = readLineSafe("Enter destination name: ");
                string country = readLineSafe("Enter country: ");
                string date = readLineSafe("Enter date (YYYY-MM-DD): ");
                cout << "Enter number of days: ";
                int days = readIntSafe();
                trip.addDestination(Destination(name, country, date, days));
            } else if (ch == 2) {
                trip.viewItinerary();
            } else if (ch == 3) {
                trip.saveToFile("itinerary.txt");
            }
        }

        else if (choice == 0) {
            admin.savePlans("plans.txt");
            trip.saveToFile("itinerary.txt");
            cout << "Goodbye!\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
