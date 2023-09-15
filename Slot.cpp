#include <iostream> //input and output stream
#include <string>
#include <vector>
using namespace std;

struct Slot
{
    int slotNumber; //stores slot number
    bool isAvailable; //determins if slot is available or not
};

vector<Slot> initializeSlots(int numberOfSlots) {
    vector<Slot> slots;

    for(int i = 1; i <= numberOfSlots; i++) {
        Slot newSlot;
        newSlot.slotNumber = i;
        newSlot.isAvailable = true;
        slots.push_back(newSlot);
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

void reserveSlot(vector<Slot>& slots){
    cout << "Enter Slot:" << endl;
    int slot;
    cin >> slot;

    // Checks if slot is already occupied
    if(!slots[slot - 1].isAvailable){
        cout << "Slot " << slot << " is already occupied. Please choose another slot." << endl;
    } else {

        // TO DO: Check if student id is valid 
        cout << "School ID Number:" << endl;
        int idNumber;
        cin >> idNumber;
        cin.ignore();

        cout << "Student Name:" << endl;
        string studentName;
        getline(cin,studentName); //getline() reads a string from input

        //TO DO: Decide if number of hours nalang or Arrival Time nalang
        //TO DO: Handle wrong inputs
        cout << "Enter the Number of Hours:" << endl;
        int hours;
        cin >> hours;
        cin.ignore();

        cout << "Departure Time:" << endl;
        string departure;
        getline(cin, departure); //getline() reads a string from input

        slots[slot - 1].isAvailable = false; //slot # availability will become false after booking a slot

        //displays reservation info
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

int main(){
vector<Slot> slots = initializeSlots(10);
int choice;

    while(true) {
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

            char reserveChoice;
            do{
                cout << "Do you want to reserve a slot? (Input Y/y for Yes, N/n for No): ";
                cin >> reserveChoice;
            
            switch(reserveChoice){
            case 'y':
            case 'Y':
                reserveSlot(slots);
                break;
            case 'n':
            case 'N':
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
        } while (reserveChoice != 'n' && reserveChoice != 'N');
        break;

        case 2:
            cout << "View my Reservations" << endl;
            break;
        case 3: 
            cout << "Cancel Reservation" << endl;
            break;
        case 4:
            cout << "Exiting the application" << endl;
            return 0;
        default:
            cout << "Invalid input. Please enter a valid choice." << endl;
        }
    }

    return 0;
}


