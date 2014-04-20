HW_NAME = project
HW_FILES = Makefile $(SRC) $(HDR)
HW_TURNIN_DIR  = solitaire
HW_SCRATCH_DIR = scratch
TEST_HW_CMD =

TGT = solitaire

CC     = g++
CFLAGS = -g -Wall -Wextra -std=c++11
LFLAGS =
LDLIBS =

HDR = $(wildcard *.h)
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

### RULES ###
.PHONY: clean all todolist submit check

all: $(TGT)

# generate dependency files (*.d) with only user header files
%.d: %.cpp
	$(CC) $(CFLAGS) -c -MMD $<

# include generated compilation dependencies
-include $(DEP)

# compile
%.o: %.cpp %.d Makefile
	$(CC) $(CFLAGS) -c $< -o $@

# link
$(TGT): $(OBJ)
	$(CC) $(LFLAGS) $(LDLIBS) $(OBJ) -o $(TGT)

clean:
	rm -f $(OBJ) $(DEP) $(TGT)

todolist:
	@echo "Checking for \"TODO\" and \"FIXME\" in $(SRC) $(HDR)..."; \
	for file in $(SRC) $(HDR); do					 \
		fgrep -Hni -e TODO -e FIXME $$file;			 \
	done;								 \
	exit 0;

submit:
	rm -rvf $(HW_TURNIN_DIR) $(HW_SCRATCH_DIR);		\
	mkdir $(HW_TURNIN_DIR) $(HW_SCRATCH_DIR);		\
	cp $(HW_FILES) $(HW_TURNIN_DIR);			\
	cp $(HW_FILES) $(HW_SCRATCH_DIR);			\
	make -C $(HW_SCRATCH_DIR);				\
	$(TEST_HW_CMD)						\
	rm -rvf $(HW_SCRATCH_DIR);				\
	turnin -v -c cis190 -p $(HW_NAME) $(HW_TURNIN_DIR)

check:
	turnin -v -c cis190 -p $(HW_NAME)

compare:
	for file in $(HW_FILES); do			\
		diff -q $$file $(HW_TURNIN_DIR);	\
	done;
