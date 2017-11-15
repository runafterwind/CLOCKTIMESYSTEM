#include "clocktim.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <iconv.h>	
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>

#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>


/*
	�����û�id��ָ��ģ�棬���ϴ���������
	api 10 �����µı���ģ���ϴ���������
	key:
	serial:
	fid:
	reseve:
	
	return:
	<?xml version="1.0" encoding="UTF-8" ?>
	<template> 
		<fid value="00001" /> 
		<reserved value="LONGSTRINGOFTEMPLATE"/>
	</template>
*/

#define PATH  "tmp.xml"

char * Save_Templates(char * Key,char * Serial,char * fid,char *  Reseved)
{

#if 1
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;
	xmlAttrPtr tmpattr=NULL;
	doc = xmlNewDoc(BAD_CAST"1.0");
	if (doc == NULL) {
     		fprintf(stderr, "Failed to new doc.\n");
     		return NULL;
     	}
	
		 //�������ڵ�
	 root_node = xmlNewNode(NULL, BAD_CAST"template");		
	 if (root_node == NULL) {
		fprintf(stderr, "Failed to new root node.\n");
	 	goto FAILED;
	 }
	//�����ڵ���ӵ��ĵ���
  
	xmlDocSetRootElement(doc, root_node);
#if 0
	xmlNewChild(root_node, NULL,BAD_CAST"fid", (xmlChar *)fid);		
	xmlNewChild(root_node, NULL, BAD_CAST"reserved", (xmlChar *)Reseved);
#else
	tmpnode=xmlNewTextChild(root_node, NULL, "fid", NULL);
	tmpattr=xmlNewProp(tmpnode,"value",(xmlChar *)fid);
	tmpnode=xmlNewTextChild(root_node, NULL, "reserved", NULL);
	tmpattr=xmlNewProp(tmpnode,"value",(xmlChar *)Reseved);

#endif
	//���ĵ����浽�ļ��У�����utf-8�����ʽ����
	xmlSaveFormatFileEnc(PATH, doc, "UTF-8", 1);
	xmlFreeDoc(doc);

    	int fd;
	int size;
	char * content;
	struct stat filinfo;
	stat(PATH,&filinfo);
	size=filinfo.st_size;
	fd=open(PATH,O_RDWR);
	content=(char *)malloc(size);
	read(fd,content,size);
	close(fd);

	//�����ڴ��е�xml�ַ���
	//xmlNodePtr bak=NULL;
	doc=xmlReadMemory(content, size, NULL, NULL, 0);
	root_node=xmlDocGetRootElement( doc);
	tmpnode=root_node->children;
	while(tmpnode!=NULL)
		{

			if(!xmlStrcmp(tmpnode->name, (const char *)"fid"))
				printf("%s value=%s \n",tmpnode->name,xmlGetNoNsProp(tmpnode, "value"));

			if(!xmlStrcmp(tmpnode->name, (const char *)"reserved"))
				printf("%s value=%s \n",tmpnode->name,xmlGetNoNsProp(tmpnode, "value"));

		/*	
			if(tmpnode->children){
				bak=tmpnode->children->next;
				tmpnode=tmpnode->children;
				}
			else if(tmpnode=tmpnode->next){
				bak=tmpnode->next->next;
				tmpnode=tmpnode->next;
				}
			else
				tmpnode=bak;
		*/
			
		 tmpnode=tmpnode->next;
	}

	
	
	/*  �� conternt ���͸���������?*/
       return content;
FAILED:
	if (doc) {
     	xmlFreeDoc(doc);
     	}
	  return NULL;

#else
		xmlDocPtr  doc = NULL;
		xmlNodePtr root_node = NULL;
		xmlNodePtr tmpnode=NULL;
		xmlAttrPtr tmpattr=NULL;
	
		char * fidattr=NULL;
		char * resattr=NULL;
		
		char * back;		//backΪ�ӷ��������ص�����

		doc=xmlReadMemory(back, size, NULL, NULL, 0);
		root_node=xmlDocGetRootElement( doc);
		tmpnode=root_node->children;
		while(tmpnode!=NULL)
		{

			if(!xmlStrcmp(tmpnode->name, (const char *)"fid"))
				printf("%s value=%s \n",tmpnode->name,(fidattr=xmlGetNoNsProp(tmpnode, "value")));

			if(!xmlStrcmp(tmpnode->name, (const char *)"reserved"))
				printf("%s value=%s \n",tmpnode->name,(resattr=xmlGetNoNsProp(tmpnode, "value")));

			
			
		 tmpnode=tmpnode->next;
	}
		
	return back;
#endif


}




/*

	api27:ͬ�����ص�ģ������������
	key:
	serial:
	fid:
	all:
	return : //����ֵ���ɷ��������ص����ݣ����Ǹ��������ϴ������ݸ���ô����
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<Header>
	<status>Successful</status>
	<status_message></status_message>
	<header_title></header_title>
	</Header>
	 
	<Detail>
	</Detail>
	<Table>
	</Table>
	</result>

*/

char * Update_Template_Status(char *Key,char * Serial ,char * fid,BOOL  ALL)
{


}


/*

	api8:���ڽ�ģ����Ʒ��������ص�ʱ�ӡ� 
	��һ��������������ȡ���п������ص�ʱ�ӵ�ģ����б� 
	�����á�Download_Templates_Batch_4���������ؿ���ģ������Ρ�
	key:
	serial:
	
*/

char *Download_Templates_4(char * Key,char * Serial) 
{

}


/*
	api9:���ڴӷ�����������ģ��
	key:
	serial:
	�������ķ������ݣ�
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<current_time name="Account Current Time" value="2012-12-14 13:52:51" />
	<utc_offset name="Account UTC Offset" value="-8.00" />
	<account_name name="Account Name" value="Processing Point Test Room" />
	</result>

*/
char *  Download_Templates_Batch_4(char *key,char *serial)
{

	char * back;	//���������ص����ݣ���Ҫ����
	
	
}



/*
	api4:�ӷ�������ȡʱ����±���ʱ��
	key:
	serial:

*/
int update_time()
{


}





#define KEY "key4646"
#define SERIAL  "asdfaf6464"
#define FID  "123456"
#define RESETV  "sdflk"
int main()
{
	char * p;

	p=Save_Templates(KEY, SERIAL, FID, RESETV);
	printf("contern:%s \n",p);
	return 0;
}

