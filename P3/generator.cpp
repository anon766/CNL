#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool checkPolynomial(string polynomial)
{
	int k = polynomial.length();
	int even = 1;
	int sum = 0;
	for(auto it = polynomial.crbegin(); it != polynomial.crend(); ++it)
	{
		if(*it == '1')
		{
			if(even)
				sum += 1;
			else
				sum -= 1;
		}
		even *= -1;
	}
	if(sum != 0 && polynomial[k - 1] != '0')
		return true;
	else
		return false;
}

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

string generator(string message, string polynomial)
{
	int index = polynomial.length();
	string append = string(index - 1, '0');
	string messageAppend = message + append;
	int n = messageAppend.length();
	string temp = message.substr(0, index);
	while(index < n)
	{
		if(temp[0] == '0')
			temp = xorString(string(index, '0'), temp) + messageAppend[index];
		else
			temp = xorString(polynomial, temp) + messageAppend[index];
		index++;
	}	
	if(temp[0] == '0')
		temp = xorString(string(index, '0'), temp);
	else
		temp = xorString(polynomial, temp);
	message = message + temp;
	return message;
}

int main(int argc, char* argv[])
{
	ifstream input(argv[1]);
	string message, polynomial;
	input >> message;
	input >> polynomial;
	//cout<<"Enter message: ";
	//cin>>message;
	//cout<<"Enter polynomial: ";
	//cin>>polynomial;
	if(checkPolynomial(polynomial))
	{
		string encoded_message = generator(message, polynomial);
		cout<<encoded_message<<"\n";
		cout<<polynomial<<"\n";
	}
	else
		cout<<"Error\n";
	return 0;
}


