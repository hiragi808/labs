//
// Created by macbook on 13.04.26.
//
#include<sstream>
#include "point.h"

#include <iostream>
point::point(int xs, int ys) {
    x=xs;
    y=ys;
}

std::string point::printp() {
    using namespace std;
    string r;
    string xs = to_string(x);
    string ys = to_string(y);
    r="{"+xs+";"+ys+"}";
    return r;
}
point point::createpoint() {
    using namespace std;
    int x,y;
    cout<<"Enter X: ";
    while (!(cin>>x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Ошибка!";
    }
    cout<<"Enter Y: ";
    while (!(cin>>y)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Ошибка!";
    }
    point p(x,y);
    return p;
}
line::line(std::vector<point*> pts) {
    points=pts;
}
line line::createCustom() {
    int count;
    std::cout << "Сколько точек будет в вашей ломаной? ";
    while (!(std::cin >> count) || count < 0) {
        std::cout << "Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    std::vector<point*> newPoints;
    for (int i = 0; i < count; ++i) {
        std::cout << "Точка #" << i + 1 << ":" << std::endl;
        // Создаем точку в динамической памяти, чтобы она жила долго
        point* p = new point(point::createpoint());
        newPoints.push_back(p);
    }
    return newPoints;
}
void line::printL() const {
    std::cout << "Линия [";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i]->printp() << (i == points.size() - 1 ? "" : ",");
    }
    std::cout << "]" << std::endl;
}
void line::add(std::vector<point*> p) {
    for (auto c:p) {
        points.push_back(c);
    }
}
void line::addcustom() {
    using namespace std;
    vector<point*> p;
    int s;
    while (!(cin>>s)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Ошибка!";
    }
    for (int i=0;i<=s;i++) {
        point* pi= new point(point::createpoint());
        p.push_back(pi);
    }
    add(p);
}

double line::getLength() const {
     double totalLength = 0;
     for (size_t i = 0; i < points.size() - 1; ++i) {
         double dx = points[i+1]->getx() - points[i]->getx();
         double dy = points[i+1]->gety() - points[i]->getx();
         totalLength += std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
     }
    return totalLength;
}
void t3() {
    using namespace std;
    line micurva =line::createCustom();
    micurva.printL();


    point p1(1, 5);
    point p2(2, 8);
    point p3(5, 3);

    // Собираем первую ломаную из адресов этих точек
    line line1({&p1, &p2, &p3});

    // Создаем новые точки для середины
    point pMid1(2, -5);
    point pMid2(4, -8);

    // Собираем вторую ломаную:
    // начало (&p1) и конец (&p3) берем у первой ломаной
    line line2({&p1, &pMid1, &pMid2, &p3});

    // Вывод результатов
    std::cout << "Состояние до сдвига:" << std::endl;
    line1.printL();
    line2.printL();

    std::cout << "Сдвигаем начало p1 на {10; 10}..." << std::endl;
    p1.setx(10);
    p1.sety(10);

    line1.printL();
    line2.printL();
}

void t4() {
    using namespace std;

    point p1(1, 5);
    point p2(2, 8);
    point p3(5, 3);

    // Собираем первую ломаную из адресов этих точек
    line line2({&p1, &p2, &p3});
    point p4(5, 15);
    point p5(8, 10);
    line2.printL();
    cout << "Длинна:"<<line2.getLength()<<endl;
    line2.add({&p4,&p5});
    line2.printL();
    cout << "Длинна:"<<line2.getLength()<<endl;


    line line1 = line::createCustom();
    line1.printL();
    cout << "Длинна:"<<line1.getLength()<<endl;
    line1.addcustom();
    line1.printL();
    cout << "Длинна:"<<line1.getLength()<<endl;


}