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
    bool isFirstLine = true;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Skip header line (starts with #)
        if (isFirstLine && line[0] == '#') {
            isFirstLine = false;
            continue;
        }
        isFirstLine = false;
        
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
    
    // Write header for admin readability
    file << "# Booking Data Format: bookingId|renterUsername|ownerUsername|motorbikeId|startDate|endDate|status|totalCost|brand|model|color|size|plateNo\n";
    
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
    bool isFirstLine = true;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Skip header line (starts with #)
        if (isFirstLine && line[0] == '#') {
            isFirstLine = false;
            continue;
        }
        isFirstLine = false;
        
        try {
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
            if (!temp.empty()) {
        motorbike.pricePerDay = stod(temp);
            } else {
                motorbike.pricePerDay = 0.0;
            }
            
            getline(ss, motorbike.city, '|');
            getline(ss, motorbike.startDate, '|');
            getline(ss, motorbike.endDate, '|');
            
            getline(ss, temp, '|');
            if (!temp.empty()) {
                motorbike.minRenterRating = stod(temp);
            } else {
                motorbike.minRenterRating = 0.0;
            }
        
        getline(ss, temp, '|');
        motorbike.isAvailable = (temp == "1");
        
        getline(ss, temp, '|');
            motorbike.isListed = (temp == "1");
            
            getline(ss, temp, '|');
            if (!temp.empty()) {
        motorbike.rating = stod(temp);
            } else {
                motorbike.rating = 0.0;
            }
        
        getline(ss, motorbike.description, '|');
        
        motorbikes.push_back(motorbike);
        } catch (const exception& e) {
            // Skip malformed lines
            cout << "Warning: Skipping malformed motorbike data line\n";
            continue;
        }
    }
    
    file.close();
}

