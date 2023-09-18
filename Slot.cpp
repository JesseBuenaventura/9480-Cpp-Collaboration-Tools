#include <iostream> //input and output stream
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Reservation {
    int slotNumber;
    int idNumber;
    string studentName;
    string departureTime;
};

struct Slot {
    int slotNumber; //stores slot number
    bool isAvailable; //determines if slot is available or not
    Reservation reservation; // stores reservation details for the slot if it's reserved
};

bool login(int& idNumber, const string& password){
    int idNum;
    string pass;
    bool loggedIn = false;

    while (!loggedIn){
        cout << "Enter your ID Number: ";
        cin >> idNum;

        cout << "Enter your password: ";
        cin >> pass;

        if(idNum == idNumber && pass == password) {
            idNumber = idNum;
            cout << "You've Successfully Login!" << endl;
            loggedIn = true;
        } else {
            cout << "Invalid ID Number or password. Please try again!" << endl;
        }
    }
    return true;
}
    


// cin >> user;
//     if (user == username){
//         cout << "Enter your Password: ";
//         cin >> pass;
//         if (pass == password){
//             cout << "Successfully Login!" << endl;
//             return true;
//         } else  {
//             cout << "Incorrect Username or Password! Try Again!" << endl;
//         }
//     } else {
//         cout << "Incorrect Username or Password! Try Again!" << endl;
//     }
//     return false;

vector<Slot> initializeSlots(int numberOfSlots) {
    vector<Slot> slots(numberOfSlots);

    for(int i = 0; i < numberOfSlots; i++) {
        slots[i] = {i + 1, true}; //used braced initializer to simplify code
        //i+1 - slot numbers start from 1 and then increment by 1 for each slot
        //true - initializes isAvailable member to true which indicates each slot is available
    }
    return slots;
}

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

bool bookedIDNumber(const vector<Slot>& slots, int idNumber) {
    for (const Slot& slot : slots) {
        //check if slot is booked or not and if an IDNumber has already booked a slot
        if (!slot.isAvailable && slot.reservation.idNumber == idNumber) {
            return true;
        }
    }
    return false;
}

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
            cout << "Student Name: ";
            string studentName;
            cin.ignore();
            getline(cin, studentName); // getline() reads a string from input

            // TO DO: Decide if number of hours only or Arrival Time only
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

            cout << "Departure Time: ";
            string departure;
            getline(cin, departure); // getline() reads a string from input

            slots[slot - 1].isAvailable = false; // slot # availability will become false after booking a slot

            // Save the reservation details
            slots[slot - 1].reservation.slotNumber = slot;
            slots[slot - 1].reservation.idNumber = idNumber;
            slots[slot - 1].reservation.studentName = studentName;
            slots[slot - 1].reservation.departureTime = departure;

            // displays reservation info
            cout << "-----------------------------" << endl;
            cout << "Confirm Reservation" << endl;
            cout << "Details:" << endl;
            cout << "Slot Number: " << slot << endl;
            cout << "ID Number: " << idNumber << endl;
            cout << "Name: " << studentName << endl;
            cout << "Time: " << departure << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

void viewAllReservations(const vector<Slot>& slots) {
    bool foundReservation = false;

    cout << "All Reservations: " << endl;

    for(const Slot& slot : slots) {
        if(!slot.isAvailable) { // if the slot is occupied, it has a reservation
            foundReservation = true;
            cout << "-----------------------------" << endl;
            cout << "Slot Number: " << slot.slotNumber << endl;
            cout << "ID Number: " << slot.reservation.idNumber << endl;
            cout << "Name: " << slot.reservation.studentName << endl;
            cout << "Time: " << slot.reservation.departureTime << endl;
            cout << "-----------------------------" << endl;
        }
    }

    if (!foundReservation) {
        cout << "No reservations found." << endl;
    }
}

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


int main(){
    int idNumber = 1234567;
    string password = "wisdom";
    bool loggedIn = false;
    bool hasReserved = false;

    cout << "Hello, Welcome to ParkRes!" << endl;
    loggedIn = login(idNumber,password);

    if(!loggedIn){
        return 1;
    }
    // cout << "Enter your Username: ";
    // cin >> user;
    // if (user == userName){
    //     cout << "Enter your Password: ";
    //     cin >> pass;
    //     if (pass == password){
    //         cout << "Successfully Login!" << endl;
    //         loggedIn = true;
    //     } else  {
    //         cout << "INCORRECT Username or Password! Try Again!" << endl;
    //     }
    // }

vector<Slot> slots = initializeSlots(10);
int choice;

    while(loggedIn) {
        cout << "\n----Choose an option----" << endl;
        cout << "1. View Available Slots" << endl;
        cout << "2. View my Reservations" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "View Available Slots" << endl;
            viewAvailableSlots(slots);

            if (!hasReserved){
                char reserveChoice;
                do{
                    cout << "Do you want to reserve a slot? (Input Y/y for Yes, N/n for No): ";
                    cin >> reserveChoice;
                    
                    switch(reserveChoice){
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
                } while (reserveChoice != 'n' && reserveChoice != 'N');
            } else {
                cout << "You already made a reservation." << endl;
            }
        break;

        case 2:
            viewAllReservations(slots);
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

