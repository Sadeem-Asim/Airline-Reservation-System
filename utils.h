#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
using namespace std;

bool inputCheck(char originalInput , vector<char> checkFields){
    for(int i = 0; i < checkFields.size(); i++){
        if (originalInput == checkFields[i]){
            return true;
        }
    }
    return false;
}

void printElement(int width , string element){
    cout<< left << setw(width) << setfill(' ')<<element;
}

void loadingFeature(){
    system("cls");
    int i =5 , j =7 , k = 10 , l =18;
    while(i < 120){
        for(int i = 0; i < 5;i++){
            cout<<endl;
        }
        cout<<setw(i)<<setfill(' ')<<"   **"<<endl;
        cout<<setw(j)<<setfill(' ')<<"     **"<<endl;
        cout<<setw(k)<<setfill(' ')<<"***     **"<<endl;
        cout<<setw(l)<<setfill(' ')<<"  ****************"<<endl;
        cout<<setw(k)<<setfill(' ')<<"***     **"<<endl;
        cout<<setw(j)<<setfill(' ')<<"     **"<<endl;
        cout<<setw(i)<<setfill(' ')<<"   **"<<endl;
        cout<<"                                               Loading...                                   "<<endl;
        Sleep(500);
        i +=18;j +=18;k +=18;l +=18;
        system("cls");
    }
}


class flightDetails{
    public:
    string flightNo,flightArrival,flightDeparture,totalFlightTime,
    departureAirport , arrivalAirport, flightDate ,flightDay,totalSeats;
};

bool checkSeatCorrect(string seatNo , int rows){
    int row , col;
    char ch = seatNo[0];
    char a = 'A';
    row = (atoi((seatNo.substr(1,1)).c_str()));
    col = (atoi((seatNo.substr(2,4)).c_str()));
    if(row > rows){
    return false;
    }
    if(col > 10){
    return false;
    }
    for(int i = 0;i< rows;i++,a++){
    if(ch == a){
    if(row != i+1){
    return false;
    }
    }
    }
    return true;
}
