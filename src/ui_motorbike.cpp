/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Motorbike UI Implementation
 * 
 * This file implements the UIMotorbike class methods for handling motorbike
 * management operations including listing, searching, and viewing details.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_motorbike.h"
#include "ui_core.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>

using namespace std;

/**
 * Constructor
 */
UIMotorbike::UIMotorbike() : auth(nullptr), bookingManager(nullptr), uiCore(nullptr), uiBooking(nullptr) {
}

/**
 * Destructor
 */
UIMotorbike::~UIMotorbike() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays the motorbike listing management menu with options to list, unlist, and view motorbike.
 */
void UIMotorbike::showMotorbikeListingMenu() {
    if (!uiCore) {
        cout << "Error: Core UI not available.\n";
        return;
    }

    while (true) {
        uiCore->clearScreen();
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
                uiCore->pauseScreen();
        }
    }
}

/**
 * Handles the motorbike listing process with comprehensive input validation.
 * Collects all required information for listing an electric motorbike.
 */
void UIMotorbike::listMyMotorbike() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    // Check if user already has a motorbike listed
    if (bookingManager->isMotorbikeListed(username)) {
        cout << "You already have a motorbike listed. Each member can only list one motorbike.\n";
        uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Handles the motorbike unlisting process with validation.
 */
void UIMotorbike::unlistMyMotorbike() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
    cout << "=== UNLIST MY MOTORBIKE ===\n";
    
    if (!bookingManager->isMotorbikeListed(username)) {
        cout << "You don't have any motorbike listed.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays the current motorbike listing for the logged-in user.
 */
void UIMotorbike::viewMyMotorbikeListing() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
    cout << "=== MY MOTORBIKE LISTING ===\n";
    
    if (!bookingManager->isMotorbikeListed(username)) {
        cout << "You don't have any motorbike listed.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays the motorbike search menu and handles user selection.
 */
void UIMotorbike::showMotorbikeSearchMenu() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    int choice;
    do {
        uiCore->clearScreen();
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
                uiCore->pauseScreen();
        }
    } while (choice != 2);
}

/**
 * Handles the motorbike search process with filtering criteria.
 */
void UIMotorbike::searchMotorbikes() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
        uiCore->pauseScreen();
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
    uiCore->clearScreen();
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
    uiCore->pauseScreen();
}

/**
 * Displays detailed information about a specific motorbike.
 */
void UIMotorbike::displayMotorbikeDetails(const Motorbike& motorbike) {
    if (!uiCore) {
        cout << "Error: Core UI not available.\n";
        return;
    }

    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays reviews for a specific motorbike.
 */
void UIMotorbike::displayMotorbikeReviews(const string& motorbikeId) {
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
 * Handles rental request submission for a specific motorbike.
 */
void UIMotorbike::makeRentalRequest(const Motorbike& motorbike) {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}
