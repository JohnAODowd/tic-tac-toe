/* Colman O'Keeffe 114712191 23 Nov 2016
* note frequencies from http://www.phy.mtu.edu/~suits/notefreqs.html 1540 23 Nov 2016
Ver 01 period = 1/f in milli secs all values calculated manually on calculator
Ver 02 all periods altered randomly to ensure a know tune is NOT used
the differance in the change in tones is not noticable to me as a layman. 
*/


# define Col_c4 3800 // approx 261.63 Hz
# define Col_d4 3400 // approx 293.66 Hz
# define Col_e4 3000 // approx 329.63 Hz 
# define Col_f4 2800 // approx 349.23 Hz
# define Col_g4 2500 // approx 392.00 Hz
# define Col_a4 2200 // approx 440.00 Hz
# define Col_b4 2000 // approx 493.88 Hz
# define Col_c5 1900 // approx 523.25 Hz
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

int colmans_tune[] = {Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4, Col_c4, Col_g4, Col_d4, Col_f4, Col_a4, Col_c5, Col_b4, Col_e4};
int colmans_beats[] = {30, 16, 20, 10, 40, 20, 60, 20, 40, 10, 40, 20, 30, 10, 60, 20};
int MAXIMUM_COUNT = sizeof(colmans_tune) / 2; // Tune length i.o.t. loop



// tempo
long tempo = 10000;
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
    note = colmans_tune[timer];
    beat = colmans_beats[timer];
    
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


