
-include config.mk
ifndef CONFIG_MK_INCLUDED
$(error config.mk not built. Run configure script.)
endif

CXX      ?= g++
CXXFLAGS += -Iinclude -DVERSION=\"$(VERSION)\" $(XML2_CFLAGS)
LDFLAGS  += 

headers    = $(wildcard include/*.h)
lib_hdr    = $(wildcard src/*.h)
lib_src    = $(wildcard src/*.cpp)
lib_libs   = $(XML2_LIBS) 
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

all: libxmlmm$(LIBEXT)

libxmlmm$(LIBEXT): $(patsubst %.cpp, %.o, $(lib_src))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ $(lib_libs) -Wl,--out-implib=$(patsubst %$(LIBEXT),%.a, $@) -o $@

check: test-libxmlmm$(EXEEXT)	
	./test-libxmlmm$(EXEEXT)

test-libxmlmm$(EXEEXT): libxmlmm$(LIBEXT) $(patsubst %.cpp, %.o, $(test_src))
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@

clean: 
	rm -f src/*.o src/*.d test/*.o test/*.d libxmlmm$(LIBEXT) test-libxmlmm$(EXEEXT)	

dist:
	mkdir libxmlmm-$(VERSION)
	cp --parents $(dist_files) libxmlmm-$(VERSION)
	tar -czvf libxmlmm-$(VERSION).tar.gz libxmlmm-$(VERSION)
	rm -rf libxmlmm-$(VERSION)

install: libxmlmm$(LIBEXT)
	mkdir -p $(prefix)/include/libxmlmm
	cp $(headers) $(prefix)/include/libxmlmm
	mkdir -p $(prefix)/lib
	cp libxmlmm.a $(prefix)/lib
	mkdir -p $(prefix)/lib/pkgconfig
	cp libxmlmm.pc $(prefix)/pkgconfig
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
	
%.o : %.cpp config.mkmake
	$(CXX) $(CXXFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)	

ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, %.d, $(lib_src))
-include $(patsubst %.cpp, %.d, $(test_src))
endif