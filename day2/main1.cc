#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_FILE "input.txt"

#define BLUE_COUNT 14
#define GREEN_COUNT 13
#define RED_COUNT 12

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

bool invalidCount(int cnt, std::string Color) {
    if(Color=="blue") {
        return cnt > BLUE_COUNT;
    }
    if(Color=="green") {
        return cnt > GREEN_COUNT;
    }
    if(Color=="red") {
        return cnt > RED_COUNT;
    }
    return 0;
}

// Game 1: 7 red, 14 blue; 2 blue, 3 red, 3 green; 4 green, 12 blue, 15 red; 3 green, 12 blue, 3 red; 11 red, 2 green
int assess_game(char line[], int l) {
    int cnt = 0;
    std::string Color;
    // get start
    int i = (8 + (l>=10) + (l>=100)) - 2; // l is current line to account for spacing

    do {
        do {
            i+=2;
            cnt = getNum(line, i);
            i += 1;
            Color = getColor(line, i);
            if(invalidCount(cnt, Color)) {
                return 0;
            }
        } while(line[i]==',');
    } while(line[i]==';');

    // game is valid
    return l;
}

int main(void) {
    int sum_valid = 0;
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
        sum_valid += assess_game(line, l++);
        file.getline(line, 256);
    }

    file.close();
    std::cout << "Valid ID Sum: " << sum_valid << std::endl;
    return 0;
}