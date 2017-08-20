#include <limits.h>
#include "readstruct.h"
#include "gtest/gtest.h"
namespace {


TEST(ReadStructTest, Standard) {

student allstudents[20];
readallstudents("standard.txt",allstudents); 

EXPECT_EQ(29, allstudents[0].age);
EXPECT_EQ(34, allstudents[1].age);
EXPECT_STREQ("YLei", allstudents[0].name);
EXPECT_STREQ("Smile", allstudents[1].name);
}


TEST(ReadStructTest, Emtpyline) {

student allstudents[20];
readallstudents("emtpyline.txt",allstudents); 

EXPECT_EQ(29, allstudents[0].age);
EXPECT_EQ(34, allstudents[1].age);
EXPECT_STREQ("YLei", allstudents[0].name);
EXPECT_STREQ("Smile", allstudents[1].name);
}


TEST(ReadStructTest, Maxlen) {

student allstudents[20];
readallstudents("maxlen.txt",allstudents); 

EXPECT_EQ(29, allstudents[0].age);
EXPECT_EQ(34, allstudents[1].age);
EXPECT_STREQ("YLei123456789876543210", allstudents[0].name);
EXPECT_STREQ("Smile", allstudents[1].name);
}


}
