#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// Motorbike class - simplified without inheritance
class Motorbike {
private:
    string motorbikeId;
    string ownerUsername;
    string brand;
    string model;
    string color;
    string size;
    string plateNo;
    double pricePerDay;
    string location;
    bool isAvailable;
    double rating;
    string description;
    string availableStartDate;  // Available rental period start date
    string availableEndDate;    // Available rental period end date
    double minRenterRating;     // Minimum required renter rating
    bool isListed;              // Whether the motorbike is currently listed
    
public:
    // Constructor
    Motorbike(const string& motorbikeId = "", const string& ownerUsername = "",
              const string& brand = "", const string& model = "", 
              const string& color = "", const string& size = "",
              const string& plateNo = "", double pricePerDay = 0.0,
              const string& location = "", bool isAvailable = true,
              double rating = 0.0, const string& description = "",
              const string& availableStartDate = "", const string& availableEndDate = "",
              double minRenterRating = 0.0, bool isListed = false);
    
    // Destructor
    ~Motorbike() = default;
    
    // Core functions
    void displayInfo() const;
    double calculateRentalCost(int days) const;
    string getVehicleType() const { return "Motorbike"; }
    
    // Getters
    string getMotorbikeId() const { return motorbikeId; }
    string getOwnerUsername() const { return ownerUsername; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    string getSize() const { return size; }
    string getPlateNo() const { return plateNo; }
    double getPricePerDay() const { return pricePerDay; }
    string getLocation() const { return location; }
    bool getIsAvailable() const { return isAvailable; }
    double getRating() const { return rating; }
    string getDescription() const { return description; }
    string getAvailableStartDate() const { return availableStartDate; }
    string getAvailableEndDate() const { return availableEndDate; }
    double getMinRenterRating() const { return minRenterRating; }
    bool getIsListed() const { return isListed; }
    
    // Setters with validation
    void setMotorbikeId(const string& motorbikeId) { this->motorbikeId = motorbikeId; }
    void setOwnerUsername(const string& ownerUsername) { this->ownerUsername = ownerUsername; }
    void setBrand(const string& brand) { this->brand = brand; }
    void setModel(const string& model) { this->model = model; }
    void setColor(const string& color) { this->color = color; }
    void setSize(const string& size) { this->size = size; }
    void setPlateNo(const string& plateNo) { this->plateNo = plateNo; }
    void setPricePerDay(double pricePerDay) { this->pricePerDay = pricePerDay; }
    void setLocation(const string& location) { this->location = location; }
    void setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
    void setRating(double rating) { this->rating = rating; }
    void setDescription(const string& description) { this->description = description; }
    void setAvailableStartDate(const string& date) { availableStartDate = date; }
    void setAvailableEndDate(const string& date) { availableEndDate = date; }
    void setMinRenterRating(double rating);
    void setIsListed(bool isListed) { this->isListed = isListed; }
    
    // Business logic methods
    bool isAvailableForDate(const string& date) const;
    bool isAvailableForDateRange(const string& startDate, const string& endDate) const;
    bool meetsRenterRequirements(double renterRating) const;
    int getEngineSize() const;
    bool isElectric() const;
};

// Booking class with proper encapsulation
class Booking {
private:
    string bookingId;
    string renterUsername;
    string ownerUsername;
    string motorbikeId;
    string startDate;
    string endDate;
    string status; // "Pending", "Approved", "Rejected", "Completed"
    double totalCost;
    string brand;
    string model;
    string color;
    string size;
    string plateNo;
    
public:
    // Constructor
    Booking(const string& bookingId = "", const string& renterUsername = "",
            const string& ownerUsername = "", const string& motorbikeId = "",
            const string& startDate = "", const string& endDate = "",
            const string& status = "Pending", double totalCost = 0.0,
            const string& brand = "", const string& model = "",
            const string& color = "", const string& size = "",
            const string& plateNo = "");
    
    // Destructor
    ~Booking() = default;
    
