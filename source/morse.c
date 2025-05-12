#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Morse code definitions
const char* MORSE_TABLE[] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--.."   // Z
};

const char* MORSE_DIGITS[] = {
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};

const char* MORSE_SPECIAL[] = {
    ".-.-.-", // .
    "--..--", // ,
    "..--..", // ?
    "-.-.--", // !
    "-..-.",  // /
    "-.--.",  // (
    "-.--.-", // )
    ".-...",  // &
    "---...", // :
    "-.-.-.", // ;
    "-...-",  // =
    ".-.-.",  // +
    "-....-", // -
    ".-..-.", // "
    ".--.-.", // @
    "..--.-"  // _
};

const char SPECIAL_CHARS[] = ".,?!/()&:;=+-\"@_";

// Function to convert a character to Morse code
const char* charToMorse(char c) {
    if (isalpha(c)) {
        return MORSE_TABLE[toupper(c) - 'A'];
    } else if (isdigit(c)) {
        return MORSE_DIGITS[c - '0'];
    } else {
        // Check for special characters
        for (int i = 0; i < strlen(SPECIAL_CHARS); i++) {
            if (c == SPECIAL_CHARS[i]) {
                return MORSE_SPECIAL[i];
            }
        }
    }
    return NULL; // Character not supported
}

// Function to convert Morse code to a character
char morseToChar(const char* morse) {
    // Check letters
    for (int i = 0; i < 26; i++) {
        if (strcmp(morse, MORSE_TABLE[i]) == 0) {
            return 'A' + i;
        }
    }
    
    // Check digits
    for (int i = 0; i < 10; i++) {
        if (strcmp(morse, MORSE_DIGITS[i]) == 0) {
            return '0' + i;
        }
    }
    
    // Check special characters
    for (int i = 0; i < strlen(SPECIAL_CHARS); i++) {
        if (strcmp(morse, MORSE_SPECIAL[i]) == 0) {
            return SPECIAL_CHARS[i];
        }
    }
    
    return '\0'; // Morse code not recognized
}

// Function to encode text to Morse code
void encodeToMorse(const char* text, FILE* output) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            fprintf(output, "/ "); // Word separator
        } else {
            const char* morse = charToMorse(text[i]);
            if (morse != NULL) {
                fprintf(output, "%s ", morse);
            }
        }
    }
    fprintf(output, "\n");
}

// Function to decode Morse code to text
void decodeMorse(const char* morse, FILE* output) {
    char buffer[10]; // Buffer to store a single Morse code
    int bufferIndex = 0;
    
    for (int i = 0; i <= strlen(morse); i++) {
        if (morse[i] == ' ' || morse[i] == '\0') {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                if (strcmp(buffer, "/") == 0) {
                    fprintf(output, " "); // Word separator
                } else {
                    char c = morseToChar(buffer);
                    if (c != '\0') {
                        fprintf(output, "%c", c);
                    }
                }
                bufferIndex = 0;
            }
        } else {
            buffer[bufferIndex++] = morse[i];
        }
    }
    fprintf(output, "\n");
}

// Function to read from a file
char* readFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate memory for the content
    char* content = (char*)malloc(fileSize + 1);
    if (content == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    // Read the file content
    size_t bytesRead = fread(content, 1, fileSize, file);
    content[bytesRead] = '\0';
    
    fclose(file);
    return content;
}

// Function to display help information
void displayHelp() {
    printf("Morse Code Translator\n");
    printf("Usage:\n");
    printf("  morse -e [text]        Encode text to Morse code\n");
    printf("  morse -d [morse]       Decode Morse code to text\n");
    printf("  morse -ef [file]       Encode text from file\n");
    printf("  morse -df [file]       Decode Morse code from file\n");
    printf("  morse -eo [file] [text]  Encode text and save to file\n");
    printf("  morse -do [file] [morse] Decode Morse code and save to file\n");
    printf("  morse -h               Display this help information\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: Insufficient arguments\n");
        displayHelp();
        return 1;
    }
    
    // Check for help option
    if (strcmp(argv[1], "-h") == 0) {
        displayHelp();
        return 0;
    }
    
    // Process command line arguments
    if (strcmp(argv[1], "-e") == 0) {
        // Encode text from command line
        if (argc < 3) {
            printf("Error: No text provided for encoding\n");
            return 1;
        }
        encodeToMorse(argv[2], stdout);
    } 
    else if (strcmp(argv[1], "-d") == 0) {
        // Decode Morse code from command line
        if (argc < 3) {
            printf("Error: No Morse code provided for decoding\n");
            return 1;
        }
        decodeMorse(argv[2], stdout);
    } 
    else if (strcmp(argv[1], "-ef") == 0) {
        // Encode text from file
        if (argc < 3) {
            printf("Error: No input file specified\n");
            return 1;
        }
        char* content = readFromFile(argv[2]);
        if (content != NULL) {
            encodeToMorse(content, stdout);
            free(content);
        } else {
            return 1;
        }
    } 
    else if (strcmp(argv[1], "-df") == 0) {
        // Decode Morse code from file
        if (argc < 3) {
            printf("Error: No input file specified\n");
            return 1;
        }
        char* content = readFromFile(argv[2]);
        if (content != NULL) {
            decodeMorse(content, stdout);
            free(content);
        } else {
            return 1;
        }
    } 
    else if (strcmp(argv[1], "-eo") == 0) {
        // Encode text and save to file
        if (argc < 4) {
            printf("Error: Missing output file or text\n");
            return 1;
        }
        FILE* outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            printf("Error: Cannot open output file\n");
            return 1;
        }
        encodeToMorse(argv[3], outputFile);
        fclose(outputFile);
    } 
    else if (strcmp(argv[1], "-do") == 0) {
        // Decode Morse code and save to file
        if (argc < 4) {
            printf("Error: Missing output file or Morse code\n");
            return 1;
        }
        FILE* outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            printf("Error: Cannot open output file\n");
            return 1;
        }
        decodeMorse(argv[3], outputFile);
        fclose(outputFile);
    } 
    else {
        printf("Error: Invalid option\n");
        displayHelp();
        return 1;
    }
    
    return 0;
}