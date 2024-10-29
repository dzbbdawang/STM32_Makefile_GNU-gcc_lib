MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x20000
    RAM (rw) : ORIGIN = 0x20000000, LENGTH = 0x2800
}

/* 变量赋值 - 保留原有定义 */
__initial_sp = ORIGIN(RAM) + LENGTH(RAM) + 1;
__heap_base = __initial_sp - 0x1000;
__heap_limit = __heap_base - 0x500;

_estack = __initial_sp;
Heap_Mem = __heap_base;
Stack_Mem = __initial_sp;

ENTRY(ResetHandler)

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        _stext = .;
        __Vectors = .;
        *(.text)
        *(.text.*)
        KEEP(*(.init))
        . = ALIGN(4);
        _etext = .;

        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
        _sidata = LOADADDR(.data);
    } > RAM AT> FLASH

    .bss :
    {
        PROVIDE(_sbss = .);
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        PROVIDE(_ebss = .);
    } > RAM

    /* 堆段 - 使用启动文件中定义的 .heap 段 */
    .heap :
    {
        PROVIDE(__heap_base = .);
        *(.heap)
        . = ALIGN(8);
        PROVIDE(__heap_limit = .);
    } > RAM

    /* 栈段 - 使用启动文件中定义的 .stack 段 */
    .stack :
    {
        . = ALIGN(8);
        *(.stack)
        . = ALIGN(8);
        PROVIDE(__initial_sp = .);
    } > RAM
}
