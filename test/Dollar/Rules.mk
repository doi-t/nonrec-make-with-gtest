local_test_suites := test_Dollar
target_libraries := lib/Dollar/libDollar.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-test, $(subdirectory)/$(local_test_suites), $(local_src), $(target_libraries)))
