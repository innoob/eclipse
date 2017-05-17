/*
This is a tool for the header file for 
the program's debug and exception handling,
which defines the debug macros and all the functions declared
*/

#ifndef NEWPROJECT
#define NEWPROJECT


int putError(int);

int crDir(const char*);

char* my_strcpy(char*,const char*,int);

int crPath(void);

char* crClasspath(char*);

char* crProject(char*);

char* crMakefile(char*,char*);

int fileWriteLine(FILE*,char*);

char* crClass(char*,char*,char*);

char* myReplace(const char*,const char,const char);

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


char *my_strcpy(char *dst,const char *src,int start)  
{  
    assert(dst != NULL);  
    assert(src != NULL);  
    char *ret = dst;
    memcpy(dst,src+start,strlen(src)-start);
    return ret;  
}
/*
This is a function that is used to handle errors and give hints, 
which returns an integer that indicates the error state
*/
int putError(int state){

	switch(state){
		case 0:
			printf("帮助信息：\n");
			break;
		case 1:
			printf("未加入指定的参数!：\n");
			break;
		case 2:
			printf("加入的参数错误!：\n");
			break;
		case 3:
			printf("加入的参数未知！");
			break;
		case 4:
			printf("加入的参数长度错误，不符合要求！\n");
			break;
		case 5:
			printf("内存分配错误，请清理内存并重试！\n");
			return 5;
		case 6:
			printf("创建文件指针失败!\n");
			return 6;
		default:
			printf("未知错误！");
			return 0;
	}
	// -t type<web,console> -m comment -M maven -E encoding -JRE

		printf("\n	用法： newproject -d <项目地址> -p <项目名称> -b <包名> \n\n 实例：\n    	在当前目录(.)下创建 com.test.demo 包\n");
		printf("\n	newproject -d . -p hello -bcom.test.demo\n\n");
		printf(" 参数列表：\n\n");
		printf("	-p <项目名称>\n		这个参数为你设置项目名称。\n\n");
		printf("	-b <包名>\n		这个参数为你项目的初始包名，如果不设置将会创建com.default包。\n\n");
		printf("	-d <项目地址>\n		这个参数为你设置项目地址，如果不设置将会默认在当前目录。\n\n");
		printf("	-h <-help>\n 		显示帮助信息\n\n");
		printf("	-debug\n		显示调试信息\n\n");
		return state;
}

#endif

#ifndef DEBUG_VAR
#define _f(x,y) x##y
#define f(x,y) _f(x,y)
#define _CON(x) ":"#x
#define CON(x,y) _CON(f(x,y)) 
#define DEBUG_VAR(a,b) if(dbg) printf(a _CON(b)"=%s\n",b)


#endif

#ifndef DEBUG_VARLIST
#define DEBUG_VARLIST if(dbg) printf("argv[%d]='%s'leng=%d\n",i,argv[i],strlen(argv[i]))
#endif

#ifndef DEBUG_ARGLEN
#define DEBUG_ARGLEN if(dbg) printf("argc.leng=%d\n",argc)
#endif
