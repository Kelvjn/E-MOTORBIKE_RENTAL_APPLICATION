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
    std::vector<Motorbike> getAvailableMotorbikes();
    std::vector<Motorbike> getUserMotorbikes(const std::string& username);
    Motorbike* getMotorbikeById(const std::string& motorbikeId);
    
    // Statistics
    double getUserRenterRating(const std::string& username);
    double getUserMotorbikeRating(const std::string& username);
    
    // Sample data
    void createSampleData();
};

#endif
