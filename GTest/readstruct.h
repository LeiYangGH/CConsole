#ifndef GTEST_READSTRUCT_H_
#define GTEST_READSTRUCT_H_
typedef struct student
{
	char name[20];
	int age;
}student;

//student allstudents[20];
//int allstudentscount;
void readallstudents(char* filename, student allstudents[20]);
#endif  // GTEST_SAMPLES_SAMPLE1_H_
