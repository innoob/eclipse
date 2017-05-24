/*
This is a tool for the header file for 
the program's debug and exception handling,
which defines the debug macros and all the functions declared
*/

#ifndef MYTOOLS
#define MYTOOLS

char* my_strcpy(char*,const char*,int);

int fileWriteLine(FILE*,char*);

char* myReplace(const char*,const char,const char);

int is_num(const char*);

char cpy[128];

int fileWriteLine(FILE* fp,char* linner)
{

	if(fp==NULL) return putError(6);
	fputs(linner,fp);
	return 1;
	// fclose(fp);
}

char* myReplace(const char* string,const char src,const char rep)
{		
	assert(string!=NULL&&src!=NULL&&rep!=NULL);
	memset(cpy,0,sizeof(cpy));
	for(int i = 0;string[i]!='\0';cpy[i]=string[i]==src?rep:string[i],i++);
	return cpy;
}


char* my_strcpy(char *dst,const char *src,int start)  
{  
    assert(dst != NULL);  
    assert(src != NULL);  
    char *ret = dst;
    memcpy(dst,src+start,strlen(src)-start);
    return ret;  
}

int is_num(const char* str)
{
	assert(str!=NULL);
	int i;
	for(i=0;str[i]!='\0'&&str[i]>='0'&&str[i]<='9';++i);
	return i==strlen(str);
}

#endif