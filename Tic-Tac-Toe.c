#include <stdio.h>

//Numbers for the symbols
#define CROSS 1
#define CIRCLE 0
#define NOTUSED -1

//Macros for symbols
#define SYM_CROSS 'X'
#define SYM_CIRC  'O'
#define SYM_EMPTY '-'


//Function Declarations

int choosePlayer(); //Chosing which player to start
void display(int arr[][3]); //displaying thetic-tac-toe board
void init(int arr[][3]);	//initializing the matrix
void enterSymb(int arr[][3], int sym);	//function for entering a particular symbol at a particular palce in the matrix
int playerGen(int * player);  //Function to keep alternating the platers chances
char playerToSym(int PlayerNo);	//converting player numbers to their symbols (eg 1-->X)
int ifCellsLeft(int arr[][3]);	//To check if empty cells are left
int checkRow(int arr[][3],int rowToCheck,int playerToCheck);	//checking a particular row for wins
int checkCol(int arr[][3],int ColToCheck,int playerToCheck);	//checking columns for wins
int checkDiag(int arr[][3],int playerToCheck);	//checking the two diagonals
int check(int arr[][3],int playerToCheck);	//Check function which uses above functions to check the whole array



int main(){
	int  cells[3][3];
	int Player=choosePlayer();
	int currentPlayer;
	init(cells);
	while(1){
		currentPlayer=playerGen(&Player);
		//printf("It is %c's turn\n",playerToSym(currentPlayer));
		enterSymb(cells,currentPlayer);
		display(cells);
		//Checking for wins
		if(check(cells,currentPlayer)){
			printf("player %c has won\n",playerToSym(currentPlayer));
			printf("Game Over!!\n");
			break;
		}
		//Checking  for a tie
		if(!ifCellsLeft(cells)){
			printf("It is a TIE ,Game Over!!\n");
			break;
		}
		
	}	 
}



void init(int arr[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			arr[i][j]=NOTUSED;
		}
	}	
}

int choosePlayer(){
	char Player;
	while(1){
		printf("Enter X of O to choose the first player\n");
		scanf("%c",&Player);
		switch(Player){
			case'X': return CROSS;
			case'O':return CIRCLE;
			default: printf("Enter correct values\n");
		}
	}
}


void display(int arr[][3]){
	int i=0,j=0;
	char cellContent;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			switch(arr[i][j]){
				case 1: cellContent=SYM_CROSS;
					break;
				case 0: cellContent=SYM_CIRC;
					break;
				case -1:cellContent=SYM_EMPTY;
					break;
				
			}
			printf("[%c]",cellContent);
		}
		printf("\n");
	}
}

char playerToSym(int PlayerNo){
	switch(PlayerNo){
		case 1: return SYM_CROSS;
		case 0: return SYM_CIRC;				
	}
}



int playerGen(int * player){
	int playerForThisTurn=*player;
	if(*player==CIRCLE) 
		*player=CROSS;
	else if(*player==CROSS)
		*player=CIRCLE;
	
	return playerForThisTurn;
}



void enterSymb(int arr[][3], int sym){
	int row,column;
	while(1){
		printf("Enter row and column\n");
		scanf("%d%d",&row,&column);
		if((row<=3&&row>=0)&&(column<=3 && column>=0)){
			if(arr[row-1][column-1]==NOTUSED){
				arr[row-1][column-1]= sym;
				break;
			}else{
				printf("Select an empty cell\n");
			}
			
		}else if(!((row<=3&&row>=0)&&(column<=3 && column>=0))){
			printf("please enter appropriate values for rows and columns\n");			
		}		
		
	}
}

int ifCellsLeft(int arr[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(arr[i][j]==NOTUSED)
				return 1;
		}
	}
	return 0;
}





int checkRow(int arr[][3],int rowToCheck,int playerToCheck){
	int i;
	for(i=0;i<3;i++){
		if(arr[rowToCheck][i]!=playerToCheck)
			return 0;
	}
	return 1;
}

int checkCol(int arr[][3],int ColToCheck,int playerToCheck){
	int i;
	for(i=0;i<3;i++){
		if(arr[i][ColToCheck]!=playerToCheck)
			return 0;
	}
	return 1;
}

int checkDiag(int arr[][3],int playerToCheck){
	int flag1=1;
	int flag2=1;
	int i,j;
	for(i=0;i<3;i++){
		if(arr[i][i]!=playerToCheck){
			flag1=0;
		}
	}
	
	for(i=0,j=2;i<3 && j>=0;i++,j--){
		if(arr[i][j]!=playerToCheck){
			flag2=0;
		}
	}
	if(flag1 || flag2){
		return 1;
	}else{
		return 0;
	}
}

int check(int arr[][3],int playerToCheck){
	int i;
	for(i=0;i<3;i++){
		if(checkRow(arr,i,playerToCheck) || checkCol(arr,i,playerToCheck)){
			return 1;
		}
	}
	
	if(checkDiag(arr,playerToCheck)){
		return 1;
	}
	
	return 0;

}
