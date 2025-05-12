cmake_minimum_required(VERSION 3.10)
project(morse C)

# Setze C-Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Füge Compiler-Warnungen hinzu
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Definiere Quellverzeichnis
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Füge ausführbare Datei hinzu
add_executable(morse ${SOURCE_DIR}/morse.c)

# Installation konfigurieren (optional)
install(TARGETS morse DESTINATION bin)