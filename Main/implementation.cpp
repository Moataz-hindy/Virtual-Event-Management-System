#include "events.h"

set<User*> allUsers;
set<Event*> allEvents;




//////////////////////////   Menu   //////////////////////////

void Menu::setup() {

    loadUsersData();
    loadEventsData();
    cout << "=========================" << endl;
    cout << "=========WELCOME=========" << endl;
    cout << "=========================" << endl;

    start_menu();
}


void Menu::start_menu(){
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
                break;
            case 2:
                signup();
                break;
            case 3:
                saveEventsToFile();
                saveUsersToFile();
                exit(0);
            default:
                cout << "Invalid choice, please choose 1, 2 or 3." << endl;
        }
    }
}


void Menu::main_menu(User* user){
    if(user == nullptr) return;
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
                user->schedule_event();
                break; // Continue the loop to let the user choose again
            case 2:
                user->register_event();
                break;
            case 3:
                search_menu();
                break;
            case 4:
                user->postpone_meeting();
                break;
            case 5:
                user->cancel_meeting();
                break;
            case 6:
                user->viewUserEvents();
                break;
            case 7:
                Menu::feedback_menu(user);
                break;
            case 8:
                Feedback::review_feedbacks(user);
                break;
            case 9:
                start_menu();  // Sign out and return to the start menu
                return; // Exit the loop and the main_menu function
            default:
                cout << "Invalid choice, please choose a number." << endl;
        }
    }
}


void Menu::search_menu(){
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

    cout << "\nPlease choose the type of the event: (enter 0 to exit)" << endl;
    cout << "1) Conference" << endl;
    cout << "2) Webinar" << endl;
    cout << "3) Workshop" << endl;
    cout << "Enter a number: ";
    int searched_type;
    string searched_typeSTR;
    while(true){
        if(!(cin >> searched_type)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, choose (1-3): ";
            continue;
        }
        else if(searched_type == 0){
            cout << "Exited searching!" << endl;
            loadingAnimation(3);
            return;
        }
        else if(searched_type < 1 || searched_type > 3){
            cout << "Invalid choice, choose (1-3): ";
        }
        else break;
    }
    switch(searched_type){
    case 1:
        searched_typeSTR = "Conference";
        break;
    case 2:
        searched_typeSTR = "Webinar";
        break;
    case 3:
        searched_typeSTR = "Workshop";
        break;
    }
    for(Event* event : allEvents){
        if(searched_typeSTR == event->getType()){
            matchedEvents.insert(event);
        }
    }
    if(matchedEvents.empty()){
        cout << "No results found!" << endl;
        loadingAnimation(3);
    }else{
        cout << endl;
        printMultiset(matchedEvents);
    }

}


void search_by_date(){
    set<Event*> matchedEvents;

    cout << "Enter event date (YYYY-MM-DD): (enter '0' to exit)" << endl;
    string searched_event_date;
    getline(cin >> ws, searched_event_date);

    if(searched_event_date == "0"){
        cout << "Exited searching!" << endl;
        loadingAnimation(3);
        return;
    }
    for(Event* event : allEvents){
        if(searched_event_date == event->getDate()){
            matchedEvents.insert(event);
        }
    }
    if(matchedEvents.empty()){
        cout << "No results found!" << endl;
        loadingAnimation(3);
    }else{
        cout << endl;
        printMultiset(matchedEvents);
    }
}


void search_by_name(){
    set<Event*> matchedEvents;

    cout << "Enter event name: (enter '0' to exit)" << endl;
    string searched_event_name;
    getline(cin >> ws, searched_event_name);

    if(searched_event_name == "0"){
        cout << "Exited searching!" << endl;
        loadingAnimation(3);
        return;
    }
    for(Event* event : allEvents){
        if(searched_event_name == event->getName()){
            matchedEvents.insert(event);
        }
    }
    if(matchedEvents.empty()){
        cout << "No results found!" << endl;
        loadingAnimation(3);
    }else{
        cout << endl;
        printMultiset(matchedEvents);
    }
}


