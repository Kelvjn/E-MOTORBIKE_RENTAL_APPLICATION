#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>

using namespace std;

BookingManager::BookingManager() {
    bookingFilename = "bookings.txt";
    motorbikeFilename = "motorbikes.txt";
    loadBookings();
    loadMotorbikes();
    
    // Create sample data if no bookings exist
    if (bookings.empty()) {
        createSampleData();
    }
}

BookingManager::~BookingManager() {
    saveBookings();
    saveMotorbikes();
}

void BookingManager::loadBookings() {
    ifstream file(bookingFilename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Booking booking;
        
        getline(ss, booking.bookingId, '|');
        getline(ss, booking.renterUsername, '|');
        getline(ss, booking.ownerUsername, '|');
        getline(ss, booking.motorbikeId, '|');
        getline(ss, booking.startDate, '|');
        getline(ss, booking.endDate, '|');
        getline(ss, booking.status, '|');
        
        string temp;
        getline(ss, temp, '|');
        booking.totalCost = stod(temp);
        
        getline(ss, booking.brand, '|');
        getline(ss, booking.model, '|');
        getline(ss, booking.color, '|');
        getline(ss, booking.size, '|');
        getline(ss, booking.plateNo, '|');
        
        bookings.push_back(booking);
    }
    
    file.close();
}

void BookingManager::saveBookings() {
    ofstream file(bookingFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot open bookings.txt for writing\n";
        return;
    }
    
    for (const Booking& booking : bookings) {
        file << booking.bookingId << "|"
             << booking.renterUsername << "|"
             << booking.ownerUsername << "|"
             << booking.motorbikeId << "|"
             << booking.startDate << "|"
             << booking.endDate << "|"
             << booking.status << "|"
             << booking.totalCost << "|"
             << booking.brand << "|"
             << booking.model << "|"
             << booking.color << "|"
             << booking.size << "|"
             << booking.plateNo << "\n";
    }
    
    file.close();
}

void BookingManager::loadMotorbikes() {
    ifstream file(motorbikeFilename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Motorbike motorbike;
        
        getline(ss, motorbike.motorbikeId, '|');
        getline(ss, motorbike.ownerUsername, '|');
        getline(ss, motorbike.brand, '|');
        getline(ss, motorbike.model, '|');
        getline(ss, motorbike.color, '|');
        getline(ss, motorbike.size, '|');
        getline(ss, motorbike.plateNo, '|');
        
        string temp;
        getline(ss, temp, '|');
        motorbike.pricePerDay = stod(temp);
        
        getline(ss, motorbike.location, '|');
        
        getline(ss, temp, '|');
        motorbike.isAvailable = (temp == "1");
        
        getline(ss, temp, '|');
        motorbike.rating = stod(temp);
        
        getline(ss, motorbike.description, '|');
        
        motorbikes.push_back(motorbike);
    }
    
    file.close();
}

void BookingManager::saveMotorbikes() {
    ofstream file(motorbikeFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot open motorbikes.txt for writing\n";
        return;
    }
    
    for (const Motorbike& motorbike : motorbikes) {
        file << motorbike.motorbikeId << "|"
             << motorbike.ownerUsername << "|"
             << motorbike.brand << "|"
             << motorbike.model << "|"
             << motorbike.color << "|"
             << motorbike.size << "|"
             << motorbike.plateNo << "|"
             << motorbike.pricePerDay << "|"
             << motorbike.location << "|"
             << (motorbike.isAvailable ? "1" : "0") << "|"
             << motorbike.rating << "|"
             << motorbike.description << "\n";
    }
    
    file.close();
}

string BookingManager::generateBookingId() {
    static int counter = 1;
    return "BK" + to_string(counter++);
}

bool BookingManager::createBooking(const string& renter, const string& motorbikeId, 
                                  const string& startDate, const string& endDate) {
    Motorbike* motorbike = getMotorbikeById(motorbikeId);
    if (!motorbike || !motorbike->isAvailable) {
        return false;
    }
    
    Booking booking;
    booking.bookingId = generateBookingId();
    booking.renterUsername = renter;
    booking.ownerUsername = motorbike->ownerUsername;
    booking.motorbikeId = motorbikeId;
    booking.startDate = startDate;
    booking.endDate = endDate;
    booking.status = "Pending";
    booking.brand = motorbike->brand;
    booking.model = motorbike->model;
    booking.color = motorbike->color;
    booking.size = motorbike->size;
    booking.plateNo = motorbike->plateNo;
    booking.totalCost = motorbike->pricePerDay; // Simplified calculation
    
    bookings.push_back(booking);
    saveBookings();
    return true;
}

bool BookingManager::approveBooking(const string& bookingId, const string& owner) {
    for (Booking& booking : bookings) {
        if (booking.bookingId == bookingId && booking.ownerUsername == owner) {
            booking.status = "Approved";
            saveBookings();
            return true;
        }
    }
    return false;
}

