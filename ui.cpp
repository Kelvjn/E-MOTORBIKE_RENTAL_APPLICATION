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
#include <cctype>
#include <iomanip> // Required for setw and setprecision

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
    int choice;
    do {
        clearScreen();
        cout << "=== GUEST MENU ===\n";
        cout << "1.View motorbike listings\n";
        cout << "2.Search motorbikes\n";
        cout << "3.Back to main menu\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewGuestMotorbikeListings();
                break;
            case 2:
                searchGuestMotorbikes();
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
void UI::showMemberMenu() {
    int choice;
    do {
        clearScreen();
        cout << "=== MEMBER MENU ===\n";
        cout << "1.Activity Dashboard\n";
        cout << "2.List my motorbike for rent\n";
        cout << "3.Browse available motorbikes\n";
        cout << "4.My bookings\n";
        cout << "5.Rental requests (for my motorbikes)\n";
        cout << "6.Complete approved rentals\n";
        cout << "7.My profile\n";
        cout << "8.Rate completed rentals\n";
        cout << "9.Identity verification\n";
        cout << "10.Logout\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                showActivityDashboard();
                break;
            case 2:
                showMotorbikeListingMenu();
                break;
            case 3:
                showMotorbikeSearchMenu();
                break;
            case 4:
                cout << "Viewing my bookings...\n";
                pauseScreen();
                break;
            case 5:
                viewRentalRequests();
                break;
            case 6:
                viewApprovedRentals();
                break;
            case 7:
                showProfileMenu();
                break;
            case 8:
                viewCompletedRentals();
                break;
            case 9:
                showVerificationMenu();
                break;
            case 10:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    } while (choice != 10);
}

/**
 * Displays the admin menu with administrative functions.
 * Admins can view all member profiles, motorbike listings, and system statistics.
 */
void UI::showAdminMenu() {
    int choice;
    do {
        clearScreen();
        cout << "=== ADMIN MENU ===\n";
        cout << "1.View all member profiles\n";
        cout << "2.View all motorbike listings\n";
        cout << "3.System statistics\n";
        cout << "4.Logout\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                viewAllMemberProfiles();
                break;
            case 2:
                viewAllMotorbikeListings();
                break;
            case 3:
                showSystemStatistics();
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
                    auth->displayProfile(auth->getCurrentUser()->getUsername(), bookingManager);
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
        pauseScreen();
        return;
    }
    
    cout << "Enter new phone number (or press Enter to keep current): ";
    getline(cin, phoneNumber);
    if (phoneNumber.empty()) {
        phoneNumber = currentUser->getPhoneNumber();
    } else if (!auth->validatePhoneNumber(phoneNumber)) {
        cout << "Invalid phone number format. Profile not updated.\n";
        pauseScreen();
        return;
    }
    
    // Update profile in database and memory
    if (auth->updateProfile(currentUser->getUsername(), fullName, email, phoneNumber)) {
        cout << "\nProfile updated successfully!\n";
        // Update current user object to reflect changes immediately
        currentUser->getFullName() = fullName;
        currentUser->getEmail() = email;
        currentUser->getPhoneNumber() = phoneNumber;
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
    if (auth->changePassword(auth->getCurrentUser()->getUsername(), oldPassword, newPassword)) {
        cout << "Password changed successfully!\n";
        // Update current user object to reflect changes immediately
        // Password is updated through Auth class, not directly
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
    cout << "Current balance: " << auth->getCurrentUser()->getCreditPoints() << " CPs\n";
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
    if (password != auth->getCurrentUser()->getPassword()) {
        cout << "Incorrect password. Top-up cancelled.\n";
        pauseScreen();
        return;
    }
    
    // Process top-up
    if (auth->topUpCreditPoints(auth->getCurrentUser()->getUsername(), amount)) {
        cout << "Successfully topped up " << amount << " CPs!\n";
        cout << "New balance: " << (auth->getCurrentUser()->getCreditPoints() + amount) << " CPs\n";
        // Update current user object to reflect changes immediately
        // Credit points are updated through Auth class, not directly
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
    // If there's an immediate leftover newline from previous formatted input (>>) consume it
    if (cin.peek() == '\n') {
        cin.ignore(1, '\n');
    }
    // Now wait for exactly one Enter from the user
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Electric motorbike listing management functions

/**
 * Displays the motorbike listing management menu with options to list, unlist, and view motorbike.
 */
void UI::showMotorbikeListingMenu() {
    while (true) {
        clearScreen();
        cout << "=== MOTORBIKE LISTING MANAGEMENT ===\n";
        cout << "1. List My Motorbike for Rent\n";
        cout << "2. Unlist My Motorbike\n";
        cout << "3. View My Current Listing\n";
        cout << "4. Back to Member Menu\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                listMyMotorbike();
                break;
            case 2:
                unlistMyMotorbike();
                break;
            case 3:
                viewMyMotorbikeListing();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
    }
}

/**
 * Handles the motorbike listing process with comprehensive input validation.
 * Collects all required information for listing an electric motorbike.
 */
void UI::listMyMotorbike() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    // Check if user already has a motorbike listed
    if (bookingManager->isMotorbikeListed(username)) {
        cout << "You already have a motorbike listed. Each member can only list one motorbike.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== LIST MY MOTORBIKE FOR RENT ===\n";
    cout << "Please provide the following information:\n\n";
    
    string brand, model, color, size, plateNo, location, startDate, endDate;
    double pricePerDay, minRenterRating;
    
    // Get motorbike details
    cout << "Brand: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, brand);
    
    cout << "Model: ";
    getline(cin, model);
    
    cout << "Color: ";
    getline(cin, color);
    
    cout << "Size (e.g., 50cc, 110cc): ";
    getline(cin, size);
    
    cout << "Plate Number: ";
    getline(cin, plateNo);
    
    // Get location (HCMC or Hanoi only)
    cout << "Location (HCMC or Hanoi): ";
    getline(cin, location);
    
    // Get available rental period
    cout << "Available Start Date (DD/MM/YYYY): ";
    getline(cin, startDate);
    
    cout << "Available End Date (DD/MM/YYYY): ";
    getline(cin, endDate);
    
    // Get daily rental rate
    cout << "Daily Rental Rate (CP): ";
    cin >> pricePerDay;
    
    // Get minimum required renter rating
    cout << "Minimum Required Renter Rating (1.0-5.0): ";
    cin >> minRenterRating;
    
    // Validate and process listing
    if (bookingManager->listMotorbike(username, brand, model, color, size, plateNo,
                                     pricePerDay, location, startDate, endDate, minRenterRating)) {
        cout << "\nMotorbike listed successfully!\n";
    } else {
        cout << "\nFailed to list motorbike. Please check your input.\n";
    }
    
    pauseScreen();
}

/**
 * Handles the motorbike unlisting process with validation.
 */
void UI::unlistMyMotorbike() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== UNLIST MY MOTORBIKE ===\n";
    
    if (!bookingManager->isMotorbikeListed(username)) {
        cout << "You don't have any motorbike listed.\n";
        pauseScreen();
        return;
    }
    
    cout << "Are you sure you want to unlist your motorbike? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (tolower(confirm) == 'y') {
        if (bookingManager->unlistMotorbike(username)) {
            cout << "Motorbike unlisted successfully!\n";
        }
    } else {
        cout << "Unlisting cancelled.\n";
    }
    
    pauseScreen();
}

/**
 * Displays the current motorbike listing for the logged-in user.
 */
void UI::viewMyMotorbikeListing() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== MY MOTORBIKE LISTING ===\n";
    
    if (!bookingManager->isMotorbikeListed(username)) {
        cout << "You don't have any motorbike listed.\n";
        pauseScreen();
        return;
    }
    
    // Get user's motorbike
    vector<Motorbike> userMotorbikes = bookingManager->getUserMotorbikes(username);
    
    for (const Motorbike& motorbike : userMotorbikes) {
        if (motorbike.getIsListed()) {
            cout << "Motorbike ID: " << motorbike.getMotorbikeId() << "\n";
            cout << "Brand: " << motorbike.getBrand() << " " << motorbike.getModel() << "\n";
            cout << "Color: " << motorbike.getColor() << "\n";
            cout << "Size: " << motorbike.getSize() << "\n";
            cout << "Plate Number: " << motorbike.getPlateNo() << "\n";
            cout << "Location: " << motorbike.getLocation() << "\n";
            cout << "Daily Rate: " << motorbike.getPricePerDay() << " CP\n";
            cout << "Available Period: " << motorbike.getAvailableStartDate() << " to " << motorbike.getAvailableEndDate() << "\n";
            cout << "Minimum Renter Rating: " << motorbike.getMinRenterRating() << "\n";
            cout << "Current Rating: " << motorbike.getRating() << "/5.0\n";
            cout << "Status: " << (motorbike.getIsAvailable() ? "Available" : "Not Available") << "\n";
            break;
        }
    }
    
    pauseScreen();
}

/**
 * Displays the motorbike search menu and handles user selection.
 */
void UI::showMotorbikeSearchMenu() {
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
    
    int choice;
    do {
        clearScreen();
        cout << "=== MOTORBIKE SEARCH MENU ===\n";
        cout << "1. Search Available Motorbikes\n";
        cout << "2. Back to Member Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                searchMotorbikes();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    } while (choice != 2);
}

/**
 * Handles the motorbike search process with filtering criteria.
 */
void UI::searchMotorbikes() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== SEARCH AVAILABLE MOTORBIKES ===\n";
    
    // Get search criteria
    string searchDate, city;
    string startDate, endDate;
    bool useDateRange = false;
    
    cout << "Search by:\n";
    cout << "1. Single date\n";
    cout << "2. Date range\n";
    cout << "Enter your choice: ";
    
    int dateChoice;
    cin >> dateChoice;
    
    if (dateChoice == 2) {
        useDateRange = true;
        cout << "Enter start date (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, startDate);
        
        cout << "Enter end date (DD/MM/YYYY): ";
        getline(cin, endDate);
        
        searchDate = startDate; // Use start date for compatibility
    } else {
        cout << "Enter search date (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, searchDate);
    }
    
    cout << "Enter city (HCMC or Hanoi): ";
    getline(cin, city);
    
    // Validate city input
    if (city != "HCMC" && city != "Hanoi") {
        cout << "Invalid city. Only HCMC and Hanoi are supported.\n";
        pauseScreen();
        return;
    }
    
    // Perform search
    vector<Motorbike> results;
    if (useDateRange) {
        results = bookingManager->searchMotorbikesByDateRange(startDate, endDate, city, username, *auth);
    } else {
        results = bookingManager->searchMotorbikes(searchDate, city, username, *auth);
    }
    
    // Display results
    clearScreen();
    cout << "=== SEARCH RESULTS ===\n";
    if (useDateRange) {
        cout << "Date Range: " << startDate << " to " << endDate << "\n";
    } else {
        cout << "Search Date: " << searchDate << "\n";
    }
    cout << "City: " << city << "\n";
    cout << "Found " << results.size() << " available motorbike(s)\n\n";
    
    if (results.empty()) {
        cout << "No motorbikes found matching your criteria.\n";
        cout << "This could be due to:\n";
        cout << "- No motorbikes available in " << city << " on " << searchDate << "\n";
        cout << "- Your rating doesn't meet the minimum requirements\n";
        cout << "- Insufficient credit points\n";
        cout << "- License requirements not met (for motorbikes > 50cc)\n";
    } else {
        cout << "Available Motorbikes:\n";
        cout << "ID  | Brand/Model        | Color  | Size  | Plate No.    | Daily Rate | Rating | Min Rating\n";
        cout << "----|-------------------|--------|-------|--------------|------------|--------|-----------\n";
        
        for (size_t i = 0; i < results.size(); i++) {
            const Motorbike& motorbike = results[i];
            cout << setw(3) << (i + 1) << " | "
                 << setw(17) << (motorbike.getBrand() + " " + motorbike.getModel()) << " | "
                 << setw(6) << motorbike.getColor() << " | "
                 << setw(5) << motorbike.getSize() << " | "
                 << setw(12) << motorbike.getPlateNo() << " | "
                 << setw(10) << motorbike.getPricePerDay() << " CP | "
                 << setw(6) << fixed << setprecision(1) << motorbike.getRating() << " | "
                 << setw(9) << motorbike.getMinRenterRating() << "\n";
        }
        
        // Option to view details
        cout << "\nEnter motorbike number to view details (0 to go back): ";
        int choice;
        cin >> choice;
        
        if (choice > 0 && choice <= static_cast<int>(results.size())) {
            displayMotorbikeDetails(results[choice - 1]);
            
            // Ask if user wants to make a rental request
            cout << "\nDo you want to make a rental request for this motorbike? (y/n): ";
            char requestChoice;
            cin >> requestChoice;
            
            if (tolower(requestChoice) == 'y') {
                makeRentalRequest(results[choice - 1]);
            }
            
            // Details view already pauses; avoid a second pause here
            return;
        }
    }
    
    // Pause only when not returning from details view
    pauseScreen();
}

/**
 * Displays detailed information about a specific motorbike.
 */
void UI::displayMotorbikeDetails(const Motorbike& motorbike) {
    clearScreen();
    cout << "=== MOTORBIKE DETAILS ===\n";
    cout << "Motorbike ID: " << motorbike.getMotorbikeId() << "\n";
    cout << "Brand: " << motorbike.getBrand() << "\n";
    cout << "Model: " << motorbike.getModel() << "\n";
    cout << "Color: " << motorbike.getColor() << "\n";
    cout << "Engine Size: " << motorbike.getSize() << "\n";
    cout << "Plate Number: " << motorbike.getPlateNo() << "\n";
    cout << "Location: " << motorbike.getLocation() << "\n";
    cout << "Daily Rental Rate: " << motorbike.getPricePerDay() << " CP\n";
    cout << "Available Period: " << motorbike.getAvailableStartDate() << " to " << motorbike.getAvailableEndDate() << "\n";
    cout << "Minimum Required Renter Rating: " << motorbike.getMinRenterRating() << "\n";
    cout << "Motorbike Rating: " << motorbike.getRating() << "/5.0\n";
    cout << "Description: " << motorbike.getDescription() << "\n";
    
    // Display reviews
    displayMotorbikeReviews(motorbike.getMotorbikeId());
    
    pauseScreen();
}

/**
 * Displays reviews for a specific motorbike.
 */
void UI::displayMotorbikeReviews(const string& motorbikeId) {
    if (!bookingManager) {
        return;
    }
    
    cout << "\n=== CUSTOMER REVIEWS ===\n";
    
    vector<string> reviews = bookingManager->getMotorbikeReviews(motorbikeId);
    double averageRating = bookingManager->getAverageRating(motorbikeId);
    
    cout << "Average Rating: " << fixed << setprecision(1) << averageRating << "/5.0\n\n";
    
    if (reviews.empty()) {
        cout << "No reviews available for this motorbike.\n";
    } else {
        cout << "Customer Comments:\n";
        for (size_t i = 0; i < reviews.size(); i++) {
            cout << (i + 1) << ". " << reviews[i] << "\n";
        }
    }
}

/**
 * Displays all member profiles for admin view.
 * Shows comprehensive information about all registered members.
 */
void UI::viewAllMemberProfiles() {
    if (!auth) {
        cout << "Error: Authentication system not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== ALL MEMBER PROFILES ===\n\n";
    
    vector<User> allUsers = auth->getAllUsers();
    
    if (allUsers.empty()) {
        cout << "No users found in the system.\n";
        pauseScreen();
        return;
    }
    
    // Display header
    cout << setw(15) << left << "Username" << " | "
         << setw(20) << "Full Name" << " | "
         << setw(25) << "Email" << " | "
         << setw(12) << "Phone" << " | "
         << setw(8) << "Role" << " | "
         << setw(8) << "CPs" << " | "
         << setw(8) << "Rating" << " | "
         << setw(12) << "License Expiry" << "\n";
    cout << string(120, '-') << "\n";
    
    int memberCount = 0;
    int adminCount = 0;
    
    for (const User& user : allUsers) {
        cout << setw(15) << left << user.getUsername() << " | "
             << setw(20) << user.getFullName() << " | "
             << setw(25) << user.getEmail() << " | "
             << setw(12) << user.getPhoneNumber() << " | "
             << setw(8) << user.getRole() << " | "
             << setw(8) << fixed << setprecision(0) << user.getCreditPoints() << " | "
             << setw(8) << fixed << setprecision(1) << user.getRating() << " | "
             << setw(12) << user.getLicenseExpiry() << "\n";
        
        if (user.getRole() == "member") {
            memberCount++;
        } else if (user.getRole() == "admin") {
            adminCount++;
        }
    }
    
    cout << "\n=== SUMMARY ===\n";
    cout << "Total Users: " << allUsers.size() << "\n";
    cout << "Members: " << memberCount << "\n";
    cout << "Admins: " << adminCount << "\n";
    
    pauseScreen();
}

/**
 * Displays all motorbike listings for admin view.
 * Shows comprehensive information about all listed motorbikes.
 */
void UI::viewAllMotorbikeListings() {
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== ALL MOTORBIKE LISTINGS ===\n\n";
    
    vector<Motorbike> allMotorbikes = bookingManager->getAvailableMotorbikes();
    
    if (allMotorbikes.empty()) {
        cout << "No motorbikes found in the system.\n";
        pauseScreen();
        return;
    }
    
    // Display header
    cout << setw(8) << left << "ID" << " | "
         << setw(15) << "Owner" << " | "
         << setw(20) << "Brand/Model" << " | "
         << setw(8) << "Color" << " | "
         << setw(8) << "Size" << " | "
         << setw(12) << "Plate No." << " | "
         << setw(8) << "Location" << " | "
         << setw(10) << "Daily Rate" << " | "
         << setw(8) << "Rating" << " | "
         << setw(8) << "Listed" << " | "
         << setw(8) << "Available" << "\n";
    cout << string(120, '-') << "\n";
    
    int listedCount = 0;
    int availableCount = 0;
    double totalValue = 0.0;
    
    for (const Motorbike& motorbike : allMotorbikes) {
        cout << setw(8) << left << motorbike.getMotorbikeId() << " | "
             << setw(15) << motorbike.getOwnerUsername() << " | "
             << setw(20) << (motorbike.getBrand() + " " + motorbike.getModel()) << " | "
             << setw(8) << motorbike.getColor() << " | "
             << setw(8) << motorbike.getSize() << " | "
             << setw(12) << motorbike.getPlateNo() << " | "
             << setw(8) << motorbike.getLocation() << " | "
             << setw(10) << fixed << setprecision(0) << motorbike.getPricePerDay() << " CP | "
             << setw(8) << fixed << setprecision(1) << motorbike.getRating() << " | "
             << setw(8) << (motorbike.getIsListed() ? "Yes" : "No") << " | "
             << setw(8) << (motorbike.getIsAvailable() ? "Yes" : "No") << "\n";
        
        if (motorbike.getIsListed()) {
            listedCount++;
            totalValue += motorbike.getPricePerDay();
        }
        if (motorbike.getIsAvailable()) {
            availableCount++;
        }
    }
    
    cout << "\n=== SUMMARY ===\n";
    cout << "Total Motorbikes: " << allMotorbikes.size() << "\n";
    cout << "Listed Motorbikes: " << listedCount << "\n";
    cout << "Available Motorbikes: " << availableCount << "\n";
    cout << "Total Daily Value: " << fixed << setprecision(0) << totalValue << " CP\n";
    
    pauseScreen();
}

/**
 * Displays comprehensive system statistics for admin view.
 * Shows detailed information about users, motorbikes, and bookings.
 */
void UI::showSystemStatistics() {
    if (!auth || !bookingManager) {
        cout << "Error: System components not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== SYSTEM STATISTICS ===\n\n";
    
    // Get all data
    vector<User> allUsers = auth->getAllUsers();
    vector<Motorbike> allMotorbikes = bookingManager->getAvailableMotorbikes();
    vector<Booking> allBookings = bookingManager->getAllBookings();
    
    // Calculate statistics
    int totalUsers = allUsers.size();
    int memberCount = 0;
    int adminCount = 0;
    double totalCreditPoints = 0.0;
    double averageRating = 0.0;
    
    for (const User& user : allUsers) {
        if (user.getRole() == "member") {
            memberCount++;
            totalCreditPoints += user.getCreditPoints();
            averageRating += user.getRating();
        } else if (user.getRole() == "admin") {
            adminCount++;
        }
    }
    
    int totalMotorbikes = allMotorbikes.size();
    int listedMotorbikes = 0;
    int availableMotorbikes = 0;
    double totalMotorbikeValue = 0.0;
    double averageMotorbikeRating = 0.0;
    
    for (const Motorbike& motorbike : allMotorbikes) {
        if (motorbike.getIsListed()) {
            listedMotorbikes++;
            totalMotorbikeValue += motorbike.getPricePerDay();
        }
        if (motorbike.getIsAvailable()) {
            availableMotorbikes++;
        }
        averageMotorbikeRating += motorbike.getRating();
    }
    
    int totalBookings = allBookings.size();
    int pendingBookings = 0;
    int approvedBookings = 0;
    int completedBookings = 0;
    int rejectedBookings = 0;
    double totalBookingValue = 0.0;
    
    for (const Booking& booking : allBookings) {
        if (booking.getStatus() == "Pending") pendingBookings++;
        else if (booking.getStatus() == "Approved") approvedBookings++;
        else if (booking.getStatus() == "Completed") completedBookings++;
        else if (booking.getStatus() == "Rejected") rejectedBookings++;
        
        totalBookingValue += booking.getTotalCost();
    }
    
    // Display statistics
    cout << "=== USER STATISTICS ===\n";
    cout << "Total Users: " << totalUsers << "\n";
    cout << "Members: " << memberCount << "\n";
    cout << "Admins: " << adminCount << "\n";
    cout << "Total Credit Points: " << fixed << setprecision(0) << totalCreditPoints << " CP\n";
    if (memberCount > 0) {
        cout << "Average Member Rating: " << fixed << setprecision(1) << (averageRating / memberCount) << "/5.0\n";
    }
    
    cout << "\n=== MOTORBIKE STATISTICS ===\n";
    cout << "Total Motorbikes: " << totalMotorbikes << "\n";
    cout << "Listed Motorbikes: " << listedMotorbikes << "\n";
    cout << "Available Motorbikes: " << availableMotorbikes << "\n";
    cout << "Total Daily Value: " << fixed << setprecision(0) << totalMotorbikeValue << " CP\n";
    if (totalMotorbikes > 0) {
        cout << "Average Motorbike Rating: " << fixed << setprecision(1) << (averageMotorbikeRating / totalMotorbikes) << "/5.0\n";
    }
    
    cout << "\n=== BOOKING STATISTICS ===\n";
    cout << "Total Bookings: " << totalBookings << "\n";
    cout << "Pending Bookings: " << pendingBookings << "\n";
    cout << "Approved Bookings: " << approvedBookings << "\n";
    cout << "Completed Bookings: " << completedBookings << "\n";
    cout << "Rejected Bookings: " << rejectedBookings << "\n";
    cout << "Total Booking Value: " << fixed << setprecision(0) << totalBookingValue << " CP\n";
    
    cout << "\n=== SYSTEM OVERVIEW ===\n";
    cout << "System Utilization: " << fixed << setprecision(1) << ((double)listedMotorbikes / totalMotorbikes * 100) << "%\n";
    cout << "Booking Success Rate: " << fixed << setprecision(1) << ((double)approvedBookings / totalBookings * 100) << "%\n";
    
    pauseScreen();
}

/**
 * Displays limited motorbike listings for guests.
 * Shows only brand, model, engine size, and location as per requirements.
 */
void UI::viewGuestMotorbikeListings() {
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== GUEST MOTORBIKE LISTINGS ===\n";
    cout << "Note: As a guest, you can only view basic information.\n";
    cout << "Register as a member to see full details and make bookings.\n\n";
    
    vector<Motorbike> guestMotorbikes = bookingManager->getGuestMotorbikes();
    
    if (guestMotorbikes.empty()) {
        cout << "No motorbikes available for viewing.\n";
        pauseScreen();
        return;
    }
    
    // Display header with limited information
    cout << setw(20) << left << "Brand/Model" << " | "
         << setw(8) << "Size" << " | "
         << setw(8) << "Location" << "\n";
    cout << string(40, '-') << "\n";
    
    for (const Motorbike& motorbike : guestMotorbikes) {
        cout << setw(20) << left << (motorbike.getBrand() + " " + motorbike.getModel()) << " | "
             << setw(8) << motorbike.getSize() << " | "
             << setw(8) << motorbike.getLocation() << "\n";
    }
    
    cout << "\n=== GUEST ACCESS LIMITATIONS ===\n";
    cout << "As a guest, you cannot view:\n";
    cout << "- Ratings and reviews\n";
    cout << "- Pricing information\n";
    cout << "- Owner details\n";
    cout << "- Availability dates\n";
    cout << "- Make rental requests\n\n";
    
    cout << "To access full features, please register as a member.\n";
    
    pauseScreen();
}

/**
 * Allows guests to search motorbikes with limited information.
 * Search by city only, showing basic motorbike details.
 */
void UI::searchGuestMotorbikes() {
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "=== GUEST MOTORBIKE SEARCH ===\n";
    cout << "Note: Guest search is limited to city filtering only.\n\n";
    
    string city;
    cout << "Enter city to search (HCMC or Hanoi): ";
    cin.ignore();
    getline(cin, city);
    
    // Validate city input
    if (city != "HCMC" && city != "Hanoi") {
        cout << "Invalid city. Only HCMC and Hanoi are supported.\n";
        pauseScreen();
        return;
    }
    
    // Get all guest motorbikes and filter by city
    vector<Motorbike> allGuestMotorbikes = bookingManager->getGuestMotorbikes();
    vector<Motorbike> filteredMotorbikes;
    
    for (const Motorbike& motorbike : allGuestMotorbikes) {
        if (motorbike.getLocation() == city) {
            filteredMotorbikes.push_back(motorbike);
        }
    }
    
    // Display results
    clearScreen();
    cout << "=== SEARCH RESULTS FOR " << city << " ===\n";
    cout << "Found " << filteredMotorbikes.size() << " motorbike(s) in " << city << "\n\n";
    
    if (filteredMotorbikes.empty()) {
        cout << "No motorbikes found in " << city << ".\n";
    } else {
        // Display header with limited information
        cout << setw(20) << left << "Brand/Model" << " | "
             << setw(8) << "Size" << " | "
             << setw(8) << "Location" << "\n";
        cout << string(40, '-') << "\n";
        
        for (const Motorbike& motorbike : filteredMotorbikes) {
            cout << setw(20) << left << (motorbike.getBrand() + " " + motorbike.getModel()) << " | "
                 << setw(8) << motorbike.getSize() << " | "
                 << setw(8) << motorbike.getLocation() << "\n";
        }
    }
    
    cout << "\n=== GUEST SEARCH LIMITATIONS ===\n";
    cout << "As a guest, you cannot:\n";
    cout << "- Search by date\n";
    cout << "- Filter by price range\n";
    cout << "- Filter by rating requirements\n";
    cout << "- View detailed motorbike information\n";
    cout << "- Make rental requests\n\n";
    
    cout << "Register as a member to access advanced search features.\n";
    
    pauseScreen();
}

/**
 * Handles rental request submission for a specific motorbike.
 */
void UI::makeRentalRequest(const Motorbike& motorbike) {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== MAKE RENTAL REQUEST ===\n";
    cout << "Motorbike: " << motorbike.getBrand() << " " << motorbike.getModel() << "\n";
    cout << "Daily Rate: " << motorbike.getPricePerDay() << " CP\n";
    cout << "Available Period: " << motorbike.getAvailableStartDate() << " to " << motorbike.getAvailableEndDate() << "\n\n";
    
    string startDate, endDate;
    
    cout << "Enter rental start date (DD/MM/YYYY): ";
    cin.ignore();
    getline(cin, startDate);
    
    cout << "Enter rental end date (DD/MM/YYYY): ";
    getline(cin, endDate);
    
    // Submit the rental request
    if (bookingManager->createBooking(username, motorbike.getMotorbikeId(), startDate, endDate, *auth)) {
        cout << "\nRental request submitted successfully!\n";
    } else {
        cout << "\nFailed to submit rental request.\n";
    }
    
    pauseScreen();
}

/**
 * Displays rental requests for motorbike owners to approve/reject.
 */
void UI::viewRentalRequests() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== RENTAL REQUESTS FOR MY MOTORBIKES ===\n";
    
    vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
    
    if (rentalRequests.empty()) {
        cout << "No pending rental requests found.\n";
        pauseScreen();
        return;
    }
    
    cout << "Pending Requests:\n";
    cout << "ID  | Renter        | Motorbike        | Period           | Cost  | Status\n";
    cout << "----|---------------|------------------|------------------|-------|--------\n";
    
    for (size_t i = 0; i < rentalRequests.size(); i++) {
        const Booking& request = rentalRequests[i];
        cout << setw(3) << (i + 1) << " | "
             << setw(13) << request.getRenterUsername() << " | "
             << setw(16) << (request.getBrand() + " " + request.getModel()) << " | "
             << setw(16) << (request.getStartDate() + "-" + request.getEndDate()) << " | "
             << setw(5) << request.getTotalCost() << " CP | "
             << request.getStatus() << "\n";
    }
    
    cout << "\nEnter request number to approve/reject (0 to go back): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(rentalRequests.size())) {
        manageRentalRequest(rentalRequests[choice - 1]);
    }
    
    pauseScreen();
}

/**
 * Handles approval or rejection of a specific rental request.
 */
void UI::manageRentalRequest(const Booking& request) {
    clearScreen();
    cout << "=== MANAGE RENTAL REQUEST ===\n";
    cout << "Booking ID: " << request.getBookingId() << "\n";
    cout << "Renter: " << request.getRenterUsername() << "\n";
    cout << "Motorbike: " << request.getBrand() << " " << request.getModel() << "\n";
    cout << "Period: " << request.getStartDate() << " to " << request.getEndDate() << "\n";
    cout << "Total Cost: " << request.getTotalCost() << " CP\n\n";
    
    cout << "1. Approve Request\n";
    cout << "2. Reject Request\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            if (bookingManager->approveBooking(request.getBookingId(), request.getOwnerUsername(), *auth)) {
                cout << "Request approved successfully!\n";
            } else {
                cout << "Failed to approve request.\n";
            }
            break;
        case 2:
            if (bookingManager->rejectBooking(request.getBookingId(), request.getOwnerUsername())) {
                cout << "Request rejected.\n";
            } else {
                cout << "Failed to reject request.\n";
            }
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
    }
    // Do not pause here; the caller (viewRentalRequests) will pause once
}

