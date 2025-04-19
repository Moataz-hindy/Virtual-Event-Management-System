
#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <set>


using namespace std;


class Event{
    private:
    string event_name, description, platform, date, time, type;
    int capacity;

    public:
    //Constructors
    Event();
    Event(string n, string desc, string d, string t, string p, int c, string typ);

    //Member functions
    void displayDetails() const;

    //Getter methods
    string getName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getPlatform() const;
    int getCapacity() const;
    string getType() const;

    // Used to store Events in set in order of Dates
    bool operator<(const Event& other) const;
};

class Attendee {
private:
    string name, email, affiliation;

public:
    Attendee();
    Attendee(string n, string e, string a);

    void setEmail(string e);
    string getEmail() const;

    void setName(string n);
    string getName() const;

    void setAffiliation(string a);
    string getAffiliation() const;
};

class Feedback {
private:
    string name;
    int rating;
    string review;

public:
    Feedback() {}
    Feedback(string n, int ra, string re);

    void display() const;

    int getRating() const;
    string getReview() const;
};

//Functions definitions
void setup();
void start_menu(unordered_set<string>& usernames);
void signup(unordered_set<string>& usernames);
string login();
void main_menu(string const& logged_user);
void schedule_event(string const& logged_user);
Event createEvent_Factory();
void saveEventToFile(const Event& e, const string& username);
multiset<Event> loadEventsForUser(const string& username);
template <typename T> void printMultiset(const multiset<T>& mset);

#endif
