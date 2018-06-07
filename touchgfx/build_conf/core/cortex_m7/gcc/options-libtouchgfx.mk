float_options := -mfpu=fpv5-sp-d16 -mfloat-abi=softfp

assembler_options    += -mthumb -mno-thumb-interwork -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq="" -fno-exceptions
c_compiler_options   += -mthumb -mno-thumb-interwork -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq="" -fno-exceptions
cpp_compiler_options += -mthumb -mno-thumb-interwork -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq="" -fno-exceptions
linker_options       += -mthumb -mno-thumb-interwork -mcpu=cortex-m7 -Wno-psabi $(float_options) -fno-exceptions
