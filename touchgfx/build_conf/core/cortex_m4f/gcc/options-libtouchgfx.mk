float_options := -mfpu=fpv4-sp-d16 -mfloat-abi=softfp

assembler_options    += -mthumb -mno-thumb-interwork -mcpu=cortex-m4 -march=armv7e-m -Wno-psabi $(float_options) -DCORE_M4 -D__irq="" -fno-exceptions
c_compiler_options   += -mthumb -mno-thumb-interwork -mcpu=cortex-m4 -march=armv7e-m -Wno-psabi $(float_options) -DCORE_M4 -D__irq="" -fno-exceptions
cpp_compiler_options += -mthumb -mno-thumb-interwork -mcpu=cortex-m4 -march=armv7e-m -Wno-psabi $(float_options) -DCORE_M4 -D__irq="" -fno-exceptions
linker_options       += -mthumb -mno-thumb-interwork -mcpu=cortex-m4 -march=armv7e-m -Wno-psabi $(float_options) -fno-exceptions
