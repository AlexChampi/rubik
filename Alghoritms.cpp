//
// Created by alekschamp on 18.05.22.
//

#include <random>
#include <array>
#include <functional>
#include "Events.h"

bool isSideReady(int side, const std::string &colors) {
    for (int i = side * 6 + 1; i < side * 6 + 6; ++i) {
        if (colors[i] != colors[i - 1]) {
            return false;
        }
    }
    return true;
}

void Events::solve() {
//    Events::cross();
    Events::cornerCross();
}

void Events::cross() {
    this->y();
    this->y();
    std::string cur_colors = cube->getColors();
    bool itRotated = false;
    int cnt = 0;
    while (cnt < 4) {
        itRotated = false;
        cur_colors = cube->getColors();
        for (int i = 1; i < 9; i += 2) {
            if (cur_colors[i] == 'W') {
                if (i == 1 && cur_colors[16] == 'B') {
                    this->L();
                    this->L();
                    itRotated = true;
                    break;
                }
                if (i == 5 && cur_colors[23] == 'R') {
                    this->F();
                    this->F();
                    itRotated = true;
                    break;
                }
                if (i == 7 && cur_colors[34] == 'G') {
                    this->R();
                    this->R();
                    itRotated = true;
                    break;
                }
                if (i == 3 && cur_colors[41] == 'O') {
                    this->B();
                    this->B();
                    itRotated = true;
                    break;
                }

            }
        }
        if (cur_colors[16] == 'W' && cur_colors[1] == 'B') {
            this->u();
            this->f();
            this->L();
            this->F();
            itRotated = true;
        }
        if (cur_colors[23] == 'W' && cur_colors[5] == 'R') {
            this->u();
            this->r();
            this->F();
            this->R();
            itRotated = true;
        }
        if (cur_colors[34] == 'W' && cur_colors[7] == 'G') {
            this->u();
            this->b();
            this->R();
            this->B();
            itRotated = true;
        }
        if (cur_colors[41] == 'W' && cur_colors[3] == 'O') {
            this->u();
            this->l();
            this->B();
            this->L();
            itRotated = true;
        }
        if (cur_colors[14] == 'W') {
            this->l();
            this->u();
            this->L();
            itRotated = true;
        }
        if (cur_colors[25] == 'W') {
            this->f();
            this->u();
            this->F();
            itRotated = true;
        }
        if (cur_colors[30] == 'W') {
            this->r();
            this->u();
            this->R();
            itRotated = true;
        }
        if (cur_colors[37] == 'W') {
            this->b();
            this->u();
            this->B();
            itRotated = true;
        }
        if (cur_colors[12] == 'W') {
            this->L();
            this->u();
            this->l();
            itRotated = true;
        }
        if (cur_colors[19] == 'W') {
            this->F();
            this->u();
            this->f();
            itRotated = true;
        }
        if (cur_colors[32] == 'W') {
            this->R();
            this->u();
            this->r();
            itRotated = true;
        }
        if (cur_colors[43] == 'W') {
            this->B();
            this->u();
            this->b();
            itRotated = true;
        }
        if (cur_colors[10] == 'W') {
            this->L();
            this->L();
            this->u();
            this->l();
            this->l();
            itRotated = true;
        }
        if (cur_colors[21] == 'W') {
            this->F();
            this->F();
            this->u();
            this->f();
            this->f();
            itRotated = true;
        }
        if (cur_colors[28] == 'W') {
            this->R();
            this->R();
            this->u();
            this->r();
            this->r();
            itRotated = true;
        }
        if (cur_colors[39] == 'W') {
            this->B();
            this->B();
            this->u();
            this->b();
            this->b();
            itRotated = true;
        }
        if (cur_colors[50] == 'W' && cur_colors[21] != 'R') {
            this->F();
            this->F();
            this->u();
            this->f();
            this->f();
        }
        if (cur_colors[52] == 'W' && cur_colors[28] != 'G') {
            this->R();
            this->R();
            this->u();
            this->r();
            this->r();
        }
        if (cur_colors[48] == 'W' && cur_colors[39] != 'O') {
            this->B();
            this->B();
            this->u();
            this->b();
            this->b();
        }
        if (cur_colors[46] == 'W' && cur_colors[10] != 'B') {
            this->L();
            this->L();
            this->u();
            this->l();
            this->l();
        }

        if (!itRotated) {
            cnt++;
            this->U();
        } else {
            cnt = 0;
        }
    }
    this->Y();
    this->Y();
}


void Events::cornerCross() {
    bool isRotated = false;
    std::string cur_colors = cube->getColors();
    int cnt = 0;
    while (cnt < 4) {
        isRotated = false;

        if (cur_colors[17] == 'W' && cur_colors[2] == 'B' && cur_colors[20] == 'R') {
            this->l();
            this->u();
            this->L();
            isRotated = true;
        }
        if (cur_colors[26] == 'W' && cur_colors[8] == 'R' && cur_colors[35] == 'G') {
            this->f();
            this->u();
            this->F();
            isRotated = true;
        }
        if (cur_colors[33] == 'W' && cur_colors[6] == 'G' && cur_colors[44] == 'O') {
            this->r();
            this->u();
            this->R();
            isRotated = true;
        }
        if (cur_colors[38] == 'W' && cur_colors[0] == 'O' && cur_colors[15] == 'B') {
            this->b();
            this->u();
            this->B();
            isRotated = true;
        }


        if (!isRotated) {
            cnt++;
            this->U();
        } else {
            cnt = 0;
        }
    }
}


void Events::shuffle() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(20, 100);
    std::uniform_int_distribution<> distribution(0, 11);

    for (int i = 0; i < distrib(rd); ++i) {
        switch (distribution(rd)) {
            case 0:
                F();
                break;
            case 1:
                R();
                break;
            case 2:
                L();
                break;
            case 3:
                B();
                break;
            case 4:
                U();
                break;
            case 5:
                D();
                break;
            case 6:
                f();
                break;
            case 7:
                r();
                break;
            case 8:
                l();
                break;
            case 9:
                b();
                break;
            case 10:
                u();
                break;
            case 11:
                d();
                break;

        }
    }
}
