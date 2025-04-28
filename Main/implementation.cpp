#include "events.h"

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
Feedback::Feedback()
    : submissionTimestamp_(getCurrentTimestamp()),
      anonymous_(false),
      likelihoodToRecommend_(-1),
      experienceLevel_(AttendeeExperienceLevel::NOT_SET),
      eventDate_("")
{}

Feedback::Feedback(const string& reviewerUsername,
                   const string& eventName,
                   const string& eventType,
                   const string& eventDate)
    : reviewerUsername_(reviewerUsername),
      eventName_(eventName),
      eventType_(eventType),
      submissionTimestamp_(getCurrentTimestamp()),
      anonymous_(false),
      likelihoodToRecommend_(-1),
      experienceLevel_(AttendeeExperienceLevel::NOT_SET),
      eventDate_(eventDate)
{}

// --- Core Feedback Information ---

void Feedback::setOverallFeeling(const string& feeling) {overallFeeling_ = feeling;}

string Feedback::getOverallFeeling() const {return overallFeeling_;}

void Feedback::setLikelihoodToRecommend(int score) {
    if (score >= 0 && score <= 10)
        likelihoodToRecommend_ = score;
    else
        likelihoodToRecommend_ = -1;
}

int Feedback::getLikelihoodToRecommend() const {return likelihoodToRecommend_;}

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

void Feedback::setHighlight(const string& highlight) {highlight_ = highlight;}

string Feedback::getHighlight() const {return highlight_;}

void Feedback::setImprovementSuggestion(const string& suggestion) {improvementSuggestion_ = suggestion;}

string Feedback::getImprovementSuggestion() const {return improvementSuggestion_;}

void Feedback::addTag(const string& tag) {tags_.push_back(tag);}

const vector<string>& Feedback::getTags() const {return tags_;}

// --- Reviewer Information ---

void Feedback::setExperienceLevel(AttendeeExperienceLevel level) {experienceLevel_ = level;}

Feedback::AttendeeExperienceLevel Feedback::getExperienceLevel() const {return experienceLevel_;}

void Feedback::setAttendedAnonymously(bool anonymous) {anonymous_ = anonymous;}

bool Feedback::didAttendAnonymously() const {return anonymous_;}

// --- General Event Info ---

string Feedback::getReviewerUsername() const {return reviewerUsername_;}

string Feedback::getEventName() const {
return eventName_;}

string Feedback::getEventType() const {return eventType_;}

string Feedback::getSubmissionTimestamp() const {return submissionTimestamp_;}

void Feedback::setEventDate(const string& eventDate) {eventDate_ = eventDate;}

string Feedback::getEventDate() const {return eventDate_;}

