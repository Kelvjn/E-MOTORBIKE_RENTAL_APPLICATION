/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Main Application Entry Point
 * 
 * This file contains the main function that initializes and runs the
 * E-Motorcycle Rental Application. It sets up the user interface,
 * authentication system, and booking management system.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include <iostream>
#include <string>
#include "ui.h"
#include "auth.h"
#include "booking.h"

using namespace std;

/**
 * Main function - Application entry point
 * 
 * Initializes the application components and runs the main program loop.
 * Handles user authentication, menu navigation, and application flow.
 * 
 * @return 0 on successful execution
 */
int main() {
    // Initialize application components
    UI ui;                    // User interface handler
    Auth auth;                // Authentication system
    BookingManager bookingManager;  // Booking and motorbike management
    
    // Set up component references for cross-class communication
    ui.setAuth(&auth);
    ui.setBookingManager(&bookingManager);
    
    // Display welcome screen with project information
    ui.showWelcomeScreen();
    
    // Main application loop
    while (true) {
        int choice = ui.showMainMenu();
        
        // Handle user menu selection
        switch (choice) {
            case 1: // Guest access
                ui.showGuestMenu();
                break;
            case 2: // Member login
                if (auth.login()) {
                    ui.showMemberMenu();
                }
                break;
            case 3: // Admin login
                if (auth.adminLogin()) {
                    ui.showAdminMenu();
                }
                break;
            case 4: // New member registration
                auth.registerUser();
                break;
            case 5: // Exit application
                cout << "\nThank you for using E-MOTORBIKE RENTAL APPLICATION!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
