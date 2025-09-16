#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

// Base class for all vehicles
class Vehicle {
protected:
    std::string brand;
    std::string model;
    std::string color;
    std::string size;
    std::string plateNo;
    double pricePerDay;
    std::string location;
    bool isAvailable;
    double rating;
    std::string description;
    
public:
    // Constructor
    Vehicle(const std::string& brand = "", const std::string& model = "", 
            const std::string& color = "", const std::string& size = "",
            const std::string& plateNo = "", double pricePerDay = 0.0,
            const std::string& location = "", bool isAvailable = true,
            double rating = 0.0, const std::string& description = "");
    
    // Virtual destructor for proper inheritance
    virtual ~Vehicle() = default;
    
    // Pure virtual functions - must be implemented by derived classes
    virtual void displayInfo() const = 0;
    virtual double calculateRentalCost(int days) const = 0;
    virtual std::string getVehicleType() const = 0;
    
    // Getters
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    std::string getColor() const { return color; }
    std::string getSize() const { return size; }
    std::string getPlateNo() const { return plateNo; }
    double getPricePerDay() const { return pricePerDay; }
    std::string getLocation() const { return location; }
    bool getIsAvailable() const { return isAvailable; }
    double getRating() const { return rating; }
    std::string getDescription() const { return description; }
    
    // Setters with validation
    void setBrand(const std::string& brand) { this->brand = brand; }
    void setModel(const std::string& model) { this->model = model; }
    void setColor(const std::string& color) { this->color = color; }
    void setSize(const std::string& size) { this->size = size; }
    void setPlateNo(const std::string& plateNo) { this->plateNo = plateNo; }
    void setPricePerDay(double pricePerDay);
    void setLocation(const std::string& location) { this->location = location; }
    void setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }
    void setRating(double rating);
    void setDescription(const std::string& description) { this->description = description; }
    
    // Utility methods
    int getEngineSize() const;
    bool isElectric() const;
};

// Motorbike class inherits from Vehicle
class Motorbike : public Vehicle {
private:
    std::string motorbikeId;
    std::string ownerUsername;
    // New fields for electric motorbike listings
    std::string availableStartDate;  // Available rental period start date
    std::string availableEndDate;    // Available rental period end date
    double minRenterRating;          // Minimum required renter rating
    bool isListed;                   // Whether the motorbike is currently listed
    
public:
    // Constructor
    Motorbike(const std::string& motorbikeId = "", const std::string& ownerUsername = "",
              const std::string& brand = "", const std::string& model = "", 
              const std::string& color = "", const std::string& size = "",
              const std::string& plateNo = "", double pricePerDay = 0.0,
              const std::string& location = "", bool isAvailable = true,
              double rating = 0.0, const std::string& description = "",
              const std::string& availableStartDate = "", const std::string& availableEndDate = "",
              double minRenterRating = 0.0, bool isListed = false);
    
    // Destructor
    ~Motorbike() override = default;
    
    // Override pure virtual functions from Vehicle
    void displayInfo() const override;
    double calculateRentalCost(int days) const override;
    std::string getVehicleType() const override { return "Motorbike"; }
    
    // Getters
    std::string getMotorbikeId() const { return motorbikeId; }
    std::string getOwnerUsername() const { return ownerUsername; }
    std::string getAvailableStartDate() const { return availableStartDate; }
    std::string getAvailableEndDate() const { return availableEndDate; }
    double getMinRenterRating() const { return minRenterRating; }
    bool getIsListed() const { return isListed; }
    
    // Setters with validation
    void setMotorbikeId(const std::string& motorbikeId) { this->motorbikeId = motorbikeId; }
    void setOwnerUsername(const std::string& ownerUsername) { this->ownerUsername = ownerUsername; }
    void setAvailableStartDate(const std::string& date) { availableStartDate = date; }
    void setAvailableEndDate(const std::string& date) { availableEndDate = date; }
    void setMinRenterRating(double rating);
    void setIsListed(bool isListed) { this->isListed = isListed; }
    
    // Business logic methods
    bool isAvailableForDate(const std::string& date) const;
    bool isAvailableForDateRange(const std::string& startDate, const std::string& endDate) const;
    bool meetsRenterRequirements(double renterRating) const;
};

// Booking class with proper encapsulation
class Booking {
private:
    std::string bookingId;
    std::string renterUsername;
    std::string ownerUsername;
    std::string motorbikeId;
    std::string startDate;
    std::string endDate;
    std::string status; // "Pending", "Approved", "Rejected", "Completed"
    double totalCost;
    std::string brand;
    std::string model;
    std::string color;
    std::string size;
    std::string plateNo;
    
public:
    // Constructor
    Booking(const std::string& bookingId = "", const std::string& renterUsername = "",
            const std::string& ownerUsername = "", const std::string& motorbikeId = "",
            const std::string& startDate = "", const std::string& endDate = "",
            const std::string& status = "Pending", double totalCost = 0.0,
            const std::string& brand = "", const std::string& model = "",
            const std::string& color = "", const std::string& size = "",
            const std::string& plateNo = "");
    
    // Destructor
    ~Booking() = default;
    
