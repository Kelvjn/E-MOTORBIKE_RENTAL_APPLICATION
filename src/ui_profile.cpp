/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Profile UI Implementation
 * 
 * This file implements the UIProfile class methods for handling profile
 * management operations including viewing, updating, and credit management.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_profile.h"
#include "ui_core.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * Constructor
 */
UIProfile::UIProfile() : auth(nullptr), bookingManager(nullptr), uiCore(nullptr) {
}

/**
 * Destructor
 */
UIProfile::~UIProfile() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays the profile management menu with comprehensive profile operations.
 * Provides access to view, update, and manage user profile information.
 */
void UIProfile::showProfileMenu() {
    if (!auth || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }

    while (true) {
        uiCore->clearScreen();
        cout << "=== PROFILE MANAGEMENT ===\n";
        cout << "1. View Profile Information\n";
        cout << "2. Update Profile Information\n";
        cout << "3. Change Password\n";
        cout << "4. Top Up Credit Points\n";
        cout << "5. View Booking History\n";
        cout << "6. Back to Member Menu\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (auth->getCurrentUser()) {
                    auth->displayProfile(auth->getCurrentUser()->getUsername(), bookingManager);
                }
                uiCore->pauseScreen();
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
                uiCore->pauseScreen();
        }
    }
}

/**
 * Handles profile information updates with input validation.
 * Allows users to update their full name, email, and phone number.
 * Username cannot be changed for security reasons.
 */
