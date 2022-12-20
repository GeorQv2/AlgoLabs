#include <iostream>
#include <vector>
#include <random>

std::vector<std::string> split(std::string str) {
	std::vector<std::string> result;
	std::string temp = "";
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ',')
		{
			if (str[i] != ' ')
			{
				temp += str[i];
			}
		}
		else {
			result.push_back(temp);
			temp = "";
		}
	}
	result.push_back(temp);
	return result;
}

int DiceResult(std::string d) {
	std::string numOfThr = "", dValue = "", extraVal = "";
	char op = ' ';
	bool meetD = false;
	for (size_t i = 0; i < d.size(); i++)
	{
		if (d[i] != 'd' && !meetD)
		{
			numOfThr += d[i];
		}
		else if (d[i] == 'd') 
		{
			meetD = true;
		}
		else if (d[i] == '+' || d[i] == '-' || d[i] == '*') 
		{
			op = d[i];
		}
		else if (op == ' ')
		{
			dValue += d[i];
		}
		else 
		{
			extraVal += d[i];
		}
	}
	int result = 0, nT = 1, dVal = std::atoi(dValue.c_str());
	std::random_device dev;
	std::mt19937 rng(dev());
	if (numOfThr != "")
	{
		nT = std::atoi(numOfThr.c_str());
	}
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, dVal); // distribution in range [1, dVal]

	for (size_t i = 0; i < nT; i++)
	{
		result += dist6(rng);
	}

	switch (op)
	{
	case '+':
		result += std::atoi(extraVal.c_str());
		break;
	case '-':
		result -= std::atoi(extraVal.c_str());
		break;
	case '*':
		result *= std::atoi(extraVal.c_str());
		break;
	default:
		break;
	}
	return result;
}

int OverallResult(std::string dice) {
	int result = 0;
	std::vector<std::string> dieces = split(dice);
	for (size_t i = 0; i < dieces.size(); i++)
	{
		result += DiceResult(dieces[i]);
	}
	return result;
}

void printAll(const std::vector<std::string>& vec) {
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << i + 1<< ") " << vec[i] << std::endl;
	}
}

int main() {
	for (size_t i = 0; i < 3000; i++)
	{
		std::cout<< OverallResult("3d10")<< std::endl;
	}
}