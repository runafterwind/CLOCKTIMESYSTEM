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

#if 1		//发送部分
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

	xmlFreeDoc(doc);

	
	/*  将 conternt 发送给服务器端?*/
       return content;
FAILED:
	if (doc) {
     	xmlFreeDoc(doc);
     	}
	  return NULL;

#else		//接受部分
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
	xmlFreeDoc(doc);

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

int  Update_Template_Status(char *Key,char * Serial ,char * fid,BOOL  ALL)
{


}


/*

	api8:用于将模板从云服务器下载到时钟。 
	第一个调用是用来获取所有可以下载到时钟的模板的列表。 
	随后调用“Download_Templates_Batch_4”用于下载可用模板的批次。
	key:
	serial:

	return:
		<?xml version="1.0" encoding="UTF-8" ?>
		<result>
		 
			<Batch>
		 

				<User>

				</User>
				<User>

				</User>

				<Finger_ID value="021890"/>


				<Finger_ID value="000001"/>
		 
			</Batch>
		</result>

	
*/

int Download_Templates_4(char * Key,char * Serial) 
{

	/*发送？*/


	/*接 	收*/
	char * back;	//返回报文
       int length;	//返回报文长度	
	   
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;

	char * fingerID[10]={NULL};		//最多支持10个
	int count=0;
	int i;
	
	doc=xmlReadMemory(back, length, NULL, NULL, 0);
	root_node=xmlDocGetRootElement(doc);

	tmpnode=root_node->children;
	while(tmpnode)
	{
		if(xmlStrcmp(tmpnode->name, "Batch"))
			{
				tmpnode=tmpnode->children;
				continue;
			}

		if(xmlStrcmp(tmpnode->name,"Finger_ID" ))
			{
			fingerID[count++]=xmlGetProp(tmpnode, "value");
			}
		
		tmpnode=tmpnode->next;
	}

	/*处理 ?*/

	for(i=0;i<10;i++)
		if(fingerID[i])
			free(fingerID[i]);
		
}


/*
	api9:用于从服务器上下载模板
	key:
	serial:
	服务器的返回内容：
	

*/
int  Download_Templates_Batch_4(char *key,char *serial)
{

	char * back;	//服务器返回的数据，需要解析
	
	
	
}



/*
	api4:从服务器获取时间更新本地时间
	key:
	serial:

	(success)
	return:<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<current_time name="Account Current Time" value="2012-12-14 13:52:51" />
	<utc_offset name="Account UTC Offset" value="-8.00" />
	<account_name name="Account Name" value="Processing Point Test Room" />
	</result>

	(failed)
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<current_time name="Sorry" value="Account not found" />
	<utc_offset name="" value="" />
	<account_name name="" value="" />
	</result>


*/
int update_time(char * key,char * serial)
{

	/*发送报文? */
	
	/*接收报文*/

	char * back;	//返回报文
       int length;	//返回报文长度	
	   
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;
	xmlAttrPtr tmpattr=NULL;
	char*  curr_tim[2]={NULL};
	char utc_offset[2]={NULL};
	char account[2]={NULL};
	
	doc=xmlReadMemory(back, length, NULL, NULL, 0);
	root_node=xmlDocGetRootElement(doc);

	tmpnode=root_node->children;
	while(tmpnode)
	{
		
		if(!xmlStrcmp(tmpnode->name, (const char *)"current_time"))
			{
				//printf("%s value=%s \n",tmpnode->name,(fidattr=xmlGetNoNsProp(tmpnode, "value")));
				curr_tim[0]=xmlGetNoNsProp(tmpnode, "name");
				curr_tim]1]=xmlGetProp(tmpnode, "value");
			}
		if(!xmlStrcmp(tmpnode->name, (const char *)"utc_offset"))
			{
				//printf("%s value=%s \n",tmpnode->name,(resattr=xmlGetNoNsProp(tmpnode, "value")));
				utc_offset[0]=xmlGetProp(tmpnode, "name");
				utc_offset[1]=xmlGetProp(tmpnode, "value");
			}

		if(!xmlStrcmp(tmpnode->name, (const char *)"account_name"))
			{
				account[0]=xmlGetProp(tmpnode, "name");
				account[1]=xmlGetProp(tmpnode, "value");
			}
		
		tmpnode=tmpnode->next;
	}

	/*处理 ?*/

	free(curr_tim[0]);
	free(curr_tim[1]);
	free(utc_offset[0]);
	free(utc_offset[1]);
	free(account[0]);
	free(account[1]);
	
}