void Menu::feedback_menu(User* user) {
    // Load all events associated with this user
    set<Event*> registeredEvents = user->get_registered_events();

    if (registeredEvents.empty()) {
        cout << "\nNo events found to give feedback on!" << endl;
        loadingAnimation(3);
        return;
    }

    // List all available events for the user to choose from
    cout << endl;
    cout << "Select an event to give feedback on:" << endl;
    int index = 1;
    vector<Event*> eventList;
    for (Event* e : registeredEvents) {
        cout << index++ << ") " << e->getName() << " on " << e->getDate() << " at " << e->getTime() << endl;
        eventList.push_back(e);
    }

    // Ask user to select an event by number
    int choice;
    cout << "Enter event number: ";
    cin >> choice;
    cout << endl;

    // Check if user selection is valid
    if (choice < 1 || static_cast<size_t>(choice) > eventList.size()) {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Get the selected event
    Event* selectedEvent = eventList[choice - 1];

    // Extract event details
    string eventTitle = selectedEvent->getName();
    string eventDate = selectedEvent->getDate();
    string eventType = selectedEvent->getType();
    string creator = selectedEvent->getCreator()->getUsername();

    // Create a Feedback object
    Feedback fb(user->getUsername(), eventTitle, eventType, eventDate);

    // Attach the event creator as an observer
    User* creatorUser = nullptr;
    for (const User* user : allUsers) {
        if (user->getUsername() == creator) {
            creatorUser = const_cast<User*>(user);
            fb.attach(creatorUser);
            break;
        }
    }

    // Define a list of feedback aspects
    vector<string> aspects = {"Content", "Delivery", "Relevance", "Duration"};

    // Collect and process feedback
    if (fb.collectFeedbackInteractive(aspects)) {
        fb.display(true); // Show notice if an event is in the future
        fb.saveToFile();
        fb.notify(); // Notify observers (now includes creatorUser)
    } else {
        cout << "Feedback not collected because the event has not been launched yet." << endl;
    }
}




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

    // Used to store Users in a set in alphabetical order.
bool User::operator<(const User& other) const {
        return username < other.username;
    }

void User::update(const string& eventName, const string& message) {
    cout << "Notification for " << username << ": " << message << " for event: " << eventName << endl;
}


void User::schedule_event(){
    int choice;
    cout << "\nPlease choose the type of the event:" << endl;
    cout << "1) Conference" << endl;
    cout << "2) Webinar" << endl;
    cout << "3) Workshop" << endl;
    cout << "4) Exit" << endl;
    cout << "Enter a number: ";

    while(true){
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        else if(choice < 1 || choice > 4){
            cout << "Invalid input, Please enter a number (1-4): ";
        }
        else break;
    }
    Event* event = nullptr;
    switch (choice) {
        case 1:
            event = Event::eventBuilder(Conference_, this);
            break;
        case 2:
            event = Event::eventBuilder(Webinar_, this);
            break;
        case 3:
            event = Event::eventBuilder(Workshop_, this);
            break;
        case 4:
            return;
        default:
            return;
    }
    if (event) {
        allEvents.insert(event);
    }
    cout << "Event scheduled successfully!" << endl;
    loadingAnimation(3);
}


set<Event*> User::get_scheduled_events() {
    set<Event*> userEvents;
    for(Event* event : allEvents){
        if(username == event->getCreator()->getUsername())
            userEvents.insert(event);
    }
    return userEvents;
}


void User::register_event(){
    vector <Event*> events;
    for(Event* event : allEvents){
        if (username == event->getCreator()->getUsername()) continue;
        events.push_back(event);
    }
    if (events.empty()){
        cout << "\nNo events available for registration." << endl;
        loadingAnimation(3);
        return;
    }

    cout << "\nAvailable events:" << endl;
    for(int i=0 ; i<events.size() ; i++){
        cout << "----------------------------" << endl;
        cout << i+1 << ")\n";
        events[i]->displayDetails();
        cout << endl;
    }
    cout << "Choose an event to register (1-" << events.size() << ") (enter 0 to exit): ";

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
        else if(isRegistered(events[choice - 1])){
            cout << "You've already registered for this event!" << endl;
            cout << "Choose another event: " << endl;
        }
        else break;
    }

    Event* selectedEvent = events[choice - 1];
    if (!selectedEvent->addRegistrar(this)) {
        cout << "Sorry, this event is already full!" << endl;
        loadingAnimation(3);
    } else {
        cout << "\nYou've registered successfully!" << endl;
        selectedEvent->attach(this);
        loadingAnimation(3);
    }
}


