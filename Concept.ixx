module;

export import <string>;
export import <map>;
export import <vector>;
export import <unordered_map>;
export import <concepts>;

export module Concept;
export import TypeMetadata;

export namespace std
{
	export std::string to_string(const std::string& str) { return str; }
	export std::string to_string(const char* str) { return str; }
}

export namespace Concepts
{
	constexpr char stx = '\02';
	constexpr char etx = '\03';
	constexpr char epp = '\05';
	constexpr char dle = '\10';
	constexpr char stxdle[]{ 02, 10 };
	
	template <typename T> using DeRefPtr = std::remove_const_t<std::remove_pointer_t<T>>;
	template <typename T> concept IsCharArr = std::is_pointer_v<T> && std::is_same_v<char, DeRefPtr<T>>;

	template <typename> struct GetArrSizeT;
	template <typename T, size_t N> struct GetArrSizeT<std::array<T, N>> { constexpr static size_t size = N; };
	
	template <typename T> concept IsStdArray = std::is_same_v<T, std::array<typename T::value_type, GetArrSizeT<T>::size>>;
	template <typename T> concept IsStdString = std::is_same_v<std::string, T>;
	template <typename T> concept IsStdVector = std::is_same_v<T, std::vector<typename T::value_type, typename T::allocator_type>>;
	
	template <typename T> concept IsStdMap = std::same_as<T, std::map<typename T::key_type, typename T::mapped_type, typename T::key_compare, typename T::allocator_type>>;
	template <typename T> concept IsStdHashMap = 
		std::same_as<T, std::unordered_map<typename T::key_type, typename T::mapped_type, typename T::hasher, typename T::key_equal, typename T::allocator_type>>;
	
	template <typename T> concept IsAnyStdMap = IsStdHashMap<T> || IsStdMap<T>;
}
