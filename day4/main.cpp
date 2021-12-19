#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

class Game {
    static const int BOARD_SIZE = 5;

    struct Board {
        int numbers[BOARD_SIZE][BOARD_SIZE]{0};
        bool marked[BOARD_SIZE][BOARD_SIZE]{false};
    };

    std::vector<int> numbers;
    std::vector<Board> boards;

    static void markNumber(Board &, int);
    static int boardSum(const Board &);
    static bool checkWin(const Board &);

public:
    explicit Game(std::istream &);

    [[nodiscard]] int part1() const;
    [[nodiscard]] int part2() const;
};

int main() {

    std::ifstream mock("day4-mock.txt");
    Game mock_game(mock);

    assert(mock_game.part1() == 4512);
    assert(mock_game.part2() == 1924);

    std::ifstream input("day4.txt");
    Game game(input);

    std::cout << "part 1: " << game.part1() << std::endl;
    std::cout << "part 2: " << game.part2() << std::endl;

    return 0;
}

Game::Game(std::istream &data) {

    std::string line;
    data >> line;

    std::istringstream line_stream(line);

    char comma;
    for (int number; line_stream >> number; line_stream >> comma)
        numbers.emplace_back(number);

    while (data.good()) {
        Board board;
        for (auto &rows: board.numbers) {
            for (int &pos: rows) {
                int number;
                if (data >> number)
                    pos = number;
                else
                    return;
            }
        }
        boards.emplace_back(board);
    }
}

void Game::markNumber(Board &board, int number) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.numbers[i][j] == number) {
                board.marked[i][j] = true;
                return;
            }
        }
    }
}

int Game::boardSum(const Board &board) {
    int sum = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!board.marked[i][j])
                sum += board.numbers[i][j];
        }
    }
    return sum;
}

bool Game::checkWin(const Board &board) {
    // check row win
    for (int i = 0; i < BOARD_SIZE; i++) { // NOLINT(modernize-loop-convert)
        bool win = true;
        for (int j = 0; j < BOARD_SIZE && win; j++)
            win = board.marked[i][j];
        if (win)
            return true;
    }
    // check column win
    for (int i = 0; i < BOARD_SIZE; i++) {
        bool win = true;
        for (int j = 0; j < BOARD_SIZE && win; j++)
            win = board.marked[j][i];
        if (win)
            return true;
    }
    return false;
}

int Game::part1() const {

    std::vector<Board> playing_boards = this->boards;

    for (int number: numbers) {
        for (Board &board: playing_boards) {
            markNumber(board, number);
            if (checkWin(board))
                return number * boardSum(board);
        }
    }

    return 0;
}

int Game::part2() const {

    std::vector<Board> playing_boards = boards;

    for (int number: numbers) {
        for (auto it = playing_boards.begin(); it != playing_boards.end();) {
            Board &board = *it;

            markNumber(board, number);

            if (checkWin(board)) {
                if (playing_boards.size() == 1)
                    return number * boardSum(playing_boards.back());

                it = playing_boards.erase(it);
            }
            else
                it++;
        }
    }

    return 0;
}
