#include <iostream>
#include <fstream>
#include <unordered_set>
#inlcude <string>

using namespace std;

void login(){
    string username, password;
    bool loginSuccess = false;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    fstream users("loginDataBase.txt");
    
    if (!users.is_open()) {
        cout << "Error: Unable to open database file!" << endl;
        return ;
    }
    
    string fileUsername, filePassword;
    
    while (getline(users, fileUsername)) {
        if (getline(users, filePassword)) {  
            if (fileUsername == username && filePassword == password) {
                loginSuccess = true;
                break;
            }
        }
    }

    users.close();
    
    if (loginSuccess) {
        cout << "Welcome, " << username << endl;
    } else {
        cout << "Invalid username or password!" << endl;
        login();
    }
    
}


void signup(unordered_set<string> usernames){

        string username, password;

        fstream users("loginDataBase.txt", ios::app);

        if (!users.is_open()) {
            cout << "Error: Unable to open database file!" << endl;
            return ;
        }

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if(usernames.count(username)){
            cout << "Username is taken!" << endl;
            signup(usernames);
        }else{
            users << username << " " << password << "\n";
        }

        users.close();
    }


void start_menu(unordered_set<string> usernames){
    int choice;
    cout << "Please choose one of these options:" << endl;
    cout << "1) Login" << endl;
    cout << "2) Signup" << endl;
    cout << "3) Exit" << endl;
    cout << "Enter a number: ";
    cin >> choice;

    switch (choice){
        case 1 :
            login();
            //start_menu(usernames);
            break;
        case 2:
            signup(usernames);
            start_menu(usernames);
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Invalid choice, please choose 1, 2 or 3" << endl;
            start_menu(usernames); 
            break;
    }
}


void setup(){
    
    unordered_set<string> usernames;
    string userName;
    fstream users("loginDataBase.txt");
    while(users >> userName){
        usernames.insert(userName);
        users >> userName;
    }
    users.close();

    cout << "=========================" << endl;
    cout << "=========================" << endl;
    cout << "=========WELCOME=========" << endl;
    cout << "=========================" << endl;
    cout << "=========================" << endl;

    start_menu(usernames);

}

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


int main(){

    setup();

    return 0;
}
