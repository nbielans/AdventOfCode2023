#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#define INPUT_FILE "input.txt"

enum CARDS { _J=1, _2, _3, _4, _5, _6, _7, _8, _9, _T, _Q, _K, _A };
enum HAND_TYPE { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, FULL_HOUSE, FOUR_OF_A_KIND, FIVE_OF_A_KIND };

class Hand {
    private:
        std::vector<CARDS> hand;
        HAND_TYPE type;
        int bid;
    public:
        Hand(const std::vector<CARDS>& _hand, int _bid) {
            hand = _hand;
            bid = _bid;
            std::unordered_map<CARDS, int> occurances;
            occurances[_J] = 0;

            for(const CARDS& card: hand) {
                try {
                    occurances.at(card)++;
                } catch(std::out_of_range) {
                    occurances[card] = 1;
                }
            }
            
            int size = occurances.size() - (occurances[_J]==0);

            if(size==5 || size==4 || size==1) {
                type = (size==5) ? HIGH_CARD : 
                       (size==4) ? ONE_PAIR  :
                                   FIVE_OF_A_KIND;
            } else if(size==3) {
                type = THREE_OF_A_KIND;
                for(const auto& occ: occurances) {
                    if(occ.second==2) {
                        type = TWO_PAIR;
                        break;
                    }
                }
            } else { // size==2
                type = FULL_HOUSE;
                for(const auto& occ: occurances) {
                    if(occ.second==4) {
                        type = FOUR_OF_A_KIND;
                        break;
                    }
                }
            }
            
            if(occurances[_J] && type!=FIVE_OF_A_KIND) {
                int num = occurances[_J];
                if(type==FOUR_OF_A_KIND || type==HIGH_CARD) {
                    type = (HAND_TYPE) ((int) type + 1);
                } else if((num==2)&&(type==TWO_PAIR)) {
                    type = (HAND_TYPE) ((int) type + 3);
                } else {
                    type = (HAND_TYPE) ((int) type + 2);
                }
            }
        }

        int getBid() const { return bid; }
        HAND_TYPE getType() const { return type; }
        std::vector<CARDS>::const_iterator cbegin() const { return hand.cbegin(); }

        bool operator<(const Hand& other) {
            if(type != other.getType()) {
                return type < other.getType();
            }

            auto it = hand.cbegin();
            auto oit = other.cbegin();
            while(it!=hand.end()) {
                if((*it)!=(*oit)) {
                    return (*it)<(*oit);
                }
                it++;
                oit++;
            }

            return false;
        }
};

bool isNum(char c) {
    return (c >= '0') && (c <='9');
}

int getNum(const std::string& line, int i) {
    int val = 0;
    
    while(isNum(line[i])) {
        val *= 10;
        val += line[i]-'0';
        i++;
    }

    return val;
}

CARDS getCard(char c) {
    if(c<='9') {
        return (CARDS) (c-'0');
    }

    switch(c) {
        case 'A': return _A;
        case 'K': return _K;
        case 'Q': return _Q;
        case 'J': return _J;
        case 'T': 
        default:  return _T; 
    }
}

void setPlayers(std::ifstream& file, std::list<Hand>& players) {
    std::string line;
    std::vector<CARDS> hand(5);
    int bid;

    while(!file.eof()) {
        std::getline(file, line);
        for(int i=0; i<5; i++) {
            hand[i] = getCard(line[i]);
        }
        bid = getNum(line, 6);
        
        players.push_back(Hand(hand, bid));
    }    
}

long getWinnings(const std::list<Hand>& players) {
    long winnings = 0;
    int i = 1;
    for(auto player: players) {
        winnings += i*player.getBid();
        i++;
    }

    return winnings;
}

int main(void) {
    std::list<Hand> players;
    std::ifstream file;
    file.open(INPUT_FILE);
    if(!file.is_open()) {
        return 1;
    }

    setPlayers(file, players);

    players.sort();

    long winnings = getWinnings(players);

    std::cout << "Winnings: " << winnings << std::endl;    
    return 0;
}