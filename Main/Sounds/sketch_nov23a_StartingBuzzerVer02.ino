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
/* debugging removed for Hornpipe for Lisa
  if (DEBUGGING){
    Serial.begin(9600); // serial out for debug code 
  }
*/
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
/* HornpipeVer01 http://www.guitarnick.com/sailors-hornpipe-irish-flatpicking-guitar-score-tab.html

int hornpipe_tune[] = {Col_g4, Col_a5, Col_d4, Col_g4, Col_c4, Col_d4, Col_g4, Col_d4, Col_g4, Col_g4, Col_c4, Col_a5, Col_d4,  Col_g4, Col_c4, Col_d4, Col_g4};
int hornpipe_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
int MAXIMUM_COUNT = sizeof(hornpipe_tune) / 2; // Tune length i.o.t. loop
*/
/* Colmans_hornpipe Ver01
int Colmans_hornpipe_tune[] = {Col_e4, Col_c5, Col_f4, Col_d4, Col_c4, Col_a4m, Col_b4m, Col_a4m, Col_b4m, Col_e4, Col_c4, Col_e4, Col_c4, Col_d4, Col_c4, Col_a4m, Col_b4m};
int Colmans_hornpipe_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
int MAXIMUM_COUNT = sizeof(Colmans_hornpipe_tune) / 2; // Tune length i.o.t. loop
*/
/* Hornpipe for Lisa - replaced Chord02 Col_c5 with Col_g4 - replaced Chord04 Col_d4 with Col_b4 - replaced Chord14 with Col_g4 with Col_f4
int Hornpipe_for_Lisa_tune[] = {Col_e4, Col_g4, Col_f4, Col_b4, Col_c4, Col_a4m, Col_b4m, Col_a4m, Col_b4m, Col_e4, Col_c4, Col_e4, Col_c4, Col_f4, Col_c4, Col_a4m, Col_b4m};
int Hornpipe_for_Lisa_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
int MAXIMUM_COUNT = sizeof(Hornpipe_for_Lisa_tune) / 2; // Tune length i.o.t. loop
Hornpipe for Lisa added NO_OF_REPETETIONS No - 5
*/
/*
int StartingBuzzer_tune[] = {Col_c5, Col_b4m, Col_a4m, Col_e4, Col_c4};
int StartingBuzzer_beats[] = {20, 20, 20, 20, 20};
// int MAXIMUM_COUNT = sizeof(StartingBuzzer_tune) / 2; // Tune length i.o.t. loop removed when creating Music function
// Starting Buzzer changed No of repetitions to 01
int StartingBuzzer_No_of_repetitions[] = {1};

// tempo
int StartingBuzzer_tempo[] = {35000};  // Ver3 for Greensleeves original tempo lengthened from 10000 to 30000 
                     // Hornpipe for Lisa tempo lenghtened from 30000 to 35000
// length of pause
int StartingBuzzer_pause[]  = {10000}; // original pause increased from 1000 to 5000
                    // Hornpipe for Lisa pause increased from 5000 to 10000
// add to loop to pause for 1 sec

int StartingBuzzer_rest_count[] = {200};

How to create an array with music information in it
StartingBuzzer[0] = sizeof(StartingBuzzer_tune)
StartingBuzzer[1] = StartingBuzzer_beats[]
StartingBuzzer[2] = StartingBuzzer_No_of_repetitions[]
StartingBuzzer[3] = StartingBuzzer_tempo[]
StartingBuzzer[4] = StartingBuzzer_pause[]
StartingBuzzer[5] = StartingBuzzer_rest_count[]}
StartingBuzzer[6-10] = tune
StartingBuzzer[11-15] = beats
StartingBuzzer[] ={5, 1, 35000, 10000, 200, Col_c5, 20, Col_b4m, 20, Col_a4m, 20, Col_e4, 20, Col_c4, 20};
*/

// Hornpipe for Lisa rest_count increased from 100 to 200
// setup variables for main function

int note = 0;
int beat = 0;
long duration = 0;
int reps = 0;
int rest_count = 0;

// try to play a note

void Music(int Tune_Selection){
  int Music_data[15];
  if (Tune_Selection == 1){
    // Starting Buzzer
    int Music_data[] = {5, 1, 35000, 10000, 200, Col_c5, 20, Col_b4m, 20, Col_a4m, 20, Col_e4, 20, Col_c4, 20};
  }
/*
How to create an array with music information in it
StartingBuzzer[0] = sizeof(StartingBuzzer_tune)
StartingBuzzer[1] = StartingBuzzer_beats[]
StartingBuzzer[2] = StartingBuzzer_No_of_repetitions[]
StartingBuzzer[3] = StartingBuzzer_tempo[]
StartingBuzzer[4] = StartingBuzzer_pause[]
StartingBuzzer[5] = StartingBuzzer_rest_count[]}
StartingBuzzer[6-10] = tune
StartingBuzzer[11-15] = beats
*/

    int No_of_repetitions = Music_data[2];
    long tempo = Music_data[3];
    int pause = Music_data[4];
    rest_count = Music_data[5];
    int Music_tune[Music_data[0]];
    int Music_beats[Music_data[0]];
    int music_index = Music_data[0];
    for (int index =0; index < Music_data[0]; index++){
      Music_tune[music_index] = Music_data[(5 + index)];
      Music_beats[music_index] = Music_data[(5 + index)];
    }
    int MAXIMUM_COUNT = sizeof(Music_tune) / 2; 
  
  if (reps < No_of_repetitions){
      for (int timer = 0; timer < MAXIMUM_COUNT; timer++){
        note = Music_tune[timer];
        beat = Music_beats[timer];
        duration = beat * tempo;
        play_note();
        delayMicroseconds(pause);
      }
      reps ++;
  }
   else{  
      digitalWrite(buzzer_out, LOW);
/* Debugging removed for Hornpipe for Lisa    
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
*/
  }
}


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
// Colmans Scale - Try to play the entire scale
// Hornpipe for Lisa added next line

void loop(){
  Music(1);
}


