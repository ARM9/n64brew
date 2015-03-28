#==============
# N64 Graphics
#==============
.equ BPP0,  0x0000 # VI Status/Control: Color Depth Blank (No Data Or Sync) (Bit 0..1)
#*RESERVED*: equ 0x0001 # VI Status/Control: Color Depth Reserved (Bit 0..1)
.equ BPP16, 0x0002 # VI Status/Control: Color Depth 16BPP R5/G5/B5/A1 (Bit 0..1)
.equ BPP32, 0x0003 # VI Status/Control: Color Depth 32BPP R8/G8/B8/A8 (Bit 0..1)
.equ GAMMA_DITHER_EN, 0x00004 # VI Status/Control: Gamma Dither Enable (Requires: Gamma Enable) (Bit 2)
.equ GAMMA_EN,        0x00008 # VI Status/Control: Gamma Enable (Gamma Boost For YUV Images) (Bit 3)
.equ DIVOT_EN,    0x00010 # VI Status/Control: Divot Enable (Used With Anti-alias) (Bit 4)
.equ VBUS_CLK_EN, 0x00020 # VI Status/Control: Video Bus Clock Enable (Bit 5)
.equ INTERLACE, 0x00040 # VI Status/Control: Interlace/Serrate (Used With Interlaced Display) (Bit 6)
.equ TST_MODE,  0x00080 # VI Status/Control: Test Mode (Bit 7)
.equ AA_MODE_0, 0x00000 # VI Status/Control: AA Mode 0 = Anti­-alias & Resample (Always Fetch Extra Lines) (Bit 8..9)
.equ AA_MODE_1, 0x00100 # VI Status/Control: AA Mode 1 = Anti­-alias & Resample (Fetch Extra Lines When Needed) (Bit 8..9)
.equ AA_MODE_2, 0x00200 # VI Status/Control: AA Mode 2 = Resample Only (Bit 8..9)
.equ AA_MODE_3, 0x00300 # VI Status/Control: AA Mode 3 = Replicate Pixels & No Interpolation (Bit 8..9)
.equ DIAG_0, 0x00400 # VI Status/Control: Diagnotic 0 (Bit 10..11)
.equ DIAG_1, 0x00800 # VI Status/Control: Diagnotic 1 (Bit 10..11)
.equ PIXEL_ADV_0, 0x00000 # VI Status/Control: Pixel Advance 0 (Bit 12..15)
.equ PIXEL_ADV_1, 0x01000 # VI Status/Control: Pixel Advance 1 (Bit 12..15)
.equ PIXEL_ADV_2, 0x02000 # VI Status/Control: Pixel Advance 2 (Bit 12..15)
.equ PIXEL_ADV_3, 0x03000 # VI Status/Control: Pixel Advance 3 (Bit 12..15)
.equ PIXEL_ADV_4, 0x04000 # VI Status/Control: Pixel Advance 4 (Bit 12..15)
.equ PIXEL_ADV_5, 0x05000 # VI Status/Control: Pixel Advance 5 (Bit 12..15)
.equ PIXEL_ADV_6, 0x06000 # VI Status/Control: Pixel Advance 6 (Bit 12..15)
.equ PIXEL_ADV_7, 0x07000 # VI Status/Control: Pixel Advance 7 (Bit 12..15)
.equ PIXEL_ADV_8, 0x08000 # VI Status/Control: Pixel Advance 8 (Bit 12..15)
.equ PIXEL_ADV_9, 0x09000 # VI Status/Control: Pixel Advance 9 (Bit 12..15)
.equ PIXEL_ADV_A, 0x0A000 # VI Status/Control: Pixel Advance A (Bit 12..15)
.equ PIXEL_ADV_B, 0x0B000 # VI Status/Control: Pixel Advance B (Bit 12..15)
.equ PIXEL_ADV_C, 0x0C000 # VI Status/Control: Pixel Advance C (Bit 12..15)
.equ PIXEL_ADV_D, 0x0D000 # VI Status/Control: Pixel Advance D (Bit 12..15)
.equ PIXEL_ADV_E, 0x0E000 # VI Status/Control: Pixel Advance E (Bit 12..15)
.equ PIXEL_ADV_F, 0x0F000 # VI Status/Control: Pixel Advance F (Bit 12..15)
.equ DITHER_FILTER_EN, 0x10000 # VI Status/Control: Dither Filter Enable (Used With 16BPP Display) (Bit 16)

.macro ScreenNTSC width,height, status, origin 
  lui $a0,VI_BASE # A0 = VI Base Register (0xA4400000)
  li $t0,\status        # T0 = Status/Control
  sw $t0,VI_STATUS($a0) # Store Status/Control To VI Status Register (0xA4400000)
  la $t0,\origin        # T0 = Origin (Frame Buffer Origin In Bytes)
  sw $t0,VI_ORIGIN($a0) # Store Origin To VI Origin Register (0xA4400004)
  li $t0,\width         # T0 = Width (Frame Buffer Line Width In Pixels)
  sw $t0,VI_WIDTH($a0)  # Store Width To VI Width Register (0xA4400008)
  li $t0,0x200          # T0 = Vertical Interrupt (Interrupt When Current Half-Line 0x200)
  sw $t0,VI_V_INTR($a0) # Store Vertical Interrupt To VI Interrupt Register (0xA440000C)
  li $t0,0                     # T0 = Current Vertical Line (Current Half-Line, Sampled Once Per Line = 0)
  sw $t0,VI_V_CURRENT_LINE($a0) # Store Current Vertical Line To VI Current Register (0xA4400010)
  li $t0,0x3E52239      # T0 = Video Timing (Start Of Color Burst In Pixels from H-Sync = 3, Vertical Sync Width In Half Lines = 229, Color Burst Width In Pixels = 34, Horizontal Sync Width In Pixels = 57)
  sw $t0,VI_TIMING($a0) # Store Video Timing To VI Burst Register (0xA4400014)
  li $t0,0x20D          # T0 = Vertical Sync (Number Of Half-Lines Per Field = 525)
  sw $t0,VI_V_SYNC($a0) # Store Vertical Sync To VI V Sync Register (0xA4400018)
  li $t0,0xC15          # T0 = Horizontal Sync (5-bit Leap Pattern Used For PAL only = 0, Total Duration Of A Line In 1/4 Pixel = 3093)
  sw $t0,VI_H_SYNC($a0) # Store Horizontal Sync To VI H Sync Register (0xA440001C)
  li $t0,0xC150C15           # T0 = Horizontal Sync Leap (Identical To H Sync = 3093, Identical To H Sync = 3093)
  sw $t0,VI_H_SYNC_LEAP($a0) # Store Horizontal Sync Leap To VI Leap Register (0xA4400020)
  li $t0,0x6C02EC        # T0 = Horizontal Video (Start Of Active Video In Screen Pixels = 108, End Of Active Video In Screen Pixels = 748)
  sw $t0,VI_H_VIDEO($a0) # Store Horizontal Video To VI H Start Register (0xA4400024)
  li $t0,0x2501FF        # T0 = Vertical Video (Start Of Active Video In Screen Half-Lines = 37, End Of Active Video In Screen Half-Lines = 511)
  sw $t0,VI_V_VIDEO($a0) # Store Vertical Video To VI V Start Register (0xA4400028)
  li $t0,0xE0204         # T0 = Vertical Burst (Start Of Color Burst Enable In Half-Lines = 14, End Of Color Burst Enable In Half-Lines = 516)
  sw $t0,VI_V_BURST($a0) # Store Vertical Burst To VI V Burst Register (0xA440002C)
  li $t0,(0x100*(\width/160)) # T0 = X-Scale (Horizontal Subpixel Offset In 2.10 Format = 0, 1/Horizontal Scale Up Factor In 2.10 Format)
  sw $t0,VI_X_SCALE($a0)     # Store X-Scale To VI X Scale Register (0xA4400030)
  li $t0,(0x100*(\height/60)) # T0 = Y-Scale (Vertical Subpixel Offset In 2.10 Format = 0, 1/Vertical Scale Up Factor In 2.10 Format)
  sw $t0,VI_Y_SCALE($a0)     # Store Y-Scale To VI Y Scale Register (0xA4400034)