/*
	api1:向服务器发出更新logo请求，返回一个logo下载的URL
	key:
	serial:

	返回报文：
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<message name="Logo" value="http://ws.trackmytime.com/clock.cfc?method=get_logo&account=2162&size=3
	20x240" />
	</result>

*/
int update_logo(char * key,char * serial)
{

	/*  发送请求?*/
	/*如何创建报文*/	
	

	/*接收返回*/
	char * back;
	int length;
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;

	char* name=NULL;
	char* URL=NULL;

	doc=xmlReadMemory(back, length, NULL, NULL, 0);
	root_node=xmlDocGetRootElement(doc);
	tmpnode=root_node->children;
	if(xmlStrcmp(tmpnode, "message"))
		{
			name=xmlGetNoNsProp(tmpnode, "name");
			URL=xmlGetNoNsProp(tmpnode, "value");
		}

	/*处理 ?*/
	
	free(URL);
	free(name);
	xmlFreeDoc(doc);

}




/*
	Key
 		AJ5P8EG3M2Z3
	Serial
		e.g., BN4000-20082123
	Diagnostic_Message
		e.g., "Camera lens failure"

	return:
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
	<message value ="Request received. Ticket has been created." />
	</result>


*/

int Diagnostic_Alert(char *key ,char * serial,char * diagnostc_msg)
{

	/*创建报文*/
	
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;
	xmlAttrPtr tmpattr=NULL;
	
	doc = xmlNewDoc(BAD_CAST"1.0");
	if (doc == NULL) {
     		fprintf(stderr, "Failed to new doc.\n");
     		return -1;
     	}
	
		 //创建根节点
	 root_node = xmlNewNode(NULL, BAD_CAST"result");		
	 if (root_node == NULL) {
		fprintf(stderr, "Failed to new root node.\n");
		return -1;
	 }
	xmlDocSetRootElement(doc, root_node);
	tmpnode=xmlNewChild(root_node, NULL,BAD_CAST"messag", NULL);	
	xmlNewProp(tmpnode,"value",(xmlChar * )diagnostc_msg);
	xmlSaveFormatFileEnc(PATH, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	
	/*报文解析*/
	char * back;
	int length;
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;
	char * msg=NULL;
	
	doc=xmlReadMemory(back, length, NULL, NULL, 0);
	root_node=xmlDocGetRootElement(doc);
	tmpnode=root_node->children;
	if(xmlStrcmp(tmpnode, "message"))
	{
		msg=xmlGetNoNsProp(tmpnode, "value");
	}
	/*处理 ?*/

	free(msg);
	xmlFreeDoc(doc);
}


/*
	api2:先服务器请求更新固件，服务器返回固件下载的URL
	key:
	serial:
	version:

	服务器返回:
	<?xml version="1.0" encoding="UTF-8" ?>
	<result>
		<firmware>
			<current_fwvrs>BN4000-4.9</current_fwvrs>
			<current_fwurl>http://ws.trackmytime.com/firmware/BN3000-4.9.bin</current_fwurl>
			<current_fwsize>12551168</current_fwsize>
		</firmware>
	</result>

*/
int Update_Firmware2(char *key,char * setial,char * version)
{
	/*创建报文?*/


	/*解析报文*/
	char * back;
	int length;
	xmlDocPtr  doc = NULL;
       xmlNodePtr root_node = NULL;
	xmlNodePtr tmpnode=NULL;

	xmlChar * fwvrs=NULL,*fwurl=NULL,*fwsize;

	doc=xmlReadMemory(back, length, NULL, NULL, 0);
	root_node=xmlDocGetRootElement(doc);
	tmpnode=root_node->children;
	while()
	{
		if(xmlStrcmp(tmpnode->name, "firmware"))
			{
				tmpnode=tmpnode->children;
				continue;
			}

		if(xmlStrcmp(tmpnode->name, "current_fwvrs"))
			{
				fwvrs=xmlNodeGetContent(tmpnode);
			}
		if(xmlStrcmp(tmpnode->name, "current_fwurl"))
			{
				fwurl=xmlNodeGetContent(tmpnode);
			}
		if(xmlStrcmp(tmpnode->name, "current_fwsize"))
			{
				fwsize=xmlNodeGetContent(tmpnode);
			}

		tmpnode=tmpnode->next;
		
	}


	/*处理*/

	free(fwsize);
	free(fwurl);
	free(fwvrs);
}


/*
	api39:用于按地区获取支持电话号码
	
	
*/

int Get_Support_Number()
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

