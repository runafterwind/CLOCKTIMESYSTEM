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
	新增用户id及指纹模版，并上传到服务器
	api 10 ：将新的本地模板上传到服务器
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
	
		 //创建根节点
	 root_node = xmlNewNode(NULL, BAD_CAST"template");		
	 if (root_node == NULL) {
		fprintf(stderr, "Failed to new root node.\n");
	 	goto FAILED;
	 }
	//将根节点添加到文档中
  
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
	//将文档保存到文件中，按照utf-8编码格式保存
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

	//解析内存中的xml字符串
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

	
	
	/*  将 conternt 发送给服务器端?*/
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
		
		char * back;		//back为从服务器返回的数据

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

	api27:同步本地的模板链表到服务器
	key:
	serial:
	fid:
	all:
	return : //返回值是由服务器返回的内容，但是给服务器上传的内容该怎么构建
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

	api8:用于将模板从云服务器下载到时钟。 
	第一个调用是用来获取所有可以下载到时钟的模板的列表。 
	随后调用“Download_Templates_Batch_4”用于下载可用模板的批次。
	key:
	serial:
	
*/

char *Download_Templates_4(char * Key,char * Serial) 
{

}


/*
	api9:用于从服务器上下载模板
	key:
	serial:
	服务器的返回内容：
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<current_time name="Account Current Time" value="2012-12-14 13:52:51" />
	<utc_offset name="Account UTC Offset" value="-8.00" />
	<account_name name="Account Name" value="Processing Point Test Room" />
	</result>

*/
char *  Download_Templates_Batch_4(char *key,char *serial)
{

	char * back;	//服务器返回的数据，需要解析
	
	
}



/*
	api4:从服务器获取时间更新本地时间
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

