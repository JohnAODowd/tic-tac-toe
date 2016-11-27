#define Col_c4 3822 // 261.63 Hz period = 1/f in milli secs
#define Col_d4 3405 // 293.66 Hz all values calculated manually on calculator
#define Col_e4m 3214 // 311.13 Hz
#define Col_e4 3037 // 329.63 Hz
#define Col_f4 2863 // 349.23 Hz
#define Col_g4 2551 // 392.00 Hz
#define Col_a4m 2407 // 415.30 Hz
#define Col_a4 2272 // 440.00 Hz
#define Col_b4m 2025 // 493.88 Hz
#define Col_b4 2025 // 493.88 Hz
#define Col_c5 1911 // 523.25 Hz
#define Col_a5 1136 // 880.00 Hz
#define Col_b5 1012 // 987.77 Hz
#define rest 0
#define buzzer_out 12
static int note = 0;
static int beat = 0;
static long duration = 0;
static int hornpipe_tune[] = {Col_g4, Col_a5, Col_d4, Col_g4, Col_c4, Col_d4, Col_g4, Col_d4, Col_g4, Col_g4, Col_c4, Col_a5, Col_d4,  Col_g4, Col_c4, Col_d4, Col_g4};
static int hornpipe_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
static int hornpipe_MAXIMUM_COUNT = sizeof(hornpipe_tune) / sizeof(int); // Tune length i.o.t. loop

static int colmans_tune[] = {Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4, Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4};
static int colmans_beats[] = {30, 16, 20, 10, 40, 20, 60, 20, 40, 10, 40, 20, 30, 10, 60, 20};
static int colmans_MAXIMUM_COUNT = sizeof(colmans_tune) / sizeof(int);

static int StartingBuzzer_tune[] = {Col_c5, Col_b4m, Col_a4m, Col_e4, Col_c4};
static int StartingBuzzer_beats[] = {20, 20, 20, 20, 20};
static int StartingBuzzer_MAXIMUM_COUNT = sizeof(StartingBuzzer_tune) / sizeof(int); 
// tempo
#define tempo 30000 // Ver3 for Greensleeves original tempo lengthened from 10000 to 30000 
// length of pause
#define pause 5000 // original pause increased from 1000 to 5000
// add to loop to pause for 1 sec
static int rest_count = 100;
