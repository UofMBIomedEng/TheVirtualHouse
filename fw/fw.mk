CELL_MK_DIR := $(CELL_SDK)/samples/mk

include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_OPTIMIZE_LV := -O2
PPU_INCDIRS	:= -Iinclude 
PPU_CPPFLAGS	:= -DPSGL -D_DEBUG -DCELL_DISPLAY_MODE=DisplayMode_$(CELL_DISPLAY_MODE)
PPU_CXXSTDFLAGS += -fno-exceptions
PPU_SRCS	:=  \
		src/FWApplication.cpp \
		src/FWCamera.cpp \
		src/FWDebugConsole.cpp \
		src/FWDebugFont.cpp \
		src/FWDebugFontRenderer.cpp \
		src/FWDisplayInfo.cpp \
		src/FWNullApplication.cpp \
		src/FWNullDebugFontRenderer.cpp \
		src/FWNullWindow.cpp src/FWWindow.cpp \
		src/cell/FWCellInput.cpp \
		src/cell/FWCellMain.cpp \
		src/cell/FWCellTime.cpp \
		src/cell/FWCellSystemCallback.cpp \
		src/psgl/FWGLApplication.cpp \
		src/psgl/FWGLCamApplication.cpp \
		src/psgl/FWGLCamControlApplication.cpp \
		src/psgl/FWGLDebugFontRenderer.cpp \
		src/psgl/FWGLGrid.cpp src/FWInput.cpp \
		src/psgl/FWCellGLWindow.cpp

PPU_LIB_TARGET	:= libfw.a

include $(CELL_MK_DIR)/sdk.target.mk

