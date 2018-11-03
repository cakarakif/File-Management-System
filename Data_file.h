
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>

struct _Index {
	int key;
	int offset;
	
};
typedef struct _Index Index;
int myFileCreate(char *myfilename,char *jsonfilename);
int myFileOpen(char *myfilename); 
int myFileClose();
int myFileWrite(void *data,int size);
int myFileDelete(void * key,int size);
int myWriteIndex();
void printIndexingFile();
int myFileFind(void * key,void *data,int firstIdx, int lastIdx);
int myFileFindNext(void * key, void * data);
int myFileReindex();
void json_parse(FILE *fp ,json_object *jobj);
void writeheader(char *flag);
void bubble_sort();
static FILE *p=NULL;
static FILE * p1=NULL;
static int keyStart=0, keyEnd=0, location=0 ,bytenum=0,nIdx=-1,flg=0,  hdbyte=0,  size=0,key0rder=0;
   
static Index *ndx;


int myFileCreate(char *myfilename,char *jsonfilename){
    
    p = fopen(myfilename, "a");
      size=ftell(p);
  FILE *infr=fopen("myIndexingFile.ndx","a");
     FILE *jsonfile =fopen(jsonfilename,"r");
	char header[200];
  fgets(header,200,jsonfile);
  char * string =header;
  	json_object *jobj = json_tokener_parse(string);
	json_parse(p,jobj);
    fclose(jsonfile);
     fclose(infr);
   fclose(p);
  if(size==bytenum)
   printf("File has been created successfully\n");
   else
   printf("File  has been created before \n");
    
    return 1;//successful.  
}


int myFileOpen(char *myfilename){
   if(!p){
       printf("File has not been created!\n");
       return 0;
       }
p = fopen(myfilename, "a");
 FILE *inf=fopen("myIndexingFile.ndx","r");
 ndx=(Index*)malloc(200*sizeof(int));
 FILE *dec=fopen("myfilename.dat","r+b");
 fseek(dec,hdbyte,SEEK_SET);
fwrite("true ",5,1,dec);
fclose(dec);
flg=1;
 printf("File has been opened successfully\n");
     int i=0;
     Index temp;
     fseek(inf,0,SEEK_END);
     int sizeindex=ftell(inf)/sizeof(Index);
     fseek(inf,0,SEEK_SET);
     if(sizeindex!=0){
while(!feof(inf)){
      fread(&temp,sizeof(Index),1,inf);
ndx[i].key=temp.key;
     ndx[i].offset=temp.offset;
         i++;
}
location=i-1;//**
}
       return 1;
}
int myFileClose(){
     if(!p){
       printf("File has not been created!\n");
       return 0;
       }
    else if(flg==0){
       printf("File has not been opened! \n");
       return -1;
       }
    if(p!=NULL){
   FILE *decc=fopen("myfilename.dat","r+b");
 fseek(decc,hdbyte,SEEK_SET);
fwrite("false",5,1,decc);
fclose(decc);
    if(myFileReindex()==1)printf("File has been done re-indexing successfully!\n");
    else printf("File has not been done re-indexing!\n");
      flg=0;
    fclose(p);
    return 1;
    }
    return 0;
}
int myFileWrite(void *data,int size){
     if(!p){
       printf("File has not been created!\n");
       return 0;
       }
    else if(flg==0){
       printf("File has not been opened!\n");
       return -1;
       }
       int numfile=0;
       
    FILE *inputFile;
    inputFile = fopen("myfilename.dat","r+b");
    fseek(inputFile,bytenum+(location*size),SEEK_SET);
 fwrite(data,size,1,inputFile);
 fclose(inputFile);
data = data+keyStart-1;
ndx[location].key=atoi(data);
if(location==0)
ndx[location].offset=bytenum;///********
else{
 ndx[location].offset=(bytenum+size*(location));
}
location++;
bubble_sort();
printf("File has been written successfully!\n");
return 1;
//ndx = (Index*) realloc (ndx,sizeof(int)*2);
}
int myFileDelete(void * key,int size){
    if(!p){
       printf("File has not been created!\n");
       return -1 ;
       }
    else if(flg==0){
       printf("File has not been opened!\n");
       return -2;
       }
    p1=fopen("myfilename.dat","r");
    //ndx delete
    int doff=0;
    for(int i=0;i<location;i++){
if(*(int*)key==ndx[i].key){
    doff=ndx[i].offset;
    for(int j=i;j<location-1;j++){
ndx[j].key=ndx[j+1].key;
ndx[j].offset=ndx[j+1].offset;
    }  
    location--;
}
}
if(doff!=0){
   for(int i=0;i<location;i++){
if(ndx[i].offset>doff){
ndx[i].offset=ndx[i].offset-size;
}
}

  //file delete
  FILE *df=fopen("myfilename.dat","r+b");
fseek(p1, doff, SEEK_SET);
    int i;	
    void *buffer;
    buffer = malloc(size);
     fseek(df,0, SEEK_SET);
    for(i=0;i<location;i++)							
    {
   fseek(p1, size, SEEK_CUR);
	fread(buffer,size,1,p1);
  	fseek(df,doff+(i*size), SEEK_SET);
  fwrite(buffer,size,1,df);
    } 
    fclose(df);
printf("File has been deleted successfully!\n");
    return 1;
}
printf("File has not been deleted !\n");
return 0;
  
}
int myWriteIndex(){
    if(!p){
       printf("File has not been created!\n");
       return 0;
       }
    else if(flg==0){
       printf("File has not been opened !\n");
       return 0;
       }
    //int flag;
     FILE *inf=fopen("myIndexingFile.ndx","a");
     fclose(fopen("myIndexingFile.ndx", "w"));
for(int i=0;i<location;i++){
   fwrite(&ndx[i],sizeof(Index),1,inf);
}
fclose(inf);
return 1;

}
void printIndexingFile(){
    if(!p){
       printf("File has not been created!\n");
        }
    else if(flg==0){
       printf("File has not been opened!\n");
       }
       else{
 Index *object=malloc(sizeof(Index));
    FILE * file= fopen("myIndexingFile.ndx", "r");
    if (file != NULL) {
        while(fread(object, sizeof(Index), 1, file))
        printf("Key : %d , Offset : %d\n",object->key,object->offset);
        fclose(file);
    }
    }
}

