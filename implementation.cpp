#include "events.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <set>
#include <sstream>


using namespace std;

////////////////////////////////////////////////////

Event::Event(){}
Event::Event(string n, string desc, string p, string d, string t, int c, string typ)
    : event_name(n), description(desc), platform(p), date(d), time(t), type(typ), capacity(c) {}

void Event::displayDetails() const {
    cout << "Event: " << event_name << " (" << type << ")" << endl;
    cout << "Date: " << date << " at " << time << endl;
    cout << "Platform: " << platform << endl;
    cout << "Description: " << description << endl;
    cout << "Capacity: " << capacity << endl;
}

//Implemtation of getter functions
string Event::getName() const { return event_name; }
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getTime() const { return time; }
string Event::getPlatform() const { return platform; }
int Event::getCapacity() const { return capacity; }
string Event::getType() const { return type; }

bool Event::operator<(const Event& other) const {
    return (date == other.date) ? (time < other.time) : (date < other.date);
}

////////////////////////////////////////////////////

Attendee::Attendee() {}
Attendee::Attendee(string n, string e, string a) : name(n), email(e), affiliation(a) {}

void Attendee::setEmail(string e) { email = e; }
string Attendee::getEmail() const { return email; }

void Attendee::setName(string n) { name = n; }
string Attendee::getName() const { return name; }

void Attendee::setAffiliation(string a) { affiliation = a; }
string Attendee::getAffiliation() const { return affiliation; }

////////////////////////////////////////////////////



Feedback::Feedback() {}
Feedback::Feedback(string n, int ra, string re)
    : name(n), rating(ra), review(re) {
    if (rating < 0) rating = 0;
    if (rating > 5) rating = 5;
}

void Feedback::display() const {
    cout << name << " rated " << rating << " out of 5" << endl;
    cout << "Review: " << review << endl;
}
int Feedback::getRating() const { return rating; }
string Feedback::getReview() const { return review; }

////////////////////////////////////////////////////
multiset<Event> loadEventsForUser(const string& username) {
    ifstream file("events.txt");
    multiset<Event> userEvents;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUser, name, desc, date, time, platform, capacityStr, type;

        getline(ss, fileUser, '|');
        if (fileUser != username) continue;

        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, platform, '|');
        getline(ss, capacityStr, '|');
        getline(ss, type, '|');

        int capacity = stoi(capacityStr);
        Event e(name, desc, date, time, platform, capacity, type);
        userEvents.insert(e);
    }

    return userEvents;
}


template <typename T>
void printMultiset(const multiset<T>& mset) {
    cout << "Meetings:\n" << "-----------------------------" << endl;
    for (const T& value : mset) {
        value.displayDetails();  // Calls the displayDetails() method
        cout << "-----------------------------" << endl;  // Optional separator
    }
    cout << endl;
}

string login() {
    string username, password;

    while (true) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream users("loginDataBase.txt");
        if (!users.is_open()) {
            cout << "Error: Unable to open database file!" << endl;
            exit(0);
            return ""; // Use empty string instead of nullptr for string return type
        }

        string fileUsername, filePassword;
        bool loginSuccess = false;

        while (users >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                loginSuccess = true;
                break;
            }
        }

        users.close();

        if (loginSuccess) {
            cout << "Welcome, " << username << "!" << endl;
            return username;
        } else {
            cout << "Invalid username or password! Please try again." << endl;
        }
    }
}

void signup(unordered_set<string>& usernames) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (usernames.count(username)) {
        cout << "Username is taken!" << endl;
        signup(usernames);
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
            main_menu(login());
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

void main_menu(string const& logged_user) {
    while (true) {
        int choice;
        cout << "\nPlease choose one of these options:" << endl;
        cout << "1) Schedule Meeting" << endl;
        cout << "2) Open Calendar for user" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter a number: ";
        cin >> choice;

        switch (choice) {
            case 1:
                schedule_event(logged_user);
            break;
            case 2:
                printMultiset(loadEventsForUser(logged_user));
            break;
            case 3:
                setup();
                exit(0);
            default:
                cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        }
    }
}

Event createEvent_Factory() {
    string name, desc, platform, date, time, type;
    int capacity;

    cin.ignore();
    cout << "Enter event name: ";
    getline(cin, name);
    cout << "Enter description: ";
    getline(cin, desc);
    cout << "Enter platform: ";
    getline(cin, platform);
    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter time (HH:MM): ";
    getline(cin, time);
    cout << "Enter type: ";
    getline(cin, type);
    cout << "Enter capacity: ";
    cin >> capacity;

    return Event(name, desc, date, time, platform, capacity, type);
}

void saveEventToFile(const Event& e, const string& username) {
    ofstream file("events.txt", ios::app); // append mode
    if (!file.is_open()) {
        cout << "Error opening events file!" << endl;
        return;
    }

    file << username << "|"
        << e.getName() << "|"
        << e.getDescription() << "|"
        << e.getDate() << "|"
        << e.getTime() << "|"
        << e.getPlatform() << "|"
        << e.getCapacity() << "|"
        << e.getType() << "\n";

    file.close();
}

void schedule_event(string const& logged_user) {
    static multiset<Event> eventList;
    Event const e = createEvent_Factory();
    eventList.insert(e);

    saveEventToFile(e,logged_user);
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

int main() {
    setup();
    return 0;
}
