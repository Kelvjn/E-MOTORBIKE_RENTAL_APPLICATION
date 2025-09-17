#include "booking.h"
#include "auth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;


// ============================================================================
// MOTORBIKE CLASS IMPLEMENTATION
// ============================================================================

Motorbike::Motorbike(const string& motorbikeId, const string& ownerUsername,
                     const string& brand, const string& model, const string& color,
                     const string& size, const string& plateNo, double pricePerDay,
                     const string& location, bool isAvailable, double rating,
                     const string& description, const string& availableStartDate,
                     const string& availableEndDate, double minRenterRating,
                     bool isListed)
    : motorbikeId(motorbikeId), ownerUsername(ownerUsername), brand(brand), model(model),
      color(color), size(size), plateNo(plateNo), pricePerDay(pricePerDay),
      location(location), isAvailable(isAvailable), rating(rating), description(description),
      availableStartDate(availableStartDate), availableEndDate(availableEndDate),
      minRenterRating(minRenterRating), isListed(isListed) {
}

void Motorbike::displayInfo() const {
    cout << "=== MOTORBIKE DETAILS ===" << endl;
    cout << "ID: " << motorbikeId << endl;
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Color: " << color << endl;
    cout << "Size: " << size << endl;
    cout << "Plate: " << plateNo << endl;
    cout << "Price/Day: " << pricePerDay << " CP" << endl;
    cout << "Location: " << location << endl;
    cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    cout << "Rating: " << rating << "/5.0" << endl;
    cout << "Description: " << description << endl;
    cout << "Available Period: " << availableStartDate << " to " << availableEndDate << endl;
    cout << "Min Renter Rating: " << minRenterRating << endl;
    cout << "Listed: " << (isListed ? "Yes" : "No") << endl;
}

double Motorbike::calculateRentalCost(int days) const {
    return pricePerDay * days;
}

void Motorbike::setMinRenterRating(double rating) {
    if (rating >= 0 && rating <= 5) {
        this->minRenterRating = rating;
    }
}

