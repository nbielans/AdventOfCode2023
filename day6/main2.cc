#include <iostream>
#include <fstream>
#include <list>
#include <string>

#define INPUT_FILE "input.txt"

struct Race {
    long time;
    long dist;
};

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

void updateNum(const std::string& line, int& i, long& val) {
    while(isNum(line[i])) {
        val*=10;
        val+= line[i]-'0';
        i++;
    }
}

void getRaces(std::ifstream& file, std::list<Race>& races) {
    std::string times;
    std::string dists;
    Race temp;
    std::getline(file, times);
    std::getline(file, dists);
    int i = 0;
    int j = 0;

    temp.time = 0;
    temp.dist = 0;
    while(i < times.size()) {
        while(!isNum(times[i])) { i++; }
        while(!isNum(dists[j])) { j++; }

        updateNum(times, i, temp.time);
        updateNum(dists, j, temp.dist);
    }
    races.push_back(std::move(temp));
    std::cout << temp.time << ' ' << temp.dist << std::endl;
}

int getMargin(Race race) {
    int margin = 0;
    long dist;

    for(int hold = 1; hold<race.time; hold++) {
        dist = (race.time - hold) * hold;
        if(dist > race.dist) {
            margin++;
        }
    }

    return margin;
}

int main(void) {
    std::list<Race> races;
    
    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }

    getRaces(file, races);

    int margin = 1;
    for(const auto& race: races) {
        margin *= getMargin(race);
    }

    std::cout << "Margin: " << margin << std::endl;
    return 0;
}