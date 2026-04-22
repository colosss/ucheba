#include <iostream>

using namespace std;

class Calendar{

private:
int day;
int month;
int year;

public:
    
    Calendar(){
        day=1;
        month=1;
        year=1901;
    }
    Calendar(int _day, int _month, int _year){
        proverca_dat(_day, _month, _year);
        day=_day;
        month=_month;
        year=_year;
    }
    ~Calendar(){
        cout<<"Destroi Calendar"<<endl;
    }
    
    void proverca_dat(int &_day, int &_month, int &_year);
    void print_cal();
    void print_full_cal();
    string convert_month(int _month);
    void reload_dat(int _day, int _month, int _year);
    friend bool operator<(const Calendar &cal1, const Calendar &cal2);
    friend bool operator>(const Calendar &cal1, const Calendar &cal2);
    Calendar operator-(const Calendar &other)const;

};
bool operator<(const Calendar &cal1, const Calendar &cal2){
    if (cal1.year<cal2.year)return true;
    else if (cal1.year==cal2.year){
        if (cal1.month<cal2.month) return true;
        else if (cal1.month==cal2.month){
            if (cal1.day<cal2.day) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
bool operator>(const Calendar &cal1, const Calendar &cal2){
    if (cal1.year>cal2.year)return true;
    else if (cal1.year==cal2.year){
        if (cal1.month>cal2.month) return true;
        else if (cal1.month==cal2.month){
            if (cal1.day>cal2.day) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
Calendar Calendar::operator-(const Calendar &other)const{
    Calendar result(*this);
    result.year -=other.year;
    result.month -=other.month;

    if(result.month <0){
        result.month+=12;
        result.year--;
    }
    result.day -=other.day;
    if (result.day<=0){
        result.month--;
        if(result.month<0){
            result.month =12;
            result.year--;
        }
        if (result.month==2){
        if(result.year%4==0 && (result.year%100!=0 or result.year%400==0)){
            result.day+=29;
        }
        else {
            result.day+=28;
        }
    }
    else if (result.month%2==0){
        result.day+=30;
    }
    else if (result.month%2!=0){
        result.day+=31;
    }
    }
    return result;
}