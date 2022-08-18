#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Signup:public User{
    string name;
    string email;
    string password;
    char role;
    public:
    Signup(string u, string e, string p , char r){
        name = u;
        email = e;
        password = p;
        role  =r;
}

bool signingUp();
};


bool Signup::signingUp(){
    // Making A New File
    ofstream user(email + ".txt");
    ofstream users("users.txt" , ios::app);

    User::setRole(role);
    // Writing To A File
    user<<email<<"-"<<password<<"-"<<name<<"-"<<role<<endl;
    users<<name<<"-"<<email<<"-"<<role<<endl;
    users.close();
    User::setUserName(name);
    User::setRole(role);
    User::setEmail(email);
    User::setLoggedIn(true);
    return true;
}


class Login : public User{
    string email;
    string password;
    bool authenticated = false;
    public:
    Login(string email, string password){
    this->email = email;
    this->password = password;
    }
    bool logInCheck();
    bool getAuthenticated() { return authenticated; }
};

bool Login::logInCheck(){
    string e , p , n;
    string flightId  = "", ticketId = "";
    string r;
    // Opening File Of user
    ifstream user(email+".txt");
    if(!user){
        cout<<"Your Email Or Password Was Incorrect! Please Try Again!"<<endl;
        return false;
    }
    // Reading File Of user
    getline(user, e ,'-');
    getline(user, p , '-');
    getline(user, n , '-');
    getline (user , r ,'-');
    getline(user ,flightId , '-');
    getline(user ,ticketId , '-');

    if(email == e && password == p){
        authenticated = true;
        User::setLoggedIn(authenticated);
        User::setEmail(email);
        User::setUserName(n);
        User::setRole(r[0]);
        User::setFlightId(flightId);
        User::setTicketId(ticketId);
        return true;
    }
    return false;
}