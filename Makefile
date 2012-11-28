PACKAGE = libxmlmm
VERSION = 0.6.0

CXX      ?= g++ -std=c++0x
CXXFLAGS += -Iinclude -DVERSION=\"$(VERSION)\" -DLIBXML_STATIC
LDFLAGS  += 
prefix   ?= /usr/local

headers    = $(wildcard include/*.h)
lib_hdr    = $(wildcard src/*.h)
lib_src    = $(wildcard src/*.cpp)
lib_libs   = -lxml2 
test_hdr   = $(wildcard test/*.h)
test_src   = $(wildcard test/*.cpp)
test_libs  = $(lib_libs) -lUnitTest++
extra_dist = Makefile README.md $(wildcard docs/*.md)
dist_files = $(headers) $(lib_hdr) $(lib_src) $(test_hdr) $(test_src) $(extra_dist)

ifeq ($(MSYSTEM), MINGW32)
  EXEEXT    = .exe  
  LIBEXT    = .dll
else
  EXEEXT    =
  LIBEXT    = .so  
endif

.PHONY: all check clean install uninstall dist apidoc

all: $(PACKAGE)$(LIBEXT)

$(PACKAGE)$(LIBEXT): $(patsubst %.cpp, %.o, $(lib_src))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ $(lib_libs) -Wl,--out-implib=$(patsubst %$(LIBEXT),%.a, $@) -o $@

check: test-$(PACKAGE)$(EXEEXT)	
	./test-$(PACKAGE)$(EXEEXT)

test-$(PACKAGE)$(EXEEXT): $(PACKAGE)$(LIBEXT) $(patsubst %.cpp, %.o, $(test_src))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@

clean: 
	rm -f src/*.o src/*.d test/*.o test/*.d $(PACKAGE)$(LIBEXT) test-$(PACKAGE)$(EXEEXT)	

dist:
	mkdir $(PACKAGE)-$(VERSION)
	cp --parents $(dist_files) $(PACKAGE)-$(VERSION)
	tar -czvf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION)

install: $(PACKAGE)$(LIBEXT)
	mkdir -p $(prefix)/include/$(PACKAGE)
	cp $(headers) $(prefix)/include/$(PACKAGE)
	mkdir -p $(prefix)/lib
	cp $(PACKAGE).a $(prefix)/lib
	mkdir -p $(prefix)/bin
	cp $(PACKAGE)$(LIBEXT) $(prefix)/bin

uninstall:
	rm -r $(prefix)/include/$(PACKAGE)
	rm $(prefix)/lib/$(PACKAGE).a
	rm $(prefix)/bin/$(PACKAGE)$(LIBEXT)

apidoc:
	mkdir -p apidoc
	doxygen Doxyfile
	
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)	

ifneq "$(MAKECMDGOALS)" "clean"
deps  = $(patsubst %.cpp, %.d, $(lib_src))
deps += $(patsubst %.cpp, %.d, $(test_src))
-include $(deps)
endif