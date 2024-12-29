#include <iostream>
#include <fstream>
using namespace std;

class Computer {
public:
    Computer(uint64_t a, uint64_t b, uint64_t c, string program) : a{a}, b{b}, c{c}, program(std::move(program)) {
    }

    void solve() {
        while (ptr < program.size()) {
            uint64_t instruction = program[ptr] - '0';
            uint64_t operand = program[ptr + 2] - '0';
            executeInstruction(instruction, operand);
            movePtr(instruction, operand);
            //printRegisters();
        }

        printOutput();
    }

private:
    void executeInstruction(uint64_t instruction, uint64_t operand) {
        switch (instruction) {
            case 0:
                adv(operand);
                break;
            case 1:
                bxl(operand);
                break;
            case 2:
                bst(operand);
                break;
            case 4:
                bxc();
                break;
            case 5:
                out(operand);
                break;
            case 6:
                bdv(operand);
                break;
            case 7:
                cdv(operand);
                break;
            default:
                break;
        }
    }

    void adv(uint64_t operand) {
        uint64_t denominator = 1u << min(combo(operand), 31llu);
        a /= denominator;
    }

    void bxl(uint64_t operand) {
        b ^= operand;
    }

    void bst(uint64_t operand) {
        b = combo(operand) % 8;
    }

    void bxc() {
        b ^= c;
    }

    void out(uint64_t operand) {
        output.push_back(combo(operand) % 8);
    }

    void bdv(uint64_t operand) {
        uint64_t denominator = 1u << min(combo(operand), 31llu);
        b = a / denominator;
    }

    void cdv(uint64_t operand) {
        uint64_t denominator = 1u << min(combo(operand), 31llu);
        c = a / denominator;
    }

    void movePtr(uint64_t instruction, uint64_t operand) {
        if (instruction == 3 && a) {
            ptr = operand;
        } else {
            ptr += 4;
        }
    }

    uint64_t combo(uint64_t operand) {
        switch (operand) {
            case 0:
            case 1:
            case 2:
            case 3:
                return operand;
            case 4:
                return a;
            case 5:
                return b;
            case 6:
                return c;
            default:
                return -1;
        }
    }

    void printRegisters() {
        cout << "A = " << a << endl;
        cout << "B = " << b << endl;
        cout << "C = " << c << endl;
    }

    void printOutput() {
        for (int i = 0; i < output.size(); ++i) {
            if (i) {
                cout << ',';
            }
            cout << output[i];
        }
        cout << endl;
    }

    uint64_t a, b, c;
    uint64_t ptr{0};
    string program;
    vector<uint64_t> output;
};

int main() {
    ifstream file("input.txt");
    
    uint64_t a, b, c;
    string skip, program;

    file >> skip >> skip >> a;
    file >> skip >> skip >> b;
    file >> skip >> skip >> c;
    file >> skip >> program;

    Computer computer(a, b, c, program);
    computer.solve();

    return 0;
}