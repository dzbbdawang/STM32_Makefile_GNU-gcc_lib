#一个stm32的makefile,使用内核为M3的STM32F103R6,使用开源GCC编译器,在当前文件夹下生成OBJ
#文件夹存放编译输出文件,对于每一个项目符号，在生成一个OBJ/项目符号名称文件夹

# STM32F103R6 (Cortex-M3) Makefile
# 使用开源GCC编译器
# 编译输出文件存放在当前目录下的OBJ文件夹中
# 每个项目符号在OBJ文件夹下创建对应的子文件夹

# 编译器设置
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump

# 项目名称
PROJECT = CS

# 项目文件夹
PROJECT_DIR = mo_ban

# 编译标志
CFLAGS = -mcpu=cortex-m3 -march=armv7-m -Wall \
         -O3 -ffunction-sections -fdata-sections -fno-common \
         -flto -fno-exceptions -fno-unwind-tables -fno-use-cxa-atexit \
         $(shell find $(PROJECT_DIR) -type d -exec echo "-I{}" \;)
ASFLAGS = -mcpu=cortex-m3 -mfloat-abi=soft -march=armv7-m
LDFLAGS = -T stm32R6.ld -nostartfiles -Wl,--gc-sections -flto

# 源文件
C_SOURCES = $(shell find $(PROJECT_DIR) -name '*.c')
ASM_SOURCES = $(PROJECT_DIR)/start/startup_stm32f10x_ld.s

# 目标文件
OBJECTS = $(addprefix OBJ/$(PROJECT)/, $(notdir $(C_SOURCES:.c=.o)))
OBJECTS += OBJ/$(PROJECT)/startup_stm32f10x_ld.o

# 输出目录
OUTPUT_DIR = OBJ/$(PROJECT)/out

# 默认目标
all: $(OUTPUT_DIR) $(OUTPUT_DIR)/$(PROJECT).elf $(OUTPUT_DIR)/$(PROJECT).hex $(OUTPUT_DIR)/$(PROJECT).bin $(OUTPUT_DIR)/$(PROJECT).lst $(OUTPUT_DIR)/$(PROJECT).map

# 创建输出目录
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# 编译规则
OBJ/$(PROJECT)/%.o: $(PROJECT_DIR)/*/%.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ/$(PROJECT)/startup_stm32f10x_ld.o: $(PROJECT_DIR)/start/startup_stm32f10x_ld.s
	$(AS) $(ASFLAGS) -c $< -o $@

# 链接
$(OUTPUT_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@ -Wl,-Map=$(OUTPUT_DIR)/$(PROJECT).map,--cref
	$(SIZE) $@

# 生成hex文件
$(OUTPUT_DIR)/$(PROJECT).hex: $(OUTPUT_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

# 生成bin文件
$(OUTPUT_DIR)/$(PROJECT).bin: $(OUTPUT_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

# 生成反汇编文件
$(OUTPUT_DIR)/$(PROJECT).lst: $(OUTPUT_DIR)/$(PROJECT).elf
	$(OBJDUMP) -h -S $< > $@

# 清理
clean:
	rm -rf OBJ

.PHONY: all clean
