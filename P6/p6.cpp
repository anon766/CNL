#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	string input;
	cout<<"Enter transmit power of network device: ";
	getline(cin, input);
	int index = input.find(" ");
	int value = stoi(input.substr(0, index));
	string unit = input.substr(index + 1);
	if(unit == "W")
	{
		cout<<10 * log10(value)<<" dBW\n";
		cout<<10 * log10(value * 1000)<<" dBm\n";
	}
	else if(unit == "dBW")
		cout<<pow(10, value/10)<<" W"<<endl;
	else
		cout<<pow(10, value/10)/1000<<" W"<<endl;
	return 0;
}
