ENTRY(main);

SECTIONS
{
    . = 0x08000000;
    .text :
    {   /* BYTE，SHORT，LONG，QUAD 命令分别存储 1，2，4，8 字节 */
        LONG(0x20010000);
        LONG(main | 1);
        *(.text)
        *(.text*)
    }
}