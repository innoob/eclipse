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
	char* addjar;
	int dbg = 0;

	if((className=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((classType=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((directory=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((packName=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((filePath=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((addjar=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);

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
			}else if(argv[i][1]=='a'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(addjar,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(addjar,argv[i],2);

DEBUG_VAR("assignment",addjar);
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

	char* loge;
	if(!strlen(filePath)){
	if(strlen(addjar)){
		if((strstr(addjar,".jar")-addjar)+4==strlen(addjar)){
			loge=addpath(addjar);
			return;
		}else{
			printf("这不是一个有效的jar包");
			return;
		}
	}
		
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
		my_strcpy(packName,strstr(directory,"src/"),4);
	}
DEBUG_VAR("finaly",myReplace(packName,'/','.'));

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
	free(addjar);
	addjar=NULL;
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
	char* loge=NULL;
	char buff[512];
	char doc[512];
	char varib[256];
	char field[256];
	FILE *fp=NULL;

	if((fp=fopen(file,"r+"))==NULL) return putError(6);
	char* box[20];
	int pt =0;
	int pv = 0;
	int pf=0;
	int num=0;
	while(fgets(buff,sizeof(buff),fp)!=NULL){
		if(strstr(buff,"class")!=NULL){
			my_split(box,buff," ");
			pv+=sprintf(varib+pv,"\n\n\tpublic %s (",box[1]);
		}
		if(strstr(buff,"private")!=NULL){
			num = my_split(box,buff," ;")-2;
			pt+=sprintf(doc+pt,"\tpublic %s get%s(){\n\t\treturn this.%s;\n\t}\n",box[0],pascalName(box[1]),box[1]);
			pt+=sprintf(doc+pt,"\tpublic void set%s(%s %s){\n\t\tthis.%s=%s;\n\t}\n",pascalName(box[1]),box[0],box[1],box[1],box[1]);
			if(varib[pv-1]=='(')
			pv+=sprintf(varib+pv,"%s %s",box[0],box[1]);
			else
			pv+=sprintf(varib+pv,",%s %s",box[0],box[1]);
			pf+=sprintf(field+pf,"\t\tthis.%s = %s;\n",box[1],box[1]);
		}
	}
	if(!num){
		fclose(fp);
		fp=NULL;
		loge="variable not found!";
		return loge;
	}
	int ft = 0;
	fseek(fp,ft,SEEK_END);
	while('}'!=fgetc(fp)){
		fseek(fp,--ft,SEEK_END);
	}
	fseek(fp,--ft,SEEK_END);
	fprintf(fp,"%s){\n%s\t}\n%s\n}",varib,field,doc);
	// if(fileWriteLine(fp,line))
	// if(fileWriteLine(fp,line3))
	// if(fileWriteLine(fp,line2))
	loge = "create Class success！";
	// free(doc);
	// doc=NULL;
	fclose(fp);
	fp=NULL;
	// for(int i= 0 ;i<pt;i++)
	// free(box[i]);
	// free(box);
	// box=NULL;
	// free(file);
	// file=NULL;
	return loge;
}
char* addpath(char* jarpath)
{
	FILE* fp;
	if((fp = fopen(".classpath","r+"))==NULL){
		printf("当前目录不在项目地址");
		return;
	}

	crDir("lib");
	char cmd[128];
	sprintf(cmd,"cp %s lib/",jarpath);
	system(cmd);

	char jarname[128];
	int l = strlen(jarpath);
	while(l-->0)
		if(jarpath[l]=='/')
		break;
	my_strcpy(jarname,jarpath,l);
	
	char addline[128];
	sprintf(addline,"\t<classpathentry kind=\"lib\" path=\"lib%s\"/>\n</classpath>\0",jarname);
	fseek(fp,-13,SEEK_END);
	fputs(addline,fp);

	free(fp);
	fp=NULL;
}
int crDir(const char* sPathName)  
{  
	// char DirName[256];
	char * DirName;
	if((DirName = (char*)malloc(sizeof(char)*strlen(sPathName)))==NULL) return putError(5);
	strcpy(DirName, sPathName);  
	int i,len = strlen(DirName);  
	if(DirName[len-1]!='/')
	strcat(DirName, "/");  

	len = strlen(DirName);

	for(i=1; i<len; ++i)  
	{
		if(DirName[i]=='/')  
		{  
			DirName[i] = 0;  
			if(access(DirName, NULL)!=0 )  
			{
				if(mkdir(DirName, 0755)==-1)  
				{
					perror("mkdir error");
					free(DirName);
					DirName=NULL;
					return -1; 
				}
			}
			DirName[i] = '/';
		}
	}
	free(DirName);
	DirName=NULL;
	return 0;  
}