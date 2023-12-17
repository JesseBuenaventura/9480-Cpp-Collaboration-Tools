#include <iostream> //input and output stream
#include <string>
#include <vector>
#include <limits>
using namespace std;

/**
 * Structure that contains the reservation details of the user
*/
struct Reservation {
    int slotNumber;
    int idNumber;
    string studentName;
    int hours;
};

/**
 * Structure that contains the details of a slot
*/
struct Slot {
    int slotNumber; //stores slot number
    bool isAvailable; //determines if slot is available or not
    Reservation reservation; // stores reservation details for the slot if it's reserved
};

/**
 * Function for the user to login into the program
*/
bool login(int &idNumber, const string &password) {
    while (true) {
        cout << "Enter your ID Number: ";
        int inputIdNumber;
        cin >> inputIdNumber;

        cout << "Enter your password: ";
        string inputPassword;
        cin >> inputPassword;

        if (inputIdNumber == idNumber && inputPassword == password) {
            idNumber = inputIdNumber;
            cout << "You have successfully logged in!" << endl;
            return true;
        } else {
            cout << "Invalid ID Number or password. Please try again!" << endl;
        }
    }
}

/**
 * Function to initialize the slots
*/
vector<Slot> initializeSlots(int numberOfSlots) {
    vector<Slot> slots(numberOfSlots);

    for(int i = 0; i < numberOfSlots; i++) {
        Slot newSlot;
        newSlot.slotNumber = i + 1;
        newSlot.isAvailable = true;
        newSlot.reservation = {0, 0, "", 0}; // Initialize reservation with default values

        slots[i] = newSlot;
    }
    return slots;
}

/**
 * Function to display the available slots
*/
void viewAvailableSlots(const vector<Slot>& slots){
    cout << "List of Available slots: " << endl;

    for (const Slot& slot : slots) {
        if (slot.isAvailable) {
            cout << "Slot " << slot.slotNumber << "\tis available." << endl;
        } else {
            cout << "Slot " << slot.slotNumber << "\tis occupied." << endl;
        }
    }
}

/**
 * Function to check if slot is booked or not and if an IDNumber has already booked a slot
*/
bool bookedIDNumber(const vector<Slot>& slots, int idNumber) {
    for (const Slot& slot : slots) {
        if (!slot.isAvailable && slot.reservation.idNumber == idNumber) {
            return true;
        }
    }
    return false;
}

/**
 * Function that enables the user to reserve a slot
*/
void reserveSlot(vector<Slot>& slots, int idNumber) {
    cout << "Enter Slot: ";
    int slot;
    cin >> slot;

    // Checks if slot is already occupied
    if (!slots[slot - 1].isAvailable) {
        cout << "Slot " << slot << " is already occupied. Please choose another slot." << endl;
    } else {
        if(bookedIDNumber(slots, idNumber)){
            cout << "You have already made a reservation." << endl;
        } else {
            string studentName;
            bool validName = false;
            
            while (!validName){
            cout << "Student Name: ";
            cin.ignore();
            getline(cin, studentName); // getline() reads a string from input

            validName = true;
            for(char character : studentName){ //iterates through each character
                if(isdigit(character)){ //checks if character is a digit
                    validName= false;
                    break;
                    }
                }
                if(!validName){
                    cout << "Invalid input. Student name should not contain any numbers." << endl;
                }
            }

            cout << "Enter the Number of Hours: ";
            int hours;
            while (true) {
                cin >> hours;
                if (hours <= 0 || hours > 24) {
                    cout << "Invalid number of hours" << endl;
                    cout << "Enter the Number of Hours: ";
                    cin.ignore();
                } else {
                    break;
                }
            }
            cin.ignore();

            slots[slot - 1].isAvailable = false; // slot # availability will become false after booking a slot

            // Save the reservation details
            slots[slot - 1].reservation.slotNumber = slot;
            slots[slot - 1].reservation.idNumber = idNumber;
            slots[slot - 1].reservation.studentName = studentName;
            slots[slot - 1].reservation.hours = hours;

            // displays reservation info
            cout << "\n-----------------------------" << endl;
            cout << "Confirm Reservation" << endl;
            cout << "Details:" << endl;
            cout << "Slot Number: " << slot << endl;
            cout << "ID Number: " << idNumber << endl;
            cout << "Name: " << studentName << endl;
            cout << "Hours: " << hours << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

/**
 * Function to display the reservation details of the user
*/
void viewReservation(const vector<Slot>& slots) {
    bool foundReservation = false;

    cout << "\nReservation: " << endl;

    for(const Slot& slot : slots) {
        if(!slot.isAvailable) { // if the slot is occupied, it has a reservation
            foundReservation = true;
            cout << "-----------------------------" << endl;
            cout << "Slot Number: " << slot.slotNumber << endl;
            cout << "ID Number: " << slot.reservation.idNumber << endl;
            cout << "Name: " << slot.reservation.studentName << endl;
            cout << "Time: " << slot.reservation.hours << endl;
            cout << "-----------------------------" << endl;
        }
    }

    if (!foundReservation) {
        cout << "No reservations found." << endl;
    }
}

/**
 * Function that allows a user to cancel their reservation
*/
bool cancelReservation (vector<Slot>& slots, int idNumber) {
    for (Slot& slot : slots) {
        if (slot.reservation.idNumber == idNumber) {
            slot.isAvailable = true;
            slot.reservation.idNumber = 0;
            return true;
        } 
    }
    return false;
}

/**
 * Main Function
*/
int main(){
    int idNumber = 12345678;
    string password = "wisdom";
    bool loggedIn = false;
    bool hasReserved = false;

    cout << "Hello, Welcome to ParkRes!" << endl;
    loggedIn = login(idNumber,password);

    if(!loggedIn){
        return 1;
    }

    vector<Slot> slots = initializeSlots(10);
    int choice;

    while(loggedIn) {
        cout << "\n----Choose an option----" << endl;
        cout << "1. View Available Slots" << endl;
        cout << "2. View my Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "View Available Slots" << endl;
            viewAvailableSlots(slots);

            char reserveChoice;
            do {
                if (!hasReserved) {
                    cout << "\nDo you want to reserve a slot? (Input Y/y for Yes, N/n for No): ";
                    cin >> reserveChoice;
            
                switch (reserveChoice) {
                    case 'y':
                    case 'Y':
                        reserveSlot(slots, idNumber);
                        hasReserved = true;
                        break;
                    case 'n':
                    case 'N':
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                }
            } else {
                break;
        }
    } while (reserveChoice != 'n' && reserveChoice != 'N');
    break;

        case 2:
            viewReservation(slots);
            break;
        case 3:
            if (cancelReservation(slots, idNumber)) {
                hasReserved = false;
                cout << "Reservation has been Cancelled" << endl;
            } else {
                cout << "No reservations found" << endl;
            }
            break;
        case 4:
            cout << "Logging Out" << endl;
            loggedIn = false;
            break;
        default:
            cout << "Invalid input. Please enter a valid choice." << endl;
        }
    }

    return 0;
}