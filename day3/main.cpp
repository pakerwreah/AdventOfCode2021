#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

std::vector<std::string> parse(std::istream &input);

int part1(const std::vector<std::string> &numbers);
int part2(const std::vector<std::string> &numbers);

int main() {

    std::istringstream mock("00100\n11110\n10110\n10111\n10101\n01111\n00111\n11100\n10000\n11001\n00010\n01010");
    std::vector<std::string> m_numbers = parse(mock);

    assert(part1(m_numbers) == 198);
    assert(part2(m_numbers) == 230);

    std::ifstream file("day3.txt");
    std::vector<std::string> numbers = parse(file);

    std::cout << "part 1: " << part1(numbers) << std::endl;
    std::cout << "part 2: " << part2(numbers) << std::endl;

    return 0;
}

std::vector<std::string> parse(std::istream &input) {

    std::vector<std::string> numbers;

    for (std::string line; input >> line;)
        numbers.emplace_back(line);

    return numbers;
}

int part1(const std::vector<std::string> &numbers) {

    std::string gamma_bin, epsilon_bin;
    size_t length = numbers[0].length();

    for (int i = 0; i < length; i++) {
        int zeros = 0, ones = 0;

        for (const std::string &binary: numbers)
            *(binary[i] == '1' ? &ones : &zeros) += 1;

        gamma_bin += ones >= zeros ? "1" : "0";
        epsilon_bin += zeros <= ones ? "0" : "1";
    }

    int gamma = std::stoi(gamma_bin, nullptr, 2);
    int epsilon = std::stoi(epsilon_bin, nullptr, 2);

    return gamma * epsilon;
}

int part2(const std::vector<std::string> &numbers) {

    std::vector<std::string> oxygen_generator_numbers = numbers;
    std::vector<std::string> co2_scrubber_numbers = numbers;

    size_t length = numbers[0].length();

    for (int i = 0; i < length && oxygen_generator_numbers.size() > 1; i++) {
        int zeros = 0, ones = 0;

        for (const std::string &binary: oxygen_generator_numbers)
            *(binary[i] == '1' ? &ones : &zeros) += 1;

        for (auto it = oxygen_generator_numbers.begin(); it != oxygen_generator_numbers.end();) {
            if((*it)[i] == (ones >= zeros ? '1' : '0'))
                it++;
            else
                it = oxygen_generator_numbers.erase(it);
        }
    }

    for (int i = 0; i < length && co2_scrubber_numbers.size() > 1; i++) {
        int zeros = 0, ones = 0;

        for (const std::string &binary: co2_scrubber_numbers)
            *(binary[i] == '1' ? &ones : &zeros) += 1;

        for (auto it = co2_scrubber_numbers.begin(); it != co2_scrubber_numbers.end();) {
            if((*it)[i] == (zeros <= ones ? '0' : '1'))
                it++;
            else
                it = co2_scrubber_numbers.erase(it);
        }
    }

    std::string oxygen_generator_bin = oxygen_generator_numbers.back();
    std::string co2_scrubber_bin = co2_scrubber_numbers.back();

    int oxygen_generator = std::stoi(oxygen_generator_bin, nullptr, 2);
    int co2_scrubber = std::stoi(co2_scrubber_bin, nullptr, 2);

    return oxygen_generator * co2_scrubber;
}
