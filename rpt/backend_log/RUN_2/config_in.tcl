set ::env(PDK) "sky130A"
set ::env(STD_CELL_LIBRARY) "sky130_fd_sc_hd"
set script_dir $::env(DESIGN_DIR)
set ::env(DESIGN_NAME) lab1

set ::env(VERILOG_FILES) "\
    $script_dir/src/core_empty/lsu/*.v \
    $script_dir/src/core_empty/units/*.v \
    $script_dir/src/core_empty/pipeline/*.v \
    $script_dir/src/core_empty/core_empty.v \
    $script_dir/src/cache/cacheblock/std_dffe.v \
    $script_dir/src/cache/cacheblock/std_dffr.v \
    $script_dir/src/cache/*.v \
    $script_dir/src/*.v \
    $script_dir/src/params.vh"

set ::env(VERILOG_FILES_BLACKBOX) "$script_dir/src/cache/cacheblock/sky130_sram_1kbyte_1rw1r_32x256_8.v"
set ::env(EXTRA_LEFS) "$script_dir/src/macros/lef/sky130_sram_1kbyte_1rw1r_32x256_8.lef"
set ::env(EXTRA_GDS_FILES) "$script_dir/src/macros/gds/sky130_sram_1kbyte_1rw1r_32x256_8.gds"


## Clock configurations
set ::env(CLOCK_PORT) "clk"
set ::env(CLOCK_PERIOD) "50"