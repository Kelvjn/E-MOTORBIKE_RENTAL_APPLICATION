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
    std::string city; // HCMC or Hanoi only
    std::string startDate; // Available rental period start
    std::string endDate;   // Available rental period end
    double minRenterRating; // Minimum required renter rating
    bool isAvailable;
    bool isListed;     // Track if motorbike is currently listed
    double rating;
    std::string description;
};

struct UserInfo {
    std::string city;
    std::string searchDate;
    double userRating;
    double userCreditPoints;
    bool hasValidLicense;
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
    bool isDateInRange(const std::string& searchDate, const std::string& startDate, const std::string& endDate);
    int getEngineSize(const std::string& size);
    double calculateRentalCost(const Motorbike& motorbike, const std::string& searchDate);
    
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
    
    // Motorbike management
    bool addMotorbike(const Motorbike& motorbike);
    bool listMotorbike(const std::string& ownerUsername, const std::string& brand, const std::string& model,
                      const std::string& color, const std::string& size, const std::string& plateNo,
                      double pricePerDay, const std::string& city, const std::string& startDate,
                      const std::string& endDate, double minRenterRating, const std::string& description);
    bool unlistMotorbike(const std::string& ownerUsername);
    bool hasUserListedMotorbike(const std::string& username);
    bool validateCity(const std::string& city);
    bool validateDateFormat(const std::string& date);
    bool isDateValid(const std::string& startDate, const std::string& endDate);
    std::vector<Motorbike> getAvailableMotorbikes();
    std::vector<Motorbike> getUserMotorbikes(const std::string& username);
    Motorbike* getMotorbikeById(const std::string& motorbikeId);
    Motorbike* getUserMotorbike(const std::string& username);
    
    // Search and filtering functions
    std::vector<Motorbike> searchMotorbikes(const UserInfo& criteria);
    std::vector<Motorbike> filterMotorbikes(const std::vector<Motorbike>& motorbikes, const UserInfo& criteria);
    
   
    
    // Statistics
    double getUserRenterRating(const std::string& username);
    double getUserMotorbikeRating(const std::string& username);
    
    // Admin functions
    std::vector<Motorbike> getAllMotorbikes();
    std::vector<Booking> getAllBookings();
    std::vector<Booking> getMotorbikeBookings(const std::string& motorbikeId);
    
    // Sample data
    void createSampleData();
    void createSampleMotorbikes();

    bool isLeap(int year);
    int daysInMonth(int month, int year) ;
    int dateToDays(int d, int m, int y);
    int calculateDay(const std::string& startData , const std::string endDate);
    double calculatingRentalCost(const Motorbike& motorbike, const std::string& startDate,
                                 const std::string& endDate);
    bool isReting(const std::string& username);
    void creatingBooking(const std::string& renter, const struct Motorbike& motorbike, 
                                  const std::string& startDate, const std::string& endDate);
};

#endif