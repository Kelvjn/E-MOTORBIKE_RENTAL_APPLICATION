#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <limits>

// Base class for all users
class Person {
protected:
    std::string fullName;
    std::string email;
    std::string phoneNumber;
    std::string idType; // "Citizen ID" or "Passport"
    std::string idNumber;
    
public:
    // Constructor
    Person(const std::string& name = "", const std::string& email = "", 
           const std::string& phone = "", const std::string& idType = "", 
           const std::string& idNumber = "");
    
    // Virtual destructor for proper inheritance
    virtual ~Person() = default;
    
    // Pure virtual function - must be implemented by derived classes
    virtual void displayInfo() const = 0;
    
    // Getters
    std::string getFullName() const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getIdType() const { return idType; }
    std::string getIdNumber() const { return idNumber; }
    
    // Setters with validation
    void setFullName(const std::string& name) { fullName = name; }
    void setEmail(const std::string& email) { this->email = email; }
    void setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
    void setIdType(const std::string& type) { idType = type; }
    void setIdNumber(const std::string& number) { idNumber = number; }
};

// User class inherits from Person
class User : public Person {
private:
    std::string username;
    std::string password;
    std::string role; // "member" or "admin"
    std::string licenseNumber;
    std::string licenseExpiry;
    double creditPoints;
    double rating;
    std::string license;
    bool isVerified; // Identity verification status
    std::string verificationDate; // Date when verification was completed
    
public:
    // Constructor
    User(const std::string& username = "", const std::string& password = "", 
         const std::string& role = "member", const std::string& fullName = "",
         const std::string& email = "", const std::string& phone = "",
         const std::string& idType = "", const std::string& idNumber = "",
         const std::string& licenseNumber = "", const std::string& licenseExpiry = "",
         double creditPoints = 20.0, double rating = 3.0, const std::string& license = "",
         bool isVerified = false, const std::string& verificationDate = "");
    
    // Destructor
    ~User() override = default;
    
    // Override pure virtual function from Person
    void displayInfo() const override;
    
    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getRole() const { return role; }
    std::string getLicenseNumber() const { return licenseNumber; }
    std::string getLicenseExpiry() const { return licenseExpiry; }
    double getCreditPoints() const { return creditPoints; }
    double getRating() const { return rating; }
    std::string getLicense() const { return license; }
    bool getIsVerified() const { return isVerified; }
    std::string getVerificationDate() const { return verificationDate; }
    
    // Setters with validation
    void setUsername(const std::string& username) { this->username = username; }
    void setPassword(const std::string& password) { this->password = password; }
    void setRole(const std::string& role) { this->role = role; }
    void setLicenseNumber(const std::string& licenseNumber) { this->licenseNumber = licenseNumber; }
    void setLicenseExpiry(const std::string& licenseExpiry) { this->licenseExpiry = licenseExpiry; }
    void setCreditPoints(double creditPoints);
    void setRating(double rating);
    void setLicense(const std::string& license) { this->license = license; }
    void setIsVerified(bool isVerified) { this->isVerified = isVerified; }
    void setVerificationDate(const std::string& date) { verificationDate = date; }
    
    // Business logic methods
    bool deductCreditPoints(double amount);
    bool addCreditPoints(double amount);
    bool hasValidLicense() const;
    bool isAdmin() const { return role == "admin"; }
    bool isMember() const { return role == "member"; }
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
    // Constructor
    Auth();
    
    // Destructor
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
    
    // Profile management
    bool updateProfile(const std::string& username, const std::string& fullName, 
                      const std::string& email, const std::string& phoneNumber);
    bool changePassword(const std::string& username, const std::string& oldPassword, 
                       const std::string& newPassword);
    bool topUpCreditPoints(const std::string& username, double amount);
    bool deductCreditPoints(const std::string& username, double amount);
    void displayProfile(const std::string& username, class BookingManager* bookingManager = nullptr);
    
    // Utility functions
    std::string hidePassword();
    
    // User data access methods for search functionality
    double getUserRenterRating(const std::string& username);
    double getUserCreditPoints(const std::string& username);
    std::string getUserLicenseExpiry(const std::string& username);
    
    // Admin methods
    std::vector<User> getAllUsers(); // Get all users for admin view
    
    // Identity verification methods
    bool verifyIdentity(const std::string& username);
    bool isUserVerified(const std::string& username);
    void displayVerificationStatus(const std::string& username);
};

#endif