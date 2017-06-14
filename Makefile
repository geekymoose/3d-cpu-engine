CC			= c++
CF_FLAGS	= -g -Wall
LIBS_FLAGS	=
EXEC_FILE	= 3d-soft-engine
OBJS_FILE	:= $(wildcard ./src/*.cpp)

# General
.PHONY: $(EXEC_FILE)
$(EXEC_FILE): $(OBJS_FILE)
	$(CC) $(CF_FLAGS) $(LIBS_FLAGS) $^ -o $(EXEC_FILE)

# Asset Rules
.PHONY: all
all: $(EXEC_FILE)
	@echo make project

.PHONY: clean
clean:
	@echo cleaning
	-rm -f *.o
	-rm -f $(EXEC_FILE)

.PHONY: run
run:
	@echo running
	./$(EXEC)
