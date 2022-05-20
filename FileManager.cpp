//
// Created by alekschamp on 18.05.22.
//

#include <iostream>
#include "FileManager.h"

std::string FileManager::inputFile;
std::ofstream FileManager::out;

void FileManager::initialize() {

    out.open("log.txt");
}