bool User::isRegistered(Event* event){
    set<User*> eventRegistrars = event->getRegistrars();
    return(eventRegistrars.find(this) != eventRegistrars.end());
}

set<Event*> User::get_registered_events() {
    set<Event*> RegisteredEvents;
    for(Event* event : allEvents){
        set<User*> eventRegistrars = event->getRegistrars();
        auto it = (eventRegistrars).find(this);
        if(it != eventRegistrars.end()){
            RegisteredEvents.insert(event);
        }
    }
    return RegisteredEvents;
}


void User::viewUserEvents(){
    set<Event*> ScheduledEvents = get_scheduled_events();
    set<Event*> RegisteredEvents = get_registered_events();


    cout << "\nScheduled ";
    if(ScheduledEvents.empty())
        cout << "Meetings:\n-----------------------------\nYou have no scheduled meetings." << endl;
    else
        printMultiset(ScheduledEvents);

    cout << "\nRegistered ";
    if(RegisteredEvents.empty())
        cout << "Meetings:\n-----------------------------\nYou have no registered meetings." << endl;
    else
        printMultiset(RegisteredEvents);
    loadingAnimation(3);
}


void User::postpone_meeting() {

    set<Event*> userEventsSet = get_scheduled_events();
    vector<Event*> userEvents;
    for(Event* event : userEventsSet){
        userEvents.push_back(event);
    }

    if (userEvents.empty()){
        cout << "\nYou haven't scheduled any events!" << endl;
        loadingAnimation(3);
        return;
    }

    cout << "\nYour events:" << endl;
    for(int i=0 ; i<userEvents.size() ; i++){
        cout << "----------------------------" << endl;
        cout << i+1 << ")\n";
        userEvents[i]->displayDetails();
        cout << endl;
    }

    string newDate, newTime;
    cout << "Choose the event you want to postpone (1-" << userEvents.size() << ") (enter 0 to cancel): ";
    int choice;
    while (true) {
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (0 to cancel): ";
            continue;
        }
        if (choice == 0) {
            cout << "Postponement canceled.\n";
            loadingAnimation(3);
            return;
        }
        if (choice < 1 || choice > userEvents.size()) {
            cout << "Invalid choice, choose (1-" << userEvents.size() << "): ";
            continue;
        }
        break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
    Event* selectedEvent = userEvents[choice - 1];

    cout << "New date (YYYY-MM-DD): ";
    getline(cin, newDate);
    while((newDate[4] != '-') || (newDate[7] != '-'))  {
        cout << "Wrong format!" << endl << "Enter date (YYYY-MM-DD): ";
        getline(cin, newDate);
    }
    selectedEvent->setDate(newDate);

    cout << "New time (HH:MM): ";
    getline(cin, newTime);
    while(newTime[2] != ':') {
    cout << "Wrong format!" << endl << "Enter time (HH:MM): ";
    getline(cin, newTime);
    }
    selectedEvent->setTime(newTime);
    selectedEvent->notify(Event_postponement);

    cout << "Event postponed successfully!\n";

    loadingAnimation(3);
}


void User::cancel_meeting() {

    set<Event*> userEventsSet = get_scheduled_events();
    vector<Event*> userEvents;
    for(Event* event : userEventsSet){
        userEvents.push_back(event);
    }

    if (userEvents.empty()){
        cout << "\nYou haven't scheduled any events!" << endl;
        loadingAnimation(3);
        return;
    }

    cout << "\nYour events:" << endl;
    for(int i=0 ; i<userEvents.size() ; i++){
        cout << "----------------------------" << endl;
        cout << i+1 << ")\n";
        userEvents[i]->displayDetails();
        cout << endl;
    }

    string eventName, line;
    cout << "Choose the event you want to cancel (1-" << userEvents.size() << ") (or type 'exit' to cancel): ";
    getline(cin >> ws, eventName);
    int choice = stoi(eventName);
    while(true){
        if (eventName == "exit") {
            cout << "Exited cancellation.\n";
            loadingAnimation(3);
            return;  // Immediately exit the function
        }
        else if(choice < 1 || choice > userEvents.size()){
            cout << "Invalid choice, choose (1-" << userEvents.size() << "): ";
        }
        else break;
    }
    Event* selectedEvent = userEvents[choice - 1];
    allEvents.erase(selectedEvent);
    cout << "Event canceled successfully!\n";
    selectedEvent->notify(Event_cancellation);
    selectedEvent->detach(this);
    loadingAnimation(3);
}




