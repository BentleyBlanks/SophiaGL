#pragma once
#include <core/s3Settings.h>

enum s3KeyCode
{
	/* The unknown key */
	unknown = -1,

	/* printable keys */
	space        = 32,
	apostrophe   = 39,
	comma        = 44,
	minus        = 45,
	period       = 46,
	slash        = 47,
	D0           = 48,
	D1           = 49,
	D2           = 50,
	D3           = 51,
	D4           = 52,
	D5           = 53,
	D6           = 54,
	D7           = 55,
	D8           = 56,
	D9           = 57,
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
	del			 = 261,
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

	last
};

class s3MouseEvent
{
public:
	enum s3ButtonType
	{
		NONE = -1,
		LEFT = 0,
		MIDDLE,
		RIGHT
	};

	s3MouseEvent(s3ButtonType type,
				 int x,
				 int y,
				 int offsetX,
				 int offsetY,
				 float scroll,
				 bool control,
				 bool shift);

	//void print(int state) const;

	s3ButtonType type;
	// position
	int x, y;
	// The offset of the mouse moved since the last event
	int offsetX, offsetY;
	// Distance of the wheel scrolled
	float scroll;
	// Is the Control / Shift / Alt modifier pressed
	bool control, shift;
};

class s3KeyEvent
{
public:
	s3KeyEvent(s3KeyCode keyCode,
			   unsigned int key,
			   bool control,
			   bool shift,
			   bool alt);

	//void print(int state) const;

	// Type of the key
	s3KeyCode keyCode;
	// This value will be 0 if it is a non-printable character.
	unsigned int key;
	// Is the Control / Shift / Alt modifier pressed
	bool control, shift, alt;
};