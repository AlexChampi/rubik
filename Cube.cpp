//
// Created by alekschamp on 15.05.22.
//

#include <iostream>
#include <random>
#include <functional>
#include <cstring>
#include "Cube.h"


const std::map<Color, std::string> Cube::colorName = Cube::getColorNames();

std::map<Color, std::string> Cube::getColorNames() {
    std::map<Color, std::string> m;
    m[RED] = "RED";
    m[YELLOW] = "YELLOW";
    m[BLUE] = "BLUE";
    m[GREEN] = "GREEN";
    m[ORANGE] = "ORANGE";
    m[WHITE] = "WHITE";
    return m;
}

void Cube::draw() {

    glPushMatrix();
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            for (int k = -size / 2; k < (size + 1) / 2; ++k) {
                if (!bricks[i + size / 2][j + size / 2][k + size / 2].isRot &&
                    (i == -size / 2 || i == (size + 1) / 2 - 1 ||
                     j == -size / 2 || j == (size + 1) / 2 - 1 ||
                     k == -size / 2 || k == (size + 1) / 2 - 1)) {
                    bricks[i + size / 2][j + size / 2][k + size / 2].draw(i * 2, j * 2, k * 2);
                }
            }
        }
    }
    if (rotateAngle[0] != 0) {
        rotateSide(-1, 2, -1, 0);
    }

    if (rotateAngle[1] != 0) {
        rotateSide(0, -1, -1, 1);
    }

    if (rotateAngle[2] != 0) {
        rotateSide(-1, -1, 2, 2);
    }

    if (rotateAngle[3] != 0) {
        rotateSide(2, -1, -1, 3);
    }

    if (rotateAngle[4] != 0) {
        rotateSide(-1, -1, 0, 4);
    }

    if (rotateAngle[5] != 0) {
        rotateSide(-1, 0, -1, 5);
    }
    glPopMatrix();
}

void Cube::F() {
    _f(2, (size + 1) / 2);
}

void Cube::B() {
    _b(4, 0);
}

void Cube::L() {
    _l(1, 0);
}

void Cube::R() {
    _r(3, (size + 1) / 2);
}

void Cube::U() {
    _u(0, (size + 1) / 2);
}

void Cube::D() {
    _d(5, 0);
}

void Cube::f() {
    _b(2, (size + 1) / 2);
}

void Cube::b() {
    _f(4, 0);
}

void Cube::l() {
    _r(1, 0);
}

void Cube::r() {
    _l(3, (size + 1) / 2);
}

void Cube::u() {
    _d(0, (size + 1) / 2);
}

void Cube::d() {
    _u(5, 0);
}

void Cube::resetRotation(int pos) {
    Cube::rotateAngle[pos] = 0;
}

void Cube::resetBlockRotation(int x, int y, int z) {
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            if (x > -1) {
                bricks[x][i + 1][j + 1].isRot = false;
            }
            if (y > -1) {
                bricks[i + 1][y][j + 1].isRot = false;
            }
            if (z > -1) {
                bricks[i + 1][j + 1][z].isRot = false;
            }
        }
    }

}

void Cube::endRotation(int x, int y, int z, int side) {
    resetBlockRotation(x, y, z);
    resetRotation(side);
}

void Cube::rotateVis(float angle, int side, int x, int y, int z) {
    Cube::rotateAngle[side] = angle;
    setBlockRotation(x, y, z);
}

void Cube::setBlockRotation(int x, int y, int z) {
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            if (x > -1) {
                bricks[x][i + size / 2][j + size / 2].isRot = true;
            }
            if (y > -1) {
                bricks[i + size / 2][y][j + size / 2].isRot = true;
            }
            if (z > -1) {
                bricks[i + size / 2][j + size / 2][z].isRot = true;
            }
        }
    }

}


void Cube::realRotation(int x, int y, int z, int pos, int step) {

    for (int s = 0; s < step; ++s) {

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                tmp[j][size - 1 - i] = (x > -1) ? bricks[x][i][j] : ((y > -1) ? bricks[i][y][j]
                                                                              : bricks[i][j][z]);
            }
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                (x > -1) ? tmp[i][j].XOZ() : (y > -1) ? tmp[i][j].YOZ() : tmp[i][j].XOY();
                ((x > -1) ? bricks[x][i][j] : ((y > -1) ? bricks[i][y][j] : bricks[i][j][z])) = tmp[i][j];
            }
        }

    }
}

