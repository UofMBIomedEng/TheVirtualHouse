#   SCE CONFIDENTIAL                                      
#   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
#   Copyright (C) 2006 Sony Computer Entertainment Inc.   
#   All Rights Reserved.                                  

CELL_SDK ?= /usr/local/cell
CELL_MK_DIR ?= $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

SUBDIR          =   $(CELL_SDK)/samples/fw

PPU_LIB_TARGET	=	libfwgcm.a
PPU_SRCS		=	src/gcm/memory.cpp \
					src/gcm/FWGCMApplication.cpp \
					src/gcm/FWGCMCamApplication.cpp \
					src/gcm/FWGCMCamControlApplication.cpp \
					src/gcm/FWGCMDebugFontRenderer.cpp \
					src/gcm/FWCellGCMWindow.cpp \
					src/gcm/FWCellMain.cpp \
					src/FWApplication.cpp \
					src/FWCamera.cpp \
					src/FWDebugConsole.cpp \
					src/FWDebugFont.cpp \
					src/FWDebugFontRenderer.cpp \
					src/FWDisplayInfo.cpp \
					src/FWInput.cpp \
					src/FWNullApplication.cpp \
					src/FWNullDebugFontRenderer.cpp \
					src/FWNullWindow.cpp \
					src/FWWindow.cpp \
					src/cell/FWCellInput.cpp \
					src/cell/FWCellTime.cpp \
					src/cell/FWCellSystemCallback.cpp \
					$(VPSHADER_PPU_OBJS) $(FPSHADER_PPU_OBJS)

COMMONDIR		=	$(CELL_SDK)/samples/gcm/common

PPU_INCDIRS		+=	-I$(CELL_TARGET_PATH)/ppu/include/vectormath/cpp
PPU_INCDIRS		+=	-Iinclude -Iinclude/gcm -I$(COMMONDIR)
PPU_CXXFLAGS	+=	-fno-rtti --param large-function-growth=800

VPSHADER_SRCS	=	dbgfont_vpshader.cg clear_vpshader.cg
FPSHADER_SRCS	=	dbgfont_fpshader.cg clear_fpshader.cg

VPSHADER_PPU_OBJS = $(patsubst %.cg, $(OBJS_DIR)/%.ppu.o, $(VPSHADER_SRCS))
FPSHADER_PPU_OBJS = $(patsubst %.cg, $(OBJS_DIR)/%.ppu.o, $(FPSHADER_SRCS))

include $(CELL_MK_DIR)/sdk.target.mk

PPU_OBJS += $(VPSHADER_PPU_OBJS) $(FPSHADER_PPU_OBJS)

$(VPSHADER_PPU_OBJS): $(OBJS_DIR)/%.ppu.o : %.vpo
	@mkdir -p $(dir $(@))
	$(PPU_OBJCOPY)  -I binary -O elf64-powerpc-celloslv2 -B powerpc $< $@


$(FPSHADER_PPU_OBJS): $(OBJS_DIR)/%.ppu.o : %.fpo
	@mkdir -p $(dir $(@))
	$(PPU_OBJCOPY)  -I binary -O elf64-powerpc-celloslv2 -B powerpc $< $@

