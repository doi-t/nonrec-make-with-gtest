library-name := libDollar.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-library, $(subdirectory)/$(library-name), $(local_src)))
