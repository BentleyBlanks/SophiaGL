#pragma once
#include <core/s3Settings.h>

// template class would caused redefinition of s3EnumHelper, if enum was declared inside class
#define __S3ENUM_TO_STRING(Type, ...)																					   \
class s3EnumHelper##Type																								   \
{																													 	   \
public:																												 	   \
	s3EnumHelper##Type()																									 	   \
	{																												 	   \
		std::string enumStr(#__VA_ARGS__);																				   \
																													 	   \
		parseEnumString(enumStr);																					 	   \
	}																												 	   \
																													 	   \
	int getCount() const																							 	   \
	{																												 	   \
		return (int)indexList.size();																					   \
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
	static s3EnumHelper##Type& getHelper()																				   \
	{																												 	   \
		static s3EnumHelper##Type helper;																				   \
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
			size_t pos = fieldStr.find("=");																			   \
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
    enum class Type : int { __VA_ARGS__ };                     \

#define s3Enum(Type, ...)                                      \
    __S3ENUM_DEFINE(Type, __VA_ARGS__)                         \
    __S3ENUM_TO_STRING(Type, __VA_ARGS__)

// core macro that would be used
//#define s3EnumUtilOutsideClass(Type) (s3EnumHelper##Type::getHelper())
//#define s3EnumUtilInsideClass(ClassName, Type) (ClassName::s3EnumHelper##Type::getHelper())

#define FOO1(Type) s3EnumHelper##Type::getHelper()
#define FOO2(ClassName, Type) ClassName::s3EnumHelper##Type::getHelper()


//--! https://blog.csdn.net/lmhuanying1012/article/details/78715351
// overload macro function(__VA_ARGS__ expand slightly different from GCC and VS compiler)
//#define s3EnumUtilOverload(_1, _2, FunctionName, ...) FunctionName
//#define s3EnumUtil(...) s3EnumUtilOverload(__VA_ARGS__, s3EnumUtilInsideClass, s3EnumUtilOutsideClass)(__VA_ARGS__)

#define _my_BUGFX(x) x

#define _my_NARG2(...) _my_BUGFX(_my_NARG1(__VA_ARGS__,_my_RSEQN()))
#define _my_NARG1(...) _my_BUGFX(_my_ARGSN(__VA_ARGS__))
#define _my_ARGSN(_1,_2,N,...) N
#define _my_RSEQN() 2,1,0

#define _my_FUNC2(name,n) name ## n
#define _my_FUNC1(name,n) _my_FUNC2(name,n)
#define GET_MACRO(func,...) _my_FUNC1(func,_my_BUGFX(_my_NARG2(__VA_ARGS__))) (__VA_ARGS__)

#define FOO(...) GET_MACRO(FOO,__VA_ARGS__)