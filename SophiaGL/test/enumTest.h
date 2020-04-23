#include<iostream>  
#include <string>
#include <sstream>
#include <map>
#include <vector>
//private:																						            
enum class MyEnum
{
	E_MEMBER1,
	E_MEMBER2,
	E_MEMBER3
};

//#define __S3ENUM_TO_STRING(Type, ...)														
class s3EnumUtil
{
public:
	s3EnumUtil()
	{
		std::stringstream si("E_MEMBER1, E_MEMBER2, E_MEMBER3");
		std::string token;
		while ((token = getName(si)).length())
		{
			stringTable.push_back("MyEnum::" + token);
			valueTable["MyEnum::" + token] = valueTable[token] = stringTable.size() - 1;
		}
	}
	std::string toString(MyEnum type) const
	{
		return stringTable[static_cast<int>(type)];
	}
	int toIndex(MyEnum type) const
	{
		std::string result = stringTable[static_cast<int>(type)];
	}
	MyEnum fromString(std::string s) const
	{
		return static_cast<MyEnum>(valueTable.at(s));
	}
	MyEnum fromIndex(int index) const
	{
		std::string result = stringTable[index];
		return static_cast<MyEnum>(valueTable.at(result));
	}
	static s3EnumUtil& getHelper()
	{
		static s3EnumUtil helper;
		return helper;
	}
	static std::string getName(std::stringstream& si)
	{
		std::string ret;
		while (si &&
			   !((si.peek() >= 'a' && si.peek() <= 'z') ||
			   (si.peek() >= 'A' && si.peek() <= 'Z') ||
			   (si.peek() >= '0' && si.peek() <= '9')))
			si.get();
		if (!si) return "";
		while ((si.peek() >= 'a' && si.peek() <= 'z') ||
			   (si.peek() >= 'A' && si.peek() <= 'Z') ||
			   (si.peek() >= '0' && si.peek() <= '9'))
			ret += si.get();
		return ret;
	}
	std::vector<std::string> stringTable;
	std::map<std::string, int> valueTable;
};

//#define __S3ENUM_DEFINE(TypeName, ...)                             \
//    enum class TypeName { __VA_ARGS__ };                           \
//
//#define s3Enum(TypeName, ...)                                      \
//    __S3ENUM_DEFINE(TypeName, __VA_ARGS__)                         \
//    __S3ENUM_TO_STRING(TypeName, __VA_ARGS__)
//
//#define s3EnumUtil(Type) (s3EnumUtil##Type::getHelper())

//s3Enum(MyEnum,
//       E_MEMBER1,
//       E_MEMBER2,
//       E_MEMBER3);

int main()
{
	auto xxx = s3EnumUtil::getHelper();

	std::cout << s3EnumUtil::getHelper().toString(MyEnum::E_MEMBER1) << std::endl;
	std::cout << (int)s3EnumUtil::getHelper().fromString("MyEnum::E_MEMBER1") << std::endl;

	return 0;
}