void BookingManager::saveMotorbikes() {
    ofstream file(motorbikeFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot open motorbikes.txt for writing\n";
        return;
    }
    
    // Write header for admin readability
    file << "# Motorbike Data Format: motorbikeId|ownerUsername|brand|model|color|size|plateNo|pricePerDay|city|startDate|endDate|minRenterRating|isAvailable|isListed|rating|description\n";
    
    for (const Motorbike& motorbike : motorbikes) {
        file << motorbike.motorbikeId << "|"
             << motorbike.ownerUsername << "|"
             << motorbike.brand << "|"
             << motorbike.model << "|"
             << motorbike.color << "|"
             << motorbike.size << "|"
             << motorbike.plateNo << "|"
             << motorbike.pricePerDay << "|"
             << motorbike.city << "|"
             << motorbike.startDate << "|"
             << motorbike.endDate << "|"
             << motorbike.minRenterRating << "|"
             << (motorbike.isAvailable ? "1" : "0") << "|"
             << (motorbike.isListed ? "1" : "0") << "|"
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
        if (motorbike.isAvailable && motorbike.isListed) {
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
    // Calculate renter rating based on completed bookings and reviews
    // For now, check if user exists in auth system and return their rating
    // TODO: This should be integrated with Auth class to get actual user rating
    
    // Count completed bookings as renter
    int completedBookings = 0;
    for (const Booking& booking : bookings) {
        if (booking.renterUsername == username && booking.status == "Completed") {
            completedBookings++;
        }
    }
    
    // Base rating starts at 3.0 for new users
    double baseRating = 3.0;
    
    // Increase rating based on completed bookings (simple algorithm)
    double bonusRating = completedBookings * 0.1; // 0.1 point per completed booking
    double finalRating = baseRating + bonusRating;
    
    // Cap at 5.0
    return (finalRating > 5.0) ? 5.0 : finalRating;
}

double BookingManager::getUserMotorbikeRating(const string& username) {
    vector<Motorbike> userMotorbikes = getUserMotorbikes(username);
    
    if (userMotorbikes.empty()) {
        return 0.0; // No motorbikes registered
    }
    
    double totalRating = 0.0;
    int ratedMotorbikes = 0;
    
    for (const Motorbike& motorbike : userMotorbikes) {
        if (motorbike.rating > 0.0) { // Only count motorbikes with reviews
            totalRating += motorbike.rating;
            ratedMotorbikes++;
        }
    }
    
    if (ratedMotorbikes == 0) {
        return 0.0; // No rated motorbikes
    }
    
    return totalRating / ratedMotorbikes;
}

bool BookingManager::listMotorbike(const string& ownerUsername, const string& brand, const string& model,
                                  const string& color, const string& size, const string& plateNo,
                                  double pricePerDay, const string& city, const string& startDate,
                                  const string& endDate, double minRenterRating, const string& description) {
    
    // Check if user already has a listed motorbike
    if (hasUserListedMotorbike(ownerUsername)) {
        cout << "Error: You can only register one electric motorbike.\n";
        return false;
    }
    
    // Validate city
    if (!validateCity(city)) {
        cout << "Error: City must be either 'HCMC' or 'Hanoi'.\n";
        return false;
    }
    
    // Validate dates
    if (!validateDateFormat(startDate) || !validateDateFormat(endDate)) {
        cout << "Error: Invalid date format. Please use DD/MM/YYYY format.\n";
        return false;
    }
    
    if (!isDateValid(startDate, endDate)) {
        cout << "Error: End date must be after start date.\n";
        return false;
    }
    
    // Validate price
    if (pricePerDay <= 0) {
        cout << "Error: Daily rental rate must be positive.\n";
        return false;
    }
    
    // Validate minimum renter rating
    if (minRenterRating < 0 || minRenterRating > 5) {
        cout << "Error: Minimum renter rating must be between 0 and 5.\n";
        return false;
    }
    
    // Generate unique motorbike ID
    static int counter = 1;
    string motorbikeId = "MB" + to_string(counter++);
    
    // Create new motorbike
    Motorbike motorbike;
    motorbike.motorbikeId = motorbikeId;
    motorbike.ownerUsername = ownerUsername;
    motorbike.brand = brand;
    motorbike.model = model;
    motorbike.color = color;
    motorbike.size = size;
    motorbike.plateNo = plateNo;
    motorbike.pricePerDay = pricePerDay;
    motorbike.city = city;
    motorbike.startDate = startDate;
    motorbike.endDate = endDate;
    motorbike.minRenterRating = minRenterRating;
    motorbike.isAvailable = true;
    motorbike.isListed = true;
    motorbike.rating = 0.0; // Initial rating
    motorbike.description = description;
    
    motorbikes.push_back(motorbike);
    saveMotorbikes();
    
    cout << "Motorbike listed successfully! ID: " << motorbikeId << "\n";
    return true;
}

bool BookingManager::unlistMotorbike(const string& ownerUsername) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == ownerUsername && motorbike.isListed) {
            // Check if motorbike has pending bookings
            for (const Booking& booking : bookings) {
                if (booking.motorbikeId == motorbike.motorbikeId && 
                    (booking.status == "Pending" || booking.status == "Approved")) {
                    cout << "Error: Cannot unlist motorbike with pending or approved bookings.\n";
                    return false;
                }
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

bool BookingManager::hasUserListedMotorbike(const string& username) {
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == username && motorbike.isListed) {
            return true;
        }
    }
    return false;
}

Motorbike* BookingManager::getUserMotorbike(const string& username) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.ownerUsername == username) {
            return &motorbike;
        }
    }
    return nullptr;
}

bool BookingManager::validateCity(const string& city) {
    return (city == "HCMC" || city == "Hanoi");
}

bool BookingManager::validateDateFormat(const string& date) {
    // Simple date format validation (DD/MM/YYYY)
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    // Check if day, month, year are numeric
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Skip '/' characters
        if (!isdigit(date[i])) return false;
    }
    
    // Basic range validation
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    
    // Get current year (simplified - in real implementation, use system time)
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    int currentYear = currentTime->tm_year + 1900;
    
    if (year < currentYear) return false;
    
    return true;
}

