#include "libeFunction.h"

int menu() // Create menu - done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);					//hide cursor
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle,&structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo( handle, &structCursorInfo );

	int key=0; 
    int code;  
    do {
            system("cls");  
            SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
            printf("	CHOOSE LVL		\n\n");
            key=(key+3)%3; 
			 
            if (key==0){
            	SetConsoleTextAttribute(hStdOut, 30); 
            	printf("	--> EASY		\n");
            	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
			} 
            else  {
            	printf("	    EASY		\n");
			}
			if (key==1){
            	SetConsoleTextAttribute(hStdOut, 30); 
            	printf("	--> MEDIUM		\n");
            	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
			} 
            else  {
            	printf("	    MEDIUM		\n");
			}
			if (key==2){
            	SetConsoleTextAttribute(hStdOut, 30); 
            	printf("	--> HARD		\n");
            	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
			} 
            else  {
            	printf("	    HARD		\n");
			}             
        	
			code=getch();
            if (code==224)
            {
                code=getch();
                if (code==80) key++; 
                if (code==72) key--;
           }
        }while(code!=13); 
	    system("cls");  
	
	return key;
}

void EntPar(int &size, int &nbomb) //Enter level (size and numbers of bomb) - done
{
	int level;
	level=menu();
	if (level == 0) { size = 8 * 8; nbomb = 8 * 8 * 12 / 100;}
	else if (level == 1) {size = 10 * 10; nbomb = 10 * 10 * 15 / 100 ;} 
	else if (level == 2) {size = 14 * 14; nbomb = 14 * 14 * 18 / 100;}
}

void EntArr(sSaper *s, int size, int nbomb) //Enter array - done
{
	srand(time(NULL));
	int i, schet=0, sum,r;
	r=sqrt(size);
	for (i=0; i<size; i++){
		s[i].close = C;									//close all						
	}
	
	do {
		i=rand()%size;
		if (s[i].znach==B) continue;
		s[i].znach=B;									// bomb = 9
		schet++;
	} while (schet!=nbomb);
	
	for (i=0; i<size; i++){
		sum=0;
		if (s[i].znach==B) continue;										//Counting the number of bombs in a circle
		if ((i-r-1>=0) && (s[i-r-1].znach==B) && ((i-r)%r!=0)) sum++;		//up-left
		if ((i-r>=0) && (s[i-r].znach==B)) sum++;
		if ((i-r+1>=0) && (s[i-r+1].znach==B) && ((i-r+1)%r!=0)) sum++;
		if (((i)%r!=0) && (s[i-1].znach==B)) sum++;
		if (((i+1)%r!=0) && s[i+1].znach==B) sum++;
		if ((i+r-1<size) && (s[i+r-1].znach==B) && ((i+r)%r!=0)) sum++;
		if ((i+r<size) && (s[i+r].znach==B)) sum++;
		if ((i+r+1<size) && (s[i+r+1].znach==B) && ((i+r+1)%r!=0)) sum++;
		s[i].znach=sum;
	}
}

void PrinArr(sSaper *s, int size, int cell) //printe mine field - done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
	int i=sqrt(size);
	int r=i, c=i, count=0;
	
	for (r=0; r<size*2+i; r+=i){
		printf("\n");
		for (c=0; c<i; c++){
			if (r%(i*2)==0) printf ("-----");
			else {
				if (count==cell){
					SetConsoleTextAttribute(hStdOut, 30);
					if (s[count].close == C) {
						printf("|   |");
					}
					else {
						printf("| %i |", s[count].znach);
					}
					
					SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
					count++;
					continue;
				}
				if (s[count].close == C) {
					printf("|   |");
				}
				else if ( s[count].close == O ) {
					switch (s[count].znach){
						case 1: 
						case 2: 
						case 3: 
						case 4: SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN); break;
						case 5: 
						case 6: 
						case 7: 
						case 8: SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE); break;
						case 9: SetConsoleTextAttribute(hStdOut, 80); break;
						default: SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY); break;
					}
					
					printf("| %i |", s[count].znach);
					SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
				}
				count++;				
			}
		}
	}
}

