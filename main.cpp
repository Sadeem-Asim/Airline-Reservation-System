#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

#include "utils.h"
#include "user.h"
#include "authentication.h"
#include "ticket.h"
#include "flight.h"

using namespace std;
class App{
    private:
    User* currentUser;
    Flight flight;
    public:
    ~App(){
    delete currentUser;
    }
    void mainMenuAdmin();
    void mainMenuUser();
    void logInAndSignUp();
};

void App::logInAndSignUp(){
    char option;
    bool success;
    while(true){
        cout<<"                  Welcome To Airline Reservation System !       "<<endl;
        cout<<"                  Enter L for Log In and S for Sign Up          "<<endl;
        option=getche();
        vector <char> checkFields{'l' , 's' , 'L'  , 'S'};
        success = inputCheck(option , checkFields);
        if(success) break;
        cout<<"Error  Try Again "<<endl;
}

// Log In
    if(option == 'l' || option == 'L'){
        User* user;
        int logInTries = 0;
        bool success;
        do{
        if(logInTries > 2){
        cout<<"Wanna Sign Up. Register Now ? Enter s"<<endl;
        option=getche();
        if(option == 's' || option == 'S')break;
        }
        string e, p;
        cout<<"Enter Email : ";
        cin>>e;
        cout<<"Enter Password : ";
        cin>>p;
        user = new Login(e , p);
        success = user->logInCheck();
        logInTries++;
        }while(!success);
        if(success){
            cout<<"Logged In Successfully"<<endl;
            currentUser = user;
            if(currentUser->getRole() == 'a') mainMenuAdmin();
            else if(currentUser->getRole() == 'u') mainMenuUser();
        }
        }

// Sign Up
    if(option == 's' || option == 'S'){
        User* user;
        bool success = false;
        do{
            string n,e,p;
            char r;
            cout<<"Enter Name : ";
            cin>>n;
            cout<<"Enter Email : ";
            cin>>e;
            cout<<"Enter Password : ";
            cin>>p;
            cout<<"Enter Role('u' for User And 'a' for Admin) : ";
            r=getche();
            vector <char> checkRole{'a' , 'u'};
            bool roleCheck = inputCheck(r , checkRole);
            if(!roleCheck){
                cout<<"Invalid Role"<<endl;
                continue;
            }
            user = new Signup(n,e,p,r);
            success =  user->signingUp();
        }while(!success);

        if(success){
            cout<<"Signed Up Successfully!"<<endl;
            currentUser = user;
            if(user->getRole() == 'a') mainMenuAdmin();
            else if(user->getRole() == 'u') mainMenuUser();
        }
        }
    }

void App::mainMenuUser(){
        loadingFeature();
        system("CLS");
        string bookedFlightAndTicket;
        string bookedFlight;
        string bookedTicket;
        char option;
        vector <char> allowedOptions{'1' , '2' , '3' , '4'};
        do{
            do{
                cout<<endl<<"MAIN MENU USER"<<endl;
                cout<<"1 - Book Your Seat"<<endl;
                cout<<"2 - See All Flights Schedule"<<endl;
                cout<<"3 - Print My Ticket"<<endl;
                cout<<"4 - Quit"<<endl;
                option = getche();
            }while(!inputCheck(option , allowedOptions));
            switch (option){
                case '1':
                bookedFlightAndTicket = flight.bookTicket();
                bookedFlight = bookedFlightAndTicket.substr(0,3);
                bookedTicket = bookedFlightAndTicket.substr(4,10);
                currentUser->saveBookedFlightAndTickets(bookedFlight , bookedTicket);
                break;
                case '2':
                flight.seeAllFlights();
                    break;
                case '3':
                flight.printMyTicket(currentUser);
                   break;
                case '4':
                  break;
                default:
                cout<<"Invalid Option"<<endl;
                    break;
                }
        }while(option != '4');
}

void App::mainMenuAdmin(){
    loadingFeature();
    system("CLS");
    char option;
    vector <char> allowedOptions{'1' , '2' , '3' , '4'};
        do{
            do{
            cout<<endl<<"MAIN MENU ADMIN"<<endl;
            cout<<"1 - Add Flight"<<endl;
            cout<<"2 - Delete Flight"<<endl;
            cout<<"3 - See All Flights"<<endl;
            cout<<"4 - Quit"<<endl;
            option = getche();
            system("cls");
            }while(!inputCheck(option , allowedOptions));
            switch (option){
                case '1':
                flight.addFlight();
                    break;
                case '2':
                flight.deleteFlight();
                    break;
                case '3':
                flight.seeAllFlights();
                    break;
                case '4':
                    break;
                default:
                    cout<<"Invalid Option Enter Again Or Press 4 To Quit"<<endl;
                    break;
            }
        }while(option != '4');
}
int main(){
    loadingFeature();
    system("CLS");
    App app;
    app.logInAndSignUp();
    system("cls");
    return 0;
}





