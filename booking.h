#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

struct Booking {
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
};

struct Motorbike {
    std::string motorbikeId;
    std::string ownerUsername;
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
    // New fields for electric motorbike listings
    std::string availableStartDate;  // Available rental period start date
    std::string availableEndDate;    // Available rental period end date
    double minRenterRating;          // Minimum required renter rating
    bool isListed;                   // Whether the motorbike is currently listed
};

class BookingManager {
private:
    std::vector<Booking> bookings;
    std::vector<Motorbike> motorbikes;
    std::string bookingFilename;
    std::string motorbikeFilename;
    
    void loadBookings();
    void saveBookings();
    void loadMotorbikes();
    void saveMotorbikes();
    std::string generateBookingId();
    std::string generateMotorbikeId();
    
public:
    BookingManager();
    ~BookingManager();
    
    // Booking management
    bool createBooking(const std::string& renter, const std::string& motorbikeId, 
                      const std::string& startDate, const std::string& endDate);
    bool approveBooking(const std::string& bookingId, const std::string& owner);
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
    bool meetsSearchCriteria(const Motorbike& motorbike, const std::string& searchDate, 
                            const std::string& city, const std::string& username, class Auth& auth);
    bool isDateInRange(const std::string& searchDate, const std::string& startDate, const std::string& endDate);
    double calculateTotalCost(const Motorbike& motorbike, const std::string& startDate, const std::string& endDate);
    int getEngineSize(const std::string& size);
    bool hasValidLicense(const std::string& username, class Auth& auth, int engineSize);
    std::vector<std::string> getMotorbikeReviews(const std::string& motorbikeId);
    double getAverageRating(const std::string& motorbikeId);
    
    // Sample data
    void createSampleData();
    void createSampleMotorbikes();
};

#endif
