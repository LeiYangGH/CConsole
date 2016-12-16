#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define STRING_FORMAT_3 "%s\t%s\t%s\r\n"
#define STRING_FORMAT_4 "%s\t%s\t%s\t%s\r\n"
#define STRING_DEVICEID "设备序号"
#define STRING_DEVICENAME "设备名称"
#define STRING_INSTOREFILE "instore.txt"
#define STRING_USERETURNFILE "usereturn.txt"
#define STRING_FIXFILE "fix.txt"
#define STRING_UPDATEFILE "update.txt"
#define MAX_STRLEN 20

char *modulenames[4] =
{
	"设备入库登记",
	"设备领用与归还登记",
	"设备维修登记",
	"设备变更登记"
};

//字符串转整数
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//输入信息
void inputstring(char str[], char* purpose)
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("请输入%s，%d个字符以内，不能带Tab或回车符:", purpose, MAX_STRLEN);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("您的 %s 为 %s \r\n", purpose, str);
}

////////设备入库登记--->/////////////////
#pragma region instore
typedef struct instore
{
	char id[MAX_STRLEN];
	char name[MAX_STRLEN];
	char time[MAX_STRLEN];
}instore;

instore allinstores[50];
int allinstorescount = 0;

void displayinstore(instore rec)
{
	printf("\r\n");
	printf(STRING_FORMAT_3, rec.id, rec.name, rec.time);
}

void displayallinstores()
{
	int i;
	printf("所有%d条入库如下\r\n", allinstorescount);
	printf("--------------------------------------------\r\n");
	printf("设备序号\t设备名称\t入库时间\r\n");
	for (i = 0; i < allinstorescount; i++)
	{
		displayinstore(allinstores[i]);
	}
	printf("--------------------------------------------\r\n");
}

instore getinstorefromline(char *line)
{
	char *part;
	int index = 0;
	instore rec;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(rec.id, part);
			break;
		case 2:
			strcpy(rec.name, part);
			break;
		case 3:
			strcpy(rec.time, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return rec;
}

void readallinstores()
{
	char line[200];
	FILE *fp = fopen(STRING_INSTOREFILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_INSTOREFILE);
		getchar();
		exit(1);
	}
	allinstorescount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		++allinstorescount;
		allinstores[allinstorescount - 1] = getinstorefromline(line);
	}
}

void writeallinstores()
{
	FILE *fp = fopen(STRING_INSTOREFILE, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_INSTOREFILE);
		getchar();
		exit(1);
	}

	int i;
	instore rec;
	for (i = 0; i < allinstorescount; i++)
	{
		rec = allinstores[i];
		fprintf(fp, STRING_FORMAT_3, rec.id, rec.name, rec.time);
	}
	fclose(fp);
	printf("已保存记录到文件%s。", STRING_INSTOREFILE);
}

int getinstoreidexbyid(char *id)
{
	int i;
	int found = 0;
	for (i = 0; i < allinstorescount; i++)
	{
		instore b = allinstores[i];
		if (strcmp(b.id, id) == 0)
		{
			found = 1;
			return i;
		}
	}
	return -1;
}

void findinstorebyid(char *id)
{
	int index = getinstoreidexbyid(id);
	if (index >= 0)
	{
		printf("查找到入库如下\r\n");
		printf("--------------------------------------------\r\n");
		displayinstore(allinstores[index]);
	}
	else
		printf("没找到记录:%s!\r\n", id);
}

void promptfindinstore()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	findinstorebyid(id);
}

void addinstore(char id[], char name[], char time[])
{
	instore b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	strcpy(b.time, time);
	allinstores[allinstorescount++] = b;
	writeallinstores();
}

void promptaddinstore()
{
	char id[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char time[MAX_STRLEN] = "";
	inputstring(id, "STRING_DEVICEID");
	if (getinstoreidexbyid(id) > 0)
		printf("id已经存在!\r\n");
	else
	{
		inputstring(name, STRING_DEVICENAME);
		if (getinstoreidexbyid(name) > 0)
			printf("name已经存在!\r\n");
		else
		{
			inputstring(time, "入库时间");
			addinstore(id, name, time);
			printf("完成第%d个入库录入!\r\n", allinstorescount);
		}
	}
}

void removeinstore(char id[])
{
	int i;
	int index;
	index = getinstoreidexbyid(id);
	if (index >= 0)
	{
		if (index < allinstorescount - 1)
			for (i = index; i < allinstorescount - 1; i++)
				allinstores[i] = allinstores[i + 1];
		allinstorescount--;
		writeallinstores();
		printf("删除完毕，剩下%d个。\r\n", allinstorescount);
	}
	else
		printf("没找到输入的id对应的记录\r\n", allinstorescount);
}

void promptremoveinstore()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	removeinstore(id);
}

