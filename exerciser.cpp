#include "exerciser.h"

void exercise(connection *C) {
    query1(C, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << endl;
    query1(C, 0, 35, 40, 0, 0, 0, 1, 5, 20, 0, 0, 0, 1, 0, 10, 0, 0, 0);
    cout << endl;
    query1(C, 1, 0, 100, 1, 0, 100, 1, 0, 100, 1, 0, 100, 1, 0, 100, 1, 0, 100);
    cout << endl;
    query1(C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << endl;
    cout << endl;
    query2(C, "Gold");
    cout << endl;
    query2(C, "LightBlue");
    cout << endl;
    query2(C, "Maroon");
    cout << endl;
    query2(C, "Black");
    cout << endl;
    cout << endl;
    query3(C, "Duke");
    cout << endl;
    query3(C, "UNC");
    cout << endl;
    query3(C, "NCSU");
    cout << endl;
    query3(C, "WakeForest");
    cout << endl;
    cout << endl;
    query4(C, "NC", "DarkBlue");
    cout << endl;
    query4(C, "NC", "LightBlue");
    cout << endl;
    query4(C, "NC", "Gold");
    cout << endl;
    query4(C, "NC", "Red");
    cout << endl;
    cout << endl;
    query5(C, 10);
    cout << endl;
    query5(C, 9);
    cout << endl;
    query5(C, 5);
    cout << endl;
    query5(C, 0);
    cout << endl;
}
