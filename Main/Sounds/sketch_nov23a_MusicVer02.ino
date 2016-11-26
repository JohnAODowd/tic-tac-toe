/* Colman O'Keeffe 114712191 26 Nov 2016 - Final version to be copied into Main Program - Comments deleted to shorten code

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

int buzzer_out = 12;

void setup(){
  pinMode(buzzer_out, OUTPUT);
}

int colmans_tune[] = {Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4, Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4};
int colmans_beats[] = {30, 16, 20, 10, 40, 20, 60, 20, 40, 10, 40, 20, 30, 10, 60, 20};
int colmans_MAXIMUM_COUNT = sizeof(colmans_tune) / 2;

int Colmans_hornpipe_tune[] = {Col_e4, Col_c5, Col_f4, Col_d4, Col_c4, Col_a4m, Col_b4m, Col_a4m, Col_b4m, Col_e4, Col_c4, Col_e4, Col_c4, Col_d4, Col_c4, Col_a4m, Col_b4m};
int Colmans_hornpipe_beats[] = {40, 20, 20, 20, 20, 10, 8, 10, 8, 20, 20, 20, 20, 10, 10, 10, 10};
int Colmans_hornpipe_MAXIMUM_COUNT = sizeof(Colmans_hornpipe_tune) / 2;

int StartingBuzzer_tune[] = {Col_c5, Col_b4m, Col_a4m, Col_e4, Col_c4};
int StartingBuzzer_beats[] = {20, 20, 20, 20, 20};
int StartingBuzzer_MAXIMUM_COUNT = sizeof(StartingBuzzer_tune) / 2; // Tune length i.o.t. loop

int NO_OF_REPETITIONS = 1;
int MAXIMUM_COUNT = 0;

long tempo = 35000;  
int pause  = 10000; 
int rest_count = 200;

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

int reps = 1;
int music = 1;

void loop(){
  if (reps < NO_OF_REPETITIONS){
      if (music == 1){
        MAXIMUM_COUNT = StartingBuzzer_MAXIMUM_COUNT;
      } 
      if (music == 2){
        MAXIMUM_COUNT = colmans_MAXIMUM_COUNT;
      }
      if (music == 3){
        MAXIMUM_COUNT = Colmans_hornpipe_MAXIMUM_COUNT;
      }
      for (int timer = 0; timer < MAXIMUM_COUNT; timer++){
        if (music == 2){
          note = colmans_tune[timer];
          beat = colmans_beats[timer];        
        }
        if (music == 1){
          note = StartingBuzzer_tune[timer];
          beat = StartingBuzzer_beats[timer];        
        }
        if (music == 3){
          note = Colmans_hornpipe_tune[timer];
          beat = Colmans_hornpipe_beats[timer];        
        }
        duration = beat * tempo;
        play_note();
        delayMicroseconds(pause);
      }
      reps ++;
  }
   else{  
      digitalWrite(buzzer_out, LOW);
  }
}
