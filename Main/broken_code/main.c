#include "defines.h"
void clear_leds(){
  /*
    Turn all pins low.
  */
  PORTD = CLR;
  PORTB = CLR;
}
void red_on(int row,int col){
  PORTD |= row;
  PORTB |= col;
}
void write_board(int *arr){
  // light the board, check if the place is taken
  // and light up given diode
  Serial.begin(9600);
  for(int i=0;i<9;i++){
    if(arr[i] == -1){
      clear_leds();
      delay(1);
      PORTD |= YLWS[i];
      delay(RFRSH_RATE);
    } else if(arr[i] == 1){
      clear_leds();
      delay(1);
      int index = i/3;
      red_on(ROWS[index],REDS[index]);
      delay(RFRSH_RATE);   
    } 
  }
}
void setup() {
  // put your setup code here, to run once:
  DDRD |= DDRD_PINS;
  DDRB |= DDRB_PINS;
  clear_leds();
}

void loop() {
  // put your main code here, to run repeatedly:
  //clear_leds();
  //int arr[] = {1,-1,-1,1,1,1,1,1,1};
  //int arr[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
  //int arr[] = {1,1,1,1,1,1,1,1,1};
  //red_on(ROWS[2],REDS[1]);
  //write_board(arr);
  //red_on(ROW3_ON,RED_1);
  //delay(RFRSH_RATE);
  //clear_leds();
}
