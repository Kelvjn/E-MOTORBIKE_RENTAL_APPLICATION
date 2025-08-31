#include "booking.h"
#include "auth.h"
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
    
    // Create sample motorbikes if no motorbikes exist
    if (motorbikes.empty()) {
        createSampleMotorbikes();
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
        
        // Read basic fields with error checking
        if (!getline(ss, booking.bookingId, '|')) continue;
        if (!getline(ss, booking.renterUsername, '|')) continue;
        if (!getline(ss, booking.ownerUsername, '|')) continue;
        if (!getline(ss, booking.motorbikeId, '|')) continue;
        if (!getline(ss, booking.startDate, '|')) continue;
        if (!getline(ss, booking.endDate, '|')) continue;
        if (!getline(ss, booking.status, '|')) continue;
        
        // Read total cost with error handling
        string temp;
        if (!getline(ss, temp, '|')) continue;
        try {
            booking.totalCost = stod(temp);
        } catch (const std::invalid_argument& e) {
            booking.totalCost = 0.0; // Default value
        }
        
        if (!getline(ss, booking.brand, '|')) continue;
        if (!getline(ss, booking.model, '|')) continue;
        if (!getline(ss, booking.color, '|')) continue;
        if (!getline(ss, booking.size, '|')) continue;
        if (!getline(ss, booking.plateNo, '|')) continue;
        
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
        
        // Read basic fields with error checking
        if (!getline(ss, motorbike.motorbikeId, '|')) continue;
        if (!getline(ss, motorbike.ownerUsername, '|')) continue;
        if (!getline(ss, motorbike.brand, '|')) continue;
        if (!getline(ss, motorbike.model, '|')) continue;
        if (!getline(ss, motorbike.color, '|')) continue;
        if (!getline(ss, motorbike.size, '|')) continue;
        if (!getline(ss, motorbike.plateNo, '|')) continue;
        
        // Read price with error handling
        string temp;
        if (!getline(ss, temp, '|')) continue;
        try {
            motorbike.pricePerDay = stod(temp);
        } catch (const std::invalid_argument& e) {
            motorbike.pricePerDay = 0.0; // Default value
        }
        
        if (!getline(ss, motorbike.location, '|')) continue;
        
        // Read availability
        if (!getline(ss, temp, '|')) continue;
        motorbike.isAvailable = (temp == "1");
        
        // Read rating with error handling
        if (!getline(ss, temp, '|')) continue;
        try {
            motorbike.rating = stod(temp);
        } catch (const std::invalid_argument& e) {
            motorbike.rating = 5.0; // Default rating
        }
        
        if (!getline(ss, motorbike.description, '|')) continue;
        
        // Handle new fields with backward compatibility
        if (ss.good()) {
            getline(ss, motorbike.availableStartDate, '|');
            getline(ss, motorbike.availableEndDate, '|');
            
            if (ss.good()) {
                getline(ss, temp, '|');
                try {
                    motorbike.minRenterRating = stod(temp);
                } catch (const std::invalid_argument& e) {
                    motorbike.minRenterRating = 3.0; // Default minimum rating
                }
            } else {
                motorbike.minRenterRating = 3.0; // Default minimum rating
            }
            
            if (ss.good()) {
                getline(ss, temp, '|');
                motorbike.isListed = (temp == "1");
            } else {
                motorbike.isListed = false; // Default to not listed
            }
        } else {
            // Set default values for old format
            motorbike.availableStartDate = "";
            motorbike.availableEndDate = "";
            motorbike.minRenterRating = 3.0;
            motorbike.isListed = false;
        }
        
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
             << motorbike.description << "|"
             << motorbike.availableStartDate << "|"
             << motorbike.availableEndDate << "|"
             << motorbike.minRenterRating << "|"
             << (motorbike.isListed ? "1" : "0") << "\n";
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

vector<Booking> BookingManager::getAllBookings() {
    return bookings; // Return all bookings for admin view
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

vector<Motorbike> BookingManager::getGuestMotorbikes() {
    vector<Motorbike> guestMotorbikes;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.isListed && motorbike.isAvailable) {
            guestMotorbikes.push_back(motorbike);
        }
    }
    return guestMotorbikes;
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

// Electric motorbike listing management methods

string BookingManager::generateMotorbikeId() {
    static int counter = 1;
    return "MB" + to_string(counter++);
}

bool BookingManager::listMotorbike(const string& ownerUsername, const string& brand, 
                                  const string& model, const string& color, 
                                  const string& size, const string& plateNo,
                                  double pricePerDay, const string& location,
                                  const string& availableStartDate, const string& availableEndDate,
                                  double minRenterRating) {
    
    // Check if user already has a motorbike listed
    if (isMotorbikeListed(ownerUsername)) {
        cout << "Error: You already have a motorbike listed. Each member can only list one motorbike.\n";
        return false;
    }
    
    // Validate listing data
    if (!validateListingData(location, availableStartDate, availableEndDate, pricePerDay, minRenterRating)) {
        return false;
    }
    
    // Create new motorbike listing
    Motorbike motorbike;
    motorbike.motorbikeId = generateMotorbikeId();
    motorbike.ownerUsername = ownerUsername;
    motorbike.brand = brand;
    motorbike.model = model;
    motorbike.color = color;
    motorbike.size = size;
    motorbike.plateNo = plateNo;
    motorbike.pricePerDay = pricePerDay;
    motorbike.location = location;
    motorbike.isAvailable = true;
    motorbike.rating = 5.0; // Default rating for new listing
    motorbike.description = brand + " " + model + " - " + color + " " + size;
    motorbike.availableStartDate = availableStartDate;
    motorbike.availableEndDate = availableEndDate;
    motorbike.minRenterRating = minRenterRating;
    motorbike.isListed = true;
    
    motorbikes.push_back(motorbike);
    saveMotorbikes();
    
    cout << "Motorbike listed successfully!\n";
    cout << "Motorbike ID: " << motorbike.motorbikeId << "\n";
    cout << "Brand: " << brand << " " << model << "\n";
    cout << "Location: " << location << "\n";
    cout << "Daily Rate: " << pricePerDay << " CP\n";
    cout << "Available Period: " << availableStartDate << " to " << availableEndDate << "\n";
    cout << "Minimum Renter Rating: " << minRenterRating << "\n";
    
    return true;
}

bool BookingManager::unlistMotorbike(const string& ownerUsername) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == ownerUsername && motorbike.isListed) {
            // Check if motorbike is currently booked
            if (isMotorbikeBooked(ownerUsername)) {
                cout << "Error: Cannot unlist motorbike that is currently booked.\n";
                return false;
            }
            
            motorbike.isListed = false;
            motorbike.isAvailable = false;
            saveMotorbikes();
            
            cout << "Motorbike unlisted successfully!\n";
            return true;
        }
    }
    
    cout << "Error: No listed motorbike found for this user.\n";
    return false;
}

