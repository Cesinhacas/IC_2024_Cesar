###########################################################################
## Makefile generated for component 'test1'. 
## 
## Makefile     : test1_rtw.mk
## Generated on : Tue Oct 22 09:50:02 2024
## Final product: ./test1.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = test1
MAKEFILE                  = test1_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2022b
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/labt5/OneDrive/Desktop/Cesar/IC_2024_Cesar/Matlab
TGT_FCN_LIB               = None
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
CMD_FILE                  = test1_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = test1.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./test1.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/test1 -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=test1

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/test1/coder_posix_time.c $(START_DIR)/codegen/lib/test1/test1_data.c $(START_DIR)/codegen/lib/test1/rt_nonfinite.c $(START_DIR)/codegen/lib/test1/rtGetNaN.c $(START_DIR)/codegen/lib/test1/rtGetInf.c $(START_DIR)/codegen/lib/test1/test1_initialize.c $(START_DIR)/codegen/lib/test1/test1_terminate.c $(START_DIR)/codegen/lib/test1/test1.c $(START_DIR)/codegen/lib/test1/tic.c $(START_DIR)/codegen/lib/test1/timeKeeper.c $(START_DIR)/codegen/lib/test1/toc.c $(START_DIR)/codegen/lib/test1/CoderTimeAPI.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = coder_posix_time.obj test1_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj test1_initialize.obj test1_terminate.obj test1.obj tic.obj timeKeeper.obj toc.obj CoderTimeAPI.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/codegen/lib/test1/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


coder_posix_time.obj : $(START_DIR)/codegen/lib/test1/coder_posix_time.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


test1_data.obj : $(START_DIR)/codegen/lib/test1/test1_data.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_nonfinite.obj : $(START_DIR)/codegen/lib/test1/rt_nonfinite.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetNaN.obj : $(START_DIR)/codegen/lib/test1/rtGetNaN.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetInf.obj : $(START_DIR)/codegen/lib/test1/rtGetInf.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


test1_initialize.obj : $(START_DIR)/codegen/lib/test1/test1_initialize.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


test1_terminate.obj : $(START_DIR)/codegen/lib/test1/test1_terminate.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


test1.obj : $(START_DIR)/codegen/lib/test1/test1.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


tic.obj : $(START_DIR)/codegen/lib/test1/tic.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


timeKeeper.obj : $(START_DIR)/codegen/lib/test1/timeKeeper.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


toc.obj : $(START_DIR)/codegen/lib/test1/toc.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


CoderTimeAPI.obj : $(START_DIR)/codegen/lib/test1/CoderTimeAPI.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


