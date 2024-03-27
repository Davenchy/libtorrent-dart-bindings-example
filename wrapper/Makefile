CC = g++
TEST_BIN = test
SRC = wrapper.cpp
INCLUDE = wrapper.hpp
LIB_NAME = libwrapper.so


.PHONY += debug
debug: $(TEST_BIN)

.PHONY += run
run: debug
	./$(TEST_BIN)

$(TEST_BIN): $(SRC) $(INCLUDE)
	g++ $^ -o $@ -g `pkg-config --libs libtorrent-rasterbar`

.PHONY += build
build: $(LIB_NAME)

$(LIB_NAME): $(SRC) $(INCLUDE)
	g++ $^ -o $(LIB_NAME) -shared -fPIC `pkg-config --libs libtorrent-rasterbar`
