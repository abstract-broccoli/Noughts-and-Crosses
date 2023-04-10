#include <stdio.h>
#include <stdlib.h>
//Function that prints out the game board
void print_Board(char displayTokens[3][3]){
  for (int i=0;i<3;i++){
    printf("%d\t\t|%d\t\t|%d\t\t\n",3*i+0,3*i+1,3*i+2);
    printf("\t%c\t|\t%c\t|\t%c\t\n",displayTokens[i][0],displayTokens[i][1],displayTokens[i][2]);
    printf("\t \t|\t \t|\t \t\n");
    i<2?printf("-------------------------------------------------\n"):printf("\n");
  } 
}
//Function that updates the game board
void update_game(int player,int position,int Board[3][3],char displayTokens[3][3]){
  int row=position/3;
  int col=position%3;
  Board[row][col]=player;
  char token = (player==1)?'0':'X';
  displayTokens[row][col]=token;
  print_Board(displayTokens);
}

//Function Checks if there is a winner
int Winner(int Board[3][3]){
  int checkEqual(int a,int b,int c){
    return a==b && a==c && b==c && a!=0;
  }
  for (int i=0;i<3;i++){
    if (checkEqual(Board[i][0],Board[i][1],Board[i][2])){return 1;} //horizontal_win_scenario
    if (checkEqual(Board[0][i],Board[1][i],Board[2][i])){return 1;} //vertical_win_scenario
  }
  if (checkEqual(Board[0][0],Board[1][1],Board[2][2])){return 1;} //diagonal_win_scenario 1
  if (checkEqual(Board[0][2],Board[1][1],Board[2][0])){return 1;} //diagonal_win_scenario 2
  return 0;
}
//Function checks if game board is full
int isFull(int input[3][3]){
  for (int i=0;i<3;i++){
    for (int j=0;j<3;j++){
      if (input[i][j]==0){return 0;}
    }  
  }
  return 1;
}
//Function Prints Out Result
int print_Results(int Board[3][3]){
  if (Winner(Board)) {
    printf("Winner\n");
  } else if (isFull(Board)) {
    printf("Draw\n");
  } 
}


//Collects the player input and checks if input is an integer
int collect_input() {
  int player_input;
  scanf("%d", &player_input);
  // Clear input buffer to prevent invalid input from causing an infinite loop
  while (getchar() != '\n') {}
  return player_input;
}
//Checks if input is actually a square on the board (0-9)
int isPlayable(int player_input) {
  if (player_input >= 0 && player_input <= 8) {
    return 1;
  } else {
    printf("Input not valid! Enter Number 0-9!\n");
    return 0;
  }
}
//Check if square is even empty
int isEmpty(int Board[3][3], int row, int col) {
  if (Board[row][col] == 0) {
    return 1;
  } else {
    printf("Square already full!\n");
    return 0;
  }
}
//Main Player Input Function
int playerMove(int Board[3][3]) {
  int inputSquare;
  int isInputValid = 0;
  int i,j;
  //collects a valid player input
  while (!isInputValid) {
    printf("Enter Square:");
    inputSquare = collect_input();
    i = inputSquare / 3;
    j = inputSquare % 3;
    //check if input is playable
    if (isPlayable(inputSquare)&&isEmpty(Board, i, j)) {
      isInputValid = 1;
    } 
  }
  return 3*i+j;
}

