/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Booking UI Implementation
 * 
 * This file implements the UIBooking class methods for handling booking
 * management operations including requests, approvals, and completions.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_booking.h"
#include "ui_core.h"
#include "auth.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

using namespace std;

/**
 * Constructor
 */
UIBooking::UIBooking() : auth(nullptr), bookingManager(nullptr), uiCore(nullptr) {
}

/**
 * Destructor
 */
UIBooking::~UIBooking() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays rental requests for motorbike owners to approve/reject.
 */
void UIBooking::viewRentalRequests() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
    cout << "=== RENTAL REQUESTS FOR MY MOTORBIKES ===\n";
    
    vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
    
    if (rentalRequests.empty()) {
        cout << "No pending rental requests found.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Handles approval or rejection of a specific rental request.
 */
void UIBooking::manageRentalRequest(const Booking& request) {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }

    uiCore->clearScreen();
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
void UIBooking::viewCompletedRentals() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Handles motorbike rating by the renter.
 */
void UIBooking::rateMotorbike(const Booking& booking) {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }

    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays approved rentals that can be completed.
 */
void UIBooking::viewApprovedRentals() {
    if (!auth || !auth->getCurrentUser() || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    string username = auth->getCurrentUser()->getUsername();
    
    uiCore->clearScreen();
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
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Handles rental completion.
 */
void UIBooking::completeRental(const Booking& booking) {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }

    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}
