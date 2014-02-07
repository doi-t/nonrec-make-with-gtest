# non-recursive make with googletest

# Usage:$(subdirectory)
subdirectory = $(patsubst %/Rules.mk,%,$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

# Usage:$(eval $(call source-to-object, source-file-list))
source-to-object = $(subst .cc,.o,$(filter %.cc, $1))

# Usage:$(eval $(call make-library, library-name, source-file-list))
define make-library
  libraries		+= $1
  sources		+= $2

  $1: $(call source-to-object, $2)
	$(AR) $(ARFLAGS) $$@ $$^
endef

# Usage:$(eval $(call make-exec-binary, exec-binary-name, source-file-list, libraries))
define make-exec-binary
  programs	+= $1
  sources	+= $2

  $1: $(call source-to-object, $2) $3
endef

# Usage:$(eval $(call test_suites, source-file-list, target_libraries))
define make-test
  test_suites	+= $1
  sources		+= $2

  $1: $2 $3
	g++ $(CXXFLAGS) -g -Wextra $(CPPFLAGS) -I$(GTEST_ROOT)/include $$^ $(GTEST_LIBS) -pthread -o $$@
	$$@
endef

# サブディレクトリの情報を収集する変数の初期化 
Rules		:= $(subst /Rules.mk,,$(shell find . -name Rules.mk))
programs	:= 
libraries	:=
sources		:=
test_suites	:=

objects			= $(call source-to-object, $(sources))
dependencies	= $(subst .o,.d,$(objects))

include_dirs	:=	./lib ./bin ./test
CPPFLAGS		+=	$(addprefix -I ,$(include_dirs))
vpath %.h $(include_dirs)

MV := mv -f
RM := rm -f
CP := cp
MKDIR := mkdir
SED := sed
LN := ln

#C++コンパイラオプション
CXXFLAGS := -Wall 
#CXXFLAGS := -Wall -O3
#CXXFLAGS := -Wall -g

#gtest関連
GTEST_ROOT := /usr/local/gtest
GTEST_INSTALL := ./gtest_install
GTEST_UNINSTALL := ./gtest_uninstall
GTEST_LIBS := $(GTEST_ROOT)/lib/libgtest.a $(GTEST_ROOT)/lib/libgtest_main.a

#リンカ
CC := g++
#リンカオプション
LDFLAGS := -Wall 

all:

### include Rules, in random order
include $(addsuffix /Rules.mk,$(Rules))

### Rules
.PHONY: all
all: $(programs) libraries

.PHONY: test
test: $(test_suites)

.PHONY: libraries
libraries: $(libraries)

.PHONY: setup_gtest
setup_gtest:
	if [ ! -e $(GTEST_ROOT) ]; \
	then \
		bash $(GTEST_INSTALL); \
	else \
		true; \
	fi

.PHONY: remove_gtest
remove_gtest:
	if [ -e $(GTEST_ROOT) ]; \
	then \
		bash $(GTEST_UNINSTALL); \
	else \
		true; \
	fi

.PHONY: debug
debug:
	@echo "programs=$(programs)"
	@echo "objects=$(objects)"
	@echo "sources=$(sources)"
	@echo "Rules=$(Rules)"
	@echo "libraries=$(libraries)"
	@echo "test_suites=$(test_suites)"
	@echo "dependencies=$(dependencies)"

.PHONY: clean
clean:
	$(RM) $(objects) $(programs) $(libraries) $(dependencies) $(test_suites)

ifneq "$(MAKECMDGOALS)" "clean"
  include $(dependencies)
endif

### 依存関係の自動生成
%.d: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP $< |\
		$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@
