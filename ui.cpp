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
#include <map>

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
    while (true) {
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
}

/**
 * Displays the member menu with full functionality options.
 * Members can manage their motorbikes, make bookings, and access profile features.
 */
void UI::showMemberMenu() {
    while (true) {
        clearScreen();
        cout << "=== MEMBER MENU ===\n";
        cout << "1.Motorbike management\n";
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
                showMotorbikeMenu();
                break;
            case 2:
                searchAndBrowseMotorbikes();
                break;
            case 3:
                cout << "Viewing my bookings...\n";
                pauseScreen();
                break;
            case 4:
                topUpCreditPoints();
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
}

/**
 * Displays the admin menu with administrative functions.
 * Admins can view all member profiles, motorbike listings, and system statistics.
 */
void UI::showAdminMenu() {
    while (true) {
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
                viewAllMemberProfiles();
                break;
            case 2:
                viewAllMotorbikeListings();
                break;
            case 3:
                viewSystemStatistics();
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice.\n";
                pauseScreen();
        }
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
 * Displays the motorbike management menu with listing options.
 * Allows members to list, view, and unlist their electric motorbike.
 */
void UI::showMotorbikeMenu() {
    while (true) {
        clearScreen();
        cout << "=== MOTORBIKE MANAGEMENT ===\n";
        cout << "1.List my motorbike for rent\n";
        cout << "2.View my motorbike\n";
        cout << "3.Unlist my motorbike\n";
        cout << "4.Back to Member Menu\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                listMotorbikeForRent();
                break;
            case 2:
                viewMyMotorbike();
                break;
            case 3:
                unlistMyMotorbike();
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
 * Collects all required information according to the electric motorbike listing requirements.
 */
void UI::listMotorbikeForRent() {
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
    cout << "=== LIST ELECTRIC MOTORBIKE FOR RENT ===\n";
    cout << "Note: Each member can only register one electric motorbike.\n\n";
    
    // Check if user already has a listed motorbike
    if (bookingManager->hasUserListedMotorbike(auth->getCurrentUser()->username)) {
        cout << "You already have a motorbike listed for rent.\n";
        cout << "You can only register one electric motorbike per account.\n";
        pauseScreen();
        return;
    }
    
    string brand, model, color, size, plateNo, city, startDate, endDate, description;
    double pricePerDay, minRenterRating;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Collect motorbike information
    cout << "Enter motorbike brand: ";
    getline(cin, brand);
    
    cout << "Enter motorbike model: ";
    getline(cin, model);
    
    cout << "Enter motorbike color: ";
    getline(cin, color);
    
    cout << "Enter engine size (e.g., 50cc, 125cc): ";
    getline(cin, size);
    
    cout << "Enter plate number: ";
    getline(cin, plateNo);
    
    // Collect rental information
    cout << "Enter daily rental rate (in CP): ";
    cin >> pricePerDay;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter city (HCMC or Hanoi only): ";
    getline(cin, city);
    
    cout << "Enter available start date (DD/MM/YYYY): ";
    getline(cin, startDate);
    
    cout << "Enter available end date (DD/MM/YYYY): ";
    getline(cin, endDate);
    
    cout << "Enter minimum required renter rating (0.0-5.0): ";
    cin >> minRenterRating;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter motorbike description (optional): ";
    getline(cin, description);
    
    // Attempt to list the motorbike
    if (bookingManager->listMotorbike(auth->getCurrentUser()->username, brand, model, color, size, 
                                     plateNo, pricePerDay, city, startDate, endDate, 
                                     minRenterRating, description)) {
        cout << "\nMotorbike listed successfully!\n";
    } else {
        cout << "\nFailed to list motorbike. Please check your input and try again.\n";
    }
    
    pauseScreen();
}

/**
 * Displays the user's listed motorbike information.
 * Shows all details including rental period, city, and pricing.
 */
void UI::viewMyMotorbike() {
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
    cout << "=== MY MOTORBIKE ===\n";
    
    Motorbike* userMotorbike = bookingManager->getUserMotorbike(auth->getCurrentUser()->username);
    
    if (!userMotorbike) {
        cout << "You don't have any motorbike registered.\n";
        cout << "Use 'List my motorbike for rent' option to register your electric motorbike.\n";
    } else {
        cout << "Motorbike ID: " << userMotorbike->motorbikeId << "\n";
        cout << "Brand: " << userMotorbike->brand << "\n";
        cout << "Model: " << userMotorbike->model << "\n";
        cout << "Color: " << userMotorbike->color << "\n";
        cout << "Engine Size: " << userMotorbike->size << "\n";
        cout << "Plate Number: " << userMotorbike->plateNo << "\n";
        cout << "Daily Rate: " << userMotorbike->pricePerDay << " CP\n";
        cout << "City: " << userMotorbike->city << "\n";
        cout << "Available Period: " << userMotorbike->startDate << " - " << userMotorbike->endDate << "\n";
        cout << "Minimum Renter Rating: " << userMotorbike->minRenterRating << "/5.0\n";
        cout << "Status: " << (userMotorbike->isListed ? "Listed" : "Unlisted") << "\n";
        cout << "Rating: " << userMotorbike->rating << "/5.0\n";
        
        if (!userMotorbike->description.empty()) {
            cout << "Description: " << userMotorbike->description << "\n";
        }
    }
    
    pauseScreen();
}

/**
 * Handles the motorbike unlisting process.
 * Removes the motorbike from available listings unless it has active bookings.
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
    
    clearScreen();
    cout << "=== UNLIST MY MOTORBIKE ===\n";
    
    if (!bookingManager->hasUserListedMotorbike(auth->getCurrentUser()->username)) {
        cout << "You don't have any motorbike listed for rent.\n";
        pauseScreen();
        return;
    }
    
    cout << "Are you sure you want to unlist your motorbike? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        if (bookingManager->unlistMotorbike(auth->getCurrentUser()->username)) {
            cout << "Your motorbike has been unlisted successfully!\n";
        } else {
            cout << "Failed to unlist motorbike. It may have pending bookings.\n";
        }
    } else {
        cout << "Unlisting cancelled.\n";
    }
    
    pauseScreen();
}

/**
 * Handles motorbike search and browsing with comprehensive filtering.
 * Applies all search criteria including date, city, rating, CPs, and license requirements.
 */
void UI::searchAndBrowseMotorbikes() {
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
    cout << "=== SEARCH AVAILABLE MOTORBIKES ===\n\n";
    
    // Collect search criteria
    SearchCriteria criteria;
    string city, searchDate;
    
    // Get user's current information
    User* currentUser = auth->getCurrentUser();
    criteria.userRating = currentUser->rating;
    criteria.userCreditPoints = currentUser->creditPoints;
    criteria.hasValidLicense = hasValidLicense(currentUser->username);
    
    // Display user's current status
    cout << "Your current status:\n";
    cout << "- Renter Rating: " << criteria.userRating << "/5.0\n";
    cout << "- Credit Points: " << criteria.userCreditPoints << " CPs\n";
    cout << "- Valid License: " << (criteria.hasValidLicense ? "Yes" : "No") << "\n\n";
    
    // Get search parameters
    while (true) {
        cout << "Enter city (HCMC or Hanoi): ";
        cin >> city;
        if (bookingManager->validateCity(city)) {
            criteria.city = city;
            break;
        }
        cout << "Invalid city. Please enter 'HCMC' or 'Hanoi'.\n";
    }
    
    while (true) {
        cout << "Enter search date (DD/MM/YYYY): ";
        cin >> searchDate;
        if (bookingManager->validateDateFormat(searchDate)) {
            criteria.searchDate = searchDate;
            break;
        }
        cout << "Invalid date format. Please use DD/MM/YYYY format.\n";
    }
    
    cout << "\nSearching for motorbikes...\n\n";
    
    // Perform search
    vector<Motorbike> results = bookingManager->searchMotorbikes(criteria);
    
    if (results.empty()) {
        cout << "No motorbikes found matching your criteria.\n";
        cout << "This could be due to:\n";
        cout << "- No motorbikes available in " << city << " on " << searchDate << "\n";
        cout << "- Your renter rating (" << criteria.userRating << ") is below required minimums\n";
        cout << "- Insufficient credit points (" << criteria.userCreditPoints << " CPs)\n";
        if (!criteria.hasValidLicense) {
            cout << "- No valid license for motorbikes > 50cc\n";
        }
    } else {
        displaySearchResults(results);
    }
    
    pauseScreen();
}

/**
 * Displays search results with detailed motorbike information and filtering reasons.
 */
void UI::displaySearchResults(const vector<Motorbike>& results) {
    cout << "=== SEARCH RESULTS ===\n";
    cout << "Found " << results.size() << " motorbike(s) matching your criteria:\n\n";
    
    for (size_t i = 0; i < results.size(); i++) {
        const Motorbike& motorbike = results[i];
        
        cout << "[" << (i + 1) << "] " << motorbike.brand << " " << motorbike.model << "\n";
        cout << "    Engine: " << motorbike.size << " | Color: " << motorbike.color << "\n";
        cout << "    Location: " << motorbike.city << " | Daily Rate: " << motorbike.pricePerDay << " CPs\n";
        cout << "    Rating: " << motorbike.rating << "/5.0 | Min. Renter Rating: " << motorbike.minRenterRating << "/5.0\n";
        cout << "    Available: " << motorbike.startDate << " - " << motorbike.endDate << "\n";
        
        if (!motorbike.description.empty()) {
            cout << "    Description: " << motorbike.description << "\n";
        }
        
        cout << "\n";
    }
    
    // Option to view detailed information
    cout << "Enter motorbike number to view details and reviews (0 to return): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)results.size()) {
        viewMotorbikeDetails(results[choice - 1]);
    }
}

/**
 * Displays detailed motorbike information including reviews and ratings.
 */
void UI::viewMotorbikeDetails(const Motorbike& motorbike) {
    clearScreen();
    cout << "=== MOTORBIKE DETAILS ===\n\n";
    
    cout << "MOTORBIKE INFORMATION:\n";
    cout << "Brand: " << motorbike.brand << "\n";
    cout << "Model: " << motorbike.model << "\n";
    cout << "Color: " << motorbike.color << "\n";
    cout << "Engine Size: " << motorbike.size << "\n";
    cout << "Plate Number: " << motorbike.plateNo << "\n";
    cout << "Daily Rate: " << motorbike.pricePerDay << " CPs\n";
    cout << "Location: " << motorbike.city << "\n";
    cout << "Available Period: " << motorbike.startDate << " - " << motorbike.endDate << "\n";
    cout << "Minimum Renter Rating: " << motorbike.minRenterRating << "/5.0\n";
    cout << "Average Rating: " << motorbike.rating << "/5.0\n";
    
    if (!motorbike.description.empty()) {
        cout << "Description: " << motorbike.description << "\n";
    }
    
    cout << "\n=== REVIEWS ===\n";
    
    // Get and display reviews
    vector<Review> reviews = bookingManager->getMotorbikeReviews(motorbike.motorbikeId);
    
    if (reviews.empty()) {
        cout << "No reviews yet.\n";
    } else {
        for (const Review& review : reviews) {
            cout << "Reviewer: " << review.reviewerUsername << "\n";
            cout << "Rating: " << review.rating << "/5.0\n";
            cout << "Date: " << review.reviewDate << "\n";
            cout << "Comment: " << review.comment << "\n";
            cout << "---\n";
        }
    }
    
    cout << "\nOptions:\n";
    cout << "1. Request to rent this motorbike\n";
    cout << "2. Back to search results\n";
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Rental request feature coming soon!\n";
            pauseScreen();
            break;
        case 2:
        default:
            break;
    }
}

/**
 * Checks if a user has a valid driver's license.
 * For engines > 50cc, a valid license is required.
 */
bool UI::hasValidLicense(const string& username) {
    // Get user information from auth system
    if (!auth || !auth->getCurrentUser()) {
        return false;
    }
    
    User* user = auth->getCurrentUser();
    if (user->username != username) {
        return false; // Security check
    }
    
    // Check if user has license information
    if (user->licenseNumber == "N/A" || user->licenseExpiry == "N/A") {
        return false;
    }
    
    // Simple license validity check (in real system, would check expiry date)
    // For now, assume license is valid if it exists
    return !user->licenseNumber.empty() && user->licenseNumber != "N/A";
}

/**
 * Display all member profiles for admin review.
 * Shows comprehensive member information including ratings and booking history.
 */
void UI::viewAllMemberProfiles() {
    clearScreen();
    cout << "=== ALL MEMBER PROFILES ===\n\n";
    
    if (!auth) {
        cout << "Error: Authentication system not available.\n";
        pauseScreen();
        return;
    }
    
    // Get all users from auth system
    vector<User> allUsers = auth->getAllUsers();
    
    if (allUsers.empty()) {
        cout << "No members found in the system.\n";
        pauseScreen();
        return;
    }
    
    int memberCount = 0;
    for (const User& user : allUsers) {
        if (user.role == "member") {
            memberCount++;
            cout << "--- MEMBER " << memberCount << " ---\n";
            cout << "Username: " << user.username << "\n";
            cout << "Full Name: " << user.fullName << "\n";
            cout << "Email: " << user.email << "\n";
            cout << "Phone: " << user.phoneNumber << "\n";
            cout << "ID Type: " << user.idType << "\n";
            cout << "ID Number: " << user.idNumber << "\n";
            cout << "License Number: " << user.licenseNumber << "\n";
            cout << "License Expiry: " << user.licenseExpiry << "\n";
            cout << "Credit Points: " << user.creditPoints << " CP\n";
            cout << "Rating: " << user.rating << "/5.0\n";
            
            // Show booking statistics
            if (bookingManager) {
                vector<Booking> userBookings = bookingManager->getUserBookings(user.username);
                cout << "Total Bookings: " << userBookings.size() << "\n";
                
                // Count by status
                int pending = 0, approved = 0, completed = 0, rejected = 0;
                for (const Booking& booking : userBookings) {
                    if (booking.status == "Pending") pending++;
                    else if (booking.status == "Approved") approved++;
                    else if (booking.status == "Completed") completed++;
                    else if (booking.status == "Rejected") rejected++;
                }
                
                cout << "  - Pending: " << pending << ", Approved: " << approved 
                     << ", Completed: " << completed << ", Rejected: " << rejected << "\n";
                
                // Show motorbike ownership
                vector<Motorbike> userMotorbikes = bookingManager->getUserMotorbikes(user.username);
                cout << "Owned Motorbikes: " << userMotorbikes.size() << "\n";
                for (const Motorbike& mb : userMotorbikes) {
                    cout << "  - " << mb.brand << " " << mb.model << " (" << mb.plateNo 
                         << ") - " << (mb.isListed ? "Listed" : "Not Listed") << "\n";
                }
            }
            
            cout << "\n";
        }
    }
    
    if (memberCount == 0) {
        cout << "No members found in the system.\n";
    } else {
        cout << "Total Members: " << memberCount << "\n";
    }
    
    pauseScreen();
}

/**
 * Display all motorbike listings for admin review.
 * Shows comprehensive motorbike information including owner details and booking status.
 */
void UI::viewAllMotorbikeListings() {
    clearScreen();
    cout << "=== ALL MOTORBIKE LISTINGS ===\n\n";
    
    if (!bookingManager) {
        cout << "Error: Booking system not available.\n";
        pauseScreen();
        return;
    }
    
    // Get all motorbikes
    vector<Motorbike> allMotorbikes = bookingManager->getAllMotorbikes();
    
    if (allMotorbikes.empty()) {
        cout << "No motorbikes found in the system.\n";
        pauseScreen();
        return;
    }
    
    cout << "Total Motorbikes: " << allMotorbikes.size() << "\n\n";
    
    for (size_t i = 0; i < allMotorbikes.size(); i++) {
        const Motorbike& mb = allMotorbikes[i];
        
        cout << "--- MOTORBIKE " << (i + 1) << " ---\n";
        cout << "ID: " << mb.motorbikeId << "\n";
        cout << "Owner: " << mb.ownerUsername << "\n";
        cout << "Brand & Model: " << mb.brand << " " << mb.model << "\n";
        cout << "Color: " << mb.color << "\n";
        cout << "Engine Size: " << mb.size << "\n";
        cout << "Plate Number: " << mb.plateNo << "\n";
        cout << "Price per Day: " << mb.pricePerDay << " CP\n";
        cout << "City: " << mb.city << "\n";
        cout << "Available Period: " << mb.startDate << " to " << mb.endDate << "\n";
        cout << "Min Renter Rating: " << mb.minRenterRating << "/5.0\n";
        cout << "Status: " << (mb.isAvailable ? "Available" : "Unavailable") 
             << ", " << (mb.isListed ? "Listed" : "Unlisted") << "\n";
        cout << "Rating: " << mb.rating << "/5.0\n";
        cout << "Description: " << mb.description << "\n";
        
        // Show booking history for this motorbike
        vector<Booking> motorbikeBookings = bookingManager->getMotorbikeBookings(mb.motorbikeId);
        cout << "Total Bookings: " << motorbikeBookings.size() << "\n";
        
        if (!motorbikeBookings.empty()) {
            cout << "Recent Bookings:\n";
            int showCount = min(3, (int)motorbikeBookings.size()); // Show last 3 bookings
            for (int j = 0; j < showCount; j++) {
                const Booking& booking = motorbikeBookings[j];
                cout << "  - " << booking.renterUsername << " (" << booking.startDate 
                     << " to " << booking.endDate << ") - " << booking.status << "\n";
            }
        }
        
        cout << "\n";
    }
    
    pauseScreen();
}

/**
 * Display comprehensive system statistics for admin monitoring.
 * Shows user counts, booking statistics, revenue, and system health metrics.
 */
void UI::viewSystemStatistics() {
    clearScreen();
    cout << "=== SYSTEM STATISTICS ===\n\n";
    
    if (!auth || !bookingManager) {
        cout << "Error: System components not available.\n";
        pauseScreen();
        return;
    }
    
    // User Statistics
    vector<User> allUsers = auth->getAllUsers();
    int totalUsers = allUsers.size();
    int memberCount = 0, adminCount = 0;
    double totalCreditPoints = 0.0;
    
    for (const User& user : allUsers) {
        if (user.role == "member") {
            memberCount++;
            totalCreditPoints += user.creditPoints;
        } else if (user.role == "admin") {
            adminCount++;
        }
    }
    
    cout << "=== USER STATISTICS ===\n";
    cout << "Total Users: " << totalUsers << "\n";
    cout << "Members: " << memberCount << "\n";
    cout << "Admins: " << adminCount << "\n";
    cout << "Total Credit Points in System: " << totalCreditPoints << " CP\n";
    if (memberCount > 0) {
        cout << "Average Credit Points per Member: " << (totalCreditPoints / memberCount) << " CP\n";
    }
    cout << "\n";
    
    // Motorbike Statistics
    vector<Motorbike> allMotorbikes = bookingManager->getAllMotorbikes();
    int totalMotorbikes = allMotorbikes.size();
    int listedMotorbikes = 0, availableMotorbikes = 0;
    double totalRevenue = 0.0;
    map<string, int> cityCount, brandCount;
    
    for (const Motorbike& mb : allMotorbikes) {
        if (mb.isListed) listedMotorbikes++;
        if (mb.isAvailable) availableMotorbikes++;
        cityCount[mb.city]++;
        brandCount[mb.brand]++;
    }
    
    cout << "=== MOTORBIKE STATISTICS ===\n";
    cout << "Total Motorbikes: " << totalMotorbikes << "\n";
    cout << "Listed Motorbikes: " << listedMotorbikes << "\n";
    cout << "Available Motorbikes: " << availableMotorbikes << "\n";
    
    cout << "By City:\n";
    for (const auto& pair : cityCount) {
        cout << "  - " << pair.first << ": " << pair.second << " motorbikes\n";
    }
    
    cout << "Top Brands:\n";
    for (const auto& pair : brandCount) {
        cout << "  - " << pair.first << ": " << pair.second << " motorbikes\n";
    }
    cout << "\n";
    
    // Booking Statistics
    vector<Booking> allBookings = bookingManager->getAllBookings();
    int totalBookings = allBookings.size();
    int pendingBookings = 0, approvedBookings = 0, completedBookings = 0, rejectedBookings = 0;
    
    for (const Booking& booking : allBookings) {
        if (booking.status == "Pending") pendingBookings++;
        else if (booking.status == "Approved") approvedBookings++;
        else if (booking.status == "Completed") {
            completedBookings++;
            totalRevenue += booking.totalCost;
        }
        else if (booking.status == "Rejected") rejectedBookings++;
    }
    
    cout << "=== BOOKING STATISTICS ===\n";
    cout << "Total Bookings: " << totalBookings << "\n";
    cout << "Pending: " << pendingBookings << "\n";
    cout << "Approved: " << approvedBookings << "\n";
    cout << "Completed: " << completedBookings << "\n";
    cout << "Rejected: " << rejectedBookings << "\n";
    cout << "Total Revenue: " << totalRevenue << " CP\n";
    
    if (totalBookings > 0) {
        cout << "Success Rate: " << ((double)(approvedBookings + completedBookings) / totalBookings * 100) << "%\n";
    }
    cout << "\n";
    
    // Review Statistics
    vector<Review> allReviews = bookingManager->getAllReviews();
    cout << "=== REVIEW STATISTICS ===\n";
    cout << "Total Reviews: " << allReviews.size() << "\n";
    
    if (!allReviews.empty()) {
        double totalRating = 0.0;
        for (const Review& review : allReviews) {
            totalRating += review.rating;
        }
        cout << "Average Rating: " << (totalRating / allReviews.size()) << "/5.0\n";
    }
    
    pauseScreen();
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