bool BookingManager::isDateValid(const string& startDate, const string& endDate) {
    // Extract dates for comparison
    int startDay = stoi(startDate.substr(0, 2));
    int startMonth = stoi(startDate.substr(3, 2));
    int startYear = stoi(startDate.substr(6, 4));
    
    int endDay = stoi(endDate.substr(0, 2));
    int endMonth = stoi(endDate.substr(3, 2));
    int endYear = stoi(endDate.substr(6, 4));
    
    // Simple date comparison (year, month, day)
    if (endYear > startYear) return true;
    if (endYear < startYear) return false;
    
    if (endMonth > startMonth) return true;
    if (endMonth < startMonth) return false;
    
    return endDay > startDay;
}


bool BookingManager::isDateInRange(const string& searchDate, const string& startDate, const string& endDate) {
    // Simple date comparison (assumes DD/MM/YYYY format)
    // Extract day, month, year for comparison
    int searchDay = stoi(searchDate.substr(0, 2));
    int searchMonth = stoi(searchDate.substr(3, 2));
    int searchYear = stoi(searchDate.substr(6, 4));
    
    int startDay = stoi(startDate.substr(0, 2));
    int startMonth = stoi(startDate.substr(3, 2));
    int startYear = stoi(startDate.substr(6, 4));
    
    int endDay = stoi(endDate.substr(0, 2));
    int endMonth = stoi(endDate.substr(3, 2));
    int endYear = stoi(endDate.substr(6, 4));
    
    // Convert to comparable format (YYYYMMDD)
    int searchDateInt = searchYear * 10000 + searchMonth * 100 + searchDay;
    int startDateInt = startYear * 10000 + startMonth * 100 + startDay;
    int endDateInt = endYear * 10000 + endMonth * 100 + endDay;
    
    return (searchDateInt >= startDateInt && searchDateInt <= endDateInt);
}

int BookingManager::getEngineSize(const string& size) {
    // Extract numeric value from size string (e.g., "125cc" -> 125)
    string numStr = "";
    for (char c : size) {
        if (isdigit(c)) {
            numStr += c;
        }
    }
    return numStr.empty() ? 0 : stoi(numStr);
}

double BookingManager::calculateRentalCost(const Motorbike& motorbike, const string& searchDate) {
    // For simplicity, assume 1 day rental
    // In real implementation, this would calculate based on rental duration
    (void)searchDate; // Suppress unused parameter warning
    return motorbike.pricePerDay;
}

vector<Motorbike> BookingManager::searchMotorbikes(const UserInfo& criteria) {
    vector<Motorbike> availableMotorbikes = getAvailableMotorbikes();
    return filterMotorbikes(availableMotorbikes, criteria);
}

vector<Motorbike> BookingManager::filterMotorbikes(const vector<Motorbike>& motorbikes, const UserInfo& criteria) {
    vector<Motorbike> filteredResults;
    
    for (const Motorbike& motorbike : motorbikes) {
        // Check all filtering criteria
        bool passesAllFilters = true;
        
        // 1. City filter
        if (motorbike.city != criteria.city) {
            passesAllFilters = false;
        }
        
        // 2. Date availability filter
        if (!isDateInRange(criteria.searchDate, motorbike.startDate, motorbike.endDate)) {
            passesAllFilters = false;
        }
        
        // 3. Renter rating filter
        if (criteria.userRating < motorbike.minRenterRating) {
            passesAllFilters = false;
        }
        
        // 4. Credit points filter (sufficient CPs for rental)
        double rentalCost = calculateRentalCost(motorbike, criteria.searchDate);
        if (criteria.userCreditPoints < rentalCost) {
            passesAllFilters = false;
        }
        
        // 5. License filter for engines > 50cc
        int engineSize = getEngineSize(motorbike.size);
        if (engineSize > 50 && !criteria.hasValidLicense) {
            passesAllFilters = false;
        }
        
        if (passesAllFilters) {
            filteredResults.push_back(motorbike);
        }
    }
    
    return filteredResults;
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
    
    // Create sample motorbikes if none exist
    if (motorbikes.empty()) {
        createSampleMotorbikes();
    }
}

