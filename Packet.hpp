/**
 *	@file	Packet.hpp
 *	@author	Kia
 */
#pragma once
#include <variant>
#include <optional>
#include <string>

namespace Origins::Models::Enum
{
	/**
	 *	@brief	The default packet protocol uses these characters
	 *			as visual dilimeters for data seperation and
	 *			organization.
	 */
	constexpr char stx = '\02';
	constexpr char etx = '\03';
	constexpr char epp = '\05';
	constexpr char dle = '\10';

	/**
	 *	@brief	List of basic data types that get 
	 */
	enum class DataType : unsigned char
	{
		String,
		Int16,
		Int32,
		Int64,
		Byte,
		UInt16,
		UInt32,
		UInt64,
		UByte,
		Float,
		Double
#ifdef __future
		, floatx3
#endif
		, NotValid
	};

	/**
	 *	@brief	List of all the packets.
	 */
	enum class packet : unsigned long long
	{
		Login = 0L,
		LoginConfirm = 1L,

		LoginFailBadInfo = 2L,
		LoginFailBan = 3L,
		LoginFailMaint = 4L,
		CreateAccount = 5L,
		AccountCreated = 6L,

		CreateAccountFailBadInfo = 7L,
		CreateAccountFailBanned = 8L,
		Ping = 9L,

		RequestCharacters = 10L,
		RequestedCharacters = 11L,

		CreateCharacter = 12L,
		CreateCharacterFailBadInfo = 13L,
		GenericError = static_cast<unsigned long long>(-1),

	};


	/**
	 *	@brief	Variant of the list of basic data types for networking.
	 */
	using PacketVariant = std::variant<bool, char, unsigned char, short, unsigned short, long, unsigned long, long long, unsigned long long, float, double, std::string>;


	/**
	 *	@brief	The information from recVariant needs to be extracted.
	 *	@tparam	T The expected infomration for extraction that gets denoted by visit.
	 */
	template <class T = unsigned long> struct ExtractPacketVar
	{
		std::optional<T> operator()(const bool df) const { if constexpr (std::is_same_v<T, bool>) return df; return std::nullopt; }
		std::optional<T> operator()(const char df) const { if constexpr (std::is_same_v<T, char>) return df; return std::nullopt; }
		std::optional<T> operator()(const unsigned char df) const { if constexpr (std::is_same_v<T, unsigned char>) return df; return std::nullopt; }
		std::optional<T> operator()(const short df) const { if constexpr (std::is_same_v<T, short>) return df; return std::nullopt; }
		std::optional<T> operator()(const unsigned short df) const { if constexpr (std::is_same_v<T, unsigned short>) return df; return std::nullopt; }
		std::optional<T> operator()(const long df) const { if constexpr (std::is_same_v<T, long>) return df; return std::nullopt; }
		std::optional<T> operator()(const unsigned long df) const { if constexpr (std::is_same_v<T, unsigned long>) return df; return std::nullopt; }
		std::optional<T> operator()(const long long df) const { if constexpr (std::is_same_v<T, long long>) return df; return std::nullopt; }
		std::optional<T> operator()(const unsigned long long df) const { if constexpr (std::is_same_v<T, unsigned long long>) return df; return std::nullopt; }
		std::optional<T> operator()(const float df) const { if constexpr (std::is_same_v<T, float>) return df; return std::nullopt; }
		std::optional<T> operator()(const double df) const { if constexpr (std::is_same_v<T, double>) return df; return std::nullopt; }
		std::optional<T> operator()(const std::string& df) const { if constexpr (std::is_same_v<T, std::string>) return df; return std::nullopt; }
		template<class b> void operator()(const b&) const
		{
			//static_assert(false, "missing variant type");
		}
	};
	template<typename T = unsigned long> auto extractVal(PacketVariant& ref)
	{
		return std::visit(ExtractPacketVar<T>(), ref).value_or(T{ 0 });
	}
}
namespace OModelE = Origins::Models::Enum;


