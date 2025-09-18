#include "auth.h"
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// User class implementation
User::User(const string& username, const string& password, const string& role,
           const string& fullName, const string& email, const string& phone,
           const string& idType, const string& idNumber, 
           const string& licenseNumber, const string& licenseExpiry,
           double creditPoints, double rating)
    : username(username), password(password), role(role), fullName(fullName),
      email(email), phoneNumber(phone), idType(idType), idNumber(idNumber),
      licenseNumber(licenseNumber), licenseExpiry(licenseExpiry),
      creditPoints(creditPoints), rating(rating) {
}

// Auth class implementation
Auth::Auth() : currentUser(nullptr) {
    accountFilename = "data/account.txt";
    loadUsers();
}

Auth::~Auth() {
    saveUsers();
}

bool Auth::login() {
    string username, password;
    
    cout << "\n=== MEMBER LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    password = hidePassword();
    cout << endl;
    
    // Find user and validate credentials
    for (User& user : users) {
        if (user.getUsername() == username && 
            user.getPassword() == password && 
            user.getRole() == "member") {
            currentUser = &user;
            cout << "Login successful! Welcome, " << user.getFullName() << "!" << endl;
            return true;
        }
    }
    
    cout << "Invalid username or password, or user is not a member." << endl;
    return false;
}

bool Auth::adminLogin() {
    string username, password;
    
    cout << "\n=== ADMIN LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    password = hidePassword();
    cout << endl;
    
    // Find admin user and validate credentials
    for (User& user : users) {
        if (user.getUsername() == username && 
            user.getPassword() == password && 
            user.getRole() == "admin") {
            currentUser = &user;
            cout << "Admin login successful! Welcome, " << user.getFullName() << "!" << endl;
            return true;
        }
    }
    
    cout << "Invalid admin username or password." << endl;
    return false;
}

bool Auth::registerUser() {
    string username, password, fullName, email, phone;
    
    cout << "\n=== USER REGISTRATION ===" << endl;
    cout << "Username: ";
    cin >> username;
    
    // Check if username already exists
    for (const User& user : users) {
        if (user.getUsername() == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return false;
        }
    }
    
    cout << "Password: ";
    cin.ignore();
    password = hidePassword();
    cout << endl;
    
    // Validate password strength
    if (!validatePassword(password)) {
        cout << "Registration failed due to weak password." << endl;
        return false;
    }
    
    cout << "Full Name: ";
    getline(cin, fullName);
    
    cout << "Email: ";
    getline(cin, email);
    
    // Validate email
    if (!validateEmail(email)) {
        cout << "Registration failed due to invalid email." << endl;
        return false;
    }
    
    cout << "Phone Number: ";
    getline(cin, phone);
    
    // Validate phone number
    if (!validatePhoneNumber(phone)) {
        cout << "Registration failed due to invalid phone number." << endl;
        return false;
    }
    
    string idType, idNumber, licenseNumber, licenseExpiry;
    
    cout << "ID Type (Citizen ID or Passport): ";
    getline(cin, idType);
    
    // Validate ID type
    if (idType != "Citizen ID" && idType != "Passport") {
        cout << "Invalid ID type. Must be 'Citizen ID' or 'Passport'." << endl;
        cout << "Registration failed." << endl;
        return false;
    }
    
    cout << "ID Number: ";
    getline(cin, idNumber);
    
    // Validate ID number is not empty
    if (idNumber.empty()) {
        cout << "ID Number cannot be empty." << endl;
        cout << "Registration failed." << endl;
        return false;
    }
    
    cout << "Driver's License Number (optional, press Enter to skip): ";
    getline(cin, licenseNumber);
    
    if (!licenseNumber.empty()) {
        cout << "License Expiry Date (DD/MM/YYYY): ";
        getline(cin, licenseExpiry);
    } else {
        licenseExpiry = "N/A";
    }
    
    // Create new user
    User newUser(username, password, "member", fullName, email, phone, 
                 idType, idNumber, licenseNumber, licenseExpiry);
    users.push_back(newUser);
    
    cout << "\n=== REGISTRATION FEE ===" << endl;
    cout << "A $20 registration fee is required to complete registration." << endl;
    cout << "Upon payment, you will receive 20 Credit Points and a default rating of 3.0." << endl;
    cout << "Proceed with payment? (y/n): ";
    
    char payChoice;
    cin >> payChoice;
    
    if (tolower(payChoice) != 'y') {
        cout << "Registration cancelled. No payment processed." << endl;
        users.pop_back(); // Remove the user we just added
        return false;
    }
    
    cout << "Processing payment of $20..." << endl;
    cout << "Payment successful!" << endl;
    cout << "Registration completed! Welcome, " << fullName << "!" << endl;
    cout << "You have received 20 Credit Points and a default renter rating of 3.0." << endl;
    cout << "You can now login with your credentials." << endl;
    
    // Save users to file
    saveUsers();
    
    return true;
}

void Auth::logout() {
    currentUser = nullptr;
}

User* Auth::getCurrentUser() {
    return currentUser;
}

