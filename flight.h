#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Flight{
vector <flightDetails> flights;
Ticket* ticket;
public:
Flight(){
flightDetails temp;
ifstream file("flight.txt");
while(!file.eof()) {
getline(file , temp.flightNo , '-');
getline(file , temp.flightDeparture , '-');
getline(file , temp.departureAirport , '-');
getline(file , temp.flightArrival , '-');
getline(file , temp.arrivalAirport , '-');
getline(file , temp.totalFlightTime , '-');
getline(file , temp.totalSeats , '-');
getline(file , temp.flightDate , '-');
getline(file , temp.flightDay , '\n');
flights.push_back(temp);
}
}

void addFlight();
void deleteFlight();
void seeAllFlights();
string bookTicket();
void printMyTicket(User*);
};

void Flight::addFlight(){
string flightNo,flightArrival,flightDeparture,totalFlightTime,
departureAirport , arrivalAirport, flightDate ,flightDay;
int totalSeats;
cout<<"Please Enter Details Of Your Flight"<<endl;
cout<<"Enter Flight No : ";
cin.clear();
cin.ignore(INT_MAX , '\n');
//to remove some  getline error
getline(cin,flightNo);
cout<<"Enter Flight Departure Time : ";
getline(cin,flightDeparture);
cout<<"Enter Flight Departure Airport : ";
getline(cin,departureAirport);
cout<<"Enter Flight Arrival Time : ";
getline(cin,flightArrival);
cout<<"Enter Flight Arrival Airport : ";
getline(cin,arrivalAirport);
cout<<"Enter Flight Total Time : ";
getline(cin,totalFlightTime);
cout<<"Enter Flight Date : ";
getline(cin,flightDate);
cout<<"Enter Flight Day : ";
getline(cin,flightDay);
cout<<"Enter Total Seats Of Airplane : ";
cin>>totalSeats;
ofstream flights("flight.txt" , ios::app);
flights<<flightNo<<"-"<<flightDeparture<<"-"<<departureAirport<<"-"<<flightArrival<<"-"<<arrivalAirport
<<"-"<<totalFlightTime<<"-"<<totalSeats<<"-"<<flightDate<<"-"<<flightDay<<"\n";
cout<<"Added Flight Successfully"<<endl;
}

void Flight::seeAllFlights(){
cout<<endl;
printElement(11 , "Flight Id");
printElement(18 , "Flight Departure");
printElement(16 , "Flight Arrival");
printElement(19 , "Departure Airport");
printElement(17 , "Arrival Airport");
printElement(19 , "Total Flight Time");
printElement(13 , "Flight Date");
printElement(12 , "Flight Day");
cout<<endl;
for(int i = 0; i < flights.size()-1; i++){
printElement(11 , flights[i].flightNo);
printElement(18 , flights[i].flightDeparture);
printElement(16 ,flights[i].flightArrival);
printElement(19 , flights[i].departureAirport);
printElement(17 , flights[i].arrivalAirport);
printElement(19 , flights[i].totalFlightTime);
printElement(13 , flights[i].flightDate);
printElement(12 , flights[i].flightDay);
cout<<endl;
}}


void Flight::deleteFlight(){
    seeAllFlights();
    int option , count = 1;
    string t,line , eraseLine;
    cout<<"Enter The Flight You Want To Delete"<<endl;
    cin>>option;
    string path = "flight.txt";
    ifstream file(path);
    while(!file.eof()){
        getline(file ,t , '\n');
        if(count == option){
            eraseLine = t;
            break;
        }
        count++;
    }
    ofstream temp;
    temp.open("temp.txt");
    while(getline(file, line)){
        if(line != eraseLine){
            temp<<line<<endl;
        }
    }
    temp.close();
    file.close();
    const char *p =path.c_str();
    remove(p);
    rename("temp.txt", p);
}


string Flight::bookTicket(){
    int option;
    string confirmation;
    char ticketType;
    string ticketNo;
    seeAllFlights();
    do{
        cout<<"1-Enter E for Economy"<<endl;
        cout<<"2-Enter F for First Class"<<endl;
        cout<<"3-Enter B for Business"<<endl;
        ticketType = getche();
        cout<<endl;
        vector <char> checkType = {'e','E','f','F','b','B'};
        bool success = inputCheck(ticketType, checkType);
        if(!success){
            cout<<"Invalid Input"<<endl;
        continue;
        // return "";
        }
        if(ticketType == 'e' || ticketType == 'E') ticket = new EconomyTicket(flights);
        if(ticketType == 'f'|| ticketType == 'F') ticket = new FirstClassTicket(flights);
        if(ticketType == 'b'|| ticketType == 'B') ticket = new BusinessTicket(flights);
        ticket->showSeats();
        cout<<"The Ticket Price Is : "<<ticket->calculateTicketPrice()<<endl;
        cout<<"Choose Your Seat Like This : (A11, B21)"<<endl;
        cout<<"Enter The Seat No You Want To Book : ";
        cin>>ticketNo;
        confirmation = ticket->confirmBooking(ticketNo);
        if(confirmation == ""){
            cout<<"Incorrect Seat No Or Already Booked"<<endl;
        }
    }while(confirmation == "");

    ticket->showSeats();

    return confirmation;
}



void Flight::printMyTicket(User* user){
    if(user->getEmail() == "" || user->getFlightId() == ""|| user->getTicketId() == ""){
        cout<<"You Didn't Bought Any Ticket"<<endl;
        return;
    }
    flightDetails flight;
    for(int i = 0; i < flights.size() -1; i++){
        if(user->getFlightId() == flights[i].flightNo){
            flight = flights[i];
        }
    }


    if(flight.flightNo != user->getFlightId() ){
        cout<<"No Flight Found "<<endl;
        return;
    }

    ofstream file(user->getUserName() + user->getTicketId() + ".txt");
        file<<"Name               : "<<user->getUserName()<<endl;
        file<<"Flight             : "<<user->getFlightId()<<endl;
        file<<"Seat No            : "<<user->getTicketId()<<endl;
        file<<"Departure Airport  : " << flight.departureAirport <<endl;
        file<<"Arrival Airport    : " << flight.arrivalAirport <<endl;
        file<<"Departure Time     : " << flight.flightDeparture <<endl;
        file<<"Departure Time     : " << flight.flightArrival <<endl;
        file<<"Flight Day         : " << flight.flightDay <<endl;
        file<<"Flight Date        : " << flight.flightDate <<endl;


    cout<<"Successfully Printed Your Ticket"<<endl;
}








