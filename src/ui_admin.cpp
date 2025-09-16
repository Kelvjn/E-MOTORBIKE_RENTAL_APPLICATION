/**
 * E-MOTORBIKE RENTAL APPLICATION
 * Admin UI Implementation
 * 
 * This file implements the UIAdmin class methods for handling administrative
 * functions including system monitoring and data viewing.
 * 
 * @author Group 5 - EEET2482/EEET2653/COSC2082/COSC2721
 * @version 1.0
 * @date Semester 2 2025
 */

#include "ui_admin.h"
#include "ui_core.h"
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
UIAdmin::UIAdmin() : auth(nullptr), bookingManager(nullptr), uiCore(nullptr) {
}

/**
 * Destructor
 */
UIAdmin::~UIAdmin() {
    // Note: We don't delete the pointers as they are managed externally
}

/**
 * Displays all member profiles for admin view.
 * Shows comprehensive information about all registered members.
 */
void UIAdmin::viewAllMemberProfiles() {
    if (!auth || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
    cout << "=== ALL MEMBER PROFILES ===\n\n";
    
    vector<User> allUsers = auth->getAllUsers();
    
    if (allUsers.empty()) {
        cout << "No users found in the system.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays all motorbike listings for admin view.
 * Shows comprehensive information about all listed motorbikes.
 */
void UIAdmin::viewAllMotorbikeListings() {
    if (!bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
    cout << "=== ALL MOTORBIKE LISTINGS ===\n\n";
    
    vector<Motorbike> allMotorbikes = bookingManager->getAvailableMotorbikes();
    
    if (allMotorbikes.empty()) {
        cout << "No motorbikes found in the system.\n";
        uiCore->pauseScreen();
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
    
    uiCore->pauseScreen();
}

/**
 * Displays comprehensive system statistics for admin view.
 * Shows detailed information about users, motorbikes, and bookings.
 */
void UIAdmin::showSystemStatistics() {
    if (!auth || !bookingManager || !uiCore) {
        cout << "Error: Required components not available.\n";
        if (uiCore) uiCore->pauseScreen();
        return;
    }
    
    uiCore->clearScreen();
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
    if (totalMotorbikes > 0) {
        cout << "System Utilization: " << fixed << setprecision(1) << ((double)listedMotorbikes / totalMotorbikes * 100) << "%\n";
    }
    if (totalBookings > 0) {
        cout << "Booking Success Rate: " << fixed << setprecision(1) << ((double)approvedBookings / totalBookings * 100) << "%\n";
    }
    
    uiCore->pauseScreen();
}
