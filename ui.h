/**
 * E-MOTORBIKE RENTAL APPLICATION
 * User Interface Header File
 * 
 * This file defines the UI class that handles all user interface operations
 * including menu display, user input handling, and screen management.
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

// Forward declarations
class Auth;
class BookingManager;
struct Booking;

/**
 * UI Class - User Interface Manager
 * 
 * Handles all user interface operations including menu display,
 * user input validation, screen management, and profile operations.
 * Provides a clean separation between user interaction and business logic.
 */
class UI {
public:
    // Core UI functions
    void showWelcomeScreen();      // Display application welcome screen
    int showMainMenu();            // Display and handle main menu selection
    void showGuestMenu();          // Display guest-specific menu options
    void showMemberMenu();         // Display member-specific menu options
    void showAdminMenu();          // Display admin-specific menu options
    void clearScreen();            // Clear the console screen
    void pauseScreen();            // Pause for user input
    
    // Profile management functions
    void showProfileMenu();        // Display profile management menu
    void updateProfileInformation(); // Handle profile information updates
    void changeUserPassword();     // Handle password change operations
    void topUpCreditPoints();      // Handle credit point top-up operations
    void viewBookingHistory();     // Display user booking history
    
    // Electric motorbike listing functions
    void showMotorbikeListingMenu(); // Display motorbike listing menu
    void listMyMotorbike();        // Handle motorbike listing process
    void unlistMyMotorbike();      // Handle motorbike unlisting process
    void viewMyMotorbikeListing(); // Display current motorbike listing
    
    // Motorbike search and filtering functions
    void showMotorbikeSearchMenu(); // Display motorbike search menu
    void searchMotorbikes();       // Handle motorbike search process
    void displayMotorbikeDetails(const struct Motorbike& motorbike); // Display motorbike details
    void displayMotorbikeReviews(const std::string& motorbikeId); // Display motorbike reviews
    
    // Rental request and management functions
    void makeRentalRequest(const struct Motorbike& motorbike); // Submit rental request
    void viewRentalRequests(); // View rental requests for owner
    void manageRentalRequest(const struct Booking& request); // Approve/reject requests
    void viewCompletedRentals(); // View completed rentals for rating
    void rateMotorbike(const struct Booking& booking); // Rate motorbike after rental
    void viewApprovedRentals(); // View approved rentals for completion
    void completeRental(const struct Booking& booking); // Complete rental
    
    // Dashboard and advanced features
    void showActivityDashboard(); // Display personalized activity dashboard
    void showVerificationMenu(); // Display identity verification menu
    
    // Guest functions
    void viewGuestMotorbikeListings(); // Display limited motorbike listings for guests
    void searchGuestMotorbikes(); // Search motorbikes with limited information for guests
    
    // Admin functions
    void viewAllMemberProfiles(); // Display all member profiles
    void viewAllMotorbikeListings(); // Display all motorbike listings
    void showSystemStatistics(); // Display system statistics
    
    // Component reference setters
    void setAuth(Auth* auth) { this->auth = auth; }
    void setBookingManager(BookingManager* bookingManager) { this->bookingManager = bookingManager; }
    
private:
    Auth* auth;                    // Reference to authentication system
    BookingManager* bookingManager; // Reference to booking management system
};

#endif
