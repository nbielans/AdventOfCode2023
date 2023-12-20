#include <iostream>
#include <fstream>
#include <list>
#include <string>

#define INPUT_FILE "input.txt"

struct Race {
    int time;
    int dist;
};

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

int getNum(const std::string& line, int& i) {
    int val = 0;

    while(isNum(line[i])) {
        val*=10;
        val+= line[i]-'0';
        i++;
    }

    return val;
}

void getRaces(std::ifstream& file, std::list<Race>& races) {
    std::string times;
    std::string dists;
    Race temp;
    std::getline(file, times);
    std::getline(file, dists);
    int i = 0;
    int j = 0;

    while(i < times.size()) {
        while(!isNum(times[i])) { i++; }
        while(!isNum(dists[j])) { j++; }

        temp.time = getNum(times, i);
        temp.dist = getNum(dists, j);

        races.push_back(std::move(temp));
    }
}

int getMargin(Race race) {
    int margin = 0;
    int dist;

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