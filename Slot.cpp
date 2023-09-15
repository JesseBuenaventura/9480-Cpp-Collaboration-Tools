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
            cout << "Slot " << slot.slotNumber << " is available." << endl;
        } else {
            cout << "Slot " << slot.slotNumber << " is occupied." << endl;
        }
    }
}

int main(){
vector<Slot> slots = initializeSlots(10);
int choice;

    while(true) {
        cout << "----Choose an option----" << endl;
        cout << "1. View Available Slots" << endl;
        cout << "2. View my Reservations" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAvailableSlots(slots);
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


