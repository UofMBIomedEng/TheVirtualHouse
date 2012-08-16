#   SCE CONFIDENTIAL                                      
#   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
#   Copyright (C) 2006 Sony Computer Entertainment Inc.   
#   All Rights Reserved.                                  

CELL_MK_DIR := $(CELL_SDK)/samples/mk

include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_OPTIMIZE_LV		:= -O2
PPU_INCDIRS		:= -Iinclude -I../include
PPU_CPPFLAGS		:= -DPSGL -D_DEBUG
PPU_CXXSTDFLAGS		+= -fno-exceptions
PPU_SRCS		:= src/testapp.cpp
PPU_TARGET		:= testapp.elf
PPU_LIBS		:= ../libfw.a
PPU_LDLIBDIR		:= -L.. -L$(PPU_PSGL_LIBDIR)
PPU_LDLIBS		:= -lPSGL -lPSGLU -lPSGLFX -lm \
				   -lresc_stub -lgcm_cmd -lgcm_sys_stub \
				   -lnet_stub -lio_stub -lsysutil_stub -lsysmodule_stub

include $(CELL_MK_DIR)/sdk.target.mk