.endm

.macro ScreenPAL width,height, status, origin 
  lui $a0,VI_BASE # A0 = VI Base Register (0xA4400000)
  li $t0,\status        # T0 = Status/Control
  sw $t0,VI_STATUS($a0) # Store Status/Control To VI Status Register (0xA4400000)
  la $t0,\origin        # T0 = Origin (Frame Buffer Origin In Bytes)
  sw $t0,VI_ORIGIN($a0) # Store Origin To VI Origin Register (0xA4400004)
  li $t0,\width         # T0 = Width (Frame Buffer Line Width In Pixels)
  sw $t0,VI_WIDTH($a0)  # Store Width To VI Width Register (0xA4400008)
  li $t0,0x200          # T0 = Vertical Interrupt (Interrupt When Current Half-Line 0x200)
  sw $t0,VI_V_INTR($a0) # Store Vertical Interrupt To VI Interrupt Register (0xA440000C)
  li $t0,0                     # T0 = Current Vertical Line (Current Half-Line, Sampled Once Per Line = 0)
  sw $t0,VI_V_CURRENT_LINE($a0) # Store Current Vertical Line To VI Current Register (0xA4400010)
  li $t0,0x404233A      # T0 = Video Timing (Start Of Color Burst In Pixels from H-Sync = 4, Vertical Sync Width In Half Lines = 04, Color Burst Width In Pixels = 35, Horizontal Sync Width In Pixels = 58)
  sw $t0,VI_TIMING($a0) # Store Video Timing To VI Burst Register (0xA4400014)
  li $t0,0x271          # T0 = Vertical Sync (Number Of Half-Lines Per Field = 625)
  sw $t0,VI_V_SYNC($a0) # Store Vertical Sync To VI V Sync Register (0xA4400018)
  li $t0,0x150C69       # T0 = Horizontal Sync (5-bit Leap Pattern Used For PAL only = 21: %10101, Total Duration Of A Line In 1/4 Pixel = 3177)
  sw $t0,VI_H_SYNC($a0) # Store Horizontal Sync To VI H Sync Register (0xA440001C)
  li $t0,0xC6F0C6E           # T0 = Horizontal Sync Leap (Identical To H Sync = 3183, Identical To H Sync = 3182)
  sw $t0,VI_H_SYNC_LEAP($a0) # Store Horizontal Sync Leap To VI Leap Register (0xA4400020)
  li $t0,0x800300        # T0 = Horizontal Video (Start Of Active Video In Screen Pixels = 128, End Of Active Video In Screen Pixels = 768)
  sw $t0,VI_H_VIDEO($a0) # Store Horizontal Video To VI H Start Register (0xA4400024)
  li $t0,0x5F0239        # T0 = Vertical Video (Start Of Active Video In Screen Half-Lines = 95, End Of Active Video In Screen Half-Lines = 569)
  sw $t0,VI_V_VIDEO($a0) # Store Vertical Video To VI V Start Register (0xA4400028)
  li $t0,0x9026B         # T0 = Vertical Burst (Start Of Color Burst Enable In Half-Lines = 9, End Of Color Burst Enable In Half-Lines = 619)
  sw $t0,VI_V_BURST($a0) # Store Vertical Burst To VI V Burst Register (0xA440002C)
  li $t0,(0x100*(\width/160)) # T0 = X-Scale (Horizontal Subpixel Offset In 2.10 Format = 0, 1/Horizontal Scale Up Factor In 2.10 Format)
  sw $t0,VI_X_SCALE($a0)     # Store X-Scale To VI X Scale Register (0xA4400030)
  li $t0,(0x100*(\height/60)) # T0 = Y-Scale (Vertical Subpixel Offset In 2.10 Format = 0, 1/Vertical Scale Up Factor In 2.10 Format)
  sw $t0,VI_Y_SCALE($a0)     # Store Y-Scale To VI Y Scale Register (0xA4400034)
.endm

.macro WaitScanline scanline # Wait For RDP To Reach Scanline
  lui $a0,VI_BASE # A0 = VI Base Register (0xA4400000)
  li $t0,\scanline # T0 = Scan Line
  Wait\@:
    lw $t1,VI_V_CURRENT_LINE($a0) # T1 = Current Scan Line
    sync # Sync Load
    bne $t1,$t0,Wait\@ # IF (Current Scan Line != Scan Line) Wait
    nop # Delay Slot # ELSE Continue
.endm

# RDP Commands
.macro DPC start,end  # Run DPC Command Buffer: Start Address, End Address
  lui $a0,DPC_BASE # A0 = Reality Display Processer Control Interface Base Register (0xA4100000)
  la $a1,start # A1 = DPC Command Start Address
  sw $a1,DPC_START($a0) # Store DPC Command Start Address To DP Start Register (0xA4100000)
  addi $a1,end-start # A1 = DPC Command End Address
  sw $a1,DPC_END($a0) # Store DPC Command End Address To DP End Register (0xA4100004)
.endm

.macro No_Op  # No Effect On RDP Command Execution, Useful For Padding Command Buffers
  .word 0x00000000 # HI Word: COMMAND 0x00 (Bit 56..61)
  .word 0x00000000 # LO Word: Zero (Bit 0..31)
.endm