void createsampleinstores()
{
	FILE *fp;
	printf("创建示例记录信息...");
	fp = fopen(STRING_INSTOREFILE, "wb");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_INSTOREFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26入库");
		fprintf(fp, STRING_FORMAT_3, "002", "键盘", "昨天 周日入库");
		fclose(fp);
		printf("示例记录信息已创建。");
	}
}

////////<---设备入库登记/////////////////
#pragma endregion instore


#pragma region usereturn
////////设备领用与归还登记--->/////////////////
typedef struct usereturn
{
	char id[MAX_STRLEN];
	char name[MAX_STRLEN];
	char usetime[MAX_STRLEN];
	char returntime[MAX_STRLEN];
}usereturn;

usereturn allusereturns[50];
int allusereturnscount = 0;

void displayusereturn(usereturn rec)
{
	printf("\r\n");
	printf(STRING_FORMAT_4, rec.id, rec.name, rec.usetime, rec.returntime);
}

void displayallusereturns()
{
	int i;
	printf("所有%d条领用和归还如下\r\n", allusereturnscount);
	printf("--------------------------------------------\r\n");
	printf("设备序号\t设备名称\t领用时间\t归还时间\r\n");
	for (i = 0; i < allusereturnscount; i++)
	{
		displayusereturn(allusereturns[i]);
	}
	printf("--------------------------------------------\r\n");
}

usereturn getusereturnfromline(char *line)
{
	char *part;
	int index = 0;
	usereturn rec;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(rec.id, part);
			break;
		case 2:
			strcpy(rec.name, part);
			break;
		case 3:
			strcpy(rec.usetime, part);
			break;
		case 4:
			strcpy(rec.returntime, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return rec;
}

void readallusereturns()
{
	char line[200];
	FILE *fp = fopen(STRING_USERETURNFILE, "r");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_USERETURNFILE);
		getchar();
		exit(1);
	}
	allusereturnscount = 0;

	while (fgets(line, 1024, fp) != NULL)
	{
		if (strlen(line) < 5)
			continue;
		++allusereturnscount;
		allusereturns[allusereturnscount - 1] = getusereturnfromline(line);
	}
}

void writeallusereturns()
{
	FILE *fp = fopen(STRING_USERETURNFILE, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_USERETURNFILE);
		getchar();
		exit(1);
	}

	int i;
	usereturn rec;
	for (i = 0; i < allusereturnscount; i++)
	{
		rec = allusereturns[i];
		fprintf(fp, STRING_FORMAT_4, rec.id, rec.name, rec.usetime, rec.returntime);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

int getusereturnidexbyid(char *id)
{
	int i;
	int found = 0;
	for (i = 0; i < allusereturnscount; i++)
	{
		usereturn b = allusereturns[i];
		if (strcmp(b.id, id) == 0)
		{
			found = 1;
			return i;
		}
	}
	return -1;
}

void findusereturnbyid(char *id)
{
	int index;
	index = getusereturnidexbyid(id);
	if (index >= 0)
	{
		printf("查找到记录信息如下\r\n");
		printf("--------------------------------------------\r\n");
		displayusereturn(allusereturns[index]);
	}
	else
		printf("没找到记录:%s!\r\n", id);
}

void promptfindusereturn()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	findusereturnbyid(id);
}

void addusereturn(char id[], char name[], char usetime[], char returntime[])
{
	usereturn b;
	int index;
	index = getusereturnidexbyid(id);
	if (index >= 0)
	{
		strcpy(b.id, id);
		strcpy(b.name, name);
		strcpy(b.usetime, usetime);
		strcpy(b.returntime, returntime);
		allusereturns[allusereturnscount++] = b;
		writeallusereturns();
	}
	else
		printf("%s还没入库不能用!\r\n", name);
}

