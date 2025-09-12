# E-MOTORBIKE RENTAL APPLICATION

run the application: .\motorbike_rental.exe

A C++ console-based electric motorbike rental application that allows users to register as members, list their electric motorbike for rent, browse and book other members' motorbikes, top up credit points (CPs), and provide ratings after each completed ride.

## Features

### User Roles
- **Guest**: Can view general motorbike listings (brand, model, engine size and location only); cannot view other details such ratings and reviews; cannot make rental requests.
- **Member**: Can list their own motorbike for rent; can search for and request to rent other members' motorbikes (if eligible); can top up CPs, rate others, and manage their profile.
- **Admin**: Can view all member profiles and motorbike listings without restriction; can access comprehensive system statistics and monitoring.

### Current Implementation
- User authentication system
- Member registration with comprehensive validation
- File-based user management (account.txt)
- Role-based access control
- Password masking for security
- Strong password policy enforcement
- Menu-driven interface
- Complete Profile Management System
- Guest access with limited functionality

## How to Run the Application

### Prerequisites
- **C++ Compiler**: g++ (GNU Compiler Collection) recommended
- **Operating System**: Windows (required for conio.h support)
- **Make Tool**: GNU Make for build automation
- **Terminal**: Command Prompt or PowerShell

### Step-by-Step Instructions

#### **Step 1: Open Terminal/Command Prompt**
1. Open Command Prompt or PowerShell
2. Navigate to the project directory:
   ```bash
   cd D:\Github_Test\E-MOTORBIKE_RENTAL_APPLICATION
   ```

#### **Step 2: Clean Previous Build (Optional)**
If you have previously compiled the application, clean the old files:
```bash
make clean
```

#### **Step 3: Compile the Application**
Compile all source files into an executable:
```bash
make
```
**Expected Output:**
```
g++ -std=c++11 -Wall -Wextra -c main.cpp -o main.o
g++ -std=c++11 -Wall -Wextra -c ui.cpp -o ui.o
g++ -std=c++11 -Wall -Wextra -c auth.cpp -o auth.o
g++ -std=c++11 -Wall -Wextra -c booking.cpp -o booking.o
g++ main.o ui.o auth.o booking.o -o motorbike_rental_v4
```

#### **Step 4: Run the Application**
**Option A: Using Make (Recommended)**
```bash
make run
```

**Option B: Direct Execution**
```bash
./motorbike_rental
```

### Application Startup
After running the application, you will see:
```
EEET2482/EEET2653/COSC2082/COSC2721 GROUP PROJECT
Semester 2 2025
E-MOTORBIKE RENTAL APPLICATION
Instructor: Dr Ling Huo Chong, Dr Ushik Shrestha, Dr Tri Huynh
Group: Group 5.
S3992133, Lu Duc Thinh
S3928379, Jang Soohyuk
S3975144, Pham Tuan Hai
S4027077, Vu The Quyen

Use the app as 1.Guest  2.Member  3.Admin  4.Register  5.Exit
Enter your choice:
```

### Available Options
1. **Guest**: Browse motorbike listings (limited view)
2. **Member**: Full access to rental features (requires login)
3. **Admin**: Administrative functions (requires admin login)
4. **Register**: Create new member account
5. **Exit**: Close the application

### Default Login Credentials

#### **Admin Account**
- **Username**: `admin`
- **Password**: `admin123`

#### **Sample Member Accounts**
The system includes sample member accounts for testing:
- Various usernames like `iAmMember1`, `iAmMember2`, etc.
- Default password pattern: `password123`
- Starting credit points: 20 CPs
- Default rating: 3.0

### Troubleshooting

#### **Compilation Errors**
- **"Permission denied"**: Close any running instances of the application
- **"g++ not found"**: Install MinGW or another C++ compiler
- **"make not found"**: Install GNU Make or use manual compilation

#### **Runtime Errors**
- **"Cannot open file"**: Ensure all data files exist in the project directory
- **"Permission denied"**: Run as administrator if needed
- **"Application crashes"**: Check if all required files are present

#### **Manual Compilation (if make fails)**
```bash
g++ -std=c++11 -Wall -Wextra main.cpp ui.cpp auth.cpp booking.cpp -o motorbike_rental
```

### File Structure After Compilation
```
E-MOTORBIKE_RENTAL_APPLICATION/
├── motorbike_rental.exe # Executable file
├── main.o                     # Compiled main.cpp
├── ui.o                       # Compiled ui.cpp
├── auth.o                     # Compiled auth.cpp
├── booking.o                  # Compiled booking.cpp
├── account.txt               # User data (auto-created)
├── bookings.txt              # Booking data (auto-created)
├── motorbikes.txt            # Motorbike data (auto-created)
└── [source files...]
```

