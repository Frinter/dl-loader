CPP := g++
CC := gcc

SUB_DIRS := $(shell find src -type d -print)
OBJ_DIRS := $(foreach dir,$(SUB_DIRS),$(patsubst src%,build%,$(dir)))
SRC := $(foreach dir,$(SUB_DIRS),$(wildcard $(dir)/*.cc))
CORE := src/module.cc src/modulerepository.cc src/sharedlibraryrepository.cc \
	src/readwritelock.cc src/util/repository.cc src/windows/sharedlibrary.cc \
	src/windows/thread.cc src/windows/mutex.cc
MAIN := src/main.cc
OBJ := $(patsubst src/%.cc,build/%.o,$(filter-out $(MAIN),$(SRC)))
CORE_OBJ := $(patsubst src/%.cc,build/%.o,$(CORE))
MAIN_OBJ := $(patsubst src/%.cc,build/%.o,$(MAIN))
INCLUDE := -Isrc -Iinclude
CFLAGS := $(INCLUDE)
RELEASE_TARGET := bin/core.a
DEBUG_TARGET := bin/debug

TEST_SUB_DIRS := $(shell find test -type d -print)
TEST_OBJ_DIRS := $(foreach dir,$(TEST_SUB_DIRS),$(patsubst test%,test-build%,$(dir)))
TEST_SRC := $(foreach dir,$(TEST_SUB_DIRS),$(wildcard $(dir)/*.cc))
TEST_OBJ := $(patsubst test/%.cc,test-build/%.o,$(TEST_SRC))
TEST_TARGET := bin/test

.PRECIOUS: build/%.d test-build/%.d
.PHONY: clean debug release test
.DEFAULT_GOAL := debug

release: $(RELEASE_TARGET)
debug: $(DEBUG_TARGET)

test: $(TEST_TARGET)

$(DEBUG_TARGET): $(MAIN_OBJ) $(RELEASE_TARGET)
	$(CPP) -o $@ $(CFLAGS) -std=c++11 $^

$(RELEASE_TARGET): $(CORE_OBJ)
	ar rvs $@ $^

$(TEST_TARGET): $(TEST_OBJ)
	$(CPP) -o $@ $(CFLAGS) -std=c++11 $^

$(OBJ_DIRS) $(TEST_OBJ_DIRS):
	mkdir -p $@

build/%.d: src/%.c | $(OBJ_DIRS)
	$(CC) -MM -MT build/$*.o $(CFLAGS) -MF $@ $<

build/%.o: src/%.c build/%.d | $(OBJ_DIRS)
	$(CC) -c -o $@ $(CFLAGS) $<

build/%.d: src/%.cc | $(OBJ_DIRS)
	$(CPP) -std=c++11 -MM -MT build/$*.o $(CFLAGS) -MF $@ $<

build/%.o: src/%.cc build/%.d | $(OBJ_DIRS)
	$(CPP) -c -o $@ -std=c++11 $(CFLAGS) $<

bin/%.dll: build/%.o
	$(CPP) -shared -o $@ $^

test-build/%.d: test/%.cc | $(TEST_OBJ_DIRS)
	$(CPP) -std=c++11 -MM -MT test-build/$*.o $(CFLAGS) -Isrc -MF $@ $<

test-build/%.o: test/%.cc test-build/%.d | $(TEST_OBJ_DIRS)
	$(CPP) -c -o $@ -std=c++11 $(CFLAGS) -Isrc $<

clean:
	if [ -d "build" ]; then rm -R build; fi
	if [ -d "test-build" ]; then rm -R test-build; fi

include $(wildcard build/*.d)
include $(wildcard test-build/*.d)
