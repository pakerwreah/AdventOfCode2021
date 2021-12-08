#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

int part1(const std::vector<int> &depths);
int part2(const std::vector<int> &depths);

int main() {

    std::vector<int> mock = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};

    assert(part1(mock) == 7);
    assert(part2(mock) == 5);

    std::ifstream file("day1.txt");
    std::vector<int> depths;
    for (int value; file >> value;)
        depths.emplace_back(value);

    std::cout << "part 1: " << part1(depths) << std::endl;
    std::cout << "part 2: " << part2(depths) << std::endl;

    return 0;
}

int part1(const std::vector<int> &depths) {

    int increases = 0;
    for (int i = 1; i < depths.size(); i++) {
        if (depths[i] > depths[i - 1])
            increases++;
    }
    return increases;
}

int part2(const std::vector<int> &depths) {

    auto window = [&](int from) {
        int sum = 0;
        for (int i = from, count = 0; count < 3; i++, count++)
            sum += depths[i];
        return sum;
    };

    int increases = 0;
    for (int i = 0; i < depths.size() - 3; i++) {
        if (window(i + 1) > window(i))
            increases++;
    }
    return increases;
}
