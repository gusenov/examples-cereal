#!/bin/bash

EXE_FILE="./program.out"

[ -f "$EXE_FILE" ] && rm "$EXE_FILE"

c++ -Wall -I '../cereal-1.2.2/include/' `find . -name "*.cpp" | tr '\n' ' '` -o "$EXE_FILE" \
  && "$EXE_FILE"
