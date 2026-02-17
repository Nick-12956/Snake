#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <thread>
#include <chrono>
#define xaxis(x) for(i=0;i<x;i++) cout << "  ";
#define hori(x) for(i=0;i<x;i++) cout <<r<< '-' <<w;
#define w "\033[0m"
#define r "\033[31m"
#define g "\033[32m"
#define y "\033[33m"
#define b "\033[34m"
struct tail{
    int tx, ty;
    tail(int x, int z) : tx(x), ty(z) {}
};
void cs() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
int xrand() {
    return ((rand() % 39) + 1);
}
int yrand() {
    return ((rand() % 9) + 1);
}
int main() {
    int hx, hy, hd, ax, ay, i, j, k, score = 0;
    bool game_on = true, space;
    vector<tail> tails;
    string input;
    srand(time(NULL));
    tails.emplace_back(1,1);
    cs();
    cout <<y<< "------{ Snake Game }------\n\n" <<b<< "Press Enter to start" <<w;
    cin.ignore();
    hx=2; hy=1; hd = 0;
    ax = xrand();
    ay = yrand();
    do{
        cs();
        hori(80);
        cout << endl;
        for(j = 0;j < 10;j++) {
            cout <<r<< '|' <<w;
            for(k = 0;k < 40;k++) {
                space = true;
                if((hx == k)&&(hy == j)) {
                    if(hd == 0) cout <<b<< "> " <<w;
                    else if(hd == 1) cout <<b<< "v " <<w;
                    else if(hd == 2) cout <<b<< "< " <<w;
                    else cout <<b<< "^ " <<w;
                    space = false;
                }
                else if((ax == k)&&(ay == j)) {
                    cout <<g<< "* " <<w;
                    space = false;
                }
                else {
                    for(i = 0;i < tails.size();i++) {
                        if((tails.at(i).tx == k)&&(tails.at(i).ty == j)) {
                            cout <<y<< "o " <<w;
                            space = false;
                        }
                    }
                }
                if(k == 39) cout <<r<< '|' <<w;
                else if(space) cout << "  ";
            }
            cout << endl;
        }
        hori(80);
        cout << endl <<b<< "-> Score : " << score * 10 << endl <<y<< "-> Tails : " << tails.size() <<w<< "\n\nEnter Input (W,A,S,D) to move, (Enter) to continue : ";
        if((hx == -1)||(hy == -1)||(hx == 39)||(hy == 10)) game_on = false;
        else {
            for(i = 0; i < tails.size(); i++) {
                if((hx == tails.at(i).tx)&&(hy == tails.at(i).ty)) {
                    game_on = false;
                    break;
                }
            }
        }
        if(game_on) {
            getline(cin, input);
            if(!input.empty()) {
                if((input == "W")||(input == "w")) {
                    if(hd == 1) {
                        cout <<r<< "Can't turn 180 degrees => Considered as Enter" <<w;
                        cin.ignore();
                    }
                    else hd = 3;
                }
                else if((input == "A")||(input == "a")) {
                    if(hd == 0) {
                        cout <<r<< "Can't turn 180 degrees => Considered as Enter" <<w;
                        cin.ignore();
                    }
                    else hd = 2;
                }
                else if((input == "S")||(input == "s")) {
                    if(hd == 3) {
                        cout <<r<< "Can't turn 180 degrees => Considered as Enter" <<w;
                        cin.ignore();
                    }
                    else hd = 1;
                }
                else if((input == "D")||(input == "d")) {
                    if(hd == 2) {
                        cout <<r<< "Can't turn 180 degrees => Considered as Enter" <<w;
                        cin.ignore();
                    }
                    else hd = 0;
                }
                else {
                    cout <<r<< "Wrong Input => Considered as Enter" <<w;
                    cin.ignore();
                }
            }
        }
        if((ax == hx)&&(ay == hy)) {
            tails.emplace_back(tails.at(tails.size()-1).tx,tails.at(tails.size()-1).ty);
            score++;
            ax = xrand();
            ay = yrand();
        }
        for((i = tails.size()-1);i >= 0;i--) {
            if(i == 0) {
                tails.at(i).tx = hx;
                tails.at(i).ty = hy;
            }
            else {
                tails.at(i).tx = tails.at(i-1).tx;
                tails.at(i).ty = tails.at(i-1).ty;
            }
        }
        if(hd == 0) hx++;
        else if(hd == 1) hy++;
        else if(hd == 2) hx--;
        else hy--;
    }while(game_on);
    cs();
    cout <<r<< "-----<{ Game Over }>-----\n\nScore : " <<b<< score <<y<< "\nTails : " << tails.size() <<w;
    return 0;
}
/*
direction = direction (0-right, 1-down, 2-left, 3-up)
hx = head x position
hy = head y position
hd = head direction
tx = tail x position
ty = tail y position
ax = apple x position
ay = apple y position
range of play (1,1) - (40,10)
j = rows (y limits)
k = columns (x limits)
w = white text
r = red text
g = green text
y = yellow text
b = blue text
*/