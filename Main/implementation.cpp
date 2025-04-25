
#include "events.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <set>
#include <sstream>
#include <limits>

using namespace std;

unordered_set<string> usernames;

//////////////////////////User//////////////////////////
User::User(){}
User::User(string u, string p): username(u), password(p){}

void User::setUsername(string u) { username = u; }
string User::getUsername() const { return username; }

void User::setPassword(string p) { password = p; }
string User::getPassword() const { return password; }

    // Used to store Users in set in alphabetical order.
bool User::operator<(const User& other) const {
        return username < other.username;
    }


///////////////////////////Event/////////////////////////
Event::Event(){}
Event::Event(string n, string desc, string p, string d, string t, int c)
    : event_name(n), description(desc), platform(p), date(d), time(t), capacity(c) {}



//Implemtation of getter functions
string Event::getName() const { return event_name; }
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getTime() const { return time; }
string Event::getPlatform() const { return platform; }
int Event::getCapacity() const { return capacity; }

bool Event::operator<(const Event& other) const {
    return (date == other.date) ? (time < other.time) : (date < other.date);
}
////////////////////////Conference////////////////////////////
Conference::Conference(){}
Conference::Conference(string n, string desc, string p, string d, string t, int c, int dur)
    : Event(n, desc, p, d, t, c), duration(dur) {}

string Conference::getType() const{ return "Conference";}
int Conference::getDuration() const{ return duration;}

Event* Conference::create_event(){
    string name, desc, platform, date, time;
    int capacity, duration;

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
    cout << "Enter capacity: ";
    cin >> capacity;
    cout << "Enter Duration (In days): ";
    cin >> duration;

    Conference* conference = new Conference(name, desc, platform, date, time, capacity, duration);
    return conference;
}

void Conference::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Duration: " << getDuration() << " days" << endl;
}

void Conference::saveToFile(const string& username){
    ofstream file("events.txt", ios::app); // append mode
    if (!file.is_open()) {
        cout << "Error opening events file!" << endl;
        return;
    }

    file << this->getType() << '|'
        << username << "|"
        << this->getName() << "|"
        << this->getDescription() << "|"
        << this->getDate() << "|"
        << this->getTime() << "|"
        << this->getPlatform() << "|"
        << this->getCapacity() << "|"
        << this->getDuration() << "\n";
}

Event* Conference::loadFromFile(const string& line){

    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, durationStr, type;
    getline(ss, type, '|');
    getline(ss, fileUser, '|');

    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, durationStr, '|');

    int capacity = stoi(capacityStr);
    int duration = stoi(durationStr);

    Conference* conference = new Conference(name, desc, platform, date, time, capacity, duration);

    return conference;
}
/////////////////////////Webinar///////////////////////////
Webinar::Webinar(){}
Webinar::Webinar(string n, string desc, string p, string d, string t, int c, string h)
    : Event(n, desc, p, d, t, c), host(h) {}

string Webinar::getType() const{ return "Webinar";}
string Webinar::getHost() const{ return host;}

void Webinar::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Host: " << getHost() << endl;
}

Event* Webinar::create_event(){
    string name, desc, platform, date, time, host;
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
    cout << "Enter capacity: ";
    cin >> capacity;
    cin.ignore();
    cout << "Enter Host: ";
    getline(cin, host);

    Webinar* webinar = new Webinar(name, desc, platform, date, time, capacity, host);
    return webinar;
}


void Webinar::saveToFile(const string& username){
    ofstream file("events.txt", ios::app); // append mode
    if (!file.is_open()) {
        cout << "Error opening events file!" << endl;
        return;
    }

    file << this->getType() << '|'
        << username << "|"
        << this->getName() << "|"
        << this->getDescription() << "|"
        << this->getDate() << "|"
        << this->getTime() << "|"
        << this->getPlatform() << "|"
        << this->getCapacity() << "|"
        << this->getHost() << "\n";
    file.close();
}

Event* Webinar::loadFromFile(const string& line){
    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, host, type;
    getline(ss, type, '|');
    getline(ss, fileUser, '|');

    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, host, '|');

    int capacity = stoi(capacityStr);

    Webinar* webinar = new Webinar(name, desc, platform, date, time, capacity, host);

    return webinar;
}
////////////////////////////Workshop////////////////////////
Workshop::Workshop(){}
Workshop::Workshop(string n, string desc, string p, string d, string t, int c, string i)
    : Event(n, desc, p, d, t, c), instructor(i) {}

string Workshop::getType() const{ return "Workshop";}
string Workshop::getInstructor() const{ return instructor;}

void Workshop::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Instructor: " << getInstructor() << endl;
}

Event* Workshop::create_event(){
    string name, desc, platform, date, time, instructor;
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
    cout << "Enter capacity: ";
    cin >> capacity;
    cin.ignore();
    cout << "Enter Instructor: ";
    getline(cin, instructor);

    Workshop* workshop = new Workshop(name, desc, platform, date, time, capacity, instructor);
    return workshop;
}

