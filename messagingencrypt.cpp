#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string encryptPassword(const string& password) {
    string encryptedPassword = password;

    // Encrypt the password (example: shift each character by 1)
    for (char& c : encryptedPassword) {
        if (c != ' ') {
            c = (c - 'a' + 1) % 26 + 'a';
        }
    }

    return encryptedPassword;
    
}
    
struct SMS {
    string sender;
    string receiver;
    string message;
};

class User {
public:
    string username;
    string password;
    double balance;

    User(const string& username, const string& password, double balance)
        : username(username), password(password), balance(balance) {}
};

class SMSApplication {
private:
    vector<User> userList;
    vector<SMS> smsList;
    string currentUser;
    string logFile = "sms_log.txt";

public:
    SMSApplication() {}

    void registerUser(const string& username, const string& password, double initialBalance) {
        string encryptedPassword = encryptPassword(password);

    // Create a new user object with the encrypted password
    User newUser = {username, encryptedPassword, initialBalance};

    // Add the user to the userList
    userList.push_back(newUser);

    cout << "User registered successfully: " << username << "\n\n";
       
    }

   bool loginUser(const string& username, const string& password) {
    // Encrypt the entered password
    string encryptedPassword = encryptPassword(password);

    // Find the user in the userList
    for (const auto& user : userList) {
        if (user.username == username && user.password == encryptedPassword) {
            cout << "Logged in successfully as user: " << username << "\n\n";
            currentUser = username;
            return true;
        }
    }

    cout << "Invalid username or password. Login failed!\n\n";
    return false;
}


    void rechargeBalance(double amount) {
        // Find the user in the userList
        User* currentUserPtr = nullptr;
        for (auto& user : userList) {
            if (user.username == currentUser) {
                currentUserPtr = &user;
                break;
            }
        }

        if (currentUserPtr == nullptr) {
            cout << "Current user not found!\n\n";
            return;
        }

        currentUserPtr->balance += amount;
        cout << "Balance successfully recharged. Current balance: $" << currentUserPtr->balance << "\n\n";
    }

    void sendSMS(const string& receiver, const string& message) {
        SMS sms;
        sms.sender = currentUser;
        sms.receiver = receiver;
        sms.message = message;

        // Check if the receiver name matches the current user
        bool validReceiver = false;

        for (const auto& user : userList) {
            if (user.username == receiver) {
                validReceiver = true;
                break;
            }
        }

        if (!validReceiver) {
            cout << "Invalid receiver name. You can only send messages to registered usernames.\n\n";
            return;
        }

        // Find the user in the userList
        User* senderUser = nullptr;
        for (auto& user : userList) {
            if (user.username == currentUser) {
                senderUser = &user;
                break;
            }
        }

        if (senderUser == nullptr) {
            cout << "Sender user not found!\n\n";
            return;
        }

        // Calculate the cost based on the length of the message
        double cost = 0.05 * message.length();

        // Check if there is enough balance to send the SMS
        if (senderUser->balance < cost) {
            cout << "Insufficient balance to send SMS!\n\n";
            return;
        }

        // Deduct the cost from the sender's balance
        senderUser->balance -= cost;

        // Simulate sending the SMS
        cout << "Sending SMS:\n"
             << "Sender: " << sms.sender << "\n"
             << "Receiver: " << sms.receiver << "\n"
             << "Message: " << sms.message << "\n"
             << "SMS sent successfully!\n\n";

        // Add the sent SMS to the list
        smsList.push_back(sms);

        // Log the sent SMS
        logSMS(sms);
    }

    void receiveSMS() {
        bool foundSMS = false;
        cout << "Received SMSs for user " << currentUser << ":\n";
        for (const auto& sms : smsList) {
            if (sms.receiver == currentUser) {
                cout << "Sender: " << sms.sender << "\n"
                     << "Message: " << sms.message << "\n\n";
                foundSMS = true;
            }
        }

        if (!foundSMS) {
            cout << "No SMSs found for the current user.\n\n";
        }
    }

