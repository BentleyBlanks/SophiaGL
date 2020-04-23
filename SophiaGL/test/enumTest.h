#define _CRT_SECURE_NO_WARNINGS

#include <iostream>  
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

//È¥¿Õ¸ñ
std::string deleteSpace(const std::string& str)
{
	if (str.empty()) return std::string("");

	std::string tmpStr;
	for (int i = 0; i < str.length(); i++)
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			tmpStr += str[i];

	return tmpStr;
}

bool parseEnumString(const std::string& str, std::map<int, std::string>& keyValueList)
{
	// string with enum type name and value
	std::vector<std::string> fieldList;

	// parse fieldList by comma
	size_t pos = str.find(",");
	size_t lastPos = 0;
	while (pos != std::string::npos)
	{
		fieldList.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = pos + 1;
		pos = str.find(",", static_cast<unsigned int>(lastPos));
	}

	if (lastPos != str.length())
		fieldList.push_back(str.substr(lastPos, str.length() - lastPos));

	if (fieldList.size() == 0)
		return false;

	// default value start with 0
	int defaultValue = 0;

	// parse enum type name and specific value
	keyValueList.clear();
	for (std::vector<std::string>::iterator it = fieldList.begin(); it != fieldList.end(); it++)
	{
		long value;
		std::string enumStr = deleteSpace(*it);
		std::string name;

		// equal character may not provided
		int pos = static_cast<int>(enumStr.find("="));
		if (pos != std::string::npos)
		{
			char valueStr[64] = { '\0' };
			std::string temp;
			name = enumStr.substr(0, pos);

			// substr after equal(value string)
			temp = enumStr.substr(pos + 1, (*it).length());
			sscanf(temp.c_str(), "%[^LlUu]", valueStr);
			temp = valueStr;

			if (temp.find("0x") != std::string::npos)
				value = strtol(valueStr, NULL, 16);
			else if (temp[0] == '0')
				value = strtol(valueStr, NULL, 8);
			else
				value = strtol(valueStr, NULL, 10);
		}
		else
		{
			name = enumStr;
			value = defaultValue;
		}

		defaultValue = value + 1;
		keyValueList[value] = name;
	}

	if (keyValueList.size() == 0)
		return false;
	return true;
}

