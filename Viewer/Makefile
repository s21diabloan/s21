.PHONY: all clean rebuild install tests
# Определение переменных
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets` -lGL -lGLU -lglut

SRC_DIR := .
EXTENSIONS := cpp h
find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))
ADDRESS_FILE := address.txt

# Исходные файлы и объектные файлы
SOURCES = \
    main.cpp \
    mainwindow.cpp \
    objcontroller.cpp \
    objmodel.cpp \
    objview.cpp

OBJECTS = $(SOURCES:.cpp=.o)

# Имя исполняемого файла
TARGET = 3D

# Правило по умолчанию
all: install dvi tests

# Правило для создания исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

# Правило для компиляции .cpp файлов в .o файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки промежуточных файлов
clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -rf build/
	rm -rf docs
	rm -rf 3D.pro.user
	cd tests && make clean

# Правило для компиляции и очистки
rebuild: clean all

# Цель установки и сборки проекта
install:
	clear
	@mkdir -p build
	@cd build && qmake ../3D.pro && make

uninstall:
	rm -rf build

dvi:
	doxygen dox_conf.dox
	open docs/html/index.html

dist:
	@mkdir -p build
	@cd build && qmake ../3D.pro && make
	rm -rf 3D_Archived/
	mkdir -p 3D_Archived/src
	cp -r ./build/3D 3D_Archived/src/
	tar cvzf 3D_Archived.tgz 3D_Archived/
	rm -rf 3D_Archived

style:
	clang-format -i -style=google *.cpp *.h *.hpp
	clang-format -i -style=google tests/*.cpp
	clang-format -i -style=google sourses/*.cpp sourses/*.h
	clang-format -i -style=google giflib/*
.PHONY: style

clang:
	clang-format -n -style=google $(SRC_FILES)
.PHONY: clang

run:
	@./build/3D


tests:
	cp objmodel.cpp tests/objmodel.cpp
	cp objmodel.h tests/objmodel.h
	cd tests && make test

gcov_report:
	cp objmodel.cpp tests/objmodel.cpp
	cp objmodel.h tests/objmodel.h
	cd tests && make gcov_report

leaks: tests
	cp objmodel.cpp tests/objmodel.cpp
	cp objmodel.h tests/objmodel.h
	cd tests && make leaks
