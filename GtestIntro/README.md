
# 1.Install

```cmd
sudo apt-get install libgtest-dev

```
**安装成功之后文件**

* cmake 文件
    /lib/x86_64-linux-gnu/cmake/GTest/GTestTargets-none.cmake
    /lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake
    /lib/x86_64-linux-gnu/cmake/GTest/GTestTargets.cmake
    /lib/x86_64-linux-gnu/cmake/GTest/GTestConfigVersion.cmake
* gtest头文件
    /usr/include/gtest/gtest.h
* 静态库文件
    /lib/x86_64-linux-gnu/libgtest.a
    /lib/x86_64-linux-gnu/libgtest_main.a

* 使用gtest,需要在CMakeLists.txt加入
    find_package(GTest)

    add_executable(example_unittest example_unittest.cc)
    target_link_libraries(example_unittest GTest::gtest GTest::gtest_main)

需要区分的概念：

* Test: 单个测试用例
* TestSuite: 包含多个测试用例
* TestProgram: 包含多个TestSuite


# 2.测试


## 2.1 TEST

```c++
TEST(TestSuitName, TestName)
{
    ...Test Body...
}
```

## 2.2 EXPECT|ASSERT基本操作

GoogleTest 提供 EXPECT_* 和 ASSERT_* 两种类型的宏，用于判断代码是否按照预期执行。EXPECT 只产生普通错误，ASSERT 产生严重错误。

```c++

{ ASSERT | EXPECT }_EQ(v1, v2)	 // v1 == v2
{ ASSERT | EXPECT }_NE(v1, v2)	 // v1 != v2
{ ASSERT | EXPECT }_LT(v1, v2)	// v1 < v2
{ ASSERT | EXPECT }_LE(v1, v2)	// v1 <= v2
{ ASSERT | EXPECT }_GT(v1, v2)	// v1 > v2
{ ASSERT | EXPECT }_GE(v1, v2)	// v1 >= v2
{ ASSERT | EXPECT }_TRUE(condition)	// condition 为真
{ ASSERT | EXPECT }_FALSE(condition)	// condition 为假

```

EXPECT 和 ASSERT 两种宏，都支持 << 输出字符串 -- 失败时输出日志


## 2.3 字符串比较 

```c++

{ ASSERT | EXPECT }_STREQ(s1, s2)	//s1 == s2
{ ASSERT | EXPECT }_STRNE(s1, s2)	//s1 != s2
{ ASSERT | EXPECT }_STRCASEEQ(s1, s2)	//s1 == s2（忽略大小）
{ ASSERT | EXPECT }_STRCASENE(s1, s2)	//s1 != s2（忽略大小）

```
字符串比较需要用特殊的宏，不能直接使用ASSERT_EQ 不然比较的是对应的地址



## 2.4 浮点数比较

浮点数不能精确表示，直接比较会有 BUG，下面是用于判断浮点数是否相等的宏，只要 |val1 - val2| <= abs_error 便相等，前两个宏默认 abs_error = 4ULPs

```c++

{ ASSERT | EXPECT }_FLOAT_EQ(val1, val2)	//val1 == val2
{ ASSERT | EXPECT }_DOUBLE_EQ(val1, val2)	//val1 == val2
{ ASSERT | EXPECT }_NEAR(v1, v2, abs_error)	//val1 == val2

```

## 2.5自定义抛错和检错

### 2.5.1 抛错

当测试不可能出现的情况时，需要用到 ADD_FAILURE 或者 FAIL，主动触发一次失败。ADD_FAILURE 产生普通错误，FAIL 产生严重错误。比如在条件判断 if-else 或者 switch-case 可能会使用到。

```c++
void TestHelper(int i) 
{
  if (i > 0) 
  {
    SUCCEED();
  } else 
  {
    ADD_FAILURE() << "negative";
  }
}

```

### 2.5.2 检错

{ EXPECT | ASSERT }_NO_FATAL_FAILURE

EXPECT_NO_FATAL_FAILURE 可以判断测试代码是否有普通错误出现，可以结合 ADD_FAILURE 和 FAIL 使用

```c++
TEST(SimpleTest, Positive) { 
  EXPECT_NO_FATAL_FAILURE(TestHelper(1)); 
}

TEST(SimpleTest, Negative) { 
  EXPECT_NO_FATAL_FAILURE(TestHelper(-1)); 
}

```

### 2.5.3 检查程序终止错误

{ ASSERT | EXPECT }_DEATH

```c++
void TestHelper(int i) {
  int* ptr = nullptr;
  *ptr = i;
}

TEST(SimpleTest, Death) {
  EXPECT_DEATH(TestHelper(0), "");
}

```


## 2.6跳过测试用例

如果需要跳过某个测试用例，或者某种情况出现跳过执行，可以使用 GTEST_SKIP

```c++

TEST(SimpleTest, Skip) {
  GTEST_SKIP() << "Skip";
  ASSERT_EQ(0, 1) << "FAIL";
}

```


# 3.TEST_F/TEST_P复用测试代码

## 3.1 TEST_F

如果有测试代码需要在每个测试用例都执行，可以使用 TEST_F 编写。使用 TEST_F 之前，必须继承 testing::Test 类。SetUp 和 TearDown() 两个函数分别在测试用例开始前和测试用例结束时调用。

```c++
class SimpleTest : public testing::Test {
 protected:
  SimpleTest() { std::cout << __func__ << std::endl; }
  ~SimpleTest() { std::cout << __func__ << std::endl; }
  void SetUp() override { std::cout << __func__ << std::endl; }

  void TearDown() override { std::cout << __func__ << std::endl; }

  void DoSomething() { std::cout << __func__ << std::endl; }
};

TEST_F(SimpleTest, Empty) {
  std::cout << "begin\n";
  DoSomething();
  std::cout << "end\n";
}

TEST_F(SimpleTest, Empty2) {
  std::cout << "begin\n";
  DoSomething();
  std::cout << "end\n";
}

```








