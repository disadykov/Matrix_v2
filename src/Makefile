# Compiler settings
CPP = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror
LDFLAGS =
LIB_NAME = s21_matrix_oop.a
LIB_FILES = s21_matrix_oop.o
TESTFILE = s21_matrixplus

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin) # macOS
		LIBFLAGS = -fno-elide-constructors 
		GTEST_LIB = -lgtest
		LEAK = /leaks_tests/mac_leak.sh
		LDFLAGS += -fprofile-arcs --coverage
		OPEN_COMMAND = open report/html/index.html
else # Linux
		LIBFLAGS = -lstdc++
		GTEST_LIB = -lgtest -pthread
		LEAK = /leaks_tests/linux_leak.sh
		LDFLAGS += --coverage
		OPEN_COMMAND = xdg-open report/html/index.html
endif

all: test

check:
	@echo
	@echo --------------------------------- CHECK START ---------------------------------------
	clang-format -n --style=Google *.cpp
	clang-format -n --style=Google *.h
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.h
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp
	@echo --------------------------------- CHECK END -----------------------------------------
	@echo

$(LIB_FILES):
	$(CPP) -c $(CPPFLAGS) $(LIBFLAGS) s21*.cpp

$(LIB_NAME): $(LIB_FILES)
	ar rcs $(LIB_NAME) $<
	ranlib $(LIB_NAME)
	rm -rf *.o

clean:
	clear
	rm -rf *.o *.a *.gcno .clang-format *.out main test_matrix_oop coverage.info report *.gcda *.info ./gcov_report *.gcov

develop: clean check $(LIB_NAME)
	@echo --------------------------------- DEVELOPMENT START ---------------------------------------
	$(CPP) -c $(CPPFLAGS) main.cpp
	$(CPP) $(CPPFLAGS) *.o *.a -o main
	@echo
	./main
	@echo --------------------------------- DEVELOPMENT END -----------------------------------------
	@echo

test: clean $(LIB_NAME)
	@echo
	@echo --------------------------------- TEST START ---------------------------------------
	$(CPP) -c $(CPPFLAGS) test_matrix_oop.cpp $(LDFLAGS)
	$(CPP) $(CPPFLAGS) *.o *.a -o test_matrix_oop $(GTEST_LIB) $(LDFLAGS)
	./test_matrix_oop
	@echo --------------------------------- TEST END -----------------------------------------
	@echo

leak: test
	.$(LEAK)

gcov_report: clean
	mkdir -p report
	$(CPP) $(CPPFLAGS) $(LDFLAGS) *oop.cpp -o gcov_report $(GTEST_LIB) $(LIBFLAGS)
	./gcov_report
	lcov --capture --directory . --output-file report/coverage.info
	lcov --remove report/coverage.info '/usr/*' '*/gtest/*' '*/test/*' '*/v1/*' --output-file report/coverage_filtered.info
	genhtml report/coverage_filtered.info --output-directory report/html
	$(OPEN_COMMAND)
