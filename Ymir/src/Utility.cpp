#pragma once

#include "utility.h"

string ReadFile(const string &filename) {
    ifstream fin(filename);
    return string(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
}