bool BookingManager::rejectBooking(const string& bookingId, const string& owner) {
    for (Booking& booking : bookings) {
        if (booking.bookingId == bookingId && booking.ownerUsername == owner) {
            booking.status = "Rejected";
            saveBookings();
            return true;
        }
    }
    return false;
}

vector<Booking> BookingManager::getUserBookings(const string& username) {
    vector<Booking> userBookings;
    for (const Booking& booking : bookings) {
        if (booking.renterUsername == username) {
            userBookings.push_back(booking);
        }
    }
    return userBookings;
}

vector<Booking> BookingManager::getUserRentalRequests(const string& username) {
    vector<Booking> rentalRequests;
    for (const Booking& booking : bookings) {
        if (booking.ownerUsername == username && booking.status == "Pending") {
            rentalRequests.push_back(booking);
        }
    }
    return rentalRequests;
}

bool BookingManager::addMotorbike(const Motorbike& motorbike) {
    motorbikes.push_back(motorbike);
    saveMotorbikes();
    return true;
}

vector<Motorbike> BookingManager::getAvailableMotorbikes() {
    vector<Motorbike> available;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.isAvailable) {
            available.push_back(motorbike);
        }
    }
    return available;
}

vector<Motorbike> BookingManager::getUserMotorbikes(const string& username) {
    vector<Motorbike> userMotorbikes;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == username) {
            userMotorbikes.push_back(motorbike);
        }
    }
    return userMotorbikes;
}

Motorbike* BookingManager::getMotorbikeById(const string& motorbikeId) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.motorbikeId == motorbikeId) {
            return &motorbike;
        }
    }
    return nullptr;
}

double BookingManager::getUserRenterRating(const string& username) {
    // Simplified implementation - return default rating
    // TODO: Implement actual rating calculation based on username
    (void)username; // Suppress unused parameter warning
    return 3.5;
}

double BookingManager::getUserMotorbikeRating(const string& username) {
    // Simplified implementation - return default rating
    // TODO: Implement actual rating calculation based on username
    (void)username; // Suppress unused parameter warning
    return 4.6;
}

void BookingManager::createSampleData() {
    // Create sample bookings for demonstration
    Booking booking1;
    booking1.bookingId = "BK1";
    booking1.renterUsername = "iAmMember1";
    booking1.ownerUsername = "iAmMember8";
    booking1.motorbikeId = "MB1";
    booking1.startDate = "15/08/2025";
    booking1.endDate = "17/08/2025";
    booking1.status = "Rejected";
    booking1.totalCost = 50.0;
    booking1.brand = "VinFast";
    booking1.model = "Klara S";
    booking1.color = "Red";
    booking1.size = "50cc";
    booking1.plateNo = "59X3-216.86";
    
    bookings.push_back(booking1);
    
    // Create sample rental requests
    Booking request1;
    request1.bookingId = "BK2";
    request1.renterUsername = "IAmMember3";
    request1.ownerUsername = "iAmMember1";
    request1.motorbikeId = "MB2";
    request1.startDate = "20/08/2025";
    request1.endDate = "21/08/2025";
    request1.status = "Pending";
    request1.totalCost = 30.0;
    request1.brand = "Honda";
    request1.model = "Vision";
    request1.color = "Blue";
    request1.size = "110cc";
    request1.plateNo = "51A-12345";
    
    bookings.push_back(request1);
    
    Booking request2;
    request2.bookingId = "BK3";
    request2.renterUsername = "IAmMember4";
    request2.ownerUsername = "iAmMember1";
    request2.motorbikeId = "MB3";
    request2.startDate = "21/08/2025";
    request2.endDate = "24/08/2025";
    request2.status = "Pending";
    request2.totalCost = 90.0;
    request2.brand = "Yamaha";
    request2.model = "Exciter";
    request2.color = "Black";
    request2.size = "150cc";
    request2.plateNo = "51B-67890";
    
    bookings.push_back(request2);
    
    Booking request3;
    request3.bookingId = "BK4";
    request3.renterUsername = "IAmMember5";
    request3.ownerUsername = "iAmMember1";
    request3.motorbikeId = "MB4";
    request3.startDate = "21/08/2025";
    request3.endDate = "23/08/2025";
    request3.status = "Pending";
    request3.totalCost = 60.0;
    request3.brand = "Suzuki";
    request3.model = "Raider";
    request3.color = "White";
    request3.size = "125cc";
    request3.plateNo = "51C-11111";
    
    bookings.push_back(request3);
    
    Booking request4;
    request4.bookingId = "BK5";
    request4.renterUsername = "IAmMember2";
    request4.ownerUsername = "iAmMember1";
    request4.motorbikeId = "MB5";
    request4.startDate = "21/08/2025";
    request4.endDate = "22/08/2025";
    request4.status = "Pending";
    request4.totalCost = 40.0;
    request4.brand = "Piaggio";
    request4.model = "Liberty";
    request4.color = "Green";
    request4.size = "125cc";
    request4.plateNo = "51D-22222";
    
    bookings.push_back(request4);
    
    saveBookings();
}