int Motorbike::getEngineSize() const {
    // Extract engine size from size string (e.g., "150cc" -> 150)
    string sizeStr = size;
    size_t pos = sizeStr.find("cc");
    if (pos != string::npos) {
        sizeStr = sizeStr.substr(0, pos);
        try {
            return stoi(sizeStr);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

bool Motorbike::isElectric() const {
    // For this project, all motorbikes are considered electric
    return true;
}

bool Motorbike::isAvailableForDate(const string& date) const {
    // Simple date comparison - in real app, would use proper date parsing
    return date >= availableStartDate && date <= availableEndDate;
}

bool Motorbike::isAvailableForDateRange(const string& startDate, const string& endDate) const {
    return startDate >= availableStartDate && endDate <= availableEndDate;
}

bool Motorbike::meetsRenterRequirements(double renterRating) const {
    return renterRating >= minRenterRating;
}

// ============================================================================
// BOOKING CLASS IMPLEMENTATION
// ============================================================================

Booking::Booking(const string& bookingId, const string& renterUsername,
                 const string& ownerUsername, const string& motorbikeId,
                 const string& startDate, const string& endDate, const string& status,
                 double totalCost, const string& brand, const string& model,
                 const string& color, const string& size, const string& plateNo)
    : bookingId(bookingId), renterUsername(renterUsername), ownerUsername(ownerUsername),
      motorbikeId(motorbikeId), startDate(startDate), endDate(endDate), status(status),
      totalCost(totalCost), brand(brand), model(model), color(color), size(size), plateNo(plateNo) {
}

void Booking::setStatus(const string& status) {
    vector<string> validStatuses = {"Pending", "Approved", "Rejected", "Completed"};
    if (find(validStatuses.begin(), validStatuses.end(), status) != validStatuses.end()) {
        this->status = status;
    }
}

void Booking::setTotalCost(double totalCost) {
    if (totalCost >= 0) {
        this->totalCost = totalCost;
    }
}

int Booking::getDurationInDays() const {
    // Simple calculation - in real app, would use proper date parsing
    // For now, return 1 day as default
    return 1;
}

void Booking::displayInfo() const {
    cout << "=== BOOKING DETAILS ===" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Renter: " << renterUsername << endl;
    cout << "Owner: " << ownerUsername << endl;
    cout << "Motorbike: " << brand << " " << model << " (" << color << ", " << size << ")" << endl;
    cout << "Plate: " << plateNo << endl;
    cout << "Period: " << startDate << " to " << endDate << endl;
    cout << "Status: " << status << endl;
    cout << "Total Cost: " << totalCost << " CP" << endl;
}

// ============================================================================
// REVIEW CLASS IMPLEMENTATION
// ============================================================================

Review::Review(const string& reviewId, const string& motorbikeId, 
               const string& renterUsername, double rating,
               const string& comment, const string& reviewDate)
    : reviewId(reviewId), motorbikeId(motorbikeId), renterUsername(renterUsername),
      rating(rating), comment(comment), reviewDate(reviewDate) {
}

// ============================================================================
// BOOKING MANAGER CLASS IMPLEMENTATION
// ============================================================================

BookingManager::BookingManager() {
    bookingFilename = "data/bookings.txt";
    motorbikeFilename = "data/motorbikes.txt";
    reviewFilename = "data/reviews.txt";
    loadBookings();
    loadMotorbikes();
    loadReviews();
    
    // Create sample data if files are empty
    if (bookings.empty() && motorbikes.empty()) {
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
        if (line.empty() || line[0] == '#') continue;
        
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 13) {
            Booking booking(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
                           tokens[6], stod(tokens[7]), tokens[8], tokens[9], tokens[10], tokens[11], tokens[12]);
            bookings.push_back(booking);
        }
    }
    file.close();
}

void BookingManager::saveBookings() {
    ofstream file(bookingFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot save bookings to file." << endl;
        return;
    }
    
    file << "# Booking Data Format: bookingId|renterUsername|ownerUsername|motorbikeId|startDate|endDate|status|totalCost|brand|model|color|size|plateNo" << endl;
    
    for (const Booking& booking : bookings) {
        file << booking.getBookingId() << "|"
             << booking.getRenterUsername() << "|"
             << booking.getOwnerUsername() << "|"
             << booking.getMotorbikeId() << "|"
             << booking.getStartDate() << "|"
             << booking.getEndDate() << "|"
             << booking.getStatus() << "|"
             << booking.getTotalCost() << "|"
             << booking.getBrand() << "|"
             << booking.getModel() << "|"
             << booking.getColor() << "|"
             << booking.getSize() << "|"
             << booking.getPlateNo() << endl;
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
        if (line.empty() || line[0] == '#') continue;
        
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 16) {
            Motorbike motorbike(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
                               tokens[6], stod(tokens[7]), tokens[8], tokens[9] == "1", stod(tokens[10]),
                               tokens[11], tokens[12], tokens[13], stod(tokens[14]), tokens[15] == "1");
            motorbikes.push_back(motorbike);
        }
    }
    file.close();
}

void BookingManager::saveMotorbikes() {
    ofstream file(motorbikeFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot save motorbikes to file." << endl;
        return;
    }
    
    file << "# Motorbike Data Format: motorbikeId|ownerUsername|brand|model|color|size|plateNo|pricePerDay|location|isAvailable|rating|description|availableStartDate|availableEndDate|minRenterRating|isListed" << endl;
    
    for (const Motorbike& motorbike : motorbikes) {
        file << motorbike.getMotorbikeId() << "|"
             << motorbike.getOwnerUsername() << "|"
             << motorbike.getBrand() << "|"
             << motorbike.getModel() << "|"
             << motorbike.getColor() << "|"
             << motorbike.getSize() << "|"
             << motorbike.getPlateNo() << "|"
             << motorbike.getPricePerDay() << "|"
             << motorbike.getLocation() << "|"
             << (motorbike.getIsAvailable() ? "1" : "0") << "|"
             << motorbike.getRating() << "|"
             << motorbike.getDescription() << "|"
             << motorbike.getAvailableStartDate() << "|"
             << motorbike.getAvailableEndDate() << "|"
             << motorbike.getMinRenterRating() << "|"
             << (motorbike.getIsListed() ? "1" : "0") << endl;
    }
    file.close();
}

string BookingManager::generateBookingId() {
    return "BK" + to_string(bookings.size() + 1);
}

string BookingManager::generateMotorbikeId() {
    return "MB" + to_string(motorbikes.size() + 1);
}

bool BookingManager::createBooking(const string& renter, const string& motorbikeId,
                                  const string& startDate, const string& endDate, Auth& auth) {
    // Find the motorbike
    Motorbike* motorbike = getMotorbikeById(motorbikeId);
    if (!motorbike) {
        cout << "Motorbike not found." << endl;
        return false;
    }
    
    // Validate renter requirements
    double renterRating = auth.getUserRenterRating(renter);
    if (renterRating < motorbike->getMinRenterRating()) {
        cout << "Your rating (" << renterRating << ") is below the required rating (" 
             << motorbike->getMinRenterRating() << ")." << endl;
        return false;
    }
    
    double totalCost = calculateTotalCost(*motorbike, startDate, endDate);
    double renterCPs = auth.getUserCreditPoints(renter);
    if (renterCPs < totalCost) {
        cout << "Insufficient credit points. Required: " << totalCost 
             << " CP, Available: " << renterCPs << " CP." << endl;
        return false;
    }
    
    // Check for active rentals
    if (hasActiveRental(renter)) {
        cout << "You already have an active rental." << endl;
        return false;
    }
    
    // Check license requirement
    int engineSize = motorbike->getEngineSize();
    if (engineSize > 50 && !hasValidLicense(renter, auth, engineSize)) {
        cout << "Valid license required for motorbikes over 50cc." << endl;
        return false;
    }
    
    // Check date availability
    if (!motorbike->isAvailableForDateRange(startDate, endDate)) {
        cout << "Motorbike not available for the selected date range." << endl;
        return false;
    }
    
    // Check for overlapping approved bookings
    if (hasOverlappingApprovedBookings(motorbikeId, startDate, endDate)) {
        cout << "Motorbike already booked for this period." << endl;
        return false;
    }
    
    // Create booking
    string bookingId = generateBookingId();
    Booking booking(bookingId, renter, motorbike->getOwnerUsername(), motorbikeId,
                   startDate, endDate, "Pending", totalCost, motorbike->getBrand(),
                   motorbike->getModel(), motorbike->getColor(), motorbike->getSize(),
                   motorbike->getPlateNo());
    
    bookings.push_back(booking);
    saveBookings();
    
    cout << "Rental request submitted successfully!" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Total Cost: " << totalCost << " CP" << endl;
    cout << "Status: Pending approval from owner" << endl;
    
    return true;
}

bool BookingManager::approveBooking(const string& bookingId, const string& owner, Auth& auth) {
    for (Booking& booking : bookings) {
        if (booking.getBookingId() == bookingId && booking.getOwnerUsername() == owner && booking.isPending()) {
            // Check for overlapping approved bookings
            if (hasOverlappingApprovedBookings(booking.getMotorbikeId(), booking.getStartDate(), booking.getEndDate())) {
                cout << "Cannot approve: overlapping booking exists." << endl;
                return false;
            }
            
            // Deduct credit points
            if (!auth.deductCreditPoints(booking.getRenterUsername(), booking.getTotalCost())) {
                cout << "Failed to deduct credit points." << endl;
                return false;
            }
            
            // Update booking status
            booking.setStatus("Approved");
            
            // Reject overlapping requests
            rejectOverlappingRequests(booking.getMotorbikeId(), booking.getStartDate(), 
                                    booking.getEndDate(), bookingId);
            
            // Mark motorbike as unavailable
            Motorbike* motorbike = getMotorbikeById(booking.getMotorbikeId());
            if (motorbike) {
                motorbike->setIsAvailable(false);
            }
            
            saveBookings();
            saveMotorbikes();
            
            cout << "Booking approved successfully!" << endl;
            cout << "Credit points deducted: " << booking.getTotalCost() << " CP" << endl;
            
            return true;
        }
    }
    return false;
}

bool BookingManager::rejectBooking(const string& bookingId, const string& owner) {
    for (Booking& booking : bookings) {
        if (booking.getBookingId() == bookingId && booking.getOwnerUsername() == owner && booking.isPending()) {
            booking.setStatus("Rejected");
            saveBookings();
            cout << "Booking rejected." << endl;
            return true;
        }
    }
    return false;
}

vector<Booking> BookingManager::getUserBookings(const string& username) {
    vector<Booking> userBookings;
    for (const Booking& booking : bookings) {
        if (booking.getRenterUsername() == username) {
            userBookings.push_back(booking);
        }
    }
    return userBookings;
}

vector<Booking> BookingManager::getUserRentalRequests(const string& username) {
    vector<Booking> requests;
    for (const Booking& booking : bookings) {
        if (booking.getOwnerUsername() == username && booking.isPending()) {
            requests.push_back(booking);
        }
    }
    return requests;
}

vector<Booking> BookingManager::getAllBookings() {
    return bookings;
}

bool BookingManager::addMotorbike(const Motorbike& motorbike) {
    motorbikes.push_back(motorbike);
    saveMotorbikes();
    return true;
}

vector<Motorbike> BookingManager::getAvailableMotorbikes() {
    vector<Motorbike> available;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.getIsAvailable() && motorbike.getIsListed()) {
            available.push_back(motorbike);
        }
    }
    return available;
}

