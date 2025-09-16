#include "auth.h"
#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// ============================================================================
// PERSON CLASS IMPLEMENTATION
// ============================================================================

Person::Person(const string& name, const string& email, const string& phone, 
               const string& idType, const string& idNumber) 
    : fullName(name), email(email), phoneNumber(phone), idType(idType), idNumber(idNumber) {
}

// ============================================================================
// USER CLASS IMPLEMENTATION
// ============================================================================

User::User(const string& username, const string& password, const string& role,
           const string& fullName, const string& email, const string& phone,
           const string& idType, const string& idNumber, const string& licenseNumber,
           const string& licenseExpiry, double creditPoints, double rating,
           const string& license, bool isVerified, const string& verificationDate)
    : Person(fullName, email, phone, idType, idNumber),
      username(username), password(password), role(role), licenseNumber(licenseNumber),
      licenseExpiry(licenseExpiry), creditPoints(creditPoints), rating(rating),
      license(license), isVerified(isVerified), verificationDate(verificationDate) {
}

void User::displayInfo() const {
    cout << "=== USER PROFILE ===" << endl;
    cout << "Username: " << username << endl;
    cout << "Full Name: " << fullName << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Role: " << role << endl;
    cout << "Credit Points: " << creditPoints << endl;
    cout << "Rating: " << rating << endl;
    cout << "License: " << license << endl;
    cout << "Verified: " << (isVerified ? "Yes" : "No") << endl;
    if (isVerified) {
        cout << "Verification Date: " << verificationDate << endl;
    }
}

void User::setCreditPoints(double creditPoints) {
    if (creditPoints >= 0) {
        this->creditPoints = creditPoints;
    }
}

void User::setRating(double rating) {
    if (rating >= 0 && rating <= 5) {
        this->rating = rating;
    }
}

bool User::deductCreditPoints(double amount) {
    if (amount > 0 && creditPoints >= amount) {
        creditPoints -= amount;
        return true;
    }
    return false;
}

bool User::addCreditPoints(double amount) {
    if (amount > 0) {
        creditPoints += amount;
        return true;
    }
    return false;
}

bool User::hasValidLicense() const {
    // Simple validation - in real app, would check expiry date
    return !license.empty() && license != "N/A";
}

// ============================================================================
// AUTH CLASS IMPLEMENTATION
// ============================================================================

Auth::Auth() {
    filename = "account.txt";
    currentUser = nullptr;
    loadUsers();
    
    // Create default admin account if no users exist
    if (users.empty()) {
        User admin("admin", "admin123", "admin", "System Administrator", 
                  "admin@system.com", "0000000000", "Citizen ID", "ADMIN_ID",
                  "ADMIN_LICENSE", "2099-12-31", 1000.0, 5.0, "ADMIN_LICENSE", 
                  true, "2025-01-01");
        users.push_back(admin);
        saveUsers();
    }
}

Auth::~Auth() {
    if (currentUser != nullptr) {
        delete currentUser;
    }
}

void Auth::loadUsers() {
    ifstream file(filename);
    if (!file.is_open()) {
        return; // File doesn't exist yet, that's okay
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            // Trim each token
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 13) {
            User user;
            user.setUsername(tokens[0]);
            user.setPassword(tokens[1]);
            user.setRole(tokens[2]);
            user.setFullName(tokens[3]);
            user.setEmail(tokens[4]);
            user.setPhoneNumber(tokens[5]);
            user.setIdType(tokens[6]);
            user.setIdNumber(tokens[7]);
            user.setLicenseNumber(tokens[8]);
            user.setLicenseExpiry(tokens[9]);
            user.setCreditPoints(stod(tokens[10]));
            user.setRating(stod(tokens[11]));
            user.setLicense(tokens[12]);
            
            // Handle new verification fields with backward compatibility
            if (tokens.size() >= 15) {
                user.setIsVerified(tokens[13] == "1");
                user.setVerificationDate(tokens[14]);
            } else {
                user.setIsVerified(false);
                user.setVerificationDate("");
            }
            
            users.push_back(user);
        }
    }
    file.close();
}

void Auth::saveUsers() {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot save users to file." << endl;
        return;
    }
    
    // Write header
    file << "# Account Data Format: username|password|role|fullName|email|phone|idType|idNumber|licenseNumber|licenseExpiry|creditPoints|rating|license|isVerified|verificationDate" << endl;
    
    for (const User& user : users) {
        file << user.getUsername() << "|"
             << user.getPassword() << "|"
             << user.getRole() << "|"
             << user.getFullName() << "|"
             << user.getEmail() << "|"
             << user.getPhoneNumber() << "|"
             << user.getIdType() << "|"
             << user.getIdNumber() << "|"
             << user.getLicenseNumber() << "|"
             << user.getLicenseExpiry() << "|"
             << user.getCreditPoints() << "|"
             << user.getRating() << "|"
             << user.getLicense() << "|"
             << (user.getIsVerified() ? "1" : "0") << "|"
             << user.getVerificationDate() << endl;
    }
    file.close();
}