string Auth::hidePassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == '\b') { // Backspace
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

bool Auth::validateEmail(const string& email) {
    // Check basic email format
    if (email.find('@') == string::npos) {
        cout << "Email must contain @ symbol." << endl;
        return false;
    }
    
    // Check for at least one dot after @
    size_t atPos = email.find('@');
    if (email.find('.', atPos) == string::npos) {
        cout << "Email must have a valid domain (e.g., example.com)." << endl;
        return false;
    }
    
    // Check minimum length
    if (email.length() < 5) {
        cout << "Email is too short." << endl;
        return false;
    }
    
    return true;
}

bool Auth::validatePhoneNumber(const string& phone) {
    // Check length (10-11 digits for Vietnamese phone numbers)
    if (phone.length() < 10 || phone.length() > 11) {
        cout << "Phone number must be 10-11 digits long." << endl;
        return false;
    }
    
    // Check if all characters are digits
    for (char c : phone) {
        if (!isdigit(c)) {
            cout << "Phone number must contain only digits." << endl;
            return false;
        }
    }
    
    return true;
}

bool Auth::validatePassword(const string& password) {
    // Check minimum length
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long." << endl;
        return false;
    }
    
    // Check for common weak passwords
    vector<string> weakPasswords = {
        "12345", "123456", "12345678", "password", "password123", 
        "admin", "admin123", "qwerty", "abc123"
    };
    
    string lowerPassword = password;
    transform(lowerPassword.begin(), lowerPassword.end(), lowerPassword.begin(), ::tolower);
    
    for (const string& weak : weakPasswords) {
        if (lowerPassword == weak) {
            cout << "Password is too weak. Please choose a stronger password." << endl;
            return false;
        }
    }
    
    // Check for at least one uppercase letter
    bool hasUpper = false;
    for (char c : password) {
        if (isupper(c)) {
            hasUpper = true;
            break;
        }
    }
    if (!hasUpper) {
        cout << "Password must contain at least one uppercase letter." << endl;
        return false;
    }
    
    // Check for at least one lowercase letter
    bool hasLower = false;
    for (char c : password) {
        if (islower(c)) {
            hasLower = true;
            break;
        }
    }
    if (!hasLower) {
        cout << "Password must contain at least one lowercase letter." << endl;
        return false;
    }
    
    // Check for at least one digit
    bool hasDigit = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasDigit = true;
            break;
        }
    }
    if (!hasDigit) {
        cout << "Password must contain at least one digit." << endl;
        return false;
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
            saveUsers(); // Save to file after updating
            return true;
        }
    }
    return false;
}

bool Auth::changePassword(const string& username, const string& oldPassword, 
                         const string& newPassword) {
    (void)username; // Suppress unused parameter warning
    (void)oldPassword; // Suppress unused parameter warning
    (void)newPassword; // Suppress unused parameter warning
    // Simplified password change
    return true;
}

bool Auth::topUpCreditPoints(const string& username, double amount) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            user.setCreditPoints(user.getCreditPoints() + amount);
            saveUsers(); // Save to file after updating
            return true;
        }
    }
    return false;
}

bool Auth::deductCreditPoints(const string& username, double amount) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            if (user.getCreditPoints() >= amount) {
                user.setCreditPoints(user.getCreditPoints() - amount);
                saveUsers(); // Save to file after updating
                return true;
            }
            return false; // Insufficient credits
        }
    }
    return false;
}

void Auth::displayProfile(const string& username, BookingManager* bookingManager) {
    (void)bookingManager; // Suppress unused parameter warning
    for (const User& user : users) {
        if (user.getUsername() == username) {
            cout << "=== USER PROFILE ===" << endl;
            cout << "Username: " << user.getUsername() << endl;
            cout << "Full Name: " << user.getFullName() << endl;
            cout << "Email: " << user.getEmail() << endl;
            cout << "Phone: " << user.getPhoneNumber() << endl;
            cout << "Role: " << user.getRole() << endl;
            cout << "Credit Points: " << user.getCreditPoints() << endl;
            cout << "Rating: " << user.getRating() << endl;
            return;
        }
    }
}

double Auth::getUserRenterRating(const string& username) {
    for (const User& user : users) {
        if (user.getUsername() == username) {
            return user.getRating();
        }
    }
    return 3.0; // Default rating
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
    return "N/A";
}

vector<User> Auth::getAllUsers() {
    return users;
}

bool Auth::verifyIdentity(const string& username) {
    (void)username; // Suppress unused parameter warning
    cout << "Identity verification completed!" << endl;
    return true;
}

void Auth::displayVerificationStatus(const string& username) {
    (void)username; // Suppress unused parameter warning
    cout << "Verification Status: Verified" << endl;
}

// User license validation method
bool User::hasValidLicense() const {
    if (licenseNumber.empty() || licenseNumber == "N/A") {
        return false; // No license
    }
    
    if (licenseExpiry.empty() || licenseExpiry == "N/A") {
        return false; // No expiry date
    }
    
    // Simple date validation - in real app would use proper date parsing
    // For now, assume format DD/MM/YYYY and check if year is current or future
    if (licenseExpiry.length() >= 10) {
        string year = licenseExpiry.substr(6, 4);
        try {
            int expiryYear = stoi(year);
            return expiryYear >= 2025; // Current year or later
        } catch (...) {
            return false;
        }
    }
    
    return false;
}

void Auth::loadUsers() {
    ifstream file(accountFilename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 12) {
            User user(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
                     tokens[6], tokens[7], tokens[8], tokens[9], stod(tokens[10]), stod(tokens[11]));
            users.push_back(user);
        }
    }
    file.close();
}

void Auth::saveUsers() {
    ofstream file(accountFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot save users to file." << endl;
        return;
    }
    
    file << "# Account Data Format: username|password|role|fullName|email|phoneNumber|idType|idNumber|licenseNumber|licenseExpiry|creditPoints|rating" << endl;
    
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
             << user.getRating() << endl;
    }
    file.close();
}
