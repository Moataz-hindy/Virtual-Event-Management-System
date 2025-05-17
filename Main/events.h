// events.h this is the main header file for event management system
#ifndef EVENTS_H // if the header is not defined, this is the first time including this file
#define EVENTS_H // then define it immediately to prevent future inclusions
// standard library included
#include <string> // to handle strings
#include <set> // used for ordered collections
#include <unordered_set> // used for fast lookups
#include <vector> // used for dynamic arrays
#include <iostream> // used for the i/o operations
#include <fstream> // used for file operations
#include <sstream> // used for string streams
#include <limits> // used for numeric limits
#include <map> // used for ordered key-value storage (std::map)
#include <ctime> // used for time functions
#include <iomanip> // used for output formatting
#include <cctype> // used for character handling
#include <chrono> // used for time management
#include <algorithm>

using namespace std; // using a standard namespace

extern unordered_set<string> usernames; // a global username registry for quick lookups

enum eventType {
    Conference_, Workshop_, Webinar_
};

enum notificationType {
    Event_postponement,Event_cancellation, Event_registration, Event_feedback
};

class User;

class Observer{
public:
    virtual void update(const string& eventName, const string& message ) = 0;
    virtual ~Observer() = default;
};

// an abstract base class called event
class Event {
private:
    string event_name, description, platform, date, time, creator; // private event attributes with event's details
    int capacity; // stores max attendees
    set <string> registrars; // registered users
    bool full; // the max capacity flag
    vector<Observer*> observers_;; // an observer pointer to notify observers
    User* creator_user; // a pointer to the creator user

public:
    Event(); // a default constructor
    Event(string n, string desc, string p, string d, string t, string creator, int c, int f); // a parametrised constructor
    virtual ~Event() = default; // a virtual destructor

    // pure virtual functions
    virtual void displayDetails() const = 0; // shows the event's details
    // Factory Method: Implements the Factory Design Pattern
    static Event* eventBuilder(const eventType Type, const string&);
    virtual void saveToFile(const string& username) = 0; // saves the event to file
    bool isFull(); // checks if the event has reached max capacity
    static bool isRegistered(const string& username, Event* e); // checks if a username is registered for a specific event
    set<string> getRegistrars(); // gets registered users in an event
    bool addRegistrar(const string& username); // adds the user to registrars
    void saveRegistrar(const string& username);
    static void schedule_event(string const& logged_user, Event* event); // a function that allows the user to create + schedule an event
    static void meeting_postponement(const string& username); // a function to handle rescheduling of existing events
    static void meeting_cancellation(const string& username); // a function to cancel any scheduled events
    static void search_by_name(); // searches for events by name
    static void search_by_date(); // searches for events by date
    static void search_by_type(); // searches for events by type
    static void register_event(const string& username); // a function for the user to register into an event
    static void loadEventsData();

    //Observer Methods
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify(notificationType);

    // getter functions to get the event's details
    string getName() const;
    string getDescription() const;
    string getDate() const;
    string getTime() const;
    User* getCreator() const;
    string getPlatform() const;
    int getCapacity() const;
    virtual string getType() const = 0; // gets the event type

    bool operator<(const Event& other) const; // an operator overload
};

// a derived class from base class event called conference
class Conference : public Event{
private:
    int duration; // a private attribute that checks the duration of a conference
public:
    Conference(); // a default constructor
    Conference(string n, string desc, string p, string d, string t, string creator, int c, int dur); // a parametrised constructor
    ~Conference() override = default; // a destructor

    // overridden virtual functions
    void displayDetails() const override;
    // Static Factory Method: Part of Factory Design Pattern
    static Event* create_event(string);
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line); // static type load method/function

    // getter functions
    string getType() const override;
    int getDuration() const;
};

// a derived class from base class event called webinar
class Webinar : public Event {
private:
    string host; // a private attribute that stores the host
public:
    Webinar(); // a default constructor
    Webinar(string n, string desc, string p, string d, string t, string creator, int c, string h); // a parametrised constructor
    ~Webinar() override = default; // a destructor

    // overridden virtual functions
    void displayDetails() const override;
    // Static Factory Method: Part of Factory Design Pattern
    static Event* create_event(string);
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line); // a static type load method/function

    // getter functions
    string getType() const override;
    string getHost() const;
};