### Understanding .o Files
**Object Files (.o)** are intermediate files created during compilation:
- **Purpose**: Compiled machine code for each source file
- **Creation**: Generated when `g++ -c` compiles individual .cpp files
- **Linking**: Combined by the linker to create the final executable
- **Benefits**: Faster recompilation (only changed files need recompiling)
- **Cleanup**: Can be safely deleted with `make clean`

**Compilation Process:**
1. **Preprocessing**: Expands includes and macros
2. **Compilation**: Converts .cpp to .o (object files)
3. **Linking**: Combines .o files into executable

### Quick Start Guide
1. **First Time Setup**:
   ```bash
   make clean
   make
   make run
   ```

2. **Subsequent Runs**:
   ```bash
   make run
   ```

3. **Testing Different Roles**:
   - Try **Guest** first to browse listings
   - Use **Register** to create a member account
   - Login as **Member** to access full features
   - Login as **Admin** to view system statistics

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
- `booking.h/booking.cpp` - Booking and motorbike management
- `account.txt` - User data storage (created automatically)
- `bookings.txt` - Booking data storage (created automatically)
- `motorbikes.txt` - Motorbike listings data storage (created automatically)
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

## Guest Features

### Limited Access Functionality
Guests can browse motorbike listings with restricted information as per requirements:

1. **View Motorbike Listings**
   - **Available Information**: Brand, model, engine size, and location only
   - **Restricted Information**: No ratings, reviews, pricing, owner details, or availability dates
   - **Display Format**: Clean tabular format with limited columns
   - **Access Limitation**: Cannot view detailed motorbike information

2. **Search Motorbikes**
   - **Search Criteria**: City filtering only (HCMC or Hanoi)
   - **Limited Search**: Cannot search by date, price, or rating requirements
   - **Results Display**: Same limited information as listings view
   - **No Booking**: Cannot make rental requests

### Guest Access Restrictions
As per requirements, guests **cannot**:
- View motorbike ratings and reviews
- See pricing information (daily rates)
- Access owner details
- View availability dates
- Make rental requests
- Access advanced search filters
- View detailed motorbike specifications

### User Experience
- **Clear Limitations**: System clearly explains what guests cannot access
- **Registration Prompt**: Encourages guests to register for full access
- **Consistent Interface**: Same menu structure as other roles
- **Information Display**: Only shows permitted information fields

### Guest Menu Options
1. **View motorbike listings** - Browse all available motorbikes with limited info
2. **Search motorbikes** - Filter by city only
3. **Back to main menu** - Return to main application menu

## Electric Motorbike Listing Features

### Member Motorbike Management
Members can manage their electric motorbike listings through the member menu:

1. **List My Motorbike for Rent**
   - Each member can list only one electric motorbike
   - Required information:
     - Brand, model, color, size, plate number
     - Available rental period (start and end date)
     - City location (HCMC or Hanoi only)
     - Daily rental rate (in Credit Points)
     - Minimum required renter rating (1.0-5.0)
   - Comprehensive input validation
   - Automatic motorbike ID generation

2. **Unlist My Motorbike**
   - Remove motorbike from rental listings
   - Cannot unlist if motorbike is currently booked
   - Confirmation prompt for safety

3. **View My Current Listing**
   - Display complete motorbike information
   - Show availability status and ratings
   - Display rental period and pricing

### Validation Rules
- **Location**: Must be either "HCMC" or "Hanoi"
- **Daily Rate**: Must be greater than 0 CP
- **Minimum Rating**: Must be between 1.0 and 5.0
- **Rental Period**: Start and end dates cannot be empty
- **One Listing**: Each member can only have one active listing

### Sample Data
The system includes 20 sample electric motorbikes:
- **10 motorbikes in HCMC**: Various brands (VinFast, Honda, Yamaha, Suzuki, Piaggio)
- **10 motorbikes in Hanoi**: Diverse models and specifications
- **Price Range**: 20-65 CP per day
- **Rating Range**: 3.8-4.9 stars
- **Engine Sizes**: 50cc to 155cc

## Motorbike Search and Filtering Features

### Advanced Search and Filtering System
Members can search for available motorbikes with comprehensive filtering criteria:

1. **Search by Date and City**
   - Search for motorbikes available on a specific date
   - Filter by city (HCMC or Hanoi only)
   - Real-time availability checking

2. **Comprehensive Motorbike Information**
   - Brand, model, engine size, and motorbike rating
   - Customer reviews and average scores
   - Detailed motorbike specifications
   - Pricing and availability information

