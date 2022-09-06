module;

export module iSerialize;
import iArchiver;


// Serializer
// In this case, we don't want template.
export class ISerialize
{
	public:
		virtual size_t GetSize() = 0;
		virtual IArchiver& Serialize(IArchiver& archive) = 0;
		virtual IArchiver& Deserialize(IArchiver& archive) = 0;
};


// Add in to namespace
export namespace Concepts
{
	template <typename T> concept HasSerializerInterface = std::is_convertible_v<T, ISerialize>;
}


