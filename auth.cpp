#include "auth.h"
#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <limits>

using namespace std;

Auth::Auth() {
    filename = "account.txt";
    currentUser = nullptr;
    loadUsers();
    
    // Create default admin account if no users exist
    if (users.empty()) {
        User admin;
        admin.username = "admin";
        admin.password = "admin123";
        admin.role = "admin";
        admin.fullName = "System Administrator";
        admin.email = "admin@system.com";
        admin.phoneNumber = "0000000000";
        admin.idType = "Citizen ID";
        admin.idNumber = "ADMIN_ID";
        admin.licenseNumber = "ADMIN_LICENSE";
        admin.licenseExpiry = "2099-12-31";
        admin.creditPoints = 1000.0;
        admin.rating = 5.0;
        admin.license = "ADMIN_LICENSE";
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
        if (line.empty()) continue;
        if (line[0] == '#') continue; // Skip format/comment lines
        
        stringstream ss(line);
        User user;
        
        // Initialize with default values
        user.fullName = "";
        user.email = "";
        user.phoneNumber = "";
        user.idType = "Citizen ID";
        user.idNumber = "";
        user.licenseNumber = "";
        user.licenseExpiry = "";
        
        getline(ss, user.username, '|');
        getline(ss, user.password, '|');
        getline(ss, user.role, '|');
        
        // Check if this is old format (6 fields) or new format (13 fields)
        string nextField;
        getline(ss, nextField, '|');
        
        // Try to convert to double to check if it's creditPoints (old format)
        try {
            user.creditPoints = stod(nextField);
            // This is old format, so we need to read the remaining fields
            string temp;
            getline(ss, temp, '|');
            try {
                user.rating = stod(temp);
            } catch (const std::invalid_argument& e) {
                user.rating = 3.0; // Default rating
            }
            getline(ss, user.license, '|');
            
            // Set default values for new fields
            if (user.role == "admin") {
                user.fullName = "System Administrator";
                user.email = "admin@system.com";
                user.phoneNumber = "0000000000";
                user.idType = "Citizen ID";
                user.idNumber = "ADMIN_ID";
                user.licenseNumber = "ADMIN_LICENSE";
                user.licenseExpiry = "2099-12-31";
            }
        } catch (const std::invalid_argument&) {
            // This is new format, so nextField is actually fullName
            user.fullName = nextField;
            getline(ss, user.email, '|');
            getline(ss, user.phoneNumber, '|');
            getline(ss, user.idType, '|');
            getline(ss, user.idNumber, '|');
            getline(ss, user.licenseNumber, '|');
            getline(ss, user.licenseExpiry, '|');
            
            string temp;
            getline(ss, temp, '|');
            try {
                user.creditPoints = stod(temp);
            } catch (const std::invalid_argument& e) {
                user.creditPoints = 0.0; // Default value
            }
            
            getline(ss, temp, '|');
            try {
                user.rating = stod(temp);
            } catch (const std::invalid_argument& e) {
                user.rating = 3.0; // Default rating
            }
            
            getline(ss, user.license, '|');
        }
        
        users.push_back(user);
    }
    
    file.close();
}

void Auth::saveUsers() {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open account.txt for writing\n";
        return;
    }
    
    for (const User& user : users) {
        file << user.username << "|"
             << user.password << "|"
             << user.role << "|"
             << user.fullName << "|"
             << user.email << "|"
             << user.phoneNumber << "|"
             << user.idType << "|"
             << user.idNumber << "|"
             << user.licenseNumber << "|"
             << user.licenseExpiry << "|"
             << user.creditPoints << "|"
             << user.rating << "|"
             << user.license << "\n";
    }
    
    file.close();
}

string Auth::hidePassword() {
    string password;
    char ch;
    
    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter key
            break;
        } else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    
    return password;
}

bool Auth::validateCredentials(const string& username, const string& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

bool Auth::login() {
    string username, password;
    
    cout << "Enter username: ";
    cin >> username;
    
    cout << "Enter password: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    password = hidePassword();
    cout << endl;
    
    if (validateCredentials(username, password)) {
        // Find the user and set as current user
        for (const User& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = new User(user);
                cout << "\nYou have successfully logged in.\n\n";
                return true;
            }
        }
    } else {
        cout << "\nInvalid username or password.\n\n";
    }
    
    return false;
}

bool Auth::adminLogin() {
    string username, password;
    
    cout << "Enter admin username: ";
    cin >> username;
    
    cout << "Enter admin password: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    password = hidePassword();
    cout << endl;
    
    if (validateCredentials(username, password)) {
        // Check if user is admin
        for (const User& user : users) {
            if (user.username == username && user.password == password) {
                if (user.role == "admin") {
                    currentUser = new User(user);
                    cout << "\nYou have successfully logged in as Admin.\n\n";
                    return true;
                } else {
                    cout << "\nAccess denied. Admin privileges required.\n\n";
                    return false;
                }
            }
        }
    } else {
        cout << "\nInvalid admin credentials.\n\n";
    }
    
    return false;
}

