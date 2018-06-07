assembler_options    += -mthumb -mno-thumb-interwork -mcpu=cortex-m3 -march=armv7-m -Wno-psabi -DCORE_M3 -D__irq="" -fno-exceptions
c_compiler_options   += -mthumb -mno-thumb-interwork -mcpu=cortex-m3 -march=armv7-m -Wno-psabi -DCORE_M3 -D__irq="" -fno-exceptions
cpp_compiler_options += -mthumb -mno-thumb-interwork -mcpu=cortex-m3 -march=armv7-m -Wno-psabi -DCORE_M3 -D__irq="" -fno-exceptions
linker_options       += -mthumb -mno-thumb-interwork -mcpu=cortex-m3 -march=armv7-m -Wno-psabi -fno-exceptions
