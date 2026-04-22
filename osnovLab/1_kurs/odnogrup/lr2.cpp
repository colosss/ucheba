#include <iostream>
using namespace std;

int main() {
    double x, y;

    setlocale(LC_ALL, "");
    cout << "Введите координату x: ";
    cin >> x;
    cout << "Введите координату y: ";
    cin >> y;

    if ((x * x + y * y) <= 1 && (x <= 0 || y >= 0)) {
        cout << "Точка попадает в заштрихованную область.\n";
    }
    else {
        cout << "Точка не попадает в заштрихованную область.\n";
    }

    return 0;
}