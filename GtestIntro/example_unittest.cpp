#include <gtest/gtest.h>


/**
 * 注意TestSuit 和 Test的层次划分
*/


TEST(SimpleTest, Expect)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 2);
}

TEST(SimpleTest, Expect2)
{
    EXPECT_LT(2, 2) << "Failure";
    EXPECT_LE(2, 2);
    EXPECT_LT(2,2) << "Failure Again";
}

TEST(SimpleTest, Assert)
{
    ASSERT_GT(2, 1);
    ASSERT_GT(2, 2) << "FATAL";
    ASSERT_GE(1, 2) << "No Touch";
}


/**
 * 比较字符串内容的时候需要用特殊的宏
*/
TEST(SimpleTest, String)
{
    char str[] = "abc";
    char str2[] = "abc";
    char str3[] = "Abc";
    //ASSERT_EQ(str, str2);
    ASSERT_STREQ(str, str2);
    ASSERT_STRNE(str, str3);
    ASSERT_STRCASEEQ(str, str3);

}

/**
 * 浮点数进行比较的时候需要用特殊的宏，不然会出现精度问题
*/

TEST(SimpleTest, Float)
{
    double val1 = 1.2;
    double val2 = static_cast<double>(6) / 5;
    ASSERT_EQ(val1, val2);
    ASSERT_DOUBLE_EQ(val1, val2);
    
}

/**
 * ADD_FAILURE() / FAIL() / SUCCEED() 可以用来控制测试失败的时候的行为
 * ADD_FAILURE() 普通错误
 * FAIL() 严重错误
*/
void TestHelper(int i )
{
    if(i > 0)
    {
        SUCCEED();
    }
    else 
    {
        ADD_FAILURE() << "negative";
    }
}

TEST(SimpleTest, Fail)
{
    TestHelper(10);
}


/**
 * EXPECTE_NO_FATAL_FAILURE 可以用来判断测试代码是否有普通错误出现，可以结合 ADD_FAILURE
 * 和 FAIL 使用
*/

TEST(SimpleTest, Positve)
{
    EXPECT_NO_FATAL_FAILURE(TestHelper(1));
}

TEST(SimpleTest, Negative)
{
    EXPECT_NO_FATAL_FAILURE(TestHelper(-1));

}


/**
 * EXPECT_DEATH用于测试会失败的程序
*/

void TestHelper1(int i)
{
    int * ptr = nullptr;
    *ptr = i;
}

TEST(SimpleTest, Death)
{
    EXPECT_DEATH(TestHelper1(0), "");
}


/**
 * 如果需要跳过某个测试用例，或则某种情况出现跳过执行，可以使用GTEST_SKIP
*/

TEST(SimpleTest, Skip)
{
    GTEST_SKIP() << "skip";
    ASSERT_EQ(0, 1) << "Fail";
}


/**
 * TEST_F / TEST_P 复用测试代码
*/
class SimpleTest1 : public testing::Test
{
protected:
    SimpleTest1() { std::cout << __func__ << std::endl;}
    ~SimpleTest1(){std::cout << __func__ << std::endl;}
    void SetUp() override {std::cout << __func__ << std::endl; }

    void TearDown() override{std::cout << __func__ << std::endl; }

    void DoSomething() {std::cout << __func__ << std::endl;}
};


TEST_F(SimpleTest1, Empty)
{
    std::cout << "begin\n";
    DoSomething();
    std::cout << "end\n";
}


TEST_F(SimpleTest1, Empty2)
{
    std::cout << "begin\n";
    DoSomething();
    std::cout << "end\n";
}




class Simple
{
protected:
    friend class SimpleTest2;
    int counts() const { return 0;}
};

class SimpleTest2 : public testing::Test
{
protected:
    SimpleTest2 () = default;
    ~SimpleTest2() = default;
    void SetUp() override {}
    void TearDown() override {}
    int counts(const Simple & simple){ return simple.counts(); }
};

TEST_F(SimpleTest2, Empty3)
{
    Simple simple;
    int cnt = counts(simple);
    ASSERT_EQ(cnt, 0);
}

