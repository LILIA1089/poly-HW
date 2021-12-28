#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double G = -9.8;

std::vector<std::pair<double, double>> Walls;
std::pair<double, double> velocity;

int getInterval(const std::string& filename) {

    double h;
    double x = 0;

    int interval = 0;
    int fall_interval;
    int size = 0;

    std::ifstream infile(filename);
    infile >> h;
    infile >> velocity.first >> velocity.second;

    while (true) {
        int target = 0; 
        
        if (velocity.first < 0) {
            target = 0;
            return target;
        }

        if (velocity.first > 0) {
            target = interval;
        }

        if (target > size - 1) {
            double wall_x, wall_h;
            if (infile >> wall_x >> wall_h) {
                Walls.push_back(std::make_pair(wall_x, wall_h));
                size++;
            }

            else {
                return size;
            }

        }

        double t = fabs((x - Walls[target].first) / velocity.first);

        x = Walls[target].first;
        h = h + velocity.second * t + (G * t * t) / 2.0;
        velocity.second = velocity.second + G * t;

        if (h <= 0) {
            return interval;
        }

        if (h > Walls[target].second) {
            if (velocity.first < 0) {
                interval--;
            }

            if (velocity.first > 0) {
                interval++;
            }
        }

        else {
            velocity.first =velocity.first* (-1);
        }
    }
    
}


int main(int argc, char** argv) {
    
    if (argc == 2) {
        std::cout << getInterval(argv[1]) << std::endl;
    }

    return 0;
}
