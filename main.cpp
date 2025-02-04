#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>  // For fixed-width integer types (uint8_t, uint32_t)
#include <cstring>
#include <iomanip>

// The ELF header is defined in a packed format, so we disable padding.
#if defined(_MSC_VER)
    #pragma pack(push, 1)
#elif defined(__GNUC__)
    #pragma pack(push, 1)
#endif

// Definition for 32-bit ELF header (Elf32_Ehdr)
// This structure is based on the System V Application Binary Interface (ABI)
// for the ELF format. For more details, see:
//   - "System V Application Binary Interface, Edition 4"
//   - The "ELF" specification (search for "ELF header" online).
struct Elf32_Ehdr {
    unsigned char e_ident[16]; // Magic number and other info
    uint16_t e_type;           // Object file type
    uint16_t e_machine;        // Architecture (e.g., EM_386)
    uint32_t e_version;        // Object file version
    uint32_t e_entry;          // Entry point virtual address
    uint32_t e_phoff;          // Program header table file offset
    uint32_t e_shoff;          // Section header table file offset
    uint32_t e_flags;          // Processor-specific flags
    uint16_t e_ehsize;         // ELF header size in bytes
    uint16_t e_phentsize;      // Program header table entry size
    uint16_t e_phnum;          // Program header table entry count
    uint16_t e_shentsize;      // Section header table entry size
    uint16_t e_shnum;          // Section header table entry count
    uint16_t e_shstrndx;       // Section header string table index
};

// Definition for 64-bit ELF header (Elf64_Ehdr)
struct Elf64_Ehdr {
    unsigned char e_ident[16]; // Magic number and other info
    uint16_t e_type;           // Object file type
    uint16_t e_machine;        // Architecture (e.g., EM_X86_64)
    uint32_t e_version;        // Object file version
    uint64_t e_entry;          // Entry point virtual address
    uint64_t e_phoff;          // Program header table file offset
    uint64_t e_shoff;          // Section header table file offset
    uint32_t e_flags;          // Processor-specific flags
    uint16_t e_ehsize;         // ELF header size in bytes
    uint16_t e_phentsize;      // Program header table entry size
    uint16_t e_phnum;          // Program header table entry count
    uint16_t e_shentsize;      // Section header table entry size
    uint16_t e_shnum;          // Section header table entry count
    uint16_t e_shstrndx;       // Section header string table index
};

// ELF64 Section Header structure.
// Each section header describes a section (for example, the .text section contains code).
struct Elf64_Shdr {
    uint32_t sh_name;      // Offset into the section header string table for this section's name
    uint32_t sh_type;      // Section type (e.g., SHT_PROGBITS)
    uint64_t sh_flags;     // Section flags (e.g., executable, writable, etc.)
    uint64_t sh_addr;      // Virtual address of the section in memory
    uint64_t sh_offset;    // File offset where the section data begins
    uint64_t sh_size;      // Size of the section in bytes
    uint32_t sh_link;      // Section header table index link (meaning depends on section type)
    uint32_t sh_info;      // Extra information (depends on section type)
    uint64_t sh_addralign; // Alignment of the section in memory
    uint64_t sh_entsize;   // Size of each entry if the section holds a table of fixed-size entries
};

// Restore the default packing of structure members
#if defined(_MSC_VER) || defined(__GNUC__)
    #pragma pack(pop)
#endif

// Constants for identifying ELF files via e_ident[]
constexpr int EI_MAG0    = 0;  // File identification index 0
constexpr int EI_MAG1    = 1;  // File identification index 1
constexpr int EI_MAG2    = 2;  // File identification index 2
constexpr int EI_MAG3    = 3;  // File identification index 3
constexpr int EI_CLASS   = 4;  // File class: 1 = 32-bit, 2 = 64-bit
constexpr int EI_DATA    = 5;  // Data encoding: 1 = little endian, 2 = big endian
constexpr int EI_VERSION = 6;  // File version
constexpr int EI_OSABI   = 7;  // Operating system/ABI identification

// Expected magic numbers for ELF files
constexpr unsigned char ELFMAG0 = 0x7f;
constexpr unsigned char ELFMAG1 = 'E';
constexpr unsigned char ELFMAG2 = 'L';
constexpr unsigned char ELFMAG3 = 'F';

