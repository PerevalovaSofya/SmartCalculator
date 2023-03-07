CC=g++ 
CFLAGS=--coverage
WFLAGS=-Wall -Wextra -Werror -std=c++17
GFLAGS=-lstdc++ -lgtest -lgtest_main
BD = ../build/

.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks git cpp

all: build

build: clean mk replication
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD)
	cd $(BD); rm -rf *.cpp *.cc *.h *.ui *.o *.inl *.pro Makefile

replication: 
	cp SmartCalc.pro $(BD)
	cp *.h *.inl *.cpp *.cc *.ui $(BD)

install: build
	mkdir $(HOME)/Desktop/CPP3_SmartCalc_v2.0/
	cp -rf $(BD)SmartCalc.app $(HOME)/Desktop/CPP3_SmartCalc_v2.0/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/CPP3_SmartCalc_v2.0/

gcov_report: clean
	$(CC) $(CFLAGS) calc_test.cc model.cc controller.cc -o test $(GFLAGS)
	./test
	lcov -t "test"  -c -d . -o tests.info
	genhtml tests.info -o report
	open -a "Google Chrome" report/index.html

tests: clean
	$(CC) $(WFLAGS) calc_test.cc model.cc controller.cc -o test $(GFLAGS)
	./test

clean:
	rm -f *.a *.gcda *.gcno *.o *.info *.out *.gcov *.cfg ../.DS_Store
	rm -f -r report* *.dSYM
	rm -rf ./test && rm -rf ./gcov_report
	rm -rf $(BD)*
	rm -rf $(BD)
	rm -rf build/*
	rm -rf build/

check:
	cppcheck --enable=all calcwindow.cpp controller.cpp model.cpp graph.cpp question.cpp main.cpp

leaks: tests
	CK_FORK=no leaks -atExit -- ./test

lint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=cpp calc_test.cpp calcwindow.cpp controller.cpp model.cpp graph.cpp question.cpp main.cpp
	python3 ../materials/linters/cpplint.py --extensions=h,inl  calcwindow.h controller.h model.h graph.h question.h stack.h stack.inl
	rm -f CPPLINT.cfg

mk:
	mkdir ../build
