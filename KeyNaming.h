/*
	KeyNaming.h
	Keynaming 2.2 interface
	(c)2001-2008 Jens Ayton <jens@ayton.se>, except where otherwise noted.	
	Tabs = 4, Indent = 4. Live with it. :-)
	
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

/*!
	@header
	@version		2.2
	@discussion		Copyright &copy; 2001&ndash;2008 Jens Ayton
					
					Permission is hereby granted, free of charge, to any person obtaining a copy
					of this software and associated documentation files (the "Software"), to deal
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
					<hr />
					Like UCKeyTranslate(), but much less scary.
					
					<h2>Overview</h2>
					
					The KeyNaming library converts virtual key codes (as provided by the various event systems) or HID usages codes (as provided by IOKit’s HID interface) to descriptive strings reflecting the current keyboard layout.
					
					Two macros affect the availability of KeyNaming functions. Functions taking virtual key codes as parameters are disabled if <code>KEYNAMING_ENABLE_VKC</code> is defined as zero. Functions taking HID usage codes as parameters are disabled if <code>KEYNAMING_ENABLE_HID</code> is defined as zero. By default, both are set to 1 and dead code stripping is assumed to work.
					
					<h2>Cocoa</h2>
					Normal <a href="http://developer.apple.com/documentation/Cocoa/Conceptual/CarbonCocoaDoc/Articles/InterchangeableDataTypes.html">toll-free bridging</a> rules apply: if calling from Cocoa, cast results to <code>NSString *</code> or <code>NSArray *</code>, and remember to release.
	@copyright		2001–2008 Jens Ayton
*/


#ifndef INCLUDED_KEYNAMING_h
#define INCLUDED_KEYNAMING_h


#include <CoreFoundation/CoreFoundation.h>


#ifndef KEYNAMING_ENABLE_VKC
	#define KEYNAMING_ENABLE_VKC		1
#endif
#ifndef KEYNAMING_ENABLE_HID
	#define KEYNAMING_ENABLE_HID		1
#endif


