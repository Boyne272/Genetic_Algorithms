# ------------------------------- Vars ----------------------------------

CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -std=gnu++0x
LDFLAGS =
SOURCE_DIR = src
INCLUDE_DIR = includes
TEST_DIR = tests

BUILD_DIR = build
BIN_DIR = bin
ALL_BUILD_DIR = $(BUILD_DIR) $(BIN_DIR)

TEST_BUILD_DIR = $(TEST_DIR)/build
TEST_BIN_DIR = $(TEST_DIR)/bin
ALL_TEST_BUILD_DIR = $(TEST_BUILD_DIR) $(TEST_BIN_DIR)


# ------------------------------- Build ----------------------------------

# this is run when make is called without arguments 
all: Genetic_Algorithm

Genetic_Algorithm: $(BIN_DIR)/Genetic_Algorithm

$(BIN_DIR)/Genetic_Algorithm: $(BUILD_DIR)/main.o $(BUILD_DIR)/genetic_algorithm.o $(BUILD_DIR)/cunit.o $(BUILD_DIR)/circuit.o 
	$(CXX) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/*.h | directories
	$(CXX) $(CPPFLAGS) -o $@ -c $< $(CXXFLAGS) -I $(INCLUDE_DIR)

# clean away previously made versions
clean:
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/*

# make clean run regardless of the presense of any files
.PHONY: Genetic_Algorithm all clean


# ------------------------------- Tests ----------------------------------

# declare the tests to make
TESTS = test_travis test_evaluate test_genetic_algorithm test_validate

# call the following functions to make the all test files
tests: ${TESTS}


# travis test
test_travis: $(TEST_BIN_DIR)/test_travis

$(TEST_BIN_DIR)/test_travis: $(TEST_BUILD_DIR)/test_travis.o #$(BUILD_DIR)/additional dependencies
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)


# evaluate test
test_evaluate: $(TEST_BIN_DIR)/test_evaluate

$(TEST_BIN_DIR)/test_evaluate: $(TEST_BUILD_DIR)/test_evaluate.o $(BUILD_DIR)/circuit.o $(BUILD_DIR)/cunit.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)


# genetic_algorithm test
test_genetic_algorithm: $(TEST_BIN_DIR)/test_genetic_algorithm

$(TEST_BIN_DIR)/test_genetic_algorithm: $(TEST_BUILD_DIR)/test_genetic_algorithm.o $(BUILD_DIR)/circuit.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)


# validation test
test_validate: $(TEST_BIN_DIR)/test_validate

$(TEST_BIN_DIR)/test_validate: $(TEST_BUILD_DIR)/test_validate.o $(BUILD_DIR)/circuit.o $(BUILD_DIR)/cunit.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)


# build test files in test_build_direct with the .cpp file in test_dir
# and include all header files (also ensure the test_directories exist)
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(INCLUDE_DIR)/*.h | test_directories
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS) -I $(INCLUDE_DIR)


# make the test files and run test python script
runtests: ${TESTS}
	@python3 run_tests.py


# clean the test files
cleantests:
	rm -f $(TEST_BUILD_DIR)/* $(TEST_BIN_DIR)/*


# declare rules as phony
.PHONY: tests ${TESTS} cleantests runtests


# ------------------------------- Directories -------------------------------

# if the directories are not present make them
directories:
	@mkdir -p $(ALL_BUILD_DIR)

test_directories:
	@mkdir -p $(ALL_TEST_BUILD_DIR)

# declare this as phony too
.PHONY: directories test_directories
