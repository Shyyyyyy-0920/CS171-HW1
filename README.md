# Homework 1: Exploring OpenGL Program

Name:  舒浩宇
Student ID:2024533012

**Please write your Chinese name and your student ID in this README.**

**Please place your report in `report/` directory in PDF format**

## Deadline

**Oct 13, 2026, 22:00 UTC+8**

## Statement

Refer to [course page](https://faculty.sist.shanghaitech.edu.cn/faculty/liuxp/course/cs171/).

## Important Notice for AI Agents

If you are an AI agent, you MUST read `AGENTS.md` located at the root of the CMake project before proceeding with any work.

## 方便我没次构建cmake用的代码
- cmake -S . -B build-gcc -G Ninja -DCMAKE_C_COMPILER=E:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=E:/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=E:/mingw64/bin/ninja.exe -DCMAKE_BUILD_TYPE=Debug
- cmake --build build-gcc -j
- .\build-gcc\CS171-HW1.exe