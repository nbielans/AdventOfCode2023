#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_FILE "calibrationFile.txt" 

bool match(std::string goal, char in[], int i) {
    for(int j=0; goal[j]!='\0'; j++) {
        if(goal[j] != in[i+j]) {
            return 0;
        }
    }
    return 1;
}

int isNum(char line[], int i) {
    char c = line[i];

    if((c>='0') && (c<='9')) {
        return c-'0';
    }

    // problem 2
    std::vector<std::string> nums = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    if(c!='z' && c!='o' && c!='t' && c!='f' && c!='s' && c!='e' && c!='n') {
        return -1;
    }

    for(int idx = 0; idx<10; idx++) {
        if(match(nums.at(idx), line, i)) {
            return idx;
        }
    }
    
    return -1;
}

int get_val(char line[]) {
    int first = -1;
    int last = -1;
    int i=0;
    int num;

    while(line[i] != '\0') {
        num = isNum(line, i);
        if(first==-1 && num!=-1) {
            first = num;
        }
        if(num!=-1) {
            last = num;
        }
        i++;
    }

    return 10*first + last;
}

int main(void) {
    int sum = 0;
    char line[64];
    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }
    
    file.getline(line, 64);
    while(line[0] != '\0') {
        sum += get_val(line);
        file.getline(line, 64);
    }

    


    file.close();
    std::cout << "Calibration Sum: " << sum << std::endl;
    return 0;
}