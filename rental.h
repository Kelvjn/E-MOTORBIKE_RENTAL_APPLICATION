#ifndef RENTAL_H
#define RENTAL_H

#include "motobike.h"
#include "member.h"
#include <string>

using namespace std;

class Rental{
private:
    member* renter;
    member* owner;
    motorbike* motorbike;
    string startDate, endDate;
    bool completed;

public:
    Rental(member* r, member* o, motobike* mb, string start, string end);

    void completedRental(); //renter returns motorbike
    void rateBoth(int renterStars, string renterComment, int motorbikeStars, string motorbikeComment);

    bool isCompleted() const;

};

#endif