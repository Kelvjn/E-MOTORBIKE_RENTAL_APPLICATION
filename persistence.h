#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <vector>
#include "Member.h"
#include "Motorbike.h"

using namespace std;

namespace Persistence {
    void saveMembers(const vector<Member*>& members);
    void loadMembers(vector<Member*>& members);

    void saveMotorbikes(const vector<Motorbike*>& bikes);
    void loadMotorbikes(vector<Motorbike*>& bikes);
}

#endif
