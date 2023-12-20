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

struct entryRange {
    long src;
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

long getDestination(const std::list<almanacTriple>& map, entryRange entry) {
    for(auto tri: map) {
        if((tri.src<=entry.src) && (entry.src<(tri.src+tri.range))) {
            return tri.dest + (entry.src - tri.src);
        }
    }

    return entry.src;
}

void setEntriesRanges(std::list<entryRange>& entries, std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    entryRange temp;
    int i = 0;

    while(!isNum(line[i])) { i++; }

    while(i < line.size()) {
        temp.src = getNum(line, i);
        temp.range = getNum(line, i);
        entries.push_back(std::move(temp));
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

void removeOverlaps(std::list<entryRange>& entries, const std::list<almanacTriple>& map) {
    for(const almanacTriple& tri: map) {
        for(auto it = entries.begin(); it!=entries.end(); it++) {
            if(((*it).src < tri.src) && ((*it).src+(*it).range > tri.src)) {
                entryRange temp;
                temp.src = (*it).src;
                temp.range = tri.src - temp.src;

                entries.insert(it, temp);
                (*it).src = tri.src;
                (*it).range -= temp.range;
            }
        }
    }
}

void convert(std::list<entryRange>& entries, const std::list<almanacTriple>& map) {
    removeOverlaps(entries, map);
    
    for(auto& entry: entries) {
        entry.src = getDestination(map, entry);
    }
}

int main(void) {
    long minLocation;
    std::list<entryRange> entries;
    std::list<almanacTriple> map;

    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }

    setEntriesRanges(entries, file);

    while(!file.eof()) {
        setMap(map, file);
        convert(entries, map);
    }

    minLocation = entries.front().src;
    for(const auto& entry: entries) {
        if(entry.src < minLocation) {
            minLocation = entry.src;
        }
    }

    file.close();
    std::cout << "min location: " << minLocation << std::endl;
    return 0;
}