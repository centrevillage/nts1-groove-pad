/*
 * SRAM=16kb
 * FLASH=64kb
 */
ENTRY(Reset_Handler)

/* minimum heap size */
_Min_Heap_Size = 0;
/* minimum stack = 1K byte */
_Min_Stack_Size = 0x400;
/* estack address = end of ram address */
_estack = 0x20000000+16K;

MEMORY
{
  RAM (xrw)        : ORIGIN = 0x20000000, LENGTH = 16K
  FLASH (rx)       : ORIGIN = 0x08000000, LENGTH = 64K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))            /* Startup code */
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)                   /* remaining code */
    *(.text.*)                 /* remaining code */
    *(.rodata)                 /* read-only data (constants) */
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
     _etext = .;
     _sidata = _etext;
  } >FLASH
  
  .data : AT ( _sidata )
  {
    . = ALIGN(4);
    _sdata = . ;
    *(.ramtext*)
    . = ALIGN(4);
    *(.data*)
    *(.data.*)
    . = ALIGN(4);
     _edata = . ;
  } >RAM

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
   _ebss = . ;
  } >RAM
  
  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );
  
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM
}
