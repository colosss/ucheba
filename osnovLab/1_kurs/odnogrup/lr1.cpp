#include <iostream>
#include <cmath>

#define   pi 3.14159265358979323846
using namespace std;

double toRadians(double degrees) {
    return degrees * pi/ 180.0; 
}

double znachenie_z1(double a, double b) {
    return pow(cos(a), 4) + pow(sin(b), 2) + 0.25 * pow(sin(2 * a), 2) - 1;
}

double znachenie_z2(double a, double b) {
    return sin(b + a) * sin(b - a);
}

int main() {
    setlocale(LC_ALL, "Rus");
    double a_degrees, b_degrees;
    double a_radians, b_radians;
    double z1, z2;

    cout << "Введите значение a в градусах: " << endl;
    cin >> a_degrees;
    cout << "Введите значение b в градусах: " << endl;
    cin >> b_degrees;

    a_radians = toRadians(a_degrees);
    b_radians = toRadians(b_degrees);

    z1 = znachenie_z1(a_radians, b_radians);
    z2 = znachenie_z2(a_radians, b_radians);

    cout << "Значение 1-го выражения:\tz1 = " << z1 << endl;
    cout << "Значение 2-го выражения:\tz2 = " << z2 << endl;

    return 0;
}