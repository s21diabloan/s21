.PHONY: all clean test leaks gcov_report rebuild

CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC

# Автоматическое получение путей с помощью qmake
QT_INCLUDE := $(shell qmake -query QT_INSTALL_HEADERS | tr -d ' ')
QT_LIBS := $(shell qmake -query QT_INSTALL_LIBS | tr -d ' ')

QT_FLAGS = -L$(QT_LIBS) -lQt6Core -lQt6Gui
GTEST_FLAGS = -lgtest
GCOV_FLAG = -fprofile-arcs -ftest-coverage
NAME = s21_viewer
TESTFILE = test
LIB_NAME = objmodel

OS = $(shell uname)
ifeq ($(OS), Linux)
    LIBFLAGS = -lstdc++ `pkg-config --cflags --libs gtest`
else
    LIBFLAGS = -lstdc++ -lm -lgtest
endif

rebuild: clean all

check: leaks gcov_report 

all: $(TESTFILE) check

$(TESTFILE):
	$(CC) $(LIB_NAME).cpp tests.cpp -I$(QT_INCLUDE)/QtCore -I$(QT_INCLUDE) $(FLAGS) $(QT_FLAGS) $(GCOV_FLAG) -o $(TESTFILE) $(LIBFLAGS)
	LD_LIBRARY_PATH=$(QT_LIBS):$$LD_LIBRARY_PATH ./$(TESTFILE)

gcov_report: $(TESTFILE)
	mkdir -p report
	lcov --capture --directory . --output-file test.info --no-external
	lcov --extract test.info "*objmodel.cpp" -o filtered_test.info
	genhtml -o report filtered_test.info

clean:
	rm -f *.o *.a *.gcno *.gcda *.info a.out $(TESTFILE)
	rm -rf report/
	rm -rf objmodel.cpp objmodel.h

leaks:
ifeq ($(OS), Linux)
	LD_LIBRARY_PATH=$(QT_LIBS):$$LD_LIBRARY_PATH valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TESTFILE)
else
	LD_LIBRARY_PATH=$(QT_LIBS):$$LD_LIBRARY_PATH leaks -atExit -- ./$(TESTFILE)
endif