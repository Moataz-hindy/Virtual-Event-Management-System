#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <set>
#include <unordered_set>


using namespace std;


class Event{
    private:
    string event_name, description, platform, date, time;
    int capacity;

    public:
    //Constructors
    Event();
    Event(string n, string desc, string d, string t, string p, int c);

    //Member functions
    virtual void displayDetails() const = 0;
    virtual Event* create_event() = 0;
    virtual void saveToFile(const string& username) = 0;
    virtual Event* loadFromFile(const string& username) = 0;

    //Getter methods
    string getName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getPlatform() const;
    int getCapacity() const;
    virtual string getType() const = 0;

    // Used to store Events in set in order of Dates
    bool operator<(const Event& other) const;
};

class Conference : public Event{
    private:
    int duration;
    public:
    Conference();
    Conference(string n, string desc, string d, string t, string p, int c, int dur);

    void displayDetails() const;
    Event* create_event();
    void saveToFile(const string& username);
    Event* loadFromFile(const string& username);

    string getType() const;
    int getDuration() const;
};

class Webinar : public Event{
    private:
    string host;
    public:
    Webinar();
    Webinar(string n, string desc, string d, string t, string p, int c, string h);

    void displayDetails() const;
    Event* create_event();
    void saveToFile(const string& username);
    Event* loadFromFile(const string& username);

    string getType() const;
    string getHost() const;
};

class Workshop : public Event{
    private:
    string instructor;
    public:
    Workshop();
    Workshop(string n, string desc, string d, string t, string p, int c, string i);

    void displayDetails() const;
    Event* create_event();
    void saveToFile(const string& username);
    Event* loadFromFile(const string& username);

    string getType() const;
    string getInstructor() const;
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
    Feedback();
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
void main_menu(string const& logged_user, unordered_set<string>& usernames);
void events_menu(string const& logged_user, unordered_set<string>& usernames);
void signout(unordered_set<string>& usernames);
void schedule_event(string const& logged_user, Event* event);
multiset<Event*> loadEventsForUser(const string& username);
template <typename T> void printMultiset(const multiset<T>& mset);

#endif
