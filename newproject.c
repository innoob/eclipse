/*********************************************************************
 *> Author:裴鉴湘 By:Vim 6.4 On:Linux 4.9.0-deepin4-amd64 GNU/Linux
 *> Email:jb71415@outlook.com
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "newproject.h"


/*
This program requires two necessary parameters
 <ProjectName> and <PackageName> to create a project,
you can also specify additional parameters,
such as: "-d" <directory> is used to specify the path of the project, 
if you don't specify the default path project will be created in the current directory
*/

int main(int argc,char** argv)
{
	char* packName;
	char* proName;
	char* proDir;
	char* className;
	int dbg = 0;

	if((packName=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((proName= (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((proDir= (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	if((className=(char*)malloc(sizeof(char)*128))==NULL) return putError(5);

	for(int i = 1;i<argc;++i){
		dbg=!strcmp(argv[i],"-debug");
	}

DEBUG_ARGLEN;

	for(int i = 1;i<argc;++i)
	{
		
		if(argv[i][0]!='-'){
			if(argc<2){
				return putError(1);
			}
			my_strcpy(proName,argv[i],0);
			if(++i<argc&&argv[i][0]!='-'&&argv[i][0]!='.') my_strcpy(packName,argv[i],0);
			else return putError(2);
			break;
			// return putError(1);
		}else{
			
DEBUG_VARLIST;

			if(argv[i][1]=='h'){
				return putError(0);
			}else if(argv[i][1]=='p'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(proName,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(proName,argv[i],2);

DEBUG_VAR("assignment",proName);
			}else if(argv[i][1]=='b'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(packName,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(packName,argv[i],2);

DEBUG_VAR("assignment",packName);
			}else if(argv[i][1]=='c'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(className,argv[i],0);
					else return putError(2);
				}else
				my_strcpy(className,argv[i],2);

DEBUG_VAR("assignment",className);
			}else if(argv[i][1]=='d'){
				if(strlen(argv[i])<3){
					if(++i<argc&&argv[i][0]!='-') my_strcpy(proDir,argv[i],0);
					else return putError(2);
				}else{
					if(strcmp(argv[i],"-debug"))
					my_strcpy(proDir,argv[i],2);
				}

DEBUG_VAR("assignment",proDir);
			}else{
				return putError(3);
			}

			// switch(argv[i][1]){
			// 	case 'd':
			// 		strcpy(proDir,argv[i]+2);
			// 		break;
			// 	case 'p':
			// 		strcpy(proName,argv[i]+2);
			// 		break;
			// 	case 'b':
			// 		strcpy(packName,argv[i]+2);
			// 		break;
			// 	default:
			// 		putError(3);
			// }
			// printf("argv[%d]=%s\n",i,argv[i]);
		}
	}

	if(!strlen(proName)){
		return putError(1);
	}
	if(!strlen(packName)){
		my_strcpy(packName,"com.default",0);		
	}
	if(!strlen(proDir)){
		my_strcpy(proDir,"./",0);
	}
	if(!strlen(className)){
		my_strcpy(className,proName,0);
	}


/*Replace word <.> to </> in here
Make a path to Create project and package
*/


// 	myReplace(packName,'.','/');
// DEBUG_VAR("Replace",packName);	
	
	char  packPath[128];
	
	if(proDir[strlen(proDir)-1]!='/'){
		strcat(proDir,"/");
	}
	strcat(proDir,proName);
	sprintf(packPath,"%s/src/%s",proDir,myReplace(packName,'.','/'));
	strcat(proDir,"/bin");

DEBUG_VAR("finaly",proDir);
DEBUG_VAR("finaly",packPath);
DEBUG_VAR("finaly",className);

//Create directory in here

	crDir(proDir);
	crDir(packPath);
	char* loge = crClasspath(proName);
DEBUG_VAR("",loge);
	loge = crProject(proName);
DEBUG_VAR("",loge);
	loge = crMakefile(proName,packName);
DEBUG_VAR("",loge);
	loge = crClass(packPath,packName,className);
DEBUG_VAR("",loge);


	free(proName);
	proName=NULL;
	free(packName);
	packName=NULL;
	free(proDir);
	proDir=NULL;
	free(className);
	className=NULL;

	return 0;
}
/*
This is a file path to create a function, 
this function can be directly created subdirectories 
without the need to create one by one, 
used to project packaging.
	<sPathName> --> directory
*/
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

char* crClasspath(char* proName)
{
	char* path;
	if((path = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;
	strcpy(path,proName);
	strcat(path,"/.classpath");

	xmlDoc* doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNode* root = xmlNewNode(NULL,BAD_CAST"classpath");
	xmlDocSetRootElement(doc,root);
	xmlNode* chnode = xmlNewNode(NULL,BAD_CAST"classpathentry");
	xmlNewProp(chnode,BAD_CAST"kind",BAD_CAST"src");
	xmlNewProp(chnode,BAD_CAST"path",BAD_CAST"src");	
	xmlAddChild(root,chnode);
	chnode = xmlNewNode(NULL,BAD_CAST"classpathentry");
	xmlNewProp(chnode,BAD_CAST"kind",BAD_CAST"con");
	xmlNewProp(chnode,BAD_CAST"path",BAD_CAST"org.eclipse.jdt.launching.JRE_CONTAINER/org.eclipse.jdt.internal.debug.ui.launcher.StandardVMType/JavaSE-1.8");
	xmlAddChild(root,chnode);
	chnode = xmlNewNode(NULL,BAD_CAST"classpathentry");
	xmlNewProp(chnode,BAD_CAST"kind",BAD_CAST"output");
	xmlNewProp(chnode,BAD_CAST"path",BAD_CAST"bin");
	xmlAddChild(root,chnode);
	
	if(!xmlSaveFile(path,doc)){
		loge = "create .classpath failed!";
	}else{
		loge="create .classpath success!";
	}
	xmlFreeDoc(doc);
	doc=NULL;
	free(path);
	path=NULL;

	return loge;
}

char* crProject(char* proName)
{
	char* path;
	if((path = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;
	strcpy(path,proName);
	strcat(path,"/.project");

	xmlDoc* doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNode* root = xmlNewNode(NULL,BAD_CAST"projectDescription");
	xmlDocSetRootElement(doc,root);
	xmlNode* chnode = xmlNewNode(NULL,BAD_CAST"name");
	xmlNodeAddContent(chnode,proName);
	xmlAddChild(root,chnode);

	chnode = xmlNewNode(NULL,BAD_CAST"comment");
	xmlNodeAddContent(chnode,"\n");
	xmlAddChild(root,chnode);

	chnode = xmlNewNode(NULL,BAD_CAST"projects");
	xmlNodeAddContent(chnode,"\n");
	xmlAddChild(root,chnode);

	chnode = xmlNewNode(NULL,BAD_CAST"buildSpec");
	xmlNodeAddContent(chnode,"\n");
	xmlAddChild(root,chnode);
	xmlNode* itemnode = xmlNewNode(NULL,BAD_CAST"buildCommand");
	xmlAddChild(chnode,itemnode);
	chnode = xmlNewNode(NULL,BAD_CAST"name");
	xmlNodeAddContent(chnode,"org.eclipse.jdt.core.javabuilder");
	xmlAddChild(itemnode,chnode);
	chnode = xmlNewNode(NULL,BAD_CAST"arguments");
	xmlNodeAddContent(chnode,"\n");
	xmlAddChild(itemnode,chnode);


	chnode = xmlNewNode(NULL,BAD_CAST"natures");
	xmlNodeAddContent(chnode,"\n");
	xmlAddChild(root,chnode);
	itemnode = xmlNewNode(NULL,BAD_CAST"nature");
	xmlNodeAddContent(itemnode,"org.eclipse.jdt.core.javanature");
	xmlAddChild(chnode,itemnode);

	if(!xmlSaveFile(path,doc)){
		loge="create .project failed!";
	}else{
		loge="create .project success!";
	}
	
	xmlFreeDoc(doc);
	doc=NULL;
	free(path);
	path=NULL;

	return loge;

}

char* crMakefile(char* proName,char* packName)
{		
	char* path;
	if((path = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;
	sprintf(path,"%s/Makefile",proName);
	FILE *fp;
	if((fp=fopen(path,"w+"))==NULL) return putError(6);

	char line1[128];
	sprintf(line1,"Target=%s.$(class)\n",packName);

	char line2[128];
	sprintf(line2,"	javac -d ./bin ./src/%s/*.java\n\n",myReplace(packName,'.','/'));

	if(fileWriteLine(fp,line1))
	if(fileWriteLine(fp,"Objs= ./bin/$(path)/*.class\n\n"))
	if(fileWriteLine(fp,"all:$(Target)\n"))
	if(fileWriteLine(fp,"	clear;\n"))
	if(fileWriteLine(fp,"	java -classpath ./bin $< $(args)\n\n"))
	if(fileWriteLine(fp,"$(Target):\n"))
	if(fileWriteLine(fp,line2))
	if(fileWriteLine(fp,"clean:\n"))
	if(fileWriteLine(fp,"	-rm -rf ./bin/*\n"))
	loge = "create Makefile success！";
	fclose(fp);
	fp=NULL;
	free(path);
	path=NULL;
	return loge;
}


char* crClass(char* packPath,char*packName,char* class)
{
	char* path;
	if((path = (char*)malloc(sizeof(char)*128))==NULL) return putError(5);
	char* loge;
	sprintf(path,"%s/%s.java",packPath,class);

	FILE *fp;	
	if((fp=fopen(path,"w+"))==NULL) return putError(6);

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
	free(path);
	path=NULL;
	return loge;
}

// int crProject(char* path){
//     //定义文档和节点指针
//     xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
//     xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"root");
//     //设置根节点
//     xmlDocSetRootElement(doc,root_node)
//     //在根节点中直接创建节点
//     xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");
//     xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");
//     xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");
//     //创建一个节点，设置其内容和属性，然后加入根结点
//     xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"node2");
//     xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");
//     xmlAddChild(root_node,node);
//     xmlAddChild(node,content);
//     xmlNewProp(node,BAD_CAST"attribute",BAD_CAST "yes");
//     //创建一个儿子和孙子节点
//     node = xmlNewNode(NULL, BAD_CAST "son");
//     xmlAddChild(root_node,node);
//     xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");
//     xmlAddChild(node,grandson);
//     xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));
//     //存储xml文档
//     int nRel = xmlSaveFile("CreatedXml.xml",doc);
//     if (nRel != -1)
//     {
//        cout<<"一个xml文档被创建,写入"<<nRel<<"个字节"<<endl;
//     }
//     //释放文档内节点动态申请的内存
//     xmlFreeDoc(doc);

//     return 1;
// }