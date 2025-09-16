/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Dashboard UI Header File
 * 
 * This file defines the UIDashboard class that handles dashboard
 * and special features including activity overview and verification.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <iostream>
#include <string>

using namespace std;

// Forward declarations
class Auth;
class BookingManager;
class UICore;
class UIMotorbike;
class UIBooking;

/**
 * UIDashboard Class - Dashboard and Special Features Interface
 * 
 * Handles dashboard functionality and special features including
 * activity overview and identity verification system.
 */
class UIDashboard {
public:
    // Constructor
    UIDashboard();
    
    // Destructor
    ~UIDashboard();
    
    // Dashboard and special features
    void showActivityDashboard();  // Display personalized activity dashboard
    void showVerificationMenu();   // Display identity verification menu
    
    // Component reference setters
    void setAuth(Auth* auth) { this->auth = auth; }
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    void setUICore(UICore* uiCore) { this->uiCore = uiCore; }
    void setUIMotorbike(UIMotorbike* uiMotorbike) { this->uiMotorbike = uiMotorbike; }
    void setUIBooking(UIBooking* uiBooking) { this->uiBooking = uiBooking; }
    
private:
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
    UICore* uiCore;                // Reference to core UI functions
    UIMotorbike* uiMotorbike;      // Reference to motorbike UI functions
    UIBooking* uiBooking;          // Reference to booking UI functions
};

#endif
