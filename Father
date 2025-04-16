#include <iostream>
#include <fstream>
#include <unordered_set>

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


int main(){

    setup();

    return 0;
}
