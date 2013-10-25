


LIBDIR := lib/
LIBS := lib/libhdfjive.so


all: $(LIBS)
.PHONY : clean clean-doc



$(LIBS): | $(LIBDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)


lib/libhdfjive.so : include/hdfjive.h src/hdfjive.cpp include/hdfjive-neuro.h src/hdfjive-neuro.cpp
	g++ -c -g -Wall -Werror -fpic src/hdfjive.cpp   -o lib/hdfjive.o -Iinclude -O3 -std=c++0x
	g++ -c -g -Wall -Werror -fpic src/hdfjive-neuro.cpp   -o lib/hdfjive-neuro.o -Iinclude -O3 -std=c++0x
	g++ -g -shared -o lib/libhdfjive.so lib/hdfjive.o  lib/hdfjive-neuro.o  -O3 -std=c++0x

# Test linking:
test/hdfjive_test1.x : test/hdfjive_test1.cpp lib/libhdfjive.so
	g++ -L$(LIBDIR) -Iinclude -Wall -o test/hdfjive_test1.x test/hdfjive_test1.cpp -lhdfjive -lhdf5 -lhdf5_hl -std=c++0x
	

runtests: test/hdfjive_test1.x
	echo "If this fails, you might need to export LD_LIBRARY_PATH=/home/user/whereis/hdf-jive/lib/:$LD_LIBRARY_PATH;"
	./test/hdfjive_test1.x






doc:
	make -C doc html

clean-doc:
	make -C doc clean





clean:
	rm -rf $(LIBDIR)
	rm -f test/hdfjive_test1.x test/myfile.hdf myfile.hdf


