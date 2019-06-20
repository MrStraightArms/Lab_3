#include "../../Libraries/Classes/Calculator/Calculator.hpp"
#include <gtest/gtest.h>

Calculator calc;
TEST(Arifmetic, mod_10_3)
{
	
	string test_str = "10%3";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "1");
}
TEST(Arifmetic, mod_5_6__1_1)
{

	string test_str = "5.6%1.1";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "0.0999998");
}
TEST(Arifmetic, sqrt_144)
{

	string test_str = "sqrt(144)";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "12");
}

TEST(Arifmetic, sqrt_144_144)
{
	string test_str = "sqrt(144.144)";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "12.006");
}

TEST(Arifmetic, sqrt_primer)
{
	string test_str = "sqrt(20*5+44)*10";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "120");
}

TEST(Arifmetic, sqrt_primer_1)
{
	string test_str = " 10+sqrt(20*5+44)*10";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "130");
}

TEST(Arifmetic, sqrt_minus_1)
{
	string test_str = "sqrt(-1)";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}

TEST(Arifmetic, task_wish_mach_parentheses)
{
	string test_str = "1+25*8/(18/5+1)-((18*5-9)/8)-(1+1)";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "32.3533");
}

TEST(Arifmetic, task_1)
{
	string test_str = "(15/3 + 26*2 +(54/9))-2^2^2 +18/9/2";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "48");
}

TEST(Arifmetic, task_2)
{
	string test_str = "18/3+2^3-1.52+48.6/3";
	string result = calc.Calculate(test_str);
	ASSERT_NO_THROW(calc.Calculate(test_str));
	ASSERT_EQ(result, "28.68");
}

TEST(Arifmetic, MR_MW)
{
	string test_str = "18/3+2^3-1.52+48.6/3";
	string result = calc.Calculate(test_str);

	ASSERT_NO_THROW(calc.Calculate("MW"));
	ASSERT_NO_THROW(calc.Calculate("MR + 10"));
	ASSERT_EQ(calc.result_out, "38.68");
}

TEST(Arifmetic, incorrect_input_much_points)
{
	string test_str = "12..2+18";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}

TEST(Arifmetic, incorrect_operators)
{
	string test_str = "28*-6";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}

TEST(Arifmetic, incorrect_parentheses)
{
	string test_str = "1+(5*(5+6)";
	ASSERT_ANY_THROW(calc.Calculate(test_str));
}

int main(int argc, char **argv)
{	 
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}