void promptaddusereturn()
{
	int instoreidex;
	char id[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char timeuse[MAX_STRLEN] = "";
	char timeusereturn[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	if (getusereturnidexbyid(id) >= 0)
		printf("已经领用过不能再领用!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(timeuse, "领用时间");
			inputstring(timeusereturn, "归还时间");
			addusereturn(id, allinstores[instoreidex].name, timeuse, timeusereturn);
			printf("完成第%d个设备领用和归还登记!\r\n", allusereturnscount);
		}
		else
			printf("还没入库不能领用或归还!\r\n");
	}
}

void removeusereturn(char id[])
{
	int i;
	int index;
	index = getusereturnidexbyid(id);
	if (index >= 0)
	{
		if (index < allusereturnscount - 1)
			for (i = index; i < allusereturnscount - 1; i++)
				allusereturns[i] = allusereturns[i + 1];
		allusereturnscount--;
		writeallusereturns();
		printf("删除完毕，剩下%d个。\r\n", allusereturnscount);
	}
	else
		printf("没找到输入的id对应的记录\r\n", allusereturnscount);
}

void promptremoveusereturn()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	removeusereturn(id);
}

void createsampleusereturns()
{
	FILE *fp;
	printf("创建示例记录信息...");
	fp = fopen(STRING_USERETURNFILE, "wb");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_USERETURNFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_4, "001", "CPU", "2016-09-26借", "2016-09-27还");
		fprintf(fp, STRING_FORMAT_4, "002", "键盘", "昨天 周日借", "明天 周二还");
		fclose(fp);
		printf("示例记录信息已创建。");
	}
}
////////<---设备领用与归还登记/////////////////
#pragma endregion


////////设备维修登记--->/////////////////
#pragma region fix
typedef struct fix
{
	char id[MAX_STRLEN];
	char name[MAX_STRLEN];
	char time[MAX_STRLEN];
}fix;

fix allfixes[50];
int allfixescount = 0;

void displayfix(fix rec)
{
	printf("\r\n");
	printf(STRING_FORMAT_3, rec.id, rec.name, rec.time);
}

void displayallfixes()
{
	int i;
	printf("所有%d条变更信息如下\r\n", allfixescount);
	printf("--------------------------------------------\r\n");
	printf("设备序号\t设备名称\t变更时间\r\n");
	for (i = 0; i < allfixescount; i++)
	{
		displayfix(allfixes[i]);
	}
	printf("--------------------------------------------\r\n");
}

fix getfixfromline(char *line)
{
	char *part;
	int index = 0;
	fix rec;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(rec.id, part);
			break;
		case 2:
			strcpy(rec.name, part);
			break;
		case 3:
			strcpy(rec.time, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return rec;
}

void readallfixes()
{
	char line[200];
	FILE *fp = fopen(STRING_FIXFILE, "r");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_FIXFILE);
	else
	{
		allfixescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allfixescount;
			allfixes[allfixescount - 1] = getfixfromline(line);
		}
	}
}

void writeallfixes()
{
	FILE *fp = fopen(STRING_FIXFILE, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_FIXFILE);
		getchar();
		exit(1);
	}

	int i;
	fix rec;
	for (i = 0; i < allfixescount; i++)
	{
		rec = allfixes[i];
		fprintf(fp, STRING_FORMAT_3, rec.id, rec.name, rec.time);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

int getfixindexbyid(char *id)
{
	int i;
	int found = 0;
	for (i = 0; i < allfixescount; i++)
	{
		fix b = allfixes[i];
		if (strcmp(b.id, id) == 0)
		{
			found = 1;
			return i;
		}
	}
	return -1;
}

void findfixbyid(char *id)
{
	int index = getfixindexbyid(id);
	if (index >= 0)
	{
		printf("查找到记录信息如下\r\n");
		printf("--------------------------------------------\r\n");
		displayfix(allfixes[index]);
	}
	else
		printf("没找到记录:%s!\r\n", id);
}

void promptfindfix()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	findfixbyid(id);
}

void addfix(char id[], char name[], char time[])
{
	fix b;
	int index;
	index = getfixindexbyid(id);
	if (index >= 0)
	{
		fix b;
		strcpy(b.id, id);
		strcpy(b.name, name);
		strcpy(b.time, time);
		allfixes[allfixescount++] = b;
		writeallfixes();
	}
	else
		printf("%s还没入库不能用!\r\n", name);
}

