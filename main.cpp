#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_SLOTS = 5;


struct Vehicle
{
    string vehicleNumber;
    string vehicleType;
    int slotNumber;
    Vehicle* next;
};


struct QueueNode
{
    string vehicleNumber;
    string vehicleType;
    QueueNode* next;
};


class ParkingLot
{
private:


    int parkingSlots[MAX_SLOTS];

    Vehicle* head;

    QueueNode* front;
    QueueNode* rear;

public:


    ParkingLot()
    {
        head = nullptr;
        front = nullptr;
        rear = nullptr;

        for (int i = 0; i < MAX_SLOTS; i++)
        {
            parkingSlots[i] = 0;
        }
    }


    int findFreeSlot()
    {
        for (int i = 0; i < MAX_SLOTS; i++)
        {
            if (parkingSlots[i] == 0)
            {
                return i;
            }
        }

        return -1;
    }

 
    bool vehicleExists(string number)
    {
        Vehicle* temp = head;

        while (temp != nullptr)
        {
            if (temp->vehicleNumber == number)
            {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

 
    void parkVehicle(string number, string type)
    {
        if (vehicleExists(number))
        {
            cout << "\nVehicle is already parked!\n";
            return;
        }

        int slot = findFreeSlot();

        if (slot == -1)
        {
            addToQueue(number, type);

            cout << "\nParking lot is FULL.\n";
            cout << "Vehicle added to waiting queue.\n";

            return;
        }

        parkingSlots[slot] = 1;

     
        Vehicle* newVehicle = new Vehicle;

        newVehicle->vehicleNumber = number;
        newVehicle->vehicleType = type;
        newVehicle->slotNumber = slot + 1;
        newVehicle->next = nullptr;

       
        if (head == nullptr)
        {
            head = newVehicle;
        }
        else
        {
            Vehicle* temp = head;

            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = newVehicle;
        }

        cout << "\nVehicle parked successfully!\n";
        cout << "Vehicle Number : " << number << endl;
        cout << "Vehicle Type   : " << type << endl;
        cout << "Parking Slot   : " << slot + 1 << endl;
    }

    void addToQueue(string number, string type)
    {
        QueueNode* newNode = new QueueNode;

        newNode->vehicleNumber = number;
        newNode->vehicleType = type;
        newNode->next = nullptr;

        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

 
    void removeFromQueue(string& number, string& type)
    {
        if (front == nullptr)
        {
            return;
        }

        QueueNode* temp = front;

        number = temp->vehicleNumber;
        type = temp->vehicleType;

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }


    void exitVehicle(string number)
    {
        Vehicle* current = head;
        Vehicle* previous = nullptr;

        while (current != nullptr &&
               current->vehicleNumber != number)
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "\nVehicle not found in parking lot.\n";
            return;
        }

        int slot = current->slotNumber;

        if (previous == nullptr)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        delete current;

        parkingSlots[slot - 1] = 0;

        cout << "\nVehicle exited successfully.\n";
        cout << "Vehicle Number : " << number << endl;
        cout << "Freed Slot     : " << slot << endl;

        if (front != nullptr)
        {
            string nextVehicle;
            string nextType;

            removeFromQueue(nextVehicle, nextType);

            cout << "\nVehicle from waiting queue is being assigned...\n";

            parkingSlots[slot - 1] = 1;

            Vehicle* newVehicle = new Vehicle;

            newVehicle->vehicleNumber = nextVehicle;
            newVehicle->vehicleType = nextType;
            newVehicle->slotNumber = slot;
            newVehicle->next = nullptr;

            if (head == nullptr)
            {
                head = newVehicle;
            }
            else
            {
                Vehicle* temp = head;

                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }

                temp->next = newVehicle;
            }

            cout << "\nWaiting vehicle automatically parked.\n";
            cout << "Vehicle Number : " << nextVehicle << endl;
            cout << "Vehicle Type   : " << nextType << endl;
            cout << "Parking Slot   : " << slot << endl;
        }
    }

   
    void displaySlots()
    {
        cout << "\n====================================\n";
        cout << "        PARKING SLOT STATUS\n";
        cout << "====================================\n";

        for (int i = 0; i < MAX_SLOTS; i++)
        {
            cout << "Slot " << setw(2) << i + 1 << " : ";

            if (parkingSlots[i] == 0)
            {
                cout << "FREE";
            }
            else
            {
                cout << "OCCUPIED";
            }

            cout << endl;
        }
    }

   
    void displayVehicles()
    {
        cout << "\n====================================\n";
        cout << "        PARKED VEHICLES\n";
        cout << "====================================\n";

        if (head == nullptr)
        {
            cout << "No vehicles are currently parked.\n";
            return;
        }

        Vehicle* temp = head;

        cout << left
             << setw(20) << "Vehicle Number"
             << setw(15) << "Vehicle Type"
             << setw(10) << "Slot"
             << endl;

        cout << "---------------------------------------------\n";

        while (temp != nullptr)
        {
            cout << left
                 << setw(20) << temp->vehicleNumber
                 << setw(15) << temp->vehicleType
                 << setw(10) << temp->slotNumber
                 << endl;

            temp = temp->next;
        }
    }

   
    void displayQueue()
    {
        cout << "\n====================================\n";
        cout << "        WAITING VEHICLES\n";
        cout << "====================================\n";

        if (front == nullptr)
        {
            cout << "No vehicles are waiting.\n";
            return;
        }

        QueueNode* temp = front;

        int position = 1;

        while (temp != nullptr)
        {
            cout << position << ". "
                 << temp->vehicleNumber
                 << " (" << temp->vehicleType << ")"
                 << endl;

            temp = temp->next;
            position++;
        }
    }

   
    void searchVehicle(string number)
    {
        Vehicle* temp = head;

        while (temp != nullptr)
        {
            if (temp->vehicleNumber == number)
            {
                cout << "\nVehicle Found!\n";
                cout << "Vehicle Number : "
                     << temp->vehicleNumber << endl;

                cout << "Vehicle Type   : "
                     << temp->vehicleType << endl;

                cout << "Parking Slot   : "
                     << temp->slotNumber << endl;

                return;
            }

            temp = temp->next;
        }

     
        QueueNode* q = front;

        while (q != nullptr)
        {
            if (q->vehicleNumber == number)
            {
                cout << "\nVehicle Found in Waiting Queue!\n";
                cout << "Vehicle Number : "
                     << q->vehicleNumber << endl;

                cout << "Vehicle Type   : "
                     << q->vehicleType << endl;

                cout << "Status         : Waiting\n";

                return;
            }

            q = q->next;
        }

        cout << "\nVehicle not found.\n";
    }

 
    int countFreeSlots()
    {
        int count = 0;

        for (int i = 0; i < MAX_SLOTS; i++)
        {
            if (parkingSlots[i] == 0)
            {
                count++;
            }
        }

        return count;
    }

 
    int countVehicles()
    {
        int count = 0;

        Vehicle* temp = head;

        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

   
    void displaySummary()
    {
        cout << "\n====================================\n";
        cout << "        PARKING SUMMARY\n";
        cout << "====================================\n";

        cout << "Total Slots       : "
             << MAX_SLOTS << endl;

        cout << "Occupied Slots    : "
             << countVehicles() << endl;

        cout << "Available Slots   : "
             << countFreeSlots() << endl;
    }

 
    ~ParkingLot()
    {
        while (head != nullptr)
        {
            Vehicle* temp = head;
            head = head->next;
            delete temp;
        }

        while (front != nullptr)
        {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};


int main()
{
    ParkingLot parkingLot;

    int choice;
    string vehicleNumber;
    string vehicleType;

    do
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "       PARKING LOT MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Park Vehicle\n";
        cout << "2. Vehicle Exit\n";
        cout << "3. Display Parking Slots\n";
        cout << "4. Display Parked Vehicles\n";
        cout << "5. Display Waiting Queue\n";
        cout << "6. Search Vehicle\n";
        cout << "7. Parking Summary\n";
        cout << "8. Exit Program\n";

        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:

                cout << "\nEnter Vehicle Number: ";
                cin >> vehicleNumber;

                cout << "Enter Vehicle Type: ";
                cin >> vehicleType;

                parkingLot.parkVehicle(
                    vehicleNumber,
                    vehicleType
                );

                break;


            case 2:

                cout << "\nEnter Vehicle Number to Exit: ";
                cin >> vehicleNumber;

                parkingLot.exitVehicle(vehicleNumber);

                break;


            case 3:

                parkingLot.displaySlots();

                break;


            case 4:

                parkingLot.displayVehicles();

                break;


            case 5:

                parkingLot.displayQueue();

                break;


            case 6:

                cout << "\nEnter Vehicle Number to Search: ";
                cin >> vehicleNumber;

                parkingLot.searchVehicle(vehicleNumber);

                break;


            case 7:

                parkingLot.displaySummary();

                break;


            case 8:

                cout << "\nThank you for using "
                     << "Parking Lot Management System!\n";

                break;


            default:

                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}