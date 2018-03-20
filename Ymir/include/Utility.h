#pragma once

#include <fstream>
#include <iterator>
#include <string>

using std::ifstream;
using std::streambuf;
using std::string;
using std::istreambuf_iterator;

string ReadFile(const string &filename);