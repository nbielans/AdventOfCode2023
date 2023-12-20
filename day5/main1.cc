#include <iostream>
#include <fstream>
#include <string>
#include <list>

#define INPUT_FILE "input.txt"

struct almanacTriple {
    long src;
    long dest;
    long range;
};

bool isNum(char c) {
    return (c>='0' && c<='9');
}

long getNum(const std::string& line, int& i) {
    long num = 0;
    while(isNum(line[i])) {
        num *= 10;
        num += line[i]-'0';
        i++;
    }

    while(line[i]==' ') {
        i++;
    }

    return num;
}

long getDestination(const std::list<almanacTriple>& map, long entry) {
    for(auto tri: map) {
        if((tri.src<=entry) && (entry<(tri.src+tri.range))) {
            return tri.dest + (entry - tri.src);
        }
    }

    return entry;
}

void setEntries(std::list<long>& entries, std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    int i = 0;

    while(!isNum(line[i])) { i++; }

    while(i < line.size()) {
        entries.push_back(getNum(line, i));
    }
}

almanacTriple getTriple(const std::string& line) {
    almanacTriple tri;
    int i = 0;

    tri.dest = getNum(line, i);
    tri.src = getNum(line, i);
    tri.range = getNum(line, i);

    return tri;
}

void setMap(std::list<almanacTriple>& map, std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    int i = 0;

    while(!isNum(line[0])) {
        std::getline(file, line);
    }

    map.clear();
    while(isNum(line[0])) {
        map.push_back(getTriple(line));
        std::getline(file, line);
    }
}

void convert(std::list<long>& entries, const std::list<almanacTriple>& map) {
    for(auto& entry: entries) {
        entry = getDestination(map, entry);
    }
}

int main(void) {
    long minLocation;
    std::list<long> entries;
    std::list<almanacTriple> map;

    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }

    setEntries(entries, file);

    while(!file.eof()) {
        setMap(map, file);
        convert(entries, map);
    }

    minLocation = entries.front();
    for(const auto& entry: entries) {
        if(entry < minLocation) {
            minLocation = entry;
        }
    }

    file.close();
    std::cout << "min location: " << minLocation << std::endl;
    return 0;
}