// Function to check whether a file is an ELF file
// It does this by checking the first 4 bytes of the file for the magic number
bool isELF(const std::vector<uint8_t>& data) {
    if (data.size() < 4) {
        return false;
    }
    return (data[EI_MAG0] == ELFMAG0 &&
            data[EI_MAG1] == ELFMAG1 &&
            data[EI_MAG2] == ELFMAG2 &&
            data[EI_MAG3] == ELFMAG3);
}

// Function to print the details from the ELF header
// It distinguishes between 32-bit and 64-bit headers
void printELFHeader(const std::vector<uint8_t>& data) {
    if (!isELF(data)) {
        std::cout << "Not an ELF file" << std::endl;
        return;
    }
    // e_ident[EI_CLASS] indicates the class:
    // 1 means ELF32; 2 means ELF64.
    uint8_t elfClass = data[EI_CLASS];

    if (elfClass == 1) { // ELF32
        if (data.size() < sizeof(Elf32_Ehdr)) {
            std::cout << "File is too small to be a valid ELF32 file" << std::endl;
            return;
        }
        const Elf32_Ehdr* hdr = reinterpret_cast<const Elf32_Ehdr*>(data.data());
        std::cout << "File is an ELF32 file" << std::endl;
        std::cout << "ELF32 Header:" << std::endl;
        std::cout << "Magic: ";
        for (int i = 0; i < 4; i++)
            std::cout << std::hex << static_cast<int>(hdr->e_ident[i]) << " ";
        std::cout << std::dec << std::endl;

        std::cout << "Class: " << (hdr->e_ident[EI_CLASS] == 1 ? "ELF32" : "Unknown") << std::endl;

        // Data encoding: 1 = little endian, 2 = big endian
        std::cout << "Data: " << (hdr->e_ident[EI_DATA] == 1 ? "little endian" : "big endian") << std::endl;

        // ELF version
        std::cout << "Version: " << hdr->e_ident[EI_VERSION] << std::endl;

        // OS/ABI identification
        std::cout << "OS/ABI: " << static_cast<int>(hdr->e_ident[EI_OSABI]) << std::endl;

        // Object file type (e.g., relocatable, executable, shared object, core file).
        std::cout << "Type: 0x" << std::hex << hdr->e_type << std::dec << std::endl;

        // Machine type (e.g., 0x03 for x86).
        std::cout << "Machine: 0x" << std::hex << hdr->e_machine << std::dec << std::endl;

        // Entry point address
        std::cout << "Entry: 0x" << std::hex << hdr->e_entry << std::dec << std::endl;
    } else if (elfClass == 2) { // ELF64
        if (data.size() < sizeof(Elf64_Ehdr)) {
            std::cout << "File is too small to be a valid ELF64 file" << std::endl;
            return;
        }
        const Elf64_Ehdr* hdr = reinterpret_cast<const Elf64_Ehdr*>(data.data());
        std::cout << "File is an ELF64 file" << std::endl;

        // Print magic numbers.
        std::cout << "Magic: ";
        for (int i = 0; i < 16; i++)
            std::cout << std::hex << static_cast<int>(hdr->e_ident[i]) << " ";
        std::cout << std::dec << std::endl;

        // Print class information.
        std::cout << "Class: " << (elfClass == 2 ? "ELF64" : "Unknown") << std::endl;

        // Data encoding.
        uint8_t dataEncoding = hdr->e_ident[EI_DATA];
        std::cout << "Data: " << (dataEncoding == 1 ? "Little Endian" : "Big Endian") << std::endl;

        // ELF version.
        std::cout << "Version: " << static_cast<int>(hdr->e_ident[EI_VERSION]) << std::endl;

        // OS/ABI.
        std::cout << "OS/ABI: " << static_cast<int>(hdr->e_ident[EI_OSABI]) << std::endl;

        // Object file type.
        std::cout << "Type: 0x" << std::hex << hdr->e_type << std::dec << std::endl;

        // Machine type.
        std::cout << "Machine: 0x" << std::hex << hdr->e_machine << std::dec << std::endl;

        // Entry point address.
        std::cout << "Entry point: 0x" << std::hex << hdr->e_entry << std::dec << std::endl;
    }
    else {
        std::cout << "Unknown ELF class: " << static_cast<int>(elfClass) << std::endl;
    }
}

