/**
 * E-MOTORBIKE RENTAL APPLICATION
 * User Interface Implementation
 * 
 * This file implements the UI class methods for handling user interface
 * operations, menu display, input validation, and profile management.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * Displays the application welcome screen with project information
 * and group member details.
 */
void UI::showWelcomeScreen() {
    clearScreen();
    cout << "EEET2482/EEET2653/COSC2082/COSC2721 GROUP PROJECT\n";
    cout << "Semester 2 2025\n";
    cout << "E-MOTORBIKE RENTAL APPLICATION\n";
    cout << "Instructor: Dr Ling Huo Chong, Dr Ushik Shrestha, Dr Tri Huynh\n";
    cout << "Group: Group 5.\n";
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
int UI::showMainMenu() {
    int choice;
    cout << "Use the app as 1.Guest  2.Member  3.Admin  4.Register  5.Exit\n";
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
void UI::showGuestMenu() {
    clearScreen();
    cout << "=== GUEST MENU ===\n";
    cout << "1.View motorbike listings\n";
    cout << "2.Search motorbikes\n";
    cout << "3.Back to main menu\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Viewing motorbike listings...\n";
            pauseScreen();
            break;
        case 2:
            cout << "Searching motorbikes...\n";
            pauseScreen();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
    }
}

/**
 * Displays the member menu with full functionality options.
 * Members can manage their motorbikes, make bookings, and access profile features.
 */
void UI::showMemberMenu() {
    clearScreen();
    cout << "=== MEMBER MENU ===\n";
    cout << "1.List my motorbike for rent\n";
    cout << "2.Browse available motorbikes\n";
    cout << "3.My bookings\n";
    cout << "4.Top up credit points\n";
    cout << "5.My profile\n";
    cout << "6.Logout\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Listing motorbike for rent...\n";
            pauseScreen();
            break;
        case 2:
            cout << "Browsing available motorbikes...\n";
            pauseScreen();
            break;
        case 3:
            cout << "Viewing my bookings...\n";
            pauseScreen();
            break;
        case 4:
            cout << "Topping up credit points...\n";
            pauseScreen();
            break;
        case 5:
            showProfileMenu();
            break;
        case 6:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
    }
}

/**
 * Displays the admin menu with administrative functions.
 * Admins can view all member profiles, motorbike listings, and system statistics.
 */
void UI::showAdminMenu() {
    clearScreen();
    cout << "=== ADMIN MENU ===\n";
    cout << "1.View all member profiles\n";
    cout << "2.View all motorbike listings\n";
    cout << "3.System statistics\n";
    cout << "4.Logout\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Viewing all member profiles...\n";
            pauseScreen();
            break;
        case 2:
            cout << "Viewing all motorbike listings...\n";
            pauseScreen();
            break;
        case 3:
            cout << "Viewing system statistics...\n";
            pauseScreen();
            break;
        case 4:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
    }
}



/**
 * Displays the profile management menu with comprehensive profile operations.
 * Provides access to view, update, and manage user profile information.
 */
void UI::showProfileMenu() {
    while (true) {
        clearScreen();
        cout << "=== PROFILE MANAGEMENT ===\n";
        cout << "1.View Profile Information\n";
        cout << "2.Update Profile Information\n";
        cout << "3.Change Password\n";
        cout << "4.Top Up Credit Points\n";
        cout << "5.View Booking History\n";
        cout << "6.Back to Member Menu\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (auth && auth->getCurrentUser()) {
                    auth->displayProfile(auth->getCurrentUser()->username, bookingManager);
                }
                pauseScreen();
                break;
            case 2:
                updateProfileInformation();
                break;
            case 3:
                changeUserPassword();
                break;
            case 4:
                topUpCreditPoints();
                break;
            case 5:
                viewBookingHistory();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    }
}

/**
 * Handles profile information updates with input validation.
 * Allows users to update their full name, email, and phone number.
 * Username cannot be changed for security reasons.
 */
void UI::updateProfileInformation() {
    if (!auth || !auth->getCurrentUser()) {
        cout << "Error: No user logged in.\n";
        pauseScreen();
        return;
    }
    
    User* currentUser = auth->getCurrentUser();
    string fullName, email, phoneNumber;
    
    clearScreen();
    cout << "=== UPDATE PROFILE INFORMATION ===\n";
    cout << "Note: Username cannot be changed.\n\n";
    
    // Display current values for reference
    cout << "Current full name: " << currentUser->fullName << "\n";
    cout << "Current email: " << currentUser->email << "\n";
    cout << "Current phone number: " << currentUser->phoneNumber << "\n\n";
    
    // Get new values with option to keep current
    cout << "Enter new full name (or press Enter to keep current): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, fullName);
    if (fullName.empty()) {
        fullName = currentUser->fullName;
    }
    
    cout << "Enter new email (or press Enter to keep current): ";
    getline(cin, email);
    if (email.empty()) {
        email = currentUser->email;
    } else if (!auth->validateEmail(email)) {
        cout << "Invalid email format. Profile not updated.\n";
        pauseScreen();
        return;
    }
    
    cout << "Enter new phone number (or press Enter to keep current): ";
    getline(cin, phoneNumber);
    if (phoneNumber.empty()) {
        phoneNumber = currentUser->phoneNumber;
    } else if (!auth->validatePhoneNumber(phoneNumber)) {
        cout << "Invalid phone number format. Profile not updated.\n";
        pauseScreen();
        return;
    }
    
    // Update profile in database and memory
    if (auth->updateProfile(currentUser->username, fullName, email, phoneNumber)) {
        cout << "\nProfile updated successfully!\n";
        // Update current user object to reflect changes immediately
        currentUser->fullName = fullName;
        currentUser->email = email;
        currentUser->phoneNumber = phoneNumber;
    } else {
        cout << "\nFailed to update profile.\n";
    }
    
    pauseScreen();
}

