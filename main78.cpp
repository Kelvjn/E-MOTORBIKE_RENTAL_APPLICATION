#include <iostream>
#include <vector>
#include "Persistence.h"
#include "Member.h"
#include "Motorbike.h"

using namespace std;

// Search function
void searchMotorbikes(const vector<Motorbike*>& bikes, const string& date, const string& city) {
    cout << "\nAvailable motorbikes in " << city << " on " << date << ":\n";
    vector<Motorbike*> results;
    int index = 1;
    for (auto b : bikes) {
        if (b->isAvailable(date, city)) {
            cout << index << ". ";
            b->displayBasicInfo();
            results.push_back(b);
            index++;
        }
    }

    if (results.empty()) {
        cout << "No motorbikes found.\n";
        return;
    }

    // Ask if user wants full details
    cout << "\nEnter number to view full details (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice > 0 && choice <= results.size()) {
        cout << "\n--- Motorbike Details ---\n";
        results[choice - 1]->displayFullInfo();
    }
}

int main() {
    vector<Member*> members;
    vector<Motorbike*> bikes;

    // Load previous session data
    Persistence::loadMembers(members);
    Persistence::loadMotorbikes(bikes);

    cout << "Welcome to E-Motorbike Rental System\n";
    cout << "Loaded " << members.size() << " members and "
         << bikes.size() << " motorbikes.\n\n";

    int choice;
    do {
        cout << "\n==== MENU ====\n";
        cout << "1. Register Member\n";
        cout << "2. List Motorbike\n";
        cout << "3. View Members\n";
        cout << "4. View Motorbikes\n";
        cout << "5. Search Motorbikes (by date & city)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // flush newline

        if (choice == 1) {
            string uname, pwd, name, email;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pwd);
            cout << "Enter full name: ";
            getline(cin, name);
            cout << "Enter email: ";
            getline(cin, email);

            Member* m = new Member(uname, pwd, name, email);
            m->setCredits(20); // signup bonus
            members.push_back(m);

            cout << "Member " << uname << " registered with 20 CP.\n";
        }
        else if (choice == 2) {
            string brand, model, color, city, plate, start, end;
            int size, year, rate;
            cout << "Enter brand: "; getline(cin, brand);
            cout << "Enter model: "; getline(cin, model);
            cout << "Enter color: "; getline(cin, color);
            cout << "Enter city (HCMC/Hanoi): "; getline(cin, city);
            cout << "Enter engine size (cc): "; cin >> size; cin.ignore();
            cout << "Enter year made: "; cin >> year; cin.ignore();
            cout << "Enter daily rate (CP): "; cin >> rate; cin.ignore();
            cout << "Enter plate number: "; getline(cin, plate);
            cout << "Enter available start date (YYYY-MM-DD): "; getline(cin, start);
            cout << "Enter available end date (YYYY-MM-DD): "; getline(cin, end);

            Motorbike* mb = new Motorbike(brand, model, color, city, size, year, rate, plate, start, end);
            bikes.push_back(mb);

            cout << "Motorbike " << brand << " " << model << " listed.\n";
        }
        else if (choice == 3) {
            cout << "\n--- Members ---\n";
            for (auto m : members) {
                cout << m->getUsername() 
                     << " | CP: " << m->getCredits()
                     << " | Rating: " << m->getRenterRating() << "\n";
            }
        }
        else if (choice == 4) {
            cout << "\n--- Motorbikes ---\n";
            for (auto b : bikes) {
                b->displayFullInfo();
            }
        }
        else if (choice == 5) {
            string date, city;
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter city (HCMC/Hanoi): ";
            getline(cin, city);
            searchMotorbikes(bikes, date, city);
        }

    } while (choice != 0);

    // Save data on exit
    Persistence::saveMembers(members);
    Persistence::saveMotorbikes(bikes);

    cout << "Data saved. Goodbye!\n";
    return 0;
}
