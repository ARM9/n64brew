
    #include "n64.inc"
    #include "n64_gfx.inc"

    .text
    .align 4
    .global screenNTSC
    .type   screenNTSC,@function
screenNTSC:
    .equ screen_ptr,$a0
    .equ status,    $a1

    .equ vi_ptr,    $t0
    .equ tmp,       $t1
    .equ width,     $t2
    .equ height,    $t3
    .equ fb_ptr,    $t4
    .equ fb_size,   $t5
    .equ const,     $t6

    .set at; .set noreorder

    lui vi_ptr,VI_BASE // A0 = VI Base Register (0xA4400000)
    sw status,VI_STATUS(vi_ptr) // Store Status/Control To VI Status Register (0xA4400000)

    lw fb_ptr,8(screen_ptr)    // ptr
    lw fb_size,12(screen_ptr)  // size
    xor tmp,fb_ptr,fb_size
    sw tmp,VI_ORIGIN(vi_ptr) // Store Origin To VI Origin Register (0xA4400004)

    .set noat
    lw width,0(screen_ptr)     // width
    sw width,VI_WIDTH(vi_ptr)  // Store Width To VI Width Register (0xA4400008)
    li tmp,0x200          // T0 = Vertical Interrupt (Interrupt When Current Half-Line 0x200)
    sw tmp,VI_V_INTR(vi_ptr) // Store Vertical Interrupt To VI Interrupt Register (0xA440000C)
    li tmp,0                     // T0 = Current Vertical Line (Current Half-Line, Sampled Once Per Line = 0)
    sw tmp,VI_V_CURRENT_LINE(vi_ptr) // Store Current Vertical Line To VI Current Register (0xA4400010)
    li tmp,0x3E52239      // T0 = Video Timing (Start Of Color Burst In Pixels from H-Sync = 3, Vertical Sync Width In Half Lines = 229, Color Burst Width In Pixels = 34, Horizontal Sync Width In Pixels = 57)
    sw tmp,VI_TIMING(vi_ptr) // Store Video Timing To VI Burst Register (0xA4400014)
    li tmp,0x20D          // T0 = Vertical Sync (Number Of Half-Lines Per Field = 525)
    sw tmp,VI_V_SYNC(vi_ptr) // Store Vertical Sync To VI V Sync Register (0xA4400018)
    li tmp,0xC15          // T0 = Horizontal Sync (5-bit Leap Pattern Used For PAL only = 0, Total Duration Of A Line In 1/4 Pixel = 3093)
    sw tmp,VI_H_SYNC(vi_ptr) // Store Horizontal Sync To VI H Sync Register (0xA440001C)
    li tmp,0xC150C15           // T0 = Horizontal Sync Leap (Identical To H Sync = 3093, Identical To H Sync = 3093)
    sw tmp,VI_H_SYNC_LEAP(vi_ptr) // Store Horizontal Sync Leap To VI Leap Register (0xA4400020)
    li tmp,0x6C02EC        // T0 = Horizontal Video (Start Of Active Video In Screen Pixels = 108, End Of Active Video In Screen Pixels = 748)
    sw tmp,VI_H_VIDEO(vi_ptr) // Store Horizontal Video To VI H Start Register (0xA4400024)
    li tmp,0x2501FF        // T0 = Vertical Video (Start Of Active Video In Screen Half-Lines = 37, End Of Active Video In Screen Half-Lines = 511)
    sw tmp,VI_V_VIDEO(vi_ptr) // Store Vertical Video To VI V Start Register (0xA4400028)
    li tmp,0xE0204         // T0 = Vertical Burst (Start Of Color Burst Enable In Half-Lines = 14, End Of Color Burst Enable In Half-Lines = 516)
    sw tmp,VI_V_BURST(vi_ptr) // Store Vertical Burst To VI V Burst Register (0xA440002C)

    li const,160
    divu $0,width,const
    mflo tmp
    sll tmp,tmp,8
    // li tmp,(0x100*(\width/160)) // T0 = X-Scale (Horizontal Subpixel Offset In 2.10 Format = 0, 1/Horizontal Scale Up Factor In 2.10 Format)
    sw tmp,VI_X_SCALE(vi_ptr)     // Store X-Scale To VI X Scale Register (0xA4400030)

    lw height,4(screen_ptr)   // height
    li const,60
    divu $0,height,const
    mflo tmp
    sll tmp,tmp,8
    // li tmp,(0x100*(\height/60)) // T0 = Y-Scale (Vertical Subpixel Offset In 2.10 Format = 0, 1/Vertical Scale Up Factor In 2.10 Format)
    sw tmp,VI_Y_SCALE(vi_ptr)     // Store Y-Scale To VI Y Scale Register (0xA4400034)

    jr $ra
    nop
    .size screenNTSC,.-screenNTSC


    .global swapFramebuffer
    .type swapFramebuffer,@function
swapFramebuffer:
    .equ screen_ptr,$a0

    .equ vi_ptr,    $t0
    .equ fb_ptr,    $t1
    .equ fb_size,   $t2
    .equ tmp,       $t3

    .set noat; .set noreorder
    lw fb_ptr,8(screen_ptr)
    lui vi_ptr,VI_BASE // A0 = VI Base Register (0xA4400000)
    lw fb_size,12(screen_ptr) // screen size in bytes

    sw fb_ptr,VI_ORIGIN(vi_ptr) // Store Origin To VI Origin Register (0xA4400004)
    xor tmp,fb_ptr,fb_size

    jr $ra
    sw tmp,8(screen_ptr)

    .size swapFramebuffer,.-swapFramebuffer


    .global waitScanline
    .type waitScanline,@function
waitScanline: // Wait For RDP To Reach Scanline
    .equ vi_ptr,$t0
    .equ tmp,   $t1

    .set noat; .set noreorder
    lui vi_ptr,VI_BASE // A0 = VI Base Register (0xA4400000)
0:
    lw tmp,VI_V_CURRENT_LINE(vi_ptr) // T1 = Current Scan Line
    sync // Sync Load
    bne tmp,$a0,0b // IF (Current Scan Line != Scan Line) Wait
    nop
    jr $ra
    nop // Delay Slot

    .size waitScanline,.-waitScanline

// vim:ft=mips