///////////////////////////   Event   /////////////////////////

Event::Event(){}
Event::Event(string n, User* creator, string desc, string p, string d, string t, int c, int f)
    : event_name(std::move(n)), creator_user(creator), description(desc), platform(p), date(d), time(t), capacity(c), full(f) {
    creator_name = creator ? creator->getUsername() : "";
}

//Implementation of getter functions
string Event::getName() const { return event_name; }
User* Event::getCreator() const { return creator_user;}
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getTime() const { return time; }
string Event::getPlatform() const { return platform; }
int Event::getCapacity() const { return capacity; }
set<User*> Event::getRegistrars(){ return registrars; }

bool Event::operator<(const Event& other) const {
    return (date == other.date) ? (time < other.time) : (date < other.date);
}

void Event::setDate(string newDate){ date = newDate; }
void Event::setTime(string newTime){ time = newTime; }


bool Event::addRegistrar(User* user){
    if (isFull()) return false;
    registrars.insert(user);
    if(registrars.size() >= capacity)
        full = 1;
    return true;
}


bool Event::isFull(){
    return full;
}


// Factory Method Implementation: Part of Factory Design Pattern
Event* Event::eventBuilder(const eventType Type, User* creator) {
    if (Type == Conference_) {
        return Conference::create_event(creator);
    }
    else if (Type == Webinar_) {
        return Webinar::create_event(creator);
    }
    else if (Type == Workshop_) {
        return Workshop::create_event(creator);
    }
    else return nullptr;
}

void Event::attach(Observer* observer) {
    observers_.push_back(observer);
}
void Event::detach(Observer* observer) {
    observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
}
void Event::notify(const notificationType type) {
    switch (type) {
        case 0:
            for (Observer* observer : observers_) {
                observer->update(this->getName(), "Date changed to " + this->getDate());
            }
            break;
        case 1:
            for (Observer* observer : observers_) {
                observer->update(this->getName(), "Canceled");
            }
            break;
        default:
            return;
    }
}


////////////////////////   Conference   ////////////////////////////

Conference::Conference(){}
Conference::Conference(string n, User* creator, string desc, string p, string d, string t, int c, int dur)
    : Event(n, creator, desc, p, d, t, c, 0), duration(dur) {}

string Conference::getType() const{ return "Conference";}
int Conference::getDuration() const{ return duration;}

// Static Factory Method Implementation: Part of Factory Design Pattern
Event* Conference::create_event(User* creator){
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

    Conference* conference = new Conference(name, creator, desc, platform, date, time, capacity, duration);
    return conference;
}


void Conference::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Creator: " << (getCreator() ? getCreator()->getUsername() : "Unknown") << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Duration: " << getDuration() << " days" << endl;
}


void Conference::saveToFile(ofstream& file){
    file << getType() << "|"
        << creator_name << "|"
        << event_name << "|"
        << description << "|"
        << date << "|"
        << time << "|"
        << platform << "|"
        << capacity << "|"
        << duration << "|";
    for(User* registrar : registrars){
        file << registrar->getUsername() << "|";
    }
    file << endl;
}


Event* Conference::loadFromFile(const string& line){
    stringstream ss(line);
    string creatorName, name, desc, date, time, platform, capacityStr, durationStr, type, registrar;
    getline(ss, type, '|');
    getline(ss, creatorName, '|');
    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, durationStr, '|');
    int capacity = stoi(capacityStr);
    int duration = stoi(durationStr);
    User* creator = nullptr;
    for(User* user : allUsers){
        if(user->getUsername() == creatorName){
            creator = user;
            break;
        }
    }
    Conference* conference = new Conference(name, creator, desc, platform, date, time, capacity, duration);
    while(getline(ss, registrar, '|')){
        for(User* user : allUsers){
            if(registrar == user->getUsername())
                conference->addRegistrar(user);
        }
    }
    return conference;
}




