CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DTEST_INTEGRATE -DRUN_INTEGRATE
LIBS = -lm
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = hw4

FUNCS = func1.c func2.c func3.c func4.c func5.c
SRCS =  hw4.c integrator-hw4.c $(FUNCS)

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
$(EXEC): $(SRCS) hw4.h
	$(GCC) $(SRCS) -o $(EXEC) $(LIBS)

TESTS = 1 2 3 4

testall: $(EXEC)
	$(foreach i, $(TESTS), ./$(EXEC) testcases/test$(i) testcases/output$(i);)	

testgen: testgen.c integrator-hw4.c $(FUNCS) 
	$(GCC) testgen.c integrator-hw4.c $(FUNCS) -o testgen $(LIBS)

testcases: testgen hw4.h
	/bin/rm -f -r testcases
	mkdir testcases
	./testgen testcases/test1 -5.0 10.5 100000
	./testgen testcases/test2 -1.0 23.0 100000
	./testgen testcases/test3 5.8 37.9 100000
	./testgen testcases/test4 8.0 102.5 100000

.c.o: 
	$(GCC) -c $*.c 

clean:
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f hw4 hw4.prof
