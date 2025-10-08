cmake_minimum_required(VERSION 3.16)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(proc-clone3 proc-clone3/main.c)
add_executable(shell-or shell-or/main.c)
add_executable(cpu-sort cpu-sort/main.c)
add_executable(ema-replace-str ema-replace-str/main.c)
