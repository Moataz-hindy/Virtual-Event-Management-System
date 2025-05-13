#include "events.h"

set<User> Users; // haven't used yet
unordered_set<string> usernames;
set<Event*> allEvents;


//////////////////////////   User   //////////////////////////
User::User(){}
User::User(string u, string p, string e, string a): username(u), password(p), email(e), affiliation(a){}

void User::setUsername(string u) { username = u; }
string User::getUsername() const { return username; }

void User::setPassword(string p) { password = p; }
string User::getPassword() const { return password; }

void User::setAffiliation(string a){ affiliation = a; }
string User::getAffiliation() const{ return affiliation; }

void User::setEmail(string e){ email = e; }
string User::getEmail() const{ return email; }

    // Used to store Users in set in alphabetical order.
bool User::operator<(const User& other) const {
        return username < other.username;
    }
///////////////////////////   Event   /////////////////////////
Event::Event(){}
Event::Event(string n, string desc, string p, string d, string t, int c, int f)
    : event_name(std::move(n)), description(desc), platform(p), date(d), time(t), capacity(c), full(f){}

//Implemtation of getter functions
string Event::getName() const { return event_name; }
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getTime() const { return time; }
string Event::getPlatform() const { return platform; }
int Event::getCapacity() const { return capacity; }
set<string> Event::getRegistrars(){
    return registrars;
}
bool Event::addRegistrar(const string& username){
    if (isFull()) return false;
    registrars.insert(username);
    if(registrars.size() >= capacity)
        full = 1;
    return true;
}
void Event::saveRegistrar(const string& username){
    ifstream inFile("events.txt");
    string line, fileEventName, fileEventDate, fileEventTime;
    vector <string> lines;
    int targetLine, index = 0;
    while(getline(inFile, line)){
        lines.push_back(line);
        stringstream ss(line);
        getline(ss, fileEventName, '|'); //skip type
        getline(ss, fileEventName, '|'); //skip username
        getline(ss, fileEventName, '|'); //get event name
        getline(ss, fileEventDate, '|'); //skip description
        getline(ss, fileEventDate, '|'); //get date
        getline(ss, fileEventTime, '|'); //get time
        if(event_name == fileEventName && date == fileEventDate && time == fileEventTime){
            targetLine = index;
        }
        index++;
    }
    inFile.close();
    for(const string& registrar : registrars){
        if (lines[targetLine].back() != '|') lines[targetLine] += '|';
        lines[targetLine] += registrar + "|";
    }

    ofstream outFile("events.txt", ios::trunc);
    for(const string& l : lines){
        outFile << l << endl;
    }
    outFile.close();
}
bool Event::isFull(){
    return full;
}
bool Event::operator<(const Event& other) const {
    return (date == other.date) ? (time < other.time) : (date < other.date);
}
// Factory Method Implementation: Part of Factory Design Pattern
Event* Event::eventBuilder(const eventType Type) {
    if (Type == Conference_) {
        return Conference::create_event();
    }
    else if (Type == Webinar_) {
        return Webinar::create_event();
    }
    else if (Type == Workshop_) {
        return Workshop::create_event();
    }
    else return nullptr;
}
////////////////////////   Conference   ////////////////////////////
Conference::Conference(){}
Conference::Conference(string n, string desc, string p, string d, string t, int c, int dur)
    : Event(n, desc, p, d, t, c, 0), duration(dur) {}

string Conference::getType() const{ return "Conference";}
int Conference::getDuration() const{ return duration;}

