exec-binary-name := sample
dependent-libraries := lib/add/libadd.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-exec-binary, $(subdirectory)/$(exec-binary-name), $(local_src), $(dependent-libraries)))