int myFileFind(void * key,void *data,int firstIdx, int lastIdx){
   if(!p){
       printf("File has not been created!\n");
       return 0;
       }
    else if(flg==0){
       printf("File has not been opened!\n");
       return -1;
       }
int middleIdx= (firstIdx+lastIdx)/2; 
if(ndx[firstIdx].key==*(int*)key){
      nIdx=firstIdx+1;
    return ndx[firstIdx].offset;
	
}
	
    if(ndx[lastIdx].key==*(int*)key){
       nIdx=lastIdx+1;
      return ndx[lastIdx].offset;
	
    }
	
if(middleIdx==firstIdx || middleIdx == lastIdx) {
    printf("Record has not been found!");
		return -1;
	}
     if(ndx[middleIdx].key==*(int*)key){
    nIdx=middleIdx+1;
       return ndx[middleIdx].offset;
	
     }
	
    if(ndx[middleIdx].key>*(int*)key) {
		 myFileFind(key,data,firstIdx+1,middleIdx-1);					
	} 
	else {
		 myFileFind(key,data,middleIdx+1,lastIdx-1);				
	}
}

int myFileFindNext(void * key, void * data){
    if(!p){
       printf("File has not been created!\n");
       return 0;
       }
    else if(flg==0){
       printf("File has not been opened!\n");
       return -1;
       }
    myFileFind(key,data,0,location);
if(nIdx==-1 || nIdx>location-1){
printf("Record does not exist!\n");
return -1;
}
int nextIdx=nIdx;
nIdx=-1;
return ndx[nextIdx].offset;

}
int myFileReindex(){
   return myWriteIndex();
}
void json_parse(FILE *p ,json_object *jobj)
   {
   enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		type = json_object_get_type(val);
		switch (type) {
			case json_type_string: 
           if(strcmp(key,"keyStart")==0) keyStart=atoi(json_object_get_string(val));
           else if(strcmp(key,"keyEnd")==0) keyEnd=atoi(json_object_get_string(val));
            else if(strcmp(key,"order")==0 && strcmp(json_object_get_string(val),"ASC")==0) key0rder=0;
            else if(strcmp(key,"order")==0 && strcmp(json_object_get_string(val),"DSC")==0) key0rder=1;
            if(size==0) fprintf(p,"%sl", json_object_get_string(val));
            bytenum+=(strlen(json_object_get_string(val)) + 1 ) * sizeof(char);
	break;
		}
	}
    bytenum+=(strlen("false") ) * sizeof(char);
    if(size==0) {hdbyte=ftell(p);
     fprintf(p,"%s","false");}
}



void bubble_sort()
{
  int c, d, tempkey,tempoffset;
 
  for (c = 0 ; c <  location-1; c++)
  {
    for (d = 0 ; d < location- c-1; d++)
    {
      if (key0rder==0 && ndx[d].key > ndx[d+1].key)
      {
        tempkey  = ndx[d].key;
        ndx[d].key = ndx[d+1].key;
        ndx[d+1].key = tempkey;
        //
         tempoffset  = ndx[d].offset;
        ndx[d].offset = ndx[d+1].offset;
        ndx[d+1].offset = tempoffset;
      }
      else if (key0rder==1 && ndx[d].key < ndx[d+1].key)
      {
        tempkey  = ndx[d].key;
        ndx[d].key = ndx[d+1].key;
        ndx[d+1].key = tempkey;
        //
         tempoffset  = ndx[d].offset;
        ndx[d].offset = ndx[d+1].offset;
        ndx[d+1].offset = tempoffset;
      }
    }
  }
}

