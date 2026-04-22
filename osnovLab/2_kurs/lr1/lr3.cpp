#include <iostream>
#include "lr3.hpp"

using namespace std;
void Calendar::proverca_dat(int &_day, int &_month, int &_year){
        if (_month==2){
            if(_year%4==0 && (_year%100!=0 or _year%400==0)){
                if(_day>29){
                    cout<<"Day ("<<_day<<") bolshe dopustimogo znacheniy (29), on bil izmenen do maximalnogo dopustimogo (29)"<<endl;
                    _day=29;
                }
            }
            else {
                if(_day>28){
                    cout<<"Day ("<<_day<<") bolshe dopustimogo znacheniy (28), on bil izmenen do maximalnogo dopustimogo (28)"<<endl;
                    _day=28;
                }
            }
        }
        else if (_month%2==0){
            if (_day>30){
                cout<<"Data: "<<_day<<"."<<_month<<"."<<_year<<" !day ("<<_day<<") bolshe dopustimogo znacheniy(30), on bil izmenen do maximalnogo dopustimogo (30)";
                _day=30;
                cout<<" data: "<<_day<<"."<<_month<<"."<<_year<<endl<<endl;
            }
        }
        else if (_month%2!=0){
            if (_day>31){
                cout<<"Data: "<<_day<<"."<<_month<<"."<<_year<<" !day ("<<_day<<") bolshe dopustimogo znacheniy (31), on bil izmenen do maximalnogo dopustimogo (31)";
                _day=31;
                cout<<" data: "<<_day<<"."<<_month<<"."<<_year<<endl<<endl;
            }
        }
        if (_day<0){
            cout<<"Data: "<<_day<<"."<<_month<<"."<<_year<<" !day("<<_day<<") menishe dopustimogo znacheniy (1), on bil izmenen do minimalnogo dopustimogo (1)";
            _day=1;
            cout<<" data: "<<_day<<"."<<_month<<"."<<_year<<endl<<endl;
        }
        if (_month<0){
            cout<<"Data: "<<_day<<"."<<_month<<"."<<_year<<" !month("<<_month<<") menishe dopustimogo znacheniy(0), on bil izmenen do minimalnogo dopustimogo (1)";
            _month=1;
            cout<<" data: "<<_day<<"."<<_month<<"."<<_year<<endl<<endl;
        }
        else if (_month>12){
            cout<<"Data: "<<_day<<"."<<_month<<"."<<_year<<" !month("<<_month<<") bolshe dopustimogo znacheniy(12), on bil izmenen do maximalnogo dopustimogo (12)";
            _month=12;
            cout<<" data: "<<_day<<"."<<_month<<"."<<_year<<endl<<endl;
        }

    }
    
string Calendar::convert_month(int month){
    switch (month)
    {
    case 1:
        return "january";
    case 2:
        return "february";
    case 3:
        return "march";
    case 4:
        return "april";
    case 5:
        return "may";
    case 6: 
        return "june";
    case 7:
        return "july";
    case 8:
        return "august";
    case 9:
        return "september";
    case 10:
        return "october";
    case 11:
        return "november";
    case 12:
        return "december";
    default:
        return "january";
    }
}

void Calendar::print_cal(){
    cout<<"Data: "<<Calendar::day<<"."<<Calendar::month<<"."<<Calendar::year<<endl<<endl;
}
void Calendar::print_full_cal(){
    cout<<"Data full: "<<Calendar::day<<" "<<Calendar::convert_month(Calendar::month)<<" "<<Calendar::year<<endl<<endl;
}
void Calendar::reload_dat(int _day, int _month, int _year){
    Calendar::proverca_dat(_day, _month, _year);
    day=_day;
    month=_month;
    year=_year;
}

int main(){
Calendar cal(29, 2, 2025);
Calendar cal1 (-10, 100, 2000);
cal.print_cal();
cal1.print_full_cal();
cal.reload_dat(-100,1000,2012);
cal1.reload_dat(1,1,1999);
if (cal<cal1){
    cout<<"Pervay data menshe vtoroi"<<endl<<endl;
}
else{
    cout<<"Pervay data ne menshe vtoroi"<<endl<<endl;
}
if(cal>cal1){
    cout<<"Pervay data bolshe vtoroi"<<endl<<endl;
}
else {
    cout<<"Pervay data ne bolshe vtoroi"<<endl<<endl;
}
cal.print_cal();
cal1.print_cal();
Calendar cal2 = cal-cal1;
cout<<"cal - cal1:"<<endl;
cal2.print_cal();
}