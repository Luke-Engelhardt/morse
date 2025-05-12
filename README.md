# morse

A command-line Morse code translator written in C. This tool allows you to encode plain text into Morse code and decode Morse code back into human-readable text. It supports letters, digits, and a range of common special characters.

---

## Features

- Encode text into Morse code  
- Decode Morse code back into text  
- Read input from files or command line  
- Write output to files  
- Display help and author information  

---

## Supported Characters

- **Letters**: A–Z (case-insensitive)  
- **Digits**: 0–9  
- **Specials**: `. , ? ! / ( ) & : ; = + - " @ _`

---

## Build Instructions

### Requirements

- CMake (version 3.10 or higher)  
- A C compiler (e.g., GCC, Clang)

### Steps to Build

1. Clone the repository or place the `morse.c` and `CMakeLists.txt` in your project folder.
2. In the terminal, navigate to the project directory and create a build directory:

   ```bash
   mkdir build
   cd build

3. Run CMake to configure the project:
   ```bash
   cmake ..
4. Build the project:
   ```bash
   make
5. Clean the build files:
   ```bash
   make clean


## Usage
```bash
./morse [options] [input]

### Options:
Option	Description
- -e [text]	Encode text to Morse code
- -d [morse]	Decode Morse code to text
- -ef [file]	Encode text read from a file
- -df [file]	Decode Morse code read from a file
- -eo [file] [text]	Encode text and write Morse code to output file
- -do [file] [morse]	Decode Morse and write text to output file
- -h	Display usage information
- --programmer-info	Display author/program information