void BookingManager::createSampleMotorbikes() {
    // Sample motorbike 1
    Motorbike mb1;
    mb1.motorbikeId = "MB1";
    mb1.ownerUsername = "Thinh";
    mb1.brand = "VinFast";
    mb1.model = "Klara S";
    mb1.color = "Red";
    mb1.size = "50cc";
    mb1.plateNo = "59X3-216.86";
    mb1.pricePerDay = 25.0;
    mb1.city = "HCMC";
    mb1.startDate = "01/08/2025";
    mb1.endDate = "31/12/2025";
    mb1.minRenterRating = 2.5;
    mb1.isAvailable = true;
    mb1.isListed = true;
    mb1.rating = 4.5;
    mb1.description = "Eco-friendly electric scooter, perfect for city rides";
    motorbikes.push_back(mb1);
    
    // Sample motorbike 2
    Motorbike mb2;
    mb2.motorbikeId = "MB2";
    mb2.ownerUsername = "admin";
    mb2.brand = "Honda";
    mb2.model = "Vision";
    mb2.color = "Blue";
    mb2.size = "110cc";
    mb2.plateNo = "51A-12345";
    mb2.pricePerDay = 35.0;
    mb2.city = "HCMC";
    mb2.startDate = "01/08/2025";
    mb2.endDate = "30/11/2025";
    mb2.minRenterRating = 3.0;
    mb2.isAvailable = true;
    mb2.isListed = true;
    mb2.rating = 4.2;
    mb2.description = "Reliable Honda scooter with good fuel efficiency";
    motorbikes.push_back(mb2);
    
    // Sample motorbike 3
    Motorbike mb3;
    mb3.motorbikeId = "MB3";
    mb3.ownerUsername = "admin";
    mb3.brand = "Yamaha";
    mb3.model = "Exciter";
    mb3.color = "Black";
    mb3.size = "150cc";
    mb3.plateNo = "51B-67890";
    mb3.pricePerDay = 45.0;
    mb3.city = "Hanoi";
    mb3.startDate = "01/08/2025";
    mb3.endDate = "31/12/2025";
    mb3.minRenterRating = 4.0;
    mb3.isAvailable = true;
    mb3.isListed = true;
    mb3.rating = 4.8;
    mb3.description = "Powerful sport bike for experienced riders";
    motorbikes.push_back(mb3);
    
    // Sample motorbike 4 (small engine, no license required)
    Motorbike mb4;
    mb4.motorbikeId = "MB4";
    mb4.ownerUsername = "Thinh";
    mb4.brand = "Piaggio";
    mb4.model = "Zip";
    mb4.color = "White";
    mb4.size = "50cc";
    mb4.plateNo = "51C-11111";
    mb4.pricePerDay = 20.0;
    mb4.city = "HCMC";
    mb4.startDate = "15/08/2025";
    mb4.endDate = "31/03/2026";
    mb4.minRenterRating = 2.0;
    mb4.isAvailable = true;
    mb4.isListed = true;
    mb4.rating = 3.8;
    mb4.description = "Small and easy to handle, great for beginners";
    motorbikes.push_back(mb4);
    
    // Additional 26 motorbikes (MB5-MB30)
    vector<vector<string>> motorbikeData = {
        {"MB5", "user1", "Honda", "Lead", "Silver", "125cc", "51D-22222", "40", "HCMC", "01/09/2025", "31/01/2026", "3.5", "Premium scooter with spacious storage"},
        {"MB6", "user2", "Yamaha", "Janus", "Blue", "125cc", "51E-33333", "38", "Hanoi", "01/08/2025", "31/12/2025", "3.0", "Stylish design with modern features"},
        {"MB7", "user3", "SYM", "Attila", "Black", "125cc", "51F-44444", "42", "HCMC", "15/08/2025", "28/02/2026", "4.0", "Sporty look with excellent performance"},
        {"MB8", "user4", "Suzuki", "Raider", "Red", "150cc", "51G-55555", "48", "Hanoi", "01/08/2025", "31/03/2026", "4.2", "High performance sport bike"},
        {"MB9", "user5", "Honda", "Wave Alpha", "White", "110cc", "51H-66666", "32", "HCMC", "01/09/2025", "30/11/2025", "2.8", "Classic and reliable commuter bike"},
        {"MB10", "user6", "Yamaha", "Sirius", "Blue", "110cc", "51I-77777", "33", "Hanoi", "01/08/2025", "31/01/2026", "3.2", "Fuel-efficient with comfortable ride"},
        {"MB11", "user7", "Honda", "Air Blade", "Gray", "150cc", "51J-88888", "50", "HCMC", "15/08/2025", "31/12/2025", "4.5", "Premium automatic scooter"},
        {"MB12", "user8", "Piaggio", "Liberty", "Green", "125cc", "51K-99999", "45", "Hanoi", "01/09/2025", "28/02/2026", "3.8", "Italian design with smooth operation"},
        {"MB13", "user9", "VinFast", "Theon", "Blue", "50cc", "52A-11111", "28", "HCMC", "01/08/2025", "31/03/2026", "2.5", "Electric scooter with modern technology"},
        {"MB14", "user10", "Honda", "SH Mode", "Black", "125cc", "52B-22222", "55", "Hanoi", "01/08/2025", "31/12/2025", "4.0", "Premium scooter with advanced features"},
        {"MB15", "user11", "Yamaha", "Grande", "White", "125cc", "52C-33333", "47", "HCMC", "15/08/2025", "31/01/2026", "3.7", "Elegant design with comfortable seating"},
        {"MB16", "user12", "SYM", "Galaxy", "Silver", "50cc", "52D-44444", "25", "Hanoi", "01/09/2025", "28/02/2026", "2.0", "Compact and easy to maneuver"},
        {"MB17", "user13", "Honda", "PCX", "Gray", "150cc", "52E-55555", "60", "HCMC", "01/08/2025", "31/12/2025", "4.8", "High-end automatic scooter"},
        {"MB18", "user14", "Yamaha", "NVX", "Orange", "155cc", "52F-66666", "65", "Hanoi", "01/08/2025", "31/03/2026", "4.5", "Sport scooter with aggressive styling"},
        {"MB19", "user15", "Suzuki", "Address", "Pink", "110cc", "52G-77777", "35", "HCMC", "15/08/2025", "30/11/2025", "3.3", "Lightweight and fuel efficient"},
        {"MB20", "user16", "Piaggio", "Vespa", "Cream", "150cc", "52H-88888", "70", "Hanoi", "01/09/2025", "31/01/2026", "4.7", "Classic Italian style icon"},
        {"MB21", "user17", "Honda", "Future", "Blue", "125cc", "52I-99999", "36", "HCMC", "01/08/2025", "28/02/2026", "3.4", "Reliable and economical choice"},
        {"MB22", "user18", "Yamaha", "Jupiter", "Red", "110cc", "52J-11111", "34", "Hanoi", "01/08/2025", "31/12/2025", "3.1", "Traditional underbone motorcycle"},
        {"MB23", "user19", "SYM", "Shark", "Black", "125cc", "52K-22222", "41", "HCMC", "15/08/2025", "31/03/2026", "3.9", "Sporty scooter with sharp design"},
        {"MB24", "user20", "Honda", "SH 350i", "White", "350cc", "52L-33333", "85", "Hanoi", "01/09/2025", "31/01/2026", "4.9", "Premium maxi-scooter"},
        {"MB25", "user21", "Yamaha", "XMAX", "Gray", "300cc", "52M-44444", "80", "HCMC", "01/08/2025", "28/02/2026", "4.6", "Adventure-ready maxi-scooter"},
        {"MB26", "user22", "Suzuki", "Burgman", "Silver", "200cc", "52N-55555", "75", "Hanoi", "01/08/2025", "31/12/2025", "4.4", "Comfortable touring scooter"},
        {"MB27", "user23", "Piaggio", "MP3", "Blue", "300cc", "52O-66666", "90", "HCMC", "15/08/2025", "31/03/2026", "4.3", "Three-wheel stability and performance"},
        {"MB28", "user24", "VinFast", "Klara A2", "Green", "50cc", "52P-77777", "30", "Hanoi", "01/09/2025", "31/01/2026", "2.7", "Affordable electric mobility"},
        {"MB29", "user25", "Honda", "Winner X", "Black", "150cc", "52Q-88888", "52", "HCMC", "01/08/2025", "28/02/2026", "4.1", "Sport bike with racing heritage"},
        {"MB30", "user26", "Yamaha", "R15", "Blue", "155cc", "52R-99999", "68", "Hanoi", "01/08/2025", "31/12/2025", "4.8", "Full-faired sport motorcycle"}
    };

    for (const auto& data : motorbikeData) {
        Motorbike mb;
        mb.motorbikeId = data[0]; mb.ownerUsername = data[1]; mb.brand = data[2]; mb.model = data[3];
        mb.color = data[4]; mb.size = data[5]; mb.plateNo = data[6]; mb.pricePerDay = stod(data[7]);
        mb.city = data[8]; mb.startDate = data[9]; mb.endDate = data[10];
        mb.minRenterRating = stod(data[11]); mb.isAvailable = true; mb.isListed = true;
        mb.rating = 0.0; // Will be updated when reviews are added
        mb.description = data[12];
        motorbikes.push_back(mb);
    }
    
    saveMotorbikes();
}



