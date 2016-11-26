#define DDRD_PINS 0xFC
#define DDRB_PINS 0x7
#define ROW1 0x4
#define ROW2 0x8
#define ROW3 0x10
#define YLW_1 0x20
#define YLW_2 0x40
#define YLW_3 0x80
#define RED_1 0x1
#define RED_2 0x2
#define RED_3 0x4
#define RFRSH_RATE 1
#define CLR 0x0
#define Y1R1 YLW_1 | ROW2 | ROW3
#define Y2R1 YLW_2 | ROW2 | ROW3
#define Y3R1 YLW_3 | ROW2 | ROW3
#define Y1R2 YLW_1 | ROW1 | ROW3
#define Y2R2 YLW_2 | ROW1 | ROW3
#define Y3R2 YLW_3 | ROW1 | ROW3
#define Y1R3 YLW_1 | ROW2 | ROW1
#define Y2R3 YLW_2 | ROW2 | ROW1
#define Y3R3 YLW_3 | ROW2 | ROW1
#define ROW1_ON ROW2 | ROW3
#define ROW2_ON ROW1 | ROW3
#define ROW3_ON ROW1 | ROW2
int YLWS[] = {Y1R1,Y2R1,Y3R1,Y1R2,Y2R2,Y3R2,Y1R3,Y2R3,Y3R3};
int ROWS[] = {ROW1_ON,ROW2_ON,ROW3_ON};
int REDS[] = {RED_1,RED_2,RED_3};
