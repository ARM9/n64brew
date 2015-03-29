

    .text
    .align 4
    .global plot
    .type plot, @function
# void plot(int x, int y, unsigned color, unsigned *framebuffer)
plot:
.equ x,     $a0
.equ y,     $a1
.equ color, $a2
.equ fb,    $a3

.equ tmp,   $t8
.equ const, $t9

    .set noat; .set noreorder
    li const, 320*2
    multu y, const
    sll $at, x, 1
    mflo tmp
    add tmp, $at
    add tmp, fb
    jr $ra
    sh color, 0(tmp)

    .align 4
    .global drawLine
    .type   drawLine, @function
# void drawLine(int x1, int y1, int x2, int y2, uint16_t color, uint16_t *framebuffer);
drawLine:
.equ x1, $a0
.equ y1, $a1
.equ x2, $a2
.equ y2, $a3

.equ fb,    $t0
.equ color, $t1
.equ dx,    $t2
.equ dy,    $t3
.equ sx,    $t4
.equ sy,    $t5
.equ err,   $t6
.equ e2,    $t7
.equ const, $t8
.equ tmp,   $t9

    .set at
    .set noreorder

    # prologue
    lw color,0x24($sp)
    lw fb,0x2C($sp)
    # sx = x2 > x1 ? 1 : -1;
    subu dx,x2,x1
    bgtz dx,0f
     li sx,1
    li sx,-1
0:
    # dx = abs(x2 - x1);
    sra tmp,dx,31
    xor dx,dx,tmp
    sub dx,dx,tmp
    # abs dx
    # sy = y2 > y1 ? 1 : -1;
    subu dy,y2,y1
    bgtz dy,0f
     li sy,1
    li sy,-1
0:
    # dy = abs(y2 - y1);
    sra tmp,dy,31
    xor dy,dy,tmp
    sub dy,dy,tmp
    # abs dy
    # err = (dy >= dx ? -dy : dx) / 2;
    bge dy,dx,0f
     sub tmp,$0,dy
    move tmp,dx
0:  sra err,tmp,1
    li const,320*2
    # while(1){
    multu y1,const
0:
    # plot(x1,y1,color,fb);
    mflo tmp
    # mul tmp,y1,const
    sll $at,x1,1
    add tmp,$at
    add tmp,fb
    sh color,0(tmp)
    # if(x1==x2 && y1==y2) break;
    # e2 = err;
    bne x1,x2,1f
     move e2,err
    bne y1,y2,1f
     move e2,err
    jr $ra
     nop
1:
    # if (e2 < dy)  { err += dx; y1 += sy; }
    bge e2,dy,1f
     sub tmp,$0,e2
    add err,dx
    add y1,sy
1:
    # if (-e2 < dx) { err -= dy; x1 += sx; }
    # sub tmp,$0,e2
    bge tmp,dx,0b
     multu y1,const
    sub err,dy
    # }
    j 0b
     add x1,sx

.size drawLine, .-drawLine

    .text
    .align 4
    .global drawCircle
    .type drawCircle, @function
# void drawCircle(int x1, int y1, unsigned radius, uint16_t color, uint16_t *framebuffer);
drawCircle:
.equ x1,    $a0
.equ y1,    $a1
.equ radius,$a2
.equ color, $a3

.equ fb,    $t0
.equ x2,    $t1
.equ y2,    $t2
.equ err,   $t3
.equ tx,    $t4
.equ ty,    $t5
.equ tmp,   $t6
.equ const, $t7

    .set at
    .set noreorder

    lw fb,0x24($sp)
    # int x2 = r;
    move x2,radius
    li y2,0
    # int err = 1 - x2;
    li tmp,1
    sub err,tmp,x2

    li const,320*2
    # while(x2 >= y2){
L0:
    blt x2,y2,_end
    add tx,x1,x2
    add ty,y1,y2
    # plot(tx,ty,color,fb);
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    add tx,x1,y2
    add ty,y1,x2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    sub tx,x1,x2
    add ty,y1,y2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    sub tx,x1,y2
    add ty,y1,x2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    sub tx,x1,x2
    sub ty,y1,y2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    sub tx,x1,y2
    sub ty,y1,x2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    add tx,x1,x2
    sub ty,y1,y2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    add tx,x1,y2
    sub ty,y1,x2
    mul tmp,ty,const
    sll tx,1
    add tmp,tx
    add tmp,fb
    sh color,0(tmp)

    # y2++;
    # if(err < 0){
    bgtz err,0f
    addi y2,1
    # err += 2 * y2 + 1
    sll tmp,y2,1
    addi tmp,1
    j L0
    add err,tmp
0:  # }else{
    # x2--;
    addi x2,-1
    # err += 2 * (y2 - x2 + 1)
    sub tmp,y2,x2
    addi tmp,1
    sll tmp,1
    j L0
    add err,tmp
    # }
_end:
    jr $ra
    nop
.size drawCircle, .-drawCircle

    .set reorder; .set at
# vim:ft=mips
