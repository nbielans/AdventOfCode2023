#include <iostream>
#include <fstream>
#include <list>

#define INPUT_FILE "calibrationFile.txt" 

bool isNum(char line[], int i) {
    char c = line[i];

    if((c>='0') && (c<='9')) {
        return true;
    }

    return false;
}

int get_val(char line[]) {
    int first = -1;
    int last = -1;
    int i=0;

    while(line[i] != '\0') {
        if(first==-1 && isNum(line, i)) {
            first = line[i] - '0';
        }
        if(isNum(line, i)) {
            last = line[i] - '0';
        }
        i++;
    }

    return 10*first + last;
}

int main(void) {
    int sum = 0;
    char line[64];
    std::ifstream file;
    std::list<char> fchars;
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