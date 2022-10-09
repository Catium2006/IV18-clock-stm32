#pragma once

//栅极位
static constexpr uint16_t __index__[10] = {
    0b000000000,  // 空
    0b000000010,  // G1
    0b100000000,  // G2
    0b000000100,  // G3
    0b010000000,  // G4
    0b000001000,  // G5
    0b001000000,  // G6
    0b000100000,  // G7
    0b000010000,  // G8
    0b000000001   // G9
};

/*
    a
    dp
    d
    c
    e
    g
    b
    f
*/

/*         A
        +-----+
       /     /
    F /  G  / B
     +-----+
    /     /
 E /     / C
  +-----+   + DP
    D
这个输出信号控制的是每一位的高低电平,高电平则对应段被点亮,输出时候可以按位或
*/
#define __A__ 0b00000001
#define __B__ 0b01000000
#define __C__ 0b00001000
#define __D__ 0b00000100
#define __E__ 0b00010000
#define __F__ 0b10000000
#define __G__ 0b00100000
#define __DP__ 0b00000010

typedef __uint16_t uint16_t;

//巨大无比的手打表,标记什么字符该显示什么画面
static constexpr uint16_t charval[256] = {
    0,                                                           //空
    /*1 - 10*/                                                   //
    __A__,                                                       //
    __B__,                                                       //
    __C__,                                                       //
    __D__,                                                       //
    __E__,                                                       //
    __F__,                                                       //
    __G__,                                                       //
    __DP__,                                                      //
    0,                                                           //
    0,                                                           //
    /*11 - 20*/                                                  //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    /*21 - 30*/                                                  //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    /*31 - 35*/                                                  //
    0,                                                           //
    0,                                                           // ' '
    __D__ | __F__,                                               // '!'
    __B__ | __F__,                                               // '"'
    0,                                                           //
    /*36 - 40*/                                                  //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    __F__,                                                       // '' '
    __A__ | __D__ | __E__ | __F__,                               // '('
    /* 41 - 45*/                                                 //
        __A__ | __B__ | __C__ | __D__,                           // ')'
    0,                                                           //
    0,                                                           //
    __E__,                                                       // ','
    __G__,                                                       // '-'
    /*46 - 50*/                                                  //
    __DP__,                                                      // '.'
    __B__ | __E__ | __G__,                                       // '/'
    __A__ | __B__ | __C__ | __D__ | __E__ | __F__,               // '0'
    __B__ | __C__,                                               // '1'
    __A__ | __B__ | __D__ | __E__ | __G__,                       // '2'
    /*51 - 55*/                                                  //
        __A__ | __B__ | __C__ | __D__ | __G__,                   // '3'
    __B__ | __C__ | __F__ | __G__,                               // '4'
    __A__ | __C__ | __D__ | __F__ | __G__,                       // '5'
    __A__ | __C__ | __D__ | __E__ | __F__ | __G__,               // '6'
    __A__ | __B__ | __C__,                                       // '7'
    /*56 - 60*/                                                  //
        __A__ | __B__ | __C__ | __D__ | __E__ | __F__ | __G__,   // '8'
    __A__ | __B__ | __C__ | __D__ | __F__ | __G__,               // '9'
    0,                                                           //
    0,                                                           //
    0,                                                           //
    /*61 - 65*/                                                  //
        __D__ | __G__,                                           // '='
    0,                                                           //
    __A__ | __B__ | __E__ | __G__,                               // '?'
    0,                                                           //
    __A__ | __B__ | __C__ | __E__ | __F__ | __G__,               // 'A'
    /*66 - 70*/                                                  //
        __A__ | __B__ | __C__ | __D__ | __E__ | __F__ | __G__,   // 'B'
    __A__ | __D__ | __E__ | __F__,                               // 'C'
    __A__ | __B__ | __C__ | __D__ | __E__ | __F__,               // 'D'
    __A__ | __D__ | __E__ | __F__ | __G__,                       // 'E'
    __A__ | __E__ | __F__ | __G__,                               // 'F'
    /*71 - 75*/                                                  //
        __A__ | __C__ | __D__ | __E__ | __F__,                   // 'G'
    __B__ | __C__ | __E__ | __F__ | __G__,                       // 'H'
    __E__ | __F__,                                               // 'I'
    __B__ | __C__ | __D__,                                       // 'J'
    __A__ | __C__ | __E__ | __F__ | __G__,                       // 'K'
    /*76 - 80*/                                                  //
        __D__ | __E__ | __F__,                                   // 'L'
    __A__ | __C__ | __E__ | __G__,                               // 'M'
    __A__ | __B__ | __C__ | __E__ | __F__,                       // 'N'
    __A__ | __B__ | __C__ | __D__ | __E__ | __F__,               // 'O'
    __A__ | __B__ | __E__ | __F__ | __G__,                       // 'P'
    /*81 - 85*/                                                  //
        __A__ | __B__ | __C__ | __D__ | __E__ | __F__ | __DP__,  // 'Q'
    __A__ | __B__ | __C__ | __E__ | __F__ | __G__,               // 'R'
    __A__ | __C__ | __D__ | __F__ | __G__,                       // 'S'
    __A__ | __E__ | __F__,                                       // 'T'
    __B__ | __C__ | __D__ | __E__ | __F__,                       // 'U'
    /*86 - 90*/                                                  //
        __B__ | __C__ | __D__ | __E__ | __F__ | __G__,           // 'V'
    __B__ | __D__ | __F__ | __G__,                               // 'W'
    __B__ | __C__ | __E__ | __F__,                               // 'X'
    __B__ | __E__ | __F__ | __G__,                               // 'Y'
    __A__ | __B__ | __D__ | __E__,                               // 'Z'
    /*91 - 95*/                                                  //
        __A__ | __D__ | __E__ | __F__,                           // '['
    __C__ | __E__ | __F__,                                       // '\'
    __A__ | __B__ | __C__ | __D__,                               // ']'
    __A__ | __B__ | __F__,                                       // '^'
    __D__,                                                       // '_'
    /*96 - 100*/                                                 //
    __B__,                                                       // ' ''
    0,                                                           //
    __C__ | __D__ | __E__ | __F__ | __G__,                       // 'b'
    __D__ | __E__ | __G__,                                       // 'c'
    __B__ | __C__ | __D__ | __E__ | __G__,                       // 'd'
    /*101 - 105*/                                                //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    __C__ | __E__ | __F__ | __G__,                               // 'h'
    0,                                                           //
    /*106 - 110*/                                                //
        __C__ | __D__,                                           // 'j'
    0,                                                           //
    __E__ | __F__,                                               // 'l'
    0,                                                           //
    __C__ | __E__ | __G__,                                       // 'n'
    /*111 - 115*/                                                //
        __C__ | __D__ | __E__ | __G__,                           // 'o'
    0,                                                           //
    0,                                                           //
    __E__ | __G__,                                               // 'r'
    0,                                                           //
    /*116 - 120*/                                                //
        __D__ | __E__ | __F__ | __G__,                           // 't'
    __C__ | __D__ | __E__,                                       // 'u'
    __C__ | __D__ | __E__,                                       // 'v'
    0,                                                           //
    0,                                                           //
    /*121 -125*/                                                 //
    0,                                                           //
    0,                                                           //
    0,                                                           //
    __B__ | __C__,                                               // '|'
    0,                                                           //
    /*126 - 127*/                                                //
    0,                                                           //
    0                                                            //
};

#undef __A__
#undef __B__
#undef __C__
#undef __D__
#undef __E__
#undef __F__
#undef __G__
#undef __DP__