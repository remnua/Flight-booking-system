#include <iostream>
#include <string>
#include <vector>
using namespace std;

class FlightBooking {
public:
    FlightBooking(int id, int capacity, int reserved);
    void printStatus();
    void add(int n);
    void cancel(int n);
private:
    int id;
    int capacity;
    int reserved;
    void set_reserved(int reserved);
    void set_capacity(int capacity);
};

void FlightBooking::printStatus()
{
    double percent = 0.0;
    if (this != nullptr && this->capacity > 0) {
        percent = 100.0 * ((double)this->reserved / this->capacity);
        printf("Flight %d: %d/%d (%.2lf%%) seats taken\n", this->id, this->reserved, this->capacity, percent);
    }
}

void FlightBooking::set_reserved(int reserved) {
    if (reserved < 0)
        this->reserved = 0;
    else if (reserved > this->capacity - this->reserved)
        cout << "Cannot perform this operation\n";
    else if ((double)(reserved + this->reserved) / this->capacity > 1.05)
        cout << "Cannot reserve more than 105% of capacity\n";
    else
        this->reserved = reserved;
}

void FlightBooking::set_capacity(int capacity) {
    if (capacity <= 0) {
        cout << "Capacity should be a positive integer\n";
        this->capacity = 0;
    }
    else
        this->capacity = capacity;
}

FlightBooking::FlightBooking(int id, int capacity, int reserved) {
    this->id = id;
    set_capacity(capacity);
    set_reserved(reserved);
}

void FlightBooking::add(int n) {
    if (n > 0) {
        set_reserved(this->reserved + n);
        printStatus();
    }
    else {
        cout << "Cannot add negative number or zero of seats\n";
    }
}

void FlightBooking::cancel(int n) {
    if (n > 0) {
        if (this->reserved >= n) {
            set_reserved(this->reserved - n);
            printStatus();
        }
        else {
            cout << "Cannot cancel more seats than reserved\n";
        }
    }
    else {
        cout << "Cannot cancel a negative number of seats\n";
    }
}

int main() {
    int capacity = 0, reserved = 0;
    cout << "Provide flight capacity: ";
    cin >> capacity;
    cout << "Provide number of reserved seats: ";
    cin >> reserved;
    FlightBooking booking(1, capacity, reserved);
    string command;
    while (true) {
        cout << "Enter a command: ";
        cin >> command;
        if (command == "quit")
            break;
        cout << "Enter the number: ";
        int numb;
        if (command == "add") {
            cin >> numb;
            booking.add(numb);
        }
        else if (command == "cancel") {
            cin >> numb;
            booking.cancel(numb);
        }
        else {
            cout << "Undefined command\n";
        }
    }
    return 0;
}