.macro Fill_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
  .word 0x08000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x08 (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Fill_ZBuffer_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4: Z Inverse Depth Integer, Fraction, DzDx Change In Z Per Change In X Coordinate Integer, Fraction (ZBuffer Coefficients)
# Word 5: DzDe Change In Z Along Major Edge Integer, Fraction, DzDy Change In Z Per Change In Y Coordinate Integer, Fraction
  .word 0x09000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x09 (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Texture_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  S Texture Coordinate Integer, T Texture Coordinate Integer, W Normalized Inverse Depth Integer (Texture Coefficients)
# Word 5:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Integer
# Word 6:  S Texture Coordinate Fraction, T Texture Coordinate Fraction, W Normalized Inverse Depth Fraction
# Word 7:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Fraction
# Word 8:  DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Integer
# Word 9:  DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Integer
# Word 10: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Fraction
# Word 11: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Fraction
  .word 0x0A000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0A (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Texture_ZBuffer_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  S Texture Coordinate Integer, T Texture Coordinate Integer, W Normalized Inverse Depth Integer (Texture Coefficients)
# Word 5:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Integer
# Word 6:  S Texture Coordinate Fraction, T Texture Coordinate Fraction, W Normalized Inverse Depth Fraction
# Word 7:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Fraction
# Word 8:  DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Integer
# Word 9:  DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Integer
# Word 10: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Fraction
# Word 11: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Fraction
# Word 12: Z Inverse Depth Integer, Fraction, DzDx Change In Z Per Change In X Coordinate Integer, Fraction (ZBuffer Coefficients)
# Word 13: DzDe Change In Z Along Major Edge Integer, Fraction, DzDy Change In Z Per Change In Y Coordinate Integer, Fraction
  .word 0x0B000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0B (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Shade_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  Red Color Component Integer, Green Color Component Integer, Blue Color Component Integer, Alpha Color Component Integer (Shade Coefficients)
# Word 5:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Integer
# Word 6:  Red Color Component Fraction, Green Color Component Fraction, Blue Color Component Fraction, Alpha Color Component Fraction
# Word 7:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Fraction
# Word 8:  DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Integer
# Word 9:  DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Integer
# Word 10: DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Fraction
# Word 11: DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Fraction
  .word 0x0C000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0C (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Shade_ZBuffer_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  Red Color Component Integer, Green Color Component Integer, Blue Color Component Integer, Alpha Color Component Integer (Shade Coefficients)
# Word 5:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Integer
# Word 6:  Red Color Component Fraction, Green Color Component Fraction, Blue Color Component Fraction, Alpha Color Component Fraction
# Word 7:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Fraction
# Word 8:  DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Integer
# Word 9:  DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Integer
# Word 10: DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Fraction
# Word 11: DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Fraction
# Word 12: Z Inverse Depth Integer, Fraction, DzDx Change In Z Per Change In X Coordinate Integer, Fraction (ZBuffer Coefficients)
# Word 13: DzDe Change In Z Along Major Edge Integer, Fraction, DzDy Change In Z Per Change In Y Coordinate Integer, Fraction
  .word 0x0D000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0D (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Shade_Texture_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  Red Color Component Integer, Green Color Component Integer, Blue Color Component Integer, Alpha Color Component Integer (Shade Coefficients)
# Word 5:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Integer
# Word 6:  Red Color Component Fraction, Green Color Component Fraction, Blue Color Component Fraction, Alpha Color Component Fraction
# Word 7:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Fraction
# Word 8:  DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Integer
# Word 9:  DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Integer
# Word 10: DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Fraction
# Word 11: DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Fraction
# Word 12: S Texture Coordinate Integer, T Texture Coordinate Integer, W Normalized Inverse Depth Integer (Texture Coefficients)
# Word 13: DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Integer
# Word 14: S Texture Coordinate Fraction, T Texture Coordinate Fraction, W Normalized Inverse Depth Fraction
# Word 15: DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Fraction
# Word 16: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Integer
# Word 17: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Integer
# Word 18: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Fraction
# Word 19: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Fraction
  .word 0x0E000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0E (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm

.macro Shade_Texture_Z_Buffer_Triangle lft,level,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf 
# Word 0: Left Major Flag (0=Left Major, 1=Right Major), Number Of Mip-Maps Minus One, Tile ID, Y Coordinate Of Low, Mid Minor, Major Edge (Fixed Point S.11.2)
# Word 1: X Coordinate Of Low    Edge Integer, Fraction, DxLDy Inverse Slope Of Low    Edge Integer, Fraction
# Word 2: X Coordinate Of Major  Edge Integer, Fraction, DxHDy Inverse Slope Of Major  Edge Integer, Fraction
# Word 3: X Coordinate Of Middle Edge Integer, Fraction, DxMDy Inverse Slope Of Middle Edge Integer, Fraction
# Word 4:  Red Color Component Integer, Green Color Component Integer, Blue Color Component Integer, Alpha Color Component Integer (Shade Coefficients)
# Word 5:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Integer
# Word 6:  Red Color Component Fraction, Green Color Component Fraction, Blue Color Component Fraction, Alpha Color Component Fraction
# Word 7:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Fraction
# Word 8:  DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Integer
# Word 9:  DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Integer
# Word 10: DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Fraction
# Word 11: DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Fraction
# Word 12: S Texture Coordinate Integer, T Texture Coordinate Integer, W Normalized Inverse Depth Integer (Texture Coefficients)
# Word 13: DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Integer
# Word 14: S Texture Coordinate Fraction, T Texture Coordinate Fraction, W Normalized Inverse Depth Fraction
# Word 15: DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Fraction
# Word 16: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Integer
# Word 17: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Integer
# Word 18: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Fraction
# Word 19: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Fraction
# Word 20: Z Inverse Depth Integer, Fraction, DzDx Change In Z Per Change In X Coordinate Integer, Fraction (ZBuffer Coefficients)
# Word 21: DzDe Change In Z Along Major Edge Integer, Fraction, DzDy Change In Z Per Change In Y Coordinate Integer, Fraction
  .word 0x0F000000|(\lft<<23)|(\level<<19)|(\tile<<16)|\yl # HI Word 0: COMMAND 0x0F (Bit 56..61), lft (Bit 55), Level (Bit 51..53), Tile (Bit 48..50), YL (Bit 32..45)
  .word (\ym<<16)|\yh                                   # LO Word 0: YM (Bit 16..29), YH (Bit 9..13)
  .word (\xl<<16)|\xlf       # HI Word 1: XL Integer (Bit 48..63), XL Fraction (Bit 32..47)
  .word (\dxldy<<16)|\dxldyf # LO Word 1: DxLDy Integer (Bit 16..31), DxLDy Fraction (Bit 0..15)
  .word (\xh<<16)|\xhf       # HI Word 2: XH Integer (Bit 48..63), XH Fraction (Bit 32..47)
  .word (\dxhdy<<16)|\dxhdyf # LO Word 2: DxHDy Integer (Bit 16..31), DxHDy Fraction (Bit 0..15)
  .word (\xm<<16)|\xmf       # HI Word 3: XM Integer (Bit 48..63), XM Fraction (Bit 32..47)
  .word (\dxmdy<<16)|\dxmdyf # LO Word 3: DxMDy Integer (Bit 16..31), DxMDy Fraction (Bit 0..15)
.endm


.macro Shade_Coefficients r,g,b,a, drdx,dgdx,dbdx,dadx, rf,gf,bf,af, drdxf,dgdxf,dbdxf,dadxf, drde,dgde,dbde,dade, drdy,dgdy,dbdy,dady, drdef,dgdef,dbdef,dadef, drdyf,dgdyf,dbdyf,dadyf 
# Word 0:  Red Color Component Integer, Green Color Component Integer, Blue Color Component Integer, Alpha Color Component Integer (Shade Coefficients)
# Word 1:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Integer
# Word 2:  Red Color Component Fraction, Green Color Component Fraction, Blue Color Component Fraction, Alpha Color Component Fraction
# Word 3:  DrDx Change In Red, DgDx Change In Green, DbDx Change In Blue, DaDx Change In Alpha Per Change In X Coordinate Fraction
# Word 4:  DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Integer
# Word 5:  DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Integer
# Word 6: DrDe Change In Red, DgDe Change In Green, DbDe Change In Blue, DaDe Change In Alpha Along The Edge Fraction
# Word 7: DrDy Change In Red, DgDy Change In Green, DbDy Change In Blue, DaDy Change In Alpha Per Change In Y Coordinate Fraction
  .word (\r<<16)|(\g&0xFFFF) # HI WORD 0: Red  Integer (Bit 48..63), Green Integer (Bit 32..47)
  .word (\b<<16)|(\a&0xFFFF) # LO WORD 0: Blue Integer (Bit 16..31), Alpha Integer (Bit 0..15)
  .word (\drdx<<16)|(\dgdx&0xFFFF) # HI WORD 1: DrDx Integer (Bit 48..63), DgDx Integer (Bit 32..47)
  .word (\dbdx<<16)|(\dadx&0xFFFF) # LO WORD 1: DbDx Integer (Bit 16..31), DbDx Integer (Bit 0..15)
  .word (\rf<<16)|\gf # HI WORD 2: Red  Fraction (Bit 48..63), Green Fraction (Bit 32..47)
  .word (\bf<<16)|\af # LO WORD 2: Blue Fraction (Bit 16..31), Alpha Fraction (Bit 0..15)
  .word (\drdxf<<16)|\dgdxf # HI WORD 3: DrDx Fraction (Bit 48..63), DgDx Fraction (Bit 32..47)
  .word (\dbdxf<<16)|\dadxf # LO WORD 3: DbDx Fraction (Bit 16..31), DbDx Fraction (Bit 0..15)
  .word (\drde<<16)|(\dgde&0xFFFF) # HI WORD 4: DrDe Integer (Bit 48..63), DgDe Integer (Bit 32..47)
  .word (\dbde<<16)|(\dade&0xFFFF) # LO WORD 4: DbDe Integer (Bit 16..31), DaDe Integer (Bit 0..15)
  .word (\drdy<<16)|(\dgdy&0xFFFF) # HI WORD 5: DrDy Integer (Bit 48..63), DgDy Integer (Bit 32..47)
  .word (\dbdy<<16)|(\dady&0xFFFF) # LO WORD 5: DbDy Integer (Bit 16..31), DaDy Integer (Bit 0..15)
  .word (\drdef<<16)|\dgdef # HI WORD 6: DrDe Fraction (Bit 48..63), DgDe Fraction (Bit 32..47)
  .word (\dbdef<<16)|\dadef # LO WORD 6: DbDe Fraction (Bit 16..31), DaDe Fraction (Bit 0..15)
  .word (\drdyf<<16)|\dgdyf # HI WORD 7: DrDy Fraction (Bit 48..63), DgDy Fraction (Bit 32..47)
  .word (\dbdyf<<16)|\dadyf # LO WORD 7: DbDy Fraction (Bit 16..31), DaDy Fraction (Bit 0..15)
.endm

.macro Texture_Coefficients s,t,w, dsdx,dtdx,dwdx, sf,tf,wf, dsdxf,dtdxf,dwdxf, dsde,dtde,dwde, dsdy,dtdy,dwdy, dsdef,dtdef,dwdef, dsdyf,dtdyf,dwdyf 
# Word 0:  S Texture Coordinate Integer, T Texture Coordinate Integer, W Normalized Inverse Depth Integer
# Word 1:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Integer
# Word 2:  S Texture Coordinate Fraction, T Texture Coordinate Fraction, W Normalized Inverse Depth Fraction
# Word 3:  DsDx Change In S, DtDx Change In T, DwDx Change In W Per Change In X Coordinate Fraction
# Word 4:  DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Integer
# Word 5:  DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Integer
# Word 6: DsDe Change In S, DtDe Change In T, DwDe Change In W Along The Edge Fraction
# Word 7: DsDy Change In S, DtDy Change In T, DwDy Change In W Per Change In Y Coordinate Fraction
  .word (\s<<16)|(\t&0xFFFF) # HI WORD 0: S Integer (Bit 48..63), T Integer (Bit 32..47)
  .word (\w<<16)           # LO WORD 0: W Integer (Bit 16..31)
  .word (\dsdx<<16)|(\dtdx&0xFFFF) # HI WORD 1: DsDx Integer (Bit 48..63), DtDx Integer (Bit 32..47)
  .word (\dwdx<<16)              # LO WORD 1: DwDx Integer (Bit 16..31)
  .word (\sf<<16)|\tf # HI WORD 2: S Fraction (Bit 48..63), T Fraction (Bit 32..47)
  .word (\wf<<16)    # LO WORD 2: W Fraction (Bit 16..31)
  .word (\dsdxf<<16)|\dtdxf # HI WORD 3: DsDx Fraction (Bit 48..63), DtDx Fraction (Bit 32..47)
  .word (\dwdxf<<16)       # LO WORD 3: DwDx Fraction (Bit 16..31)
  .word (\dsde<<16)|(\dtde&0xFFFF) # HI WORD 4: DsDe Integer (Bit 48..63), DtDe Integer (Bit 32..47)
  .word (\dwde<<16)              # LO WORD 4: DwDe Integer (Bit 16..31)
  .word (\dsdy<<16)|(\dtdy&0xFFFF) # HI WORD 5: DsDy Integer (Bit 48..63), DtDy Integer (Bit 32..47)
  .word (\dwdy<<16)              # LO WORD 5: DwDy Integer (Bit 16..31)
  .word (\dsdef<<16)|\dtdef # HI WORD 6: DsDe Fraction (Bit 48..63), DtDe Fraction (Bit 32..47)
  .word (\dwdef<<16)       # LO WORD 6: DwDe Fraction (Bit 16..31)
  .word (\dsdyf<<16)|\dtdyf # HI WORD 7: DsDy Fraction (Bit 48..63), DtDy Fraction (Bit 32..47)
  .word (\dwdyf<<16)       # LO WORD 7: DwDy Fraction (Bit 16..31)
.endm

.macro ZBuffer_Coefficients z,zf,dzdx,dzdxf, dzde,dzdef,dzdy,dzdyf 
# Word 0: Z Inverse Depth Integer, Fraction, DzDx Change In Z Per Change In X Coordinate Integer, Fraction (ZBuffer Coefficients)
# Word 1: DzDe Change In Z Along Major Edge Integer, Fraction, DzDy Change In Z Per Change In Y Coordinate Integer, Fraction
  .word (\z<<16)|(\zf&0xFFFF) # HI Word 0: Z Integer (Bit 48..63), Z Fraction (Bit 32..47)
  .word (\dzdx<<16)|\dzdxf   # LO Word 0: DzDx Integer (Bit 16..31), DzDx Fraction (Bit 0..15)
  .word (\dzde<<16)|\dzdef # HI Word 1: DzDe Integer (Bit 48..63), DzDe Fraction (Bit 32..47)
  .word (\dzdy<<16)|\dzdyf # LO Word 1: DzDy Integer (Bit 16..31), DzDy Fraction (Bit 0..15)
.endm

.macro Texture_Rectangle xl,yl, tile, xh,yh, s,t, dsdx,dtdy 
# Word 0: Bottom Right X/Y, Tile ID, Top Left X/Y (Fixed Point 10.2)
# Word 1: S/T Texture Coordinate Top Left (Fixed Point S.10.5), DsDx Change In S Per Change In X, DtDy Change In T Per Change In Y (Fixed Point S.5.10)
  .word 0x24000000|(\xl<<12)|\yl  # HI Word 0: COMMAND 0x24 (Bit 56..61), XL (Bit 44..55), YL (Bit 32..43)
  .word (\tile<<24)|(\xh<<12)|\yh # LO Word 0: Tile (Bit 24..26), XH (Bit 12..23), YH (Bit 0..11)
  .word (\s<<16)|\t       # HI Word 1: S (Bit 48..63), T (Bit 32..47)
  .word (\dsdx<<16)|\dtdy # LO Word 1: DsDx (Bit 16..31), DtDy (Bit 0..15)
.endm

.macro Texture_Rectangle_Flip xl,yl, tile, xh,yh, s,t, dsdx,dtdy  # Same As Texture Rectangle Except Hardware Swaps S/T & DsDx/DtDy
# Word 0: Bottom Right X/Y, Tile ID, Top Left X/Y (Fixed Point 10.2)
# Word 1: S/T Texture Coordinate Top Left (Fixed Point S.10.5), DsDx Change In S Per Change In X, DtDy Change In T Per Change In Y (Fixed Point S.5.10)
  .word 0x25000000|(\xl<<12)|\yl  # HI Word 0: COMMAND 0x25 (Bit 56..61), XL (Bit 44..55), YL (Bit 32..43)
  .word (\tile<<24)|(\xh<<12)|\yh # LO Word 0: Tile (Bit 24..26), XH (Bit 12..23), YH (Bit 0..11)
  .word (\s<<16)|\t       # HI Word 1: S (Bit 48..63), T (Bit 32..47)
  .word (\dsdx<<16)|\dtdy # LO Word 1: DsDx (Bit 16..31), DtDy (Bit 0..15)
.endm

.macro Sync_Load  # Stall Execution Of Load Commands, Until Preceeding Primitives Completely Finish (Usually Preceed Load Commands)
  .word 0x26000000 # HI Word: COMMAND 0x26 (Bit 56..61)
  .word 0x00000000 # LO Word: Zero (Bit 0..31)
.endm

.macro Sync_Pipe  # Stall Pipeline, Until Preceeding Primitives Completely Finish (Software Can Optimize Usage)
  .word 0x27000000 # HI Word: COMMAND 0x27 (Bit 56..61)
  .word 0x00000000 # LO Word: Zero (Bit 0..31)
.endm

.macro Sync_Tile  # Allows Synchronization Between Commands That Write To The Same Tile Descriptor That An Immediately Previous Command Is Reading
  .word 0x28000000 # HI Word: COMMAND 0x28 (Bit 56..61)
  .word 0x00000000 # LO Word: Zero (Bit 0..31)
.endm

.macro Sync_Full  # Stall RDP Until Last DRAM Buffer Is Read Or Written From Any Preceeding Primitive (Needed If Memory Is To Be Reused)
  .word 0x29000000 # HI Word: COMMAND 0x29 (Bit 56..61)
  .word 0x00000000 # LO Word: Zero (Bit 0..31)
.endm

.macro Set_Key_GB wg,wb,cg,sg,cb,sb  # Set The Coefficients Used For Green/Blue Keying, KEY G/B = CLAMP(0.0, -ABS((G/B - CENTER)* SCALE) + WIDTH, 1.0) KEY ALPHA = MINIMUM OF KEY R/G/B
# Word: WIDTH G/B (Size Of Half Key Window Including Soft Edge)*SCALE, CENTER G/B Defines Color Or Intensity At Which Key Is Active (0..255), SCALE GB 1.0/(SIZE OF SOFT EDGE) (0..255)
  .word 0x2A000000|(\wg<<12)|\wb        # HI Word: COMMAND 0x2A (Bit 56..61), WIDTH G (Bit 44..55), WIDTH B (Bit 32..43)
  .word (\cg<<24)|(\sg<<16)|(\cb<<8)|\sb # LO Word: CENTER G (Bit 24..31), SCALE G (Bit 16..23), CENTER B (Bit 8..15), SCALE B (Bit 0..7)
.endm

.macro Set_Key_R wr,cr,sr  # Set The Coefficients Used For Red Keying, KEY R = CLAMP(0.0, -ABS((R - CENTER)* SCALE) + WIDTH, 1.0) KEY ALPHA = MINIMUM OF KEY R/G/B
# Word: WIDTH R (Size Of Half Key Window Including Soft Edge)*SCALE, CENTER R Defines Color Or Intensity At Which Key Is Active (0..255), SCALE R 1.0/(SIZE OF SOFT EDGE) (0..255)
  .word 0x2B000000           # HI Word: COMMAND 0x2B (Bit 56..61)
  .word (\wr<<16)|(\cr<<8)|\sr # LO Word: WIDTH R (Bit 16..27), CENTER R (Bit 8..15), SCALE R (Bit 0..7)
.endm

.macro Set_Convert k0,k1,k2,k3,k4,k5  # Updates The Coefficients For Converting YUV Pixels To RGB, R = C0*(Y-16)+C1*V, G = C0*(Y-16)+C2*U-C3*V, B = C0*(Y-16)+C4*U
# Word: K0, K1, K2, K3, K4, K5 Term Of YUV-RGB Conversion Matrix
  .word 0x2C000000|(\k0<<45)|(\k1<<36)|(\k2>>5) # HI Word: COMMAND 0x2C (Bit 56..61), K0 (Bit 45..53), K1 (Bit 36..44), K2 (Bit 27..35)
  .word (\k2<<27)|(\k3<<18)|(\k4<<9)|\k5        # LO Word: K2 (Bit 27..35), K3 (Bit 18..26), K4 (Bit 9..17), K5 (Bit 0..8)
.endm

# Set_Scissor LO Word
.equ SCISSOR_EVEN,  0x00000000 # Set_Scissor O: Field Even (Bit 24)
.equ SCISSOR_ODD,   0x01000000 # Set_Scissor O: Field Odd (Bit 24)
.equ SCISSOR_FIELD, 0x02000000 # Set_Scissor F: Scissor Field Enable (Bit 25)
.macro Set_Scissor xh,yh,xl,yl,lo  # Set The Scissoring Of Primitives
# Word: Top Left X/Y, Bottom Right X/Y (Fixed Point 10.2), Scissor Field Enable & Scissor Field Even/Odd
  .word 0x2D000000|(\xh<<12)|\yh # HI Word: COMMAND 0x2D (Bit 56..61), XH (Bit 44..55), YH (Bit 32..43)
  .word \lo|(\xl<<12)|\yl        # LO Word: F (Bit 25), O (Bit 24), XL (Bit 12..23), YL (Bit 0..11)
.endm

.macro Set_Prim_Depth pz,pdz  # Set The Depth Of Primitives
# Word: Primitive Z Depth, Primitive Delta Z Depth
  .word 0x2E000000    # HI Word: COMMAND 0x2E (Bit 56..61)
  .word (\pz<<16)|\pdz # LO Word: PRIMITIVE Z (Bit 16..31), PRIMITIVE DELTA Z (Bit 0..15)
.endm

# Set_Other_Modes Lo Word
.equ ALPHA_COMPARE_EN, 0x00000001 # Set_Other_Modes A: Conditional Color Write On Alpha Compare (Bit 0)
.equ DITHER_ALPHA_EN,  0x00000002 # Set_Other_Modes B: Use Random Noise In Alpha Compare, Otherwise Use Blend Alpha In Alpha Compare (Bit 1)
.equ Z_SOURCE_SEL,     0x00000004 # Set_Other_Modes C: Choose Between Primitive Z And Pixel Z (Bit 2)
.equ ANTIALIAS_EN,     0x00000008 # Set_Other_Modes D: If Not Force Blend, Allow Blend Enable - Use CVG Bits (Bit 3)
.equ Z_COMPARE_EN,     0x00000010 # Set_Other_Modes E: Conditional Color Write Enable On Depth Comparison (Bit 4)
.equ Z_UPDATE_EN,      0x00000020 # Set_Other_Modes F: Enable Writing Of Z If Color Write Enabled (Bit 5)
.equ IMAGE_READ_EN,    0x00000040 # Set_Other_Modes G: Enable Color/CVG Read/Modify/Write Memory Access (Bit 6)
.equ COLOR_ON_CVG,     0x00000080 # Set_Other_Modes H: Only Update Color On Coverage Overflow (Transparent Surfaces) (Bit 7)
.equ CVG_DEST_CLAMP,   0x00000000 # Set_Other_Modes I: CVG Destination Clamp (Normal) (Bit 8..9)
.equ CVG_DEST_WRAP,    0x00000100 # Set_Other_Modes I: CVG Destination Wrap (WAS Assume Full CVG) (Bit 8..9)
.equ CVG_DEST_ZAP,     0x00000200 # Set_Other_Modes I: CVG Destination Zap (Force To Full CVG) (Bit 8..9)
.equ CVG_DEST_SAVE,    0x00000300 # Set_Other_Modes I: CVG Destination Save (Don't Overwrite Memory CVG) (Bit 8..9)
.equ Z_MODE_OPAQUE,           0x00000000 # Set_Other_Modes J: Z Mode Opaque (Bit 10..11)
.equ Z_MODE_INTERPENETRATING, 0x00000400 # Set_Other_Modes J: Z Mode Interpenetrating (Bit 10..11)
.equ Z_MODE_TRANSPARENT,      0x00000800 # Set_Other_Modes J: Z Mode Transparent (Bit 10..11)
.equ Z_MODE_DECAL,            0x00000C00 # Set_Other_Modes J: Z Mode Decal (Bit 10..11)
.equ CVG_TIMES_ALPHA,  0x00001000 # Set_Other_Modes K: Use CVG Times Alpha For Pixel Alpha And Coverage (Bit 12)
.equ ALPHA_CVG_SELECT, 0x00002000 # Set_Other_Modes L: Use CVG (Or CVG*Alpha) For Pixel Alpha (Bit 13)
.equ FORCE_BLEND,      0x00004000 # Set_Other_Modes M: Force Blend Enable (Bit 14)
#*RESERVED*:      equ 0x00008000 # Set_Other_Modes N: This Mode Bit Is Not Currently Used, But May Be In The Future (Bit 15)
.equ B_M2B_1_0, 0x00000000 # Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 0, Cycle 1 (Bit 16..17)
.equ B_M2B_1_1, 0x00010000 # Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 1, Cycle 1 (Bit 16..17)
.equ B_M2B_1_2, 0x00020000 # Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 2, Cycle 1 (Bit 16..17)
.equ B_M2B_1_3, 0x00030000 # Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 3, Cycle 1 (Bit 16..17)
.equ B_M2B_0_0, 0x00000000 # Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 0, Cycle 0 (Bit 18..19)
.equ B_M2B_0_1, 0x00040000 # Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 1, Cycle 0 (Bit 18..19)
.equ B_M2B_0_2, 0x00080000 # Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 2, Cycle 0 (Bit 18..19)
.equ B_M2B_0_3, 0x000C0000 # Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 3, Cycle 0 (Bit 18..19)
.equ B_M2A_1_0, 0x00000000 # Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 0, Cycle 1 (Bit 20..21)
.equ B_M2A_1_1, 0x00100000 # Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 1, Cycle 1 (Bit 20..21)
.equ B_M2A_1_2, 0x00200000 # Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 2, Cycle 1 (Bit 20..21)
.equ B_M2A_1_3, 0x00300000 # Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 3, Cycle 1 (Bit 20..21)
.equ B_M2A_0_0, 0x00000000 # Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 0, Cycle 0 (Bit 22..23)
.equ B_M2A_0_1, 0x00400000 # Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 1, Cycle 0 (Bit 22..23)
.equ B_M2A_0_2, 0x00800000 # Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 2, Cycle 0 (Bit 22..23)
.equ B_M2A_0_3, 0x00C00000 # Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 3, Cycle 0 (Bit 22..23)
.equ B_M1B_1_0, 0x00000000 # Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 0, Cycle 1 (Bit 24..25)
.equ B_M1B_1_1, 0x01000000 # Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 1, Cycle 1 (Bit 24..25)
.equ B_M1B_1_2, 0x02000000 # Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 2, Cycle 1 (Bit 24..25)
.equ B_M1B_1_3, 0x03000000 # Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 3, Cycle 1 (Bit 24..25)
.equ B_M1B_0_0, 0x00000000 # Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 0, Cycle 0 (Bit 26..27)
.equ B_M1B_0_1, 0x04000000 # Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 1, Cycle 0 (Bit 26..27)
.equ B_M1B_0_2, 0x08000000 # Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 2, Cycle 0 (Bit 26..27)
.equ B_M1B_0_3, 0x0C000000 # Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 3, Cycle 0 (Bit 26..27)
.equ B_M1A_1_0, 0x00000000 # Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 0, Cycle 1 (Bit 28..29)
.equ B_M1A_1_1, 0x10000000 # Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 1, Cycle 1 (Bit 28..29)
.equ B_M1A_1_2, 0x20000000 # Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 2, Cycle 1 (Bit 28..29)
.equ B_M1A_1_3, 0x30000000 # Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 3, Cycle 1 (Bit 28..29)
.equ B_M1A_0_0, 0x00000000 # Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 0, Cycle 0 (Bit 30..31)
.equ B_M1A_0_1, 0x40000000 # Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 1, Cycle 0 (Bit 30..31)
.equ B_M1A_0_2, 0x80000000 # Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 2, Cycle 0 (Bit 30..31)
.equ B_M1A_0_3, 0xC0000000 # Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 3, Cycle 0 (Bit 30..31)
# Set_Other_Modes HI Word
#*RESERVED*: equ 0x0000000F # Set_Other_Modes: Reserved For Future Use, Default Value Is 0xF (Bit 32..35)
.equ ALPHA_DITHER_SEL_PATTERN,   0x00000000 # Set_Other_Modes V1: Alpha Dither Selection Pattern (Bit 36..37)
.equ ALPHA_DITHER_SEL_PATTERNB,  0x00000010 # Set_Other_Modes V1: Alpha Dither Selection ~Pattern (Bit 36..37)
.equ ALPHA_DITHER_SEL_NOISE,     0x00000020 # Set_Other_Modes V1: Alpha Dither Selection Noise (Bit 36..37)
.equ ALPHA_DITHER_SEL_NO_DITHER, 0x00000030 # Set_Other_Modes V1: Alpha Dither Selection No Dither (Bit 36..37)
.equ RGB_DITHER_SEL_MAGIC_SQUARE_MATRIX,   0x00000000 # Set_Other_Modes V2: RGB Dither Selection Magic Square Matrix (Preferred If Filtered) (Bit 38..39)
.equ RGB_DITHER_SEL_STANDARD_BAYER_MATRIX, 0x00000040 # Set_Other_Modes V2: RGB Dither Selection Standard Bayer Matrix (Preferred If Not Filtered) (Bit 38..39)
.equ RGB_DITHER_SEL_NOISE,                 0x00000080 # Set_Other_Modes V2: RGB Dither Selection Noise (As Before) (Bit 38..39)
.equ RGB_DITHER_SEL_NO_DITHER,             0x000000C0 # Set_Other_Modes V2: RGB Dither Selection No Dither (Bit 38..39)
.equ KEY_EN,      0x00000100 # Set_Other_Modes W: Enables Chroma Keying (Bit 40)
.equ CONVERT_ONE, 0x00000200 # Set_Other_Modes X: Color Convert Texel That Was The Ouput Of The Texture Filter On Cycle0, Used To Qualify BI_LERP_1 (Bit 41)
.equ BI_LERP_1,   0x00000400 # Set_Other_Modes Y: 1=BI_LERP, 0=Color Convert Operation In Texture Filter. Used In Cycle 1 (Bit 42)
.equ BI_LERP_0,   0x00000800 # Set_Other_Modes Z: 1=BI_LERP, 0=Color Convert Operation In Texture Filter. Used In Cycle 0 (Bit 43)
.equ MID_TEXEL,   0x00001000 # Set_Other_Modes a: Indicates Texture Filter Should Do A 2x2 Half Texel Interpolation, Primarily Used For MPEG Motion Compensation Processing (Bit 44)
.equ SAMPLE_TYPE, 0x00002000 # Set_Other_Modes b: Determines How Textures Are Sampled: 0=1x1 (Point Sample), 1=2x2. Note That Copy (Point Sample 4 Horizontally Adjacent Texels) Mode Is Indicated By CYCLE_TYPE (Bit 45)
.equ TLUT_TYPE,   0x00004000 # Set_Other_Modes c: Type Of Texels In Table, 0=16b RGBA(5/5/5/1), 1=IA(8/8) (Bit 46)
.equ EN_TLUT,     0x00008000 # Set_Other_Modes d: Enable Lookup Of Texel Values From TLUT. Meaningful If Texture Type Is Index, Tile Is In Low TMEM, TLUT Is In High TMEM, And Color Image Is RGB (Bit 47)
.equ TEX_LOD_EN,  0x00010000 # Set_Other_Modes e: Enable Texture Level Of Detail (LOD) (Bit 48)
.equ SHARPEN_TEX_EN, 0x00020000 # Set_Other_Modes f: Enable Sharpened Texture (Bit 49)
.equ DETAIL_TEX_EN,  0x00040000 # Set_Other_Modes g: Enable Detail Texture (Bit 50)
.equ PERSP_TEX_EN,   0x00080000 # Set_Other_Modes h: Enable Perspective Correction On Texture (Bit 51)
.equ CYCLE_TYPE_1_CYCLE, 0x00000000 # Set_Other_Modes i: Display Pipeline Cycle Control Mode 1 Cycle (Bit 52..53)
.equ CYCLE_TYPE_2_CYCLE, 0x00100000 # Set_Other_Modes i: Display Pipeline Cycle Control Mode 2 Cycle (Bit 52..53)
.equ CYCLE_TYPE_COPY,    0x00200000 # Set_Other_Modes i: Display Pipeline Cycle Control Mode Copy (Bit 52..53)
.equ CYCLE_TYPE_FILL,    0x00300000 # Set_Other_Modes i: Display Pipeline Cycle Control Mode Fill (Bit 52..53)
#*RESERVED*: equ 0x00400000 # Set_Other_Modes j: This Mode Bit Is Not Currently Used, But May Be In The Future (Bit 54)
.equ ATOMIC_PRIM, 0x00800000 # Set_Other_Modes k: Force Primitive To Be Written To Frame Buffer Before Read Of Following Primitive
.macro Set_Other_Modes hi,lo  # Set The Other Modes
# Word: Set Other Mode Settings
  .word 0x2F00000F|\hi # HI Word: COMMAND 0x2F (Bit 56..61), Reserved 0xF (Bit 32..35)
  .word \lo           # LO Word
.endm

.macro Load_Tlut sl,tl,tile,sh,th  # Used To Initiate A Load From DRAM Of An Indexed Texture Lookup Table (TLUT) (This Table Dereferences Color Indexed Texels Before Texture Filtering)
# Word: Low S Index Into Table (0..255), Low T Normally Zero, Tile ID, High S Index Into Table, High T Normally Zero (Fixed Point 10.2, Fractional Bits Should Be Zero)
  .word 0x30000000|(\sl<<12)|\tl  # HI Word: COMMAND 0x34 (Bit 56..61), SL (Bit 44..55), TL (Bit 32..43)
  .word (\tile<<24)|(\sh<<12)|\th # LO Word: Tile (Bit 24..26), SH (Bit 12..23), TH (Bit 0..11)
.endm

.macro Set_Tile_Size sl,tl,tile,sh,th  # Set The Tile Size
# Word: Low S/T Coordinate Of Tile In Image, Tile ID, High S/T Coordinate Of Tile In Image (Fixed Point 10.2)
  .word 0x32000000|(\sl<<12)|\tl  # HI Word: COMMAND 0x32 (Bit 56..61), SL (Bit 44..55), TL (Bit 32..43)
  .word (\tile<<24)|(\sh<<12)|\th # LO Word: Tile (Bit 24..26), SH (Bit 12..23), TH (Bit 0..11)
.endm

.macro Load_Block sl,tl,tile,sh,dxt  # Loads A TMEM Tile With A Single Memory "Span" From SL,TL To SH,TL (During Tile Load, T Coordinate Is Incremented By DxT Every 8 TMEM Bytes)
# Word: Low S/T Coordinate Of Tile In Image, Tile ID, High S Coordinate Of Tile In Image (Fixed Point 10.2), Unsigned Increment Value
  .word 0x33000000|(\sl<<12)|\tl   # HI Word: COMMAND 0x33 (Bit 56..61), SL (Bit 44..55), TL (Bit 32..43)
  .word (\tile<<24)|(\sh<<12)|\dxt # LO Word: Tile (Bit 24..26), SH (Bit 12..23), DxT (Bit 0..11)
.endm

.macro Load_Tile sl,tl,tile,sh,th  # Loads A TMEM Tile
# Word: Low S/T Coordinate Of Tile In Image, Tile ID, High S/T Coordinate Of Tile In Image (Fixed Point 10.2)
  .word 0x34000000|(\sl<<12)|\tl  # HI Word: COMMAND 0x34 (Bit 56..61), SL (Bit 44..55), TL (Bit 32..43)
  .word (\tile<<24)|(\sh<<12)|\th # LO Word: Tile (Bit 24..26), SH (Bit 12..23), TH (Bit 0..11)
.endm

# Set_Tile LO Word
.equ SHIFT_S_0, 0x00000000 # Set_Tile: Shift 0 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_1, 0x00000001 # Set_Tile: Shift 1 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_2, 0x00000002 # Set_Tile: Shift 2 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_3, 0x00000003 # Set_Tile: Shift 3 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_4, 0x00000004 # Set_Tile: Shift 4 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_5, 0x00000005 # Set_Tile: Shift 5 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_6, 0x00000006 # Set_Tile: Shift 6 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_7, 0x00000007 # Set_Tile: Shift 7 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_8, 0x00000008 # Set_Tile: Shift 8 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_9, 0x00000009 # Set_Tile: Shift 9 Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_A, 0x0000000A # Set_Tile: Shift A Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_B, 0x0000000B # Set_Tile: Shift B Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_C, 0x0000000C # Set_Tile: Shift C Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_D, 0x0000000D # Set_Tile: Shift D Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_E, 0x0000000E # Set_Tile: Shift E Level Of Detail Shift For S Addresses (Bit 0..3)
.equ SHIFT_S_F, 0x0000000F # Set_Tile: Shift F Level Of Detail Shift For S Addresses (Bit 0..3)
.equ MASK_S_0, 0x00000000 # Set_Tile: Mask 0 For Wrapping/Mirroring In S Direction, Zero = Clamp (Bit 14..17)
.equ MASK_S_1, 0x00000010 # Set_Tile: Mask 1 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_2, 0x00000020 # Set_Tile: Mask 2 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_3, 0x00000030 # Set_Tile: Mask 3 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_4, 0x00000040 # Set_Tile: Mask 4 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_5, 0x00000050 # Set_Tile: Mask 5 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_6, 0x00000060 # Set_Tile: Mask 6 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_7, 0x00000070 # Set_Tile: Mask 7 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_8, 0x00000080 # Set_Tile: Mask 8 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_9, 0x00000090 # Set_Tile: Mask 9 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_A, 0x000000A0 # Set_Tile: Mask A For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_B, 0x000000B0 # Set_Tile: Mask B For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_C, 0x000000C0 # Set_Tile: Mask C For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_D, 0x000000D0 # Set_Tile: Mask D For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_E, 0x000000E0 # Set_Tile: Mask E For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MASK_S_F, 0x000000F0 # Set_Tile: Mask F For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
.equ MIRROR_S, 0x00000100 # Set_Tile: Mirror Enable For S Direction (Bit 8)
.equ CLAMP_S, 0x00000200 # Set_Tile: Clamp Enable For S Direction (Bit 9)
.equ SHIFT_T_0, 0x00000000 # Set_Tile: Shift 0 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_1, 0x00000400 # Set_Tile: Shift 1 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_2, 0x00000800 # Set_Tile: Shift 2 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_3, 0x00000C00 # Set_Tile: Shift 3 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_4, 0x00001000 # Set_Tile: Shift 4 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_5, 0x00001400 # Set_Tile: Shift 5 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_6, 0x00001800 # Set_Tile: Shift 6 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_7, 0x00001C00 # Set_Tile: Shift 7 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_8, 0x00002000 # Set_Tile: Shift 8 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_9, 0x00002400 # Set_Tile: Shift 9 Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_A, 0x00002800 # Set_Tile: Shift A Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_B, 0x00002C00 # Set_Tile: Shift B Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_C, 0x00003000 # Set_Tile: Shift C Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_D, 0x00003400 # Set_Tile: Shift D Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_E, 0x00003800 # Set_Tile: Shift E Level Of Detail Shift For T Addresses (Bit 10..13)
.equ SHIFT_T_F, 0x00003C00 # Set_Tile: Shift F Level Of Detail Shift For T Addresses (Bit 10..13)
.equ MASK_T_0, 0x00000000 # Set_Tile: Mask 0 For Wrapping/Mirroring In T Direction, Zero = Clamp (Bit 14..17)
.equ MASK_T_1, 0x00004000 # Set_Tile: Mask 1 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_2, 0x00008000 # Set_Tile: Mask 2 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_3, 0x0000C000 # Set_Tile: Mask 3 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_4, 0x00010000 # Set_Tile: Mask 4 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_5, 0x00014000 # Set_Tile: Mask 5 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_6, 0x00018000 # Set_Tile: Mask 6 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_7, 0x0001C000 # Set_Tile: Mask 7 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_8, 0x00020000 # Set_Tile: Mask 8 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_9, 0x00024000 # Set_Tile: Mask 9 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_A, 0x00028000 # Set_Tile: Mask A For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_B, 0x0002C000 # Set_Tile: Mask B For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_C, 0x00030000 # Set_Tile: Mask C For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_D, 0x00034000 # Set_Tile: Mask D For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_E, 0x00038000 # Set_Tile: Mask E For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MASK_T_F, 0x0003C000 # Set_Tile: Mask F For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
.equ MIRROR_T, 0x00040000 # Set_Tile: Mirror Enable For T Direction (Bit 18)
.equ CLAMP_T, 0x00080000 # Set_Tile: Clamp Enable For T Direction (Bit 19)
.equ PALETTE_0, 0x00000000 # Set_Tile: Palette Number 0 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_1, 0x00100000 # Set_Tile: Palette Number 1 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_2, 0x00200000 # Set_Tile: Palette Number 2 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_3, 0x00300000 # Set_Tile: Palette Number 3 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_4, 0x00400000 # Set_Tile: Palette Number 4 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_5, 0x00500000 # Set_Tile: Palette Number 5 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_6, 0x00600000 # Set_Tile: Palette Number 6 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_7, 0x00700000 # Set_Tile: Palette Number 7 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_8, 0x00800000 # Set_Tile: Palette Number 8 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_9, 0x00900000 # Set_Tile: Palette Number 9 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_A, 0x00A00000 # Set_Tile: Palette Number A For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_B, 0x00B00000 # Set_Tile: Palette Number B For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_C, 0x00C00000 # Set_Tile: Palette Number C For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_D, 0x00D00000 # Set_Tile: Palette Number D For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_E, 0x00E00000 # Set_Tile: Palette Number E For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
.equ PALETTE_F, 0x00F00000 # Set_Tile: Palette Number F For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
# Set_Tile/Set_Texture_Image/Set_Color_Image HI Word
.equ SIZE_OF_PIXEL_4B,  0x00000000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 4B (Bit 51..52)
.equ SIZE_OF_PIXEL_8B,  0x00080000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 8B (Bit 51..52)
.equ SIZE_OF_PIXEL_16B, 0x00100000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 16B (Bit 51..52)
.equ SIZE_OF_PIXEL_32B, 0x00180000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 32B (Bit 51..52)
.equ IMAGE_DATA_FORMAT_RGBA,       0x00000000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format RGBA (Bit 53..55)
.equ IMAGE_DATA_FORMAT_YUV,        0x00200000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format YUV (Bit 53..55)
.equ IMAGE_DATA_FORMAT_COLOR_INDX, 0x00400000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format COLOR_INDX (Bit 53..55)
.equ IMAGE_DATA_FORMAT_IA,         0x00600000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format IA (Bit 53..55)
.equ IMAGE_DATA_FORMAT_I,          0x00800000 # Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format I (Bit 53..55)
.macro Set_Tile hi,lo  # Set The Tile
# Word: Set Tile Settings
  .word 0x35000000|\hi # HI Word: COMMAND 0x35 (Bit 56..61), Image Data Format (Bit 53..55), Size Of Pixel/Texel Color Element (Bit 51..52), Size Of Tile Line In 64Bit Words Max Of 4KB (Bit 41..49), Starting TMEM Address For Tile (Bit 32..40)
  .word \lo           # LO Word: Tile (Bit 24..26), Palette (Bit 20..23), Clamp T (Bit 19), Mirror T (Bit 18), Mask T (Bit 14..17), Shift T (Bit 10..13), Clamp S (Bit 9), Mirror S (Bit 8), Mask S (Bit 4..7), Shift S (Bit 0..3)
.endm

.macro Fill_Rectangle xl,yl,xh,yh 
# Word: Bottom Right X/Y, Top Left X/Y (Fixed Point 10.2)
  .word 0x36000000|(\xl<<12)|\yl # HI Word: COMMAND 0x36 (Bit 56..61), XL (Bit 44..55), YL (Bit 32..43)
  .word (\xh<<12)|\yh           # LO Word: XH (Bit 12..23), YH (Bit 0..11)
.endm

.macro Set_Fill_Color lo  # Set The Filling Color
# Word: Packed Color: If The Color Image Was Set BE 16B RGBA, Then The Fill Color Would Be Two Horizontally Adjacent 16B RGBA Pixels
  .word 0x37000000 # HI Word: COMMAND 0x37 (Bit 56..61)
  .word \lo        # LO Word: Packed Color (Bit 0..31)
.endm

.macro Set_Fog_Color lo  # Set The Fog Color
# Word: RGBA Color Components
  .word 0x38000000 # HI Word: COMMAND 0x38 (Bit 56..61)
  .word \lo        # LO Word: Red Component (Bit 24..31), Green Component (Bit 16..23), Blue Component (Bit 8..15), Alpha Component (Bit 0..7)
.endm

.macro Set_Blend_Color lo  # Set The Blending Color
# Word: RGBA Color Components
  .word 0x39000000 # HI Word: COMMAND 0x39 (Bit 56..61)
  .word \lo        # LO Word: Red Component (Bit 24..31), Green Component (Bit 16..23), Blue Component (Bit 8..15), Alpha Component (Bit 0..7)
.endm

.macro Set_Prim_Color minlev,levfrac,lo  # Set The Primitive Color
# Word: Prim Min Level: Minimum Clamp For LOD Fraction When In Detail Or Sharpen Texture Modes (Fixed Point 0.5), Prim Level Frac: Level Of Detail Fraction For Primitive, Used Primarily In Multi-Tile Operations For Rectangle Primitives (Fixed Point 0.8), RGBA Color Components
  .word 0x3A000000|(\minlev<<8)|\levfrac # HI Word: COMMAND 0x3A (Bit 56..61), Prim Min Level (Bit 40..44), Prim Level Frac (Bit 32..39)
  .word \lo                            # LO Word: Red Component (Bit 24..31), Green Component (Bit 16..23), Blue Component (Bit 8..15), Alpha Component (Bit 0..7)
.endm

.macro Set_Env_Color lo  # Set The Environment Color
# Word: RGBA Color Components
  .word 0x3B000000 # HI Word: COMMAND 0x3B (Bit 56..61)
  .word \lo        # LO Word: Red Component (Bit 24..31), Green Component (Bit 16..23), Blue Component (Bit 8..15), Alpha Component (Bit 0..7)
.endm

.macro Set_Combine_Mode sub_aR0, mulR0, sub_aA0, mulA0, sub_aR1, mulR1, sub_bR0, sub_bR1, sub_aA1, mulA1, addR0, sub_bA0, addA0, addR1, sub_bA1, addA1  # Set The Combine Mode
# Word: SUB_A, Multiply Input RGB Components CYCLE 0, SUB_A, Multiply Input ALPHA Components CYCLE 0, SUB_A, Multiply Input RGB Components CYCLE 1, SUB_B, Multiply Input RGB Components CYCLE 0, SUB_B, Multiply Input RGB Components CYCLE 1, SUB_A, Multiply Input ALPHA Components CYCLE 1, Adder Input RGB Components CYCLE 0, SUB_B Input ALPHA Components CYCLE 0, Adder Input ALPHA Components CYCLE 0, Adder Input RGB Components CYCLE 1, SUB_B Input ALPHA Components CYCLE 1, Adder Input ALPHA Components CYCLE 1
  .word 0x3C000000|(\sub_aR0<<20)|(\mulR0<<15)|(\sub_aA0<<12)|(\mulA0<<9)|(\sub_aR1<<5)|\mulR1 # HI Word: COMMAND 0x3C (Bit 56..61), Sub A RGB Cycle 0 (Bit 52..55), Multiply RGB Cycle 0 (Bit 47..51), Sub A Alpha Cycle 0 (Bit 44..46), Multiply Alpha Cycle 0 (Bit 41..43), Sub A RGB Cycle 1 (Bit 37..40), Multiply RGB Cycle 1 (Bit 32..36)
  .word (\sub_bR0<<28)|(\sub_bR1<<24)|(\sub_aA1<<21)|(\mulA1<<18)|(\addR0<<15)|(\sub_bA0<<12)|(\addA0<<9)|(\addR1<<6)|(\sub_bA1<<3)|\addA1 # LO Word: Sub B RGB Cycle 0 (Bit 28..31), Sub B RGB Cycle 1 (Bit 24..27), Sub A Alpha Cycle 1 (Bit 21..23), Multiply Alpha Cycle 1 (Bit 18..20), Adder RGB Cycle 0 (Bit 15..17), Sub B Alpha Cycle 0 (Bit 12..14), Adder Alpha Cycle 0 (Bit 9..11), Adder RGB Cycle 1 (Bit 6..8), Sub B Alpha Cycle 1 (Bit 3..5), Adder Alpha Cycle 1 (Bit 0..2)
.endm

.macro Set_Texture_Image hi,lo  # Set The Texture Image
# Word: Image Data Format, Size Of Pixel/Texel Color Element, Width Of Image In Pixels - 1, Base Address (Top Left Corner) Of Image In DRAM
  .word 0x3D000000|\hi # HI Word: COMMAND 0x3D (Bit 56..61), Image Data Format (Bit 53..55), Size Of Pixel/Texel Color Element (Bit 51..52), Width Of Image In Pixels - 1 (Bit 32..41)
  .word \lo           # LO Word: Base Address (Top Left Corner) Of Image In DRAM, In Bytes (Bit 0..25)
.endm

.macro Set_Z_Image lo  # Set The Z Buffer Image
# Word: Base Address (Top Left Corner) Of Image In DRAM, In Bytes
  .word 0x3E000000 # HI Word: COMMAND 0x3E (Bit 56..61)
  .word \lo        # LO Word: Base Address (Top Left Corner) Of Image In DRAM, In Bytes (Bit 0..25)
.endm

.macro Set_Color_Image hi,lo  # Set The Color Image
# Word: Image Data Format, Size Of Pixel/Texel Color Element, Width Of Image In Pixels: Image Width=Width+1, Base Address (Top Left Corner) Of Image In DRAM
  .word 0x3F000000|\hi # HI Word: COMMAND 0x3F (Bit 56..61), Image Data Format (Bit 53..55), Size Of Pixel/Texel Color Element (Bit 51..52), Width Of Image In Pixels: Image Width=Width+1 (Bit 32..41)
  .word \lo           # LO Word: Base Address (Top Left Corner) Of Image In DRAM, In Bytes (Bit 0..25)
.endm
# vim:ft=mips
