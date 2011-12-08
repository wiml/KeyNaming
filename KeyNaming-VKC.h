/*
	KeyNaming-VKC.h
	Keynaming 2.2 implementation
	© 2001-2008 Jens Ayton <jens@ayton.se>, except where otherwise noted.
	
	Copyright © 2001–2008 Jens Ayton
 
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the “Software”), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/


#ifndef INCLUDED_KEYNAMING_VKC_h
#define INCLUDED_KEYNAMING_VKC_h

#include "KeyNaming.h"

#pragma mark * Virtual Key Codes

enum
{
	/*	Virtual key codes handled specially (from: Inside Macintosh: Text, Appendix C)
		
		Function keys. These are handled by loading the releveant string IFF the
		character code 10 (kCC_FKey) is generated. This allows the function keys
		to be remapped.
		
		The Menu/Application key on Windows keyboards also generates the character
		code 10 by default. It isn't immediately clear whether the VKC is used for
		an F key in other circumstances, but apps generally seem to interpret it as
		a normal key. For now, I'm defining it as Menu Key. It's possible Unix-
		oriented keyboards use it with a different key cap, e.g. Meta.
	*/
	kVKC_F1				= 122,
	kVKC_F2				= 120,
	kVKC_F3				= 99,
	kVKC_F4				= 118,
	kVKC_F5				= 96,
	kVKC_F6				= 97,
	kVKC_F7				= 98,
	kVKC_F8				= 100,
	kVKC_F9				= 101,
	kVKC_F10			= 109,
	kVKC_F11			= 103,
	kVKC_F12			= 111,
	kVKC_F13			= 105,
	kVKC_F14			= 107,
	kVKC_F15			= 113,
	kVKC_F16			= 106,
	kVKC_Menu			= 110,
	
	/*	Escape and clear are like the F keys, using the character code kCC_EscClr. */
	kVKC_Esc			= 53,
	kVKC_Clear			= 71,
	
	/*	The following are handled directy by recognising the virtual code. */
	kVKC_Space			= 49,
	kVKC_CapsLock		= 57,
	kVKC_Shift			= 56,
	kVKC_Option			= 58,
	kVKC_Control		= 59,
	kVKC_rShift			= 60,		/*	Right-hand modifiers; not implemented */
	kVKC_rOption		= 61,
	kVKC_rControl		= 62,
	kVKC_Command		= 55,
	kVKC_Return			= 36,
	kVKC_Backspace		= 51,		/*	Left delete */
	kVKC_Delete			= 117,		/*	right delete */
	kVKC_Help			= 114,
	kVKC_Home			= 115,
	kVKC_PgUp			= 116,
	kVKC_PgDn			= 121,
	kVKC_End			= 119,
	kVKC_LArrow			= 123,
	kVKC_RArrow			= 124,
	kVKC_UArrow			= 126,
	kVKC_DArrow			= 125,
	kVKC_KpdEnter		= 76,		/*	"normal" enter key */
	kVKC_KbdEnter		= 52,		/*	Powerbooks (and some early Macs) */
	kVKC_Fn				= 63,
	
	/*	Keypad keys. These are named by loading the string "Keypad %@" and
		replacing the %@ with the key's character name. The constant names
		do not correspond to the key caps in any KCHR that I'm aware of;
		they're just used to recognise the set of keys. Note that Enter and
		Clear aren't handled this way. */
	kVKC_Kpd_0			= 81,
	kVKC_Kpd_1			= 75,
	kVKC_Kpd_2			= 67,
	kVKC_Kpd_3			= 89,
	kVKC_Kpd_4			= 91,
	kVKC_Kpd_5			= 92,
	kVKC_Kpd_6			= 78,
	kVKC_Kpd_7			= 86,
	kVKC_Kpd_8			= 87,
	kVKC_Kpd_9			= 88,
	kVKC_Kpd_A			= 69,
	kVKC_Kpd_B			= 83,
	kVKC_Kpd_C			= 84,
	kVKC_Kpd_D			= 85,
	kVKC_Kpd_E			= 82,
	kVKC_Kpd_F			= 65,
	
	/* 2.1b5: values from new list in Event.h in OS X 10.5 */
	kVKC_VolumeUp		= 72,
	kVKC_VolumeDown		= 73,
	kVKC_Mute			= 74,
	
	kVKC_F17			= 64,
	kVKC_F18			= 79,
	kVKC_F19			= 80,
	kVKC_F20			= 90,
	
	#if KEYNAMING_ENABLE_HID
	
	/*	Fake VKCs. These are used for HID usages that, to my knowledge, have
		no corresponding VKC. I use the range 0x6000 up; GetKeys() can't return
		in this range, and other VKC usages probably won't. */
	kFKC_base_			= 0x6000,
	kFKC_rCommand,
/*	kFKC_Mute,			*/
/*	kFKC_VolumeDown,	*/
/*	kFKC_VolumeUp,		*/
	kFKC_Power			= 0x6005,
	kFKC_Eject,
/*	kFKC_F17,			*/
/*	kFKC_F18,			*/
/*	kFKC_F19,			*/
/*	kFKC_F20,			*/
	kFKC_F21			= 0x600B,
	kFKC_F22,
	kFKC_F23,
	kFKC_F24,
	
	#endif
	
	kEnumAtTheEndToSatisfyIrritableCompilers
};


#pragma mark * Character Codes
enum
{
	/*	Character codes. */
	kCC_FKey			= 16,	/* see above section on F-keys */
	kCC_EscClr			= 27,	/* see above section on escape and clear */
	
	/*	These are handled by loading the corresponding string. */
	kCC_Tab				= 9,
	kCC_Space			= 32	/* Also recognised by VKC */
};


enum
{	
	/* Mode constants for Name1Key */
	kNoSpecialHandling = 0,
	kEscapeClearHandling,
	kFKeyHandling,
	kKeypadHandling,
	kUnknownHandling,
	
	kHandlingModeCount
};


#endif	/* INCLUDED_KEYNAMING_VKC_h */
