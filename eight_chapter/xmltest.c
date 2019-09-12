#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<libxml/parser.h>

#define CAST (const xmlChar*)

#define ERR 0
#define OK  1

#define NAMELEN 80

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

int InSertJobxmlfile(xmlDocPtr doc,NameValue *pNameMap,const int PropNum)
{
	xmlNodePtr root 	= NULL;
	xmlNodePtr ComPanys = NULL;
	xmlNodePtr ComPany  = NULL;
	
	int count = 0;
	
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
	for (;count <PropNum;count++)
	{
		xmlNewProp(ComPany, CAST pNameMap->p1[count], CAST pNameMap->p2[count]);
	}
	
	xmlAddChild(ComPanys,ComPany);
	
	return OK;
}

xmlDocPtr XmlDocInit(const char *filename)
{
	xmlDocPtr doc = xmlReadFile(filename,"UTF-8",XML_PARSE_RECOVER);
	if (doc == NULL)
	{
		doc = CreateXmlBaseDoc();
	}
	
	return doc;
}

xmlNodePtr FinComPanyNodeByName(const char *pName,xmlDocPtr Doc)
{
	xmlNodePtr root = xmlDocGetRootElement(Doc);
	if (root == NULL)
	{
		fprintf(stderr,"error root!\n");
		return ERR;
	}
	
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
	
	pNameMap = NULL;
	pNameMap = malloc(sizeof(NameValue));
	memset(pNameMap,0,sizeof(NameValue));
	MapInit(pNameMap);
	
	xmlKeepBlanksDefault(0);
	
	FILE *fp = fopen(argv1,"r");
	int j = 0;
	if (fp == NULL)
	{
		fprintf(stderr,"ERR:open inputfile failed\r\n");
		return ERR;
	}
	
	doc =  XmlDocInit(argv2);

	while(fgets(tempbuf,sizeof(tempbuf),fp)!=NULL)
	{
		memset(pNameMap->p2,0,sizeof(pNameMap->p2));
		count = 0;
		
		pName = strstr(tempbuf,"Name:");		
		pAddr = strstr(tempbuf,"Address:");		
		pTel = strstr(tempbuf,"Tel:");		
		pSal = strstr(tempbuf,"Sal:");
		pTime = strstr(tempbuf,"Time:");
		pScale = strstr(tempbuf,"Scale:");
		pTd = strstr(tempbuf,"Two-day-w:");
		pOd = strstr(tempbuf,"One-day-w:");


		pName += 5;
		j = 0;
		while( pName != pAddr)
		{
			pNameMap->p2[count][j++] = *pName;
			pName++;
		}
		count++;
	
		pAddr += 8;
		j = 0;
		while( pAddr != pTel)
		{
			pNameMap->p2[count][j++] = *pAddr;
			pAddr++;
		}
		count++;

		pTel += 4;
		j = 0;
		while( pTel != pSal)
		{
			pNameMap->p2[count][j++] = *pTel;
			pTel++;
		}
		count++;

		pSal += 4;
		j = 0;
		while( pSal != pTime)
		{
			pNameMap->p2[count][j++] = *pSal;
			pSal++;
		}
		count++;

		pTime += 5;
		j = 0;
		while( pTime != pScale)
		{
			pNameMap->p2[count][j++] = *pTime;
			pTime++;
		}
		count++;

		pScale += 6;
		j = 0;
		{
			pNameMap->p2[count][j++] = *pScale;
			pScale++;
		}
		count++;

		pTd += 10;
		j = 0;
		while( pTd != pOd)
		{
			pNameMap->p2[count][j++] = *pTd;
			pTd++;
		}
		count++;

		pOd += 10;
		j = 0;
		while( *pOd != '\n')
		{
			pNameMap->p2[count][j++] = *pOd;
			pOd++;
		}
		count++;

		xmlNodePtr cur = NULL;
		
		if ( (cur = FinComPanyNodeByName(pNameMap->p2[0],doc)) != NULL)
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
