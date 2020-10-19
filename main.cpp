#include <iostream>
#include <vector>
using namespace std;
class Vehicle{
protected:
    float speed;
    size_t type;
    string name;
    Vehicle(float speed, string name) : speed(speed), name(name){}
   // float Calculate = 0;
public:
    size_t  GetType(){
        return type;
    }
    string GetName(){
        return name;
    }

    virtual float Calculate(float dist) = 0;
};
class AirTransport : public Vehicle{
    vector<float> delta_percent;
    int count_of_relaxstops = 0;
public:
    AirTransport(float speed, string name, vector<float> percents) : Vehicle(speed, name), delta_percent(percents){
        type = 1;
    }
    float GetDistancePercent(int count, vector<float> percents){
        if(count >= percents.size()){
            return (1 - percents[percents.size() - 1]/100);
        }
        else{
            return (1 - percents[count]/100);
        }
        // 1, 2,3
    }
    float Calculate(float distance){
        if(distance > 1000){
            float result_time = 0;
            float covered_distance = 0;
            int count_of_relaxstops = 0;
            while(covered_distance < distance){
                //cout << covered_distance << " " << distance << endl;
                if(distance - covered_distance <= 1000){

                    result_time += (distance - covered_distance) * GetDistancePercent(count_of_relaxstops, delta_percent) / speed;
                    return result_time;
                }
                else{
                    covered_distance += 1000;
                    result_time += (1000 * GetDistancePercent(count_of_relaxstops, delta_percent) / speed);
                    count_of_relaxstops++;
                }
            }
        }
        else{
            return distance / speed;
        }
        return 0;
    }
};
class LandTransport : public Vehicle{
    float time_to_relax;
    vector<float> relaxing_time;

public:
    LandTransport(float speed, string name, float time_to_relax, vector<float> relaxing_time) : Vehicle(speed, name),
    time_to_relax(time_to_relax), relaxing_time(relaxing_time){
        type = 2;
    }
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
        return 0;
    }


};
class MyException : exception{
private:
    string m_error;
public:
    MyException(string reason) : m_error(reason){}
    const char* getError() { return m_error.c_str(); }
};
template <class T>
class Race{

    vector<T> air;
public:
    Race<T>(vector<T> air) : air(air){}

    T* Calculate(int dist){
        int winner_time = air.begin()->Calculate(dist);
        T* winner_transport = air.begin().base();
        for(auto iter = (++air.begin()); iter != air.end(); iter++){
            float temp = iter->Calculate(dist);
            if(temp < winner_time){
                winner_time = temp;
                winner_transport = iter.base();
            }
        }
        return winner_transport;

    }


};
class MixedRace{
    vector<LandTransport> landveh;
    vector<AirTransport> air;
    size_t type;
public:
    MixedRace(vector<LandTransport> landveh, vector<AirTransport> air ) : air(air), landveh(landveh){}
    Vehicle* Calculate(int dist){
        if(air.size() == 0)
            throw MyException("Vector of air vehicle mustn't be empty");
        if(landveh.size() == 0)
            throw MyException("Vector of land vehicle mustn't be empty");
        int winner_air_time = air.begin()->Calculate(dist);
        AirTransport* winner_air_transport = air.begin().base();
        for(auto iter = (++air.begin()); iter != air.end(); iter++){
            float temp = iter->Calculate(dist);
            if(temp < winner_air_time){
                winner_air_time = temp;
                winner_air_transport = iter.base();
            }
        }

        int winner_land_time = landveh.begin()->Calculate(dist);
        LandTransport* winner_land_transport = landveh.begin().base();
        for(auto iter = (++landveh.begin()); iter != landveh.end(); iter++){
            float temp = iter->Calculate(dist);
            if(temp < winner_land_time){
                winner_land_time = temp;
                winner_land_transport = iter.base();
            }
        }
        Vehicle* winner_transport;
        if(winner_air_time < winner_land_time)
            winner_transport = winner_air_transport;
        else
            winner_transport = winner_land_transport;
        return winner_transport;
    }
};


int main() {
    LandTransport bactrian_camel = LandTransport(10, "bactrian camel", 30, {5, 8});
    LandTransport speed_camel = LandTransport(40, "speed camel", 10, {5, 6.5, 8});
    LandTransport centaur = LandTransport(15, "centaur", 8, {2});
    LandTransport running_boots = LandTransport(6, "running boots", 60, {10, 5});

    AirTransport magic_carpet = AirTransport(10, "magic carpet", {0, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 5});
    AirTransport mortar = AirTransport(8, "mortar", {6});


    AirTransport broom = AirTransport(20, "broom", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});



    AirTransport testveh = AirTransport(200, "test vehicle",  {0});
    Race<AirTransport> race = Race<AirTransport>({magic_carpet, mortar, broom, testveh});

    Race<LandTransport> race2 = Race<LandTransport>({bactrian_camel, speed_camel, centaur, running_boots});
    MixedRace race3 = MixedRace({bactrian_camel, speed_camel, centaur, running_boots}, {magic_carpet, mortar, broom});
    cout << race.Calculate(1000)->GetName();
    //cout << broom.Calculate(2000);
    //cout << race2.Calculate(1000)->Calculate(1000);

    return 0;
}
