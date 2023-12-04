#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_FILE "input.txt"

bool isNum(char c) {
    return (c>='0' && c<='9');
}

int rem_num(std::string& line, int i) {
    int num = 0;
    while(i>=0 && isNum(line[i])) { i--; }
    i++;
    while(i<line.size() && isNum(line[i])) {
        num *= 10;
        num += line[i] - '0';
        line[i] = '.';
        i++;
    }
    return num;
}

long compare_to_another(const std::string& another, std::string& line) {
    long cnt = 0;

    for(int i=0; i<line.size(); i++) {
        if(another[i] != '.' && !(isNum(another[i]))) {
            if(i>0 && isNum(line[i-1])) {
                cnt += rem_num(line, i-1);
            }
            if(i<(line.size()-1) && isNum(line[i+1])) {
                cnt += rem_num(line, i+1);
            }
            if(isNum(line[i])) {
                cnt += rem_num(line, i);
            }
        }
    }

    return cnt;
}

long compare_to_self(std::string& line) {
    long cnt = 0;

    for(int i=0; i<line.size(); i++) {
        if(line[i] != '.' && !(isNum(line[i]))) {
            if(i>0 && isNum(line[i-1])) {
                cnt += rem_num(line, i-1);
            }
            if(i<(line.size()-1) && isNum(line[i+1])) {
                cnt += rem_num(line, i+1);
            }
        }
    }

    return cnt;
}

int main(void) {
    long sum_part_nums = 0;
    std::vector<std::string> lines = { "\0", "\0", "\0" };
    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }

    std::getline(file, lines[2]);
    
    // performing problem
    do {
        lines[0] = lines[1];
        lines[1] = lines[2];
        std::getline(file, lines[2]);

        sum_part_nums += compare_to_self(lines[1]);
        if(lines[0][0] != '\0') {
            sum_part_nums += compare_to_another(lines[0], lines[1]);
        }
        if(lines[2][0] != '\0') {
            sum_part_nums += compare_to_another(lines[2], lines[1]);
        }
    } while(lines[1][0] != '\0');


    file.close();
    std::cout << "Parts Sum: " << sum_part_nums << std::endl;
    return 0;
}