/**
 * Displays completed rentals for rating.
 */
void UI::viewCompletedRentals() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== COMPLETED RENTALS ===\n";
    
    vector<Booking> userBookings = bookingManager->getUserBookings(username);
    vector<Booking> completedBookings;
    
    for (const Booking& booking : userBookings) {
        if (booking.getStatus() == "Completed") {
            completedBookings.push_back(booking);
        }
    }
    
    if (completedBookings.empty()) {
        cout << "No completed rentals found.\n";
        pauseScreen();
        return;
    }
    
    cout << "Completed Rentals:\n";
    cout << "ID  | Motorbike        | Period           | Cost  | Status\n";
    cout << "----|------------------|------------------|-------|--------\n";
    
    for (size_t i = 0; i < completedBookings.size(); i++) {
        const Booking& booking = completedBookings[i];
        cout << setw(3) << (i + 1) << " | "
             << setw(16) << (booking.getBrand() + " " + booking.getModel()) << " | "
             << setw(16) << (booking.getStartDate() + "-" + booking.getEndDate()) << " | "
             << setw(5) << booking.getTotalCost() << " CP | "
             << booking.getStatus() << "\n";
    }
    
    cout << "\nEnter rental number to rate (0 to go back): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(completedBookings.size())) {
        rateMotorbike(completedBookings[choice - 1]);
    }
    
    pauseScreen();
}