vector<Motorbike> BookingManager::getGuestMotorbikes() {
    vector<Motorbike> guestMotorbikes;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.getIsListed()) {
            guestMotorbikes.push_back(motorbike);
        }
    }
    return guestMotorbikes;
}

vector<Motorbike> BookingManager::getUserMotorbikes(const string& username) {
    vector<Motorbike> userMotorbikes;
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.getOwnerUsername() == username) {
            userMotorbikes.push_back(motorbike);
        }
    }
    return userMotorbikes;
}

Motorbike* BookingManager::getMotorbikeById(const string& motorbikeId) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.getMotorbikeId() == motorbikeId) {
            return &motorbike;
        }
    }
    return nullptr;
}

bool BookingManager::listMotorbike(const string& ownerUsername, const string& brand,
                                  const string& model, const string& color, const string& size,
                                  const string& plateNo, double pricePerDay, const string& location,
                                  const string& availableStartDate, const string& availableEndDate,
                                  double minRenterRating) {
    // Check if user already has a listed motorbike
    if (isMotorbikeListed(ownerUsername)) {
        cout << "You can only list one motorbike at a time." << endl;
        return false;
    }
    
    // Validate listing data
    if (!validateListingData(location, availableStartDate, availableEndDate, pricePerDay, minRenterRating)) {
        return false;
    }
    
    string motorbikeId = generateMotorbikeId();
    string description = brand + " " + model + " - " + color + " " + size;
    
    Motorbike motorbike(motorbikeId, ownerUsername, brand, model, color, size, plateNo,
                       pricePerDay, location, true, 0.0, description, availableStartDate,
                       availableEndDate, minRenterRating, true);
    
    motorbikes.push_back(motorbike);
    saveMotorbikes();
    
    cout << "Motorbike listed successfully!" << endl;
    cout << "Motorbike ID: " << motorbikeId << endl;
    
    return true;
}