    void displayBalance() {
        // Find the user in the userList
        User* currentUserPtr = nullptr;
        for (auto& user : userList) {
            if (user.username == currentUser) {
                currentUserPtr = &user;
                break;
            }
        }

        if (currentUserPtr == nullptr) {
            cout << "Current user not found!\n\n";
            return;
        }

        cout << "Balance for user " << currentUser << ": $" << currentUserPtr->balance << "\n\n";
    }

    void changePassword(const string& newPassword) {
        // Find the user in the userList
        for (auto& user : userList) {
            if (user.username == currentUser) {
                user.password = newPassword;
                cout << "Password changed successfully for user: " << currentUser << "\n\n";
                return;
            }
        }
        cout << "User not found. Password change failed!\n\n";
    }

    void logSMS(const SMS& sms) {
        ofstream file(logFile, ios::app);
        if (file.is_open()) {
            file << "Sender: " << sms.sender << "\n"
                 << "Receiver: " << sms.receiver << "\n"
                 << "Message: " << sms.message << "\n\n";
            file.close();
        }
        else {
            cout << "Failed to log SMS to file!\n\n";
        }
    }
};

int main() {
    SMSApplication smsApp;

    int choice;
    bool exitProgram = false;
    bool loggedIn = false;
    string username, password, receiver, message, newPassword;
    double initialBalance, rechargeAmount;

    while (!exitProgram) {
        cout << "----- SMS Application -----\n";
        if (!loggedIn) {
            cout << "1. Register\n";
            cout << "2. Login\n";
        }
        else {
            cout << "3. Send SMS\n";
            cout << "4. Receive SMS\n";
            cout << "5. Check Balance\n";
            cout << "6. Recharge Balance\n";
            cout << "7. Change Password\n";
            cout << "8. Logout\n";
        }
        cout << "9. Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1:
            if (!loggedIn) {
                cout << "----- Register -----\n";
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                cout << "\n";

                smsApp.registerUser(username, password, initialBalance);
            }
            else {
                cout << "You are already logged in. Please logout to register a new user.\n\n";
            }
            break;

        case 2:
            if (!loggedIn) {
                cout << "----- Login -----\n";
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "\n";

                loggedIn = smsApp.loginUser(username, password);
            }
            else {
                cout << "You are already logged in. Please logout to login as a different user.\n\n";
            }
            break;

        case 3:
            if (loggedIn) {
                cout << "----- Send SMS -----\n";
                cout << "Enter receiver username: ";
                cin >> receiver;
                cout << "Enter message: ";
                cin.ignore();
                getline(cin, message);
                cout << "\n";

                smsApp.sendSMS(receiver, message);
            }
            else {
                cout << "You need to login first to send an SMS.\n\n";
            }
            break;

        case 4:
            if (loggedIn) {
                cout << "----- Receive SMS -----\n";
                smsApp.receiveSMS();
            }
            else {
                cout << "You need to login first to receive SMSs.\n\n";
            }
            break;

        case 5:
            if (loggedIn) {
                cout << "----- Check Balance -----\n";
                smsApp.displayBalance();
            }
            else {
                cout << "You need to login first to check your balance.\n\n";
            }
            break;

        case 6:
            if (loggedIn) {
                cout << "----- Recharge Balance -----\n";
                cout << "Enter recharge amount: ";
                cin >> rechargeAmount;
                cout << "\n";

                smsApp.rechargeBalance(rechargeAmount);
            }
            else {
                cout << "You need to login first to recharge your balance.\n\n";
            }
            break;

        case 7:
            if (loggedIn) {
                cout << "----- Change Password -----\n";
                cout << "Enter new password: ";
                cin >> newPassword;
                cout << "\n";

                smsApp.changePassword(newPassword);
            }
            else {
                cout << "You need to login first to change your password.\n\n";
            }
            break;

        case 8:
            if (loggedIn) {
                loggedIn = false;
                cout << "Logged out successfully!\n\n";
            }
            else {
                cout << "You are not logged in.\n\n";
            }
            break;

        case 9:
            exitProgram = true;
            break;

        default:
            cout << "Invalid choice! Please try again.\n\n";
            break;
        }
    }

    cout << "Thank you for using the SMS Application!\n";

    return 0;
}