bool Auth::registerUser() {
    string username, password, confirmPassword, fullName, email, phoneNumber;
    string idType, idNumber, licenseNumber, licenseExpiry;
    
    cout << "\n=== MEMBER REGISTRATION ===\n";
    cout << "Registration fee: $20\n";
    cout << "You will receive: 20 CPs and default rating of 3.0\n\n";
    
    // Username
    cout << "Enter username: ";
    cin >> username;
    
    // Check if username already exists
    for (const User& user : users) {
        if (user.username == username) {
            cout << "Username already exists. Please choose another.\n";
            return false;
        }
    }
    
    // Password
    cout << "Enter password: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    password = hidePassword();
    cout << endl;
    
    if (!validatePassword(password)) {
        return false;
    }
    
    cout << "Confirm password: ";
    confirmPassword = hidePassword();
    cout << endl;
    
    if (password != confirmPassword) {
        cout << "Passwords do not match.\n";
        return false;
    }
    
    // Full name
    cout << "Enter full name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, fullName);
    
    // Email
    cout << "Enter email: ";
    cin >> email;
    if (!validateEmail(email)) {
        return false;
    }
    
    // Phone number
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    if (!validatePhoneNumber(phoneNumber)) {
        return false;
    }
    
    // ID type and number
    cout << "Enter ID type (1 for Citizen ID, 2 for Passport): ";
    int idChoice;
    cin >> idChoice;
    if (idChoice == 1) {
        idType = "Citizen ID";
    } else if (idChoice == 2) {
        idType = "Passport";
    } else {
        cout << "Invalid choice. Please select 1 or 2.\n";
        return false;
    }
    
    cout << "Enter " << idType << " number: ";
    cin >> idNumber;
    
    // Driver's license (optional)
    cout << "Do you have a driver's license? (y/n): ";
    char hasLicense;
    cin >> hasLicense;
    
    if (tolower(hasLicense) == 'y') {
        cout << "Enter driver's license number: ";
        cin >> licenseNumber;
        cout << "Enter license expiry date (YYYY-MM-DD): ";
        cin >> licenseExpiry;
    } else {
        licenseNumber = "N/A";
        licenseExpiry = "N/A";
    }
    
    // Create new user
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.role = "member";
    newUser.fullName = fullName;
    newUser.email = email;
    newUser.phoneNumber = phoneNumber;
    newUser.idType = idType;
    newUser.idNumber = idNumber;
    newUser.licenseNumber = licenseNumber;
    newUser.licenseExpiry = licenseExpiry;
    newUser.creditPoints = 20.0; // Starting credit points as per requirement
    newUser.rating = 3.0; // Default rating as per requirement
    newUser.license = licenseNumber; // For backward compatibility
    
    users.push_back(newUser);
    saveUsers();
    
    cout << "\n=== REGISTRATION SUCCESSFUL ===\n";
    cout << "Welcome " << fullName << "!\n";
    cout << "Your account has been created with:\n";
    cout << "- 20 Credit Points\n";
    cout << "- Default rating of 3.0\n";
    cout << "- Registration fee: $20\n\n";
    
    return true;
}

void Auth::logout() {
    if (currentUser != nullptr) {
        delete currentUser;
        currentUser = nullptr;
    }
    cout << "Logged out successfully.\n";
}

User* Auth::getCurrentUser() {
    return currentUser;
}

bool Auth::isLoggedIn() {
    return currentUser != nullptr;
}

bool Auth::validatePassword(const string& password) {
    // Password must be at least 8 characters long
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long.\n";
        return false;
    }
    
    // Check for weak passwords
    vector<string> weakPasswords = {
        "12345678", "password", "qwertyui", "admin123", "letmein", 
        "welcome", "monkey", "dragon", "master", "hello123"
    };
    
    for (const string& weak : weakPasswords) {
        if (password == weak) {
            cout << "Password is too weak. Please choose a stronger password.\n";
            return false;
        }
    }
    
    // Check if password contains at least one uppercase, one lowercase, and one digit
    bool hasUpper = false, hasLower = false, hasDigit = false;
    
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    
    if (!hasUpper || !hasLower || !hasDigit) {
        cout << "Password must contain at least one uppercase letter, one lowercase letter, and one digit.\n";
        return false;
    }
    
    return true;
}

