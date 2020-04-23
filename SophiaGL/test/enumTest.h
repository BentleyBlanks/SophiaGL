#pragma once
#include<iostream>  
#include <string>
#include <sstream>
#include <map>
#include <vector>

#define __ENUM_TO_STRING(Type, ...)															                \
class EnumReflectionHelper##Type																	        \
{																								            \
public:																							            \
	EnumReflectionHelper##Type()																		    \
	{																							            \
		std::stringstream si(#__VA_ARGS__);														            \
		std::string token;																		            \
		while ((token = getName(si)).length())													            \
		{																						            \
			stringTable.push_back(#Type "::" + token);										                \
			valueTable[#Type "::" + token] = valueTable[token] = stringTable.size() - 1;	                \
		}																						            \
	}																							            \
	std::string toString(Type type) const													                \
	{																							            \
		return stringTable[static_cast<int>(type)];												            \
	}																							            \
	Type fromString(std::string s) const													                \
	{																							            \
		return static_cast<Type>(valueTable.at(s));	                                                        \
	}																							            \
	static EnumReflectionHelper##Type* getHelper()													        \
	{																							            \
		static EnumReflectionHelper##Type helper;														    \
		return &helper;																			            \
	}																							            \
private:																						            \
	static std::string getName(std::stringstream& si)											            \
	{																							            \
		std::string ret;																		            \
		while (si &&																			            \
			   !((si.peek() >= 'a' && si.peek() <= 'z') ||										            \
			   (si.peek() >= 'A' && si.peek() <= 'Z') ||										            \
			   (si.peek() >= '0' && si.peek() <= '9')))											            \
			si.get();																			            \
		if (!si) return "";																		            \
		while ((si.peek() >= 'a' && si.peek() <= 'z') ||										            \
			   (si.peek() >= 'A' && si.peek() <= 'Z') ||										            \
			   (si.peek() >= '0' && si.peek() <= '9'))											            \
			ret += si.get();																	            \
		return ret;																				            \
	}																							            \
	std::vector<std::string> stringTable;														            \
	std::map<std::string, int> valueTable;														            \
};			

#define __ENUM_DEFINE(TypeName, ...)                             \
    enum class TypeName { __VA_ARGS__ };                         \

#define ENUM_CLASS(TypeName, ...)                                \
    __ENUM_DEFINE(TypeName, __VA_ARGS__)                         \
    __ENUM_TO_STRING(TypeName, __VA_ARGS__)

#ifdef REFLECT_NS
	#define ENUM_REFLECT(TypeName) (::REFLECT_NS::EnumReflectionHelper<TypeName>::getHelper())
#else
	#define ENUM_REFLECT(Type) (EnumReflectionHelper##Type::getHelper())
#endif

ENUM_CLASS(MyEnum,
		   E_MEMBER1,
		   E_MEMBER2,
		   E_MEMBER3);

int main()
{
	std::cout << ENUM_REFLECT(MyEnum)->toString(MyEnum::E_MEMBER1) << std::endl;
	std::cout << (int)ENUM_REFLECT(MyEnum)->fromString("MyEnum::E_MEMBER1") << std::endl;

	return 0;
}