#if __cplusplus
extern "C" {
#endif


#if KEYNAMING_ENABLE_VKC

/*! @functiongroup	Virtual Key Code interface */

/*!	@function		KeyNamingCopyOneKeyName
	@abstract		Get a name for a key.
	@discussion		Given a virtual key code, returns a description as a <code>CFStringRef</code>.
					This will either be the character generated by the corresponding key in the
					current keyboard layout (for instance, <q>A</q>) or a string loaded from the
					current string table (for instance, <q>Caps Lock</q> or <q>&#x21ea;</q>).
					
					Only avaliable if <code>KEYNAMING_ENABLE_VKC</code> is non-zero.
	@param			inVirtualKeyCode	The virtual key code of the key to name.
	@result			A name string for the key. You are responsible for releasing this string.
*/
CFStringRef KeyNamingCopyOneKeyName(uint16_t inVirtualKeyCode);


/*!	@function		KeyNamingCopyKeyNames
	@abstract		Get names for a list of keys.
	@discussion		Given an array of virtual key codes, return a string containing descriptions of
					the keys. Key names will be separated by two spaces. (This is potentially useful
					for combinations, such as <q>Shift&nbsp;&nbsp;Option&nbsp;&nbsp;A</q>.)
					Marginally more efficient than multiple calls to { @link //apple_ref/c/func/KeyNamingCopyOneKeyName KeyNamingCopyOneKeyName() } in that certain internal state can
					be cached.
					
					Only avaliable if <code>KEYNAMING_ENABLE_VKC</code> is non-zero.
	@param			inCount				The number of keys.
	@param			inVirtualKeyCodes	The virtual key codes of the keys to name, in an array.
	@result			A name string for the keys. You are responsible for releasing this string.
 */
CFStringRef KeyNamingCopyKeyNames(uint32_t inCount, const uint16_t * const inVirtualKeyCodes);


/*!	@function		KeyNamingCopyKeyNamesAsArray
	@abstract		Get names for a list of keys, as a <code>CFArray</code>.
	@discussion		Given an array of virtual key codes, return a list containing a description of
					each of the keys. Marginally more efficient than multiple calls to @link
					KeyNamingCopyOneKeyName <code>KeyNamingCopyOneKeyName()</code> @/link in that
					certain internal state can be cached.
					
					Only avaliable if <code>KEYNAMING_ENABLE_VKC</code> is non-zero.
	@param			inCount				The number of keys.
	@param			inVirtualKeyCodes	The virtual key codes of the keys to name, in an array.
	@result			A list of name strings for the keys. You are responsible for releasing this
					array.
 */
CFArrayRef KeyNamingCopyKeyNamesAsArray(uint32_t inCount, const uint16_t * const inVirtualKeyCodes);

#endif	/* KEYNAMING_ENABLE_VKC */


#if KEYNAMING_ENABLE_HID

/*! @functiongroup	HID interface */

/*!	@function		KeyNamingCopyOneKeyNameHID
	@abstract		Get a name for a key.
	@discussion		Given a HID usage code in the Keyboard or Keypad page, returns a description as
					a <code>CFStringRef</code>. This will either be the character generated by the
					corresponding key in the current keyboard layout (for instance, <q>A</q>) or a
					string loaded from the current string table (for instance, <q>Caps Lock</q> or
					<q>&#x21ea;</q>).
					
					Only avaliable if <code>KEYNAMING_ENABLE_HID</code> is non-zero.
	@param			inUsage				The HID usage code of the key to name.
	@result			A name string for the key. You are responsible for releasing this string.
*/
CFStringRef KeyNamingCopyOneKeyNameHID(int32_t inUsage);


/*!	@function		KeyNamingCopyKeyNamesHID
	@abstract		Get names for a list of keys.
	@discussion		Given an array of HID usage codes, return a string containing descriptions of
					the keys. Key names will be separated by two spaces. (This is potentially useful
					for combinations, such as <q>Shift&nbsp;&nbsp;Option&nbsp;&nbsp;A</q>.)
					Marginally more efficient than multiple calls to @link
					KeyNamingCopyOneKeyNameHID <code>KeyNamingCopyOneKeyNameHID()</code> @/link in
					that certain internal state can be cached.
					
					Only avaliable if <code>KEYNAMING_ENABLE_HID</code> is non-zero.
	@param			inCount				The number of keys.
	@param			inUsages			The HID usage codes of the keys to name, in an array.
	@result			A name string for the keys. You are responsible for releasing this string.
 */
CFStringRef KeyNamingCopyKeyNamesHID(uint32_t inCount, const int32_t * const inUsages);


/*!	@function		KeyNamingCopyKeyNamesAsArrayHID
	@abstract		Get names for a list of keys, as a <code>CFArray</code>.
	@discussion		Given an array of HID usage codes, return a list containing a description of
					each of the keys. Marginally more efficient than multiple calls to @link
					KeyNamingCopyOneKeyNameHID <code>KeyNamingCopyOneKeyNameHID()</code> @/link in
					that certain internal state can be cached.
					
					Only avaliable if <code>KEYNAMING_ENABLE_VKC</code> is non-zero.
	@param			inCount				The number of keys.
	@param			inUsages			The HID usage codes of the keys to name, in an array.
	@result			A list of name strings for the keys. You are responsible for releasing this
					array.
 */
CFArrayRef KeyNamingCopyKeyNamesAsArrayHID(uint32_t inCount, const int32_t * const inUsages);

#endif	/* KEYNAMING_ENABLE_HID */


/*! @functiongroup	Configuration */

/*!	@function		KeyNamingSetStringTable
	@abstract		Specifies the string table to use for naming special keys.
	@discussion		Call to identify the property list/.strings file KeyNaming should use for
					special key names. The default is <q>KeyNaming</q>. Passing <code>NULL</code>
					will revert to default.
	@param			inTableName			The name of the string table to use.
*/
void KeyNamingSetStringTable(CFStringRef inTableName);


/*!	@function		KeyNamingSetStringTableAndBundle
	@abstract		Specifies the string table to use for naming special keys.
	@discussion		Call to identify the property list/.strings file KeyNaming should use for
					special key names, and the bundle in which to look for the file. The defaults
					are <q>KeyNaming</q> and <code>NULL</code>, which will cause the main bundle to
					be used. Passing <code>NULL</code> will revert to default.
	@param			inTableName			The name of the string table to use.
	@param			inBundle			The bundle to look in.
*/
void KeyNamingSetStringTableAndBundle(CFStringRef inTableName, CFBundleRef inBundle);


#if __cplusplus
}
#endif

#endif	/* INCLUDED_KEYNAMING_h */