/////////////////////////   Webinar   ///////////////////////////


Webinar::Webinar(){}
Webinar::Webinar(string n, User* creator, string desc, string p, string d, string t, int c, string h)
    : Event(n, creator, desc, p, d, t, c, 0), host(h) {}

string Webinar::getType() const{ return "Webinar";}
string Webinar::getHost() const{ return host;}

void Webinar::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Creator: " << (getCreator() ? getCreator()->getUsername() : "Unknown") << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Host: " << getHost() << endl;
}

// Static Factory Method Implementation: Part of Factory Design Pattern
Event* Webinar::create_event(User* creator){
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

    Webinar* webinar = new Webinar(name, creator, desc, platform, date, time, capacity, host);
    return webinar;
}


void Webinar::saveToFile(ofstream& file){
    file << getType() << "|"
        << creator_name << "|"
        << event_name << "|"
        << description << "|"
        << date << "|"
        << time << "|"
        << platform << "|"
        << capacity << "|"
        << host << "|";
    for(User* registrar : registrars){
        file << registrar->getUsername() << "|";
    }
    file << endl;
}


Event* Webinar::loadFromFile(const string& line){
    stringstream ss(line);
    string creatorName, name, desc, date, time, platform, capacityStr, host, type, registrar;
    getline(ss, type, '|');
    getline(ss, creatorName, '|');
    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, host, '|');
    int capacity = stoi(capacityStr);
    User* creator = nullptr;
    for(User* user : allUsers){
        if(user->getUsername() == creatorName){
            creator = user;
            break;
        }
    }
    Webinar* webinar = new Webinar(name, creator, desc, platform, date, time, capacity, host);
    while(getline(ss, registrar, '|')){
        for(User* user : allUsers){
            if(registrar == user->getUsername())
                webinar->addRegistrar(user);
        }
    }
    return webinar;
}




////////////////////////////   Workshop   ////////////////////////

Workshop::Workshop(){}
Workshop::Workshop(string n, User* creator, string desc, string p, string d, string t, int c, string i)
    : Event(n, creator, desc, p, d, t, c, 0), instructor(i) {}

string Workshop::getType() const{ return "Workshop";}
string Workshop::getInstructor() const{ return instructor;}

void Workshop::displayDetails() const {
    cout << "Event: " << getName() << " (" << getType() << ")" << endl;
    cout << "Creator: " << (getCreator() ? getCreator()->getUsername() : "Unknown") << endl;
    cout << "Date: " << getDate() << " at " << getTime() << endl;
    cout << "Platform: " << getPlatform() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Instructor: " << getInstructor() << endl;
}

// Static Factory Method Implementation: Part of Factory Design Pattern
Event* Workshop::create_event(User* creator){
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

    Workshop* workshop = new Workshop(name, creator, desc, platform, date, time, capacity, instructor);
    return workshop;
}


void Workshop::saveToFile(ofstream& file){
    file << getType() << "|"
        << creator_name << "|"
        << event_name << "|"
        << description << "|"
        << date << "|"
        << time << "|"
        << platform << "|"
        << capacity << "|"
        << instructor << "|";
    for(User* registrar : registrars){
        file << registrar->getUsername() << "|";
    }
    file << endl;
}


Event* Workshop::loadFromFile(const string& line){
    stringstream ss(line);
    string creatorName, name, desc, date, time, platform, capacityStr, instructor, type, registrar;
    getline(ss, type, '|');
    getline(ss, creatorName, '|');
    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, platform, '|');
    getline(ss, capacityStr, '|');
    getline(ss, instructor, '|');
    int capacity = stoi(capacityStr);
    User* creator = nullptr;
    for(User* user : allUsers){
        if(user->getUsername() == creatorName){
            creator = user;
            break;
        }
    }
    Workshop* workshop = new Workshop(name, creator, desc, platform, date, time, capacity, instructor);
    while(getline(ss, registrar, '|')){
        for(User* user : allUsers){
            if(registrar == user->getUsername())
                workshop->addRegistrar(user);
        }
    }
    return workshop;
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
void Feedback::attach(Observer* observer) {
    observers_.push_back(observer);
}
void Feedback::detach(Observer* observer) {
    observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
}
void Feedback::notify() {
    for (Observer* observer : observers_) {
        observer->update(eventName_, "New feedback received by " + reviewerUsername_);
    }
}
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
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); // Read the time in a specific format
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
    loadingAnimation(3);
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
    outfile << "generalRating: " << generalRating_ << endl;
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

