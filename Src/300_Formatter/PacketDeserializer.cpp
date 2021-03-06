 #include "stdafx.h"
#include "PacketDeserializer.h"

namespace fmt_internal
{
	//////////////////////////////////////////////////////////////////////////
	CPacketDeserializer::CPacketDeserializer(core::IChannel& channel)
		: IFormatter(channel)
		, m_bValidity(false)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	CPacketDeserializer::~CPacketDeserializer(void)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	inline static void DeserializeString(IChannel& channel, std::tstring& refValue)
	{
		do
		{
			WORD wLength;
			if (2 != channel.OnAccess(&wLength, 2))
				break;

			std::string strTemp;
			strTemp.resize(wLength);
			if (wLength != channel.OnAccess((void*)strTemp.c_str(), wLength))
				break;

			refValue = TCSFromUTF8(strTemp);
		} while (0);
	}

	//////////////////////////////////////////////////////////////////////////
	size_t CPacketDeserializer::_BeginDictionaryGrouping(std::tstring& strKey, const size_t tSize, bool bAllowMultiKey)
	{
		DeserializeString(m_Channel, strKey);

		WORD wCount = (WORD)tSize;
		if (2 != m_Channel.OnAccess(&wCount, 2))
			return 0;

		return wCount;
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_EndDictionaryGrouping()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	size_t CPacketDeserializer::_BeginArrayGrouping(std::tstring& strKey, const size_t tSize)
	{
		DeserializeString(m_Channel, strKey);

		WORD wCount = (WORD)tSize;
		if( 2 != m_Channel.OnAccess(&wCount, 2) )
			return 0;

		return wCount;
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_EndArrayGrouping()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_BeginObjectGrouping(std::tstring& strKey)
	{
		DeserializeString(m_Channel, strKey);
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_EndObjectGrouping()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_BeginRootGrouping()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void CPacketDeserializer::_EndRootGrouping()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	inline static void PacketDeserializerMetaFunction(IChannel& channel, std::tstring& strKey, T* pValue)
	{
		DeserializeString(channel, strKey);
		channel.OnAccess(pValue, sizeof(T));
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, std::tstring* pValue)
	{
		DeserializeString(m_Channel, strKey);
		DeserializeString(m_Channel, *pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT & CPacketDeserializer::Sync(std::tstring & strKey, std::ntstring * pValue)
	{
		std::tstring strTempString = TCSFromNTCS(*pValue);
		Sync(strKey, &strTempString);
		*pValue = NTCSFromTCS(strTempString);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, bool* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, char* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, short* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, int32_t* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, int64_t* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, BYTE* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, WORD* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, DWORD* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, QWORD* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, float* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	core::IFormatterT& CPacketDeserializer::Sync(std::tstring& strKey, double* pValue)
	{
		PacketDeserializerMetaFunction(m_Channel, strKey, pValue);
		return *this;
	}
}
