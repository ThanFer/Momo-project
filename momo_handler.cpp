#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void sleep_for_seconds(int seconds) {
    auto start_time = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time).count() < seconds) {
    }
}

int main() {
    string momoPin;
    bool isAuthenticated = false;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    int balance = 1000;

    // Authentication loop
    while (!isAuthenticated && attempts < MAX_ATTEMPTS) {
        int remainingAttempts = MAX_ATTEMPTS - attempts;
        cout << "Fee is GHS 0.00. Enter MM Pin (" << remainingAttempts << " attempts left):\n";
        getline(cin, momoPin);

        // Check if the momoPin is valid
        if (momoPin == "0000") {
            isAuthenticated = true;
        }

        if (!isAuthenticated) {
            attempts++;
            cout << "Incorrect Mobile Money Pin. Your account will be blocked if the atttempts is exceeded." << endl;
        }
    }

    // Authentication status
    if (isAuthenticated) {
        // Menu
        int choice;
        cout << "Please select an option:" << endl;
        cout << "1. Check balance" << endl;
        cout << "2. Change your MM Pin" << endl;
        cout << "3. Send money to someone" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        // Verify momoPin
        cout << "Please enter your MM again to proceed: ";
        string verifyPin;
        cin >> verifyPin;

        if (verifyPin != momoPin) {
            cout << "Incorrect Mobile Money Pin. Access denied." << endl;
            return 0;
        }

        // Perform selected action
        switch (choice) {
            case 1:
                cout << "Your balance is " << balance << "." << endl;
                break;
            case 2:
                cout << "Enter your new MM Pin: ";
                cin >> momoPin;
                cout << "momoPin changed successfully." << endl;
                break;
            case 3: {
                cout << "Enter the recipient's phone number: ";
                string recipient;
                cin >> recipient;
                cout << "Enter the amount to send: ";
                int amount;
                cin >> amount;
                if (amount <= balance) {
                    balance -= amount;
                    cout << "Sending " << amount << " to " << recipient << "." << endl;
                    cout << "Your new balance is " << balance << "." << endl;
                } else {
                    cout << "Insufficient funds." << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } else {
        cout << "Maximum number of attempts exceeded. Your account has been locked." << endl;
        sleep_for_seconds(5);
    }

    return 0;
}

