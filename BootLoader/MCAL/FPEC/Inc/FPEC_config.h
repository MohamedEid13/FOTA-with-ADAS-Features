#ifndef FPEC_CONFIG
#define FPEC_CONFIG

#define FLASH_START_ADDRESS   0x08000000

/***
 * For 64 kByte Flash it Ends at  : 0x0800FFFF
 * For 128 kByte Flash it Ends at : 0x0801FFFF
 */
#define FLASH_END_ADDRESS     0x0800FFFF


#define FIRSTAPP_STARTPAGE        5
#define FIRSTAPP_ENDPAGE         34

#define SECONDAPP_STARTPAGE      34
#define SECONDAPP_ENDPAGE        62


/*
 * 64 Page for 64 Kbyte Flash
 * 128 Page for 128 Kbyte Flash
 */
#define Flash_MAXPAGE            64

#endif
