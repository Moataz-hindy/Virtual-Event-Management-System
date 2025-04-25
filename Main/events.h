// events.h
#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

extern unordered_set<string> usernames;

class Event {
private:
    string event_name, description, platform, date, time;
    int capacity;

public:
    Event();
    Event(string n, string desc, string d, string t, string p, int c);
    virtual ~Event() = default;

    virtual void displayDetails() const = 0;
    virtual Event* create_event() = 0;
    virtual void saveToFile(const string& username) = 0;

    string getName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    string getPlatform() const;
    int getCapacity() const;
    virtual string getType() const = 0;

    bool operator<(const Event& other) const;
};

class Conference : public Event {
private:
    int duration;
public:
    Conference();
    Conference(string n, string desc, string d, string t, string p, int c, int dur);
    ~Conference() override = default;

    void displayDetails() const override;
    Event* create_event() override;
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line);

    string getType() const override;
    int getDuration() const;
};

class Webinar : public Event {
private:
    string host;
public:
    Webinar();
    Webinar(string n, string desc, string d, string t, string p, int c, string h);
    ~Webinar() override = default;

    void displayDetails() const override;
    Event* create_event() override;
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line);

    string getType() const override;
    string getHost() const;
};

class Workshop : public Event {
private:
    string instructor;
public:
    Workshop();
    Workshop(string n, string desc, string d, string t, string p, int c, string i);
    ~Workshop() override = default;

    void displayDetails() const override;
    Event* create_event() override;
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line);

    string getType() const override;
    string getInstructor() const;
};

class User {
    string username, password;
public:
    User();
    User(string u, string p);
    virtual ~User() = default;

    void setUsername(string u);
    string getUsername() const;

    void setPassword(string p);
    string getPassword() const;

    bool operator<(const User& other) const;
};

class Attendee : public User {
private:
    string affiliation;
public:
    Attendee();
    Attendee(string u, string p, string a);
    ~Attendee() override = default;

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
    ~Feedback() = default;

    void display() const;

    int getRating() const;
    string getReview() const;
};

void setup();
void start_menu();
void signup();
string login();
void main_menu(string const& logged_user);
void events_menu(string const& logged_user);
void schedule_event(string const& logged_user, Event* event);
set<Event*> loadEventsForUser(const string& username);
template <typename T> void printMultiset(const set<T>& mset);
User User_Factory(string const& username, string const& password);

#endif
