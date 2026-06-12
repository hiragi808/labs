//
// Created by macbook on 13.04.26.
//

#ifndef LAB15_POINT_H
#define LAB15_POINT_H


class point {
private:
    int x, y;
    public:
    point(int x,int y);
    std::string printp();
    static point createpoint();
    int getx(){return x;}
    int gety(){return y;}
    void setx(int v){ x = v; }
    void sety(int v){ y = v; }
};
class line {
private:
    std::vector<point*> points;
public:
    line(std::vector<point*> pts);
    static line createCustom();
     void add(std::vector<point*> p);
    void addcustom();
    void printL() const;
    double getLength() const;
};
void t3();
void t4();

#endif //LAB15_POINT_H