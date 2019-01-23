/* Entry Point */
ENTRY(_start)

/* define heap and stack size */
__HEAP_SIZE            = 0 ;
__STACK_SIZE           = 4096*4 ;

SRAM_SIZE =  384K;    
/* Define SRAM Base Address */
SRAM_BASE_ADDR = 0x40000000;

/* Define CPU0 Local Data SRAM Allocation */
LOCALDMEM_SIZE = 64K;
/* Define CPU0 Local Data SRAM Base Address */
LOCALDMEM_BASE_ADDR = 0x50800000;
    
MEMORY
{

    flash_rchw : org = 0x00FA0000,   len = 0x4
    cpu0_reset_vec : org = 0x00FA0004,   len = 0x4
        
    m_text :	org = 0x1000000, len = 2048K  
    m_data :	org = 0x40000000,   len = 384K
    
    int_dram  : org = 0x50800000,   len = 64K    
}