    // Getters
    std::string getBookingId() const { return bookingId; }
    std::string getRenterUsername() const { return renterUsername; }
    std::string getOwnerUsername() const { return ownerUsername; }
    std::string getMotorbikeId() const { return motorbikeId; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    std::string getStatus() const { return status; }
    double getTotalCost() const { return totalCost; }
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    std::string getColor() const { return color; }
    std::string getSize() const { return size; }
    std::string getPlateNo() const { return plateNo; }
    
    // Setters with validation
    void setBookingId(const std::string& bookingId) { this->bookingId = bookingId; }
    void setRenterUsername(const std::string& renterUsername) { this->renterUsername = renterUsername; }
    void setOwnerUsername(const std::string& ownerUsername) { this->ownerUsername = ownerUsername; }
    void setMotorbikeId(const std::string& motorbikeId) { this->motorbikeId = motorbikeId; }
    void setStartDate(const std::string& startDate) { this->startDate = startDate; }
    void setEndDate(const std::string& endDate) { this->endDate = endDate; }
    void setStatus(const std::string& status);
    void setTotalCost(double totalCost);
    void setBrand(const std::string& brand) { this->brand = brand; }
    void setModel(const std::string& model) { this->model = model; }
    void setColor(const std::string& color) { this->color = color; }
    void setSize(const std::string& size) { this->size = size; }
    void setPlateNo(const std::string& plateNo) { this->plateNo = plateNo; }
    
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
    std::string reviewId;
    std::string motorbikeId;
    std::string renterUsername;
    double rating;
    std::string comment;
    std::string reviewDate;

public:
    // Constructor
    Review(const std::string& reviewId = "", const std::string& motorbikeId = "",
           const std::string& renterUsername = "", double rating = 0.0,
           const std::string& comment = "", const std::string& reviewDate = "");
    
    // Getters
    std::string getReviewId() const { return reviewId; }
    std::string getMotorbikeId() const { return motorbikeId; }
    std::string getRenterUsername() const { return renterUsername; }
    double getRating() const { return rating; }
    std::string getComment() const { return comment; }
    std::string getReviewDate() const { return reviewDate; }
};

class BookingManager {
private:
    std::vector<Booking> bookings;
    std::vector<Motorbike> motorbikes;
    std::vector<Review> reviews;
    std::string bookingFilename;
    std::string motorbikeFilename;
    std::string reviewFilename;
    
    void loadBookings();
    void saveBookings();
    void loadMotorbikes();
    void saveMotorbikes();
    void loadReviews();
    void saveReviews();
    std::string generateBookingId();
    std::string generateMotorbikeId();
    
public:
    // Constructor
    BookingManager();
    
    // Destructor
    ~BookingManager();
    
    // Booking management
    bool createBooking(const std::string& renter, const std::string& motorbikeId, 
                      const std::string& startDate, const std::string& endDate, class Auth& auth);
    bool approveBooking(const std::string& bookingId, const std::string& owner, class Auth& auth);
    bool rejectBooking(const std::string& bookingId, const std::string& owner);
    std::vector<Booking> getUserBookings(const std::string& username);
    std::vector<Booking> getUserRentalRequests(const std::string& username);
    std::vector<Booking> getAllBookings(); // Get all bookings for admin view
    
    // Motorbike management
    bool addMotorbike(const Motorbike& motorbike);
    std::vector<Motorbike> getAvailableMotorbikes();
    std::vector<Motorbike> getGuestMotorbikes(); // Get motorbikes for guest view (limited info)
    std::vector<Motorbike> getUserMotorbikes(const std::string& username);
    Motorbike* getMotorbikeById(const std::string& motorbikeId);
    
    // Electric motorbike listing management
    bool listMotorbike(const std::string& ownerUsername, const std::string& brand, 
                      const std::string& model, const std::string& color, 
                      const std::string& size, const std::string& plateNo,
                      double pricePerDay, const std::string& location,
                      const std::string& availableStartDate, const std::string& availableEndDate,
                      double minRenterRating);
    bool unlistMotorbike(const std::string& ownerUsername);
    bool isMotorbikeListed(const std::string& ownerUsername);
    bool isMotorbikeBooked(const std::string& ownerUsername);
    bool validateListingData(const std::string& location, const std::string& startDate, 
                           const std::string& endDate, double pricePerDay, double minRating);
    
    // Statistics
    double getUserRenterRating(const std::string& username);
    double getUserMotorbikeRating(const std::string& username);
    
    // Motorbike search and filtering methods
    std::vector<Motorbike> searchMotorbikes(const std::string& searchDate, const std::string& city, 
                                           const std::string& username, class Auth& auth);
    std::vector<Motorbike> searchMotorbikesByDateRange(const std::string& startDate, const std::string& endDate, 
                                                      const std::string& city, const std::string& username, class Auth& auth);
    bool meetsSearchCriteria(const Motorbike& motorbike, const std::string& searchDate, 
                            const std::string& city, const std::string& username, class Auth& auth);
    bool meetsDateRangeSearchCriteria(const Motorbike& motorbike, const std::string& startDate, const std::string& endDate,
                                     const std::string& city, const std::string& username, class Auth& auth);
    bool isDateInRange(const std::string& searchDate, const std::string& startDate, const std::string& endDate);
    double calculateTotalCost(const Motorbike& motorbike, const std::string& startDate, const std::string& endDate);
    int getEngineSize(const std::string& size);
    bool hasValidLicense(const std::string& username, class Auth& auth, int engineSize);
    std::vector<std::string> getMotorbikeReviews(const std::string& motorbikeId);
    double getAverageRating(const std::string& motorbikeId);
    
    // Rental request validation and management
    bool hasActiveRental(const std::string& username);
    bool hasOverlappingApprovedBookings(const std::string& motorbikeId, const std::string& startDate, const std::string& endDate);
    void rejectOverlappingRequests(const std::string& motorbikeId, const std::string& startDate, const std::string& endDate, const std::string& approvedBookingId);
    bool completeRental(const std::string& bookingId, const std::string& renterUsername);
    bool rateMotorbike(const std::string& bookingId, const std::string& renterUsername, double rating, const std::string& comment);
    bool rateRenter(const std::string& bookingId, const std::string& ownerUsername, double rating, const std::string& comment);
    
    // Sample data
    void createSampleData();
    void createSampleMotorbikes();
};

#endif