LDFLAGS = -I include -l SDL2-2.0.0
CXX = gcc

PROG = game

OBJS = helper.o color.o mathematics.o graphics.o r2d.o main.o

all: $(PROG)

%.o: r2d/%.c r2d/%.h main.c
	$(CXX) -c $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LDFLAGS)

clean:
	rm $(PROG) *.o
