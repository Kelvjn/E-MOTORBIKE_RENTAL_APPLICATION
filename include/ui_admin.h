/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Admin UI Header File
 * 
 * This file defines the UIAdmin class that handles administrative
 * functions including viewing all profiles and system statistics.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <iostream>
#include <string>

// Forward declarations
class Auth;
class BookingManager;
class UICore;

/**
 * UIAdmin Class - Administrative Interface
 * 
 * Handles all administrative functions including viewing all member profiles,
 * motorbike listings, and comprehensive system statistics.
 */
class UIAdmin {
public:
    // Constructor
    UIAdmin();
    
    // Destructor
    ~UIAdmin();
    
    // Admin functions
    void viewAllMemberProfiles();    // Display all member profiles
    void viewAllMotorbikeListings(); // Display all motorbike listings
    void showSystemStatistics();     // Display system statistics
    
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
