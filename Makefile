DESTDIR  = /usr/local/include
MAKEFLAGS += --no-builtin-rules

all:
	@echo "nameof is a header-only library, it needs no build."
	@echo "Run sudo make install [DESTDIR=...] to install headers or "
	@echo "    make run-tests to build and run tests"

install:
	$(INSTALL) include/meta $(DESTDIR) 

run-tests:
	$(MAKE) -C test run-tests

clean:
	$(MAKE) -C test clean