bool BookingManager::unlistMotorbike(const string& ownerUsername) {
    for (Motorbike& motorbike : motorbikes) {
        if (motorbike.getOwnerUsername() == ownerUsername && motorbike.getIsListed()) {
            if (isMotorbikeBooked(ownerUsername)) {
                cout << "Cannot unlist: motorbike has active bookings." << endl;
                return false;
            }
            
            motorbike.setIsListed(false);
            saveMotorbikes();
            cout << "Motorbike unlisted successfully." << endl;
            return true;
        }
    }
    cout << "No listed motorbike found for this user." << endl;
    return false;
}

bool BookingManager::isMotorbikeListed(const string& ownerUsername) {
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.getOwnerUsername() == ownerUsername && motorbike.getIsListed()) {
            return true;
        }
    }
    return false;
}

bool BookingManager::isMotorbikeBooked(const string& ownerUsername) {
    for (const Booking& booking : bookings) {
        if (booking.getOwnerUsername() == ownerUsername && booking.isApproved()) {
            return true;
        }
    }
    return false;
}

bool BookingManager::validateListingData(const string& location, const string& startDate,
                                        const string& endDate, double pricePerDay, double minRating) {
    if (location != "HCMC" && location != "Hanoi") {
        cout << "Invalid location. Only HCMC and Hanoi are supported." << endl;
        return false;
    }
    
    if (pricePerDay <= 0) {
        cout << "Price per day must be positive." << endl;
        return false;
    }
    
    if (minRating < 0 || minRating > 5) {
        cout << "Minimum renter rating must be between 0 and 5." << endl;
        return false;
    }
    
    // Parse dates for proper comparison (DD/MM/YYYY format)
    if (!isValidDate(startDate) || !isValidDate(endDate)) {
        cout << "Invalid date format. Please use DD/MM/YYYY format." << endl;
        return false;
    }
    
    if (!isDateBefore(startDate, endDate)) {
        cout << "Start date must be before end date." << endl;
        return false;
    }
    
    return true;
}

