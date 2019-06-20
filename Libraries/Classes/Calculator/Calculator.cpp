#include "Calculator.hpp"

Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}
bool Calculator::Is_sqrt(string in_str)
{
	string main = "sqrt(";
	bool res = (in_str.find(main) != string::npos) ? true : false;
	return res;
}


template <typename T> string Calculator::to_str(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

bool Calculator::Is_1_priority(string in_str)
{
	return ((in_str.find('(') != string::npos)
		|| (in_str.find(')') != string::npos)) ? true : false;
}

bool Calculator::Is_2_priority(string in_str) // Тру если строка не чесло а выражение
{
	return (in_str.find('^') != string::npos) ? true : false;
}

bool Calculator::Is_thr_prior(string in_str) // Тру если строка не чесло а выражение
{
	return ((in_str.find('*') != string::npos)
		|| (in_str.find('/') != string::npos)
		|| (in_str.find('^') != string::npos)) ? true : false;
}

bool Calculator::Is_4_prior(string in_str) // Тру если строка не чесло а выражение
{
	return ((in_str.find('+') != string::npos)
		|| (in_str.find('-') != string::npos)) ? true : false;
}

bool Calculator::Also_minus (string in_str) // Тру если строка не чесло а выражение
{
	return ((in_str.find('*') != string::npos)
		|| (in_str.find('/') != string::npos)
		|| (in_str.find('+') != string::npos)
		|| (in_str.find('%') != string::npos)
		|| (in_str.find('^') != string::npos)) ? false : true;
} 

bool Calculator::Not_a_number(string in_str) // Тру если строка не чесло а выражение
{
	return ((in_str.find('*') != string::npos)
		|| (in_str.find('/') != string::npos)
		|| (in_str.find('-') != string::npos)
		|| (in_str.find('+') != string::npos)
		|| (in_str.find('%') != string::npos)
		|| (in_str.find('^') != string::npos)) ? true : false;
}

vector<string> Calculator::Get_1_priority(string in_str)
{
	vector<string> work(3, "");
	size_t count = 0;

	for (size_t i = 0; i < in_str.size(); i++)
	{
		if (in_str[i] == '(')
		{
			count++;
			work[1].push_back(in_str[i]);
		}
		else if (in_str[i] == ')')
		{
			count--;
			work[1].push_back(in_str[i]);
			if (count == 0)
			{
				work[2] = in_str.substr(i + 1);
				break;
			}
		}
		else if (count > 0)
		{
			work[1].push_back(in_str[i]);
		}
		if (count == 0)
		{
			work[0].push_back(in_str[i]);
		}
	}
	work[1] = work[1].substr(1, work[1].size() - 2);
	return work;
}

string Calculator::First_priority(string in_str)
{
	string tmp_str = in_str;
	if (!Is_1_priority(in_str))
	{
		result_out = Fourth_priority(in_str);
		return result_out;
	}
	else 
	{
		vector<string> tmp = Get_1_priority(tmp_str);
		if (Is_1_priority(tmp[2]))
		{
		string result_out = tmp[0] + First_priority(tmp[1]) + First_priority(tmp[2]);
		return Fourth_priority(result_out);
		}
		else if (Is_1_priority(tmp[1]))
		{
			string result_out = tmp[0] + First_priority(tmp[1]) + tmp[2];
			return Fourth_priority(result_out);

		}		
		else
		{
			string result_out = Fourth_priority(tmp[0] + Fourth_priority(tmp[1]) + tmp[2]);
			return result_out;
		}
	}
}

vector<string> Calculator::Find_sqrt(string in_str)
{
	string main = "sqrt(", tmp;

	vector<string> out_vector;
	size_t pos = in_str.find_first_of(main), count = 1, num_in_sqrt = pos + 5;
	tmp = in_str.substr(0, pos);
	out_vector.push_back(tmp);
	tmp.clear();
	while (count > 0)
	{
		tmp.push_back(in_str[num_in_sqrt]);
		if (in_str[num_in_sqrt] == '(')
			count++;
		if (in_str[num_in_sqrt] == ')')
		{
			count--;
			if (count == 0)
			{
				out_vector.push_back(tmp.substr(0, tmp.size()-1));
				tmp.clear();
				tmp = in_str.substr(num_in_sqrt + 1);
				out_vector.push_back(tmp);
				break;
			}
		}
		num_in_sqrt++;

	}
	return out_vector;

}

string Calculator::Calc_sqrt(string in_str)
{
	string tmp_string = in_str;

	if (Is_sqrt(tmp_string))
	{	
		vector<string> work_vector = Find_sqrt(tmp_string);
		if (Is_sqrt(work_vector[2]) && Is_sqrt(work_vector[1]))
		{
			tmp_string = work_vector[0] + Calc_sqrt(work_vector[1]) + Calc_sqrt(work_vector[2]);
			return tmp_string;
		}
		else if (!Is_sqrt(work_vector[2]) && Is_sqrt(work_vector[1]))
		{
			tmp_string = work_vector[0] + Calc_sqrt(work_vector[1]) + work_vector[2];
			return tmp_string;
		}
		else if (Is_sqrt(work_vector[2]) && !Is_sqrt(work_vector[1]))
		{
			tmp_string = work_vector[0] + work_vector[1] + Calc_sqrt(work_vector[2]);
			return tmp_string;
		}
		else
		{
			tmp_string = First_priority(work_vector[1]);
			if (stod(tmp_string) >= 0)
			{
				tmp_string = work_vector[0] + to_str(pow(stod(tmp_string), 0.5)) + work_vector[2];
			}
			else
			{
				throw string("ОШИБКА: под корнем отрицательное число");
			}
			return tmp_string;
		}		
	}
	else
	{
		return First_priority(tmp_string);
	}

	
}

string Calculator::Fourth_priority(string in_str)
{
	string tmp_str = in_str, minus = "";
	vector<double> vec_nums;
	vector<char> vec_operators;
	size_t pos;
	while(tmp_str[0] == '-')
	{
		tmp_str = tmp_str.substr(1, tmp_str.size());

		size_t op = tmp_str.find_first_of("+-*/^%");
		if (!Not_a_number(tmp_str))
		{
			minus = '-';
		}
		else
		{
			char oper = tmp_str[op];
			switch (oper)
			{
				case '+':
				{
					tmp_str = tmp_str.substr(op + 1) + tmp_str.substr(0, op);
					break;
				}
				case '-':
				{
					if (Also_minus(tmp_str))
					{
						minus = '-';
						for (size_t i = 0; i < tmp_str.size(); i++)
						{
							if (tmp_str[i] == '-')
							{
								tmp_str[i] = '+';
							}

						}
					}
					else
					{
						tmp_str = tmp_str.substr(op) + tmp_str.substr(0, op);

					}
					break;
				}
				case '*':
				{
					tmp_str = tmp_str.substr(1);
					minus = '-';
					break;
				}
				case  '/':
				{
					tmp_str = tmp_str.substr(1);
					minus = '-';
					break;
				}
				case '%':
				{
					tmp_str = tmp_str.substr(1);
					minus = '-';
					break;
				}
				case '^':
				{
					tmp_str = tmp_str.substr(1);
					minus = '-';
					break;
				}
			}
		}			
	}		

	while (Is_4_prior(tmp_str))
	{
		pos = tmp_str.find_first_of("+-");
		vec_operators.push_back(tmp_str[pos]);
		vec_nums.push_back(stof(Third_priority(tmp_str.substr(0, pos))));
		tmp_str = tmp_str.substr(pos + 1);
	}
	vec_nums.push_back(stof(Third_priority(tmp_str)));
	double result = vec_nums[0];

	for (size_t i = 1; i < vec_nums.size(); i++)
		(vec_operators[i - 1] == '+') ? result += vec_nums[i] : result -= vec_nums[i];

	return minus + to_str(result);
}

string Calculator::Calculate_second_priority(string in_str) 
{
	char _operater = in_str[in_str.find_first_of("^")];// передаем в сепортатор
	vector<string> tmp_calc = String_sep(in_str, _operater); // Вектор с результатом разделения 
	if (Is_2_priority(tmp_calc[1]))
	{
		return to_str(pow(stof(tmp_calc[0]),stof(Calculate_second_priority(tmp_calc[1]))));
	}
	else
	{
		return to_str(pow(stof(tmp_calc[0]), stof(tmp_calc[1])));
	}
}

string Calculator::Second_priority(string in_str) // Самый высокий приоритет у вычисления степени, мы ее вычленяем из строки
{
	size_t pos_pow = in_str.find_first_of('^');
	size_t pos_no_pow = in_str.find_first_of("*/");
	if (!Is_2_priority(in_str))
	{
		return in_str;
	}
	else if (pos_no_pow == string::npos)
	{
		return Calculate_second_priority(in_str); // считаем степень
	}
	else if (pos_pow < pos_no_pow)
	{
		string str_befor = in_str.substr(0, pos_no_pow);
		string tmp = Calculate_second_priority(str_befor); // выделям подстроку тольк ос числами и занками степени и сразу их считаем
		return  tmp + in_str.substr(pos_no_pow); // конкатенация ризультата вычисления и остатка строки	
	}
	else if (pos_pow > pos_no_pow)
	{
		string str_befor = in_str.substr(0, pos_no_pow+1);
		string tmp = in_str.substr(pos_no_pow+1);
		string tmp_2 = str_befor + Second_priority(tmp);
		return tmp_2;

	}
}

string Calculator::Third_priority(string in_str)
{	

	if (Is_2_priority(in_str))
	{
		string tmp_2 = Third_priority(Second_priority(in_str));
		return tmp_2;

	}
	if (!Not_a_number(in_str))
	{
		return in_str;
	}
	char _operater = in_str[in_str.find_last_of("/%*")];// передаем в сепортатор
	vector<string> tmp_calc = String_sep_3_priority(in_str, _operater); // Вектор с результатом разделения 
	if (Not_a_number(tmp_calc[0]))
	{	
		switch (_operater)
		{
		case '*':
		{
			string tmp_2 = to_str(stof(Third_priority(tmp_calc[0])) * stof(tmp_calc[1]));
			return tmp_2;
			break;
		}
		case '/':
		{
			string tmp_2 = to_str(stof(Third_priority(tmp_calc[0])) / stof(tmp_calc[1]));
			return  tmp_2;
			break;
		}
		default:
			string tmp_2 = to_str(fmod(stof(Third_priority(tmp_calc[0])), stof(tmp_calc[1])));
			return  tmp_2;
			break;
		}
		
	}
	else
	{
		switch (_operater)
		{
		case '*':
		{
			string tmp_2 = to_str(stof(tmp_calc[0]) * stof(tmp_calc[1]));
			return  tmp_2;
			break;
		}
		case '/':
		{
			string tmp_2 = to_str(stof(tmp_calc[0]) / stof(tmp_calc[1]));
			return tmp_2;
			break;
		}
		default:
			string tmp_2 = to_str(fmod(stof(tmp_calc[0]), stof(tmp_calc[1])));
			return  tmp_2;
			break;
		}
	}
}

vector<string> Calculator::String_sep(string in_str, char _operator)
{
	vector<string> sep_strings;

	std::istringstream iss(in_str);
	string tmp_str;

	std::getline(iss, tmp_str, _operator);
	sep_strings.push_back(tmp_str);

	std::ostringstream os;
	os << iss.rdbuf();
	sep_strings.push_back(os.str());

	return sep_strings;
}

vector<string> Calculator::String_sep_3_priority(string in_str, char _operator)
{
	vector<string> sep_strings;

	size_t pos = in_str.find_last_of(_operator);
	sep_strings.push_back(in_str.substr(0, pos));
	sep_strings.push_back(in_str.substr(pos+1));
	
	return sep_strings;
}

vector<string> Calculator::String_sep_4_priority(string in_str, char _operator)
{
	vector<string> sep_strings;

	std::istringstream iss(in_str);
	string token;

	while (std::getline(iss, token, _operator))
	{
		sep_strings.push_back(token);
	}

	return sep_strings;
}

void Calculator::Testing_in_string(string in_str) 
{
	size_t n_points = 0, count = 0;
	for (size_t i = 0; i < in_str.size(); i++)
	{
		if (in_str[i] == '.' && n_points != 0)
		{
			throw string("Fractional error on position: ") + to_str(i + 1);
		}
		else if (in_str[i] == '.')
		{
			n_points++;
		}		
		else if (Not_a_number(to_str(in_str[i])))
		{
			if (Not_a_number(to_str(in_str[i + 1])))
			{
				throw string("Error in position operators:") + to_str(i + 1);
			}
			n_points = 0;
		}
		if (in_str[i] == '(')
		{
			count++;
		}
		if (in_str[i] == ')')
		{
			count--;
		}
		if ((i == in_str.size() - 1) && count!=0)
		{
			throw string("Error in placing brackets");
		}

	}
}

string Calculator::MR_MW_sqrt_functoin(string in_str)
{
	string tmp = in_str;
	if (tmp == "MW")
	{
		if (result_out == "")
		{
			throw string("Memory is clear");
		}
		else
		{
			MR_vector.push_back(result_out);
		}
	}
	else if (tmp.find("MR") != string::npos)
	{
		while (tmp.find("MR") != string::npos)
		{
			size_t pos = tmp.find("MR");
			tmp = tmp.substr(0, pos) + result_out + tmp.substr(pos + 2);
		}
	}

	if (Is_sqrt(tmp))
	{
		tmp = Calc_sqrt(tmp);
	}
	return tmp;
}

string Calculator::Calculate(string in_str)
{
	string result = MR_MW_sqrt_functoin(in_str);
	if (result != "MW")
	{
		Testing_in_string(result);
		result = First_priority(result);
		result_out = result;
	}
	return result_out;
}



