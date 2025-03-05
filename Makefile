SRCS = $(wildcard *_test.c)
PRGS = $(patsubst %.c, %, $(SRCS))

test: $(PRGS)
	./integral_test

clear: 
	rm -rf *.o *.a *_test

fmt: 
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

%.o: %.c %.h
	gcc -g -c $< -o $@

%.a: %.o
	ar rc $@ $^

%_test.o: %_test.c
	gcc -g -c $^ -o $@

%_test: %_test.o %.a
	gcc -g -static -o $@ $^ -lm
