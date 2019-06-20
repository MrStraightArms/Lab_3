#pragma once 
#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <iomanip>


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;


class Calculator
{

public:
	Calculator();
	~Calculator();

	template <typename T> string to_str(const T& t);
	string result_out;
	string First_priority(string in_str);
	string Second_priority(string in_str);
	string Calculate_second_priority(string in_str);
	string Third_priority(string in_str);
	string Fourth_priority(string in_str);
	string MR_MW_sqrt_functoin(string in_str);
	string Calc_sqrt(string in_str);
	vector<string> Find_sqrt(string in_str);
	void Testing_in_string(string in_str);

	string Calculate(string in_str);

	vector<string> String_sep(string in_str, char _operator);
	vector<string> String_sep_3_priority(string in_str, char _operator);
	vector<string> String_sep_4_priority(string in_str, char _operator);



	bool Not_a_number(string in_str);
	bool Is_1_priority(string in_str);
	bool Is_2_priority(string in_str);
	bool Is_thr_prior(string in_str);
	bool Is_4_prior(string in_str);
	bool Also_minus(string in_str);
	bool Is_sqrt(string in_str);

	vector<string> Get_1_priority(string in_str);
	//=====================================================   	 
	vector<string> MR_vector;
private:

};
