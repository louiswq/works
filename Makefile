##############################################################################
#	Author:		wangqiang
#	Date  :		2020/11/06
#	E-mail:		louis_wq@163.com
##############################################################################
TARGET			:= test

SRC_DIR			:= src
BUILD_DIR		:= build

##############################################################################
# 源文件以及目录
##############################################################################

SRC 			:= $(wildcard $(SRC_DIR)/*.c)
INCLUDE_DIRS 	:= $(SRC_DIR)

##############################################################################
TARGET_ELF  	:= $(BUILD_DIR)/$(TARGET).elf
TARGET_OBJS 	:= $(addsuffix .o,$(addprefix $(BUILD_DIR)/$(TARGET)/,$(basename $(SRC))))


$(BUILD_DIR)/$(TARGET)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "compiling $(notdir $<)..."
	@gcc -o $@ -c $^ $(addprefix -I,$(INCLUDE_DIRS))
	
$(TARGET_ELF): $(TARGET_OBJS)
	@echo "Linking $(TARGET)"
	@gcc -o $@ $^
	@echo "Building $(TARGET) succeeded."
	
clean:
	@echo "Cleaning $(TARGET)..."
	@rm -rf $(BUILD_DIR)
	@echo "Cleaning $(TARGET) succeeded."
