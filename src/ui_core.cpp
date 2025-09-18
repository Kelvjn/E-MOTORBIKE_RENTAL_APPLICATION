/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Core UI Implementation
 * 
 * This file implements the UICore class methods for handling basic user interface
 * operations, menu display, and navigation between different UI modules.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_core.h"
#include "ui_profile.h"
#include "ui_motorbike.h"
#include "ui_booking.h"
#include "ui_admin.h"
#include "ui_guest.h"
#include "ui_dashboard.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * Constructor
 */
UICore::UICore() : auth(nullptr), bookingManager(nullptr), 
                   uiProfile(nullptr), uiMotorbike(nullptr), uiBooking(nullptr),
                   uiAdmin(nullptr), uiGuest(nullptr), uiDashboard(nullptr) {
}

/**
 * Destructor
 */
UICore::~UICore() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays the application welcome screen with project information
 * and group member details.
 */
void UICore::showWelcomeScreen() {
    clearScreen();
    cout << "EEET2482/EEET2653/COSC2082/COSC2721 GROUP PROJECT\n";
    cout << "Semester 2 2025\n";
    cout << "E-MOTORBIKE RENTAL APPLICATION\n";
    cout << "Instructor: Dr Tri Huynh\n";
    cout << "Group: 5\n";
    cout << "S3992133, Lu Duc Thinh\n";
    cout << "S3928379, Jang Soohyuk\n";
    cout << "S3975144, Pham Tuan Hai\n";
    cout << "S4027077, Vu The Quyen\n\n";
}

/**
 * Displays the main menu and handles user selection with input validation.
 * 
 * @return User's menu choice (1-5)
 */
int UICore::showMainMenu() {
    int choice;
    cout << "Use the app as 1. Guest  2. Member  3. Admin  4. Register  5. Exit\n";
    cout << "Enter your choice: ";
    
    // Input validation loop
    while (!(cin >> choice) || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1-5: ";
    }
    
    return choice;
}

/**
 * Displays the guest menu with limited functionality options.
 * Guests can view motorbike listings and search, but cannot make bookings.
 */
void UICore::showGuestMenu() {
    if (!uiGuest) {
        cout << "Error: Guest UI module not available.\n";
        pauseScreen();
        return;
    }

    int choice;
    do {
        clearScreen();
        cout << "=== GUEST MENU ===\n";
        cout << "1. View motorbike listings\n";
        cout << "2. Search motorbikes\n";
        cout << "3. Back to main menu\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                uiGuest->viewGuestMotorbikeListings();
                break;
            case 2:
                uiGuest->searchGuestMotorbikes();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 3);
}

/**
 * Displays the member menu with full functionality options.
 * Members can manage their motorbikes, make bookings, and access profile features.
 */
void UICore::showMemberMenu() {
    int choice;
    do {
        clearScreen();
        cout << "=== MEMBER MENU ===\n";
        cout << "1. Activity Dashboard\n";
        cout << "2. List my motorbike for rent\n";
        cout << "3. Browse available motorbikes\n";
        cout << "4. My bookings\n";
        cout << "5. Rental requests (for my motorbikes)\n";
        cout << "6. Complete approved rentals\n";
        cout << "7. My profile\n";
        cout << "8. Rate completed rentals (as renter)\n";
        cout << "9. Rate completed rentals (as owner)\n";
        cout << "10. Identity verification\n";
        cout << "11. Logout\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (uiDashboard) uiDashboard->showActivityDashboard();
                break;
            case 2:
                if (uiMotorbike) uiMotorbike->showMotorbikeListingMenu();
                break;
            case 3:
                if (uiMotorbike) uiMotorbike->showMotorbikeSearchMenu();
                break;
            case 4:
                if (uiBooking) uiBooking->viewUserBookings();
                break;
            case 5:
                if (uiBooking) uiBooking->viewRentalRequests();
                break;
            case 6:
                if (uiBooking) uiBooking->viewApprovedRentals();
                break;
            case 7:
                if (uiProfile) uiProfile->showProfileMenu();
                break;
            case 8:
                if (uiBooking) uiBooking->viewCompletedRentals();
                break;
            case 9:
                if (uiBooking) uiBooking->viewCompletedRentalsForOwner();
                break;
            case 10:
                if (uiDashboard) uiDashboard->showVerificationMenu();
                break;
            case 11:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 11);
}

/**
 * Displays the admin menu with administrative functions.
 * Admins can view all member profiles, motorbike listings, and system statistics.
 */
void UICore::showAdminMenu() {
    if (!uiAdmin) {
        cout << "Error: Admin UI module not available.\n";
        pauseScreen();
        return;
    }

    int choice;
    do {
        clearScreen();
        cout << "=== ADMIN MENU ===\n";
        cout << "1. View all member profiles\n";
        cout << "2. View all motorbike listings\n";
        cout << "3. System statistics\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                uiAdmin->viewAllMemberProfiles();
                break;
            case 2:
                uiAdmin->viewAllMotorbikeListings();
                break;
            case 3:
                uiAdmin->showSystemStatistics();
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 4);
}

/**
 * Clears the console screen for better user experience.
 * Uses platform-specific commands for Windows and Unix-like systems.
 */
void UICore::clearScreen() {
    #ifdef _WIN32
        system("cls");    // Windows command
    #else
        system("clear");  // Unix/Linux command
    #endif
}

/**
 * Pauses the screen and waits for user input to continue.
 * Clears input buffer and waits for Enter key press.
 */
void UICore::pauseScreen() {
    cout << "\nPress Enter to continue...";
    // If there's an immediate leftover newline from previous formatted input (>>) consume it
    if (cin.peek() == '\n') {
        cin.ignore(1, '\n');
    }
    // Now wait for exactly one Enter from the user
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