void promptaddfix()
{
	int instoreidex;
	char id[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char time[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	if (getfixindexbyid(id) >= 0)
		printf("已经维修过不能再变更!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(time, "维修时间");
			addfix(id, allinstores[instoreidex].name, time);
			printf("完成第%d个设备维修登记!\r\n", allfixescount);
		}
		else
			printf("还没入库不能维修!\r\n");
	}
}

void removefix(char id[])
{
	int i;
	int index;
	index = getfixindexbyid(id);
	if (index >= 0)
	{
		if (index < allfixescount - 1)
			for (i = index; i < allfixescount - 1; i++)
				allfixes[i] = allfixes[i + 1];
		allfixescount--;
		writeallfixes();
		printf("删除完毕，剩下%d个。\r\n", allfixescount);
	}
	else
		printf("没找到输入的id对应的记录\r\n", allfixescount);
}

void promptremovefix()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	removefix(id);
}

void createsamplefixes()
{
	FILE *fp;
	printf("创建示例记录信息...");
	fp = fopen(STRING_FIXFILE, "wb");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_FIXFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26维修");
		fprintf(fp, STRING_FORMAT_3, "002", "键盘", "昨天维修");
		fclose(fp);
		printf("示例记录信息已创建。");
	}
}
////////<---设备维修登记/////////////////
#pragma endregion fix


#pragma endregion
////////设备变更登记--->/////////////////
#pragma region update



typedef struct update
{
	char id[MAX_STRLEN];
	char name[MAX_STRLEN];
	char time[MAX_STRLEN];
}update;

update allupdates[50];
int allupdatescount = 0;

void displayupdate(update rec)
{
	printf("\r\n");
	printf(STRING_FORMAT_3, rec.id, rec.name, rec.time);
}

void displayallupdates()
{
	int i;
	printf("所有%d条记录信息如下\r\n", allupdatescount);
	printf("--------------------------------------------\r\n");
	printf("设备序号\t设备名称\t变更时间\r\n");
	for (i = 0; i < allupdatescount; i++)
	{
		displayupdate(allupdates[i]);
	}
	printf("--------------------------------------------\r\n");
}

update getupdatefromline(char *line)
{
	char *part;
	int index = 0;
	update rec;
	part = strtok(line, "\t");
	while (part != NULL)
	{
		switch (++index)
		{
		case 1:
			strcpy(rec.id, part);
			break;
		case 2:
			strcpy(rec.name, part);
			break;
		case 3:
			strcpy(rec.time, part);
			break;
		default:
			break;
		}
		part = strtok(NULL, "\t");
	}
	return rec;
}

void readallupdates()
{
	char line[200];
	FILE *fp = fopen(STRING_UPDATEFILE, "r");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_UPDATEFILE);
	else
	{
		allupdatescount = 0;

		while (fgets(line, 1024, fp) != NULL)
		{
			if (strlen(line) < 5)
				continue;
			++allupdatescount;
			allupdates[allupdatescount - 1] = getupdatefromline(line);
		}
	}
}

void writeallupdates()
{
	FILE *fp = fopen(STRING_UPDATEFILE, "wb");
	if (fp == NULL)
	{
		printf("\n打开文件%s失败!", STRING_UPDATEFILE);
		getchar();
		exit(1);
	}

	int i;
	update rec;
	for (i = 0; i < allupdatescount; i++)
	{
		rec = allupdates[i];
		fprintf(fp, STRING_FORMAT_3, rec.id, rec.name, rec.time);
	}
	fclose(fp);
	printf("已保存记录到文件。");
}

int getupdateidexbyid(char *id)
{
	int i;
	int found = 0;
	for (i = 0; i < allupdatescount; i++)
	{
		update b = allupdates[i];
		if (strcmp(b.id, id) == 0)
		{
			found = 1;
			return i;
		}
	}
	return -1;
}

void findupdatebyid(char *id)
{
	int index = getupdateidexbyid(id);
	if (index >= 0)
	{
		printf("查找到变更如下\r\n");
		printf("--------------------------------------------\r\n");
		displayupdate(allupdates[index]);
	}
	else
		printf("没找到记录:%s!\r\n", id);
}

void promptfindupdate()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	findupdatebyid(id);
}

void addupdate(char id[], char name[], char time[])
{
	update b;
	strcpy(b.id, id);
	strcpy(b.name, name);
	strcpy(b.time, time);
	allupdates[allupdatescount++] = b;
	writeallupdates();
}

