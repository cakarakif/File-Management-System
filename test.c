#include "Data_file.h"

struct _RECORD 
{  
  char team[44];
  char shortname[10];   
  char rank[4]; 
  char goalscored[4]; 
  char goalconceeded[4]; 
  char point[4]; 
  };

 
  /////
void enterInput();
void deleteInput();
void printDataFile();
void myfindKey();
void Selection();
void printMenu(int* answer);
static int flag=0;
typedef struct _RECORD RECORD;
 #define RECORD_SIZE 70
  int main(){

    Selection();
 return 0;
}
void  printDataFile(){
 FILE *inputFile;
    inputFile = fopen("myfilename.dat","r");
	int i;	    
    fseek(inputFile,0, SEEK_END);
    fseek(inputFile,bytenum, SEEK_SET);
	for(i=0;i<location;i++)   {
       // fseek(inputFile, 70*i, SEEK_CUR);
		RECORD buffer;
		fread(&buffer,sizeof(RECORD),1,inputFile);
		printf("team : %s, shortname : %s, rank :%s ,goalscored : %s, goalconceeded : %s, point :%s \n", buffer.team, buffer.shortname, buffer.rank, buffer.goalscored, buffer.goalconceeded, buffer.point);
	}
	fclose(inputFile);
}
void myfindKey(int choise){
 FILE *foundRec=fopen("myfilename.dat","r");
 int key,plc;
 void *data;
 RECORD *buffer;
 data=malloc(sizeof(RECORD));
     printf("Enter findkey : ");
    scanf("%d" ,&key);
    if(choise==0)
  plc= myFileFind(&key,data,0,location);
    
    else if(choise==1)
    plc= myFileFindNext(&key,data);

  if(plc!=-1){
 fseek(foundRec,plc,SEEK_SET);
 fread(data,RECORD_SIZE,1,foundRec) ;
buffer=(RECORD *)data;
printf("Record has been found successfully!\n");
printf("team : %s, shortname : %s, rank :%s ,goalscored : %s, goalconceeded : %s, point :%s \n", buffer->team, buffer->shortname, buffer->rank, buffer->goalscored, buffer->goalconceeded, buffer->point);
  }
    
  fclose(foundRec);
}

void deleteInput(){
    int fkey;
    printf("Enter deletekey : ");
    scanf("%d" ,&fkey);
    myFileDelete(&fkey,RECORD_SIZE);
}
void  enterInput(){
      RECORD rec;
     int delimiter=0;
     int controlRecord=0;
while(controlRecord!=-1){ 

if(delimiter==0){
  printf("Enter team : ");
    scanf("%s" ,&rec.team);
}
 else if(delimiter==1){
printf("Enter shortname : ");
    scanf("%s" ,&rec.shortname);
}

 else if(delimiter==2){
 printf("Enter rank : ");
    scanf("%s" ,&rec.rank);
}

 else if(delimiter==3){
 printf("Enter goalscored : ");
    scanf("%s" ,&rec.goalscored);
}

 else if(delimiter==4){
printf("Enter goalconceeded : ");
    scanf("%s" ,&rec.goalconceeded);
}

 else if(delimiter==5){
 printf("Enter point : ");
    scanf("%s" ,&rec.point);
    controlRecord=-1;
}
else{
    printf("Invalid Data Type");
    //return rec;
}
delimiter++;
}
if(delimiter<6)
{
    printf("Incomplete Data Type");
    flag=-1;
   // return rec;
   
}
else
myFileWrite(&rec,RECORD_SIZE);
  //return rec;
}

void printMenu(int* answer){
    //print the user menu
	printf("You can perform the following tasks: \n");
	printf("(1) Create Data and Indexing File\n");
	printf("(2) Open Data file \n");
	printf("(3) Close Data file \n");
	printf("(4) Write input to file  \n");
    printf("(5) Delete input to file \n");
	printf("(6) Write all data from key-sort array to Indexing file \n");
	printf("(7) Print all elements in indexing file  \n");
    printf("(8) Prints all records in data file \n");
	printf("(9) Find the data with the given key in the file. \n");
	printf("(10) Find the next key of the given key in the key-sort array  \n");
   printf("-------------------------------------\n");
	printf("11) Quit \n");
	printf("Please Select one... \n");
	scanf("%d",answer);
}

void Selection(){
    int answer;
    int loop=1;
     while(1){
    printMenu(&answer);
	while(answer>12 || answer<1)
	{
		printf("\nEnter a valid choice by pressing ENTER key again");
		printMenu(&answer);
	}
	switch(answer)
	{
        printf("%d",answer);
		case 1: myFileCreate("myfilename.dat","header.json");
       	break;
		case 2:myFileOpen("myfilename.dat");
         break;
		case 3: myFileClose();
         printf("Program is terminating \n");
         loop=0;
         
          break;
		case 4:enterInput();
        	break;	
		case 5: deleteInput();
         break;
         case 6: myWriteIndex();
          break;
		case 7: printIndexingFile();
         break;
		case 8:printDataFile();
        break;	
		case 9: myfindKey(0);
           break;
        case 10: myfindKey(1);
         break;
         
    }	
    if(loop==0) break;
	}
}
