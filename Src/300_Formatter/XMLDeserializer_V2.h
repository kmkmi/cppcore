#pragma once

#include <string>
#include <vector>
#include <stack>

#include "Interface.h"
#include "Pair.h"
#include "FmtTypes.h"
#include "IChannel.h"
#include "XMLFunctions.h"
#include "FormatterCommon.h"

namespace fmt_internal
{
	class CXMLDeserializer_V2 : public core::IFormatterT
	{
	private:
		std::vector<sGroupingData>	m_vecObjectCountStack;
		std::stack<ST_XML_NODE*>	m_stackTraverse;
		bool			m_bValidity;
		bool			m_bReserved[7];
		std::tstring	m_strErrMsg;
		ST_XML_NODE		m_stDummy;
		ST_XML_NODE		m_stRoot;


	public:
		CXMLDeserializer_V2(core::IChannel& channel);
		~CXMLDeserializer_V2(void);

		bool			CheckValidity(std::tstring* pStrErrMsg)		{	if( pStrErrMsg )	*pStrErrMsg = m_strErrMsg;	return m_bValidity;		}

	private:
		size_t			_BeginDictionaryGrouping(std::tstring& strKey, const size_t tSize, bool bAllowMultiKey);
		void			_EndDictionaryGrouping();

		size_t			_BeginArrayGrouping(std::tstring& strKey, const size_t tSize);
		void			_EndArrayGrouping();

		void			_BeginObjectGrouping(std::tstring& strKey);
		void			_EndObjectGrouping();

		void			_BeginRootGrouping();
		void			_EndRootGrouping();

		core::IFormatterT& Sync(std::tstring& strKey, std::tstring* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, std::ntstring* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, bool* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, char* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, short* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, int32_t* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, int64_t* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, BYTE* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, WORD* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, DWORD* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, QWORD* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, float* pValue);
		core::IFormatterT& Sync(std::tstring& strKey, double* pValue);
	};
}