/**
 * Handles motorbike rating by the renter.
 */
void UI::rateMotorbike(const Booking& booking) {
    clearScreen();
    cout << "=== RATE MOTORBIKE ===\n";
    cout << "Booking ID: " << booking.getBookingId() << "\n";
    cout << "Motorbike: " << booking.getBrand() << " " << booking.getModel() << "\n";
    cout << "Period: " << booking.getStartDate() << " to " << booking.getEndDate() << "\n\n";
    
    double rating;
    string comment;
    
    cout << "Rate the motorbike (1.0 - 5.0): ";
    cin >> rating;
    
    cout << "Enter your comment: ";
    cin.ignore();
    getline(cin, comment);
    
    if (bookingManager->rateMotorbike(booking.getBookingId(), booking.getRenterUsername(), rating, comment)) {
        cout << "Thank you for rating the motorbike!\n";
    } else {
        cout << "Failed to submit rating.\n";
    }
    
    pauseScreen();
}

/**
 * Displays approved rentals that can be completed.
 */
void UI::viewApprovedRentals() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "=== APPROVED RENTALS ===\n";
    
    vector<Booking> userBookings = bookingManager->getUserBookings(username);
    vector<Booking> approvedBookings;
    
    for (const Booking& booking : userBookings) {
        if (booking.getStatus() == "Approved") {
            approvedBookings.push_back(booking);
        }
    }
    
    if (approvedBookings.empty()) {
        cout << "No approved rentals found.\n";
        pauseScreen();
        return;
    }
    
    cout << "Approved Rentals:\n";
    cout << "ID  | Motorbike        | Period           | Cost  | Status\n";
    cout << "----|------------------|------------------|-------|--------\n";
    
    for (size_t i = 0; i < approvedBookings.size(); i++) {
        const Booking& booking = approvedBookings[i];
        cout << setw(3) << (i + 1) << " | "
             << setw(16) << (booking.getBrand() + " " + booking.getModel()) << " | "
             << setw(16) << (booking.getStartDate() + "-" + booking.getEndDate()) << " | "
             << setw(5) << booking.getTotalCost() << " CP | "
             << booking.getStatus() << "\n";
    }
    
    cout << "\nEnter rental number to complete (0 to go back): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(approvedBookings.size())) {
        completeRental(approvedBookings[choice - 1]);
    }
    
    pauseScreen();
}

