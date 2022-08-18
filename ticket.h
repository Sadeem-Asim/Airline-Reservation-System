#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

class Ticket{
    protected:
    flightDetails flight;
    string ticketId;
    int totalFlightTime;
    int totalSeats;
    int economySeats;
    int firstClassSeats;
    int businessSeats;
    int bookedSeats = 0;
    vector <string> bookedSeatsId;
    public:
    Ticket(vector <flightDetails> fd){
    int option;
    cout<<"Choose Your Flight"<<endl;
    cin>>option;
    flight = fd[option - 1];

    totalSeats = atoi(flight.totalSeats.c_str());
    totalFlightTime = atoi(flight.totalFlightTime.c_str());
    economySeats = totalSeats * 0.6;
    firstClassSeats = totalSeats * 0.3;
    businessSeats = totalSeats * 0.1;

    string temp;
    int count = 0;
    ifstream file (flight.flightNo + ".txt");
    if(!file){
        return;
    }

    while(!file.eof()){
        getline(file , temp , '-');
        if(count == 0){
        bookedSeats = atoi(temp.c_str());
        count++;
        continue;
        }
        bookedSeatsId.push_back(temp);
        count++;
    }
}

void showSeats(){
    const int col = 10;
    int rows = totalSeats / 10;
    int seats[rows][col] = {0};
    int bookedRow , bookedCol;
    for(int i = 0; i < bookedSeatsId.size();i++){
        bookedRow = (atoi((bookedSeatsId[i].substr(1,1)).c_str()))-1;
        bookedCol = (atoi((bookedSeatsId[i].substr(2,2)).c_str()))-1;
        seats[bookedRow][bookedCol] = 1;
    }


    cout<<"The Airplane Seats Are Given Below"<<endl;
    char a = 'A';
    cout<<"    ";
    for(int j =0; j< col; j++) {
        cout<<j+1<<"  ";
    }
    cout<<endl;
    for(int i = 0; i < rows; i++ , a++) {
        cout<<a<<i+1<<"  ";
    for(int j = 0;j < col; j++) {
        cout<<seats[i][j]<<"  ";
    }
    cout<<endl;
    }
    cout<<"The First 6 Columns Are Economy Class -Next 3 Are First-Class-Last Column Is Business Class"<<endl;
}

virtual double calculateTicketPrice(){return 0.0;}

string confirmBooking(string no){
    bool success = checkSeatCorrect(no ,totalSeats / 10);
    if(!success){
    return "";
    }
    ticketId = no;
    for(int i = 0; i < bookedSeatsId.size(); i++){
        if(ticketId == bookedSeatsId[i]){
            return "";
        }
    }
    cout<<"Booking Confirmed"<<endl;
    bookedSeatsId.push_back(ticketId);
    bookedSeats++;

    ofstream file(flight.flightNo + ".txt");
    file<<bookedSeats;
    for(int i=0;i<bookedSeatsId.size();i++){
        file<<"-"<<bookedSeatsId[i];
    }
    string flightIdAndSeatNo = flight.flightNo + " " + ticketId;
    return flightIdAndSeatNo;
    }
};


class EconomyTicket:public Ticket{
    double perHourRate = 10000;
    public:
    EconomyTicket(vector <flightDetails> fd):Ticket(fd){}
    double calculateTicketPrice(){
    return totalFlightTime * perHourRate;
    }
};

class FirstClassTicket:public Ticket{
    double perHourRate = 12000;
    public:
    FirstClassTicket(vector <flightDetails> fd):Ticket(fd){}

    double calculateTicketPrice(){
    return totalFlightTime * perHourRate;
    }
};

class BusinessTicket:public Ticket{
    double perHourRate = 15000;
    public:
    BusinessTicket(vector <flightDetails> fd):Ticket(fd){}
    double calculateTicketPrice(){
    return totalFlightTime * perHourRate;
    }
};