CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS = main.cpp card.cpp account.cpp journal.cpp \
       file_storage.cpp recovery.cpp atm_engine.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = atm

TEST_SRCS = tests/test_atm.cpp card.cpp account.cpp journal.cpp \
            file_storage.cpp recovery.cpp atm_engine.cpp
TEST_TARGET = tests/run_tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)
	rm -rf data/

.PHONY: all tests clean
