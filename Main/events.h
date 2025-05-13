// events.h
#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <chrono>

using namespace std;

extern unordered_set<string> usernames;

class Event {
private:
    string event_name, description, platform, date, time;
    int capacity;
    set <string> registrars;
    bool full;

public:
    Event();
    Event(string n, string desc, string p, string d, string t, int c, int f);
    virtual ~Event() = default;

    virtual void displayDetails() const = 0;
    virtual Event* create_event() = 0;
    virtual void saveToFile(const string& username) = 0;
    bool isFull();
    bool isAlreadyRegistered(const string& username);
    set<string> getRegistrars();
    void addRegister(const string& username);

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
    Conference(string n, string desc, string d, string t, string p, int c, int f, int dur);
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
    Webinar(string n, string desc, string d, string t, string p, int c, int f, string h);
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
    Workshop(string n, string desc, string d, string t, string p, int c, int f, string i);
    ~Workshop() override = default;

    void displayDetails() const override;
    Event* create_event() override;
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line);

    string getType() const override;
    string getInstructor() const;
};

class User {
    string username, password, email, affiliation;
public:
    User();
    User(string u, string p, string e, string a = "");
    virtual ~User() = default;

    void setUsername(string u);
    string getUsername() const;

    void setPassword(string p);
    string getPassword() const;

    void setEmail(string e);
    string getEmail() const;

    void setAffiliation(string a);
    string getAffiliation() const;

    bool operator<(const User& other) const;
};

extern set <Event*> allEvents;

class Feedback {
public:
    Feedback();
    Feedback(const string& reviewerUsername,
             const string& eventName,
             const string& eventType,
             const string& eventDate );

    // General event rating
    void setGeneralRating(int rating);
    int getGeneralRating() const;

    // Aspect-based ratings
    void setDetailedRating(const string& aspect, int rating);
    int  getDetailedRating(const string& aspect) const;
    const map<string,int>& getAllDetailedRatings() const;

    // Qualitative
    void setImprovementSuggestion(const string& s);
    string getImprovementSuggestion() const;

    // Metadata access
    string getReviewerUsername() const;
    string getEventName() const;
    string getEventType() const;
    string getSubmissionTimestamp() const;
    void setEventDate(const string& eventDate);
    string getEventDate() const;

    // I/O
    void display(bool showFutureNotice = false) const;
    bool collectFeedbackInteractive(const vector<string>& potentialAspects);
    void saveToFile() const;
    bool isSubmittedBeforeEvent() const;

private:
    static string getCurrentTimestamp();
    string getAutoSentimentString() const;
    static time_t convertTimestampToTime(const string& timestamp);
    int generalRating_;
    map<string,int> detailedRatings_;
    string improvementSuggestion_;
    string eventDate_;
    string reviewerUsername_, eventName_, eventType_, submissionTimestamp_;
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
User User_Factory(string const& username, string const& password, string const& email, string const& affiliation);
void meeting_postponement(const string& username);
void meeting_cancellation(const string& username);
void review_feedbacks(const string& username);
void feedback_menu(const string& logged_user);
void search_by_name();
void search_by_date();
void search_by_type();
void search_();
void register_event(const string& username);
static set<Event*> getRegesteredEvents(const string& username);
void viewUserEvents(const string& logged_user);


#endif
