CC=gcc -std=c11 -D_GNU_SOURCE -g
CFLAGS=-c -Wall -Wextra -Werror
TEST_FLAGS=-lcheck -lm -lpthread
GCOV_FLAGS=--coverage -Wall -Wextra -Werror
SOURCES=$(wildcard s21_*.c)
OBJECTS=$(SOURCES:.c=.o)
TESTS_SOURCES=test_main.c $(wildcard tests/*.c)
TESTS_OBJECTS=$(TESTS_SOURCES:.c=.o)
EXECUTABLE=s21_matrix

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif

all: test

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

rebuild: clean all

s21_matrix.a: $(OBJECTS)
	ar -rc s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a

style:
	clang-format -n *.c *.h tests/*.c tests/*.h

beautify:
	clang-format -i *.c *.h tests/*.c tests/*.h

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(TESTS_OBJECTS) s21_matrix.a *.gcov *.gcno *.gcda *.info test jeannakr *.dSYM

test: $(TESTS_OBJECTS) s21_matrix.a
	$(CC) $^ -o test $(TEST_FLAGS)
	./test

gcov_report: $(TESTS_OBJECTS)
	$(CC) $(GCOV_FLAGS) $(TESTS_OBJECTS) $(SOURCES) $(TEST_FLAGS) -o test
	./test
	gcov *.gcno
	lcov -t "s21_matrix" -o s21_matrix.info -c -d . --rc lcov_coverage
	genhtml -o report s21_matrix.info --rc lcov_coverage
	open report/index.html

leaks: test
	leaks -atExit -- ./test

vlagrind: test
	valgring --leak-check=full ./test

# jeannakr: clean
# 	$(CC) $(CFLAGS) $(SOURCES) -o jeannakr
# 	./jeannakr
