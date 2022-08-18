#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class User{
    private:
    string userName;
    string email;
    bool loggedIn = false;
    char role = 'u';
    string bookedFl , bookedTi;
    public:
    User(){}
    string getUserName() const { return userName; }
    string getEmail(){return email; }
    string getFlightId(){return bookedFl;}
    string getTicketId(){return bookedTi;}
    void setLoggedIn(bool v){ loggedIn = v;}
    void setEmail(string n){email = n;}
    void setUserName(string n){userName = n;}
    void setRole(char r){role = r;}
    void setFlightId(string r){bookedFl = r;}
    void setTicketId(string r){bookedTi = r;}
    bool getLoggedIn() { return loggedIn;}
    virtual char getRole(){return role;}
    virtual bool signingUp(){return false;}
    virtual bool logInCheck(){return false;}
    void saveBookedFlightAndTickets(string , string );
};

void User::saveBookedFlightAndTickets(string fid , string tid){
    ofstream file(email + ".txt" , ios::app);
    file<<"-"<<fid<<"-"<<tid;
    setFlightId(fid);
    setTicketId(tid);
}