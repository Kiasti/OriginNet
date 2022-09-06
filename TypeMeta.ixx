module;

#include "Packet.hpp"
import <unordered_map>;
import <vcruntime_typeinfo.h>;

export module TypeMetadata;

export namespace MetaTypes
{
	/**
	 *	@brief	Static class that just holds a map of the meta information.
	 */
	class Info
	{
		using MetaMap = std::unordered_map<size_t, OModelE::DataType>;
		public:
		static MetaMap info;

		/**
		 *	@brief	Looks up the hash id to return the packet type associated with it.
		 *	@param	hashId the Id to look for.
		 *	@return	returns a value of OModelE::DataType.
		 *
		 *	@see OModelE::DataType
		 */
		static OModelE::DataType GetDataType(const size_t hashId)
		{
			if (const auto iter = info.find(hashId); iter != info.end())
				return iter->second;
			return OModelE::DataType::NotValid;
		}

		/**
		 *	@brief	Inserts the pair combo hashid and OModelE::DataType
		 *	@param	hashId the hashid (key)
		 *	@param	dt The value to insert in to the map.
		 *
		 *	@see	OModelE::DataType
		 */
		static void Insert(const size_t hashId, OModelE::DataType dt)
		{
			info.insert_or_assign(hashId, dt);
		}
	};
	template <typename T> void ImplementType(const OModelE::DataType dt) {
		Info::Insert(typeid(T).hash_code(), dt);
	}

	template <typename T> struct GenerateMetaInfo
	{
		explicit GenerateMetaInfo(const OModelE::DataType dt) {
			Info::Insert(typeid(T).hash_code(), dt);
		}
		static OModelE::DataType GetPacketType() {
			return Info::GetDataType(typeid(T).hash_code());
		}
	};

	// Create inline metainfo
	inline GenerateMetaInfo<std::string> String(OModelE::DataType::String);
	inline GenerateMetaInfo<short> Int16(OModelE::DataType::Int16);
	inline GenerateMetaInfo<long> Int32(OModelE::DataType::Int32);
	inline GenerateMetaInfo<long long> Int64(OModelE::DataType::Int64);
	inline GenerateMetaInfo<char> Byte(OModelE::DataType::Byte);
	inline GenerateMetaInfo<unsigned short> UInt16(OModelE::DataType::UInt16);
	inline GenerateMetaInfo<unsigned long> UInt32(OModelE::DataType::UInt32);
	inline GenerateMetaInfo<unsigned long long> UInt64(OModelE::DataType::UInt64);
	inline GenerateMetaInfo<unsigned char> UByte(OModelE::DataType::UByte);
	inline GenerateMetaInfo<float> Float(OModelE::DataType::Float);
	inline GenerateMetaInfo<double> Double(OModelE::DataType::Double);

	/**
	 *	@brief	Struct that contains the packet id for type T
	 *	@tparam	T Any type as the packet type can return notvalid.
	 */
	template <typename T> struct MetaInfo
	{
		OModelE::DataType type;
		MetaInfo() {
			type = Info::GetDataType(typeid(T).hash_code());
		}
	};
}


// todo : clang implementations

