#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags



SRCS        := affin.c parser.c
TEST_SRCS	:= test.c
OBJS        := $(SRCS:.c=.o)
TEST_OBJS	:= $(TEST_SRCS:.c=.o)

CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra
PROFILE_FLAGS 	:= -fprofile-arcs -ftest-coverage
TST_LIBS		:= -lcheck -lm -lpthread
COV_LIBS		:= -lgcov -coverage

#------------------------------------------------#
#   PEERS                                        #
#------------------------------------------------#

all: clean uninstall install


install:
	@make clean
	@mkdir build
	@cd Viewer && qmake6 && make && make clean && rm Makefile && cd ../ && mv Viewer/Viewer.app build
	@cp -R build/Viewer.app ~/Desktop/Viewer.app
	@echo "┏=========================================┓"
	@echo "┃        Installed successfully.          ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf build*

test: clean
	cd Viewer && $(CC) $(CFLAGS) $(SRCS) $(TEST_SRCS) $(PROFILE_FLAGS) $(TST_LIBS) -o test
	cd Viewer && ./test

gcov_report: test
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@cd Viewer && lcov -t "viewer" -o test.info -c -d .
	@cd Viewer && genhtml -o report test.info
	@cd Viewer && open ./report/index.html

clean:
	@cd Viewer && rm -rf *.o *.a
	@cd Viewer && rm -rf *.gcno *gcda *.gcov *.info
	@cd Viewer && rm -rf test ./report && rm -rf .qmake.stash && rm -rf .qmake.stash

style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cd Viewer && clang-format -style=Google -n *.c *.h *.cpp

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cd Viewer && clang-format -style=Google -i *.c *.h *.cpp

dist: install
	@rm -rf Dist_Viewer/
	@mkdir Dist_Viewer/
	@mkdir Dist_Viewer/src
	@mv ./build/viewer.app Dist_Viewer/src/
	@tar cvzf Dist_Viewer.tgz Dist_Viewer/
	@rm -rf Dist_Viewer/
	@rmdir build

open:
	@open ./build/viewer.app

dvi:
	@open Meow.md