// ------------------------------------------------- Display Functionality --------------------------------------------------------------------
void Feedback::display() const {
    // Check if feedback is submitted before the event date
    if (isSubmittedBeforeEvent()) {
        cout << "Notice: The event has not been launched yet. Feedback submission is not allowed." << endl;
        cout << "-------------------------------------------------" << endl;
    }

    // Show the basic event and reviewer information
    cout << "--- Feedback for: " << eventName_ << " (" << eventType_ << ") ---" << endl;
    cout << "Submitted by: " << reviewerUsername_ << " on " << submissionTimestamp_ << endl;


    if (!overallFeeling_.empty()) {cout << "Overall Feeling: " << overallFeeling_ << endl;}


    if (likelihoodToRecommend_ != -1) {cout << "Likelihood to Recommend: " << likelihoodToRecommend_ << "/10" << endl;}


    if (experienceLevel_ != AttendeeExperienceLevel::NOT_SET) {cout << "Reviewer Experience Level: " << getExperienceLevelString() << endl;}

    // Show detailed aspect ratings
    cout << "\nDetailed Ratings (1-5):" << endl;
    if (detailedRatings_.empty()) {
        cout << "  (No detailed ratings given)" << endl;
    } else {
        // Go through each aspect and print its rating
        map<string, int> sortedRatings = detailedRatings_; // Copy to allow sorting if needed
        for (const auto& pair : sortedRatings) {
            cout << "  - " << pair.first << ": " << pair.second << "/5" << endl;
        }
    }


    cout << "\nQualitative Feedback:" << endl;
    if (!highlight_.empty()) {
        cout << "  Highlight: " << highlight_ << endl;
    }
    if (!improvementSuggestion_.empty()) {
        cout << "  Suggestion for Improvement: " << improvementSuggestion_ << endl;
    }

    // Show any tags (keywords) added by the reviewer
    if (!tags_.empty()) {
        cout << "  Tags: ";
        for (size_t i = 0; i < tags_.size(); ++i) {
            cout << tags_[i] << (i == tags_.size() - 1 ? "" : ", ");
        }
        cout << endl;
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
void Feedback::collectFeedbackInteractive(const vector<string>& potentialAspects) {
    submissionTimestamp_ = getCurrentTimestamp(); // Set the time when feedback is collected

    // If feedback is attempted before the event date, exit immediately
    if (isSubmittedBeforeEvent()) {return;}

    cout << "\n--- Providing Feedback for: " << eventName_ << " ---" << endl;
    cout << "Help us improve! Please share your thoughts." << endl;

    // Clear leftover input to avoid issues with getline and cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 1. Ask for Overall Feeling
    cout << "In one word or short phrase, how did the event make you feel? (e.g., Inspired, Informed, Bored): ";
    getline(cin, overallFeeling_); // Allow multi-word input

    // 2. Ask for Likelihood to Recommend
    int nps = -1;
    cout << "On a scale of 0-10, how likely are you to recommend this event to a friend or colleague? ";
    while (!(cin >> nps) || nps < 0 || nps > 10) {
        cout << "Invalid input. Please enter a number between 0 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    setLikelihoodToRecommend(nps);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline character

    // 3. Ask for Ratings on Different Aspects (optional)
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
            if (rating > 0) { // Only save ratings that are actually given
                setDetailedRating(aspect, rating);
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline character
    }

    // 4. Ask for Highlight and Suggestions
    cout << "What was the absolute highlight or best part for you? (Press Enter to skip)\n> ";
    getline(cin, highlight_);

    cout << "Do you have any specific suggestions for how we could improve next time? (Press Enter to skip)\n> ";
    getline(cin, improvementSuggestion_);

    // 5. Ask for Tags (Comma-separated input)
    string tagsInput;
    cout << "Add some tags to describe your experience (e.g., fun, informative, too_long), separated by commas:\n> ";
    getline(cin, tagsInput);

    stringstream ss(tagsInput);
    string tag;
    while (getline(ss, tag, ',')) {
        // Trim spaces from each tag
        size_t first = tag.find_first_not_of(" \t\n\r\f\v");
        if (string::npos == first) continue; // Skip empty tags
        size_t last = tag.find_last_not_of(" \t\n\r\f\v");
        tag = tag.substr(first, (last - first + 1));

        if (!tag.empty()) {
            addTag(tag);
        }
    }

    // 6. Ask for Experience Level
    int expChoice = 0;
    cout << "What is your experience level related to this event's topic? (1: Beginner, 2: Intermediate, 3: Advanced, 4: Expert, 0: Skip): ";
    while (!(cin >> expChoice) || expChoice < 0 || expChoice > 4) {
        cout << "Invalid input. Please enter a number between 0 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //User's choice to internal experience level
    if (expChoice > 0) {
        switch (expChoice) {
            case 1: setExperienceLevel(AttendeeExperienceLevel::BEGINNER); break;
            case 2: setExperienceLevel(AttendeeExperienceLevel::INTERMEDIATE); break;
            case 3: setExperienceLevel(AttendeeExperienceLevel::ADVANCED); break;
            case 4: setExperienceLevel(AttendeeExperienceLevel::EXPERT); break;
            default: setExperienceLevel(AttendeeExperienceLevel::NOT_SET); break;
        }
    } else {
        setExperienceLevel(AttendeeExperienceLevel::NOT_SET);
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline character

    // 7. Ask if Feedback Should be Anonymous
    char anonChoice = 'n'; // Default is not anonymous
    cout << "Would you like to submit this feedback anonymously? (y/n): ";
    string anonInput;
    getline(cin, anonInput);

    if (!anonInput.empty()) {
        anonChoice = tolower(anonInput[0]);
    }
    anonymous_ = (anonChoice == 'y');

    cout << "\nThank you for your valuable feedback!" << endl;
}

void Feedback::saveToFile() const {
    string filename = reviewerUsername_ + "_feedback.txt"; // Create filename using reviewer's username
    ofstream outfile(filename, ios::app); // Open file in append mode

    if (!outfile.is_open()) {
        cout << "Error saving feedback!" << endl;
        return;
    }

    // Write feedback details to the file
    outfile << "--- Feedback Start ---" << endl;
    outfile << "User: " << reviewerUsername_ << endl;
    outfile << "Event: " << eventName_ << endl;
    outfile << "Type: " << eventType_ << endl;
    outfile << "Timestamp: " << submissionTimestamp_ << endl;
    outfile << "Feeling: " << overallFeeling_ << endl;
    outfile << "Recommend: " << likelihoodToRecommend_ << endl;
    outfile << "Experience: " << getExperienceLevelString() << endl;
    outfile << "Highlight: " << highlight_ << endl;
    outfile << "Suggestion: " << improvementSuggestion_ << endl;

    // Save all detailed ratings
    outfile << "Ratings: ";
    for (const auto& pair : detailedRatings_) {
        outfile << pair.first << "=" << pair.second << ";";
    }
    outfile << endl;

    // Save all tags
    outfile << "Tags: ";
    for (size_t i = 0; i < tags_.size(); ++i) {
        outfile << tags_[i] << (i == tags_.size() - 1 ? "" : ",");
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

string Feedback::getExperienceLevelString() const {
    switch (experienceLevel_) {
        case AttendeeExperienceLevel::BEGINNER: return "Beginner";
        case AttendeeExperienceLevel::INTERMEDIATE: return "Intermediate";
        case AttendeeExperienceLevel::ADVANCED: return "Advanced";
        case AttendeeExperienceLevel::EXPERT: return "Expert";
        case AttendeeExperienceLevel::NOT_SET: return "Not Specified";
        default: return "Unknown";
    }
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
        cout << "2) Search for a meeting" << endl;
        cout << "3) Postpone Meeting" << endl;
        cout << "4) Cancel Meeting" << endl;
        cout << "5) Open Calendar for user" << endl;
        cout << "6) Give feedback" << endl;
        cout << "7) Review previous feedbacks"<< endl;
        cout << "8) Sign out"<<endl;
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
            search_();
            break;
        case 3:
            meeting_postponement (logged_user);
            break;
        case 4:
            meeting_cancellation (logged_user);
            break;
        case 5:
            printMultiset(loadEventsForUser(logged_user));
            break; // Continue the loop to let the user choose again
        case 6:
            feedback_menu(logged_user);
            break;
        case 7:
            review_feedbacks(logged_user);
            break;
         case 8:
            start_menu();  // Sign out and return to start menu
            return; // Exit the loop and the main_menu function
        default:
            cout << "Invalid choice, please choose a number." << endl;
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
    string fileUser, name, desc, date, time, platform, capacityStr, host, type;
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
        getline(ss, host, '|'); // may not be needed depending on event

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
        string updatedLine = type + "|" + fileUser + "|" + name + "|" + desc + "|" +
                             date + "|" + time + "|" + platform + "|" +
                             capacityStr + "|" + host;
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
        string fileUser, name, desc, date, time, platform, capacityStr, host, type;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, type, '|'); getline(ss, fileUser, '|'); getline(ss, name, '|');
            getline(ss, desc, '|'); getline(ss, date, '|'); getline(ss, time, '|');
            getline(ss, platform, '|'); getline(ss, capacityStr, '|'); getline(ss, host, '|');
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

    // Collect feedback from the user interactively
    fb.collectFeedbackInteractive(aspects);

    // Display the feedback summary
    fb.display();

    // Save the feedback to a file
    fb.saveToFile();

    // Clean up allocated memory for loaded events
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

    // Store feedback grouped by event name
    map<string, vector<vector<string>>> feedbacksByEvent;
    string line;
    vector<string> currentFeedback;
    string currentEvent;

    // Read the feedback file line by line
    while (getline(infile, line)) {
        if (line == "--- Feedback Start ---") {
            // Start of a new feedback block
            currentFeedback.clear();
        } else if (line == "--- Feedback End ---") {
            // End of current feedback block
            for (const string& entry : currentFeedback) {
                if (entry.find("Event: ") == 0) {
                    currentEvent = entry.substr(7); // Extract event name
                    break;
                }
            }
            if (!currentEvent.empty()) {
                feedbacksByEvent[currentEvent].push_back(currentFeedback);
            }
            currentEvent.clear();
        } else if (!line.empty()) {
            // Collect feedback lines inside the block
            currentFeedback.push_back(line);
        }
    }
    infile.close();

    if (feedbacksByEvent.empty()) {
        cout << "No feedback entries found." << endl;
        return;
    }

    // List all events the user has submitted feedback for
    cout << "\n--- Events you've given feedback for ---" << endl;
    int idx = 1;
    vector<string> eventNames;
    for (const auto& pair : feedbacksByEvent) {
        cout << idx++ << ") " << pair.first << endl;
        eventNames.push_back(pair.first);
    }

    // Ask user to select which event's feedbacks they want to review
    int choice;
    cout << "Enter the number of the event you want to review: ";
    cin >> choice;
    if (choice < 1 || choice > eventNames.size()) {
        cout << "Invalid choice!" << endl;
        return;
    }

    string selectedEvent = eventNames[choice - 1];
    cout << "\n--- Feedback for Event: " << selectedEvent << " ---" << endl;

    // Display all feedback entries for the selected event
    int feedbackIdx = 1;
    for (const auto& feedbackBlock : feedbacksByEvent[selectedEvent]) {
        cout << "\nFeedback #" << feedbackIdx++ << ":\n";
        for (const string& feedbackLine : feedbackBlock) {
            cout << feedbackLine << endl;
        }
        cout << "----------------------------------------" << endl;
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