void inpCell(sSaper *s, int size, int cell, int nbomb) //Enter coordinates and clean window -done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	int code;
	time_t start;
	start=time(NULL);		//time now

	do{
    	do{
    		//system("cls"); 
    		setcur(0,0);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED); 
    		printf("\nBOMB - %i, TIME TO BOOOOM - %i sec",nbomb,(start+size)-time(NULL));
    		SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY); 
			cell=(cell+size)%size;
			PrinArr(s,size,cell);
			
			if (kbhit()!=0){
				code=getch();
			}
       	 	if (code==224)
       		{
           		code=getch();
           		if (code==80) cell+=sqrt(size); 
           		if (code==72) cell-=sqrt(size); 
        		if (code==77) cell++; 
        		if (code==75) cell--; 			 
                //right 77 //left 75 //down 80 //up 72
        	}
        	if ((start+size)-time(NULL)<=0) break;
   		}while(code!=13);
		Open( s, size, cell ); 
		
	} while (WinLoose(s,size,(start+size)-time(NULL),nbomb));
}

void OpenAll(sSaper *s, int size) // Open all - done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	system("cls"); 
	int i;
	for (i=0; i<size; i++){
		s[i].close = O;									//open all						
	}
	i=sqrt(size);
	int r=i, c=i, count=0;
	
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
	for (r=0; r<size*2+i; r+=i){
		printf("\n");
		for (c=0; c<i; c++){
			
			if (r%(i*2)==0) printf ("-----");
			else {
				if (s[count].close == C) {
					printf("|   |");
				}
				else if ( s[count].close == O ) {
					switch (s[count].znach){
						case 1: 
						case 2: 
						case 3: 
						case 4: SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN); break;
						case 5: 
						case 6: 
						case 7: 
						case 8: SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE); break;
						case 9: SetConsoleTextAttribute(hStdOut, 80); break;
						default: SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY); break;
					}
					
					printf("| %i |", s[count].znach);
					SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
				}
				count++;				
			}
		}
	}
}

int Open( sSaper *s, int size, int count ) // recursion open - done
{
	int r=sqrt(size);
	
	if ( s[count].close != O ){
		s[count].close = O;
		
		if (s[count].znach==0){
			if ((count-r-1>=0) && (s[count-r-1].znach==0) && ((count-r)%r!=0)) Open(s, size, count-r-1);
			else if ((count-r-1>=0) && (s[count-r-1].znach!=0) && ((count-r)%r!=0)) s[count-r-1].close = O; 
			
			if ((count-r>=0) && (s[count-r].znach==0) ) Open(s, size, count-r);
			else if ((count-r>=0) && (s[count-r].znach!=0)) s[count-r].close = O;
			
			if ((count-r+1>=0) && (s[count-r+1].znach==0) && ((count-r+1)%r!=0)) Open(s, size, count-r+1);
			else if ((count-r+1>=0) && (s[count-r+1].znach!=0) && ((count-r+1)%r!=0)) s[count-r+1].close = O; 
			
			if (((count)%r!=0) && (s[count-1].znach==0)) Open(s, size, count-1);
			else if (((count)%r!=0) && (s[count-1].znach!=0)) s[count-1].close = O;
			
			if (((count+1)%r!=0) && s[count+1].znach==0) Open(s, size, count+1);
			else if (((count+1)%r!=0) && s[count+1].znach!=0) s[count+1].close = O;
			
			if ((count+r-1<size) && (s[count+r-1].znach==0) && ((count+r)%r!=0)) Open(s, size, count+r-1);
			else if ((count+r-1<size) && (s[count+r-1].znach!=0) && ((count+r)%r!=0)) s[count+r-1].close = O;
			
			if ((count+r<size) && (s[count+r].znach==0))Open(s, size, count+r);
			else if ((count+r<size) && (s[count+r].znach!=0)) s[count+r].close = O;
			
			if ((count+r+1<size) && (s[count+r+1].znach==0) && ((count+r+1)%r!=0)) Open(s, size, count+r+1);
			else if ((count+r+1<size) && (s[count+r+1].znach!=0) && ((count+r+1)%r!=0)) s[count+r+1].close = O;
		}	
	}
	
	else return 0;
}