bool BookingManager::isValidDate(const string& date) {
    // Check if date is in DD/MM/YYYY format
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    // Extract day, month, year
    string dayStr = date.substr(0, 2);
    string monthStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    try {
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        
        // Basic validation
        if (day < 1 || day > 31) return false;
        if (month < 1 || month > 12) return false;
        if (year < 2020 || year > 2030) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

bool BookingManager::isDateBefore(const string& date1, const string& date2) {
    // Parse dates (DD/MM/YYYY format)
    int day1 = stoi(date1.substr(0, 2));
    int month1 = stoi(date1.substr(3, 2));
    int year1 = stoi(date1.substr(6, 4));
    
    int day2 = stoi(date2.substr(0, 2));
    int month2 = stoi(date2.substr(3, 2));
    int year2 = stoi(date2.substr(6, 4));
    
    // Compare dates
    if (year1 < year2) return true;
    if (year1 > year2) return false;
    
    if (month1 < month2) return true;
    if (month1 > month2) return false;
    
    return day1 < day2;
}

double BookingManager::getUserRenterRating(const string& username) {
    (void)username; // Suppress unused parameter warning
    // This would typically come from the Auth system
    return 3.0; // Default rating
}

double BookingManager::getUserMotorbikeRating(const string& username) {
    double totalRating = 0.0;
    int count = 0;
    
    for (const Motorbike& motorbike : motorbikes) {
        if (motorbike.getOwnerUsername() == username) {
            totalRating += motorbike.getRating();
            count++;
        }
    }
    
    return count > 0 ? totalRating / count : 0.0;
}

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

vector<Motorbike> BookingManager::searchMotorbikesByDateRange(const string& startDate, const string& endDate,
                                                             const string& city, const string& username, Auth& auth) {
    vector<Motorbike> results;
    for (const Motorbike& motorbike : motorbikes) {
        if (meetsDateRangeSearchCriteria(motorbike, startDate, endDate, city, username, auth)) {
            results.push_back(motorbike);
        }
    }
    return results;
}

bool BookingManager::meetsSearchCriteria(const Motorbike& motorbike, const string& searchDate,
                                        const string& city, const string& username, Auth& auth) {
    // Check if motorbike is listed and available
    if (!motorbike.getIsListed() || !motorbike.getIsAvailable()) {
        return false;
    }
    
    // Check location
    if (motorbike.getLocation() != city) {
        return false;
    }
    
    // Check date availability
    if (!motorbike.isAvailableForDate(searchDate)) {
        return false;
    }
    
    // Check renter rating requirement
    double renterRating = auth.getUserRenterRating(username);
    if (renterRating < motorbike.getMinRenterRating()) {
        return false;
    }
    
    // Check credit points
    double totalCost = calculateTotalCost(motorbike, searchDate, searchDate);
    double userCPs = auth.getUserCreditPoints(username);
    if (userCPs < totalCost) {
        return false;
    }
    
    // Note: License requirement is checked during booking request, not during search
    // This allows users to see all available motorbikes but prevents booking without valid license
    
    return true;
}

bool BookingManager::meetsDateRangeSearchCriteria(const Motorbike& motorbike, const string& startDate,
                                                 const string& endDate, const string& city,
                                                 const string& username, Auth& auth) {
    // Check if motorbike is listed and available
    if (!motorbike.getIsListed() || !motorbike.getIsAvailable()) {
        return false;
    }
    
    // Check location
    if (motorbike.getLocation() != city) {
        return false;
    }
    
    // Check if the entire date range is within motorbike's available period
    if (!motorbike.isAvailableForDateRange(startDate, endDate)) {
        return false;
    }
    
    // Check for overlapping approved bookings
    if (hasOverlappingApprovedBookings(motorbike.getMotorbikeId(), startDate, endDate)) {
        return false;
    }
    
    // Check renter rating requirement
    double renterRating = auth.getUserRenterRating(username);
    if (renterRating < motorbike.getMinRenterRating()) {
        return false;
    }
    
    // Check credit points
    double totalCost = calculateTotalCost(motorbike, startDate, endDate);
    double userCPs = auth.getUserCreditPoints(username);
    if (userCPs < totalCost) {
        return false;
    }
    
    // Note: License requirement is checked during booking request, not during search
    // This allows users to see all available motorbikes but prevents booking without valid license
    
    return true;
}

bool BookingManager::isDateInRange(const string& searchDate, const string& startDate, const string& endDate) {
    return searchDate >= startDate && searchDate <= endDate;
}

double BookingManager::calculateTotalCost(const Motorbike& motorbike, const string& startDate, const string& endDate) {
    (void)startDate; // Suppress unused parameter warning
    (void)endDate;   // Suppress unused parameter warning
    // Simple calculation - in real app, would calculate actual days
    int days = 1; // Default to 1 day
    return motorbike.calculateRentalCost(days);
}

int BookingManager::getEngineSize(const string& size) {
    string sizeStr = size;
    size_t pos = sizeStr.find("cc");
    if (pos != string::npos) {
        sizeStr = sizeStr.substr(0, pos);
        try {
            return stoi(sizeStr);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

bool BookingManager::hasValidLicense(const string& username, Auth& auth, int engineSize) {
    if (engineSize <= 50) {
        return true; // No license required for 50cc and below
    }
    
    // Get current user and check license validity
    User* currentUser = auth.getCurrentUser();
    if (!currentUser || currentUser->getUsername() != username) {
        // Try to find user in auth system
        vector<User> allUsers = auth.getAllUsers();
        for (const User& user : allUsers) {
            if (user.getUsername() == username) {
                return user.hasValidLicense();
            }
        }
        return false;
    }
    
    return currentUser->hasValidLicense();
}

vector<string> BookingManager::getMotorbikeReviews(const string& motorbikeId) {
    vector<string> motorbikeComments;
    
    for (const Review& review : reviews) {
        if (review.getMotorbikeId() == motorbikeId) {
            string reviewText = "Rating: " + to_string(review.getRating()) + "/5.0 - " + 
                               review.getComment() + " (by " + review.getRenterUsername() + 
                               " on " + review.getReviewDate() + ")";
            motorbikeComments.push_back(reviewText);
        }
    }
    
    return motorbikeComments;
}

double BookingManager::getAverageRating(const string& motorbikeId) {
    double totalRating = 0.0;
    int count = 0;
    
    for (const Review& review : reviews) {
        if (review.getMotorbikeId() == motorbikeId) {
            totalRating += review.getRating();
            count++;
        }
    }
    
    if (count > 0) {
        return totalRating / count;
    }
    
    // Fallback to motorbike's stored rating if no reviews
    Motorbike* motorbike = getMotorbikeById(motorbikeId);
    return motorbike ? motorbike->getRating() : 0.0;
}

bool BookingManager::hasActiveRental(const string& username) {
    for (const Booking& booking : bookings) {
        if (booking.getRenterUsername() == username && booking.isApproved()) {
            return true;
        }
    }
    return false;
}

bool BookingManager::hasOverlappingApprovedBookings(const string& motorbikeId, const string& startDate, const string& endDate) {
    for (const Booking& booking : bookings) {
        if (booking.getMotorbikeId() == motorbikeId && booking.isApproved()) {
            // Simple overlap check - in real app, would use proper date comparison
            if (booking.getStartDate() <= endDate && booking.getEndDate() >= startDate) {
                return true;
            }
        }
    }
    return false;
}

void BookingManager::rejectOverlappingRequests(const string& motorbikeId, const string& startDate,
                                              const string& endDate, const string& approvedBookingId) {
    for (Booking& booking : bookings) {
        if (booking.getMotorbikeId() == motorbikeId && booking.getBookingId() != approvedBookingId && booking.isPending()) {
            // Simple overlap check
            if (booking.getStartDate() <= endDate && booking.getEndDate() >= startDate) {
                booking.setStatus("Rejected");
            }
        }
    }
}

bool BookingManager::completeRental(const string& bookingId, const string& renterUsername) {
    for (Booking& booking : bookings) {
        if (booking.getBookingId() == bookingId && booking.getRenterUsername() == renterUsername && booking.isApproved()) {
            booking.setStatus("Completed");
            
            // Make motorbike available again
            Motorbike* motorbike = getMotorbikeById(booking.getMotorbikeId());
            if (motorbike) {
                motorbike->setIsAvailable(true);
            }
            
            saveBookings();
            saveMotorbikes();
            
            cout << "Rental completed successfully!" << endl;
            return true;
        }
    }
    return false;
}

bool BookingManager::rateMotorbike(const string& bookingId, const string& renterUsername, double rating, const string& comment) {
    for (Booking& booking : bookings) {
        if (booking.getBookingId() == bookingId && booking.getRenterUsername() == renterUsername && booking.isCompleted()) {
            // Add review using the new function
            if (!addReview(booking.getMotorbikeId(), renterUsername, rating, comment)) {
                return false;
            }
            
            // Update motorbike rating based on all reviews
            double newAverageRating = getAverageRating(booking.getMotorbikeId());
            Motorbike* motorbike = getMotorbikeById(booking.getMotorbikeId());
            if (motorbike) {
                motorbike->setRating(newAverageRating);
                saveMotorbikes();
            }
            
            cout << "Motorbike rated successfully!" << endl;
            cout << "Rating: " << rating << "/5.0" << endl;
            cout << "Comment: " << comment << endl;
            cout << "New average rating: " << newAverageRating << "/5.0" << endl;
            
            return true;
        }
    }
    return false;
}

bool BookingManager::rateRenter(const string& bookingId, const string& ownerUsername, double rating, const string& comment) {
    for (Booking& booking : bookings) {
        if (booking.getBookingId() == bookingId && booking.getOwnerUsername() == ownerUsername && booking.isCompleted()) {
            cout << "Renter rated successfully!" << endl;
            cout << "Rating: " << rating << "/5.0" << endl;
            cout << "Comment: " << comment << endl;
            
            // In a real app, this would update the renter's rating in the Auth system
            return true;
        }
    }
    return false;
}

string BookingManager::generateReviewId() {
    return "R" + to_string(reviews.size() + 1);
}

bool BookingManager::addReview(const string& motorbikeId, const string& renterUsername, double rating, const string& comment) {
    if (rating < 1.0 || rating > 5.0) {
        cout << "Rating must be between 1.0 and 5.0." << endl;
        return false;
    }
    
    string reviewId = generateReviewId();
    string reviewDate = "25/09/2025"; // Current date - in real app would use actual date
    
    Review newReview(reviewId, motorbikeId, renterUsername, rating, comment, reviewDate);
    reviews.push_back(newReview);
    saveReviews();
    
    cout << "Review added successfully!" << endl;
    return true;
}

void BookingManager::createSampleData() {
    createSampleMotorbikes();
}

void BookingManager::createSampleMotorbikes() {
    // Create sample motorbikes
    vector<Motorbike> sampleMotorbikes = {
        Motorbike("MB1", "iAmMember1", "VinFast", "Klara S", "Red", "50cc", "59X3-216.86", 25, "HCMC", true, 4.5, "VinFast Klara S - Red 50cc", "01/08/2025", "31/12/2025", 3.5, true),
        Motorbike("MB2", "iAmMember2", "Honda", "Vision", "Blue", "110cc", "51A-12345", 30, "HCMC", true, 4.2, "Honda Vision - Blue 110cc", "01/08/2025", "30/11/2025", 3, true),
        Motorbike("MB3", "iAmMember3", "Yamaha", "Exciter", "Black", "150cc", "51B-67890", 45, "HCMC", true, 4.8, "Yamaha Exciter - Black 150cc", "01/08/2025", "31/12/2025", 4, true),
        Motorbike("MB4", "iAmMember4", "Suzuki", "Raider", "White", "125cc", "51C-11111", 35, "HCMC", true, 4, "Suzuki Raider - White 125cc", "01/08/2025", "30/09/2025", 3.5, true),
        Motorbike("MB5", "iAmMember5", "Piaggio", "Liberty", "Green", "125cc", "51D-22222", 40, "HCMC", true, 4.3, "Piaggio Liberty - Green 125cc", "01/08/2025", "31/10/2025", 3.8, true)
    };
    
    for (const Motorbike& motorbike : sampleMotorbikes) {
        motorbikes.push_back(motorbike);
    }
    
    saveMotorbikes();
}

void BookingManager::loadReviews() {
    ifstream file(reviewFilename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            Review review(tokens[0], tokens[1], tokens[2], stod(tokens[3]), tokens[4], tokens[5]);
            reviews.push_back(review);
        }
    }
    file.close();
}

void BookingManager::saveReviews() {
    ofstream file(reviewFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot save reviews to file." << endl;
        return;
    }
    
    file << "# Review Data Format: reviewId|motorbikeId|renterUsername|rating|comment|reviewDate" << endl;
    
    for (const Review& review : reviews) {
        file << review.getReviewId() << "|"
             << review.getMotorbikeId() << "|"
             << review.getRenterUsername() << "|"
             << review.getRating() << "|"
             << review.getComment() << "|"
             << review.getReviewDate() << endl;
    }
    file.close();
}