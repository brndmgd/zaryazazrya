SRCS = $(wildcard *_test.c)
PRGS = $(patsubst %.c, %, $(SRCS))

test: $(PRGS)
	./stack_test

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


# # ---

# quadratic.o: quadratic.c quadratic.h
# 	gcc -g -c quadratic.c -o quadratic.o 

# quadratic.a: quadratic.o
# 	ar rc quadratic.a quadratic.o

# quadratic_test.o: quadratic_test.c
# 	gcc -g -c quadratic_test.c -o quadratic_test.o

# quadratic_test: quadratic_test.o quadratic.a
# 	gcc -g -static -o quadratic_test quadratic_test.o quadratic.a -lm

# # ---

# integrals.o: integrals.c integrals.h
# 	gcc -g -c integrals.c -o integrals.o

# integrals.a: stack.o
# 	ar rc integrals.a integrals.o

# integrals_test.o: integrals_test.c
# 	gcc -g -c integrals_test.c -o integrals_test.o

# integrals_test: integrals_test.o integrals.a
# 	gcc -g -static -o integrals_test integrals_test.o integrals.a

# # ---

# list.o: list.c list.h
# 	gcc -g -c list.c -o list.o

# list.a: stack.o
# 	ar rc list.a list.o

# list_test.o: list_test.c
# 	gcc -g -c list_test.c -o list_test.o

# list_test: list_test.o list.a
# 	gcc -g -static -o list_test list_test.o list.a

# # ---

# stack.o: stack.c stack.h
# 	gcc -g -c stack.c -o stack.o

# stack.a: stack.o
# 	ar rc stack.a stack.o

# stack_test.o: stack_test.c
# 	gcc -g -c stack_test.c -o stack_test.o

# stack_test: stack_test.o stack.a
# 	gcc -g -static -o stack_test stack_test.o stack.a

# # ---
