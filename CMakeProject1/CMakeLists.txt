# CMakeList.txt: projekt CMake dla elementu CMakeProject1, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
PROJECT(Emedia CXX)
cmake_minimum_required (VERSION 3.8)

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (CMakeProject1 "main.cpp" "main.h" RSA.hpp jpg.cpp jpg.h)


# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
