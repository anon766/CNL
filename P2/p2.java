import java.io.*;
import java.net.*;
import java.lang.Math;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;
  
class Ping
{
	public static void ping(String ip) throws UnknownHostException, IOException
	{
    		InetAddress address = InetAddress.getByName(ip);
    		double times[] = new double[5];
		boolean flag = false;
		double sum = 0, avg = 0, max = 0, min = 6000, std = 0;
		for(int i = 0; i < 5; i++)
		{
			System.out.print("Pinging " + ip);
			double start = System.nanoTime();
    			if (address.isReachable(5000))
     				System.out.print(". Reachable");
    			else
      			{
				System.out.println(". Time exceeded. TTL = 5000 ms");
    				flag = true;
				continue;
			}
			double end = System.nanoTime();
			double elapsed = (end - start)/1000000;
			if(elapsed > max)
				max = elapsed;
			else if(elapsed < min)
				min = elapsed;
			sum += elapsed;
			times[i] = elapsed;
			System.out.println(". Time elapsed: " + elapsed + " ms");
		}
		if(!flag)
		{
			avg = sum/5;
			sum = 0;
			avg = BigDecimal.valueOf(avg).setScale(6, RoundingMode.HALF_UP).doubleValue();
			for(int i = 0; i < 5; i++)
				sum += Math.pow(times[i] - sum, 2);
			sum = sum/5;
			std = Math.sqrt(sum);
			std = BigDecimal.valueOf(std).setScale(6, RoundingMode.HALF_UP).doubleValue();
			System.out.println("5 packets sent, 5 packets received");
			System.out.println("min: " + min + " ms, max: " + max + " ms, avg: " + avg + " ms, std: " + std + " ms");
		}
		else
			System.out.println("5 packets sent, 0 packets received");
	}
  
	public static void main(String[] args) throws UnknownHostException, IOException
  	{	
    		Scanner input = new Scanner(System.in);
		System.out.print("Enter IP address or hostname to be pinged: ");
		String ip = input.nextLine();
		ping(ip);
  	}
}