/**
 * Handles password change operations with security validation.
 * Requires current password verification and new password confirmation.
 * Enforces strong password policy through the auth system.
 */
void UI::changeUserPassword() {
    if (!auth || !auth->getCurrentUser()) {
        cout << "Error: No user logged in.\n";
        pauseScreen();
        return;
    }
    
    string oldPassword, newPassword, confirmPassword;
    
    clearScreen();
    cout << "=== CHANGE PASSWORD ===\n";
    
    // Get current password for verification
    cout << "Enter current password: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    oldPassword = auth->hidePassword();
    cout << endl;
    
    // Get new password
    cout << "Enter new password: ";
    newPassword = auth->hidePassword();
    cout << endl;
    
    // Confirm new password
    cout << "Confirm new password: ";
    confirmPassword = auth->hidePassword();
    cout << endl;
    
    // Validate password confirmation
    if (newPassword != confirmPassword) {
        cout << "New passwords do not match.\n";
        pauseScreen();
        return;
    }
    
    // Process password change
    if (auth->changePassword(auth->getCurrentUser()->username, oldPassword, newPassword)) {
        cout << "Password changed successfully!\n";
        // Update current user object to reflect changes immediately
        auth->getCurrentUser()->password = newPassword;
    } else {
        cout << "Failed to change password. Please check your current password.\n";
    }
    
    pauseScreen();
}

/**
 * Handles credit point top-up operations with password authentication.
 * Allows users to add credit points to their account balance.
 * Rate: $1 = 1 Credit Point (CP)
 */
void UI::topUpCreditPoints() {
    if (!auth || !auth->getCurrentUser()) {
        cout << "Error: No user logged in.\n";
        pauseScreen();
        return;
    }
    
    string password;
    double amount;
    
    clearScreen();
    cout << "=== TOP UP CREDIT POINTS ===\n";
    cout << "Current balance: " << auth->getCurrentUser()->creditPoints << " CPs\n";
    cout << "Rate: $1 = 1 CP\n\n";
    
    // Get top-up amount
    cout << "Enter amount to top up ($): ";
    cin >> amount;
    
    // Validate amount
    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive value.\n";
        pauseScreen();
        return;
    }
    
    // Require password authentication for security
    cout << "Enter your password to confirm: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    password = auth->hidePassword();
    cout << endl;
    
    // Verify password before processing
    if (password != auth->getCurrentUser()->password) {
        cout << "Incorrect password. Top-up cancelled.\n";
        pauseScreen();
        return;
    }
    
    // Process top-up
    if (auth->topUpCreditPoints(auth->getCurrentUser()->username, amount)) {
        cout << "Successfully topped up " << amount << " CPs!\n";
        cout << "New balance: " << (auth->getCurrentUser()->creditPoints + amount) << " CPs\n";
        // Update current user object to reflect changes immediately
        auth->getCurrentUser()->creditPoints += amount;
    } else {
        cout << "Failed to top up credit points.\n";
    }
    
    pauseScreen();
}

/**
 * Displays comprehensive booking history and rating statistics.
 * Shows both rental bookings (as renter) and rental requests (as owner).
 * Includes rating information for both renter and motorbike ratings.
 */
void UI::viewBookingHistory() {
    if (!auth || !auth->getCurrentUser()) {
        cout << "Error: No user logged in.\n";
        pauseScreen();
        return;
    }
    
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== BOOKING HISTORY ===\n";
    
    string username = auth->getCurrentUser()->username;
    
    // Display user's bookings as a renter
    vector<Booking> userBookings = bookingManager->getUserBookings(username);
    
    if (userBookings.empty()) {
        cout << "No booking history found.\n";
    } else {
        cout << "Your Rental Bookings:\n";
        cout << "----------------------\n";
        cout << "Booking ID | Period | Motorbike | Status | Cost\n";
        for (const Booking& booking : userBookings) {
            cout << booking.bookingId << " | "
                 << booking.startDate << "-" << booking.endDate << " | "
                 << booking.brand << " " << booking.model << " | "
                 << booking.status << " | $"
                 << booking.totalCost << "\n";
        }
    }
    
    // Display user's rental requests (as motorbike owner)
    vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
    
    if (!rentalRequests.empty()) {
        cout << "\nRental Requests (Your Motorbikes):\n";
        cout << "----------------------------------\n";
        cout << "Booking ID | Renter | Period | Motorbike | Status\n";
        for (const Booking& request : rentalRequests) {
            cout << request.bookingId << " | "
                 << request.renterUsername << " | "
                 << request.startDate << "-" << request.endDate << " | "
                 << request.brand << " " << request.model << " | "
                 << request.status << "\n";
        }
    }
    
    // Display comprehensive rating statistics
    cout << "\nRating Statistics:\n";
    cout << "------------------\n";
    cout << "Your Renter Rating: " << auth->getCurrentUser()->rating << "/5.0\n";
    cout << "Your Motorbike Rating: " << bookingManager->getUserMotorbikeRating(username) << "/5.0\n";
    
    pauseScreen();
}

/**
 * Clears the console screen for better user experience.
 * Uses platform-specific commands for Windows and Unix-like systems.
 */
void UI::clearScreen() {
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
void UI::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
