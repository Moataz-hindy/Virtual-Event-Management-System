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

////////////////////////////////////////////////////

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

    Event* Conference::loadFromFile(const string& username){
    ifstream file("events.txt");

    Conference* conference;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUser, name, desc, date, time, platform, capacityStr, durationStr, type;

        getline(ss, type, '|');
        getline(ss, fileUser, '|');
        if (fileUser != username) continue;

        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, platform, '|');
        getline(ss, capacityStr, '|');
        getline(ss, durationStr, '|');

        int capacity = stoi(capacityStr);
        int duration = stoi(durationStr);

        conference = new Conference(name, desc, platform, date, time, capacity, duration);
    }
    return conference;
}
////////////////////////////////////////////////////

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
}

    Event* Webinar::loadFromFile(const string& username){
    ifstream file("events.txt");

    Webinar* webinar;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUser, name, desc, date, time, platform, capacityStr, host, type;
        getline(ss, type, '|');
        getline(ss, fileUser, '|');
        if (fileUser != username) continue;

        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, platform, '|');
        getline(ss, capacityStr, '|');
        getline(ss, host, '|');

        int capacity = stoi(capacityStr);
    
        webinar = new Webinar(name, desc, platform, date, time, capacity, host);

    }
    return webinar;
}

////////////////////////////////////////////////////

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
}

    Event* Workshop::loadFromFile(const string& username){
    ifstream file("events.txt");
    Workshop* workshop;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUser, name, desc, date, time, platform, capacityStr, instructor, type;
        getline(ss, type, '|');
        getline(ss, fileUser, '|');
        if (fileUser != username) continue;

        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, platform, '|');
        getline(ss, capacityStr, '|');
        getline(ss, instructor, '|');

        int capacity = stoi(capacityStr);
        
        
        workshop = new Workshop(name, desc, platform, date, time, capacity, instructor);
    }
    return workshop;
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
multiset<Event*> loadEventsForUser(const string& username) {
    ifstream file("events.txt");
    multiset<Event*> userEvents;

    string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('|');
        string type = line.substr(0, pos);
        if(type == "Conference"){
            Conference* conference = new Conference();
            userEvents.insert(conference->loadFromFile(username));
        }else if(type == "Webinar"){
            Webinar* webinar = new Webinar();
            userEvents.insert(webinar->loadFromFile(username));
        }else if(type == "Workshop"){
            Workshop* workshop = new Workshop();
            userEvents.insert(workshop->loadFromFile(username));
        }
    }

    return userEvents;
}


template <typename T> void printMultiset(const multiset<T>& mset) {
    cout << "Meetings:\n" << "-----------------------------" << endl;
    for (const T& value : mset) {
        value->displayDetails();  // Calls the displayDetails() method
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


void signout(unordered_set<string>& usernames){
    //TODO: finish signout()
    start_menu(usernames);
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
            main_menu(login(), usernames);
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

void main_menu(string const& logged_user, unordered_set<string>& usernames) {
    int choice;
    cout << "\nPlease choose one of these options:" << endl;
    cout << "1) Schedule Meeting" << endl;
    cout << "2) Open Calendar for user" << endl;
    cout << "3) Sign out" << endl;
    cout << "4) Exit" << endl;
    cout << "Enter a number: ";
    cin >> choice;

    switch (choice) {
    case 1:
        events_menu(logged_user, usernames);
        main_menu(logged_user, usernames);
    break;
    case 2:
        printMultiset(loadEventsForUser(logged_user));
        main_menu(logged_user, usernames);
    break;
    case 3:
        signout(usernames);
        break;
    case 4:
        exit(0);
    default:
        cout << "Invalid choice, please choose 1, 2 or 3." << endl;
    }
}

void events_menu(string const& logged_user, unordered_set<string>& usernames){
    Event* event;
    int choice;
    cout << "\nPlease choose the type of the event:" << endl;
    cout << "1) Conference" << endl;
    cout << "2) Webinar" << endl;
    cout << "3) Workshop" << endl;
    cout << "4) Exit" << endl;
    cout << "Enter a number: ";
    cin >> choice;

    switch (choice) {
    case 1:
        event = new Conference();
        schedule_event(logged_user, event);
    break;
    case 2:
        event = new Webinar();
        schedule_event(logged_user, event);
    break;
    case 3:
        event = new Workshop();
        schedule_event(logged_user, event);
    break;
    case 4:
        main_menu(logged_user, usernames);
    break;
    default:
        cout << "Invalid choice, please choose 1, 2 or 3." << endl;
    }
}

void schedule_event(string const& logged_user, Event* event) {

    event = event->create_event();

    static multiset<Event*> eventList;
    eventList.insert(event);

    event->saveToFile(logged_user);
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
