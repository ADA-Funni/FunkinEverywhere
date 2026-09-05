PLATFORM ?= windows

ifeq ($(PLATFORM),windows)
include make/Makefile_windows
else ifeq ($(PLATFORM),linux)
include make/Makefile_linux
else
    $(error Unknown platform: $(PLATFORM))
endif