bool findTextSection(const std::vector<uint8_t>& fileData,
                    const Elf64_Ehdr* elfHeader,
                    uint64_t& textSectionOffset,
                    uint64_t& textSectionSize) {
    if (elfHeader->e_shoff == 0 || elfHeader->e_shnum == 0) {
        std::cout << "No section header table found" << std::endl;
        return false;
    }
    // The section header table is located at the file offset specified by e_shoff.
    // Each entry in the section header table has a size specified by e_shentsize.
    // The number of entries in the section header table is specified by e_shnum.
    // The section header string table index is specified by e_shstrndx.
    uint64_t sectionHeaderOffset = elfHeader->e_shoff;
    uint16_t sectionHeaderSize = elfHeader->e_shentsize;
    uint16_t sectionCount = elfHeader->e_shnum;
    uint16_t sectionStringTableIndex = elfHeader->e_shstrndx;

    const Elf64_Shdr* sectionHeaders = reinterpret_cast<const Elf64_Shdr*>(fileData.data() + sectionHeaderOffset);

    if (sectionStringTableIndex >= sectionCount) {
        std::cout << "Invalid section string table index" << std::endl;
        return false;
    }

    const Elf64_Shdr sectionStringTableHeader = sectionHeaders[sectionStringTableIndex];

    // Pointer to the section header string table.
    const char* sectionStringTable = reinterpret_cast<const char*>(fileData.data() + sectionStringTableHeader.sh_offset);

    // Iterate over the section headers to find the .text section.
    for (uint16_t i = 0; i < sectionCount; i++) {
        const Elf64_Shdr& sh = sectionHeaders[i];
        // sh_name contains the offset in the section header string table where the name of the section is stored.
        const char* sectionName = sectionStringTable + sh.sh_name;
        if (std::strcmp(sectionName, ".text") == 0) {
            textSectionOffset = sh.sh_offset;
            textSectionSize = sh.sh_size;
            std::cout << "Found .text section at offset 0x" << std::hex << textSectionOffset << std::dec
                      << " with size 0x" << std::hex << textSectionSize << std::dec << std::endl;
            return true;
        }
    }
    std::cout << "No .text section found" << std::endl;
    return false;

}


// A helper function to read a 32-bit little-endian integer from a byte vector.
// We assume that the code vector has enough bytes starting at index.
uint32_t read32(const std::vector<uint8_t>& code, size_t index) {
    return  static_cast<uint32_t>(code[index])                  | // Byte 0: least significant
            (static_cast<uint32_t>(code[index+1]) << 8)         | // Byte 1
            (static_cast<uint32_t>(code[index+2]) << 16)        | // Byte 2
            (static_cast<uint32_t>(code[index+3]) << 24);         // Byte 3: most significant

}


// This function disassembles a buffer of code bytes. For demonstration, we only
// recognize two kinds of instructions:
//   - 0xB8-0xBF: "mov reg, imm32" (we map these to 64-bit registers: rax, rcx, ...)
//   - 0x90: "nop"
// All other bytes are simply output as "db" directives.
void disassemble(const std::vector<uint8_t>& code, uint64_t baseAddress = 0) {
    size_t i = 0;

    while (i < code.size()) {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << (baseAddress + i) << ": ";
        uint8_t opcode = code[i];

        if (opcode >= 0xB8 && opcode <= 0xBF) {
            if (i + 4 > code.size()) {
                std::cerr << "Unexpected end of code" << std::endl;
                return;
            }
            uint32_t imm = read32(code, i + 1);

            int reg = opcode - 0xB8;

            const char* reg_names[] = {"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi"};

            std::cout << "mov " << reg_names[reg] << ", 0x" << std::hex << imm << std::endl;

            i+=5;
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
    printELFHeader(code);
    const Elf64_Ehdr* elfHeader = reinterpret_cast<const Elf64_Ehdr*>(code.data());


    // Locate the .text session
    uint64_t textSectionOffset = 0, textSize = 0;
    if (!findTextSection(code, elfHeader, textSectionOffset, textSize)) {
        return 1;
    }

    // Check that the file contains the entire .text section.
    if (textSectionOffset + textSize > code.size()) {
        std::cerr << "Error: .text section exceeds file size.\n";
        return 1;
    }

    // Extract the .text section into its own buffer.
    std::vector<uint8_t> textSection(code.begin() + textSectionOffset, code.begin() + textSectionOffset + textSize);
    std::cout << "Disassembly of .text section:" << std::endl;
    disassemble(textSection, /** baseAddress = */ 0);

    return 0;
}