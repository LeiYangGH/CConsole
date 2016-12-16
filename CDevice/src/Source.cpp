#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define STRING_FORMAT_3 "%s\t%s\t%s\r\n"
#define STRING_FORMAT_4 "%s\t%s\t%s\t%s\r\n"
#define STRING_DEVICEID "�豸���"
#define STRING_DEVICENAME "�豸����"
#define STRING_INSTOREFILE "instore.txt"
#define STRING_USERETURNFILE "usereturn.txt"
#define STRING_FIXFILE "fix.txt"
#define STRING_UPDATEFILE "update.txt"
#define MAX_STRLEN 20

char *modulenames[4] =
{
	"�豸���Ǽ�",
	"�豸������黹�Ǽ�",
	"�豸ά�޵Ǽ�",
	"�豸����Ǽ�"
};

//�ַ���ת����
int toint(char *s)
{
	char *end;
	return (int)strtol(s, &end, 10);
}

//������Ϣ
void inputstring(char str[], char* purpose)
{
	int len = -1;
	char input[50] = "";
	while (len < 1 || len > MAX_STRLEN)
	{
		printf("������%s��%d���ַ����ڣ����ܴ�Tab��س���:", purpose, MAX_STRLEN);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", input);
		len = strlen(input);
	}
	strcpy(str, input);
	printf("���� %s Ϊ %s \r\n", purpose, str);
}

////////�豸���Ǽ�--->/////////////////
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
	printf("����%d���������\r\n", allinstorescount);
	printf("--------------------------------------------\r\n");
	printf("�豸���\t�豸����\t���ʱ��\r\n");
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
		printf("\n���ļ�%sʧ��!", STRING_INSTOREFILE);
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
		printf("\n���ļ�%sʧ��!", STRING_INSTOREFILE);
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
	printf("�ѱ����¼���ļ�%s��", STRING_INSTOREFILE);
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
		printf("���ҵ��������\r\n");
		printf("--------------------------------------------\r\n");
		displayinstore(allinstores[index]);
	}
	else
		printf("û�ҵ���¼:%s!\r\n", id);
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
		printf("id�Ѿ�����!\r\n");
	else
	{
		inputstring(name, STRING_DEVICENAME);
		if (getinstoreidexbyid(name) > 0)
			printf("name�Ѿ�����!\r\n");
		else
		{
			inputstring(time, "���ʱ��");
			addinstore(id, name, time);
			printf("��ɵ�%d�����¼��!\r\n", allinstorescount);
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
		printf("ɾ����ϣ�ʣ��%d����\r\n", allinstorescount);
	}
	else
		printf("û�ҵ������id��Ӧ�ļ�¼\r\n", allinstorescount);
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
	printf("����ʾ����¼��Ϣ...");
	fp = fopen(STRING_INSTOREFILE, "wb");
	if (fp == NULL)
		printf("\n���ļ�%sʧ��!", STRING_INSTOREFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26���");
		fprintf(fp, STRING_FORMAT_3, "002", "����", "���� �������");
		fclose(fp);
		printf("ʾ����¼��Ϣ�Ѵ�����");
	}
}

////////<---�豸���Ǽ�/////////////////
#pragma endregion instore


