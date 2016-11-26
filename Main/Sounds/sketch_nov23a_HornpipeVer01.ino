/* Colman O'Keeffe 114712191 23 Nov 2016
* note frequencies from http://www.phy.mtu.edu/~suits/notefreqs.html 1540 23 Nov 2016
Ver 01 period = 1/f in milli secs all values calculated manually on calculator
Ver 02 all periods altered randomly to ensure a know tune is NOT used
the differance in the change in tones is not noticable to me as a layman. 
Ver 3 returned note values to original values added A4 minor, B4 minor, E4 Minor & B5
Hornpipe Ver01 added A5
*/

# define Col_c4 3822 // 261.63 Hz period = 1/f in milli secs
# define Col_d4 3405 // 293.66 Hz all values calculated manually on calculator
# define Col_e4m 3214 // 311.13 Hz
# define Col_e4 3037 // 329.63 Hz
# define Col_f4 2863 // 349.23 Hz
# define Col_g4 2551 // 392.00 Hz
# define Col_a4m 2407 // 415.30 Hz
# define Col_a4 2272 // 440.00 Hz
# define Col_b4m 2025 // 493.88 Hz
# define Col_b4 2025 // 493.88 Hz
# define Col_c5 1911 // 523.25 Hz
# define Col_a5 1136 // 880.00 Hz
# define Col_b5 1012 // 987.77 Hz

# define rest 0

// buzzer
int buzzer_out = 12;

// debugging serial out? 1 yes 0 no
int DEBUGGING = 0;

void setup(){
  pinMode(buzzer_out, OUTPUT);
  if (DEBUGGING){
    Serial.begin(9600); // serial out for debug code 
  }
}
/* Colmans tune test scale
int colmans_tune[] = {Col_c4, Col_d4, Col_e4, Col_f4, Col_g4, Col_a4, Col_b4, Col_c5};
int colmans_beats[] = {16, 16, 16, 16, 16, 16, 16, 16};
int MAXIMUM_COUNT = sizeof(colmans_tune) / 2; // Tune length i.o.t. loop
*/
// Ver 1 change scale notes in random order altered length of beats in random order
// Ver 2a doubled length of notes in tune added random beats
/*
int colmans_tune[] = {Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4, Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4};
int colmans_beats[] = {30, 16, 20, 10, 40, 20, 60, 20, 40, 10, 40, 20, 30, 10, 60, 20};
int MAXIMUM_COUNT = sizeof(colmans_tune) / 2; // Tune length i.o.t. loop
*/
/* Ver 3 attempt at Greensleeves
* chords from https://www.acousticmusicarchive.com/greensleeves-chords-lyrics
int colmans_tune[] = {Col_g4, Col_d4, Col_b4m, Col_a4m, Col_b4, Col_g4, Col_d4, Col_b4m, Col_c4, Col_b5, Col_e4m};
int colmans_beats[] = {60, 20, 20, 60, 40, 60, 20, 40, 40, 10, 30};
int MAXIMUM_COUNT = sizeof(colmans_tune) / 2; // Tune length i.o.t. loop
*/

int hornpipe_tune[] = {Col_g4, Col_a5, Col_d4, Col_g4, Col_c4, Col_d4, Col_g4, Col_d4, Col_g4, Col_g4, Col_c4, Col_a5, Col_d4,  Col_g4, Col_c4, Col_d4, Col_g4};
int hornpipe_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
int MAXIMUM_COUNT = sizeof(hornpipe_tune) / 2; // Tune length i.o.t. loop

// tempo
long tempo = 30000;  // Ver3 for Greensleeves original tempo lengthened from 10000 to 30000 
// length of pause
int pause  = 5000; // original pause increased from 1000 to 5000
// add to loop to pause for 1 sec
int rest_count = 100;

// setup variables for main function
int note = 0;
int beat = 0;
long duration = 0;

// try to play a note
void play_note(){
  long time_so_far = 0;
  if (note > 0){
    while(time_so_far < duration){
      // buzzer on
      digitalWrite(buzzer_out, HIGH);
      delayMicroseconds(note / 2);
      // buzzer off
      digitalWrite(buzzer_out, LOW);
      delayMicroseconds(note / 2);
      // how much time has gone by
      time_so_far += (note);
    }
  }
  else{
    for (int restbeat = 0; restbeat < rest_count; restbeat++){
      delayMicroseconds(duration);
    }
  }
}

// Try to play the entire scale
void loop(){
  for (int timer = 0; timer < MAXIMUM_COUNT; timer++){
    note = hornpipe_tune[timer];
    beat = hornpipe_beats[timer];
    
    duration = beat * tempo;
    
    play_note();
    
    delayMicroseconds(pause);
    
    if (DEBUGGING){
      Serial.println(timer);
      Serial.println("times round loop:");
      Serial.println(note);
      Serial.println("-note");
      Serial.println(beat);
      Serial.println("-beat");
      Serial.println(duration);
      Serial.println("-duration");
    }
  }
}


