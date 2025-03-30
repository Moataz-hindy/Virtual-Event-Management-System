#ifndef EVENTS_H
#define EVENTS_H

using namespace std;

class Event{
    private:
    string event_name;
    string description;
    string platform;
    string date;
    string time;
    public:
    Event();
    void create_event();
};
#endif