// Static Factory Method Implementation: Part of Factory Design Pattern
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
    while((date[4] != '-') || (date[7] != '-'))  {
        cout << "Wrong format!" << endl << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);
    }
    cout << "Enter time (HH:MM): ";
    getline(cin, time);
    while(time[2] != ':') {
        cout << "Wrong format!" << endl << "Enter time (HH:MM): ";
        getline(cin, time);
    }
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
        << this->getDuration() << endl;
}
// Conference|Username|eneven name|desc|2090-01-01|23:00|Plat|capacity|duration
Event* Conference::loadFromFile(const string& line){

    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, durationStr, type, registrar;
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
    while(getline(ss, registrar, '|')){
        conference->addRegistrar(registrar);
    }
    return conference;
}
/////////////////////////   Webinar   ///////////////////////////
Webinar::Webinar(){}
Webinar::Webinar(string n, string desc, string p, string d, string t, int c, string h)
    : Event(n, desc, p, d, t, c, 0), host(h) {}

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

// Static Factory Method Implementation: Part of Factory Design Pattern
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
    while((date[4] != '-') || (date[7] != '-'))  {
        cout << "Wrong format!" << endl << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);
    }
    cout << "Enter time (HH:MM): ";
    getline(cin, time);
    while(time[2] != ':') {
        cout << "Wrong format!" << endl << "Enter time (HH:MM): ";
        getline(cin, time);
    }
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
        << this->getHost() << endl;
    file.close();
}

Event* Webinar::loadFromFile(const string& line){
    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, host, type, registrar;
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
    while(getline(ss, registrar, '|')){
        webinar->addRegistrar(registrar);
    }
    return webinar;
}
////////////////////////////   Workshop   ////////////////////////
Workshop::Workshop(){}
Workshop::Workshop(string n, string desc, string p, string d, string t, int c, string i)
    : Event(n, desc, p, d, t, c, 0), instructor(i) {}

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

// Static Factory Method Implementation: Part of Factory Design Pattern
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
    while((date[4] != '-') || (date[7] != '-'))  {
        cout << "Wrong format!" << endl << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);
    }
    cout << "Enter time (HH:MM): ";
    getline(cin, time);
    while(time[2] != ':') {
        cout << "Wrong format!" << endl << "Enter time (HH:MM): ";
        getline(cin, time);
    }
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
        << this->getInstructor() << endl;
    file.close();
}

Event* Workshop::loadFromFile(const string& line){
    stringstream ss(line);
    string fileUser, name, desc, date, time, platform, capacityStr, instructor, type, registrar;
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
    while (getline(ss, registrar, '|')) {
        workshop->addRegistrar(registrar);
    }
    return workshop;
}

bool isRegistered(const string& username, Event* event){
    set<string> eventRegistrars = event->getRegistrars();
    return(eventRegistrars.find(username) != eventRegistrars.end());
}

void register_event(const string& logged_user){
    vector <Event*> events;
    ifstream file("events.txt");
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string type, eventCreator;
        getline(ss, type, '|');
        getline(ss, eventCreator, '|');

        if(logged_user == eventCreator) continue;

        if(type == "Conference"){
            events.push_back(Conference::loadFromFile(line));
        }
        else if(type == "Webinar"){
            events.push_back(Webinar::loadFromFile(line));
        }
        else if(type == "Workshop"){
            events.push_back(Workshop::loadFromFile(line));
        }
    }
    if (events.empty()){
        cout << "\nNo events available for registration." << endl;
        return;
    }

    cout << "\nAvailable events:" << endl;
    for(int i=0 ; i<events.size() ; i++){
        cout << "----------------------------" << endl;
        cout << i+1 << ")\n";
        events[i]->displayDetails();
        cout << endl;
    }
    cout << "Choose an event to register (1-" << events.size() << ") (enter 0 to go back): ";

    int choice;
    while(true){
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, choose (1-" << events.size() << "): ";
            continue;
        }
        else if(choice == 0){
            cout << "Exited registration" << endl;
            return;
        }
        else if(choice < 1 || choice > events.size()){
            cout << "Invalid choice, choose (1-" << events.size() << "): ";
        }
        else if(isRegistered(logged_user, events[choice - 1])){
            cout << "You've already registered for this event!" << endl;
            cout << "Choose another event: " << endl;
        }
        else break;
    }

    Event* selectedEvent = events[choice - 1];
    if (!selectedEvent->addRegistrar(logged_user)) {
        cout << "Sorry, this event is already full!" << endl;
    } else {
        selectedEvent->saveRegistrar(logged_user);
        cout << "\nYou've registered successfully!" << endl;
    }
}