//Function checks if there is a winning chance for a player and returns the winning square;
int WinningChance(int Board[3][3], int Player_Num){
  int CheckForWin(int a,int b,int c){
    if (a==b && c==0 && a==Player_Num){return 3;} //3rd position is a potential win
    if (a==c && b==0 && c==Player_Num){return 2;} //2nd position is a potential win
    if (b==c && a==0 && b==Player_Num){return 1;} //1st position is a potential win
    return 0;
  }
  for (int i=0;i<3;i++){
    int Horizontal=CheckForWin(Board[i][0],Board[i][1],Board[i][2]); //check for horizontal wins
    int Vertical=CheckForWin(Board[0][i],Board[1][i],Board[2][i]); //check for vertical wins
    if (Horizontal){
          printf("i:%d, Horizontal:%d, Position:%d\n",i,Horizontal,i*3 + (Horizontal-1));
          return (i*3 + (Horizontal-1))+10;} //returns integer position of horizontal win
    if (Vertical){return ((Vertical-1)*3 + i)+10;} //returns integer position of vertical win
  }
  int Diagonal_1=CheckForWin(Board[0][0],Board[1][1],Board[2][2]); //check for diagonal wins
  int Diagonal_2=CheckForWin(Board[0][2],Board[1][1],Board[2][0]);
  if (Diagonal_1){return (4*(Diagonal_1-1))+10;} //returns integer position of diagonal win 1
  if (Diagonal_2){return (2*Diagonal_2)+10;} //returns integer position of diagonal win 2
  return 0;
}
//Function Produces Random Position Move
int RandomMove(int board[3][3]) {
    int i, j;
    do {
        i = rand() % 3;
        j = rand() % 3;
    } while (board[i][j] != 0 );
    board[i][j] = 1;  // Computer's move
    return 3 * i + j+10;
}

int computerMove(int Board[3][3],int COMPUTER,int HUMAN){
    int ComputerWins=WinningChance(Board,COMPUTER);//finds position of any computer wins
    int OpponentWins=WinningChance(Board,HUMAN);//finds position of any opponent wins
    if(ComputerWins){return ComputerWins;}
    else if(OpponentWins){return OpponentWins;}
    else {return RandomMove(Board);}
}

//Runs a SinglePlayer Game
void SinglePlayer(int Board[3][3],char displayTokens[3][3]){
  int COMPUTER,HUMAN;
  printf("Will you be Player 1 or 2?\nEnter 1 or 2:\t");
  scanf("%d",&HUMAN);
  COMPUTER=(HUMAN==1)?2:1;
  int turn=0;
  int position;
  while (!(Winner(Board)||isFull(Board))){
    int player=turn%2+1;
    printf("Player %d Turn:\n",player);
    if (player == HUMAN){position=playerMove(Board);}
    if (player == COMPUTER){position=computerMove(Board,COMPUTER,HUMAN)-10;}
    update_game(player, position, Board, displayTokens);
    turn+=1;
  }
  print_Results(Board);
}
//Runs a Multiplayer Game
void Mulitplayer(int Board[3][3],char displayTokens[3][3]){
  int turn=0;
  int position;
  while (!(Winner(Board)||isFull(Board))){
    int player=turn%2+1;
    printf("Player %d Turn:\n",player);
    if (player == 1){position=playerMove(Board);}
    if (player==2){position=playerMove(Board);}
    update_game(player, position, Board, displayTokens);
    turn+=1;
  }
  print_Results(Board);
}
//Runs a SinglePlayer Game
void NoPlayer(int Board[3][3],char displayTokens[3][3]){
  int turn=0;
  int position;
  while (!(Winner(Board)||isFull(Board))){
    int player=turn%2+1;
    printf("Player %d Turn:\n",player);
    if (player == 1){position=computerMove(Board,1,2)-10;}
    if (player == 2){position=computerMove(Board,2,1)-10;}
    update_game(player, position, Board, displayTokens);
    turn+=1;
  }
  print_Results(Board);
}
// Main Function
int main(){
    int Board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    char displayTokens[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    printf("NOUGHTS & CROSSES\n");
    print_Board(displayTokens);
    int GameMode;
    printf("Would you like to play Single-Player or Multi-Player?\nType 0 or 1:\t");
    scanf("%d",&GameMode);
    if (GameMode == 0){SinglePlayer(Board,displayTokens);} //Runs game human vs computer
    if (GameMode == 1){Mulitplayer(Board,displayTokens);} //Runs game human vs human
    if (GameMode == 2){NoPlayer(Board,displayTokens);} //Runs game computer vs computer
    return 0;
}