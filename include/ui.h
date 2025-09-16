/**
 * E-MOTORBIKE RENTAL APPLICATION
 * User Interface Manager Header File
 * 
 * This file defines the UI class that manages all user interface modules
 * and coordinates between different UI components.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class Auth;
class BookingManager;
class UICore;
class UIProfile;
class UIMotorbike;
class UIBooking;
class UIAdmin;
class UIGuest;
class UIDashboard;

/**
 * UI Class - User Interface Manager
 * 
 * Main UI manager that coordinates all UI modules and provides
 * a unified interface for the application. Acts as a facade
 * for all UI operations while delegating to specialized modules.
 */
class UI {
public:
    // Constructor and Destructor
    UI();
    ~UI();
    
    // Main UI entry points - delegates to UICore
    void showWelcomeScreen();      // Display application welcome screen
    int showMainMenu();            // Display and handle main menu selection
    void showGuestMenu();          // Display guest-specific menu options
    void showMemberMenu();         // Display member-specific menu options
    void showAdminMenu();          // Display admin-specific menu options
    
    // Component reference setters
    void setAuth(Auth* auth);
    void setBookingManager(BookingManager* bookingManager);
    
private:
    // Core system references
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
    
    // UI Module instances
    UICore* uiCore;
    UIProfile* uiProfile;
    UIMotorbike* uiMotorbike;
    UIBooking* uiBooking;
    UIAdmin* uiAdmin;
    UIGuest* uiGuest;
    UIDashboard* uiDashboard;
    
    // Helper method to initialize all UI modules
    void initializeUIModules();
    void setupModuleReferences();
};

#endif
