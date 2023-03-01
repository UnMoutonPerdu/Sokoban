_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lSDL2

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o disc.o snow.o

# put all the rules to build your applications and tests here (see examples)
example-main: example-main.o
	$(CC) $(CFLAGS) -o example-main example-main.o

example-string: example-string.o
	$(CC) $(CFLAGS) -o example-string example-string.o

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLAGS) -o read-file-formatted read-file-formatted.o

read-file-text: read-file-text.o
	$(CC) $(CFLAGS) -o read-file-text read-file-text.o

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o

test-dummy: test-dummy.o
	$(CC) $(CFLAGS) -o test-dummy test-dummy.o

# the app-ex-loader app
app-ex-loader: app-ex-loader.o
	$(CC) $(CFLAGS) -o app-ex-loader app-ex-loader.o

# the app-ex-gui app. Beware, for graphical applications, you MUST add $(LDFLAGS)!
app-ex-gui: app-ex-gui.o gui.o
	$(CC) $(CFLAGS) -o app-ex-gui app-ex-gui.o gui.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: example-main read-file-formatted read-file-text \
	write-fact test-dummy app-ex-loader app-ex-gui

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q
