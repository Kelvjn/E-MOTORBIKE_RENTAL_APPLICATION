/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Core UI Header File
 * 
 * This file defines the UICore class that handles basic UI operations
 * including menu display, screen management, and core navigation.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_CORE_H
#define UI_CORE_H

#include <iostream>
#include <string>

// Forward declarations
class Auth;
class BookingManager;
class UIProfile;
class UIMotorbike;
class UIBooking;
class UIAdmin;
class UIGuest;
class UIDashboard;

/**
 * UICore Class - Core User Interface Manager
 * 
 * Handles basic UI operations including menu display, screen management,
 * and navigation between different UI modules.
 */
class UICore {
public:
    // Constructor
    UICore();
    
    // Destructor
    ~UICore();
    
    // Core UI functions
    void showWelcomeScreen();      // Display application welcome screen
    int showMainMenu();            // Display and handle main menu selection
    void showGuestMenu();          // Display guest-specific menu options
    void showMemberMenu();         // Display member-specific menu options
    void showAdminMenu();          // Display admin-specific menu options
    void clearScreen();            // Clear the console screen
    void pauseScreen();            // Pause for user input
    
    // Component reference setters
    void setAuth(Auth* auth) { this->auth = auth; }
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    
    // UI Module setters
    void setUIProfile(UIProfile* uiProfile) { this->uiProfile = uiProfile; }
    void setUIMotorbike(UIMotorbike* uiMotorbike) { this->uiMotorbike = uiMotorbike; }
    void setUIBooking(UIBooking* uiBooking) { this->uiBooking = uiBooking; }
    void setUIAdmin(UIAdmin* uiAdmin) { this->uiAdmin = uiAdmin; }
    void setUIGuest(UIGuest* uiGuest) { this->uiGuest = uiGuest; }
    void setUIDashboard(UIDashboard* uiDashboard) { this->uiDashboard = uiDashboard; }
    
private:
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
    
    // UI Module references
    UIProfile* uiProfile;
    UIMotorbike* uiMotorbike;
    UIBooking* uiBooking;
    UIAdmin* uiAdmin;
    UIGuest* uiGuest;
    UIDashboard* uiDashboard;
};

#endif
