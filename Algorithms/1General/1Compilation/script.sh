g++ -std=gnu++17 -Wall -Wextra -Wconversion -fsanitize=undefined,address -D_GLIBCXX_DEBUG program.cpp
./a.out < input.in > output.out
