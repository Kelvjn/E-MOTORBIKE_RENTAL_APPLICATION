#include "Persistence.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// --- MEMBERS ---
void Persistence::saveMembers(const vector<Member*>& members) {
    ofstream fout("data/members.txt");
    if (!fout) {
        cerr << "Error: Could not open members.txt for saving.\n";
        return;
    }
    for (auto m : members) {
        fout << m->getUsername() << ","
             << m->getCredits() << ","
             << m->getRenterRating() << "\n";
    }
    fout.close();
}

void Persistence::loadMembers(vector<Member*>& members) {
    ifstream fin("data/members.txt");
    if (!fin) return; // no file yet
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string uname;
        int credits;
        double rating;

        getline(ss, uname, ',');
        ss >> credits;
        ss.ignore();
        ss >> rating;

        // create member with placeholder info
        Member* m = new Member(uname, "defaultPwd", "Unknown", "unknown@email.com");
        m->setCredits(credits);
        m->setRenterRating(rating);
        members.push_back(m);
    }
    fin.close();
}

// --- MOTORBIKES ---
void Persistence::saveMotorbikes(const vector<Motorbike*>& bikes) {
    ofstream fout("data/motorbikes.txt");
    if (!fout) {
        cerr << "Error: Could not open motorbikes.txt for saving.\n";
        return;
    }
    for (auto b : bikes) {
        fout << b->getBrand() << ","
             << b->getModel() << ","
             << b->getCity() << ","
             << b->getDailyRate() << ","
             << b->getRating() << "\n";
    }
    fout.close();
}

void Persistence::loadMotorbikes(vector<Motorbike*>& bikes) {
    ifstream fin("data/motorbikes.txt");
    if (!fin) return; // no file yet
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string brand, model, city;
        int rate;
        double rating;

        getline(ss, brand, ',');
        getline(ss, model, ',');
        getline(ss, city, ',');
        ss >> rate;
        ss.ignore();
        ss >> rating;

        // minimal constructor for motorbike
        Motorbike* b = new Motorbike(brand, model, "Unknown", city, 50, 2020, rate, "N/A", "2025-01-01", "2025-12-31");
        b->setRating(rating);
        bikes.push_back(b);
    }
    fin.close();
}

