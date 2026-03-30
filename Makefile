CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = hw12

TESTFLAGS = -DTEST_BUILDTREE

all: main.c tree.c
	$(GCC) $(TESTFLAGS) -o $(EXEC) main.c tree.c

testall: test1 test2 test3 test4 test5 test6

test1: all
	./$(EXEC) testcases/test1in testcases/test1post output1
	diff -w output1 expected/expected1

test2: all
	./$(EXEC) testcases/test2in testcases/test2post output2
	diff -w output2 expected/expected2

test3: all
	./$(EXEC) testcases/test3in testcases/test3post output3
	diff -w output3 expected/expected3

test4: all
	./$(EXEC) testcases/test4in testcases/test4post output4
	diff -w output4 expected/expected4

test5: all
	./$(EXEC) testcases/test5in testcases/test5post output5
	diff -w output5 expected/expected5

test6: all
	./$(EXEC) testcases/test6in testcases/test6post output6
	diff -w output6 expected/expected6

valgrind: all
	valgrind -s --errors-for-leak-kinds=all --leak-check=full --show-leak-kinds=all --error-exitcode=2 ./$(EXEC) 5000 17 > /dev/null

clean:
	rm -f $(EXEC)
	rm -f *.o
	rm -f output*