void promptaddupdate()
{
	int instoreidex;
	char id[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char time[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	if (getupdateidexbyid(id) >= 0)
		printf("已经变更过不能再变更!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(time, "入库时间");
			addupdate(id, allinstores[instoreidex].name, time);
			printf("完成第%d个设备变更登记!\r\n", allupdatescount);
		}
		else
			printf("还没入库不能变更!\r\n");
	}
}

void removeupdate(char id[])
{
	int i;
	int index;
	index = getupdateidexbyid(id);
	if (index >= 0)
	{
		if (index < allupdatescount - 1)
			for (i = index; i < allupdatescount - 1; i++)
				allupdates[i] = allupdates[i + 1];
		allupdatescount--;
		writeallupdates();
		printf("删除完毕，剩下%d个。\r\n", allupdatescount);
	}
	else
		printf("没找到输入的id对应的记录--\r\n", allupdatescount);
}

void promptremoveupdate()
{
	char id[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	removeupdate(id);
}

void createsampleupdates()
{
	FILE *fp;
	printf("创建示例变更信息...");
	fp = fopen(STRING_UPDATEFILE, "wb");
	if (fp == NULL)
		printf("\n打开文件%s失败!", STRING_UPDATEFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26更新");
		fprintf(fp, STRING_FORMAT_3, "002", "键盘", "昨天更新");
		fclose(fp);
		printf("示例变更信息已创建。");
	}
}

////////<---设备维修登记/////////////////
#pragma endregion update


////////子菜单--->/////////////////
void add(int moduleindex)
{
	switch (moduleindex)
	{
	case 0:
		promptaddinstore();
		break;
	case 1:
		promptaddusereturn();
		break;
	case 2:
		promptaddfix();
		break;
	case 3:
		promptaddupdate();
		break;
	default:
		printf("功能待实现。\r\n");
		break;
	}
}

void remove(int moduleindex)
{
	switch (moduleindex)
	{
	case 0:
		promptremoveinstore();
		break;
	case 1:
		promptremoveusereturn();
		break;
	case 2:
		promptremovefix();
		break;
	case 3:
		promptremoveupdate();
		break;
	default:
		printf("修改功能待实现。\r\n");
		break;
	}
}

void find(int moduleindex)
{

	switch (moduleindex)
	{
	case 0:
		promptfindinstore();
		break;
	case 1:
		promptfindusereturn();
		break;
	case 2:
		promptfindfix();
		break;
	case 3:
		promptfindupdate();
		break;
	default:
		printf("功能待实现。\r\n");
		break;
	}
}

void showall(int moduleindex)
{
	switch (moduleindex)
	{
	case 0:
		displayallinstores();
		break;
	case 1:
		displayallusereturns();
		break;
	case 2:
		displayallfixes();
		break;
	case 3:
		displayallupdates();
		break;
	default:
		printf("功能待实现。\r\n");
		break;
	}
}
////////<---子菜单/////////////////


void showsubmenu(int moduleindex)
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |         %s          |", modulenames[moduleindex]);
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. 查询");
		printf("\n\t 2. 修改");
		printf("\n\t 3. 删除");
		printf("\n\t 4. 显示");
		printf("\n\t 0. 返回");
		printf("\n\n 请选择: ");
		scanf("%1[01234]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			return;
		case '1':
			printf("\n\n你选择了 1\n");
			find(moduleindex);
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			add(moduleindex);
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			remove(moduleindex);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			showall(moduleindex);
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
}

int main()
{
	int choice = -1;

	//下面这句是生成示例数据，只需要运行一次，不然后面再次运行会冲掉数据
	//createsampleinstores();
	//createsampleusereturns();
	//createsamplefixes();
	//createsampleupdates();
	readallinstores();
	readallusereturns();
	readallfixes();
	readallupdates();
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t菜单(如果输入后没立即显示，请重新输入或按回车)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        设备信息管理系统          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\n\t 1. %s", modulenames[0]);
		printf("\n\t 2. %s", modulenames[1]);
		printf("\n\t 3. %s", modulenames[2]);
		printf("\n\t 4. %s", modulenames[3]);
		printf("\n\t 0. 退出");
		printf("\n\n 请选择: ");
		scanf("%1[012345]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n你选择了 1\n");
			showsubmenu(0);
			break;
		case '2':
			printf("\n\n你选择了 2\n");
			showsubmenu(1);
			break;
		case '3':
			printf("\n\n你选择了 3\n");
			showsubmenu(2);
			break;
		case '4':
			printf("\n\n你选择了 4\n");
			showsubmenu(3);
			break;
		default:
			printf("\n\n输入有误，请重选\n");
			break;
		}
		getch();
	}
	system("pause");
	return 0;
}