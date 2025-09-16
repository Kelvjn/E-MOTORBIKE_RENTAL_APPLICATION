/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Dashboard UI Implementation
 * 
 * This file implements the UIDashboard class methods for handling dashboard
 * and special features including activity overview and verification.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_dashboard.h"
#include "ui_core.h"
#include "ui_motorbike.h"
#include "ui_booking.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * Constructor
 */
UIDashboard::UIDashboard() : auth(nullptr), bookingManager(nullptr), uiCore(nullptr),
                             uiMotorbike(nullptr), uiBooking(nullptr) {
}

/**
 * Destructor
 */
UIDashboard::~UIDashboard() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays a personalized activity dashboard for members.
 * Shows account overview, active rentals, and rental requests.
 */
void UIDashboard::showActivityDashboard() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
    cout << "1. Browse available motorbikes  2. View rental requests  3. Back\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            if (uiMotorbike) uiMotorbike->showMotorbikeSearchMenu();
            break;
        case 2:
            if (uiBooking) uiBooking->viewRentalRequests();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
            if (uiCore) uiCore->pauseScreen();
    }
}

/**
 * Displays the identity verification menu.
 */
void UIDashboard::showVerificationMenu() {
    if (!auth || !auth->getCurrentUser() || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
            uiCore->pauseScreen();
            break;
        case 2:
            auth->displayVerificationStatus(username);
            uiCore->pauseScreen();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice.\n";
            uiCore->pauseScreen();
    }
}
