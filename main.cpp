#include "utf-8.h"
using namespace std;
int main(){
	//ASCII characters and unicode characters are same for english character
	cout<<"English Text\n";
	string s1 = "My name is Prashant";
	cout<<"Lenght of ASCII "<<s1.length()<<"\n";
	Unicode u1(s1);
	cout<<"Length of Unicde "<<u1.length()<<"\n";
	
	//But string library fails to recognize utf-8 characters
	cout<<"Now for Nepali\n";
	string s2 ="मेरो  नाम प्रशान्त हो ";
	cout<<"Lengh of Nepali using string library "<< s2.length()<<"\n";
	Unicode u2(s2);
	cout<<"Lengh of Nepali using utf-8 library "<<u2.length()<<"\n";

	//Problem with indexing
	 cout<<"Indexing unicode using string library\n";
	for(int i; i<s2.length();i++){
	    cout<<s2[i]<<" ";
	}
	cout << "\n";
	
	cout<<"Indexing using unicode library \n";
	for(int i; i<u2.length();i++){
	    cout<<u2[i]<<" ";
	}
	cout<<"\n";

}
