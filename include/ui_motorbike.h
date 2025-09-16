/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Motorbike UI Header File
 * 
 * This file defines the UIMotorbike class that handles motorbike management
 * operations including listing, searching, and viewing motorbike details.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_MOTORBIKE_H
#define UI_MOTORBIKE_H

#include <iostream>
#include <string>
#include <vector>

// Forward declarations
class Auth;
class BookingManager;
class UICore;
class UIBooking;
struct Motorbike;

/**
 * UIMotorbike Class - Motorbike Management Interface
 * 
 * Handles all motorbike-related operations including listing motorbikes for rent,
 * searching available motorbikes, and viewing detailed motorbike information.
 */
class UIMotorbike {
public:
    // Constructor
    UIMotorbike();
    
    // Destructor
    ~UIMotorbike();
    
    // Motorbike listing functions
    void showMotorbikeListingMenu(); // Display motorbike listing menu
    void listMyMotorbike();        // Handle motorbike listing process
    void unlistMyMotorbike();      // Handle motorbike unlisting process
    void viewMyMotorbikeListing(); // Display current motorbike listing
    
    // Motorbike search and filtering functions
    void showMotorbikeSearchMenu(); // Display motorbike search menu
    void searchMotorbikes();       // Handle motorbike search process
    void displayMotorbikeDetails(const struct Motorbike& motorbike); // Display motorbike details
    void displayMotorbikeReviews(const std::string& motorbikeId); // Display motorbike reviews
    
    // Component reference setters
    void setAuth(Auth* auth) { this->auth = auth; }
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    void setUICore(UICore* uiCore) { this->uiCore = uiCore; }
    void setUIBooking(UIBooking* uiBooking) { this->uiBooking = uiBooking; }
    
private:
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
    UICore* uiCore;                // Reference to core UI functions
    UIBooking* uiBooking;          // Reference to booking UI functions
    
    // Helper function
    void makeRentalRequest(const struct Motorbike& motorbike); // Submit rental request
};

#endif
