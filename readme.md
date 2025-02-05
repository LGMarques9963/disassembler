# 🕵️‍♂️ Reverse Disassembler with C++: A Custom Disassembler for Reverse Engineering & Malware Analysis

## 📌 About This Project
This repository is a C++ implementation of a custom disassembler designed to decode machine code (currently focusing on ELF64 binaries) into human-readable assembly instructions. This project serves as a portfolio piece for cybersecurity roles—especially reverse engineering and malware analysis.

Built using modern C++ (C++23), the tool emphasizes modular, maintainable code using data-driven design patterns (such as lookup tables and dispatch tables) for instruction decoding. It’s an educational resource for learning how to translate raw binary code back into assembly language.

---

## 🚀 Features
- ✅ **Modular Design:** Uses dispatch tables for opcode decoding, making it easy to add new instructions.
- ✅ **ELF64 Support:** Designed to analyze ELF64 binaries and extract the `.text` section.
- ✅ **Instruction Decoders:** Currently supports:
  - `mov reg, imm32` (e.g., `mov rax, imm32`)
  - `add reg, reg` (using a ModR/M byte)
  - `nop`
- ✅ **Clean & Maintainable:** Focus on readability and best practices in modern C++.
- ✅ **Cybersecurity Relevance:** A practical tool for reverse engineering, malware analysis, and binary forensics.

---

## 🛠️ Implemented Instructions
| **Instruction**           | **Description**                                                                 |
|---------------------------|---------------------------------------------------------------------------------|
| **mov reg, imm32**        | Moves a 32-bit immediate value into a register (e.g., `mov rax, imm32`).         |
| **add reg, reg**          | Adds the value in one register to another using a ModR/M byte for register-to-register encoding. |
| **nop**                   | No Operation – does nothing (1-byte instruction).                              |
| **[Others]**              | Unknown opcodes are printed as data bytes (`db` directive).                     |

---

## 🚀 Why This Project Matters
- **🔍 Reverse Engineering & Malware Analysis:**  
  Gain hands-on experience with binary analysis—a critical skill in reverse engineering and cybersecurity.
  
- **⚡ C++ Proficiency:**  
  Demonstrates modern C++ programming with efficient and modular code.
  
- **🧩 Understanding Machine Code:**  
  Learn how instructions are encoded and how to translate raw binary into assembly language.
  
- **🎯 Cybersecurity Portfolio:**  
  This project highlights skills in reverse engineering and malware analysis, which are highly sought after in cybersecurity roles.

---

## 📂 Project Structure
```
Reverse-Disassembler/
├── README.md               # This documentation
├── src
│   ├── disassembler.cpp    # Core disassembler logic (dispatch tables, decoders, etc.)
│   ├── disassembler.h      # Header definitions for disassembler functionality
│   └── main.cpp            # Entry point for testing the disassembler
├── tests
│   └── test_disassembler.cpp  # Unit tests for disassembler components
├── docs
│   └── design.md           # Design documentation and implementation details
└── CMakeLists.txt          # Build configuration for CMake
```

---

## ⚙️ Building and Running the Project
### **🔹 Prerequisites**
- C++23 Compiler (GCC 11+, Clang 14+, MSVC)
- CMake (for easy compilation)
- Git (for version control)

### **🔹 Build Instructions**
```bash
# Clone the repository
git clone https://github.com/YourUsername/Reverse-Disassembler.git
cd Reverse-Disassembler

# Create a build directory and navigate into it
mkdir build && cd build

# Configure the project with CMake
cmake ..

# Build the project
make

# Run the disassembler
./ReverseDisassembler
```

---

## 🛡️ Cybersecurity Relevance
This project is directly applicable to:
- **Reverse Engineering:** Dissect compiled binaries to recover underlying assembly instructions.
- **Malware Analysis:** Gain insights into how malicious code is structured and how to analyze it.
- **Binary Forensics:** Understand the inner workings of executables and their vulnerabilities.
- **Cybersecurity Roles:** Demonstrates skills useful in penetration testing, red teaming, and threat analysis.

---

## 🧪 Testing the Disassembler
Unit tests are included to ensure the accuracy and robustness of each instruction decoder.

To run tests:
```bash
cd build
ctest --verbose
```

---

## 🌌 Future Enhancements
- ✔️ Expand support for additional opcodes and addressing modes.
- ✔️ Add support for other binary formats (PE, Mach-O, raw binaries).
- ✔️ Implement full 64-bit immediate decoding (e.g., `movabs`).
- ✔️ Integrate a recursive-descent parser for multi-byte opcodes.

---

## 📄 Credits & Resources
- **Intel® 64 and IA-32 Architectures Software Developer’s Manual** – [Intel SDM](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- **AMD64 Architecture Programmer’s Manual** – [AMD Developer Guides](https://developer.amd.com/resources/developer-guides-manuals/)
- **OSDev Wiki on ELF** – [OSDev ELF](https://wiki.osdev.org/ELF)
- **C++ Documentation:** [cppreference.com](https://en.cppreference.com/)

---

## 🤝 Contributing
Contributions are welcome! To contribute:
- **Open an Issue:** Report bugs or suggest features.
- **Fork & Pull Request:** Enhance functionality or documentation.
- **Improve Tests:** Add more unit tests for instruction decoders.

---

## 🔒 Disclaimer
This repository is for **educational purposes only**. It is intended as a learning tool and portfolio piece for reverse engineering and malware analysis. **Do not use this tool for unauthorized or illegal analysis.**

---

## 💌 Contact
**📌 Author:** Lorran Marques<br>
**🌐 LinkedIn:** [Lorran Marques](https://www.linkedin.com/in/lgmarques/)  
**🔍 GitHub:** [LGMarques9963](https://github.com/LGMarques9963)  
**📧 Email:** lorran9963@gmail.com

---

### **🔍 Analyze. Reverse Engineer. Secure the Future. 🚀**

If you find this project helpful, please consider giving it a ⭐ on GitHub!