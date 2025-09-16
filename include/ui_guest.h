/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Guest UI Header File
 * 
 * This file defines the UIGuest class that handles guest-specific
 * functions with limited access to motorbike information.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_GUEST_H
#define UI_GUEST_H

#include <iostream>
#include <string>

// Forward declarations
class BookingManager;
class UICore;

/**
 * UIGuest Class - Guest Interface
 * 
 * Handles guest-specific functions with limited access to system features.
 * Guests can view basic motorbike information but cannot make bookings.
 */
class UIGuest {
public:
    // Constructor
    UIGuest();
    
    // Destructor
    ~UIGuest();
    
    // Guest functions
    void viewGuestMotorbikeListings(); // Display limited motorbike listings for guests
    void searchGuestMotorbikes();      // Search motorbikes with limited information for guests
    
    // Component reference setters
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    void setUICore(UICore* uiCore) { this->uiCore = uiCore; }
    
private:
    BookingManager* bookingManager; // Reference to booking management system
    UICore* uiCore;                // Reference to core UI functions
};

#endif
