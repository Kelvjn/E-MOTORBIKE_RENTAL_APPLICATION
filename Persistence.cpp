#include <fstream>
#include <vector>
#include "Member.h"

using namespace std;

void saveMembers(const vector<Member*>& members) {
    ofstream fout("data/members.txt");
    for (auto m : members) {
        fout << m->getUsername() << ","
             << m->getCredits() << ","
             << m->getRenterRating() << "\n";
    }
    fout.close();
}

void loadMembers(vector<Member*>& members) {
    ifstream fin("data/members.txt");
    string uname;
    int credits;
    double rating;
    while (fin >> uname >> credits >> rating) {
        // you’d reconstruct with proper constructor in real code
        Member* m = new Member(uname, "defaultPwd", "Unknown", "email@example.com");
        m->setCredits(credits);
        m->setRenterRating(rating);
        members.push_back(m);
    }
    fin.close();
}

void saveMotorbikes(const vector<Motorbike*>& bikes) {
    ofstream fout("data/motorbikes.txt");
    for (auto b : bikes) {
        fout << b->getBrand() << "," << b->getModel() << "," 
             << b->getCity() << "," << b->getDailyRate()
             << "," << b->getRating() << "\n";
    }
    fout.close();
}