    // Getters
    string getBookingId() const { return bookingId; }
    string getRenterUsername() const { return renterUsername; }
    string getOwnerUsername() const { return ownerUsername; }
    string getMotorbikeId() const { return motorbikeId; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    string getStatus() const { return status; }
    double getTotalCost() const { return totalCost; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    string getSize() const { return size; }
    string getPlateNo() const { return plateNo; }
    
    // Setters with validation
    void setBookingId(const string& bookingId) { this->bookingId = bookingId; }
    void setRenterUsername(const string& renterUsername) { this->renterUsername = renterUsername; }
    void setOwnerUsername(const string& ownerUsername) { this->ownerUsername = ownerUsername; }
    void setMotorbikeId(const string& motorbikeId) { this->motorbikeId = motorbikeId; }
    void setStartDate(const string& startDate) { this->startDate = startDate; }
    void setEndDate(const string& endDate) { this->endDate = endDate; }
    void setStatus(const string& status);
    void setTotalCost(double totalCost);
    void setBrand(const string& brand) { this->brand = brand; }
    void setModel(const string& model) { this->model = model; }
    void setColor(const string& color) { this->color = color; }
    void setSize(const string& size) { this->size = size; }
    void setPlateNo(const string& plateNo) { this->plateNo = plateNo; }
    
    // Business logic methods
    bool isPending() const { return status == "Pending"; }
    bool isApproved() const { return status == "Approved"; }
    bool isRejected() const { return status == "Rejected"; }
    bool isCompleted() const { return status == "Completed"; }
    int getDurationInDays() const;
    void displayInfo() const;
};

// Review class for motorbike reviews
class Review {
private:
    string reviewId;
    string motorbikeId;
    string renterUsername;
    double rating;
    string comment;
    string reviewDate;

public:
    // Constructor
    Review(const string& reviewId = "", const string& motorbikeId = "",
           const string& renterUsername = "", double rating = 0.0,
           const string& comment = "", const string& reviewDate = "");
    
    // Getters
    string getReviewId() const { return reviewId; }
    string getMotorbikeId() const { return motorbikeId; }
    string getRenterUsername() const { return renterUsername; }
    double getRating() const { return rating; }
    string getComment() const { return comment; }
    string getReviewDate() const { return reviewDate; }
};

class BookingManager {
private:
    vector<Booking> bookings;
    vector<Motorbike> motorbikes;
    vector<Review> reviews;
    string bookingFilename;
    string motorbikeFilename;
    string reviewFilename;
    
    void loadBookings();
    void saveBookings();
    void loadMotorbikes();
    void saveMotorbikes();
    void loadReviews();
    void saveReviews();
    string generateBookingId();
    string generateMotorbikeId();
    
public:
    // Constructor
    BookingManager();
    
    // Destructor
    ~BookingManager();
    
    // Booking management
    bool createBooking(const string& renter, const string& motorbikeId, 
                      const string& startDate, const string& endDate, class Auth& auth);
    bool approveBooking(const string& bookingId, const string& owner, class Auth& auth);
    bool rejectBooking(const string& bookingId, const string& owner);
    vector<Booking> getUserBookings(const string& username);
    vector<Booking> getUserRentalRequests(const string& username);
    vector<Booking> getAllBookings(); // Get all bookings for admin view
    
    // Motorbike management
    bool addMotorbike(const Motorbike& motorbike);
    vector<Motorbike> getAvailableMotorbikes();
    vector<Motorbike> getGuestMotorbikes(); // Get motorbikes for guest view (limited info)
    vector<Motorbike> getUserMotorbikes(const string& username);
    Motorbike* getMotorbikeById(const string& motorbikeId);
    
    // Electric motorbike listing management
    bool listMotorbike(const string& ownerUsername, const string& brand, 
                      const string& model, const string& color, 
                      const string& size, const string& plateNo,
                      double pricePerDay, const string& location,
                      const string& availableStartDate, const string& availableEndDate,
                      double minRenterRating);
    bool unlistMotorbike(const string& ownerUsername);
    bool isMotorbikeListed(const string& ownerUsername);
    bool isMotorbikeBooked(const string& ownerUsername);
    bool validateListingData(const string& location, const string& startDate, 
                           const string& endDate, double pricePerDay, double minRating);
    bool isValidDate(const string& date);
    bool isDateBefore(const string& date1, const string& date2);
    
    // Statistics
    double getUserRenterRating(const string& username);
    double getUserMotorbikeRating(const string& username);
    
    // Motorbike search and filtering methods
    vector<Motorbike> searchMotorbikes(const string& searchDate, const string& city, 
                                           const string& username, class Auth& auth);
    vector<Motorbike> searchMotorbikesByDateRange(const string& startDate, const string& endDate, 
                                                      const string& city, const string& username, class Auth& auth);
    bool meetsSearchCriteria(const Motorbike& motorbike, const string& searchDate, 
                            const string& city, const string& username, class Auth& auth);
    bool meetsDateRangeSearchCriteria(const Motorbike& motorbike, const string& startDate, const string& endDate,
                                     const string& city, const string& username, class Auth& auth);
    bool isDateInRange(const string& searchDate, const string& startDate, const string& endDate);
    double calculateTotalCost(const Motorbike& motorbike, const string& startDate, const string& endDate);
    int getEngineSize(const string& size);
    bool hasValidLicense(const string& username, class Auth& auth, int engineSize);
    vector<string> getMotorbikeReviews(const string& motorbikeId);
    double getAverageRating(const string& motorbikeId);
    
    // Rental request validation and management
    bool hasActiveRental(const string& username);
    bool hasOverlappingApprovedBookings(const string& motorbikeId, const string& startDate, const string& endDate);
    void rejectOverlappingRequests(const string& motorbikeId, const string& startDate, const string& endDate, const string& approvedBookingId);
    bool completeRental(const string& bookingId, const string& renterUsername);
    bool rateMotorbike(const string& bookingId, const string& renterUsername, double rating, const string& comment);
    bool rateRenter(const string& bookingId, const string& ownerUsername, double rating, const string& comment);
    
    // Review management
    string generateReviewId();
    bool addReview(const string& motorbikeId, const string& renterUsername, double rating, const string& comment);
    
    // Sample data
    void createSampleData();
    void createSampleMotorbikes();
};

#endif