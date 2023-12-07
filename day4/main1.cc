#include <iostream>
#include <fstream>
#include <vector>
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

bool isWinner(const std::vector<long>& goal_nums, int num) {
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
    std::vector<long> goal_nums;

    // set goal_nums
    while(line[i] != '|') {
        goal_nums.push_back(get_num(line, i));
    }
    while(!isNum(line[++i])) {}

    // find winning nums
    while(i < line.size()) {
        winnings += (int) isWinner(goal_nums, get_num(line, i));
    }

    if(winnings) {
        return 1<<(winnings-1);
    }
    return 0;
}

int main(void) {
    long sum_winnings = 0;
    std::string line;
    std::ifstream file;

    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }
    std::getline(file, line);

    do {
        sum_winnings += get_winnings(line);
        std::getline(file, line);
    } while(line[0] != '\0');

    std::cout << "Winnings: " << sum_winnings << std::endl;
    return 0;
}