// a derived class from base class event called workshop
class Workshop : public Event {
private:
    string instructor; // a private attribute that stores the workshop's instructor
public:
    Workshop(); // a default constructor
    Workshop(string n, string desc, string p, string d, string t, string creator, int c, string i); // a parametrised constructor
    ~Workshop() override = default; // a destructor

    // overridden virtual functions
    void displayDetails() const override;
    // Static Factory Method: Part of Factory Design Pattern
    static Event* create_event(string);
    void saveToFile(const string& username) override;
    static Event* loadFromFile(const string& line); // static type load method/function

    // getter functions
    string getType() const override;
    string getInstructor() const;
};

// a class called User
class User : public Observer {
private:
    string username, password, email, affiliation; // private attributes to store user's info
public:
    User(); // a default constructor
    User(string u, string p, string e, string a = ""); // a parametrised constructor
    virtual ~User() = default; // a virtual destructor

    User User_Factory(string const& username, string const& password, string const& email, string const& affiliation); // a factory pattern implementation for creating new User objects
    virtual void update(const string& eventName, const string& message) override;

    static void signup(); // a function that handles a new user's registration
    static string login(); // a function that handles user authentication + returns logged-in username
    static set<Event*> loadEventsForUser(const string& username); // a function that loads all events registered by a specific user
    static void loadLoginData();
    static void viewUserEvents(const string& logged_user); // a function that displays all events associated with a user
    static set<Event*> get_registered_events(const string& username); // gets all events a user is registered for

    void setUsername(string u); // sets the username
    string getUsername() const; // gets the username

    void setPassword(string p); // sets the password
    string getPassword() const; // gets the passwrod

    void setEmail(string e); // sets the email
    string getEmail() const; // gets the email

    void setAffiliation(string a); // set the affiliation
    string getAffiliation() const; // gets the affiliation

    bool operator<(const User& other) const; // a comparison operator for when we sort/order users
};

extern set <Event*> allEvents; // declares a global set of event pointers

// a class that stores + manages feedback for events
class Feedback {
public:
    Feedback(); // a default constructor
    Feedback(const string& reviewerUsername,
             const string& eventName,
             const string& eventType,
             const string& eventDate ); // a parametrised constructor

    // General event rating
    void setGeneralRating(int rating); // sets general rating
    int getGeneralRating() const; // gets general rating

    // Aspect-based ratings
    void setDetailedRating(const string& aspect, int rating); // sets detailed rating (parameter: reference to aspect + rating)
    int  getDetailedRating(const string& aspect) const; // gets detailed rating (parameter: reference to aspect)
    const map<string,int>& getAllDetailedRatings() const; // gets all aspect ratings

    // Qualitative
    void setImprovementSuggestion(const string& s); // sets the suggestion ( parameters : reference to the string )
    string getImprovementSuggestion() const; // gets the suggestion

    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();

    // Metadata access
    string getReviewerUsername() const;
    string getEventName() const;
    string getEventType() const;
    string getSubmissionTimestamp() const;
    void setEventDate(const string& eventDate); // sets the event date (parameter : reference to event date)
    string getEventDate() const; // gets the event date

    // I/O
    void display(bool) const; // prints the feedback
    bool collectFeedbackInteractive(const vector<string>& potentialAspects); // interactive feedback collection (returns true if submitted)
    void saveToFile() const; // saves feedback to the file
    bool isSubmittedBeforeEvent() const; // checks if the feedback was submitted before the event took place
    static void review_feedbacks(const string& username); // a function that displays feedback for user's events

private:
    static string getCurrentTimestamp(); // gets the current time stamp
    static time_t convertTimestampToTime(const string& timestamp); // converts the timestamp string to time_t (comparisons)
    int generalRating_; // declaration of int variable to store the general rating
    map<string,int> detailedRatings_; // aspect - specific scores
    // declared string variables to store data
    string improvementSuggestion_;
    string eventDate_;
    string reviewerUsername_, eventName_, eventType_, submissionTimestamp_;
    Observer* observer_;
};

class Menu {
public:
    void setup(); // a function that initializes system data + loads saved state
    void start_menu(); // a function that displays the initial starting menu
    void main_menu(string const& logged_user); // the main interface after the user successfully logs in
    void events_menu(string const& logged_user); // a function that displays events related operations
    void search_(); // the main interface for the searching functions
    void feedback_menu(const string& logged_user); // an interface for feedback management
};

template <typename T> void printMultiset(const set<T>& mset); // a utility template to print any set's contents

#endif // end of the EVENTS_H header