set<Event*> getRegesteredEvents(const string& username) {
    set<Event*> RegisteredEvents;
    ifstream file("events.txt");
    string line, type, fileUser;
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, type, '|'); // Read event type
        getline(iss, fileUser, '|'); // Read username (creator)
        Event* event = nullptr;
        if (type == "Conference") {
            event = Conference::loadFromFile(line);
        } else if (type == "Webinar") {
            event = Webinar::loadFromFile(line);
        } else if (type == "Workshop") {
            event = Workshop::loadFromFile(line);
        }
        if (event && isRegistered(username, event)) {
            RegisteredEvents.insert(event);
        } else if (event) {
            delete event;
        }
    }
    file.close();
    return RegisteredEvents;
}

void viewUserEvents(const string& username){
    set<Event*> ScheduledEvents = loadEventsForUser(username);
    set<Event*> RegesteredEvents = getRegesteredEvents(username);


    cout << "\nScheduled ";
    if(ScheduledEvents.empty())
        cout << "Meetings:\n-----------------------------\nYou have no scheduled meetings." << endl;
    else
        printMultiset(ScheduledEvents);

    cout << "\nRegistered ";
    if(RegesteredEvents.empty())
        cout << "Meetings:\n-----------------------------\nYou have no registered meetings." << endl;
    else
        printMultiset(RegesteredEvents);
}


////////////////////////   Feedback   ////////////////////////////
Feedback::Feedback()
    : submissionTimestamp_(getCurrentTimestamp()),
      generalRating_(-1)
{}

Feedback::Feedback(const string& reviewerUsername,
                   const string& eventName,
                   const string& eventType,
                   const string& eventDate)
    : reviewerUsername_(reviewerUsername),
      eventName_(eventName),
      eventType_(eventType),
      submissionTimestamp_(getCurrentTimestamp()),
      generalRating_(-1),
      eventDate_(eventDate)
{}

// --- General Event Rating ---
void Feedback::setGeneralRating(int rating) {
    if (rating >= 1 && rating <= 5)
        generalRating_ = rating;
    else
        generalRating_ = -1;
}

int Feedback::getGeneralRating() const {return generalRating_;}

// --- Detailed Ratings for Specific Aspects ---

void Feedback::setDetailedRating(const string& aspect, int rating) {
    if (rating >= 1 && rating <= 5) {
        detailedRatings_[aspect] = rating;
    }
}

int Feedback::getDetailedRating(const string& aspect) const {
    auto it = detailedRatings_.find(aspect);
    return (it != detailedRatings_.end()) ? it->second : 0;
}

const map<string, int>& Feedback::getAllDetailedRatings() const {return detailedRatings_;}

// ---Written Feedback (Qualitative Feedback) ---

void Feedback::setImprovementSuggestion(const string& suggestion) {improvementSuggestion_ = suggestion;}

string Feedback::getImprovementSuggestion() const {return improvementSuggestion_;}

// ------------------------------------------------- Display Functionality --------------------------------------------------------------------
void Feedback::display(bool showFutureNotice) const {
    if (showFutureNotice && isSubmittedBeforeEvent()) {
        cout << "Notice: The event has not been launched yet. Feedback submission is not allowed." << endl;
        cout << "-------------------------------------------------" << endl;
    }
    cout << "--- Feedback for: " << eventName_ << " (" << eventType_ << ") ---" << endl;
    cout << "Submitted by: " << reviewerUsername_ << " on " << submissionTimestamp_ << endl;
    if (generalRating_ != -1) {cout << "General Event Rating: " << generalRating_ << "/5" << endl;}
    cout << "\nDetailed Ratings (1-5):" << endl;
    if (detailedRatings_.empty()) {
        cout << "  (No detailed ratings given)" << endl;
    } else {
        map<string, int> sortedRatings = detailedRatings_;
        for (const auto& pair : sortedRatings) {
            cout << "  - " << pair.first << ": " << pair.second << "/5" << endl;
        }
    }
    if (!improvementSuggestion_.empty()) {
        cout << "  Suggestion for Improvement: " << improvementSuggestion_ << endl;
    }
    cout << "-----------------------------------------" << endl;
}

