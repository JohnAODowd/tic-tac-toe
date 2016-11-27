#include <EEPROM.h>
#ifndef DF_GUARD
#include "defines.h"
#endif
#include "IRremote.h"
#include "game_logic.c"
#include "sounds.h"
/*
 YELLOW LEDS ON PORTS: 2,3,4
 RED LEDS ON PORTS: 5,6,7
 ROW CONTROLLS ON PORTS: 8,9,10
*/
static char REDS[] = {RED1,RED2,RED3};
static char YLWS[] = {YLW1,YLW2,YLW3};
static char ROWS[] = {ROW1,ROW2,ROW3};
IRrecv irrecv(IR_PIN);
decode_results results;
void invalid_move();
void clear_pins();
void light_led();
void write_ledS(char arr[LED_CNT][LED_CNT]);
void light_color(char color);
void choose_color();
void play_note(char col);
void horn_pipe();
void victory_tune();

void setup() {
  // put your setup code here, to run once:
  DDRD |= DDRD_PINS;
  DDRB |= DDRB_PINS;
  clear_pins();
  irrecv.enableIRIn();
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  char turn = EEPROM.read(TRN_ADDR);
  #ifdef DEBUG
  Serial.println(turn,DEC);
  #endif DEBUG
  if(turn != RED && turn != YLW){
    game_state.yellow_player = PLYR_ONE;
    game_state.red_player = PLYR_TWO;
  }else if(turn == RED) {
    game_state.yellow_player = PLYR_TWO;
    game_state.red_player = PLYR_ONE;
  }else if(turn == YLW){
    game_state.yellow_player = PLYR_ONE;
    game_state.red_player = PLYR_TWO;
  }
  game_state.state = NOT_STRTD;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(game_state.state == INVALID_MOVE) invalid_move();
    if (!gameOver()) write_leds(board); 
    if (game_state.state == NOT_STRTD){
      choose_color();
    }else if(game_state.state == SND_HRN){
      horn_pipe();
      game_state.state = GM_RDY;
    } else if ((!gameOver()) && irrecv.decode(&results)) {
      // if game is being played
      #ifdef DEBUG
      Serial.println(results.value, HEX);
      Serial.println(gameOver(),DEC);
      #endif
      if (!gameOver()){
        //if game is not over pass in player input.
        getPlayerInput(results.value);
      }
      irrecv.resume();
    }else if(gameOver() && irrecv.decode(&results) || game_state.state == GM_LCKD && irrecv.decode(&results)){
      // handle start new game
      clear_pins();
      new_game(results.value);
      irrecv.resume();
    } else if(game_state.state == GM_LCKD){
      write_leds(board);
    }else if(gameOver()){
      // if game is over and yellow wins, light up yellow leds else light up red leds
      switch(game_state.state){
        case YLW_WIN:
            victory_tune(YLW);
            break;
        case RED_WIN:
            victory_tune(RED);
            break;
        case DRAW:
            light_color(RED);
            light_color(YLW);
            break;
      }
    } 
}
void clear_pins(){
  /*
    Turn all pins low.
  */
  PORTD = CLR;
  PORTB = CLR;
}
void light_led(char led, char row){
  /*
   Light led on row
  */
  PORTB |= row;
  PORTD |= led;
}
void write_leds(char arr[LED_CNT][LED_CNT]){
  /*
    Light corresponding leds (RED or YLW) or none,
    on a row j in column i, using persistance of vision.
  */
  for(char j = 0;j < LED_CNT;j++){
    for(char i = 0;i < LED_CNT;i++){
      if((arr[j][i]) == RED){
        light_led(REDS[i],ROWS[j]);
      } else if(arr[j][i] == YLW){
        light_led(YLWS[i],ROWS[j]);
      }
      delay(RFRSH_RT);
      clear_pins();
    }
  }
}
void light_color(char color){
  /*
  Light all leds of given color
  */
    char light_all[3][3];
    if (color == YLW) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = YLW;
    else if (color == RED) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = RED;
    #ifdef DEBUG
    // print out contents of light all array
    for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) Serial.println(light_all[i][j],DEC);
    #endif
    write_leds(light_all);
}
void choose_color(){
  /*
  Player color choice
  */
 if(irrecv.decode(&results)){
 if(results.value == PAUSE){
   game_state.state = SND_HRN;
 }
 else if(results.value == MODE && game_state.yellow_player == PLYR_ONE){
  light_color(RED);
  game_state.yellow_player = PLYR_TWO; 
  game_state.red_player = PLYR_ONE;
  EEPROM.write(TRN_ADDR,RED);
 }else if(results.value == MODE && game_state.yellow_player == PLYR_TWO){
  game_state.yellow_player = PLYR_ONE;
  game_state.red_player = PLYR_TWO;
  light_color(YLW);
  EEPROM.write(TRN_ADDR,YLW);
 }
 irrecv.resume();
 } else{
 if(game_state.yellow_player == PLYR_ONE) light_color(YLW);
 else if(game_state.yellow_player == PLYR_TWO) light_color(RED);
 }
}
void victory_tune(char col){
    for(int timer = 0; timer < colmans_MAXIMUM_COUNT; timer++){
    note = colmans_tune[timer];
    beat = colmans_beats[timer];
    
    duration = beat * tempo;
    light_color(col);
    play_note(col);
    light_color(col);
    delayMicroseconds(pause);
  }
}
static void invalid_move(){
    for(int timer = 0; timer < StartingBuzzer_MAXIMUM_COUNT; timer++){
    note = StartingBuzzer_tune[timer];
    beat = StartingBuzzer_beats[timer];
    
    duration = beat * tempo;
    play_note(NONE);
    
    delayMicroseconds(pause);
  }
} 
void horn_pipe(){
    for(int timer = 0; timer < hornpipe_MAXIMUM_COUNT; timer++){
    note = hornpipe_tune[timer];
    beat = hornpipe_beats[timer];
    
    duration = beat * tempo;
    play_note(NONE);
    
    delayMicroseconds(pause);
  }
}
void play_note(char col){
  long time_so_far = 0;
  if (note > 0){
    while(time_so_far < duration){
      // buzzer on
      if(col==YLW || col == RED) light_color(col);
      digitalWrite(buzzer_out, HIGH);
      delayMicroseconds(note / 2);
      if(col==YLW || col == RED) light_color(col);
      // buzzer off
      digitalWrite(buzzer_out, LOW);
      delayMicroseconds(note / 2);
      if(col==YLW || col == RED) light_color(col);
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
