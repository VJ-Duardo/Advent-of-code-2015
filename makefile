DAY=day21
include src/$(DAY)/makefile.title

.PHONY: all clean open

all:
	cd src/$(DAY) && $(MAKE)

install: all
	cp src/$(DAY)/$(TITLE) bin/
	cd src/utils && $(MAKE) && cp *.so ../../lib/

run: install
	./bin/$(TITLE)

clean:
	cd src/$(DAY) && $(MAKE) clean
	cd src/utils/ && $(MAKE) clean

distclean: clean
	rm -rf bin/$(TITLE) lib/*

debug: install
	gdb bin/$(TITLE)

open:
	code src/$(DAY)/*.c
	code src/$(DAY)/makefile
	code include/$(DAY)/*.h
	code src/$(DAY)/*.txt
