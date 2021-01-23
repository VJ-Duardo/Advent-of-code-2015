DAY=day14
include src/$(DAY)/makefile.title

.PHONY: all clean open

all:
	cd src/$(DAY) && $(MAKE)

install: all
	cp src/$(DAY)/$(TITLE) bin/

run: install
	./bin/$(TITLE)

clean:
	cd src/$(DAY) && $(MAKE) clean
	cd src/utils/ && rm -f *.o *.d

distclean: clean
	rm -rf bin/$(TITLE)

debug: install
	gdb bin/$(TITLE)

open:
	code src/$(DAY)/*.c
	code src/$(DAY)/makefile
	code include/$(DAY)/*.h
	code src/$(DAY)/*.txt