bool BookingManager::isMotorbikeListed(const string& ownerUsername) {
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == ownerUsername && motorbike.isListed) {
            return true;
        }
    }
    return false;
}

bool BookingManager::isMotorbikeBooked(const string& ownerUsername) {
    for (const Booking& booking : bookings) {
        if (booking.ownerUsername == ownerUsername && 
            (booking.status == "Pending" || booking.status == "Approved")) {
            return true;
        }
    }
    return false;
}

bool BookingManager::validateListingData(const string& location, const string& startDate, 
                                        const string& endDate, double pricePerDay, double minRating) {
    // Validate location (HCMC or Hanoi only)
    if (location != "HCMC" && location != "Hanoi") {
        cout << "Error: Location must be either 'HCMC' or 'Hanoi'.\n";
        return false;
    }
    
    // Validate price per day (must be positive)
    if (pricePerDay <= 0) {
        cout << "Error: Daily rental rate must be greater than 0 CP.\n";
        return false;
    }
    
    // Validate minimum renter rating (must be between 1.0 and 5.0)
    if (minRating < 1.0 || minRating > 5.0) {
        cout << "Error: Minimum renter rating must be between 1.0 and 5.0.\n";
        return false;
    }
    
    // Validate date format and logic (basic validation)
    if (startDate.empty() || endDate.empty()) {
        cout << "Error: Available rental period dates cannot be empty.\n";
        return false;
    }
    
    // Additional date validation could be added here
    // For now, we'll assume dates are in DD/MM/YYYY format
    
    return true;
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

void BookingManager::createSampleMotorbikes() {
    // Create 20 sample electric motorbikes with diverse specifications
    
    // HCMC Motorbikes (10)
    Motorbike mb1;
    mb1.motorbikeId = "MB1";
    mb1.ownerUsername = "iAmMember1";
    mb1.brand = "VinFast";
    mb1.model = "Klara S";
    mb1.color = "Red";
    mb1.size = "50cc";
    mb1.plateNo = "59X3-216.86";
    mb1.pricePerDay = 25.0;
    mb1.location = "HCMC";
    mb1.isAvailable = true;
    mb1.rating = 4.5;
    mb1.description = "VinFast Klara S - Red 50cc";
    mb1.availableStartDate = "01/08/2025";
    mb1.availableEndDate = "31/12/2025";
    mb1.minRenterRating = 3.5;
    mb1.isListed = true;
    motorbikes.push_back(mb1);
    
    Motorbike mb2;
    mb2.motorbikeId = "MB2";
    mb2.ownerUsername = "iAmMember2";
    mb2.brand = "Honda";
    mb2.model = "Vision";
    mb2.color = "Blue";
    mb2.size = "110cc";
    mb2.plateNo = "51A-12345";
    mb2.pricePerDay = 30.0;
    mb2.location = "HCMC";
    mb2.isAvailable = true;
    mb2.rating = 4.2;
    mb2.description = "Honda Vision - Blue 110cc";
    mb2.availableStartDate = "01/08/2025";
    mb2.availableEndDate = "30/11/2025";
    mb2.minRenterRating = 3.0;
    mb2.isListed = true;
    motorbikes.push_back(mb2);
    
    Motorbike mb3;
    mb3.motorbikeId = "MB3";
    mb3.ownerUsername = "iAmMember3";
    mb3.brand = "Yamaha";
    mb3.model = "Exciter";
    mb3.color = "Black";
    mb3.size = "150cc";
    mb3.plateNo = "51B-67890";
    mb3.pricePerDay = 45.0;
    mb3.location = "HCMC";
    mb3.isAvailable = true;
    mb3.rating = 4.8;
    mb3.description = "Yamaha Exciter - Black 150cc";
    mb3.availableStartDate = "01/08/2025";
    mb3.availableEndDate = "31/12/2025";
    mb3.minRenterRating = 4.0;
    mb3.isListed = true;
    motorbikes.push_back(mb3);
    
    Motorbike mb4;
    mb4.motorbikeId = "MB4";
    mb4.ownerUsername = "iAmMember4";
    mb4.brand = "Suzuki";
    mb4.model = "Raider";
    mb4.color = "White";
    mb4.size = "125cc";
    mb4.plateNo = "51C-11111";
    mb4.pricePerDay = 35.0;
    mb4.location = "HCMC";
    mb4.isAvailable = true;
    mb4.rating = 4.0;
    mb4.description = "Suzuki Raider - White 125cc";
    mb4.availableStartDate = "01/08/2025";
    mb4.availableEndDate = "30/09/2025";
    mb4.minRenterRating = 3.5;
    mb4.isListed = true;
    motorbikes.push_back(mb4);
    
    Motorbike mb5;
    mb5.motorbikeId = "MB5";
    mb5.ownerUsername = "iAmMember5";
    mb5.brand = "Piaggio";
    mb5.model = "Liberty";
    mb5.color = "Green";
    mb5.size = "125cc";
    mb5.plateNo = "51D-22222";
    mb5.pricePerDay = 40.0;
    mb5.location = "HCMC";
    mb5.isAvailable = true;
    mb5.rating = 4.3;
    mb5.description = "Piaggio Liberty - Green 125cc";
    mb5.availableStartDate = "01/08/2025";
    mb5.availableEndDate = "31/10/2025";
    mb5.minRenterRating = 3.8;
    mb5.isListed = true;
    motorbikes.push_back(mb5);
    
    Motorbike mb6;
    mb6.motorbikeId = "MB6";
    mb6.ownerUsername = "iAmMember6";
    mb6.brand = "VinFast";
    mb6.model = "Theon";
    mb6.color = "Silver";
    mb6.size = "150cc";
    mb6.plateNo = "51E-33333";
    mb6.pricePerDay = 50.0;
    mb6.location = "HCMC";
    mb6.isAvailable = true;
    mb6.rating = 4.6;
    mb6.description = "VinFast Theon - Silver 150cc";
    mb6.availableStartDate = "01/08/2025";
    mb6.availableEndDate = "31/12/2025";
    mb6.minRenterRating = 4.2;
    mb6.isListed = true;
    motorbikes.push_back(mb6);
    
    Motorbike mb7;
    mb7.motorbikeId = "MB7";
    mb7.ownerUsername = "iAmMember7";
    mb7.brand = "Honda";
    mb7.model = "Air Blade";
    mb7.color = "Orange";
    mb7.size = "125cc";
    mb7.plateNo = "51F-44444";
    mb7.pricePerDay = 38.0;
    mb7.location = "HCMC";
    mb7.isAvailable = true;
    mb7.rating = 4.1;
    mb7.description = "Honda Air Blade - Orange 125cc";
    mb7.availableStartDate = "01/08/2025";
    mb7.availableEndDate = "30/11/2025";
    mb7.minRenterRating = 3.2;
    mb7.isListed = true;
    motorbikes.push_back(mb7);
    
    Motorbike mb8;
    mb8.motorbikeId = "MB8";
    mb8.ownerUsername = "iAmMember8";
    mb8.brand = "Yamaha";
    mb8.model = "NMAX";
    mb8.color = "Gray";
    mb8.size = "155cc";
    mb8.plateNo = "51G-55555";
    mb8.pricePerDay = 55.0;
    mb8.location = "HCMC";
    mb8.isAvailable = true;
    mb8.rating = 4.7;
    mb8.description = "Yamaha NMAX - Gray 155cc";
    mb8.availableStartDate = "01/08/2025";
    mb8.availableEndDate = "31/12/2025";
    mb8.minRenterRating = 4.5;
    mb8.isListed = true;
    motorbikes.push_back(mb8);
    
    Motorbike mb9;
    mb9.motorbikeId = "MB9";
    mb9.ownerUsername = "iAmMember9";
    mb9.brand = "Suzuki";
    mb9.model = "Address";
    mb9.color = "Yellow";
    mb9.size = "110cc";
    mb9.plateNo = "51H-66666";
    mb9.pricePerDay = 28.0;
    mb9.location = "HCMC";
    mb9.isAvailable = true;
    mb9.rating = 3.9;
    mb9.description = "Suzuki Address - Yellow 110cc";
    mb9.availableStartDate = "01/08/2025";
    mb9.availableEndDate = "30/09/2025";
    mb9.minRenterRating = 3.0;
    mb9.isListed = true;
    motorbikes.push_back(mb9);
    
    Motorbike mb10;
    mb10.motorbikeId = "MB10";
    mb10.ownerUsername = "iAmMember10";
    mb10.brand = "VinFast";
    mb10.model = "Ludo";
    mb10.color = "Purple";
    mb10.size = "50cc";
    mb10.plateNo = "51I-77777";
    mb10.pricePerDay = 20.0;
    mb10.location = "HCMC";
    mb10.isAvailable = true;
    mb10.rating = 4.0;
    mb10.description = "VinFast Ludo - Purple 50cc";
    mb10.availableStartDate = "01/08/2025";
    mb10.availableEndDate = "31/10/2025";
    mb10.minRenterRating = 2.5;
    mb10.isListed = true;
    motorbikes.push_back(mb10);
    
    // Hanoi Motorbikes (10)
    Motorbike mb11;
    mb11.motorbikeId = "MB11";
    mb11.ownerUsername = "iAmMember11";
    mb11.brand = "Honda";
    mb11.model = "SH";
    mb11.color = "White";
    mb11.size = "150cc";
    mb11.plateNo = "30A-88888";
    mb11.pricePerDay = 60.0;
    mb11.location = "Hanoi";
    mb11.isAvailable = true;
    mb11.rating = 4.9;
    mb11.description = "Honda SH - White 150cc";
    mb11.availableStartDate = "01/08/2025";
    mb11.availableEndDate = "31/12/2025";
    mb11.minRenterRating = 4.5;
    mb11.isListed = true;
    motorbikes.push_back(mb11);
    
    Motorbike mb12;
    mb12.motorbikeId = "MB12";
    mb12.ownerUsername = "iAmMember12";
    mb12.brand = "Yamaha";
    mb12.model = "XSR";
    mb12.color = "Black";
    mb12.size = "155cc";
    mb12.plateNo = "30B-99999";
    mb12.pricePerDay = 65.0;
    mb12.location = "Hanoi";
    mb12.isAvailable = true;
    mb12.rating = 4.8;
    mb12.description = "Yamaha XSR - Black 155cc";
    mb12.availableStartDate = "01/08/2025";
    mb12.availableEndDate = "30/11/2025";
    mb12.minRenterRating = 4.3;
    mb12.isListed = true;
    motorbikes.push_back(mb12);
    
    Motorbike mb13;
    mb13.motorbikeId = "MB13";
    mb13.ownerUsername = "iAmMember13";
    mb13.brand = "VinFast";
    mb13.model = "Klara";
    mb13.color = "Blue";
    mb13.size = "50cc";
    mb13.plateNo = "30C-10101";
    mb13.pricePerDay = 22.0;
    mb13.location = "Hanoi";
    mb13.isAvailable = true;
    mb13.rating = 4.2;
    mb13.description = "VinFast Klara - Blue 50cc";
    mb13.availableStartDate = "01/08/2025";
    mb13.availableEndDate = "31/10/2025";
    mb13.minRenterRating = 3.0;
    mb13.isListed = true;
    motorbikes.push_back(mb13);
    
    Motorbike mb14;
    mb14.motorbikeId = "MB14";
    mb14.ownerUsername = "iAmMember14";
    mb14.brand = "Suzuki";
    mb14.model = "Burgman";
    mb14.color = "Red";
    mb14.size = "125cc";
    mb14.plateNo = "30D-20202";
    mb14.pricePerDay = 42.0;
    mb14.location = "Hanoi";
    mb14.isAvailable = true;
    mb14.rating = 4.4;
    mb14.description = "Suzuki Burgman - Red 125cc";
    mb14.availableStartDate = "01/08/2025";
    mb14.availableEndDate = "31/12/2025";
    mb14.minRenterRating = 3.8;
    mb14.isListed = true;
    motorbikes.push_back(mb14);
    
    Motorbike mb15;
    mb15.motorbikeId = "MB15";
    mb15.ownerUsername = "iAmMember15";
    mb15.brand = "Honda";
    mb15.model = "PCX";
    mb15.color = "Silver";
    mb15.size = "150cc";
    mb15.plateNo = "30E-30303";
    mb15.pricePerDay = 58.0;
    mb15.location = "Hanoi";
    mb15.isAvailable = true;
    mb15.rating = 4.6;
    mb15.description = "Honda PCX - Silver 150cc";
    mb15.availableStartDate = "01/08/2025";
    mb15.availableEndDate = "30/11/2025";
    mb15.minRenterRating = 4.2;
    mb15.isListed = true;
    motorbikes.push_back(mb15);
    
    Motorbike mb16;
    mb16.motorbikeId = "MB16";
    mb16.ownerUsername = "iAmMember16";
    mb16.brand = "Yamaha";
    mb16.model = "Aerox";
    mb16.color = "Green";
    mb16.size = "155cc";
    mb16.plateNo = "30F-40404";
    mb16.pricePerDay = 52.0;
    mb16.location = "Hanoi";
    mb16.isAvailable = true;
    mb16.rating = 4.3;
    mb16.description = "Yamaha Aerox - Green 155cc";
    mb16.availableStartDate = "01/08/2025";
    mb16.availableEndDate = "31/10/2025";
    mb16.minRenterRating = 3.9;
    mb16.isListed = true;
    motorbikes.push_back(mb16);
    
    Motorbike mb17;
    mb17.motorbikeId = "MB17";
    mb17.ownerUsername = "iAmMember17";
    mb17.brand = "VinFast";
    mb17.model = "Theon";
    mb17.color = "Orange";
    mb17.size = "150cc";
    mb17.plateNo = "30G-50505";
    mb17.pricePerDay = 48.0;
    mb17.location = "Hanoi";
    mb17.isAvailable = true;
    mb17.rating = 4.5;
    mb17.description = "VinFast Theon - Orange 150cc";
    mb17.availableStartDate = "01/08/2025";
    mb17.availableEndDate = "31/12/2025";
    mb17.minRenterRating = 4.0;
    mb17.isListed = true;
    motorbikes.push_back(mb17);
    
    Motorbike mb18;
    mb18.motorbikeId = "MB18";
    mb18.ownerUsername = "iAmMember18";
    mb18.brand = "Piaggio";
    mb18.model = "Medley";
    mb18.color = "Gray";
    mb18.size = "125cc";
    mb18.plateNo = "30H-60606";
    mb18.pricePerDay = 45.0;
    mb18.location = "Hanoi";
    mb18.isAvailable = true;
    mb18.rating = 4.1;
    mb18.description = "Piaggio Medley - Gray 125cc";
    mb18.availableStartDate = "01/08/2025";
    mb18.availableEndDate = "30/09/2025";
    mb18.minRenterRating = 3.5;
    mb18.isListed = true;
    motorbikes.push_back(mb18);
    
    Motorbike mb19;
    mb19.motorbikeId = "MB19";
    mb19.ownerUsername = "iAmMember19";
    mb19.brand = "Honda";
    mb19.model = "Lead";
    mb19.color = "Yellow";
    mb19.size = "110cc";
    mb19.plateNo = "30I-70707";
    mb19.pricePerDay = 32.0;
    mb19.location = "Hanoi";
    mb19.isAvailable = true;
    mb19.rating = 3.8;
    mb19.description = "Honda Lead - Yellow 110cc";
    mb19.availableStartDate = "01/08/2025";
    mb19.availableEndDate = "31/10/2025";
    mb19.minRenterRating = 3.2;
    mb19.isListed = true;
    motorbikes.push_back(mb19);
    
    Motorbike mb20;
    mb20.motorbikeId = "MB20";
    mb20.ownerUsername = "iAmMember20";
    mb20.brand = "Suzuki";
    mb20.model = "Swish";
    mb20.color = "Purple";
    mb20.size = "125cc";
    mb20.plateNo = "30J-80808";
    mb20.pricePerDay = 38.0;
    mb20.location = "Hanoi";
    mb20.isAvailable = true;
    mb20.rating = 4.0;
    mb20.description = "Suzuki Swish - Purple 125cc";
    mb20.availableStartDate = "01/08/2025";
    mb20.availableEndDate = "30/11/2025";
    mb20.minRenterRating = 3.6;
    mb20.isListed = true;
    motorbikes.push_back(mb20);
    
    saveMotorbikes();
}

// Motorbike search and filtering methods implementation

vector<Motorbike> BookingManager::searchMotorbikes(const string& searchDate, const string& city, 
                                                   const string& username, Auth& auth) {
    vector<Motorbike> results;
    
    for (const Motorbike& motorbike : motorbikes) {
        if (meetsSearchCriteria(motorbike, searchDate, city, username, auth)) {
            results.push_back(motorbike);
        }
    }
    
    return results;
}

bool BookingManager::meetsSearchCriteria(const Motorbike& motorbike, const string& searchDate, 
                                        const string& city, const string& username, Auth& auth) {
    // Check if motorbike is listed and available
    if (!motorbike.isListed || !motorbike.isAvailable) {
        return false;
    }
    
    // Check if motorbike is in the selected city
    if (motorbike.location != city) {
        return false;
    }
    
    // Check if search date is within available period
    if (!isDateInRange(searchDate, motorbike.availableStartDate, motorbike.availableEndDate)) {
        return false;
    }
    
    // Get user's renter rating
    double userRating = auth.getUserRenterRating(username);
    
    // Check if user's rating meets minimum requirement
    if (userRating < motorbike.minRenterRating) {
        return false;
    }
    
    // Calculate total cost for one day rental
    double totalCost = motorbike.pricePerDay;
    
    // Check if user has sufficient credit points
    double userCreditPoints = auth.getUserCreditPoints(username);
    if (userCreditPoints < totalCost) {
        return false;
    }
    
    // Check license requirement for engine size > 50cc
    int engineSize = getEngineSize(motorbike.size);
    if (engineSize > 50 && !hasValidLicense(username, auth, engineSize)) {
        return false;
    }
    
    return true;
}

bool BookingManager::isDateInRange(const string& searchDate, const string& startDate, const string& endDate) {
    // Simple date comparison (assuming DD/MM/YYYY format)
    // In a real application, you would use proper date parsing
    return searchDate >= startDate && searchDate <= endDate;
}

double BookingManager::calculateTotalCost(const Motorbike& motorbike, const string& startDate, const string& endDate) {
    // Simple calculation - in a real app, you'd parse dates and calculate days
    // For now, assume 1 day rental
    (void)startDate; // Suppress unused parameter warning
    (void)endDate;   // Suppress unused parameter warning
    return motorbike.pricePerDay;
}

int BookingManager::getEngineSize(const string& size) {
    // Extract engine size from string like "150cc"
    string numericPart;
    for (char c : size) {
        if (isdigit(c)) {
            numericPart += c;
        }
    }
    
    if (numericPart.empty()) {
        return 0;
    }
    
    try {
        return stoi(numericPart);
    } catch (const std::invalid_argument& e) {
        return 0;
    }
}

bool BookingManager::hasValidLicense(const string& username, Auth& auth, int engineSize) {
    // Get user's license expiry date
    string licenseExpiry = auth.getUserLicenseExpiry(username);
    
    // Simple check - if expiry is in the future, license is valid
    // In a real app, you'd parse the date properly
    (void)engineSize; // Suppress unused parameter warning
    return licenseExpiry > "2025-12-31"; // Assuming current date is 2025
}

vector<string> BookingManager::getMotorbikeReviews(const string& motorbikeId) {
    vector<string> reviews;
    
    // Generate sample reviews based on motorbike ID
    // In a real application, this would read from a reviews database
    if (motorbikeId == "MB1") {
        reviews.push_back("Great electric bike, very smooth ride!");
        reviews.push_back("Perfect for city commuting, highly recommend.");
        reviews.push_back("Good battery life, easy to handle.");
    } else if (motorbikeId == "MB2") {
        reviews.push_back("Reliable Honda quality, excellent performance.");
        reviews.push_back("Comfortable seat, good for long rides.");
        reviews.push_back("Fuel efficient and low maintenance.");
    } else {
        reviews.push_back("Good overall experience with this motorbike.");
        reviews.push_back("Meets expectations for the price.");
        reviews.push_back("Would recommend to others.");
    }
    
    return reviews;
}

double BookingManager::getAverageRating(const string& motorbikeId) {
    // Get the motorbike's rating from the motorbikes vector
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.motorbikeId == motorbikeId) {
            return motorbike.rating;
        }
    }
    return 0.0;
}
