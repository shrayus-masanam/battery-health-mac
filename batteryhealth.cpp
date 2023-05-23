#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cmath>
#include <algorithm>

// From: https://stackoverflow.com/a/478960
std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

// From: https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
std::string trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

int main(int argc, char *argv[])
{
    std::string max_capacity = exec("ioreg -l -w0 | grep \"MaxCapacity\"");
    max_capacity = max_capacity.substr(max_capacity.find("\"MaxCapacity\" =") + 15); // the numerical value as a string (possibly with whitespace)

    std::string design_capacity = exec("ioreg -l -w0 | grep \"DesignCapacity\"");
    design_capacity = design_capacity.substr(design_capacity.find("\"DesignCapacity\" =") + 18); // the numerical value as a string (possibly with whitespace)

    double battery_health = std::stod(max_capacity) / std::stod(design_capacity) * 100;

    if (argc == 1)
        std::cout << trunc(battery_health) << "%" << std::endl;
    else if (argc == 2) {
        if (strcmp(argv[1], "-p") == 0)
            std::cout << battery_health << "%" << std::endl;
        else if (strcmp(argv[1], "-m") == 0)
            std::cout << trim(max_capacity) << std::endl;
        else if (strcmp(argv[1], "-d") == 0)
            std::cout << trim(design_capacity) << std::endl;
        else if (strcmp(argv[1], "-h") == 0)
            std::cout << std::endl << "Usage: " << std::endl << "batteryhealth [-p | -m | -d | -h]" << std::endl << std::endl << "-p: prints the battery health as a precise percentage" << std::endl << "-m: prints the current maximum capacity of the battery (in charge cycles)" << std::endl << "-d: prints the original maximum capacity of the battery (in charge cycles)" << std::endl << "-h: prints this help message" << std::endl << std::endl << "Supplying no arguments will return the battery health as a truncated percentage." << std::endl << std::endl;
        else
            std::cout << "Invalid argument. Use -h for help." << std::endl;
    }
    return 0;
}