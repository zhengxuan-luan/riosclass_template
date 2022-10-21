# == Directories
SRC_DIR   := src
BUILD_DIR := build
DISASSEMBLY_DIR := build/disassembly
WAVE_DIR = build/wave
HEX_DIR = build/hex
# ==

# == Files
TESTS := $(shell find $(SRC_DIR)/rv64ui -type f -name '*.[Sc]')
TESTS += $(shell find $(SRC_DIR)/rv64mi -type f -name '*.[Sc]')
TEST_BINS  := $(patsubst $(SRC_DIR)/%.S, $(BUILD_DIR)/%, $(TESTS))
# ==

# == Tools
CC      := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump
OBJCOPY := riscv64-unknown-elf-objcopy
# ==

CFLAGS := -O0 -march=rv64i -mabi=lp64 -nostdlib -mcmodel=medany -fvisibility=hidden -static -I../include -Wl,-Bstatic,-T,../include/test.ld,--strip-debug -mno-relax

.SECONDARY:
.SECONDEXPANSION:
.PHONY: build clean

clean:
	find $(BUILD_DIR) -type f | xargs rm -f

build: $(TEST_BINS)  $(BUILD_DIR) $(DISASSEMBLY_DIR)

#由于64位链接器无法识别目录，需要手动添加目录
$(BUILD_DIR)/%: $(SRC_DIR)/%.S
	@echo "Building $@"
	$(CC) $(CFLAGS) $< -o $@
	$(OBJDUMP) -D $@ > $(patsubst $(BUILD_DIR)/%, $(DISASSEMBLY_DIR)/%.txt, $@)
	$(OBJCOPY) -O verilog $@  $(patsubst $(BUILD_DIR)/%, $(HEX_DIR)/%.hex, $@)
%/:
	mkdir -p $@


