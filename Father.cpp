#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

void login() {
    string username, password;
    bool loginSuccess = false;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream users("loginDataBase.txt");
    if (!users.is_open()) {
        cout << "Error: Unable to open database file!" << endl;
        return;
    }

    string fileUsername, filePassword;
    while (users >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            loginSuccess = true;
            break;
        }
    }

    users.close();

    if (loginSuccess) {
        cout << "Welcome, " << username << "!" << endl;
    } else {
        cout << "Invalid username or password!" << endl;
        login(); // optionally loop back for retry
    }
}

void signup(unordered_set<string>& usernames) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (usernames.count(username)) {
        cout << "Username is taken!" << endl;
        signup(usernames);
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream users("loginDataBase.txt", ios::app);
    if (!users.is_open()) {
        cout << "Error: Unable to open database file!" << endl;
        return;
    }

    users << username << " " << password << "\n";
    users.close();
    usernames.insert(username);

    cout << "Signup successful!" << endl;
}

void start_menu(unordered_set<string>& usernames) {
    int choice;
    cout << "\nPlease choose one of these options:" << endl;
    cout << "1) Login" << endl;
    cout << "2) Signup" << endl;
    cout << "3) Exit" << endl;
    cout << "Enter a number: ";
    cin >> choice;

    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            signup(usernames);
            start_menu(usernames);
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice, please choose 1, 2 or 3." << endl;
            start_menu(usernames);
    }
}

void setup() {
    unordered_set<string> usernames;
    string userName, dummy;
    ifstream users("loginDataBase.txt");

    while (users >> userName >> dummy) {
        usernames.insert(userName);
    }
    users.close();

    cout << "=========================" << endl;
    cout << "=========WELCOME=========" << endl;
    cout << "=========================" << endl;

    start_menu(usernames);
}

class Event {
private:
    string event_name, description, platform, date, time, type;
    int capacity;

public:
    Event() {} // default constructor
    Event(string n, string desc, string d, string t, string p, int c, string typ)
        : event_name(n), description(desc), date(d), time(t), platform(p), capacity(c), type(typ) {}

    void displayDetails() const {
        cout << "Event: " << event_name << " (" << type << ")" << endl;
        cout << "Date: " << date << " at " << time << endl;
        cout << "Platform: " << platform << endl;
        cout << "Description: " << description << endl;
        cout << "Capacity: " << capacity << endl;
    }

    string getName() const { return event_name; }
    string getDescription() const { return description; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getPlatform() const { return platform; }
    int getCapacity() const { return capacity; }
    string getType() const { return type; }
};

class Attendee {
private:
    string name, email, affiliation;

public:
    Attendee() {}
    Attendee(string n, string e, string a) : name(n), email(e), affiliation(a) {}

    void setEmail(string e) { email = e; }
    string getEmail() const { return email; }

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setAffiliation(string a) { affiliation = a; }
    string getAffiliation() const { return affiliation; }
};

class Feedback {
private:
    string name;
    int rating;
    string review;

public:
    Feedback() {}
    Feedback(string n, int ra, string re)
        : name(n), rating(ra), review(re) {
        if (rating < 0) rating = 0;
        if (rating > 5) rating = 5;
    }

    void display() const {
        cout << name << " rated " << rating << " out of 5" << endl;
        cout << "Review: " << review << endl;
    }

    int getRating() const { return rating; }
    string getReview() const { return review; }
};

int main() {
    setup();
    return 0;
}
