local_test_suites := test_add
target_libraries := lib/add/libadd.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-test, $(subdirectory)/$(local_test_suites), $(local_src), $(target_libraries)))

