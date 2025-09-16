/**
 * E-MOTORBIKE RENTAL APPLICATION
 * User Interface Manager Implementation
 * 
 * This file implements the UI class that manages all user interface modules
 * and coordinates between different UI components.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui.h"
#include "ui_core.h"
#include "ui_profile.h"
#include "ui_motorbike.h"
#include "ui_booking.h"
#include "ui_admin.h"
#include "ui_guest.h"
#include "ui_dashboard.h"
#include "auth.h"
#include "booking.h"

/**
 * Constructor - Initializes all UI modules
 */
UI::UI() : auth(nullptr), bookingManager(nullptr),
           uiCore(nullptr), uiProfile(nullptr), uiMotorbike(nullptr),
           uiBooking(nullptr), uiAdmin(nullptr), uiGuest(nullptr), 
           uiDashboard(nullptr) {
    initializeUIModules();
}

/**
 * Destructor - Cleans up all UI modules
 */
UI::~UI() {
    delete uiCore;
    delete uiProfile;
    delete uiMotorbike;
    delete uiBooking;
    delete uiAdmin;
    delete uiGuest;
    delete uiDashboard;
}

/**
 * Initialize all UI modules
 */
void UI::initializeUIModules() {
    uiCore = new UICore();
    uiProfile = new UIProfile();
    uiMotorbike = new UIMotorbike();
    uiBooking = new UIBooking();
    uiAdmin = new UIAdmin();
    uiGuest = new UIGuest();
    uiDashboard = new UIDashboard();
}

/**
 * Setup cross-references between UI modules
 */
void UI::setupModuleReferences() {
    if (!uiCore || !uiProfile || !uiMotorbike || !uiBooking || 
        !uiAdmin || !uiGuest || !uiDashboard) {
        return; // Safety check
    }

    // Set core system references for all modules
    uiCore->setAuth(auth);
    uiCore->setBookingManager(bookingManager);
    
    uiProfile->setAuth(auth);
    uiProfile->setBookingManager(bookingManager);
    uiProfile->setUICore(uiCore);
    
    uiMotorbike->setAuth(auth);
    uiMotorbike->setBookingManager(bookingManager);
    uiMotorbike->setUICore(uiCore);
    uiMotorbike->setUIBooking(uiBooking);
    
    uiBooking->setAuth(auth);
    uiBooking->setBookingManager(bookingManager);
    uiBooking->setUICore(uiCore);
    
    uiAdmin->setAuth(auth);
    uiAdmin->setBookingManager(bookingManager);
    uiAdmin->setUICore(uiCore);
    
    uiGuest->setBookingManager(bookingManager);
    uiGuest->setUICore(uiCore);
    
    uiDashboard->setAuth(auth);
    uiDashboard->setBookingManager(bookingManager);
    uiDashboard->setUICore(uiCore);
    uiDashboard->setUIMotorbike(uiMotorbike);
    uiDashboard->setUIBooking(uiBooking);
    
    // Set UI module references in UICore
    uiCore->setUIProfile(uiProfile);
    uiCore->setUIMotorbike(uiMotorbike);
    uiCore->setUIBooking(uiBooking);
    uiCore->setUIAdmin(uiAdmin);
    uiCore->setUIGuest(uiGuest);
    uiCore->setUIDashboard(uiDashboard);
}

/**
 * Set authentication system reference
 */
void UI::setAuth(Auth* auth) {
    this->auth = auth;
    setupModuleReferences();
}

/**
 * Set booking manager reference  
 */
void UI::setBookingManager(BookingManager* bookingManager) {
    this->bookingManager = bookingManager;
    setupModuleReferences();
}

/**
 * Display application welcome screen - delegates to UICore
 */
void UI::showWelcomeScreen() {
    if (uiCore) {
        uiCore->showWelcomeScreen();
    }
}

/**
 * Display and handle main menu selection - delegates to UICore
 */
int UI::showMainMenu() {
    if (uiCore) {
        return uiCore->showMainMenu();
    }
    return 5; // Default to exit
}

/**
 * Display guest-specific menu options - delegates to UICore
 */
void UI::showGuestMenu() {
    if (uiCore) {
        uiCore->showGuestMenu();
    }
}

/**
 * Display member-specific menu options - delegates to UICore
 */
void UI::showMemberMenu() {
    if (uiCore) {
        uiCore->showMemberMenu();
    }
}

/**
 * Display admin-specific menu options - delegates to UICore
 */
void UI::showAdminMenu() {
    if (uiCore) {
        uiCore->showAdminMenu();
    }
}
