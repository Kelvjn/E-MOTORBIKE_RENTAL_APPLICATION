/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Booking UI Header File
 * 
 * This file defines the UIBooking class that handles booking management
 * operations including rental requests, approvals, and completions.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_BOOKING_H
#define UI_BOOKING_H

#include <iostream>
#include <string>

// Forward declarations
class Auth;
class BookingManager;
class UICore;
struct Booking;

/**
 * UIBooking Class - Booking Management Interface
 * 
 * Handles all booking-related operations including rental requests,
 * approvals, rejections, completions, and rating systems.
 */
class UIBooking {
public:
    // Constructor
    UIBooking();
    
    // Destructor
    ~UIBooking();
    
    // Rental request and management functions
    void viewRentalRequests();     // View rental requests for owner
    void manageRentalRequest(const struct Booking& request); // Approve/reject requests
    void viewCompletedRentals();   // View completed rentals for rating
    void rateMotorbike(const struct Booking& booking); // Rate motorbike after rental
    void viewApprovedRentals();    // View approved rentals for completion
    void completeRental(const struct Booking& booking); // Complete rental
    
    // Component reference setters
    void setAuth(Auth* auth) { this->auth = auth; }
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    void setUICore(UICore* uiCore) { this->uiCore = uiCore; }
    
private:
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
    UICore* uiCore;                // Reference to core UI functions
};

#endif
