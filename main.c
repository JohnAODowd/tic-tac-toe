// Tic-tac-toc Project


// Definitions for sizes of row and columns.
#define rows 3
#define cols 3

// Three states a cell can be in: OFF, RED, or YLW.
#define OFF 0
#define RED 1
#define YLW 2

// Definitions for PINs
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7 
#define PIN8 8 
#define PIN9 9
#define PIN10 10


// Spare PINs
/*
#define PIN11 11
#define PIN12 12
#define PIN13 13
/**/


// Setup a two-dimensional 3x3 array. 
int board[rows][cols] ={ {OFF, OFF, OFF}, {OFF, OFF, OFF}, {OFF, OFF, OFF} };


void setup() {
  // put your setup code here, to run once:
  
  // access: board[1][2] == [row 1] [col 2] // Middle - Top
  
  // initialize the digital pin as an output.
  pinMode(x, OUTPUT);
  
}

void setupBoard() {
  // Row 1
  int topright = board[1][1];
  int topmid   = board[1][2];
  int topleft  = board[1][3];
  
  // Row 2
  int midright = board[2][1];
  int midmid   = board[2][2];
  int midleft  = board[2][3];
  
  // Row 3
  int botright = board[3][1];
  int botmid   = board[3][2];
  int botleft  = board[3][3];
}

bool gameOver() {
  // Game is over when there is a draw or when there is a win.
  if ( isFull() ) {

    // Check for win:

    //  vertically:
    if (topright == midright && midright == botright) ||
       (topmid == midmid && midmid == botmid) ||
       (topleft == midleft && midleft == botleft) {
      return true;
    }
    //  horizontally:
    if (topright == topmid && topmid == topleft) || 
       (midright == midmid && midmid == midleft) ||
       (botright == botmid && botmid == botleft) {
      return true;
    }
    //  diagonally:
    if (topright == midmid && midmid == botleft){
      return true;
    } else if (topleft == midmid && midmid == botright){
      return true;
    }

    // Check for draw:
    // sanity check?
    // if board is full and not won, must be a draw?

    // also: separate return for draw?

  } else {
    // Board is not full, so game is not over.
    return false;
  }

}

bool isFull(){
  // Return true if board is filled, false otherwise.
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++ ){
      if (board[i][j] == OFF){
        return false;
      }
    }
  }
  return true;
}


void loop() {
  // put your main code here, to run repeatedly: 
}


