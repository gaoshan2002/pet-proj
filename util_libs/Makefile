
.SILENT:

PLATFORMS=host  
PROJECT=util_libs
TEST_TIMEOUT=60

SRC_DIR = $(shell readlink -f .)

ifndef BUILD_DIR
	BUILD_DIR = ${SRC_DIR}/build/$(PROJECT)
else
	BUILD_DIR := ${BUILD_DIR}/$(PROJECT)
endif

ifndef INSTALL_DIR
	INSTALL_DIR = ${SRC_DIR}/install
endif

ifndef GENERATOR
	GENERATOR=Unix Makefiles
endif

ifndef BUILD_SHARED_LIBS
	BUILD_SHARED_LIBS=OFF
endif

help:
	@echo ""
	@echo "Make targets:"
	@echo "------------"
	@echo "make all - Configure/Build/Install all platforms and run host tests"
	@echo "make test - Clean/Configure/Build/Install all platforms and run host tests"
	@echo "make clean - Clean-up build directories"
	@echo "make $(PLATFORMS) - Configure/Build/Install platform (and test if host)"
	@echo ""
	@echo "Environment variables"
	@echo "---------------------"
	@echo "BUILD_DIR - default to SRC_DIR/build"
	@echo "INSTALL_DIR - default to SRC_DIR/install"
	@echo "GENERATOR - CMake generator, default to \"Unix Makefiles\""
	@echo "BUILD_SHARED_LIBS - ON or OFF (default to OFF)"
	@echo ""

all: $(PLATFORMS)

test: clean all

$(PLATFORMS):
	@echo -e "############################################################"
	@echo -e "### PLATFORM=$@"
	@echo -e "### BUILD_DIR=${BUILD_DIR}/$@"
	@echo -e "### INSTALL_DIR=${INSTALL_DIR}/$@"
	@echo -e "############################################################"
	# Create directories
	mkdir -p ${BUILD_DIR}/$@ ${INSTALL_DIR}/$@
	# Configure
	cd ${BUILD_DIR}/$@; \
	if [ "$@" != "host" ] && [ ! -f ${BUILD_DIR}/$@/CMakeCache.txt ]; \
	then \
		cmake -G"${GENERATOR}" ${SRC_DIR} -DCMAKE_TOOLCHAIN_FILE=$(SRC_DIR)/cmake/Toolchains/Toolchain-$@.cmake -DCMAKE_INSTALL_PREFIX=$(INSTALL_DIR)/$@ -DBUILD_SHARED_LIBS=$(BUILD_SHARED_LIBS) ; \
	else \
		cmake -G"${GENERATOR}" ${SRC_DIR} -DCMAKE_INSTALL_PREFIX=$(INSTALL_DIR)/$@ -DBUILD_SHARED_LIBS=$(BUILD_SHARED_LIBS) ; \
	fi; \
	# Build and Install
	cd ${BUILD_DIR}/$@; if [ -f build.ninja ] ; then ninja install ; else make install ; fi
	# Test
	if [ "$@" = "host" ] ; then cd ${BUILD_DIR}/$@; ctest --timeout ${TEST_TIMEOUT} --output-on-failure ; fi

clean:
	rm -rvf ${BUILD_DIR}
	rm -rvf build install

