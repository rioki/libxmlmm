
-include config.mk
ifndef CONFIG_MK_INCLUDED
$(error config.mk not built. Run configure script.)
endif

CXX      ?= g++
CXXFLAGS += -I. -DVERSION=\"$(VERSION)\" $(XML2_CFLAGS)
LDFLAGS  += 

lib_hdr    = $(wildcard libxmlmm/*.h)
lib_src    = $(wildcard libxmlmm/*.cpp)
lib_libs   = $(XML2_LIBS) 
test_hdr   = $(wildcard libxmlmm-test/*.h)
test_src   = $(wildcard libxmlmm-test/*.cpp)
test_libs  = $(lib_libs)
extra_dist = Makefile README.md $(wildcard docs/*.md)
dist_files = $(lib_hdr) $(lib_src) $(test_hdr) $(test_src) $(extra_dist)

ifeq ($(OS),Windows_NT)
  EXEEXT    = .exe  
  LIBEXT    = .dll
else
  EXEEXT    = .exe
  LIBEXT    = .so  
endif

.PHONY: all check clean install uninstall dist apidoc

all: libxmlmm$(LIBEXT)

libxmlmm$(LIBEXT): $(patsubst %.cpp, %.o, $(lib_src))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ $(lib_libs) -Wl,--out-implib=$(patsubst %$(LIBEXT),%.a, $@) -o $@

check: libxmlmm-test$(EXEEXT)	
	./libxmlmm-test$(EXEEXT)

libxmlmm-test$(EXEEXT): libxmlmm$(LIBEXT) $(patsubst %.cpp, %.o, $(test_src))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@

clean: 
	rm -f libxmlmm/*.o libxmlmm/*.d libxmlmm-test/*.o libxmlmm-test/*.d libxmlmm$(LIBEXT) libxmlmm-test$(EXEEXT)	

dist:
	mkdir libxmlmm-$(VERSION)
	cp --parents $(dist_files) libxmlmm-$(VERSION)
	tar -czvf libxmlmm-$(VERSION).tar.gz libxmlmm-$(VERSION)
	rm -rf libxmlmm-$(VERSION)

install: libxmlmm$(LIBEXT)
	mkdir -p $(prefix)/include/libxmlmm
	cp $(lib_hdr) $(prefix)/include/libxmlmm
	mkdir -p $(prefix)/lib
	cp libxmlmm.a $(prefix)/lib
	mkdir -p $(prefix)/lib/pkgconfig
	cp libxmlmm.pc $(prefix)/lib/pkgconfig
	mkdir -p $(prefix)/bin
	cp libxmlmm$(LIBEXT) $(prefix)/bin

uninstall:
	rm -r $(prefix)/include/libxmlmm
	rm $(prefix)/lib/libxmlmm.a
	rm $(prefix)/lib/pkgconfig/libxmlmm.pc
	rm $(prefix)/bin/libxmlmm$(LIBEXT)

apidoc:
	mkdir -p apidoc
	doxygen Doxyfile
	
%.o : %.cpp config.mk
	$(CXX) $(CXXFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)	

ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, %.d, $(lib_src))
-include $(patsubst %.cpp, %.d, $(test_src))
endif