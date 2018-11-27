COMP=gcc
CFILES=$(wildcard *.c)
HFILES=$(wildcard *.h)
OFILES=$(CFILES:.c=.o)
FINAL=prog
LINKFLAGS = -lm -o
COMPFLAGS = -c -g -O3 -std=c11

all: $(FINAL)

$(FINAL): $(OFILES) $(HFILES)
	$(COMP) $(OFILES) $(LINKFLAGS) $(FINAL)

main.o:main.c
	$(COMP) $< $(COMPFLAGS) -o $@

%.o:%.c %.h
	$(COMP) $< $(COMPFLAGS) -o $@

run: $(FINAL)
	./$(FINAL)

clear:
	rm $(OFILES) $(FINAL)
