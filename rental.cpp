#include "Rental.h"
#include <iostream>

using namespace std;

Rental::Rental(member* r, member* o, motorbike* mb, string start, string end)
{
    renter = r;
    owner = o;
    motorbike = mb;
    startDate = start;
    endDate = end;
    completed = false;

}

void Rental::completedRental()
{
    if (!completed){
        cout << "Rental completed for motorbike " << motorbike->getPlate() << endl;
        completed = true;
    } else {
        cout << "Rental already completed.\n";
    }
}

void Rental::rateBoth(int renterStars, string renterComment, int motorbikeStars, string motorbikeComment)
{
    if (!completed){
        cout << "Rental must be completed first.\n";
        return;
    }

     // Renter rates motorbike
    motorbike->addReview(motorbikeStars, renterComment);

    // Owner rates renter
    renter->addRenterReview(renterStars, motorbikeComment);

    cout << "Both renter and motorbike have been rated.\n";
}

bool Rental::isCompleted() const {
    return completed;
}


void Member::addRenterReview(int stars, const string& comment) {
    renterReviews.push_back(stars);
    int sum = 0;
    for (int r : renterReviews) sum += r;
    renterRating = (double)sum / renterReviews.size();
    cout << "Renter " << username << " new rating: " << renterRating << "\n";
}

double Member::getRenterRating() const {
    return renterRating;
}