/**
 * Handles rental completion.
 */
void UI::completeRental(const Booking& booking) {
    clearScreen();
    cout << "=== COMPLETE RENTAL ===\n";
    cout << "Booking ID: " << booking.getBookingId() << "\n";
    cout << "Motorbike: " << booking.getBrand() << " " << booking.getModel() << "\n";
    cout << "Period: " << booking.getStartDate() << " to " << booking.getEndDate() << "\n";
    cout << "Total Cost: " << booking.getTotalCost() << " CP\n\n";
    
    cout << "Are you sure you want to complete this rental? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (tolower(confirm) == 'y') {
        if (bookingManager->completeRental(booking.getBookingId(), booking.getRenterUsername())) {
            cout << "Rental completed successfully!\n";
            cout << "You can now rate the motorbike in the 'Rate completed rentals' menu.\n";
        } else {
            cout << "Failed to complete rental.\n";
        }
    } else {
        cout << "Rental completion cancelled.\n";
    }
    
    pauseScreen();
}

/**
 * Displays a personalized activity dashboard for members.
 * Shows account overview, active rentals, and rental requests.
 */
void UI::showActivityDashboard() {
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
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "ACTIVITY DASHBOARD\n\n";
    
    // Account Overview Section (plain ASCII)
    cout << "Account Overview: " << username << "\n";
    cout << string(32, '-') << "\n";
    
    // Get user data
    double creditPoints = auth->getUserCreditPoints(username);
    double renterRating = auth->getUserRenterRating(username);
    double motorbikeRating = bookingManager->getUserMotorbikeRating(username);
    
    cout << "Current Credit Points: " << fixed << setprecision(0) << creditPoints << "\n";
    cout.unsetf(ios::floatfield);
    cout << "Renter rating: " << fixed << setprecision(1) << renterRating
         << "  |  Motorbike rating: " << fixed << setprecision(1) << motorbikeRating << "\n\n";
    
    // Active rental bookings (as renter)
    cout << "Your active rental booking\n";
    cout << string(30, '-') << "\n";
    vector<Booking> userBookings = bookingManager->getUserBookings(username);
    bool hasActive = false;
    cout << left
         << setw(18) << "Rent Period" << " | "
         << setw(6)  << "Brand" << " | "
         << setw(10) << "Model" << " | "
         << setw(5)  << "Color" << " | "
         << setw(5)  << "Size"  << " | "
         << setw(9)  << "Plate No." << " | "
         << setw(10) << "Owner" << " | "
         << "Status" << "\n";
    
    for (const Booking& b : userBookings) {
        if (b.getStatus() == "Approved") {
            hasActive = true;
            cout << setw(18) << (b.getStartDate() + "-" + b.getEndDate()) << " | "
                 << setw(6)  << b.getBrand() << " | "
                 << setw(10) << b.getModel() << " | "
                 << setw(5)  << b.getColor() << " | "
                 << setw(5)  << b.getSize() << " | "
                 << setw(9)  << b.getPlateNo() << " | "
                 << setw(10) << b.getOwnerUsername() << " | "
                 << b.getStatus() << "\n";
        }
    }
    if (!hasActive) {
        cout << "No active rentals found." << "\n";
    }
    cout << "\n";
    
    // Active rental requests (as owner)
    cout << "Your active rental requests\n";
    cout << string(30, '-') << "\n";
    vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
    bool hasRequests = false;
    cout << left
         << setw(18) << "Rent period" << " | "
         << setw(13) << "Renter rating" << " | "
         << "Renter" << "\n";
    for (const Booking& req : rentalRequests) {
        if (req.getStatus() == "Pending") {
            hasRequests = true;
            double renterReqRating = auth->getUserRenterRating(req.getRenterUsername());
            cout << setw(18) << (req.getStartDate() + "-" + req.getEndDate()) << " | "
                 << setw(13) << fixed << setprecision(1) << renterReqRating << " | "
                 << req.getRenterUsername() << "\n";
        }
    }
    if (!hasRequests) {
        cout << "No pending rental requests found." << "\n";
    }
    cout << "\n";
    
    // Simple next step
    cout << "1.Browse available motorbikes  2.View rental requests  3.Back\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            showMotorbikeSearchMenu();
            break;
        case 2:
            viewRentalRequests();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
    }
}

/**
 * Displays the identity verification menu.
 */
void UI::showVerificationMenu() {
    if (!auth || !auth->getCurrentUser()) {
        cout << "Error: No user logged in.\n";
        pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    clearScreen();
    cout << "IDENTITY VERIFICATION\n\n";
    
    // Display current verification status
    auth->displayVerificationStatus(username);
    
    cout << "\nVerification options\n";
    cout << string(20, '-') << "\n";
    cout << "1. Verify My Identity\n";
    cout << "2. View Verification Status\n";
    cout << "3. Back to Main Menu\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            if (auth->verifyIdentity(username)) {
                cout << "\nIdentity verification completed successfully!\n";
            } else {
                cout << "\nIdentity verification failed. Please try again.\n";
            }
            pauseScreen();
            break;
        case 2:
            auth->displayVerificationStatus(username);
            pauseScreen();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
            pauseScreen();
    }
}

