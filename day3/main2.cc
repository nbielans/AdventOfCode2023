#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_FILE "input.txt"

bool isNum(char c) {
    return (c>='0' && c<='9');
}

long read_num(const std::string& line, int i) {
    long num = 0;
    while(i>=0 && isNum(line[i])) { i--; }
    i++;
    while(i<line.size() && isNum(line[i])) {
        num *= 10;
        num += line[i] - '0';
        i++;
    }
    return num;
}

void update_gears(int& cnt, const std::vector<std::string>& lines, std::vector<long>& gears, int& gearIdx, int idx, int i) {
    cnt++;
    gears[gearIdx] = read_num(lines[idx], i);
    gearIdx = 1 - gearIdx;
}

int checkLine(int i, int idx, const std::vector<std::string>& lines, std::vector<long>& gears, int& gearIdx) {
    int cnt = 0;
    
    // middle line where '*' is found
    if(idx==1) {
        if(i!=0 && isNum(lines[idx][i-1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i-1);
        }
        if((i+1)!=lines[idx].size() && isNum(lines[idx][i+1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i+1);
        }

        return cnt;
    }

    // non middle line
    // at start of line
    if(i==0) {
        if(isNum(lines[idx][i]) && isNum(lines[idx][i+1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i);
            return cnt;
        }
        if(isNum(lines[idx][i])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i);
        } 
        if(isNum(lines[idx][i+1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i+1);
        }
        return cnt;
    }
    // at end of line
    if((i+1)==lines[idx].size()) {
        if(isNum(lines[idx][i]) && isNum(lines[idx][i-1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i);
            return cnt;
        }
        if(isNum(lines[idx][i])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i);
        } 
        if(isNum(lines[idx][i-1])) {
            update_gears(cnt, lines, gears, gearIdx, idx, i-1);
        }
        return cnt;
    }

    // in center of line
    if(isNum(lines[idx][i]) && (isNum(lines[idx][i-1]) || isNum(lines[idx][i+1]))) {
        update_gears(cnt, lines, gears, gearIdx, idx, i);
        return cnt;
    }
    if(isNum(lines[idx][i])) {
        update_gears(cnt, lines, gears, gearIdx, idx, i);
    } 
    if(isNum(lines[idx][i-1])) {
        update_gears(cnt, lines, gears, gearIdx, idx, i-1);
    }
    if(isNum(lines[idx][i+1])) {
        update_gears(cnt, lines, gears, gearIdx, idx, i+1);
    }
    return cnt;
}

long compare(const std::vector<std::string>& lines) {
    long result = 0;
    long temp;
    std::vector<long> gears(2);
    int gearIdx = 0;

    // index 1 is not the first or last line of the file
    if(!(lines[0][0]=='\0' || lines[2][0]=='\0')) {
        for(int i=0; i<lines[0].size(); i++) {
            temp = 0;
            if(lines[1][i] == '*'){
                // check num around
                temp += checkLine(i, 0, lines, gears, gearIdx);
                temp += checkLine(i, 1, lines, gears, gearIdx);
                temp += checkLine(i, 2, lines, gears, gearIdx);
                if(temp == 2) {
                    result += gears[0]*gears[1];
                }
            }
        }
    } 
    else {
        int idx = 2*(lines[2][0]=='\0');
        for(int i=0; i<lines[0].size(); i++) {
            temp = 0;
            if(lines[1][i] == '*'){
                // check num around
                temp += checkLine(i,   1, lines, gears, gearIdx);
                temp += checkLine(i, idx, lines, gears, gearIdx);
                if(temp == 2) {
                    result += gears[0]*gears[1];
                }
            }
        }
    }

    return result;
}


int main(void) {
    long sum_ratios = 0;
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

        sum_ratios += compare(lines);
    } while(lines[1][0] != '\0');


    file.close();
    std::cout << "Parts Sum: " << sum_ratios << std::endl;
    return 0;
}