void Workshop::saveToFile(const string& username){
    ofstream file("events.txt", ios::app); // append mode
    if (!file.is_open()) {
        cout << "Error opening events file!" << endl;
        return;
    }

    file << this->getType() << '|'
        << username << "|"
        << this->getName() << "|"
        << this->getDescription() << "|"
        << this->getDate() << "|"
        << this->getTime() << "|"
        << this->getPlatform() << "|"
        << this->getCapacity() << "|"
        << this->getInstructor() << "\n";
    file.close();
}

Event* Workshop::loadFromFile(const string& line){

    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, instructor, type;
    getline(ss, type, '|');
    getline(ss, fileUser, '|');

    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, instructor, '|');

    int capacity = stoi(capacityStr);

    Workshop* workshop = new Workshop(name, desc, platform, date, time, capacity, instructor);
    return workshop;
}
////////////////////////Attendee////////////////////////////
Attendee::Attendee() {}
Attendee::Attendee(string u, string p, string a) : User(u,p), affiliation(a) {}


void Attendee::setAffiliation(string a) { affiliation = a; }
string Attendee::getAffiliation() const { return affiliation; }
////////////////////////Feedback////////////////////////////
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
set<Event*> loadEventsForUser(const string& username) {
    ifstream file("events.txt");
    set<Event*> userEvents;

    string line, type, fileUser;
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, type, '|'); // Read event type
        getline(iss, fileUser, '|'); // Read username
        if (fileUser == username) {
            if (type == "Conference") {
                userEvents.insert(Conference::loadFromFile(line));
            } else if (type == "Webinar") {
                userEvents.insert(Webinar::loadFromFile(line));
            } else if (type == "Workshop") {
                userEvents.insert(Workshop::loadFromFile(line));
            }
        }
    }

    file.close();
    return userEvents;
}

User User_Factory(string const& username, string const& password) {
    return User(username, password);
}

template <typename T> void printMultiset(const set<T>& mset) {
    cout << "Meetings:\n" << "-----------------------------" << endl;
    for (const T& value : mset) {
        value->displayDetails();  // Calls the displayDetails() method
        cout << "-----------------------------" << endl;  // Optional separator
    }
    cout << endl;
    for (Event* e : mset) {
        delete e;
    }
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

void signup() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (usernames.count(username)) {
        cout << "Username is taken!" << endl;
        signup();
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

void start_menu() {
    int choice;
    while (true){
        cout << "\nPlease choose one of these options:" << endl;
        cout << "1) Login" << endl;
        cout << "2) Signup" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter a number: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                main_menu(login());
                return;
            case 2:
                signup();
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        }
    }
}

void main_menu(string const& logged_user) {
    int choice;
    while (true) {
        cout << "\nPlease choose one of these options:" << endl;
        cout << "1) Schedule Meeting" << endl;
        cout << "2) Open Calendar for user" << endl;
        cout << "3) Sign out" << endl;
        cout << "Enter a number: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            events_menu(logged_user);
            break;
        case 2:
            printMultiset(loadEventsForUser(logged_user));
            break;
        case 3:
            start_menu();
            return;
        default:
            cout << "Invalid choice, please choose 1, 2, or 3." << endl;
        }
    }
}

void events_menu(string const& logged_user) {
    Event* event;
    int choice;

    while (true) {
        cout << "\nPlease choose the type of the event:" << endl;
        cout << "1) Conference" << endl;
        cout << "2) Webinar" << endl;
        cout << "3) Workshop" << endl;
        cout << "4) Exit" << endl;
        cout << "Enter a number: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        Event* tempEvent = nullptr;
        switch (choice) {
        case 1:
            tempEvent = new Conference();
            schedule_event(logged_user, tempEvent);
            break;
        case 2:
            tempEvent = new Webinar();
            schedule_event(logged_user, tempEvent);
            break;
        case 3:
            tempEvent = new Workshop();
            schedule_event(logged_user, tempEvent);
            break;
        case 4:
            main_menu(logged_user);
            return;
        default:
            cout << "Invalid choice, please choose 1, 2, 3, or 4." << endl;
        }
    }
}

void schedule_event(string const& logged_user, Event* event) {
    Event* newEvent = event->create_event();
    delete event;  // Delete the temporary object we created in events_menu()

    static set<Event*> eventList;
    eventList.insert(newEvent);

    newEvent->saveToFile(logged_user);
}

void setup() {
    set<User> Users;
    string userName, password;
    ifstream users("loginDataBase.txt");

    while (users >> userName >> password) {
        Users.insert(User_Factory(userName, password));
        usernames.insert(userName);
    }
    users.close();

    cout << "=========================" << endl;
    cout << "=========WELCOME=========" << endl;
    cout << "=========================" << endl;

    start_menu();
}
