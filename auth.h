#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct User {
    std::string username;
    std::string password;
    std::string role; // "member" or "admin"
    std::string fullName;
    std::string email;
    std::string phoneNumber;
    std::string idType; // "Citizen ID" or "Passport"
    std::string idNumber;
    std::string licenseNumber;
    std::string licenseExpiry;
    double creditPoints;
    double rating;
    std::string license;
};

class Auth {
private:
    std::vector<User> users;
    User* currentUser;
    std::string filename;
    
    void loadUsers();
    void saveUsers();
    bool validateCredentials(const std::string& username, const std::string& password);
    
public:
    Auth();
    ~Auth();
    
    bool login();
    bool adminLogin();
    bool registerUser();
    void logout();
    User* getCurrentUser();
    bool isLoggedIn();
    bool validatePassword(const std::string& password);
    bool validateEmail(const std::string& email);
    bool validatePhoneNumber(const std::string& phone);
    std::vector<User> getAllUsers(); // Admin function to get all users
    
    // Profile management
    bool updateProfile(const std::string& username, const std::string& fullName, 
                      const std::string& email, const std::string& phoneNumber);
    bool changePassword(const std::string& username, const std::string& oldPassword, 
                       const std::string& newPassword);
    bool topUpCreditPoints(const std::string& username, double amount);
    void displayProfile(const std::string& username, class BookingManager* bookingManager = nullptr);
    
    // Utility functions
    std::string hidePassword();
};

#endif
