#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <unistd.h> 
#include <conio.h>

#define C 0 // close
#define O 1 // open
#define B 9 // bomb

typedef struct {										//create structure 
	int znach;
	int close;
} sSaper;

int menu();												//create menu
void EntPar(int &size, int &nbomb);						//Enter level (size and numbers of bomb) 
void EntArr(sSaper *s, int size, int nbomb);			//Enter array
void PrinArr(sSaper *s, int size, int cell);			//printe mine field
void inpCell(sSaper *s, int size, int cell, int nbomb); //Inpute cell
int Open( sSaper *s, int size, int count );				//Open cell
void OpenAll(sSaper *s, int size);						//Open all field
int WinLoose(sSaper *s, int size, time_t a, int nbomb);	//Wine or Loose
void InputRecord(int size, time_t a);					//Inpute record to fiele
void PrintRecord();										//Print record to console
int exitRepeat();										//menu: exit or repeat
void cursorOff();										//"extinguish" the cursor
void setcur(int x, int y);								//setting the cursor to the position  x y 

