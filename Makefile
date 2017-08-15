OK    := [\33[32;5mOK\033[m]
ERROR := [\33[31;5mERROR\33[m]
CHECK := echo "${OK}" || (echo "${ERROR}"; exit 1;)

CXX := $(shell which g++)

CXXFLAGS := -DNDEBUG -g0 -O3 -pedantic -Wall -Wextra -std=c++11
LDFLAGS  := -L /usr/local/lib -laws-cpp-sdk-text-to-speech -laws-cpp-sdk-polly -laws-cpp-sdk-core
INCLUDES := -I /usr/include/ -I /usr/local/include/

MAIN := test.cpp

BINARY := test

all:
	@echo -n "Compiling... "
	@$(CXX) ${MAIN} ${CXXFLAGS} ${LDFLAGS} ${INCLUDES} -o ${BINARY} && ${CHECK}

clean:
	@@echo -n "Cleaning... "
	@rm ${BINARY} && ${CHECK}

run:
	@./${BINARY} || (echo "${ERROR}"; exit 1;)
