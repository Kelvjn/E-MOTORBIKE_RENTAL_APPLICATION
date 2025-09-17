#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration
class BookingManager;

// Simple User class
class User {
private:
    string username;
    string password;
    string role;
    string fullName;
    string email;
    string phoneNumber;
    string idType; // "Citizen ID" or "Passport"
    string idNumber;
    string licenseNumber; // Optional
    string licenseExpiry; // Optional
    double creditPoints;
    double rating;

public:
    // Constructor
    User(const string& username = "", const string& password = "", 
         const string& role = "member", const string& fullName = "",
         const string& email = "", const string& phone = "",
         const string& idType = "", const string& idNumber = "",
         const string& licenseNumber = "", const string& licenseExpiry = "",
         double creditPoints = 20.0, double rating = 3.0);

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }
    string getIdType() const { return idType; }
    string getIdNumber() const { return idNumber; }
    string getLicenseNumber() const { return licenseNumber; }
    string getLicenseExpiry() const { return licenseExpiry; }
    double getCreditPoints() const { return creditPoints; }
    double getRating() const { return rating; }

    // Setters
    void setFullName(const string& name) { fullName = name; }
    void setEmail(const string& e) { email = e; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setCreditPoints(double cp) { creditPoints = cp; }
    
    // License validation
    bool hasValidLicense() const;
};

// Simple Auth class
class Auth {
private:
    vector<User> users;
    User* currentUser;
    string accountFilename;
    
    // File I/O methods
    void loadUsers();
    void saveUsers();

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
    string hidePassword();
    bool validateEmail(const string& email);
    bool validatePhoneNumber(const string& phone);
    bool validatePassword(const string& password);
    bool updateProfile(const string& username, const string& fullName, 
                      const string& email, const string& phoneNumber);
    bool changePassword(const string& username, const string& oldPassword, 
                       const string& newPassword);
    bool topUpCreditPoints(const string& username, double amount);
    bool deductCreditPoints(const string& username, double amount);
    void displayProfile(const string& username, BookingManager* bookingManager = nullptr);
    
    // User data access methods
    double getUserRenterRating(const string& username);
    double getUserCreditPoints(const string& username);
    string getUserLicenseExpiry(const string& username);
    
    // Admin methods
    vector<User> getAllUsers();
    
    // Identity verification
    bool verifyIdentity(const string& username);
    void displayVerificationStatus(const string& username);
};

#endif