void Feedback::review_feedbacks(User* user) { // This function lets a user review all feedbacks they have submitted
    string userName = user->getUsername();
    string filename = userName + "_feedback.txt";
    ifstream infile(filename);
    if (!infile.is_open()) {
        // If a feedback file not found, inform the user and exit
        cout << "\nNo previous feedbacks found for user: " << userName << endl;
        loadingAnimation(3);
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
        loadingAnimation(3);
        return;
    }

    // Display all feedbacks using the Feedback::display method
    cout << "\n--- Your Feedback Entries ---" << endl;
    int idx = 1;
    for (auto& fb : feedbacks) {
        cout << "\nFeedback #" << idx++ << ":\n";
        fb.display(false); // Do not show the 'event not launched' notice
    }
    loadingAnimation(3);
}




////////////////////////////////////////////////////////////////////////////////


template <typename T> void printMultiset(const set<T>& mset) {
    cout << "Meetings:\n" << "-----------------------------" << endl;
    for (const T& value : mset) {
        value->displayDetails();  // Calls the displayDetails() method
        cout << "-----------------------------" << endl;  // Optional separator
    }
    cout << endl;
}


void signup(){
    while(true){
        string inUsername, inPassword, inEmail, inAffiliation;
        bool found = false;

        cout << "Enter username: ";
        getline(cin >> ws, inUsername);

        for(User* user : allUsers){
            if(inUsername == user->getUsername()){
                cout << "Username is taken!" << endl;
                found = true;
                break;
                }
        }
        if(found) continue;
        cout << "Enter password: ";
        getline(cin >> ws, inPassword);

        cout << "Enter email: ";
        getline(cin >> ws, inEmail);

        cout << "Enter affiliation (optional - press enter to skip): ";
        getline(cin, inAffiliation);

        User* user = new User(inUsername, inPassword, inEmail, inAffiliation);
        allUsers.insert(user);

        cout << "Signup successful!" << endl;
        loadingAnimation(3);
        break;
    }

}


User* login() {

    while (true) {
    string inUsername, inPassword, inEmail, inAffiliation;
    bool loginSuccess = false;

        cout << "Enter username: ";
        getline(cin >> ws, inUsername);
        cout << "Enter password: ";
        getline(cin >> ws, inPassword);

        for(User* user : allUsers){
            if(inUsername == user->getUsername() && inPassword == user->getPassword()){
                cout << "\nWelcome, " << inUsername << "!" << endl;
                return user; // Return the existing user pointer
            }
        }
        cout << "Invalid username or password!" << endl;
        return nullptr;
    }
}


void loadUsersData(){
    string username, password, email, affiliation, line;
    ifstream usersFile("users.txt");

    while (getline(usersFile, line)) {
        stringstream ss(line);
        ss >> username >> password >> email >> ws; //ws to discard the white space
        getline(ss, affiliation);
        allUsers.insert(new User(username, password, email, affiliation));
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


void saveUsersToFile(){

    ofstream usersFile("users.txt", ios::out | ios::trunc);  // Open once and truncate
    if (!usersFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    for(User* user : allUsers){
        usersFile << user->getUsername() << " " << user->getPassword() << " " << user->getEmail() << " " << user->getAffiliation() << endl;
    }
    usersFile.close();
}


void saveEventsToFile(){
    ofstream file("events.txt", ios::out | ios::trunc);  // Open once and truncate

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    for(Event* event : allEvents){
        event->saveToFile(file);
    }
    file.close();
}


void loadingAnimation(int seconds) {
    for (int i = 0; i < seconds; i++) {
        cout << "." << std::flush;
        this_thread::sleep_for(chrono::milliseconds(500));  // 0.5 second delay
    }
    cout << endl;
}


int main() {
    Menu menu;
    menu.setup();
    return 0;
}

