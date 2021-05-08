#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

void checkBounds(int a, int power)
{
	if(a >= pow(2, power))
		exit(0);
}

string decToBin(int a, int size)
{
	string bin(size, '0');
	for(int i = 0; i < size; i++)
		if(a & (1 << i))
			bin[size - i - 1] = '1';
	return bin;	
}

string binToHex(string bin)
{
	string res = "";
	for(int i = bin.length() - 1; i >= 0; i-=4)
	{
		string temp = bin.substr(i - 3, 4);
		if(temp == "0000") res = "0" + res; 
		if(temp == "0001") res = "1" + res;  
		if(temp == "0010") res = "2" + res;  
		if(temp == "0011") res = "3" + res;  
		if(temp == "0100") res = "4" + res;  
		if(temp == "0101") res = "5" + res;  
		if(temp == "0110") res = "6" + res;  
		if(temp == "0111") res = "7" + res;  
		if(temp == "1000") res = "8" + res;  
		if(temp == "1001") res = "9" + res;  
		if(temp == "1010") res = "a" + res;  
		if(temp == "1011") res = "b" + res;  
		if(temp == "1100") res = "c" + res;  
		if(temp == "1101") res = "d" + res;  
		if(temp == "1110") res = "e" + res;  
		if(temp == "1111") res = "f" + res;  
	}
	return res;
}


int hexToDec(string a)
{
	int dec = 0;
	int n = a.length();
	for(int i = 0; i < n; i++)
	{
		if(a[n - 1 - i] >= 'a')
			dec += (a[n - 1 - i] - 87) * pow(16, i);
		else
			dec += (a[n - 1 - i] - 48) * pow(16, i);
	}
	return dec;
}

string ipToBin(string ip)
{
	string bin;
	for(int i = 0; i < ip.length();)
	{
		string octet = "";
		int j;
		for(j = i; j < ip.length(); j++)
		{
			if(ip[j] == '.')
				break;
			octet += ip[j];
		}
		bin += decToBin(stoi(octet), 8);
		i = j+1;
	} 	
	return bin;
}

int main()
{
	vector <int> value(11);
	string src, dest;
	cout<<"Enter version (4 bits) (int): ";
	cin>>value[0];
	checkBounds(value[0], 4);
	cout<<"Enter Internet Header Length (IHL) (4 bits) (int): ";
	cin>>value[1];
	checkBounds(value[1], 4);
	cout<<"Enter Differentiated Services Code Point (DSCP) (6 bits) (int): ";
	cin>>value[2];
	checkBounds(value[2], 6);
	cout<<"Enter Explicit Congestion Notification (ECN) (2 bits) (int): ";
	cin>>value[3];
	checkBounds(value[3], 2);
	cout<<"Enter total length of packet (16 bits) (int): ";
	cin>>value[4];
	checkBounds(value[4], 16);
	cout<<"Enter identification (16 bits) (int): ";
	cin>>value[5];
	checkBounds(value[5], 16);
	cout<<"Enter DF (1 bit) (int): ";
	cin>>value[6];
	checkBounds(value[6], 1);
	cout<<"Enter MF (1 bit) (int): ";
	cin>>value[7];
	checkBounds(value[7], 1);
	cout<<"Enter fragment offset (13 bits) (int): ";
	cin>>value[8];
	checkBounds(value[8], 13);
	cout<<"Enter time to live (TTL) (8 bits) (int): ";
	cin>>value[9];
	checkBounds(value[9], 8);
	cout<<"Enter protocol (8 bits) (int): ";
	cin>>value[10];
	checkBounds(value[10], 8);
	cout<<"Enter source address (32 bits) (dotted IP string): ";
	cin>>src;
	cout<<"Enter destination address (32 bits) (dotted IP string): ";
	cin>>dest;
	cout<<"\nIPv4 header checksum is calculated as one's complement sum of 16-bit words, So"
		<<" the fields are grouped up into 16-bits hex words as follows:\n";
	vector<string> hexString(9);
	string temp;
	cout<<"\nVersion(4) IHL(4) DSCP(6) ECN(2): ";
	temp = decToBin(value[0], 4) + decToBin(value[1], 4) + decToBin(value[2], 6) + decToBin(value[3], 2);
	hexString[0] = binToHex(temp);
	cout<<hexString[0]<<"\n";
	cout<<"Total length(16): ";
	temp = decToBin(value[4], 16);
	hexString[1] = binToHex(temp);
	cout<<hexString[1]<<"\n";
	cout<<"Identification(16): ";
	temp = decToBin(value[5], 16);
	hexString[2] = binToHex(temp);
	cout<<hexString[2]<<"\n";
	cout<<"Flags(3) Fragment offset(13): ";
	temp = "0" + decToBin(value[6], 1) + decToBin(value[7], 1) + decToBin(value[8], 13);
	hexString[3] = binToHex(temp);
	cout<<hexString[3]<<"\n";
	cout<<"TTL(8) Protocol(8): ";
	temp = decToBin(value[9], 8) + decToBin(value[10], 8);
	hexString[4] = binToHex(temp);
	cout<<hexString[4]<<"\n";
	cout<<"Source address (16 + 16): ";
	temp = ipToBin(src);
	temp = binToHex(temp);
	hexString[5] = temp.substr(0, 4);
	hexString[6] = temp.substr(4);
	cout<<hexString[5]<<" "<<hexString[6]<<"\n";
	cout<<"Destination address(16 + 16): ";
	temp = ipToBin(dest);
	temp = binToHex(temp);
	hexString[7] = temp.substr(0, 4);
	hexString[8] = temp.substr(4);
	cout<<hexString[7]<<" "<<hexString[8]<<"\n";
	cout<<"\nThe sum of all 16-bit words is: ";
	int sum = 0;
	for(int i = 0; i < 9; i++)
		sum += hexToDec(hexString[i]);
	string hexSum;
	if(sum >= pow(16,4))
		hexSum = binToHex(decToBin(sum, 20));
	else
		hexSum = binToHex(decToBin(sum, 16));
	cout<<hexSum<<"\n";
	if(sum >= pow(16,4))
	{
		cout<<"\nCarry bit: ";
		string carry = binToHex(decToBin(sum / pow(16,4), 4));
		cout<<carry<<"\n";
		cout<<"The sum: ";
		hexSum = hexSum.substr(1);
		cout<<hexSum<<"\n";
		cout<<"The extra carry bit is added to the sum: ";
		sum = sum/(int)pow(16,4) + sum % (int)pow(16,4);
		hexSum = binToHex(decToBin(sum, 16));
		cout<<hexSum<<"\n";
	}
	cout<<"\nThe final checksum is the one's complement of the sum: ";
	string hexChar = "0123456789abcdef";
	string checksum;
	for(int i = 0; i < 4; i++) 
		checksum += hexChar[15 - hexChar.find(hexSum[i])];
	cout<<checksum<<"\n";
	return 0;
}

