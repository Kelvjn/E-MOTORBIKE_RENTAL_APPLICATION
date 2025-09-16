/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Profile UI Header File
 * 
 * This file defines the UIProfile class that handles profile management
 * operations including viewing, updating profile information, and credit points.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <iostream>
#include <string>

using namespace std;

// Forward declarations
class Auth;
class BookingManager;
class UICore;

/**
 * UIProfile Class - Profile Management Interface
 * 
 * Handles all profile-related operations including viewing profile information,
 * updating personal details, password management, and credit point operations.
 */
class UIProfile {
public:
    // Constructor
    UIProfile();
    
    // Destructor
    ~UIProfile();
    
    // Profile management functions
    void showProfileMenu();        // Display profile management menu
    void updateProfileInformation(); // Handle profile information updates
    void changeUserPassword();     // Handle password change operations
    void topUpCreditPoints();      // Handle credit point top-up operations
    void viewBookingHistory();     // Display user booking history
    
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
