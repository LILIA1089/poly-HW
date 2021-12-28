#include <iostream>
#include <fstream>
#include <cmath>

enum pointType { LEFTMOST, RIGHTMOST };

struct Point {
    int x;
    int y;

   void printPoint(pointType type) {

       if (type == LEFTMOST) {
           std::cout << "Leftmost: " << this->x << " " << this->y << std::endl;
       }

       if (type == RIGHTMOST) {
           std::cout << "Rightmost: " << this->x << " " << this->y << std::endl;
       }
    }
};


void findPoints(Point& fr, Point& fl, const std::string& filename) {
    std::ifstream infile(filename);

    std::pair<int, int> vectorn;

    double min_dist_r = 1;
    double min_dist_l = 1;

    infile >> vectorn.first >> vectorn.second;

    int x, y;

    while (infile >> x >> y)
    {
        if (x == 0 && y == 0) {
            continue;
        }

        double cos = (vectorn.first * x + vectorn.second * y) / (sqrt(x * x + y * y) *
            sqrt(vectorn.first * vectorn.first + vectorn.second * vectorn.second));


        cos = round(cos * 1E10) / 1E10;
        if (cos - min_dist_l <= 0 && (vectorn.first * y - vectorn.second * x) > 0)
        {
            min_dist_l = cos;
            fr.x = x;
            fr.y = y;

        }
        if (cos - min_dist_r <= 0 && (vectorn.first * y - vectorn.second * x) <= 0)
        {
            min_dist_r = cos;
            fl.x = x;
            fl.y = y;
        }
    }


    infile.close();
}


int main() 
{
    Point fr = { 0,0 };
    Point fl = { 0,0 };

    findPoints(fr, fl, "in.txt");

    fr.printPoint(LEFTMOST);
    fl.printPoint(RIGHTMOST);

    return 0;
}
