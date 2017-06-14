CC			= g++
CFLAGS		= -g -Wall
EXECUTABLE	= 3d-soft-engine
SRCFILES	:= $(wildcard ./src/*.cpp)
OBJFILES	:= $(SRCFILES:.cpp=.o)

# Rules
.PHONY: $(EXECUTABLE)
$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

%.cpp.o:
	$(CC) $(CFLAGS) -c $<

# Asset Rules
all: $(EXECUTABLE)
	@echo make project

clean:
	@echo cleaning
	-rm -f $(OBJFILES)
	-rm -f $(EXECUTABLE)

run:
	@echo running
	./$(EXECUTABLE)
