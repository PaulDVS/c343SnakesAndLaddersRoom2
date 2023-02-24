#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

//By Paul van Sitter and Aadil Sohail

void roll(int player); //Creates a random number and moves player piece forwards, calls spaceCheck
void spaceCheck(int player); //Check contents of space, moves piece depending on snake/ladder or ends game.
void checkMap(); //Displays map


char board[100];
string playerNames[2];
int playerPieces[2];
int flag = 0;


int main()
{
	
	string ch;
	int currentPlayer;
	
	for(int i = 0; i<100; i++)//Set up board with empty slots;
	{
		board[i] = 120;
	}
	board[6] = 40;// Ladders contain values 1-50 and move forward
	board[19] = 24;
	board[52] = 19;
	board[57] = 41;
	 
	board[47] = 88; //Snakes contain values 51-100 and move backwards;
	board[62] = 72; //50 added to space change value to place between 51 and 100 
	board[96] = 71;
	
	// Outer to restart game
	do
	{
		flag = 0;
		ch = "";
		currentPlayer = 0;
		playerPieces[0] = 0;
		playerPieces[1] = 0;
		
		//Loop to receive user input
		do 
		{
			cout<<endl;
			cout<<"Enter start to start game: "<<endl;
			cout<<"Enter exit to end program: "<<endl;
			cin>>ch;
			cout<<endl;
		}while(ch!="start" && ch!="exit");
		
		if(ch == "start")
		{
			checkMap();
			
			cout<<"Please enter player 1's name: "<<endl;
			cin>>playerNames[0];
			cout<<endl;
			
			cout<<"Please enter player 2's name: "<<endl;
			cin>>playerNames[1];
			cout<<endl;
			
			do //Main game loop to play game
			{	
				do
				{
					cout<<endl; //Menu for each player to: view the map, end the game or roll the dice and mvoe their piece
					cout<<"Player: "<<playerNames[currentPlayer]<<"'s turn."<<endl;
					cout<<"Enter map to view map: "<<endl;
					cout<<"Enter exit to end game: "<<endl;
					cout<<"Press any key to roll dice: "<<endl;
					cin>>ch;
					cout<<endl;
					
					if(ch == "map")
					{
						checkMap();
					}
				}while(ch=="map");
				
				if(ch == "exit")
				{
					flag=1;
					ch = "";
				}
				else
				{
					roll(currentPlayer);
				
					//Swaps the active player
					if(currentPlayer == 0)
					{
						currentPlayer = 1;
					}
					else
					{
						currentPlayer = 0;
					}
				}
				
			}while(flag == 0);
		}
		
		
	}while(ch!="exit");
	
	cout<<"Thank you for playing."<<endl;
}

//Function to roll a dice and move the players piece.
void roll(int player)
{
	int diceRoll;
	
	//Creates a rand num between 1 and 6 to be used as the dice roll.
	srand((unsigned) time(NULL));
	
	diceRoll = (rand() % 6) + 1;
	
	//Moves players piece
	cout<<"Player: "<<playerNames[player]<<" has rolled: "<<diceRoll<<endl;
	cout<<"Player's piece has moved from "<<playerPieces[player]<<endl;
	
	playerPieces[player] += diceRoll;
	
	cout<<"Player's piece has moved to "<<playerPieces[player]<<endl;
	
	//Checks the space user has landed on
	spaceCheck(player);
}

//Function to check the space the user has landed on, and end the game, move their piece up a ladder, or down a snake.
void spaceCheck(int player)
{
	if(playerPieces[player]>99)
	{
		flag = 1;
		cout<<"Player: "<<playerNames[player]<<" has reached the end of the the board and won."<<endl;
	}
	else if(board[playerPieces[player]] != 120)
	{
		if(board[playerPieces[player]] < 51)
		{
			cout<<"Player: "<<playerNames[player]<<" has landed on a ladder."<<endl;
			cout<<"Player's piece has moved from "<<playerPieces[player]<<endl;
			
			playerPieces[player] += (board[playerPieces[player]]);
			
			cout<<"Player's piece has moved to "<<playerPieces[player]<<endl;
		}
		else
		{
			cout<<"Player: "<<playerNames[player]<<" has landed on a snake."<<endl;
			cout<<"Player's piece has moved from "<<playerPieces[player]<<endl;
			
			playerPieces[player] -= ((board[playerPieces[player]]) - 50);
			
			cout<<"Player's piece has moved to "<<playerPieces[player]<<endl;
		}
	}
}


/* Loads a map of the game board, showcasing :
		normal spaces as numbers,
		Snake as S for the head of the snake and s for the tail of the snake, with numbers to match the head and the tail
		Ladders as L for the bottom of the ladder and l for the top of the ladder, with numbers to match the top and the bottom
		P1 for the location of player 1's piece 
		P2 for the location of player 2's piece 
		PP for the location of both players pieces if the share a space
*/	 
void checkMap()
{

	//Creates the top border of the map
	cout<<"================================================================"<<endl;
	
	//As the snake and ladders board has alternating lines of incrementing and decrementing lines, this map function contains
	//two row loops, one incrementing and one decrementing
	//Each loop loads in the correct symbol for each collumn in that row.
	for(int i=100; i>=0; i-=20)
	{
		for(int k=i+1; k<=i+10 && k<100; k++)
		{
			if(playerPieces[0] == k && playerPieces[1] == k){
				cout<<"|| PP ";
			}
			else if(playerPieces[0] == k)
			{
				cout<<"|| P1 ";
			}
			else if(playerPieces[1] == k)
			{
				cout<<"|| P2 ";
			}
			else if(k==6)
			{
				cout<<"|| L1 ";
			}
			else if(k==46)
			{
				cout<<"|| l1 ";
			}
			else if(k==43)
			{
				cout<<"|| l2 ";
			}
			else if(k==43)
			{
				cout<<"|| l2 ";
			}
			else if(k==47)
			{
				cout<<"|| S1 ";
			}
			else if(k==9)
			{
				cout<<"|| s1 ";
			}
			else if(k==62)
			{
				cout<<"|| S2 ";
			}
			else if(k==40)
			{
				cout<<"|| s2 ";
			}
			else if(k < 10)
			{
				cout<<"||  "<<k<<" ";
			}
			else
			{
				cout<<"|| "<<k<<" ";
			}
		}
		
		//Loads in the border between rows.
		if(i<100)
		{
			cout<<"||"<<endl;
			cout<<"================================================================"<<endl;
		}
		
		for(int j = i; j>i-10 && j>0; j--)
		{
			if(playerPieces[0] == j && playerPieces[1] == j){
				cout<<"|| PP ";
			}
			else if(playerPieces[0] == j)
			{
				cout<<"|| P1 ";
			}
			else if(playerPieces[1] == j)
			{
				cout<<"|| P2 ";
			}
			else if(j==19)
			{
				cout<<"|| L2 ";
			}
			else if(j==52)
			{
				cout<<"|| L3 ";
			}
			else if(j==71)
			{
				cout<<"|| l3 ";
			}
			else if(j==57)
			{
				cout<<"|| L4 ";
			}
			else if(j==98)
			{
				cout<<"|| l4 ";
			}
			else if(j==96)
			{
				cout<<"|| S3 ";
			}
			else if(j==75)
			{
				cout<<"|| s3 ";
			}
			else
			{
				cout<<"|| "<<j<<" ";
			}
		}
		if(i>0)
		{
			cout<<"||"<<endl;
			cout<<"================================================================"<<endl;
		}
		
	}
	cout<<endl;	
}