bool Feedback::isSubmittedBeforeEvent() const {
    // If no event date is set, allow feedback
    if (eventDate_.empty()) return false;

    // Get the current system time
    time_t now = time(nullptr);

    // Convert the event date string to a time object
    time_t eventTime = convertTimestampToTime(eventDate_);

    // If conversion fails, allow feedback
    if (eventTime == -1) return false;

    // If the current time is earlier than the event time, block feedback
    return now < eventTime;
}


time_t Feedback::convertTimestampToTime(const string& timestamp) {
    std::tm tm = {}; // Initialize an empty tm structure
    std::istringstream ss(timestamp); // Create a stream from the timestamp string
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); // Read the time in specific format
    return mktime(&tm); // Convert the tm structure into a time_t value
}

// ----------------------------------------------------------- Interaction Method -------------------------------------------------------------
bool Feedback::collectFeedbackInteractive(const vector<string>& potentialAspects) {
    submissionTimestamp_ = getCurrentTimestamp();
    if (isSubmittedBeforeEvent()) {
        return false;
    }
    cout << "\n--- Providing Feedback for: " << eventName_ << " ---" << endl;
    cout << "Help us improve! Please share your thoughts." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // 1. Ask for General Event Rating
    int genRating = -1;
    cout << "On a scale of 0-5, please rate the event overall. ";
    while (!(cin >> genRating) || genRating < 1 || genRating > 5) {
        cout << "Invalid input. Please enter a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    setGeneralRating(genRating);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // 2. Ask for Ratings on Different Aspects (optional)
    if (!potentialAspects.empty()) {
        cout << "\nPlease rate the following aspects (1-5, where 1=Poor, 5=Excellent, 0=Skip):" << endl;
        for (const auto& aspect : potentialAspects) {
            int rating = -1;
            cout << "  - " << aspect << ": ";
            while (!(cin >> rating) || rating < 0 || rating > 5) {
                cout << "Invalid input. Please enter a number between 0 and 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (rating > 0) { setDetailedRating(aspect, rating); }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // 3. Ask for Suggestions
    cout << "Do you have any specific suggestions for how we could improve next time? (Press Enter to skip)\n> ";
    getline(cin, improvementSuggestion_);
    cout << "\nThank you for your valuable feedback!" << endl;
    return true;
}

void Feedback::saveToFile() const {
    string filename = reviewerUsername_ + "_feedback.txt";
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cout << "Error saving feedback!" << endl;
        return;
    }
    outfile << "--- Feedback Start ---" << endl;
    outfile << "User: " << reviewerUsername_ << endl;
    outfile << "Event: " << eventName_ << endl;
    outfile << "Type: " << eventType_ << endl;
    outfile << "Timestamp: " << submissionTimestamp_ << endl;
    outfile << "Suggestion: " << improvementSuggestion_ << endl;
    outfile << "Ratings: ";
    bool first = true;
    for (const auto& pair : detailedRatings_) {
        if (!first) outfile << " ";
        outfile << pair.first << "=" << pair.second << ";";
        first = false;
    }
    outfile << endl;
    outfile << "--- Feedback End ---" << endl;
    outfile.close();
}

string Feedback::getCurrentTimestamp() {
    auto now = chrono::system_clock::now(); // Get current time
    auto now_c = chrono::system_clock::to_time_t(now); // Convert to time_t
    stringstream ss;

    tm timeinfo;
    localtime_s(&timeinfo, &now_c); // Safely convert to tm structure

    ss << put_time(&timeinfo, "%Y-%m-%d %H:%M:%S"); // Format time nicely

    return ss.str();
}

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

        ifstream usersFile("loginDataBase.txt");
        if (!usersFile.is_open()) {
            cout << "Error: Unable to open database file!" << endl;
            exit(0);
            return ""; // Use empty string instead of nullptr for string return type
        }

        string fileUsername, filePassword, line;
        bool loginSuccess = false;

        while (getline(usersFile, line)) {
            stringstream ss(line);
            ss >> fileUsername >> filePassword;
            if (fileUsername == username && filePassword == password) {
                loginSuccess = true;
                break;
            }
        }

        usersFile.close();

        if (loginSuccess) {
            cout << "\nWelcome, " << username << "!" << endl;
            return username;
        } else {
            cout << "Invalid username or password! Please try again." << endl;
        }
    }
}

void signup(){
    string username, password, email, affiliation;

    cout << "Enter username: ";
    cin >> username;

    if (usernames.count(username)) {
        cout << "Username is taken!" << endl;
        signup();
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter email: ";
    cin >> email;

    cin.ignore();
    cout << "Enter affiliation (optional - press enter to skip): ";
    getline(cin, affiliation);

    ofstream users("loginDataBase.txt", ios::app);
    if (!users.is_open()) {
        cout << "Error: Unable to open database file!" << endl;
        return;
    }

    users << username << " " << password << " " << email << " " << affiliation << "\n";
    users.close();
    usernames.insert(username);

    cout << "Signup successful!" << endl;
}

void start_menu(){
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

void main_menu(string const& logged_user){
    int choice;
    while (true) {
        cout << "\nPlease choose one of these options:" << endl;
        cout << "1) Schedule Meeting" << endl;
        cout << "2) Register for a Meeting" << endl;
        cout << "3) Search for a Meeting" << endl;
        cout << "4) Postpone Meeting" << endl;
        cout << "5) Cancel Meeting" << endl;
        cout << "6) Open Calendar for user" << endl;
        cout << "7) Give feedback" << endl;
        cout << "8) Review previous feedbacks"<< endl;
        cout << "9) Sign out"<<endl;
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
            events_menu(logged_user);
            break; // Continue the loop to let the user choose again
        case 2:
            register_event(logged_user);
            break;
        case 3:
            search_();
            break;
        case 4:
            meeting_postponement(logged_user);
            break;
        case 5:
            meeting_cancellation(logged_user);
            break;
        case 6:
            viewUserEvents(logged_user);
            break;
        case 7:
            feedback_menu(logged_user);
            break;
        case 8:
            review_feedbacks(logged_user);
            break;
        case 9:
            start_menu();  // Sign out and return to start menu
            return; // Exit the loop and the main_menu function
        default:
            cout << "Invalid choice, please choose a number." << endl;
        }
    }
}

void events_menu(string const& logged_user){
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
        Event* event = nullptr;
        switch (choice) {
        case 1:
            // Usage of Factory Design Pattern
            event = Event::eventBuilder(Conference_);
            break;
        case 2:
            // Usage of Factory Design Pattern
            event = Event::eventBuilder(Webinar_);
            break;
        case 3:
            // Usage of Factory Design Pattern
            event = Event::eventBuilder(Workshop_);
            break;
        case 4:
            main_menu(logged_user);
            return;
        default:
            cout << "Invalid choice, please choose 1, 2, 3, or 4." << endl;
            continue;
        }
        if (event) {
            schedule_event(logged_user, event);
        }
    }
}

void schedule_event(string const& logged_user, Event* event) {
    allEvents.insert(event);
    event->saveToFile(logged_user);
}

void loadLoginData(){
    string username, password, email, affiliation, line;
    ifstream usersFile("loginDataBase.txt");

    while (getline(usersFile, line)) {
        stringstream ss(line);
        ss >> username >> password >> email >> ws; //ws to discard the white space
        getline(ss, affiliation);
        Users.insert(User(username, password, email, affiliation));
        usernames.insert(username);
    }
    usersFile.close();
}

void loadEventsData(){
    string type, line;

    ifstream eventsFile("events.txt");

    while(getline(eventsFile, line)) {
        stringstream ss(line);
        getline(ss, type, '|');
        if(type == "Conference"){
            allEvents.insert(Conference::loadFromFile(line));
        }
        else if(type == "Webinar"){
            allEvents.insert(Webinar::loadFromFile(line));
        }
        else if(type == "Workshop"){
            allEvents.insert(Workshop::loadFromFile(line));
        }
    }
    eventsFile.close();
}

void setup() {

    loadLoginData();
    loadEventsData();
    cout << "=========================" << endl;
    cout << "=========WELCOME=========" << endl;
    cout << "=========================" << endl;

    start_menu();
}

void meeting_postponement(const string& username) {
    string eventName, line;
    cout << "What is the name of the event you want to postpone (or type 'exit' to cancel): ";
    getline(cin >> ws, eventName);

    if (eventName == "exit") {
        cout << "Postponement canceled.\n";
        return;  // Immediately exit the function
    }

    ifstream file("events.txt");
    vector<string> updatedLines;
    string type, fileUser, name, desc, date, time, platform, capacityStr, addedAttribute, registrars;
    int flag = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, type, '|');
        getline(ss, fileUser, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, platform, '|');
        getline(ss, capacityStr, '|');
        getline(ss, addedAttribute, '|');
        getline(ss, registrars);

        if (fileUser == username && name == eventName) {
            cin.ignore();
            cout << "New date (YYYY-MM-DD): ";
            getline(cin, date);
            while((date[4] != '-') || (date[7] != '-'))  {
                cout << "Wrong format!" << endl << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
            }
            cout << "New time (HH:MM): ";
            getline(cin, time);
            while(time[2] != ':') {
            cout << "Wrong format!" << endl << "Enter time (HH:MM): ";
            getline(cin, time);
            }
            flag = 1;
        }

        // Add the (possibly modified) line back
        string updatedLine;
        updatedLine = type + "|" + fileUser + "|" + name + "|" + desc + "|" +
                      date + "|" + time + "|" + platform + "|" +
                      capacityStr + "|" + addedAttribute + "|" + registrars;
        updatedLines.push_back(updatedLine);
    }
    file.close();

    // Write updated lines back into the same file
    ofstream outFile("events.txt", ios::trunc); // overwrite file
    for (const string& l : updatedLines) {
        outFile << l << endl;
    }
    outFile.close();

    if (flag == 0) {
        cout << "Event not found.\n";
        meeting_postponement(username);
    } else {
        cout << "Event postponed successfully!\n";
    }
}

