#!/usr/bin/make -f

name := "$(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")"
std := c++1z
warnflags := -Wall -Wextra -Wpedantic
binflags := -O2
dbgflags := -ggdb3 -Og
idirs := -I.
ldirs := 
bindefines := -UDEBUG
dbgdefines := -DDEBUG
buildopts := 
linkflags := -lsfml-graphics -lsfml-window -lsfml-system

gcc:
	mkdir -p bin
	g++ -std=${std} ${binflags} ${warnflags} ${idirs} ${ldirs} ${bindefines} ${buildopts} -o bin/${name} $(shell find src -iname "*.cpp") ${linkflags}
llvm:
	mkdir -p bin
	clang++ -std=${std} ${binflags} ${warnflags} ${idirs} ${ldirs} ${bindefines} ${buildopts} -o bin/${name} $(shell find src -iname "*.cpp") ${linkflags}
dbg:
	mkdir -p bin
	g++ -std=${std} ${dbgflags} ${warnflags} ${idirs} ${ldirs} ${dbgdefines} ${buildopts} -o bin/${name} $(shell find src -iname "*.cpp") ${linkflags}
lldbg:
	mkdir -p bin
	clang++ -std=${std} ${dbgflags} ${warnflags} ${idirs} ${ldirs} ${dbgdefines} ${buildopts} -o bin/${name} $(shell find src -iname "*.cpp") ${linkflags}
clean:
	rm -rf bin
.PHONY:	bin clang dbg clangdbg clean