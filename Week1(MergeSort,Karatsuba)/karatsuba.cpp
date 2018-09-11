#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// using namespace std;
std::string karatsuba(std::string x, std::string y);
void half(std::string x, int digit, std::string* half);
// long singleMultiply(long x, long y);
std::string addon(std::string s1,std::string s2);
std::string substruct(std::string s1,std::string s2);
std::string multip(std::string s, char n);
std::string multiplyby(std::string s,int n);
std::string m2(std::string s1,std::string s2);
// int digitCounter(int x);

std::string karatsuba(std::string x, std::string y){

	// int l=x.length();
	// if(l<y.length())
	// l=y.length();
	// for(int i=x.length();i<l;i++)
	// x='0'+x;
	// for(int i=y.length();i<l;i++)
	// y='0'+y;

	long digit_x = x.length();
	long digit_y = y.length();
	std::string x_half[3];
	std::string y_half[3];

	//Base-case
	if (digit_x <= 1 || digit_y <= 1) {
		return m2(x, y);
		// std::stringstream ss;
		// ss << prod;
		// return ss.str();
	}

	//Recursive
	int digit = std::max(digit_x, digit_y);
	half(x, digit/2, x_half);
	half(y, digit/2, y_half);
	// std::cout << "x_half " << x_half[0] << " " << x_half[1] << " " << x_half[2] << " " << x_half[3] << std::endl;
	// std::cout << "y_half " << y_half[0] << " " << y_half[1] << " " << y_half[2] << " " << y_half[3]<< std::endl;

  	std::string z2 = karatsuba(x_half[0], y_half[0]);
	std::string z0 = karatsuba(x_half[1], y_half[1]);
	std::string z1 = karatsuba(x_half[2], y_half[2]);

	// std::cout << "z2=" << z2 << " z0=" << z0 << " z1=" << z1 << std::endl;

	std::string PowerDigit_half = "1";
	for (int i=0; i<digit/2; i++){
		PowerDigit_half = PowerDigit_half + "0";
	}
	std::string PowerDigit = "1";
	for (int i=0; i<digit; i++){
		PowerDigit = PowerDigit + "0";
	}
	// std::cout << "PowerDigit_half=" << PowerDigit_half << std::endl;
	// std::cout << "PowerDigit=" << PowerDigit << std::endl;
	// return "0";
	std::string z1_z2_z0 = substruct(substruct(z1, z0), z2);
	std::string z1_z2_z0_power = m2(z1_z2_z0, PowerDigit_half);
	std::string z2_power = m2(z2, PowerDigit);
	// std::cout << "z0:" << z0 << std::endl;
	// std::cout << "z1_z2_z0_power:" << z1_z2_z0_power << std::endl;
	// std::cout << "z2_power:" << z2_power << std::endl;

	std::string result = addon( addon(z2_power, z1_z2_z0_power), z0);
	return result;

}


void half(std::string x, int digit, std::string *half){
	//Divide the sting in to half
	std::string firsthalf(x.begin(), x.begin() + digit);
	std::string lasthalf(x.begin() + digit, x.end());
	half[0] = firsthalf;
	half[1] = lasthalf;
	std::string addon_half = addon(firsthalf, lasthalf);
	int l = addon_half.length();
	if(l != 1){
		if(l%2 != 0) {
			addon_half = '0'+addon_half;
		}
	}
	half[2] = addon_half;
	// std::cout << "addon_half:" << l%2 << std::endl;
	// std::cout << x * 100 << std::endl;
}

// long singleMultiply(long x, long y){
// 	//Base-case
// 	if (x == 0 || y == 0) return 0;
// 	//Recursive
// 	return x + singleMultiply(x, y-1);
// }

//to add to string
std::string addon(std::string s1,std::string s2){

	int l=s1.length();
	if(l<s2.length())
	l=s2.length();
	for(int i=s1.length();i<l;i++)
	s1='0'+s1;
	for(int i=s2.length();i<l;i++)
	s2='0'+s2;

	std::string s="";
	int sum=0,carry=0;
	for(int i=s1.length()-1;i>=0;i--){
		int sum=carry+s1[i]+s2[i]-'0'-'0';
		int x=sum%10;char t=x+'0';
		s=t+s;
		carry=sum/10;
	}
	while(carry){
		char v=carry%10+'0';
		s=v+s;
		carry/=10;
	}
	return s;
}

