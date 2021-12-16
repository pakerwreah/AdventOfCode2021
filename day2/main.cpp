#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

struct Command {
    std::string direction;
    int amount;
};

std::vector<Command> parse(std::istream &input);

int part1(const std::vector<Command> &commands);
int part2(const std::vector<Command> &commands);

int main() {

    std::istringstream mock("forward 5\ndown 5\nforward 8\nup 3\ndown 8\nforward 2\n");
    std::vector<Command> m_commands = parse(mock);

    assert(part1(m_commands) == 150);
    assert(part2(m_commands) == 900);

    std::ifstream file("day2.txt");
    std::vector<Command> commands = parse(file);

    std::cout << "part 1: " << part1(commands) << std::endl;
    std::cout << "part 2: " << part2(commands) << std::endl;

    return 0;
}

std::vector<Command> parse(std::istream &input) {

    std::vector<Command> commands;

    for (Command cmd; input >> cmd.direction >> cmd.amount;)
        commands.emplace_back(cmd);

    return commands;
}

int part1(const std::vector<Command> &commands) {

    int depth = 0;
    int horizontal = 0;

    for (const Command &cmd: commands) {
        if (cmd.direction == "forward")
            horizontal += cmd.amount;
        else if (cmd.direction == "up")
            depth -= cmd.amount;
        else if (cmd.direction == "down")
            depth += cmd.amount;
    }

    return depth * horizontal;
}

int part2(const std::vector<Command> &commands) {

    int depth = 0;
    int horizontal = 0;
    int aim = 0;

    for (const Command &cmd: commands) {
        if (cmd.direction == "forward") {
            horizontal += cmd.amount;
            depth += cmd.amount * aim;
        }
        else if (cmd.direction == "up")
            aim -= cmd.amount;
        else if (cmd.direction == "down")
            aim += cmd.amount;
    }

    return depth * horizontal;
}
