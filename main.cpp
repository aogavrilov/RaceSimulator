#include <iostream>
#include <vector>
using namespace std;
class Vehicle{
    float speed;
protected: Vehicle(float speed) : speed(speed){}
};
class AirTransport : Vehicle{
    vector<float> delta_percent;
    int count_of_relaxstops = 0;
public:
    AirTransport(float speed, vector<float> percents) : Vehicle(speed), delta_percent(percents){}

};
class LandTransport : Vehicle{
    float time_to_relax;
    vector<float> relaxing_time;
    int count_of_relaxstops = 0;
public:
    LandTransport(float speed, float time_to_relax, vector<float> relaxing_time) : Vehicle(speed),
    time_to_relax(time_to_relax), relaxing_time(relaxing_time){}


};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
