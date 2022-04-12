#pragma once
#include "glIncludes.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>

glm::vec3 ReadVec3FromStrings(std::vector<std::string>& strings);
glm::vec3 ReadVec3FromStrings(std::vector<std::string>& strings, int offset);
void ParseStringByDelim(std::vector<std::string>& out, std::string str, std::string delim);
void PrintArray(std::string startText, float array[], int n, int elemsPerLine);
void PrintArray(std::string startText, unsigned int[], int n, int elemsPerLine);