#pragma region usereturn
////////�豸������黹�Ǽ�--->/////////////////
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
	printf("����%d�����ú͹黹����\r\n", allusereturnscount);
	printf("--------------------------------------------\r\n");
	printf("�豸���\t�豸����\t����ʱ��\t�黹ʱ��\r\n");
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
		printf("\n���ļ�%sʧ��!", STRING_USERETURNFILE);
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
		printf("\n���ļ�%sʧ��!", STRING_USERETURNFILE);
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
	printf("�ѱ����¼���ļ���");
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
		printf("���ҵ���¼��Ϣ����\r\n");
		printf("--------------------------------------------\r\n");
		displayusereturn(allusereturns[index]);
	}
	else
		printf("û�ҵ���¼:%s!\r\n", id);
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
		printf("%s��û��ⲻ����!\r\n", name);
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
		printf("�Ѿ����ù�����������!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(timeuse, "����ʱ��");
			inputstring(timeusereturn, "�黹ʱ��");
			addusereturn(id, allinstores[instoreidex].name, timeuse, timeusereturn);
			printf("��ɵ�%d���豸���ú͹黹�Ǽ�!\r\n", allusereturnscount);
		}
		else
			printf("��û��ⲻ�����û�黹!\r\n");
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
		printf("ɾ����ϣ�ʣ��%d����\r\n", allusereturnscount);
	}
	else
		printf("û�ҵ������id��Ӧ�ļ�¼\r\n", allusereturnscount);
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
	printf("����ʾ����¼��Ϣ...");
	fp = fopen(STRING_USERETURNFILE, "wb");
	if (fp == NULL)
		printf("\n���ļ�%sʧ��!", STRING_USERETURNFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_4, "001", "CPU", "2016-09-26��", "2016-09-27��");
		fprintf(fp, STRING_FORMAT_4, "002", "����", "���� ���ս�", "���� �ܶ���");
		fclose(fp);
		printf("ʾ����¼��Ϣ�Ѵ�����");
	}
}
////////<---�豸������黹�Ǽ�/////////////////
#pragma endregion


////////�豸ά�޵Ǽ�--->/////////////////
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
	printf("����%d�������Ϣ����\r\n", allfixescount);
	printf("--------------------------------------------\r\n");
	printf("�豸���\t�豸����\t���ʱ��\r\n");
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
		printf("\n���ļ�%sʧ��!", STRING_FIXFILE);
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
		printf("\n���ļ�%sʧ��!", STRING_FIXFILE);
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
	printf("�ѱ����¼���ļ���");
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
		printf("���ҵ���¼��Ϣ����\r\n");
		printf("--------------------------------------------\r\n");
		displayfix(allfixes[index]);
	}
	else
		printf("û�ҵ���¼:%s!\r\n", id);
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
		printf("%s��û��ⲻ����!\r\n", name);
}

void promptaddfix()
{
	int instoreidex;
	char id[MAX_STRLEN] = "";
	char name[MAX_STRLEN] = "";
	char time[MAX_STRLEN] = "";
	inputstring(id, STRING_DEVICEID);
	if (getfixindexbyid(id) >= 0)
		printf("�Ѿ�ά�޹������ٱ��!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(time, "ά��ʱ��");
			addfix(id, allinstores[instoreidex].name, time);
			printf("��ɵ�%d���豸ά�޵Ǽ�!\r\n", allfixescount);
		}
		else
			printf("��û��ⲻ��ά��!\r\n");
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
		printf("ɾ����ϣ�ʣ��%d����\r\n", allfixescount);
	}
	else
		printf("û�ҵ������id��Ӧ�ļ�¼\r\n", allfixescount);
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
	printf("����ʾ����¼��Ϣ...");
	fp = fopen(STRING_FIXFILE, "wb");
	if (fp == NULL)
		printf("\n���ļ�%sʧ��!", STRING_FIXFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26ά��");
		fprintf(fp, STRING_FORMAT_3, "002", "����", "����ά��");
		fclose(fp);
		printf("ʾ����¼��Ϣ�Ѵ�����");
	}
}
////////<---�豸ά�޵Ǽ�/////////////////
#pragma endregion fix


