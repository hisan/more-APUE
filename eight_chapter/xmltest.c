#include<stdio.h>
#include<libxml/parser.h>

#define CAST (const xmlChar*) 

int createabasexmlfile()
{
	xmlDocPtr doc = xmlNewDoc(CAST"1.0");
	xmlNodePtr root = xmlNewNode(NULL,CAST"PolicyPack");
	xmlDocSetRootElement(doc,root);
	
	xmlSaveFileEnc("test.xml",doc,"UTF-8");
	
	xmlFree(doc);
}

int main(void)
{
	createabasexmlfile();
	return 0;
}