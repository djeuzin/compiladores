CC = gcc
PROGRAM = cross
WORKINGDIR = .
INCDIRS=.
DEPFLAGS=-MP -MD
CFILES=$(foreach D,$(WORKINGDIR),$(wildcard $(D)/*.c))
OFILES=$(patsubst %.c,%.o,$(CFILES))
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OFILES)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o