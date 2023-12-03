#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_FILE "input.txt"

#define BLUE_IDX 0
#define GREEN_IDX 1
#define RED_IDX 2

bool match(std::string goal, char in[], int i) {
    for(int j=0; goal[j]!='\0'; j++) {
        if(goal[j] != in[i+j]) {
            return 0;
        }
    }
    return 1;
}

int getNum(char line[], int& i) {
    int sum = 0;
    while(line[i]>='0' && line[i]<='9') {
        sum *= 10;
        sum += line[i] - '0';
        i++;
    }

    return sum;
}

std::string getColor(char line[], int& i) {
    if(line[i] == 'b') {
        i += 4;
        return "blue";
    }
    if(line[i] == 'r') {
        i += 3;
        return "red";
    }
    if(line[i] == 'g') {
        i += 5;
        return "green";
    }

    return "";
}

void setMinCount(int cnt, std::string Color, std::vector<int>& min_cnt) {
    int idx = -1;
    if(Color=="blue") {
        idx = BLUE_IDX;
    }
    if(Color=="green") {
        idx = GREEN_IDX;
    }
    if(Color=="red") {
        idx = RED_IDX;
    }

    if(idx<0) return;

    min_cnt[idx] = (cnt>min_cnt[idx]) ? cnt : min_cnt[idx];

    return;
}

int assess_game(char line[], int l) {
    int cnt = 0;
    std::string Color;
    std::vector<int> min_cnt = {0,0,0};
    // get start
    int i = (8 + (l>=10) + (l>=100)) - 2; // l is current line to account for spacing

    do {
        do {
            i+=2;
            cnt = getNum(line, i);
            i += 1;
            Color = getColor(line, i);
            setMinCount(cnt, Color, min_cnt);
        } while(line[i]==',');
    } while(line[i]==';');

    // game is valid
    return min_cnt[0]*min_cnt[1]*min_cnt[2];
}

int main(void) {
    long sum_powers = 0;
    int l = 1;
    int cnt = 100;
    char line[256];
    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }
    file.getline(line, 256);
    while(line[0] != '\0') {
        sum_powers += assess_game(line, l++);
        file.getline(line, 256);
    }

    file.close();
    std::cout << "Min Powers Sum: " << sum_powers << std::endl;
    return 0;
}