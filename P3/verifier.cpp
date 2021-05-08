#include <iostream>
#include <string>
using namespace std;

string xorString(string a, string b)
{
	int n = b.length();
	string temp = "";
	for(int i = 1; i < n; i++)
	{
		if(a[i] == b[i])
			temp += '0';
		else
			temp += '1';
	}
	return temp;
}

bool verifier(string message, string polynomial)
{
	int index = polynomial.length();
	int n = message.length();
	string temp = message.substr(0, index);
	while(index < n)
	{
		if(temp[0] == '0')
			temp = xorString(string(index, '0'), temp) + message[index];
		else
			temp = xorString(polynomial, temp) + message[index];
		index++;
	}	
	if(temp[0] == '0')
		temp = xorString(string(index, '0'), temp);
	else
		temp = xorString(polynomial, temp);
	if(temp == string(polynomial.length() - 1, '0'))
		return true;
	else
		return false;
}

int main(int argc, char* argv[])
{
	if(argv[1] == "Error")
	{
		cout<<"Verfiying Error\n";
		exit(0);
	}
	string message(argv[1]);
	string polynomial(argv[2]);
	if(verifier(message, polynomial))
		cout<<"Correct\n";
	else
		cout<<"Incorrect\n";
	return 0;
}


