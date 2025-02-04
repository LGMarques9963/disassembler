#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>  // For fixed-width integer types (uint8_t, uint32_t)
#include <iomanip>

uint32_t read32(const std::vector<uint8_t>& code, size_t index) {
    return  static_cast<uint32_t>(code[index])                  | // Byte 0: least significant
            (static_cast<uint32_t>(code[index+1]) << 8)         | // Byte 1
            (static_cast<uint32_t>(code[index+2]) << 16)        | // Byte 2
            (static_cast<uint32_t>(code[index+3]) << 24);         // Byte 3: most significant

}

void disassemble(const std::vector<uint8_t>& code) {
    size_t i = 0;

    while (i < code.size()) {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";
        uint8_t opcode = code[i];

        if (opcode >= 0xB8 && opcode <= 0xBF) {
            if (i + 4 > code.size()) {
                std::cerr << "Unexpected end of code" << std::endl;
                return;
            }
            uint32_t imm = read32(code, i + 1);

            int reg = opcode - 0xB8;

            const char* reg_names[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};

            std::cout << "mov " << reg_names[reg] << ", 0x" << std::hex << imm << std::endl;

            i+=5;
        }
        else if (opcode == 0xC3) {
            std::cout << "ret" << std::endl;
            i++;
        } else if (opcode == 0x90) {
            std::cout << "nop" << std::endl;
            i++;
        } else {
            std::cout << "db 0x" << std::setw(2) << std::setfill('0') << static_cast<int>(opcode) << std::endl;
            i++;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<uint8_t> code((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

    file.close();

    disassemble(code);

    return 0;
}