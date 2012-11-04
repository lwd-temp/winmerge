/** 
 * @file OptionsMgr.h
 *
 * @brief Interface for Options management classes
 *
 */
// ID line follows -- this is updated by SVN
// $Id$

/* The MIT License
Copyright (c) 2004-2009 Kimmo Varis
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef _OPTIONS_MGR_
#define _OPTIONS_MGR_

#include <map>
#include "UnicodeString.h"
#include "varprop.h"

/**
 * @brief Class to store option name, value and default value.
 */
class COption
{
public:
	/**
	* @brief Return values for functions.
	*/
	enum
	{
		OPT_OK				= 0, /**< All good. */
		OPT_ERR				= 1, /**< General error. */
		OPT_WRONG_TYPE		= 2, /**< Option type was wrong. */
		OPT_UNKNOWN_TYPE	= 3, /**< Given option type is not known. */
		OPT_NOTFOUND		= 4, /**< Option name not found. */
	};

	COption();
	COption(const COption& option);

	COption& operator=(const COption& option);

	int Init(const String& name, varprop::VariantValue defaultVal);
	varprop::VariantValue Get() const;
	varprop::VariantValue GetDefault() const;
	int Set(varprop::VariantValue value, bool allowConversion = false);
	int SetDefault(varprop::VariantValue defaultValue); 
	void Reset();

protected:
	bool ConvertInteger(varprop::VariantValue & value, varprop::VT_TYPE nType);
	bool ConvertString(varprop::VariantValue & value, varprop::VT_TYPE nType);
	bool ConvertType(varprop::VariantValue & value, varprop::VT_TYPE nType);

private:
	String m_strName; /**< Option's name. */
	varprop::VariantValue m_value; /**< Option's current value. */
	varprop::VariantValue m_valueDef; /**< Option's default value. */
};

typedef std::map<String, COption> OptionsMap;

/**
 * @brief Class to store list of options.
 * This class holds a list of all options (known to application). Options
 * are accessed by their name.
 *
 * Option must be first initialized before it can be read/set. Initialization
 * is done with InitOption() method.
 */
class COptionsMgr
{
public:
	int AddOption(const String& name, varprop::VariantValue defaultValue);
	varprop::VariantValue Get(const String& name) const;
	String GetString(const String& name) const;
	int GetInt(const String& name) const;
	bool GetBool(const String& name) const;
	int Set(const String& name, varprop::VariantValue value);
	int Set(const String& name, const String& value);
	int Set(const String& name, const TCHAR *value);
	int Set(const String& name, bool value);
	int Set(const String& name, int value);
	int Reset(const String& name);
	int GetDefault(const String& name, String & value) const;
	int GetDefault(const String& name, unsigned & value) const;
	int GetDefault(const String& name, bool & value) const;

	virtual int InitOption(const String& name,
		varprop::VariantValue defaultValue) = 0;
	virtual int InitOption(const String& name, const String& defaultValue) = 0;
	virtual int InitOption(const String& name, const TCHAR *defaultValue) = 0;
	virtual int InitOption(const String& name, int defaultValue, bool serializable = true) = 0;
	virtual int InitOption(const String& name, bool defaultValue) = 0;

	virtual int SaveOption(const String& name) = 0;
	virtual int SaveOption(const String& name, varprop::VariantValue value) = 0;
	virtual int SaveOption(const String& name, const String& value) = 0;
	virtual int SaveOption(const String& name, const TCHAR *value) = 0;
	virtual int SaveOption(const String& name, int value) = 0;
	virtual int SaveOption(const String& name, bool value) = 0;
	virtual int SaveOption(const String& name, unsigned value);

	virtual int RemoveOption(const String& name);

	virtual int ExportOptions(const String& filename) const = 0;
	virtual int ImportOptions(const String& filename) = 0;
	
	virtual void SetSerializing(bool serializing=true) = 0;

protected:
	OptionsMap m_optionsMap; /**< Map where options are stored. */
};

#endif // _OPTIONS_MGR_