#define __S3ENUM_TO_STRING(Type, ...)																					   \
template<typename Type>																								 	   \
class s3EnumHelper																									 	   \
{																													 	   \
public:																												 	   \
	s3EnumHelper()																									 	   \
	{																												 	   \
		std::string enumStr(#__VA_ARGS__);																				   \
																													 	   \
		parseEnumString(enumStr);																					 	   \
	}																												 	   \
																													 	   \
	int getCount() const																							 	   \
	{																												 	   \
		return indexList.size();																					 	   \
	}																												 	   \
																													 	   \
	const std::string& toString(Type type) const																		   \
	{																													   \
		/* [] operator would add element if not exsits */																   \
		return enumList.at((int)(type));																				   \
	}																												 	   \
																													 	   \
	Type fromString(std::string s) const																			 	   \
	{																												 	   \
		for (auto it = enumList.begin(); it != enumList.end(); it++)												 	   \
			if (it->second == s)																					 	   \
				return (Type)(it->first);																			 	   \
																													 	   \
		return (Type)-1;																							 	   \
	}																												 	   \
																													 	   \
	Type fromIndex(int index) const																					 	   \
	{																												 	   \
		if(index > 0 && index < indexList.size())																	 	   \
			return (Type)(indexList[index]);																		 	   \
		return (Type)-1;																							 	   \
	}																													   \
																														   \
	void print()																										   \
	{																													   \
		for (auto it = enumList.begin(); it != enumList.end(); it++)													   \
		{																												   \
			std::cout << "Value:" << it->first << ", " << "Name: " << it->second << std::endl;							   \
		}																												   \
																														   \
		for (int i = 0; i < indexList.size(); i++)																		   \
		{																												   \
			std::cout << "Index:" << i << ", " << "Value: " << indexList[i] << std::endl;								   \
		}																												   \
	}																													   \
																													 	   \
	static s3EnumHelper& getHelper()																				 	   \
	{																												 	   \
		static s3EnumHelper helper;																					 	   \
		return helper;																								 	   \
	}																												 	   \
																													 	   \
private:																											 	   \
	std::string deleteSpace(const std::string& str)																	 	   \
	{																												 	   \
		if (str.empty()) return std::string("");																	 	   \
																													 	   \
		std::string tmpStr;																							 	   \
		for (int i = 0; i < str.length(); i++)																		 	   \
			if (str[i] != ' ')																						 	   \
				tmpStr += str[i];																					 	   \
																													 	   \
		return tmpStr;																								 	   \
	}																												 	   \
																													 	   \
	bool parseEnumString(const std::string& str)																	 	   \
	{																												 	   \
		/* string with enum type nameStr and value */																 	   \
		std::vector<std::string> fieldList;																			 	   \
																													 	   \
		/* parse fieldList by comma	*/																				 	   \
		size_t pos = str.find(",");																					 	   \
		size_t lastPos = 0;																							 	   \
		while (pos != std::string::npos)																			 	   \
		{																											 	   \
			fieldList.push_back(str.substr(lastPos, pos - lastPos));												 	   \
			lastPos = pos + 1;																						 	   \
			pos = str.find(",", static_cast<unsigned int>(lastPos));												 	   \
		}																											 	   \
																													 	   \
		if (lastPos != str.length())																				 	   \
			fieldList.push_back(str.substr(lastPos, str.length() - lastPos));										 	   \
																													 	   \
		if (fieldList.size() == 0)																					 	   \
			return false;																							 	   \
																													 	   \
		/* default value start with 0 */																			 	   \
		int defaultValue = 0;																						 	   \
																													 	   \
		/* parse enum type nameStr and specific value */															 	   \
		enumList.clear();																							 	   \
		for (std::vector<std::string>::iterator it = fieldList.begin(); it != fieldList.end(); it++)				 	   \
		{																											 	   \
			long value;																								 	   \
			std::string fieldStr = deleteSpace(*it);																 	   \
			std::string nameStr;																					 	   \
																													 	   \
			/* equal character may not provided	*/																	 	   \
			int pos = fieldStr.find("=");																			 	   \
			if (pos != std::string::npos)																			 	   \
			{																										 	   \
				char temp[64] = { '\0' };																			 	   \
				std::string valueStr;																				 	   \
				nameStr = fieldStr.substr(0, pos);																 		   \
																													 	   \
				/* substr after equal(value string)	*/																 	   \
				valueStr = fieldStr.substr(pos + 1, (*it).length());												 	   \
				sscanf(valueStr.c_str(), "%[^LlUu]", temp);															 	   \
				valueStr = temp;																					 	   \
																													 	   \
				/* convert string into interger	*/																	 	   \
				if (valueStr.find("0x") != std::string::npos)														 	   \
					value = strtol(temp, NULL, 16);																	 	   \
				else if (valueStr[0] == '0')																		 	   \
					value = strtol(temp, NULL, 8);																	 	   \
				else																								 	   \
					value = strtol(temp, NULL, 10);																	 	   \
			}																										 	   \
			else																									 	   \
			{																										 	   \
				nameStr = fieldStr;																					 	   \
				value = defaultValue;																				 	   \
			}																										 	   \
																													 	   \
			defaultValue = value + 1;																				 	   \
			indexList.push_back(value);																				 	   \
			enumList[value] = nameStr;																				 	   \
		}																											 	   \
																													 	   \
		if (enumList.size() == 0)																					 	   \
			return false;																							 	   \
		return true;																								 	   \
	}																												 	   \
																													 	   \
	std::vector<int> indexList;																						 	   \
	std::map<int, std::string> enumList;																			 	   \
};																													 

#define __S3ENUM_DEFINE(Type, ...)                             \
    enum class Type { __VA_ARGS__ };                           \

#define s3Enum(Type, ...)                                      \
    __S3ENUM_DEFINE(Type, __VA_ARGS__)                         \
    __S3ENUM_TO_STRING(Type, __VA_ARGS__)

#define s3EnumUtil(Type) (s3EnumHelper<Type>::getHelper())

s3Enum(MyEnum,
	   E_MEMBER1 = -1,
	   E_MEMBER2 = 1200,
	   E_MEMBER3 = 0xfff);

int main()
{
	//std::string testStr = "A_1dddd3 =    1000,   _A_1dddd32,      _A_1dddd34    = 11000,_A_1dddd35 = 1200,	__sdfsdf_AD_4 = 0xAdef12,	_Asdfsdfdd = 01232";
	//std::map<int, std::string> keyValueList;
	//parseEnumString(testStr, keyValueList);

	auto xxx = s3EnumUtil(MyEnum);

	std::cout << s3EnumUtil(MyEnum).toString(MyEnum::E_MEMBER1) << std::endl;
	std::cout << (int)s3EnumUtil(MyEnum).fromString("E_MEMBER1") << std::endl;

	s3EnumUtil(MyEnum).print();

	for (int i = 0; i < s3EnumUtil(MyEnum).getCount(); i++)
	{
		auto temp = s3EnumUtil(MyEnum).fromIndex(i);
		auto str = s3EnumUtil(MyEnum).toString(temp);
		auto value = s3EnumUtil(MyEnum).fromString(str);

		std::cout << str << std::endl;
		std::cout << (int)value << std::endl;
	}

	getchar();
	return 0;
}