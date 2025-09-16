#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <vector>

// Forward declaration
class BookingManager;

// Simple User class
class User {
private:
    std::string username;
    std::string password;
    std::string role;
    std::string fullName;
    std::string email;
    std::string phoneNumber;
    std::string idType; // "Citizen ID" or "Passport"
    std::string idNumber;
    std::string licenseNumber; // Optional
    std::string licenseExpiry; // Optional
    double creditPoints;
    double rating;

public:
    // Constructor
    User(const std::string& username = "", const std::string& password = "", 
         const std::string& role = "member", const std::string& fullName = "",
         const std::string& email = "", const std::string& phone = "",
         const std::string& idType = "", const std::string& idNumber = "",
         const std::string& licenseNumber = "", const std::string& licenseExpiry = "",
         double creditPoints = 20.0, double rating = 3.0);

    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getRole() const { return role; }
    std::string getFullName() const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getIdType() const { return idType; }
    std::string getIdNumber() const { return idNumber; }
    std::string getLicenseNumber() const { return licenseNumber; }
    std::string getLicenseExpiry() const { return licenseExpiry; }
    double getCreditPoints() const { return creditPoints; }
    double getRating() const { return rating; }

    // Setters
    void setFullName(const std::string& name) { fullName = name; }
    void setEmail(const std::string& e) { email = e; }
    void setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
    void setCreditPoints(double cp) { creditPoints = cp; }
    
    // License validation
    bool hasValidLicense() const;
};

// Simple Auth class
class Auth {
private:
    std::vector<User> users;
    User* currentUser;

public:
    // Constructor
    Auth();
    
    // Destructor
    ~Auth();

    // Core authentication methods
    bool login();
    bool adminLogin();
    bool registerUser();
    void logout();
    User* getCurrentUser();
    
    // User management
    std::string hidePassword();
    bool validateEmail(const std::string& email);
    bool validatePhoneNumber(const std::string& phone);
    bool validatePassword(const std::string& password);
    bool updateProfile(const std::string& username, const std::string& fullName, 
                      const std::string& email, const std::string& phoneNumber);
    bool changePassword(const std::string& username, const std::string& oldPassword, 
                       const std::string& newPassword);
    bool topUpCreditPoints(const std::string& username, double amount);
    bool deductCreditPoints(const std::string& username, double amount);
    void displayProfile(const std::string& username, BookingManager* bookingManager = nullptr);
    
    // User data access methods
    double getUserRenterRating(const std::string& username);
    double getUserCreditPoints(const std::string& username);
    std::string getUserLicenseExpiry(const std::string& username);
    
    // Admin methods
    std::vector<User> getAllUsers();
    
    // Identity verification
    bool verifyIdentity(const std::string& username);
    void displayVerificationStatus(const std::string& username);
};

#endif
