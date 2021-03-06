﻿#pragma once
#include <core/s3Enum.h>

s3Enum(s3MouseType,
	   none = -1,
	   left = 0,
	   middle,
	   right);

s3Enum(s3MouseTriggerType,
	   none = 0,
	   pressed,
	   released,
	   move,
	   scroll);

s3Enum(s3KeyTriggerType,
	   none = 0,
	   pressed,
	   released);

s3Enum(s3KeyType,
	   /* The unknown key */
	   unknown = -1,

	   /* printable keys */
	   space        = 32,
	   apostrophe   = 39,
	   comma        = 44,
	   minus        = 45,
	   period       = 46,
	   slash        = 47,
	   d0           = 48,
	   d1           = 49,
	   d2           = 50,
	   d3           = 51,
	   d4           = 52,
	   d5           = 53,
	   d6           = 54,
	   d7           = 55,
	   d8           = 56,
	   d9           = 57,
	   semicolon    = 59,
	   equal        = 61,
	   A            = 65,
	   B            = 66,
	   C            = 67,
	   D            = 68,
	   E            = 69,
	   F            = 70,
	   G            = 71,
	   H            = 72,
	   I            = 73,
	   J            = 74,
	   K            = 75,
	   L            = 76,
	   M            = 77,
	   N            = 78,
	   O            = 79,
	   P            = 80,
	   Q            = 81,
	   R            = 82,
	   S            = 83,
	   T            = 84,
	   U            = 85,
	   V            = 86,
	   W            = 87,
	   X            = 88,
	   Y            = 89,
	   Z            = 90,
	   leftBracket  = 91,
	   backslash    = 92,
	   rightBracket = 93,
	   graveAccent  = 96,
	   world1       = 16,
	   world2       = 16,

	   /* function keys */
	   escape       = 256,
	   enter        = 257,
	   tab          = 258,
	   backspace    = 259,
	   insert       = 260,
	   del          = 261,
	   right        = 262,
	   left         = 263,
	   down         = 264,
	   up           = 265,
	   pageUp       = 266,
	   pageDown     = 267,
	   home         = 268,
	   end          = 269,
	   capsLock     = 280,
	   scrolLlock   = 281,
	   numLock      = 282,
	   printScreen  = 283,
	   pause        = 284,
	   f1           = 290,
	   f2           = 291,
	   f3           = 292,
	   f4           = 293,
	   f5           = 294,
	   f6           = 295,
	   f7           = 296,
	   f8           = 297,
	   f9           = 298,
	   f10          = 299,
	   f11          = 300,
	   f12          = 301,
	   f13          = 302,
	   f14          = 303,
	   f15          = 304,
	   f16          = 305,
	   f17          = 306,
	   f18          = 307,
	   f19          = 308,
	   f20          = 309,
	   f21          = 310,
	   f22          = 311,
	   f23          = 312,
	   f24          = 313,
	   f25          = 314,
	   kp0          = 320,
	   kp1          = 321,
	   kp2          = 322,
	   kp3          = 323,
	   kp4          = 324,
	   kp5          = 325,
	   kp6          = 326,
	   kp7          = 327,
	   kp8          = 328,
	   kp9          = 329,
	   kpDecimal    = 330,
	   kpDivide     = 331,
	   kpMultiply   = 332,
	   kpSubtract   = 333,
	   kpAdd        = 334,
	   kpEnter      = 335,
	   kpEqual      = 336,
	   leftShift    = 340,
	   leftControl  = 341,
	   leftAlt      = 342,
	   leftSuper    = 343,
	   rightShift   = 344,
	   rightControl = 345,
	   rightAlt     = 346,
	   rightSuper   = 347,
	   menu         = 348,

	   last);

class s3MouseEvent
{
public:
	s3MouseEvent(s3MouseType type               = s3MouseType::none,
				 s3MouseTriggerType triggerType = s3MouseTriggerType::none,
				 int x                          = 0,
				 int y                          = 0,
				 int offsetX                    = 0,
				 int offsetY                    = 0,
				 float scroll                   = false,
				 bool control                   = false,
				 bool shift                     = false,
				 bool alt                       = false);

	void print() const;

	s3MouseType type               = s3MouseType::none;
	s3MouseTriggerType triggerType = s3MouseTriggerType::none;

	// position
	int x = 0, y = 0;
	// The offset of the mouse moved since the last event
	int offsetX = 0, offsetY = 0;
	// Distance of the wheel scrolled
	float scroll = 0.0f;
	// Is the Control / Shift / Alt modifier pressed
	bool control = false, shift = false, alt = false;
};

class s3KeyEvent
{
public:
	s3KeyEvent(s3KeyType keyType            = s3KeyType::unknown,
			   s3KeyTriggerType triggerType = s3KeyTriggerType::none,
			   std::string key				= "",
			   bool control                 = false,
			   bool shift                   = false,
			   bool alt                     = false);

	void print() const;

	// Type of the key
	s3KeyType keyType            = s3KeyType::unknown;
	s3KeyTriggerType triggerType = s3KeyTriggerType::none;

	// This value will be 0 if it is a non-printable character.
	std::string key = "";
	// Is the Control / Shift / Alt modifier pressed
	bool control = false, shift = false, alt = false;
};