void meeting_cancellation(const string& username) {
    string eventName, line;
    while (true) {
        cout << "What is the name of the event you want to cancel (or type 'exit' to go back): ";
        getline(cin >> ws, eventName); // Use ws to skip leading whitespace
        if (eventName == "exit") {
            cout << "Exited cancellation.\n";
            return;
        }

        ifstream file("events.txt");
        if (!file.is_open()) { cout << "Error opening events file!\n"; return; }
        vector<string> updatedLines;
        string type, fileUser, name, desc, date, time, platform, capacityStr, addedAttribute, registrars;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, type, '|');
            getline(ss, fileUser, '|');
            getline(ss, name, '|');
            getline(ss, desc, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, platform, '|');
            getline(ss, capacityStr, '|');
            getline(ss, addedAttribute, '|');
            getline(ss, registrars);
            if (fileUser == username && name == eventName) {
                found = true;
                continue;
            }
            updatedLines.push_back(line);
        }
        file.close();

        if (found) {
            ofstream outFile("events.txt", ios::trunc);
            for (const string& l : updatedLines) outFile << l << "\n";
            outFile.close();
            cout << "Event canceled successfully!\n";
            return;
        } else {
            cout << "Event not found or you don't have permission to cancel it. Try again.\n";
        }
    }
}

