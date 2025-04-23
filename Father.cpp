#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <set>
#include <sstream>
#include <limits>

using namespace std;

class Event {
private:
    string event_name, description, platform, date, time, type;
    int capacity;

public:
    // Used to store Events in set in order of Dates
    bool operator<(const Event& other) const {
        return (date == other.date) ? (time < other.time) : (date < other.date);
    }

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

class User {
    string username, password;
public:
    User() {};
    User(string u, string p): username(u), password(p){}

    void setUsername(string u) { username = u; }
    string getUsername() const { return username; }

    void setPassword(string p) { password = p; }
    string getPassword() const { return password; }

    // Used to store Users in set in alphabetical order.
    bool operator<(const User& other) const {
        return username < other.username;
    }


};

class Attendee : public User {
private:
    string affiliation;

public:
    Attendee() {}
    Attendee(string u, string p, string a) : User(u,p), affiliation(a) {}

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

void main_menu(string const& logged_user, unordered_set<string>& usernames);
void schedule_event(string const& logged_user);
void setup();

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
    cout << "\nUser Events:\n";
    cout << "-----------------------------" << endl;
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
            exit;
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

    while (true) {
        cout << "Enter username: ";
        cin >> username;

        if (usernames.count(username)) {
            cout << "Username is taken!" << endl;
            continue;
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
        break;
    }
}

void start_menu(unordered_set<string>& usernames) {
    int choice;
    while (true) {
        cout << "\nPlease choose one of these options:" << endl;
        cout << "1) Login" << endl;
        cout << "2) Signup" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter a number: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                main_menu(login(), usernames);
                return;
            case 2:
                signup(usernames);
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        }
    }
}

void main_menu(string const& logged_user, unordered_set<string>& usernames) {
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
                start_menu(usernames);
                exit(0);
            default:
                cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        }
    }
}

Event Event_Factory() {
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

User User_Factory(string const& username, string const& password) {
    return User(username, password);
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
    Event const e = Event_Factory();
    eventList.insert(e);

    saveEventToFile(e,logged_user);
}

void setup() {
    unordered_set<string> usernames;
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

    start_menu(usernames);
}

int main() {
    setup();
    return 0;
}
