CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = personality 

all: main.c personality.c
	$(GCC) main.c personality.c -o $(EXEC)

testall: test1 test2 test3 test4 test5 test6 test7 test8

test1: all
	./$(EXEC) inputs/input_1.txt > output1.txt
	diff output1.txt expected/expected_1.txt

test2: all
	./$(EXEC) inputs/input_2.txt > output2.txt
	diff output2.txt expected/expected_2.txt

test3: all
	./$(EXEC) inputs/input_3.txt > output3.txt
	diff output3.txt expected/expected_3.txt

test4: all
	./$(EXEC) inputs/input_4.txt > output4.txt
	diff output4.txt expected/expected_4.txt

test5: all
	./$(EXEC) inputs/input_5.txt > output5.txt
	diff output5.txt expected/expected_5.txt

test6: all
	./$(EXEC) inputs/input_6.txt > output6.txt
	diff output6.txt expected/expected_6.txt

test7: all
	./$(EXEC) inputs/input_7.txt > output7.txt
	diff output7.txt expected/expected_7.txt

test8: all
	./$(EXEC) inputs/input_8.txt > output8.txt
	diff output8.txt expected/expected_8.txt

clean:
	rm -f $(EXEC)
	rm -f *.o
	rm -f output*