int WinLoose(sSaper *s, int size, time_t a, int nbomb) // WIn or Loose - done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	int i;
	int win=0;
	
	if (a<=0){
		OpenAll(s,size);
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		Beep(300, 2000);
		printf ("\n\n\nTIME OUT\nBOOOOOOOOOM YOU LOOSE"); 
		return 0;
	}
	
	for (i=0;i<size; i++){
		if (s[i].close==O && s[i].znach==B){
			OpenAll(s,size);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			Beep(300, 1000);
			printf ("\n\n\nBOOOOOOOOOM YOU LOOSE"); 
			return 0;
		}
		else if (s[i].close==O && s[i].znach!=B){
			win++;
		}	
	} 
	
	if (win==(size-nbomb))	{
		OpenAll(s,size);
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		printf ("\n\n\nCONGRATULATIONS, YOU WINNER");
		InputRecord(size,a); 
		return 0;
	}
}

void InputRecord(int size, time_t a) // print record to file - done
{
	FILE *fp;
	char buffer[100], buff[50], name[50], timeus[20];
	int znach, time=0, sizestr, timesize;
	long fpos1, fpos2;
	char name1[50];
	
	fp=fopen("record.txt", "r+");
	if(fp==NULL){
		printf("\nError, cannot open file");
	}
	
	while(fgets(buffer,100,fp)!=0){
		fpos2=ftell(fp);
		sscanf(buffer,"%s",buff);
		znach=atoi(buff);
		if (znach==size){
			sizestr=strlen(buff);
			for ( int i=sizestr; i<strlen(buffer); i++){
				sscanf(buffer+i,"%s",buff);
				if (i==sizestr) strcpy(name1, buff);
				
				if (buff[0]>=0 && buff[0]<=9) {
					timesize=strlen(buff);
					time=atoi(buff);
				}

			}
			if (time<a){
				printf("\nyou set a new record, print your name:");
				scanf("%s", name);
				sprintf(timeus, "%i", a);
				if (strlen(timeus)<3) {
					if (strlen(timeus)<2){
						strcpy(buff, timeus);
						sprintf(timeus, "00%s", buff);
					}
					else {
						strcpy(buff, timeus);
						sprintf(timeus, "0%s", buff);
					}	
				}
				timeus[4]='\0';
				while (strlen(name)!=strlen(name1)){
					if (strlen(name)<strlen(name1)) {
						for(int i = strlen(name); i<strlen(name1); i++)name[i]=' ';
					}
					name[strlen(name1)]='\0';
				}
				fseek(fp, fpos1, SEEK_SET);
				if (size == 64) fprintf(fp,"%i \t%s\t\t%s\n", size, name, timeus);
				else fprintf(fp,"%i\t%s\t\t%s\n", size, name, timeus);
				
				fseek(fp, fpos2, SEEK_SET);
				break;
			}
		}
		fpos1=ftell(fp);	
	}
	fclose(fp);
	PrintRecord();
}

void PrintRecord()
{
	FILE *fp;
	char buffer[100];

	
	fp=fopen("record.txt", "r");
	if(fp==NULL){
		printf("\nError, cannot open file");
	}
	printf("\n\n");
	while(fgets(buffer,100,fp)!=0){
		puts(buffer);
	}
	
	fclose(fp);
}

int exitRepeat() // Repeat or Exit - done
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	
	int key=0; 
    int code;  
    do {
            system("cls");  
            SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
            printf("	CHOOSE LVL		\n\n");
            key=(key+2)%2; 
			 
            if (key==0){
            	SetConsoleTextAttribute(hStdOut, 30); 
            	printf("	[ REPEAT ]	\n");
            	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
			} 
            else  {
            	printf("	  REPEAT  	\n");
			}
			if (key==1){
            	SetConsoleTextAttribute(hStdOut, 30); 
            	printf("	 [ EXIT ] 	\n");
            	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
			} 
            else  {
            	printf("	   EXIT		\n");
			}

			code=getch();
            if (code==224)
            {
                code=getch();
                if (code==80) key++; 
                if (code==72) key--;
           }
        }while(code!=13); 
	    system("cls");  
	
	return key;
}


void setcur(int x, int y)//setting the cursor to the position  x y 
{ 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}
