#
# Recursive make - makes the subdirectory code
#

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGETS = $(GENERAL_TARGETS) $(LIB_TARGETS) $(INSTALL_TARGETS)

SUB_DIRS = \
         libs \
         apps

include $(RAP_MAKE_INC_DIR)/rap_make_recursive_dir_targets

