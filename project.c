#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "project.h"
#include "mytools.h"

int main(int argc,char** argv)
{
	char* className;
	char* classType;
	char* directory;
	char* packName;
	char* filePath;
	int dbg = 0;

	if((className=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((classType=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((directory=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((packName=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((filePath=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);

	// for(int i = 1;i<argc;++i){
	// 	dbg=!strcmp(argv[i],"-debug");
	// }

	for(int i= 0;++i<argc&&!dbg;dbg=strcmp(argv[i],"-debug")?0:1);

DEBUG_ARGLEN;

	for(int i = 1;i<argc;++i)
	{
		
		if(argv[i][0]!='-'){
			return putError(1);
		}else{
			
DEBUG_VARLIST;

			if(argv[i][1]=='h'){
				return putError(0);
			}else if(argv[i][1]=='p'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(packName,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(packName,argv[i],2);

DEBUG_VAR("assignment",packName);
			}else if(argv[i][1]=='t'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(classType,argv[i],0);												
					else return putError(2);
				}else
				my_strcpy(classType,argv[i],2);

DEBUG_VAR("assignment",classType);
			}else if(argv[i][1]=='c'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(className,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(className,argv[i],2);

DEBUG_VAR("assignment",className);
			}else if(argv[i][1]=='f'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(filePath,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(filePath,argv[i],2);

DEBUG_VAR("assignment",filePath);
			}else if(argv[i][1]=='d'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(directory,argv[i],0);
					else return putError(2);
				}else if(strcmp(argv[i],"-debug"))
					my_strcpy(directory,argv[i],2);

DEBUG_VAR("assignment",directory);
			}else{
				return putError(3);
			}
		}
	}

	if(!strlen(filePath)){
		
	if(!strlen(directory)){
		return putError(1);
	}else{
		directory[strlen(directory)-1]=directory[strlen(directory)-1]=='/'?'\0':directory[strlen(directory)-1];
	}
DEBUG_VAR("finaly",directory);
	if(!strlen(classType)){
		my_strcpy(classType,"struct",0);
	}
DEBUG_VAR("finaly",classType);
	if(!strlen(className)){
		return putError(1);
	}
DEBUG_VAR("finaly",className);
	if(!strlen(packName)){
		my_strcpy(packName,strstr(directory,"/src/"),5);
	}
DEBUG_VAR("finaly",myReplace(packName,'/','.'));


	char* loge;
	if(!strcmp(classType,"struct"))
		loge=crStruct(directory,(char*)myReplace(packName,'/','.'),className);
	else if(!strcmp(classType,"main"))
		loge=crMain(directory,(char*)myReplace(packName,'/','.'),className);
	else if(is_num(classType))
		loge=crTemp(directory,(char*)myReplace(packName,'/','.'),className,atoi(classType));
		// printf("classType is temp%d",atoi(classType));
	else
		return putError(2);

	}else{
		printf("in\n");
		getset(filePath);
	}


	


//Create directory in here

// DEBUG_VAR("",loge);
// 	loge = crProject(proName);
// DEBUG_VAR("",loge);
// 	loge = crMakefile(proName,packName);
// DEBUG_VAR("",loge);
// 	loge = crClass(packPath,packName,className);
// DEBUG_VAR("",loge);


	free(classType);
	classType=NULL;
	free(packName);
	packName=NULL;
	free(filePath);
	filePath=NULL;
	free(className);
	className=NULL;
	free(directory);
	directory=NULL;
	return 0;
}

char* crStruct(char* directory,char* packName,char* class)
{
	char* file;
	if((file = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;

	sprintf(file,"%s/%s.java",directory,class);

	FILE *fp;
	if((fp=fopen(file,"w+"))==NULL) return putError(6);

	char line[128];
	sprintf(line,"package %s;\n\n",packName);

	char line2[128];
	sprintf(line2,"public class %s {\n\n    public %s () {\n			\n	}\n\n}",class,class);

	char line3[128];
	sprintf(line3,"/**\n * %s\n */\n",class);

	if(fileWriteLine(fp,line))
	if(fileWriteLine(fp,line3))
	if(fileWriteLine(fp,line2))
	loge = "create Class success！";

	fclose(fp);
	fp=NULL;
	free(file);
	file=NULL;
	return loge;
}

char* crMain(char* directory,char* packName,char* class)
{
	char* file;
	if((file = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;

	sprintf(file,"%s/%s.java",directory,class);

	FILE *fp;
	if((fp=fopen(file,"w+"))==NULL) return putError(6);

	char line[128];
	sprintf(line,"package %s;\n\n",packName);

	char line2[128];
	sprintf(line2,"public class %s {\n\n    public static void main (String args[]) {\n			\n	}\n\n}",class);

	char line3[128];
	sprintf(line3,"/**\n * %s\n */\n",class);

	if(fileWriteLine(fp,line))
	if(fileWriteLine(fp,line3))
	if(fileWriteLine(fp,line2))
	loge = "create Class success！";

	fclose(fp);
	fp=NULL;
	free(file);
	file=NULL;
	return loge;
}

char* crTemp(char* directory,char* packName,char* class,int item)
{
	char* file;
	if((file = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;

	sprintf(file,"%s/%s.java",directory,class);

	FILE *fp;
	if((fp=fopen(file,"w+"))==NULL) return putError(6);
	char line[128];
	sprintf(line,"package %s;\n\n",packName);

	char line2[512];
	int pit = 0;
	pit+=sprintf(line2+pit,"public class %s {\n\n",class);
	for(int i = 1 ;i<=item;++i){
		pit+=sprintf(line2+pit,"\tprivate type%d name%d;\n",i,i);
	}
	pit+=sprintf(line2+pit,"\n\tpublic %s () {\n\t\n\t}\n\tpublic %s (",class,class);
	for(int i = 1;i<=item;++i){
		if(i==item){
			pit+=sprintf(line2+pit,"type%d name%d",i,i);
			break;
		}
		pit+=sprintf(line2+pit,"type%d name%d,",i,i);
	}
	pit+=sprintf(line2+pit,") {\n");
	for(int i =1 ;i<=item;++i){
		pit+=sprintf(line2+pit,"\t\tthis.name%d=name%d;\n",i,i);
	}
	pit+=sprintf(line2+pit,"\t}\n\n}");

	char line3[128];
	sprintf(line3,"/**\n * %s\n */\n",class);

	if(fileWriteLine(fp,line))
	if(fileWriteLine(fp,line3))
	if(fileWriteLine(fp,line2))
	loge = "create temp success！";

	fclose(fp);
	fp=NULL;
	free(file);
	file=NULL;
	return loge;
}

char* getset(char* file)
{
	// struct stat buf;

	// int res = stat(file,&buf);
	char* loge;
	char buff[512];
	// char* doc;
	FILE *fp;

	printf("getin:%s\n",file);
	if((fp=fopen(file,"r"))==NULL) return putError(6);
	// fseek(fp,0,SEEK_END);
	// long size=ftell(fp);
	// fseek(fp,0,SEEK_SET);
	// fclose(fp);
	// rewind(fp);
	// printf("size:%ld\n",size);
	// doc= (char*)malloc(sizeof(char)*size);
	// fgets(fp,size,doc);
	while(fgets(buff,sizeof(buff),fp)){
		if(strstr(buff,"private"))
		printf("%s",buff);
		
	}
	// fread(doc,size,1,fp);
	// doc[size-1] = '\0';
	// printf("%s",doc);

	// printf(strstr(doc,"private"));
	// char **item;
	// printf("%c",doc[1]);
	
	// for(int i =0;i<size-1;i++)
	// printf(doc[i]);

	// printf("doc[0]=%c\n",doc[0]);
	// printf("doc[1]=%c\n",doc[1]);
	// printf("doc[size-1]=%c\n",doc[size-1]);
	// printf("doc[size]=%c\n",doc[size]);



	// doc[size]
	// for(int i =0 ;i<size)
	// char line[128];
	// sprintf(line,"package %s;\n\n",packName);

	// char line2[128];
	// sprintf(line2,"public class %s {\n\n    public static void main (String args[]) {\n			\n	}\n\n}",class);

	// char line3[128];
	// sprintf(line3,"/**\n * %s\n */\n",class);

	// if(fileWriteLine(fp,line))
	// if(fileWriteLine(fp,line3))
	// if(fileWriteLine(fp,line2))
	loge = "create Class success！";
	// free(doc);
	// doc=NULL;
	fclose(fp);
	fp=NULL;
	// free(file);
	// file=NULL;
	return loge;
}