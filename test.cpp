#include <iostream>
using namespace std;



struct Hello{
public:
private:
};

struct hey:public Hello{
hey(){
cout<<"hello"<<endl;
}
};



int main (){

hey sd;
}


// The only difference between a struct and class in C++ is the default accessibility of member
//  variables and methods. In a struct they are public; in a class they are private.