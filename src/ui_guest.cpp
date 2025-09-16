/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Guest UI Implementation
 * 
 * This file implements the UIGuest class methods for handling guest-specific
 * functions with limited access to motorbike information.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_guest.h"
#include "ui_core.h"
#include "booking.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * Constructor
 */
UIGuest::UIGuest() : bookingManager(nullptr), uiCore(nullptr) {
}

/**
 * Destructor
 */
UIGuest::~UIGuest() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays limited motorbike listings for guests.
 * Shows only brand, model, engine size, and location as per requirements.
 */
void UIGuest::viewGuestMotorbikeListings() {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
    cout << "=== GUEST MOTORBIKE LISTINGS ===\n";
    cout << "Note: As a guest, you can only view basic information.\n";
    cout << "Register as a member to see full details and make bookings.\n\n";
    
    vector<Motorbike> guestMotorbikes = bookingManager->getGuestMotorbikes();
    
    if (guestMotorbikes.empty()) {
        cout << "No motorbikes available for viewing.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Allows guests to search motorbikes with limited information.
 * Search by city only, showing basic motorbike details.
 */
void UIGuest::searchGuestMotorbikes() {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
    cout << "=== GUEST MOTORBIKE SEARCH ===\n";
    cout << "Note: Guest search is limited to city filtering only.\n\n";
    
    string city;
    cout << "Enter city to search (HCMC or Hanoi): ";
    cin.ignore();
    getline(cin, city);
    
    // Validate city input
    if (city != "HCMC" && city != "Hanoi") {
        cout << "Invalid city. Only HCMC and Hanoi are supported.\n";
        uiCore->pauseScreen();
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
    uiCore->clearScreen();
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
    
    uiCore->pauseScreen();
}
