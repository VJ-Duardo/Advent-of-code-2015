DAY=day2
include src/$(DAY)/makefile.title

.PHONY: all clean

all:
	cd src/$(DAY) && $(MAKE)

install: all
	cp src/$(DAY)/$(TITLE) bin/

run: install
	./bin/$(TITLE)

clean:
	cd src/$(DAY) && $(MAKE) clean

distclean: clean
	rm -rf bin/$(TITLE)

debug: install
	gdb bin/$(TITLE)
