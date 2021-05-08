#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		cout<<"Alter Error";
		exit(0);
	}
	int bitFlip = atoi(argv[1]);
	string message = argv[2];
	string polynomial = argv[3];
	message[bitFlip] = message[bitFlip] == '0' ? '1' : '0';
	cout<<message<<"\n";
	cout<<polynomial<<"\n";
	return 0;
}
