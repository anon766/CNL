#include <iostream>
#include <string>
#include <vector>
using namespace std;

int binToDec(string bin)
{
	int dec = 0;
	for(int i = 0; i < 8; i++)
		dec += (bin[7 - i] - 48) << i;
	return dec;
}

vector<int> ipToInt(string ip)
{
	vector<int> a(4);
	int index = 0;
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
		a[index] = stoi(octet);
		index++;
		i = j+1;
	} 
	return a;
}

string buildIp(vector<int> a)
{
	string ip = "";
	for(int i = 0; i < 3; i++)
		ip += to_string(a[i]) + '.';
	ip += to_string(a[3]);
	return ip;
}


int findNetworkByte(string cidr)
{
	int index;
	for(index = 0; index < cidr.length(); index++)
		if(cidr[index] == '/')
			break;
	return stoi(cidr.substr(index + 1));
}

string findip(string cidr)
{
	int index;
	for(index = 0; index < cidr.length(); index++)
		if(cidr[index] == '/')
			break;
	return cidr.substr(0, index);
}
	
string getSubnetMask(int networkByte)
{
	int q = networkByte / 8;
	int r = networkByte % 8;
	vector<int> a(4);
	for(int i = 0; i < q; i++)
		a[i] = 255;
	if(r)
		a[q] = binToDec(string(r, '1') + string(8 - r, '0'));
	string subnetMask = buildIp(a);
	return subnetMask;
}

string getNetworkAddress(string ipstr, string subnetMaskstr)
{
	vector<int> ip = ipToInt(ipstr);
	vector<int> subnetMask = ipToInt(subnetMaskstr);
	vector<int> networkAddress(4);
	for(int i = 0; i < 4; i++)
		networkAddress[i] = ip[i] & subnetMask[i];
	string networkip = buildIp(networkAddress);
	return networkip;
}

vector <string> getHostIpRange(string nAddr, int networkByte)
{
	vector<string> hostIpRange(2);
	vector<int> startingAddress = ipToInt(nAddr);
       	startingAddress[3]++;
	hostIpRange[0] = buildIp(startingAddress);
	int q = networkByte / 8;
	int r = networkByte % 8;
	vector<int> invertSubnetMask(4, 255);
	for(int i = 0; i < q; i++)
		invertSubnetMask[i] = 0;
	if(r)
		invertSubnetMask[q] = binToDec(string(r, '0') + string(8 - r, '1'));
	int hostByte = 32 - networkByte;
	q = hostByte / 8;
	r = hostByte % 8;
	vector<int> broadcastAddress = ipToInt(nAddr);
	for(int i = 0; i < 4; i++)
		broadcastAddress[i] |= invertSubnetMask[i];
	broadcastAddress[3]--;
	hostIpRange[1] = buildIp(broadcastAddress);
	if(broadcastAddress[3] < startingAddress[3])
		hostIpRange = {"Undefined", "Undefined"};
	return hostIpRange;	
}
int main()
{
	string cidr;
	cout<<"Enter IPv4 address in CIDR notation: ";
	cin>>cidr;
	int networkByte = findNetworkByte(cidr);
	string ip = findip(cidr);
	string subnetMask = getSubnetMask(networkByte);
	cout<<"Subnet Mask: "<<subnetMask<<"\n";
	string networkAddress = getNetworkAddress(ip, subnetMask);
	cout<<"Network Address: "<<networkAddress<<"\n";	
	vector<string> hostIpRange = getHostIpRange(networkAddress, networkByte);
	cout<<"Starting IP: "<<hostIpRange[0]<<"\n";
	cout<<"Ending IP: "<<hostIpRange[1]<<"\n";
	return 0;
}
