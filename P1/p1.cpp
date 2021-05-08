#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
	string ethernet_MAC, wireless_MAC;
	string ethernet_file = "/sys/class/net/eno1/address";
	string wireless_file = "/sys/class/net/wlo1/address";
	ifstream f1(ethernet_file);
	ifstream f2(wireless_file);
	f1 >> ethernet_MAC;
	f2 >> wireless_MAC;
	cout<<"Ethernet MAC address: "<<ethernet_MAC<<"\n";
	cout<<"Wireless MAC address: "<<wireless_MAC<<"\n";
	f1.close();
	f2.close();
	
	struct hostent* host_info;
	char host[100];
	char* ip_addr;
	gethostname(host, 100);
	host_info = gethostbyname(host);
	ip_addr = inet_ntoa(*((struct in_addr*) host_info->h_addr_list[0]));
	string hostname(host);
	string ip(ip_addr);
	cout<<"The hostname is: "<<hostname<<"\n";
	cout<<"The IP address is: "<<ip_addr<<"\n";
	return 0;
}
