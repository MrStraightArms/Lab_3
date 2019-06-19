#include "../../Libraries/Classes/Calculator/Calculator.hpp"
#include <gtest/gtest.h>

TEST(Arifmetic, task_wish_mach_parentheses)
{
	Calculator calc;
	string test_str = "1+25*8/(18/5+1)-((18*5-9)/8)-(1+1)";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "32.3533");
}
TEST(Arifmetic, task_1)
{
	Calculator calc;
	string test_str = "(15/3 + 26*2 +(54/9)) - 2^2^2 +18/9/2";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "48");
}
TEST(Arifmetic, task_2)
{
	Calculator calc;
	string test_str = "18/3+2^3-1.52+48.6/3";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "28.68");
}
TEST(Arifmetic, MR_MW)
{
	Calculator calc;
	string test_str = "18/3+2^3-1.52+48.6/3";
	string result = calc.Calculate(test_str);
	result = calc.Calculate("MR");
	ASSERT_NO_THROW(calc.Calculate("MR"));
	result = calc.Calculate("MR + 10");
	ASSERT_NO_THROW(calc.Calculate("MR + 10"));
	ASSERT_EQ(result, "38.68");
}
TEST(Arifmetic, incorrect_input_much_points)
{
	Calculator calc;
	string test_str = "12..2+18";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}
TEST(Arifmetic, incorrect_operators)
{
	Calculator calc;
	string test_str = "28*-6";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}
TEST(Arifmetic, incorrect_parentheses)
{
	Calculator calc;
	string test_str = "1+(5*(5+6)";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}

int main(int argc, char **argv)
{	 
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}