// Admin functions implementation
vector<Motorbike> BookingManager::getAllMotorbikes() {
    return motorbikes;
}

vector<Booking> BookingManager::getAllBookings() {
    return bookings;
}


vector<Booking> BookingManager::getMotorbikeBookings(const string& motorbikeId) {
    vector<Booking> motorbikeBookings;
    for (const Booking& booking : bookings) {
        if (booking.motorbikeId == motorbikeId) {
            motorbikeBookings.push_back(booking);
        }
    }
    return motorbikeBookings;
}
 bool BookingManager:: isLeap(int year){
     return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
 }
  int BookingManager:: daysInMonth(int month, int year) {
    switch (month) {
        case 1:  return 31;
        case 2:  return isLeap(year) ? 29 : 28;
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

 
 int BookingManager:: dateToDays(int d, int m, int y){
    int  days = d;
    // Add days of previous months in same year
    for (int i = 1; i < m; i++)
        days += daysInMonth(i, y);
    // Add days of previous years
    for (int i = 0; i < y; i++)
        days += isLeap(i) ? 366 : 365;
    return days;
    
 }
  int BookingManager:: calculateDay (const std::string& startData , const std::string endDate){
    int sd,sm,sy;
    int ed,em,ey;
    char sep;
    int sdate;
    int edate;
    stringstream sss(startData);
    stringstream ess(endDate);
    sss >> sd >> sep >> sm >> sep >> sy;
    ess >> ed >> sep >> em >> sep >> ey;
    sdate = dateToDays(sd,sm,sy);
    edate = dateToDays(ed,em,ey);
    
    return edate - sdate;
  }
  double BookingManager::calculatingRentalCost(const Motorbike& motorbike, const string& startDate, const string& endDate){
    int day = calculateDay(startDate,endDate);
    double rentalCost = day *motorbike.pricePerDay;
    return rentalCost;
  }
  void BookingManager::creatingBooking(const string& renter, const struct Motorbike& motorbike, 
                                  const string& startDate, const string& endDate) {
    int rentingDay= calculateDay(startDate,endDate);
    Booking booking;
    booking.bookingId = generateBookingId();
    booking.renterUsername = renter;
    booking.ownerUsername = motorbike.ownerUsername;
    booking.motorbikeId = motorbike.motorbikeId;
    booking.startDate = startDate;
    booking.endDate = endDate;
    booking.status = "Pending";
    booking.brand = motorbike.brand;
    booking.model = motorbike.model;
    booking.color = motorbike.color;
    booking.size = motorbike.size;
    booking.plateNo = motorbike.plateNo;
    booking.totalCost = motorbike.pricePerDay*rentingDay; // Simplified calculation
    
    bookings.push_back(booking);
    saveBookings();
    
}
bool BookingManager:: isReting(const std::string& username){
    vector<Booking> userBookings = getUserBookings(username);
    if (userBookings.empty()){
        cout<<"hey"<<endl;
        return false;
    }
    for (const Booking& booking : bookings) {
        if (booking.status == "Approved") {
            return true;
        }
    }
    return false;
}