bool Auth::validateEmail(const string& email) {
    // Basic email validation
    if (email.find('@') == string::npos || email.find('.') == string::npos) {
        cout << "Invalid email format.\n";
        return false;
    }
    
    if (email.find('@') == 0 || email.find('@') == email.length() - 1) {
        cout << "Invalid email format.\n";
        return false;
    }
    
    return true;
}

bool Auth::validatePhoneNumber(const string& phone) {
    // Phone number should be 10-11 digits
    if (phone.length() < 10 || phone.length() > 11) {
        cout << "Phone number must be 10-11 digits.\n";
        return false;
    }
    
    // Check if all characters are digits
    for (char c : phone) {
        if (!isdigit(c)) {
            cout << "Phone number must contain only digits.\n";
            return false;
        }
    }
    
    return true;
}

bool Auth::updateProfile(const string& username, const string& fullName, 
                        const string& email, const string& phoneNumber) {
    for (User& user : users) {
        if (user.username == username) {
            user.fullName = fullName;
            user.email = email;
            user.phoneNumber = phoneNumber;
            saveUsers();
            return true;
        }
    }
    return false;
}

bool Auth::changePassword(const string& username, const string& oldPassword, 
                         const string& newPassword) {
    for (User& user : users) {
        if (user.username == username && user.password == oldPassword) {
            if (!validatePassword(newPassword)) {
                return false;
            }
            user.password = newPassword;
            saveUsers();
            return true;
        }
    }
    return false;
}

bool Auth::topUpCreditPoints(const string& username, double amount) {
    for (User& user : users) {
        if (user.username == username) {
            user.creditPoints += amount;
            saveUsers();
            return true;
        }
    }
    return false;
}

void Auth::displayProfile(const string& username, BookingManager* bookingManager) {
    for (const User& user : users) {
        if (user.username == username) {
            cout << "\n=== PROFILE INFORMATION ===\n";
            cout << "Username: " << user.username << "\n";
            cout << "Full Name: " << user.fullName << "\n";
            cout << "Email: " << user.email << "\n";
            cout << "Phone Number: " << user.phoneNumber << "\n";
            cout << "ID Type: " << user.idType << "\n";
            cout << "ID Number: " << user.idNumber << "\n";
            cout << "Driver's License: " << user.licenseNumber << "\n";
            cout << "License Expiry: " << user.licenseExpiry << "\n";
            cout << "Role: " << user.role << "\n";
            cout << "Credit Points: " << user.creditPoints << " CPs\n";
            cout << "Renter Rating: " << user.rating << "/5.0\n";
            
            if (bookingManager) {
                // Display active rental bookings
                vector<Booking> userBookings = bookingManager->getUserBookings(username);
                if (!userBookings.empty()) {
                    cout << "\n=== ACTIVE RENTAL BOOKINGS ===\n";
                    cout << "Rent Period | Brand | Model | Color | Size | Plate No. | Owner | Status\n";
                    cout << "-----------|-------|-------|-------|-----|-----------|-------|--------\n";
                    for (const Booking& booking : userBookings) {
                        cout << booking.startDate << "–" << booking.endDate << " | "
                             << booking.brand << " | " << booking.model << " | "
                             << booking.color << " | " << booking.size << " | "
                             << booking.plateNo << " | " << booking.ownerUsername << " | "
                             << booking.status << "\n";
                    }
                }
                
                // Display active rental requests
                vector<Booking> rentalRequests = bookingManager->getUserRentalRequests(username);
                if (!rentalRequests.empty()) {
                    cout << "\n=== ACTIVE RENTAL REQUESTS ===\n";
                    cout << "Rent Period | Renter | Motorbike | Status\n";
                    cout << "-----------|--------|-----------|--------\n";
                    for (const Booking& request : rentalRequests) {
                        cout << request.startDate << "–" << request.endDate << " | "
                             << request.renterUsername << " | "
                             << request.brand << " " << request.model << " | "
                             << request.status << "\n";
                    }
                }
                
                // Display rating statistics
                cout << "\n=== RATING STATISTICS ===\n";
                cout << "Your Renter Rating: " << user.rating << "/5.0\n";
                cout << "Your Motorbike Rating: " << bookingManager->getUserMotorbikeRating(username) << "/5.0\n";
            }
            
            cout << "\n";
        }
    }
}

// User data access methods for search functionality

double Auth::getUserRenterRating(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return user.rating;
        }
    }
    return 0.0; // Default rating if user not found
}

double Auth::getUserCreditPoints(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return user.creditPoints;
        }
    }
    return 0.0; // Default credit points if user not found
}

string Auth::getUserLicenseExpiry(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return user.licenseExpiry;
        }
    }
    return ""; // Empty string if user not found
}

// Admin methods

vector<User> Auth::getAllUsers() {
    return users; // Return all users for admin view
}