void UIProfile::updateProfileInformation() {
    if (!auth || !auth->getCurrentUser() || !uiCore) {
        cout << "Error: No user logged in or required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    User* currentUser = auth->getCurrentUser();
    string fullName, email, phoneNumber;
    
    uiCore->clearScreen();
    cout << "=== UPDATE PROFILE INFORMATION ===\n";
    cout << "Note: Username cannot be changed.\n\n";
    
    // Display current values for reference
    cout << "Current full name: " << currentUser->getFullName() << "\n";
    cout << "Current email: " << currentUser->getEmail() << "\n";
    cout << "Current phone number: " << currentUser->getPhoneNumber() << "\n\n";
    
    // Get new values with option to keep current
    cout << "Enter new full name (or press Enter to keep current): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, fullName);
    if (fullName.empty()) {
        fullName = currentUser->getFullName();
    }
    
    cout << "Enter new email (or press Enter to keep current): ";
    getline(cin, email);
    if (email.empty()) {
        email = currentUser->getEmail();
    } else if (!auth->validateEmail(email)) {
        cout << "Invalid email format. Profile not updated.\n";
        uiCore->pauseScreen();
        return;
    }
    
    cout << "Enter new phone number (or press Enter to keep current): ";
    getline(cin, phoneNumber);
    if (phoneNumber.empty()) {
        phoneNumber = currentUser->getPhoneNumber();
    } else if (!auth->validatePhoneNumber(phoneNumber)) {
        cout << "Invalid phone number format. Profile not updated.\n";
        uiCore->pauseScreen();
        return;
    }
    
    // Update profile in database and memory
    if (auth->updateProfile(currentUser->getUsername(), fullName, email, phoneNumber)) {
        cout << "\nProfile updated successfully!\n";
        // Update current user object to reflect changes immediately
        currentUser->setFullName(fullName);
        currentUser->setEmail(email);
        currentUser->setPhoneNumber(phoneNumber);
    } else {
        cout << "\nFailed to update profile.\n";
    }
    
    uiCore->pauseScreen();
}

/**
 * Handles password change operations with security validation.
 * Requires current password verification and new password confirmation.
 * Enforces strong password policy through the auth system.
 */
void UIProfile::changeUserPassword() {
    if (!auth || !auth->getCurrentUser() || !uiCore) {
        cout << "Error: No user logged in or required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string oldPassword, newPassword, confirmPassword;
    
    uiCore->clearScreen();
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
        uiCore->pauseScreen();
        return;
    }
    
    // Process password change
    if (auth->changePassword(auth->getCurrentUser()->getUsername(), oldPassword, newPassword)) {
        cout << "Password changed successfully!\n";
    } else {
        cout << "Failed to change password. Please check your current password.\n";
    }
    
    uiCore->pauseScreen();
}

/**
 * Handles credit point top-up operations with password authentication.
 * Allows users to add credit points to their account balance.
 * Rate: $1 = 1 Credit Point (CP)
 */
void UIProfile::topUpCreditPoints() {
    if (!auth || !auth->getCurrentUser() || !uiCore) {
        cout << "Error: No user logged in or required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string password;
    double amount;
    
    uiCore->clearScreen();
    cout << "=== TOP UP CREDIT POINTS ===\n";
    cout << "Current balance: " << auth->getCurrentUser()->getCreditPoints() << " CPs\n";
    cout << "Rate: $1 = 1 CP\n\n";
    
    // Get top-up amount
    cout << "Enter amount to top up ($): ";
    cin >> amount;
    
    // Validate amount
    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive value.\n";
        uiCore->pauseScreen();
        return;
    }
    
    // Require password authentication for security
    cout << "Enter your password to confirm: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    password = auth->hidePassword();
    cout << endl;
    
    // Verify password before processing
    if (password != auth->getCurrentUser()->getPassword()) {
        cout << "Incorrect password. Top-up cancelled.\n";
        uiCore->pauseScreen();
        return;
    }
    
    // Process top-up
    if (auth->topUpCreditPoints(auth->getCurrentUser()->getUsername(), amount)) {
        cout << "Successfully topped up " << amount << " CPs!\n";
        cout << "New balance: " << (auth->getCurrentUser()->getCreditPoints() + amount) << " CPs\n";
    } else {
        cout << "Failed to top up credit points.\n";
    }
    
    uiCore->pauseScreen();
}

/**
 * Displays comprehensive booking history and rating statistics.
 * Shows both rental bookings (as renter) and rental requests (as owner).
 * Includes rating information for both renter and motorbike ratings.
 */
void UIProfile::viewBookingHistory() {
    if (!auth || !auth->getCurrentUser() || !uiCore) {
        cout << "Error: No user logged in or required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
    cout << "=== BOOKING HISTORY ===\n";
    
    string username = auth->getCurrentUser()->getUsername();
    
    // Display user's bookings as a renter
    vector<Booking> userBookings = bookingManager->getUserBookings(username);
    
    if (userBookings.empty()) {
        cout << "No booking history found.\n";
    } else {
        cout << "Your Rental Bookings:\n";
        cout << "----------------------\n";
        cout << "Booking ID | Period | Motorbike | Status | Cost\n";
        for (const Booking& booking : userBookings) {
            cout << booking.getBookingId() << " | "
                 << booking.getStartDate() << "-" << booking.getEndDate() << " | "
                 << booking.getBrand() << " " << booking.getModel() << " | "
                 << booking.getStatus() << " | $"
                 << booking.getTotalCost() << "\n";
        }
    }
    
    // Display user's rental requests (as motorbike owner)
    vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
    
    if (!rentalRequests.empty()) {
        cout << "\nRental Requests (Your Motorbikes):\n";
        cout << "----------------------------------\n";
        cout << "Booking ID | Renter | Period | Motorbike | Status\n";
        for (const Booking& request : rentalRequests) {
            cout << request.getBookingId() << " | "
                 << request.getRenterUsername() << " | "
                 << request.getStartDate() << "-" << request.getEndDate() << " | "
                 << request.getBrand() << " " << request.getModel() << " | "
                 << request.getStatus() << "\n";
        }
    }
    
    // Display comprehensive rating statistics
    cout << "\nRating Statistics:\n";
    cout << "------------------\n";
    cout << "Your Renter Rating: " << auth->getCurrentUser()->getRating() << "/5.0\n";
    cout << "Your Motorbike Rating: " << bookingManager->getUserMotorbikeRating(username) << "/5.0\n";
    
    uiCore->pauseScreen();
}
