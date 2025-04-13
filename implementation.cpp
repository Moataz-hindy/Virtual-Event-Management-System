#include "events.h"
#include <iostream>
#include <string>
using namespace std;

class Event{
private:
    string event_name;
    string description;
    string platform;
    string date;
    string time;
    int capacity;
    string type;
public:
   Event() {} // Default constructor used in order to make the classe can be used in arrays
   Event(string n, string desc, string d, string t, string p, int c, string typ){
   event_name = n;
   description = desc;
   platform = p;
   date = d;
   time = t;
   capacity = c ;
   type = typ;
   }
   void displayDetails() const {
        cout << "Event: " << event_name << " (" << type << ")"<<endl;
        cout << "Date: " << date << " at " << time << endl;
        cout << "Platform: " << platform << endl;
        cout << "Description: " << description <<endl;
        cout << "Capacity: " << capacity  << endl;
    }
    string getName() const {
        return event_name ;
        }
    string getDescription() const {
        return description;
         }
    string getDate() const {
        return date;
        }
    string getTime() const {
        return time;
         }
    string getPlatform() const {
        return platform;
         }
    int getCapacity() const {
        return capacity;
        }
    string getType() const {
        return type;
        }

};
class Attendee{
private:
    string name;
    string email;
    string affiliation;
public:
    Attendee() {}// Default constructor used in order to make the classe can be used in arrays
    Attendee(string n, string e, string a){
    name = n;
    email = e;
    affiliation = a;
    }
    void setEmail(string e){
    email = e;
    }
    string getEmail ()const{
    return email;
    }
    void setName(string n){
       name = n;
    }
    string getName ()const{
    return name ;
    }
        void setAffiliation(string a){
       affiliation = a;
    }
    string getAffiliation()const{
    return affiliation ;
    }
 // void display(){}
};
class Feedback{
private:
    string name;
    int ratings;
    string reviews;
public:
    Feedback() {}// Default constructor used in order to make the classe can be used in arrays
    Feedback(string n,int ra, string re){
    name = n;
    ratings = ra;
    reviews = re;
// To ensure ratings are within the range
        if (ratings < 0) {
            ratings = 0;
     }
        if (ratings > 5){
                ratings = 5;
     }
}
 void display()  {
        cout <<name<<" rated "<< ratings <<"out of 5"<<endl;
        cout << "Review: " << reviews <<endl;
    }
     int getRating() const {
          return rating; 
          }
    string getReview() const {
         return review; 
         }
};

