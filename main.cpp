#include <iostream>
#include <vector>
using namespace std;
class Vehicle{
protected:
    float speed;
    Vehicle(float speed) : speed(speed){}
    float Calculate=0;
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

public:
    LandTransport(float speed, float time_to_relax, vector<float> relaxing_time) : Vehicle(speed),
    time_to_relax(time_to_relax), relaxing_time(relaxing_time){}
    float Calculate(float distance){
        if(distance > speed * time_to_relax){
            float result_time = 0;
            float covered_distance = 0;
            int count_of_relaxstops = 0;
            while(covered_distance < distance){
                if(distance - covered_distance <= speed * time_to_relax){
                    result_time += (distance - covered_distance) / speed;
                    return result_time;
                }
                else{
                    covered_distance += speed * time_to_relax;
                    result_time += time_to_relax;
                    count_of_relaxstops++;
                    if(count_of_relaxstops < relaxing_time.size()){
                        result_time += relaxing_time[count_of_relaxstops - 1];
                    }
                    else{
                        result_time += relaxing_time[relaxing_time.size() - 1];
                    }
                }
            }
        }
        else{
            return distance / speed;
        }
    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