//to add to string
std::string substruct(std::string s1,std::string s2){

	int l=s1.length();
	if(l<s2.length())
	l=s2.length();
	for(int i=s1.length();i<l;i++)
	s1='0'+s1;
	for(int i=s2.length();i<l;i++)
	s2='0'+s2;


	std::string::reverse_iterator rit_1 = s1.rbegin();
	std::string::reverse_iterator rit_2 = s2.rbegin();
	std::string c;

	bool carry = false;
	while(rit_1 != s1.rend() && rit_2 != s2.rend())

	{
			int a1 = *rit_1 - '0';
			int b1 = *rit_2 - '0';

			if(carry)
			{
					b1 += 1;
			}

			if(a1 < b1)
			{
					a1 += 10;
					carry = true;
			}
			else
			{
					carry = false;
			}

			c += (a1 - b1) + '0';

			rit_1++;
	rit_2++;
	}

	if(rit_1 != s1.rend())
	{
			do
			{
					int a1 = *rit_1 - '0';
					int b1 = carry ? 1 : 0;
					if(a1 < b1)
					{
							a1 += 10;
							carry = true;
					}
					else
					{
							carry = false;
					}

					c += (a1 - b1) + '0';
					rit_1++;

			}while(rit_1 != s1.rend());
	}

	std::reverse(c.begin(), c.end());
	return c;
}

std::string multip(std::string s, char n){
	std::string sr="";int sum=0,carry=0;
	for(int i=s.length()-1;i>=0;i--){
		sum=((s[i]-'0')*(n-'0'))+carry;//cout<<sum<<endl;
		sr=char(sum%10+'0')+sr;
		carry=sum/10;
	}
	while(carry){
		sr=char(carry%10+'0')+sr;
		carry/=10;
	}
	return sr;
}
//to put 0 at the end of any multiplication in place of X in elementary algo.
std::string multiplyby(std::string s,int n){
	int t=s.length();
	for(int i=0;i<n;i++)
	s+="0";
	return s;
}


//main function to multily two string
std::string m2(std::string s1,std::string s2){
	//Setting the length to same.
	int l=s1.length();
	if(l<s2.length())
	l=s2.length();
	for(int i=s1.length();i<l;i++)
	s1='0'+s1;
	for(int i=s2.length();i<l;i++)
	s2='0'+s2;

	std::string s[l],sf;
	for(int i=0;i<l;i++){
		s[i]=multip(s1,s2[i]);
		s[i]=multiplyby(s[i],l-i-1);
		if(i>0){
			for(int j=s[i-1].length();j<s[i].length();j++)
			s[i-1]='0'+s[i-1];
			for(int j=s[i].length();j<s[i-1].length();j++)
			s[i]='0'+s[i];
		}
	}
	for(int i=sf.length();i<s[0].length();i++)
	sf='0'+sf;
	for(int i=0;i<l;i++){
		sf=addon(sf,s[i]);
	}
	bool flag=false; std::string srf="";
	for(int i=0;i<sf.length();i++){
		//to emit per zero of string
		if(sf[i]=='0'&&flag==false&&i!=sf.length()-1)continue;
		srf+=sf[i];
		flag=true;
	}
	return srf;
}

int main(){
	std::string x = "3141592653589793238462643383279502884197169399375105820974944592";
	std::string y = "2718281828459045235360287471352662497757247093699959574966967627";
	// std::string x = "4764";
	// std::string y = "8765";
	// std::cin >> x;
	// std::cin >> y;
	std::cout << "Multiply:  " << m2(x, y) << std::endl;
	// std::cout << "Addon:     " << addon(x, y) << std::endl;
	// std::cout << "Substruct: " << substruct(x, y) << std::endl;
	std::cout << "karatsuba: " << karatsuba(x, y) << std::endl;
	// std::cout << "len x:" << x.size() << std::endl;
	//std::cout << "first half:" << x_half[0] << "last half" << x_half[1] << std::endl;
	return 0;
}

// int digitCounter(std::string x){
// 	int count = 0;
// 	while(x){
// 		x=x/10;
// 		count++;
// 	}
// 	return count;
// }