bool Auth::validateCredentials(const string& username, const string& password) {
    for (const User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;
        }
    }
    return false;
}

bool Auth::login() {
    string username, password;
    
    cout << "=== LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    password = hidePassword();
    cout << endl;
    
    if (validateCredentials(username, password)) {
        // Find the user and create a copy for currentUser
        for (const User& user : users) {
            if (user.getUsername() == username) {
                currentUser = new User(user);
                break;
            }
        }
        cout << "Login successful! Welcome, " << username << "!" << endl;
        return true;
    } else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

bool Auth::adminLogin() {
    string username, password;
    
    cout << "=== ADMIN LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    password = hidePassword();
    cout << endl;
    
    if (validateCredentials(username, password)) {
        // Find the user and check if they're admin
        for (const User& user : users) {
            if (user.getUsername() == username && user.isAdmin()) {
                currentUser = new User(user);
                cout << "Admin login successful! Welcome, " << username << "!" << endl;
                return true;
            }
        }
        cout << "Access denied. Admin privileges required." << endl;
        return false;
    } else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

bool Auth::registerUser() {
    string username, password, confirmPassword, fullName, email, phoneNumber, idType, idNumber, licenseNumber, licenseExpiry;
    
    cout << "=== REGISTRATION ===" << endl;
    cout << "Registration Requirements:" << endl;
    cout << "• PASSWORD: At least 8 characters, 1 uppercase, 1 lowercase, 1 number" << endl;
    cout << "• EMAIL: Valid email format (example@domain.com)" << endl;
    cout << "• PHONE: 10-11 digits only" << endl;
    cout << endl;
    
    // Check if username already exists
    cout << "Username: ";
    cin >> username;
    
    for (const User& user : users) {
        if (user.getUsername() == username) {
            cout << "Username already exists. Please choose another." << endl;
            return false;
        }
    }
    
    // Password validation
    do {
        cout << "Password: ";
        password = hidePassword();
        cout << endl;
        
        if (!validatePassword(password)) {
            cout << "Password does not meet requirements. Please try again." << endl;
        }
    } while (!validatePassword(password));
    
    cout << "Confirm Password: ";
    confirmPassword = hidePassword();
    cout << endl;
    
    if (password != confirmPassword) {
        cout << "Passwords do not match." << endl;
        return false;
    }
    
    cin.ignore();
    cout << "Full Name: ";
    getline(cin, fullName);
    
    // Email validation
    do {
        cout << "Email: ";
        getline(cin, email);
        
        if (!validateEmail(email)) {
            cout << "Invalid email format. Please try again." << endl;
        }
    } while (!validateEmail(email));
    
    // Phone validation
    do {
        cout << "Phone Number: ";
        getline(cin, phoneNumber);
        
        if (!validatePhoneNumber(phoneNumber)) {
            cout << "Invalid phone number. Please enter 10-11 digits only." << endl;
        }
    } while (!validatePhoneNumber(phoneNumber));
    
    cout << "ID Type (Citizen ID/Passport): ";
    getline(cin, idType);
    
    cout << "ID Number: ";
    getline(cin, idNumber);
    
    cout << "License Number: ";
    getline(cin, licenseNumber);
    
    cout << "License Expiry (YYYY-MM-DD): ";
    getline(cin, licenseExpiry);
    
    // Create new user with default values
    User newUser(username, password, "member", fullName, email, phoneNumber,
                idType, idNumber, licenseNumber, licenseExpiry, 20.0, 3.0, 
                licenseNumber, false, "");
    
    users.push_back(newUser);
    saveUsers();
    
    cout << "Registration successful! You have received 20 credit points and a default rating of 3.0." << endl;
    return true;
}

void Auth::logout() {
    if (currentUser != nullptr) {
        delete currentUser;
        currentUser = nullptr;
    }
    cout << "Logged out successfully." << endl;
}

User* Auth::getCurrentUser() {
    return currentUser;
}

bool Auth::isLoggedIn() {
    return currentUser != nullptr;
}

bool Auth::validatePassword(const string& password) {
    if (password.length() < 8) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false;
    
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

bool Auth::validateEmail(const string& email) {
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0) return false;
    
    size_t dotPos = email.find('.', atPos);
    if (dotPos == string::npos || dotPos == atPos + 1) return false;
    
    return dotPos < email.length() - 1;
}

bool Auth::validatePhoneNumber(const string& phone) {
    if (phone.length() < 10 || phone.length() > 11) return false;
    
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    
    return true;
}

bool Auth::updateProfile(const string& username, const string& fullName, 
                        const string& email, const string& phoneNumber) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            user.setFullName(fullName);
            user.setEmail(email);
            user.setPhoneNumber(phoneNumber);
            saveUsers();
            return true;
        }
    }
    return false;
}