#pragma endregion
////////�豸����Ǽ�--->/////////////////
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
	printf("����%d����¼��Ϣ����\r\n", allupdatescount);
	printf("--------------------------------------------\r\n");
	printf("�豸���\t�豸����\t���ʱ��\r\n");
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
		printf("\n���ļ�%sʧ��!", STRING_UPDATEFILE);
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
		printf("\n���ļ�%sʧ��!", STRING_UPDATEFILE);
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
	printf("�ѱ����¼���ļ���");
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
		printf("���ҵ��������\r\n");
		printf("--------------------------------------------\r\n");
		displayupdate(allupdates[index]);
	}
	else
		printf("û�ҵ���¼:%s!\r\n", id);
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
		printf("�Ѿ�����������ٱ��!\r\n");
	else
	{
		instoreidex = getinstoreidexbyid(id);
		if (instoreidex >= 0)
		{
			inputstring(time, "���ʱ��");
			addupdate(id, allinstores[instoreidex].name, time);
			printf("��ɵ�%d���豸����Ǽ�!\r\n", allupdatescount);
		}
		else
			printf("��û��ⲻ�ܱ��!\r\n");
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
		printf("ɾ����ϣ�ʣ��%d����\r\n", allupdatescount);
	}
	else
		printf("û�ҵ������id��Ӧ�ļ�¼--\r\n", allupdatescount);
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
	printf("����ʾ�������Ϣ...");
	fp = fopen(STRING_UPDATEFILE, "wb");
	if (fp == NULL)
		printf("\n���ļ�%sʧ��!", STRING_UPDATEFILE);
	else
	{
		fprintf(fp, STRING_FORMAT_3, "001", "CPU", "2016-09-26����");
		fprintf(fp, STRING_FORMAT_3, "002", "����", "�������");
		fclose(fp);
		printf("ʾ�������Ϣ�Ѵ�����");
	}
}

////////<---�豸ά�޵Ǽ�/////////////////
#pragma endregion update


////////�Ӳ˵�--->/////////////////
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
		printf("���ܴ�ʵ�֡�\r\n");
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
		printf("�޸Ĺ��ܴ�ʵ�֡�\r\n");
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
		printf("���ܴ�ʵ�֡�\r\n");
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
		printf("���ܴ�ʵ�֡�\r\n");
		break;
	}
}
////////<---�Ӳ˵�/////////////////


void showsubmenu(int moduleindex)
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |         %s          |", modulenames[moduleindex]);
		printf("\n\t          +---------------------------------+");
		printf("\n\t 1. ��ѯ");
		printf("\n\t 2. �޸�");
		printf("\n\t 3. ɾ��");
		printf("\n\t 4. ��ʾ");
		printf("\n\t 0. ����");
		printf("\n\n ��ѡ��: ");
		scanf("%1[01234]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			return;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			find(moduleindex);
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			add(moduleindex);
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			remove(moduleindex);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			showall(moduleindex);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
}

int main()
{
	int choice = -1;

	//�������������ʾ�����ݣ�ֻ��Ҫ����һ�Σ���Ȼ�����ٴ����л�������
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
		printf("\n\t�˵�(��������û������ʾ������������򰴻س�)");
		printf("\n\t          +---------------------------------+");
		printf("\n\t          |        �豸��Ϣ����ϵͳ          |");
		printf("\n\t          +---------------------------------+");
		printf("\n\n\t 1. %s", modulenames[0]);
		printf("\n\t 2. %s", modulenames[1]);
		printf("\n\t 3. %s", modulenames[2]);
		printf("\n\t 4. %s", modulenames[3]);
		printf("\n\t 0. �˳�");
		printf("\n\n ��ѡ��: ");
		scanf("%1[012345]d%*c", &choice);
		choice = getche();
		switch (choice)
		{
		case '0':
			exit(0);
			break;
		case '1':
			printf("\n\n��ѡ���� 1\n");
			showsubmenu(0);
			break;
		case '2':
			printf("\n\n��ѡ���� 2\n");
			showsubmenu(1);
			break;
		case '3':
			printf("\n\n��ѡ���� 3\n");
			showsubmenu(2);
			break;
		case '4':
			printf("\n\n��ѡ���� 4\n");
			showsubmenu(3);
			break;
		default:
			printf("\n\n������������ѡ\n");
			break;
		}
		getch();
	}
	system("pause");
	return 0;
}