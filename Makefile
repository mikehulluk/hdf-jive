


LIBDIR := lib/
LIBS := lib/libhdfjive.so


all: $(LIBS)
.PHONY : clean



$(LIBS): | $(LIBDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)


lib/libhdfjive.so : include/hdfjive.h src/hdfjive.cpp
	g++ -c -g -Wall -Werror -fpic src/hdfjive.cpp -o lib/hdfjive.o -Iinclude -O3
	g++ -g -shared -o lib/libhdfjive.so lib/hdfjive.o -O3




# Test linking:
test/hdfjive_test1.x : test/hdfjive_test1.cpp lib/libhdfjive.so
	g++ -L$(LIBDIR) -Iinclude -Wall -o test/hdfjive_test1.x test/hdfjive_test1.cpp -lhdfjive -lhdf5 -lhdf5_hl
	


runtests: test/hdfjive_test1.x
	echo "If this fails, you might need to export LD_LIBRARY_PATH=/home/user/whereis/hdf-jive/lib/:$LD_LIBRARY_PATH;"
	./test/hdfjive_test1.x





clean:
	rm -rf $(LIBDIR)
	rm -f test/hdfjive_test1.x test/myfile.hdf myfile.hdf