bool Auth::changePassword(const string& username, const string& oldPassword, 
                         const string& newPassword) {
    for (User& user : users) {
        if (user.getUsername() == username && user.getPassword() == oldPassword) {
            if (validatePassword(newPassword)) {
                user.setPassword(newPassword);
                saveUsers();
                return true;
            }
        }
    }
    return false;
}

bool Auth::topUpCreditPoints(const string& username, double amount) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            return user.addCreditPoints(amount);
        }
    }
    return false;
}

bool Auth::deductCreditPoints(const string& username, double amount) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            bool success = user.deductCreditPoints(amount);
            if (success) {
                saveUsers();
            }
            return success;
        }
    }
    return false;
}

void Auth::displayProfile(const string& username, BookingManager* bookingManager) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            user.displayInfo();
            return;
        }
    }
    cout << "User not found." << endl;
}

string Auth::hidePassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    return password;
}

double Auth::getUserRenterRating(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return user.getRating();
        }
    }
    return 0.0;
}

double Auth::getUserCreditPoints(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return user.getCreditPoints();
        }
    }
    return 0.0;
}

string Auth::getUserLicenseExpiry(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return user.getLicenseExpiry();
        }
    }
    return "";
}

vector<User> Auth::getAllUsers() {
    return users;
}

bool Auth::verifyIdentity(const string& username) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            cout << "=== IDENTITY VERIFICATION ===" << endl;
            cout << "Please provide the following information to verify your identity:" << endl;
            
            string input;
            bool verified = true;
            
            // Verify full name
            cout << "Full Name: ";
            cin.ignore();
            getline(cin, input);
            if (input != user.getFullName()) {
                cout << "Full name does not match records." << endl;
                verified = false;
            }
            
            // Verify license number
            cout << "License Number: ";
            getline(cin, input);
            if (input != user.getLicenseNumber()) {
                cout << "License number does not match records." << endl;
                verified = false;
            }
            
            // Verify email domain
            cout << "Email Domain (e.g., gmail.com): ";
            getline(cin, input);
            // Normalize both the user-entered value and stored email domain
            auto trim = [](string &s){
                size_t start = s.find_first_not_of(" \t\r\n");
                size_t end = s.find_last_not_of(" \t\r\n");
                if (start == string::npos) { s.clear(); return; }
                s = s.substr(start, end - start + 1);
            };
            auto toLowerInPlace = [](string &s){
                transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return (char)tolower(c); });
            };
            // If user typed a full email, keep only the part after '@'
            trim(input);
            size_t atPosInput = input.find('@');
            if (atPosInput != string::npos) input = input.substr(atPosInput + 1);
            toLowerInPlace(input);
            string emailDomain = user.getEmail().substr(user.getEmail().find('@') + 1);
            trim(emailDomain);
            toLowerInPlace(emailDomain);
            if (input != emailDomain) {
                cout << "Email domain does not match records." << endl;
                verified = false;
            }
            
            // Verify last 4 digits of phone
            cout << "Last 4 digits of phone number: ";
            getline(cin, input);
            string lastFour = user.getPhoneNumber().substr(user.getPhoneNumber().length() - 4);
            if (input != lastFour) {
                cout << "Phone number does not match records." << endl;
                verified = false;
            }
            
            if (verified) {
                user.setIsVerified(true);
                user.setVerificationDate("2025-01-01"); // In real app, would use current date
                saveUsers();
                cout << "Identity verification successful! You are now verified." << endl;
                return true;
            } else {
                cout << "Identity verification failed. Please try again later." << endl;
                return false;
            }
        }
    }
    return false;
}

bool Auth::isUserVerified(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return user.getIsVerified();
        }
    }
    return false;
}

void Auth::displayVerificationStatus(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            cout << "=== VERIFICATION STATUS ===" << endl;
            cout << "Username: " << username << endl;
            cout << "Status: " << (user.getIsVerified() ? "VERIFIED" : "NOT VERIFIED") << endl;
            if (user.getIsVerified()) {
                cout << "Verification Date: " << user.getVerificationDate() << endl;
            }
            return;
        }
    }
    cout << "User not found." << endl;
}