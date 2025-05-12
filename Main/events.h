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
    Event(string n, string desc, string d, string t, string p, int c, int f);
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
    enum AttendeeExperienceLevel { NOT_SET, BEGINNER, INTERMEDIATE, ADVANCED, EXPERT };

    Feedback();
    Feedback(const std::string& reviewerUsername,
             const std::string& eventName,
             const std::string& eventType,
             const std::string& eventDate );

    // Core metrics
    void setOverallFeeling(const std::string& f);
    std::string getOverallFeeling() const;

    void setLikelihoodToRecommend(int score);
    int  getLikelihoodToRecommend() const;

    // Aspect-based ratings
    void setDetailedRating(const std::string& aspect, int rating);
    int  getDetailedRating(const std::string& aspect) const;
    const std::map<std::string,int>& getAllDetailedRatings() const;

    // Qualitative
    void setHighlight(const std::string& h);
    std::string getHighlight() const;
    void setImprovementSuggestion(const std::string& s);
    std::string getImprovementSuggestion() const;

    // Tags
    void addTag(const std::string& tag);
    const std::vector<std::string>& getTags() const;

    // Reviewer context
    void setExperienceLevel(AttendeeExperienceLevel lvl);
    AttendeeExperienceLevel getExperienceLevel() const;
    void setAttendedAnonymously(bool a);
    bool didAttendAnonymously() const;

    // AI hint



// Metadata access
std::string getReviewerUsername() const;
std::string getEventName() const;
std::string getEventType() const;
std::string getSubmissionTimestamp() const;
void setEventDate(const std::string& eventDate);
std::string getEventDate() const;


    // I/O
    void display() const;
    void collectFeedbackInteractive(const std::vector<std::string>& potentialAspects);
    void saveToFile() const;
    bool isSubmittedBeforeEvent() const;

private:
    // helpers you call in .cpp must be declared here:
    static std::string getCurrentTimestamp();
    std::string getExperienceLevelString() const;
    std::string getAutoSentimentString() const;
    static time_t convertTimestampToTime(const std::string& timestamp);
    // actual data members (with trailing underscores to match your .cpp)
    std::string overallFeeling_;
    int         likelihoodToRecommend_;
    std::map<std::string,int> detailedRatings_;
    std::string highlight_, improvementSuggestion_;
    std::vector<std::string> tags_;
    AttendeeExperienceLevel experienceLevel_;
    bool anonymous_;
    std::string eventDate_;
    std::string reviewerUsername_, eventName_, eventType_, submissionTimestamp_;
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
void review_feedbacks(const std::string& username);
void feedback_menu(const std::string& logged_user);
void search_by_name();
void search_by_date();
void search_by_type();
void search_();
void register_event(const string& username);
static set<Event*> getRegesteredEvents(const string& username);
void viewUserEvents(const string& logged_user);


#endif
