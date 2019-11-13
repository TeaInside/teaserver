
COMPILER = gcc
LINKER = gcc
BIN_FILE = teaserver
LIBS = -lpthread -lpcre -lcurl
SOURCE_DIR = src/
ROOT_DEPDIR = .deps
STD_FLAG =
CONSTANTS = -DTEA_SERVER_DEBUG -DINI_MAX_LINE=2048 -DINI_ALLOW_INLINE_COMMENTS=1
INCLUDE_DIR = -Iinclude/

ifeq (${RELEASE_MODE},1)
	LINKER_FLAGS  = ${STD_FLAG} -Wall -fno-stack-protector ${INCLUDE_DIR} -s -Ofast ${CONSTANTS} -o
	COMPILER_FLAGS = ${STD_FLAG} -Wall -fno-stack-protector ${INCLUDE_DIR} -s -Ofast ${CONSTANTS} -c -o
else
	LINKER_FLAGS  = ${STD_FLAG} -Wall -fstack-protector-strong ${INCLUDE_DIR} -ggdb3 -O0 ${CONSTANTS} -o
	COMPILER_FLAGS = ${STD_FLAG} -Wall -fstack-protector-strong ${INCLUDE_DIR} -ggdb3 -O0 ${CONSTANTS} -c -o
endif

SOURCES  = $(shell find ${SOURCE_DIR} -name '*.c')
SOURCES += $(shell find ${SOURCE_DIR} -name '*.cpp')

OBJECTS = $(SOURCES:%=%.o)
SOURCES_DIR = $(shell find ${SOURCE_DIR} -type d)

DEPDIR = ${SOURCES_DIR:%=${ROOT_DEPDIR}/%}
DEPFLAGS = -MT $@ -MMD -MP -MF ${ROOT_DEPDIR}/$*.d
DEPFILES = ${SOURCES:%=${ROOT_DEPDIR}/%.d}

all: ${BIN_FILE}

${ROOT_DEPDIR}:
	mkdir -p $@

${DEPDIR}: | ${ROOT_DEPDIR}
	mkdir -p $@

${OBJECTS}: | ${DEPDIR}
	${COMPILER} ${DEPFLAGS} ${COMPILER_FLAGS} $@ ${@:%.o=%}

${BIN_FILE}: ${OBJECTS}
	${LINKER} ${LINKER_FLAGS} ${BIN_FILE} ${OBJECTS} ${LIBS}

-include ${DEPFILES}

release:
	echo ${OBJECTS}
	make clean
	make RELEASE_MODE=1 ${RELEASE_FLAGS} ${MAKE_ARG}
	strip -s ${BIN_FILE}

clean:
	rm -rf ${DEPFILES}
	rm -rf ${OBJECTS}
	rm -rf ${BIN_FILE}
