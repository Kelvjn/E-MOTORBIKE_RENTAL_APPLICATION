# E-MOTORBIKE RENTAL APPLICATION

A C++ console-based electric motorbike rental application that allows users to register as members, list their electric motorbike for rent, browse and book other members' motorbikes, top up credit points (CPs), and provide ratings after each completed ride.

## Features

### User Roles
- **Guest**: Can view general motorbike listings (brand, model, engine size and location only); cannot view other details such ratings and reviews; cannot make rental requests.
- **Member**: Can list their own motorbike for rent; can search for and request to rent other members' motorbikes (if eligible); can top up CPs, rate others, and manage their profile.
- **Admin**: Can view all member profiles and motorbike listings without restriction.

### Current Implementation
- User authentication system
- Member registration with comprehensive validation
- File-based user management (account.txt)
- Role-based access control
- Password masking for security
- Strong password policy enforcement
- Menu-driven interface
- Complete Profile Management System

## Compilation and Running

### Prerequisites
- C++ compiler (g++ recommended)
- Windows (for conio.h support)

### Compile
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

## Default Accounts

### Admin Account
- Username: `admin`
- Password: `admin123`

## Registration Requirements

### Member Registration
- **Registration Fee**: $20
- **Starting Credit Points**: 20 CPs
- **Default Rating**: 3.0
- **Required Information**:
  - Username (unique)
  - Password (strong policy enforced)
  - Full name
  - Email address
  - Phone number (10-11 digits)
  - ID type (Citizen ID or Passport)
  - ID number
  - Driver's license (optional)

### Password Policy
- Minimum 8 characters
- Must contain uppercase, lowercase, and digit
- Cannot be common weak passwords
- Examples of weak passwords: "12345678", "password", "admin123"

## File Structure

- `main.cpp` - Main application entry point
- `ui.h/ui.cpp` - User interface and menu system
- `auth.h/auth.cpp` - Authentication and user management
- `account.txt` - User data storage (created automatically)
- `Makefile` - Build configuration

## Profile Management Features

### Member Profile Management
Members can access comprehensive profile management through the member menu:

1. **View Profile Information**
   - Display complete profile details including personal information, credit points, and ratings
   - Show active rental bookings and pending rental requests
   - Display rating statistics (renter rating and motorbike rating)

2. **Update Profile Information**
   - Update full name, email address, and phone number
   - Username cannot be changed (system restriction)
   - Input validation for email format and phone number format
   - Option to keep current values by pressing Enter

3. **Change Password**
   - Requires current password verification
   - New password must meet strong password policy
   - Password confirmation to prevent typos
   - Password masking for security

4. **Top Up Credit Points**
   - Add credit points to account balance
   - Rate: $1 = 1 Credit Point (CP)
   - Password authentication required for security
   - Real-time balance update

5. **View Booking History**
   - Display all rental bookings as a renter
   - Show pending rental requests for owned motorbikes
   - Include booking details: dates, motorbike info, status, cost
   - Rating statistics overview

### Security Features
- Password masking during input
- Password authentication for sensitive operations
- Input validation for all profile fields
- Strong password policy enforcement

## Data Format

User data is stored in `account.txt` with the following format:
```
username|password|role|fullName|email|phoneNumber|idType|idNumber|licenseNumber|licenseExpiry|creditPoints|rating|license
```

## Development Status

- ✅ Authentication system
- ✅ User roles (Guest, Member, Admin)
- ✅ Member registration with validation
- ✅ Strong password policy
- ✅ File-based data storage
- ✅ Profile Management System
  - ✅ View profile information
  - ✅ Update profile information (except username)
  - ✅ Change password with validation
  - ✅ Top up credit points ($1 = 1 CP)
  - ✅ View booking history and rating statistics
- ⏳ Motorbike listing system
- ⏳ Booking system
- ⏳ Credit points management
- ⏳ Rating system

## Group Information

**EEET2482/EEET2653/COSC2082/COSC2721 GROUP PROJECT**
Semester 2 2025

**Group: Group 5**
- S3992133, Lu Duc Thinh
- S3928379, Jang Soohyuk
- S3975144, Pham Tuan Hai
- S4027077, Vu The Quyen

Instructor: Dr Ling Huo Chong, Dr Ushik Shrestha, Dr Tri Huynh