3. **Smart Filtering Criteria**
   The system automatically filters results based on user eligibility:
   - **Member's Renter Rating**: Must meet or exceed motorbike's minimum requirement
   - **Credit Points**: Must have sufficient CPs to cover full rental cost
   - **License Requirements**: Active license required for motorbikes > 50cc
   - **Location Match**: Motorbike must be in the selected city
   - **Date Availability**: Search date must be within motorbike's available period

### Search Example
**Scenario**: Michael has:
- Renter rating: 3.0
- Credit points: 60 CPs
- License status: Expired
- Search: HCMC on 15 August 2025

**Results**: Only motorbikes matching ALL criteria:
- Required renter rating ≤ 3.0
- Daily cost ≤ 60 CPs
- Engine size ≤ 50cc (no license required)
- Available in HCMC on 15 August 2025

### User Interface Features
- **Search Menu**: Easy-to-use search interface
- **Results Display**: Tabular format with key information
- **Detailed View**: Complete motorbike information and reviews
- **Filtering Feedback**: Clear explanation when no results found
- **Review System**: Customer reviews and ratings display

### Review and Rating System
- **Average Rating Display**: Shows motorbike's overall rating
- **Customer Reviews**: Sample reviews for each motorbike
- **Rating Statistics**: Detailed rating information
- **Review Content**: Helpful customer feedback and comments

## Admin Features

### Comprehensive Administrative Functions
Admins have unrestricted access to view all system data and statistics:

1. **View All Member Profiles**
   - Complete user information display
   - Username, full name, email, phone number
   - Role, credit points, rating, license expiry
   - Summary statistics (total users, members, admins)
   - Tabular format for easy reading

2. **View All Motorbike Listings**
   - Complete motorbike information
   - Owner details, brand/model, specifications
   - Location, pricing, availability status
   - Listing status and ratings
   - Summary with total value and counts

3. **System Statistics Dashboard**
   - **User Statistics**: Total users, members, admins, credit points, average ratings
   - **Motorbike Statistics**: Total motorbikes, listed/available counts, total value, average ratings
   - **Booking Statistics**: Total bookings, status breakdown (pending/approved/completed/rejected), total value
   - **System Overview**: Utilization rates, success rates, performance metrics

### Admin Access Control
- **Unrestricted Access**: Admins can view all data without filtering
- **Comprehensive Monitoring**: Full system overview and statistics
- **Data Analysis**: Detailed breakdowns and summaries
- **System Health**: Performance and utilization metrics

### Administrative Interface
- **Clean Menu System**: Easy navigation through admin functions
- **Formatted Displays**: Tabular data presentation for readability
- **Summary Statistics**: Quick overview of system status
- **Professional Layout**: Consistent formatting and organization

## Data Format

User data is stored in `account.txt` with the following format:
```
username|password|role|fullName|email|phoneNumber|idType|idNumber|licenseNumber|licenseExpiry|creditPoints|rating|license
```

Booking data is stored in `bookings.txt` with the following format:
```
bookingId|renterUsername|ownerUsername|motorbikeId|startDate|endDate|status|totalCost|brand|model|color|size|plateNo
```

Motorbike data is stored in `motorbikes.txt` with the following format:
```
motorbikeId|ownerUsername|brand|model|color|size|plateNo|pricePerDay|location|isAvailable|rating|description|availableStartDate|availableEndDate|minRenterRating|isListed
```

## Development Status

- ✅ Authentication system
- ✅ User roles (Guest, Member, Admin)
- ✅ Member registration with validation
- ✅ Strong password policy
- ✅ File-based data storage
- ✅ Guest Access System
  - ✅ Limited motorbike listings view (brand, model, size, location only)
  - ✅ City-based search functionality
  - ✅ Access restrictions enforcement
  - ✅ Clear limitation explanations
- ✅ Profile Management System
  - ✅ View profile information
  - ✅ Update profile information (except username)
  - ✅ Change password with validation
  - ✅ Top up credit points ($1 = 1 CP)
  - ✅ View booking history and rating statistics
- ✅ Electric Motorbike Listing System
  - ✅ List motorbike for rent (one per member)
  - ✅ Unlist motorbike (unless booked)
  - ✅ View current listing
  - ✅ Available rental period specification
  - ✅ City restrictions (HCMC or Hanoi only)
  - ✅ Daily rental rate in CP
  - ✅ Minimum required renter rating
- ✅ Motorbike Search and Filtering System
  - ✅ Search by date and city
  - ✅ Smart filtering based on user eligibility
  - ✅ Comprehensive motorbike information display
  - ✅ Review and rating system
  - ✅ License requirement validation
  - ✅ Credit points validation
  - ✅ Renter rating validation
- ✅ Admin System
  - ✅ View all member profiles
  - ✅ View all motorbike listings
  - ✅ System statistics dashboard
  - ✅ Comprehensive data monitoring
  - ✅ Administrative interface
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