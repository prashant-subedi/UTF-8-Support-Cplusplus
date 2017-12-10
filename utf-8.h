/**
  *Written By: Prashant Subedi
  *For:The software-Nepali Conversion Tool
  *Description:
	*This header contains the definition of the structure Data and class Unicode.
	*See individual class and structure
  */
#ifndef UNICODE_H//header gaurd
#define UNICODE_H
#include<iostream>
#include<string>
#define EOU "**\n\0"
/*
 *End of Unicode was defined to mark....Well its pretty self explainatory isn't it?
*/
struct Char
{
	/**
	  *Data structure is used to store a single UTF-8 character.
	  */
	int position;//It stores the position, in terms of bytes from which the character begins in raw string. It was used while debugging but has no use in the main program.
    char utf_size;//It stores the size in bytes of the character..using char to save memory.
    std::string unicode_char;//It stores the character.
};
class Unicode
{

	/**
	 *Description:
	 *I built this because there is  no native support for the UTF-8 characters in C++.
	 *The input data is of type string
	 *It uses the fact that 1st byte every character in UTF-8 encoding starts with a bit combination which is same for all UTF-8 characters of same byte size but diffent from those of different byte size
	 *Also the bits after 1st byte(if there are any) also follow a specific format
		*1 byte=0XXXXXXX
		*2 byte=110XXXXX 10XXXXXX
		*3 byte=1110XXXX 10XXXXXX 10XXXXXX
		*4 byte=11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
	*Using the above fact the characters are seperated and stored as data type Data, defined above.
	 */
	private:
		/*
		 */
        int unicode_length;//Stores the number of UTF-8 characters stores
        std::string raw_data;//Stores the string input
        Char *single_utf8;//Pointer to processed data and its info
        void scan_RawInput();
        
	public:
		Unicode(std::string s);
		~Unicode();

        std::string operator[](int i);
		void operator=(std::string);
        
        int length();
        int charSize(int);

};


Unicode::~Unicode()
{
    ///Destroys the memory allocated for the processed data.
	delete[] single_utf8;
}
Unicode::Unicode(std::string s){
    raw_data = s;
    scan_RawInput();    
}

int Unicode::charSize(int i)
{
	///Returns the byte size of 'i'th UTF-8 character
	if(i<=unicode_length)
    {
         return(single_utf8[i].utf_size);
    }
    else
    {
        std::cout<<std::endl<<"Error: Index Out of Bound"<<std::endl;
    }
}

std::string Unicode::operator[](int i)
{
    ///Returns the 'i'th UTF-8 character as string
    if(i<=unicode_length)
    {
        return single_utf8[i].unicode_char;
    }
    else
    {
        std::cout<<std::endl<<"Error: Index Out of Bound"<<std::endl;
    }
}

void Unicode::operator=(std::string s)
{
	raw_data=s;
	scan_RawInput();
}

int Unicode::length()
{
    ///Return length of unicode string
	return unicode_length;
}
void Unicode::scan_RawInput()
{
	/**
	  *The function allocates suficient memory and than scans through the raw data.
	  *The UTF-8 characters are seperated form each other and stored in the variable single_utf8.
	  */
	 Char *info=new Char[raw_data.length()+1];
	/*
	 *I am using length of raw_data as an index to store memory because
	 *Its the only approximation I have.
	 *It is never less than number of UTF-8 characters
	  *But its a really bad approximation, especially since most of the character that this program will handle is of size 3 bytes.
	  *Hence at the end of the function,I have done something.
	 */
    int i,j=0;
    for(i=0;i<raw_data.length();i++)
	{
		/*
		 *The UTF-8 characters are seperted by using their byte structure
		 *But it is not possible to read a single bit dirctly
		 *Hence, I am using the eqivalent integers to do the seperation
		 *(unsigned char) are used because we need the bytes as pure integer, with no sign.
		 */
		if((unsigned char)raw_data[i]<=127)
		{
			/*
			 *Lowest digit of 0XXXXXXX pemutaion is 00000000(which also happens to be smallest usigned integer) and highest is 01111111=127
			 *So if a byte is within this range, it represents a one byte character(i.e ASCII character)
			 *Value of counter does not need to be changed.
			 */
			info[j].position=i;
			info[j].utf_size=1;
			info[j].unicode_char=raw_data[i];
			}
			else if((unsigned char)raw_data[i]>=192&&(unsigned char)raw_data[i]<=223)
			{
			/*
			 *Lowest digit of 110XXXXX pemutaion is 11000000=192 and highest is 11011111=223
			 *So if a byte is within this range, it represents a two byte character(i.e ASCII character)
			 *value of counter is increased by 1.
			 */
				info[j].position=i;
				info[j].utf_size=2;
				info[j].unicode_char=raw_data[i];
				info[j].unicode_char+=raw_data[++i];
			}
			else if((unsigned char)raw_data[i]>=224&&(unsigned char)raw_data[i]<=239)
			{
			/*
			 *Lowest digit of 1110XXXX pemutaion is 11100000=224 and highest is 1110111=239
			 *So if a byte is within this range, it represents a three byte character(i.e ASCII character)
			 *value of counter is increased by 2.
			 */
				info[j].position=i;
				info[j].utf_size=3;
				info[j].unicode_char=raw_data[i];
				info[j].unicode_char+=raw_data[++i];
				info[j].unicode_char+=raw_data[++i];
			}
			else if((unsigned char)raw_data[i]>240&&(unsigned char)raw_data[i]<=247)
			{
			/*
			 *Lowest digit of 11110XXX pemutaion is 11110000=240 and highest is 11110111=247
			 *So if a byte is within this range, it represents a four byte character(i.e ASCII character)
			 *value of counter is increased by 3.
			 */
				info[j].position=i;
				info[j].utf_size=4;
				info[j].unicode_char=raw_data[i];
				info[j].unicode_char+=raw_data[++i];
				info[j].unicode_char+=raw_data[++i];
				info[j].unicode_char+=raw_data[++i];
			}
			else
			{
				/*
				 *I'm only keeping it here incase the program encounters an invalid bit sequence.
				 *Like those greater than 247.
				 *The chances of this happening are very less.
				 */
				info[j].position=i;
				info[j].utf_size=1;
				info[j].unicode_char=raw_data[i];
			}
			j++;
	}
	info[j].unicode_char=EOU;
	info[j].utf_size=0;//Its not zero byted..but it is not significant in the text
	info[j].position=i;
	unicode_length=j;
	single_utf8=new Char[unicode_length+1];
	/*
	 *To save memory, I will now copy the data to  single_utf8 whose size is allocated as required.
	 *unicode_length+1 because of the EOU.
	 *Then the I will delete the memory allocated for the info.
	 */
	for(i=0;i<=unicode_length;i++)
	{
		single_utf8[i]=info[i];
	}
	delete[] info;
}
#endif // UNICODE_H
