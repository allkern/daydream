#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

struct sh4_inst {
    std::string name;
    std::string assembly;
    std::string opcode;
};

void find_and_replace(std::string& str, const std::string& f, const std::string& r) {
    std::size_t pos = str.find(f);

    if (pos == std::string::npos)
        return;

    str.replace(pos, f.length(), r);
}

int main() {
    std::ifstream file("insns.txt", std::ios::binary);

    std::vector <sh4_inst> insns;

    sh4_inst inst;

    while (!file.eof()) {
        std::getline(file, inst.name);
        std::getline(file, inst.assembly);
        std::getline(file, inst.opcode);

        insns.push_back(inst);
    }

    for (sh4_inst& i : insns) {
        std::string fmt;
        std::string mnemonic;

        size_t pos = i.assembly.find_first_of(' ');

        mnemonic = i.assembly.substr(0, pos);

        if (pos != std::string::npos) {
            fmt = "%-7s" + i.assembly.substr(pos) + "\n";
        } else {
            fmt = "%s\n";
        }

        find_and_replace(fmt, "Rn", "R%u");
        find_and_replace(fmt, "Rm", "R%u");
        find_and_replace(fmt, "disp", "%+i");
        find_and_replace(fmt, "imm", "0x%02x");
        find_and_replace(fmt, "label", "%+i");

        std::printf(fmt.c_str(), mnemonic.c_str(), 1, 2, 3);

        // std::cout << fmt;
    }

    file.close();
}