void feedback_menu(const std::string& logged_user) {
    // Load all events associated with this user
    set<Event*> userEvents = loadEventsForUser(logged_user);

    if (userEvents.empty()) {
        // If no events found, inform the user and exit
        cout << "No events found to give feedback on!" << endl;
        return;
    }

    // List all available events for the user to choose from
    cout << endl;
    cout << "Select an event to give feedback on:" << endl;
    int index = 1;
    vector<Event*> eventList;
    for (Event* e : userEvents) {
        cout << index++ << ") " << e->getName() << " on " << e->getDate() << " at " << e->getTime() << endl;
        eventList.push_back(e);
    }

    // Ask user to select an event by number
    int choice;
    cout << "Enter event number: ";
    cin >> choice;
    cout << endl;

    // Check if user selection is valid
    if (choice < 1 || choice > eventList.size()) {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Get the selected event
    Event* selectedEvent = eventList[choice - 1];

    // Extract event details
    string eventTitle = selectedEvent->getName();
    string eventDate = selectedEvent->getDate(); // Get the event date
    string eventType = selectedEvent->getType();

    // Define a list of feedback aspects
    vector<string> aspects = { "Content", "Delivery", "Relevance", "Duration" };

    // Create a Feedback object using the logged user and selected event
    Feedback fb(logged_user, eventTitle, eventType, eventDate);
    if (fb.collectFeedbackInteractive(aspects)) {
        fb.display(true); // show notice if event is in the future
        fb.saveToFile();
    } else {
        cout << "Feedback not collected because the event has not been launched yet." << endl;
    }
    for (Event* e : userEvents) {
        delete e;
    }
}

void review_feedbacks(const std::string& username) { // This function lets a user review all feedbacks they have submitted
    string filename = username + "_feedback.txt";
    ifstream infile(filename);
    if (!infile.is_open()) {
        // If feedback file not found, inform the user and exit
        cout << "\nNo previous feedbacks found for user: " << username << endl;
        return;
    }

    // Prepare to store all feedbacks
    vector<Feedback> feedbacks;
    string line;
    // Temporary variables to hold feedback data while reading
    string eventName, eventType, eventDate, reviewer, timestamp, suggestion;
    int generalRating = -1;
    map<string, int> detailedRatings;

    // Read the file line by line
    while (getline(infile, line)) {
        if (line == "--- Feedback Start ---") {
            // Start of a new feedback block: reset all temp variables
            eventName = eventType = eventDate = reviewer = timestamp = suggestion = "";
            generalRating = -1;
            detailedRatings.clear();
        } else if (line == "--- Feedback End ---") {
            // End of a feedback block: if we have an event name, create a Feedback object
            if (!eventName.empty()) {
                Feedback fb(reviewer, eventName, eventType, eventDate);
                fb.setGeneralRating(generalRating);
                for (const auto& p : detailedRatings) fb.setDetailedRating(p.first, p.second);
                fb.setImprovementSuggestion(suggestion);
                feedbacks.push_back(fb);
            }
        } else if (!line.empty()) {
            // Parse each line in the feedback block
            if (line.find("User: ") == 0) {
                reviewer = line.substr(6);
            } else if (line.find("Event: ") == 0) {
                eventName = line.substr(7);
            } else if (line.find("Type: ") == 0) {
                eventType = line.substr(6);
            } else if (line.find("Timestamp: ") == 0) {
                timestamp = line.substr(11);
            } else if (line.find("GeneralRating: ") == 0) {
                generalRating = stoi(line.substr(14));
            } else if (line.find("Suggestion: ") == 0) {
                suggestion = line.substr(12);
            } else if (line.find("Ratings: ") == 0) {
                // Parse aspect ratings (e.g., Content=4; Delivery=5; ...)
                string ratings = line.substr(9);
                stringstream ss(ratings);
                string pair;
                while (getline(ss, pair, ';')) {
                    size_t eq = pair.find('=');
                    if (eq != string::npos) {
                        string aspect = pair.substr(0, eq);
                        int val = stoi(pair.substr(eq + 1));
                        if (!aspect.empty()) detailedRatings[aspect] = val;
                    }
                }
            }
        }
    }
    infile.close();

    // If no feedbacks were found, inform the user
    if (feedbacks.empty()) {
        cout << "No feedback entries found." << endl;
        return;
    }

    // Display all feedbacks using the Feedback::display method
    cout << "\n--- Your Feedback Entries ---" << endl;
    int idx = 1;
    for (auto& fb : feedbacks) {
        cout << "\nFeedback #" << idx++ << ":\n";
        fb.display(false); // Do not show the 'event not launched' notice
    }
}

void search_(){
    int search_choice;
    cout << "\nPlease choose one of these options:" << endl;
    cout << "1) Search by Event name" << endl;
    cout << "2) Search by Event date" << endl;
    cout << "3) Search by Event type" << endl;
    cout << "Enter a number: ";
    cin >> search_choice;
    switch(search_choice){
    case 1:
        search_by_name();
        break;
    case 2:
        search_by_date();
        break;
    case 3:
        search_by_type();
        break;
    default:
        cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        break;
    }
}

void search_by_type(){
    set<Event*> matchedEvents;

    cout << "\nPlease choose the type of the event:" << endl;
    cout << "1) Conference" << endl;
    cout << "2) Webinar" << endl;
    cout << "3) Workshop" << endl;
    cout << "Enter a number: ";
    int type_number;
    cin >> type_number;

    ifstream events("events.txt");
    string line, type;

    while(getline(events, line)){
        stringstream ss(line);
        getline(ss, type, '|');
        if(type_number == 1){
            if (type == "Conference") {
                matchedEvents.insert(Conference::loadFromFile(line));
            }
        }else if(type_number == 2){
            if (type == "Webinar") {
                matchedEvents.insert(Webinar::loadFromFile(line));
            }
        }else if(type_number == 3){
            if (type == "Workshop") {
                matchedEvents.insert(Workshop::loadFromFile(line));
            }
        }
    }

    if(matchedEvents.empty()){
        cout << "No results found!";
    }else{
        printMultiset(matchedEvents);
    }

}

void search_by_date(){
    set<Event*> matchedEvents;

    cout << "Enter event date (YYYY-MM-DD): ";
    string event_date;
    cin >> event_date;

    ifstream events("events.txt");
    string line;
    string type, fileUser, name, desc, date;
    while(getline(events, line)){
        stringstream ss(line);
        getline(ss, type, '|');
        getline(ss, fileUser, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');

        getline(ss, date, '|');
        if(event_date == date){
            if (type == "Conference") {
                matchedEvents.insert(Conference::loadFromFile(line));
            } else if (type == "Webinar") {
                matchedEvents.insert(Webinar::loadFromFile(line));
            } else if (type == "Workshop") {
                matchedEvents.insert(Workshop::loadFromFile(line));
            }
        }
    }
    if(matchedEvents.empty()){
        cout << "No results found!";
    }else{
        printMultiset(matchedEvents);
    }
}

void search_by_name(){
    set<Event*> matchedEvents;

    cout << "Enter event name: ";
    string event_name;
    cin >> event_name;

    ifstream events("events.txt");
    string line;
    string type, fileUser, name;
    while(getline(events, line)){
        stringstream ss(line);
        getline(ss, type, '|');
        getline(ss, fileUser, '|');

        getline(ss, name, '|');
        if(event_name == name){
            if (type == "Conference") {
                matchedEvents.insert(Conference::loadFromFile(line));
            } else if (type == "Webinar") {
                matchedEvents.insert(Webinar::loadFromFile(line));
            } else if (type == "Workshop") {
                matchedEvents.insert(Workshop::loadFromFile(line));
            }
        }
    }
    if(matchedEvents.empty()){
        cout << "No results found!";
    }else{
        printMultiset(matchedEvents);
    }
}

int main() {
    setup();
    return 0;
}