void Cube::rotateSide(int x, int y, int z, int pos) {
    glPushMatrix();
    int _x = (x == -1) ? 0 : 1;
    int _y = (y == -1) ? 0 : 1;
    int _z = (z == -1) ? 0 : 1;
    glRotated(rotateAngle[pos], _x, _y, _z);

    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            if (x > -1) {
                bricks[x][i + size / 2][j + size / 2].draw((x == 0) ? -size / 2 * 2 : size / 2 * 2, i * 2, j * 2);
            }
            if (y > -1) {
                bricks[i + size / 2][y][j + size / 2].draw(i * 2, (y == 0) ? -size / 2 * 2 : size / 2 * 2, j * 2);
            }
            if (z > -1) {
                bricks[i + size / 2][j + size / 2][z].draw(i * 2, j * 2, (z == 0) ? -size / 2 * 2 : size / 2 * 2);
            }
        }
    }
    glPopMatrix();


}

void Cube::_f(int pos, int param) {
    realRotation(-1, -1, param, pos, 1);
}

void Cube::_b(int pos, int param) {
    realRotation(-1, -1, param, pos, 3);
}

void Cube::_l(int pos, int param) {
    realRotation(param, -1, -1, pos, 3);
}

void Cube::_r(int pos, int param) {
    realRotation(param, -1, -1, pos, 1);
}

void Cube::_u(int pos, int param) {
    realRotation(-1, param, -1, pos, 3);
}

void Cube::_d(int pos, int param) {
    realRotation(-1, param, -1, pos, 1);
}

void Cube::log() {
    FileManager::out << ++Cube::logCounter << std::endl;
    int cnt = 1;
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            for (int k = -size / 2; k < (size + 1) / 2; ++k) {
                if (!bricks[i + size / 2][j + size / 2][k + size / 2].isRot &&
                    (i == -size / 2 || i == (size + 1) / 2 - 1 ||
                     j == -size / 2 || j == (size + 1) / 2 - 1 ||
                     k == -size / 2 || k == (size + 1) / 2 - 1)) {

                    FileManager::out << cnt++ << std::endl <<
                                     i << " " << j << " " << k << std::endl <<
                                     bricks[i + size / 2][j + size / 2][k + size / 2].getX() << " "
                                     << bricks[i + size / 2][j + size / 2][k + size / 2].getY() << " "
                                     << bricks[i + size / 2][j + size / 2][k + size / 2].getZ() << std::endl;
                    auto temp = bricks[i + size / 2][j + size / 2][k + size / 2].getColors();
                    for (auto it: temp) {
                        FileManager::out << " Side " << it.first << " color " << colorName.at(it.second) << std::endl;
                    }
                }
            }
        }
    }
    FileManager::out << std::endl;
}



std::string Cube::getColors() {
    std::vector<std::string> stringVector(6);
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            for (int k = -size / 2; k < (size + 1) / 2; ++k) {
                if (i == -size / 2 || i == (size + 1) / 2 - 1 ||
                    j == -size / 2 || j == (size + 1) / 2 - 1 ||
                    k == -size / 2 || k == (size + 1) / 2 - 1) {
                    auto map = bricks[i + size / 2][j + size / 2][k + size / 2].getColors();
                    for (auto it: map) {
                        stringVector[it.first] += Cube::colorName.at(it.second)[0];
                    }
                }
            }
        }
    }
    std::string res;
    for (auto i: stringVector) {
        res += i;
//        FileManager::out << i << std::endl;
    }
    return res;
}

Cube::Cube() {
    memset(rotateAngle, 0, sizeof(rotateAngle));
}

void Cube::readFile() {
    for (int i = -size / 2; i < (size + 1) / 2; ++i) {
        for (int j = -size / 2; j < (size + 1) / 2; ++j) {
            for (int k = -size / 2; k < (size + 1) / 2; ++k) {
                if (i == -size / 2 || i == (size + 1) / 2 - 1 ||
                    j == -size / 2 || j == (size + 1) / 2 - 1 ||
                    k == -size / 2 || k == (size + 1) / 2 - 1) {
                    for (auto i :
                            bricks[i + size / 2][j + size / 2][k + size / 2].colors) {
                        FileManager::out << Cube::colorName.at(i) << " ";
                    }
                    FileManager::out << '\n';
                }
            }
        }
    }
    exit(0);
}










