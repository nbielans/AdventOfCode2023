#include <iostream>
#include <fstream>
#include <list>
#include <string>

#define INPUT_FILE "input.txt"

int set_i(std::string line) {
    int i = 0;
    while(line[i] != ':') { i++; }
    return ++i;
}

bool isNum(char c) {
    return (c>='0' && c<='9');
}

int get_num(const std::string& line, int& i) {
    int num = 0;
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

bool isWinner(const std::list<long>& goal_nums, int num) {
    for(auto i: goal_nums) {
        if(i==num) {
            return true;
        }
    }

    return false;
}

long get_winnings(const std::string& line) {
    long winnings = 0;
    int i = set_i(line);
    int curr_num;
    std::list<long> goal_nums;

    // set goal_nums
    while(line[i] != '|') {
        goal_nums.push_back(get_num(line, i));
    }
    while(!isNum(line[++i])) {}

    // find winning nums
    while(i < line.size()) {
        winnings += (int) isWinner(goal_nums, get_num(line, i));
    }

    return winnings;
}

void append_copies(std::list<int>& future_copies, int instances, int winnings) {
    while(future_copies.size()<winnings) {
        future_copies.push_back(1);
    }

    std::list<int>::iterator it = future_copies.begin();
    while(winnings--) {
        *it += instances;
        it++;
    }
}

int main(void) {
    long num_cards = 0;
    int curr_instances;
    int curr_winnings;
    std::list<int> future_copies = { 1 };
    std::string line;
    std::ifstream file;

    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }
    std::getline(file, line);

    // calculate
    do {
        if(future_copies.size()) {
            curr_instances = future_copies.front();
            future_copies.pop_front();
        } else {
            curr_instances = 1;
        } 
        num_cards += curr_instances;

        curr_winnings = get_winnings(line);

        append_copies(future_copies, curr_instances, curr_winnings);
        std::getline(file, line);
    } while(line[0] != '\0');

    std::cout << "Num_cards: " << num_cards << std::endl;
    return 0;
}