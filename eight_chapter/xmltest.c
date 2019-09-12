#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<libxml/parser.h>

#define CAST (const xmlChar*)

#define ERR 0
#define OK  1

#define NAMELEN 30
#define ADDRLEN 30
#define TELLEN	15
#define SALLEN 10
#define TIMELEN 10
#define SCALELEN 5
#define TWODAYLEN 5
#define ONEDAYLEN 5

typedef struct st_map
{
	char p1[8][NAMELEN];	//name
	char p2[8][NAMELEN];	//value
	
}NameValue;

NameValue *pNameMap;

int MapInit(NameValue *pNameMap)
{
	if (pNameMap == NULL)
	{
		fprintf(stderr,"struct is error\r\n");
		return ERR;
	}
	
    int count = 0;
	strcpy(pNameMap->p1[count++],"Name");
	strcpy(pNameMap->p1[count++],"Address");
	strcpy(pNameMap->p1[count++],"Tel");
	strcpy(pNameMap->p1[count++],"Sal");
	strcpy(pNameMap->p1[count++],"Time");
	strcpy(pNameMap->p1[count++],"Scale");
	strcpy(pNameMap->p1[count++],"Two-day-w");
	strcpy(pNameMap->p1[count++],"One-day-w");
	
	return OK;
}

xmlDocPtr CreateXmlBaseDoc()
{
	xmlDocPtr doc = xmlNewDoc(CAST"1.0");
	xmlNodePtr root = xmlNewNode(NULL,CAST"DataBase");
	xmlDocSetRootElement(doc,root);
	xmlNodePtr ComPanys = xmlNewNode(NULL,CAST"ComPanys");
	xmlAddChild(root,ComPanys);
	
	return doc;
}

int InSertJobxmlfile(xmlDocPtr Doc,NameValue *pNameMap,const int PropNum)
{
	xmlDocPtr doc 		= NULL;
	xmlNodePtr root 	= NULL;
	xmlNodePtr ComPanys = NULL;
	xmlNodePtr ComPany  = NULL;
	
	int count = 0;
	
	doc = Doc;
	if (doc == NULL)
	{
		fprintf(stderr,"no such file\r\n");
		return ERR;
	}
	
	root = xmlDocGetRootElement(doc);
	if (root == NULL)
	{
		fprintf(stderr,"error root!\n");
		return ERR;
	}
	
	ComPanys = root->children;
	
	ComPany = xmlNewNode(NULL,CAST"ComPany");
	for (count = 0; count < PropNum; count++)
	{
		xmlNewProp(ComPany, CAST pNameMap->p1[count], CAST pNameMap->p2[count]);
	}
	
	xmlNodePtr ChildNode = ComPanys->children;
	
	if (ChildNode == NULL)
	{
		xmlAddChild(ComPanys,ComPany);
	}
	else 
	{
		xmlAddSibling(ChildNode,ComPany);
	}
	
	return OK;
}

xmlNodePtr FinComPanyNodeByName(const char *filename,const char *pName,xmlDocPtr* Doc)
{
	xmlDocPtr doc = xmlReadFile(filename,"UTF-8",XML_PARSE_RECOVER);
	if (doc == NULL)
	{
		doc = CreateXmlBaseDoc();
	}
	
	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (root == NULL)
	{
		fprintf(stderr,"error root!\n");
		return ERR;
	}
	
	*Doc = doc;
	
	xmlNodePtr ComPanys = root->children;
	xmlNodePtr cur = ComPanys->children;
	
	while(cur != NULL)
	{
		xmlChar* NameProp = NULL;
		NameProp = xmlGetProp(cur, CAST"Name");
		if ( 0 == xmlStrcmp(NameProp,CAST pName) )
		{
			xmlFree(NameProp);
			return cur;
		}
		xmlFree(NameProp);
		cur = cur->next;
	}
	
	return NULL;
}

int main()
{
	const char *argv1 = "data.txt";
	const char *argv2 = "job.xml";
	
	xmlDocPtr doc = NULL;
	char tempbuf[1024] = {0};
	int count = 0;
	char *pName,*pAddr,*pTel,*pSal,*pTime,*pScale,*pTd,*pOd;	
	char Name[30] = {0};
	
	pNameMap = NULL;
	pNameMap = malloc(sizeof(NameValue));
	memset(pNameMap,0,sizeof(NameValue));
	MapInit(pNameMap);
	
	xmlKeepBlanksDefault(0);
	
	
	
	FILE *fp = fopen(argv1,"r");
	
	if (fp == NULL)
	{
		fprintf(stderr,"ERR:open inputfile failed\r\n");
		return ERR;
	}

	while(fgets(tempbuf,sizeof(tempbuf),fp)!=NULL)
	{
		memset(pNameMap->p2,0,sizeof(pNameMap->p2));
		count = 0;
		
		pName = strstr(tempbuf,"Name:");
		strncpy(pNameMap->p2[count],pName+5,sizeof(char)*NAMELEN);
		strncpy(Name,pName+5,NAMELEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;
	
		pAddr = strstr(tempbuf,"Address:");
		strncpy(pNameMap->p2[count],pAddr+8,sizeof(char)*ADDRLEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pTel = strstr(tempbuf,"Tel:");
		strncpy(pNameMap->p2[count],pTel+4,sizeof(char)*TELLEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pSal = strstr(tempbuf,"Sal:");
		strncpy(pNameMap->p2[count],pSal+4,sizeof(char)*SALLEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pTime = strstr(tempbuf,"Time:");
		strncpy(pNameMap->p2[count],pTime+5,sizeof(char)*TIMELEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pScale = strstr(tempbuf,"Scale:");
		strncpy(pNameMap->p2[count],pScale+6,sizeof(char)*SCALELEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pTd = strstr(tempbuf,"Two-day-w:");
		strncpy(pNameMap->p2[count],pTd+10,sizeof(char)*TWODAYLEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		pOd = strstr(tempbuf,"One-day-w:");
		strncpy(pNameMap->p2[count],pOd+10,sizeof(char)*ONEDAYLEN);
		pNameMap->p2[count][strlen(pNameMap->p2[count])] = '\0';
		count++;

		xmlNodePtr cur = NULL;
		
		if ( (cur = FinComPanyNodeByName(argv2,Name,&doc)) != NULL)
		{
			//修改
			xmlUnlinkNode(cur);
			xmlFreeNode(cur);
			InSertJobxmlfile(doc,pNameMap,8);
		}
		else 
		{
			InSertJobxmlfile(doc,pNameMap,8);
		}	
	}
	
	xmlSaveFileEnc(argv2,doc,"UTF-8");
	
	return 0;
}












