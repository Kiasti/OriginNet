module;
import <memory>;
import <vector>;
import <concepts>;
export module buffer;
export import buffer.Crypt;
export import iArchiver;




//class ICrypter;

export class NetBuffer : public std::vector<unsigned char>, IArchiver
{
	private:
		std::unique_ptr<ICrypter> cryptImpl;

		// rather than uchar8 vector:
		unsigned char* startPtr;
		unsigned char* endPtr;
		ptrdiff_t curWritePos;
		ptrdiff_t curReadPos;


	public:
		NetBuffer();
		~NetBuffer();

		template <typename T> NetBuffer& operator+=(T& val) requires(std::is_arithmetic_v<T>)
		{
			for (int i = 0; i < sizeof T; ++i)
				*reinterpret_cast<char*>(*val) = *reinterpret_cast<char*>(*val) ^ 20; // xor

			std::vector<unsigned char>::push_back(val);
			return *this;
		}

		[[nodiscard]] bool IsOverflow(const size_t nSize) const
		{
			return true;
			//return buffer.length() + nSize > buffer.capacity();
		}
		void Grow() override
		{
			//buffer.reserve(buffer.length() * 2);
		}


// buff chekc
		template <typename T> void CheckBuff(const T& data) requires(Concepts::IsStdArray<T> || Concepts::IsStdVector<T> ||
			Concepts::IsStdMap<T> || Concepts::IsStdString<T>)
		{
			bool overflow;
			if constexpr (Concepts::IsStdMap<T>)
				overflow = IsOverflow(data.size() * (sizeof(typename T::mapped_type) + sizeof(typename T::key_type)));
			else
				overflow = IsOverflow(data.size() * sizeof(typename T::value_type));
			if (overflow)
				Grow();
		}
		template <typename T, size_t N> void CheckBuff(T(&a)[N]) requires (std::is_array_v<T[N]>)
		{
			if (IsOverflow(sizeof std::remove_reference_t<decltype(std::declval<T>()[0])> *N))
				Grow();
		}
		template <typename T> void CheckBuff(const T& data) requires(Concepts::IsCharArr<T>)
		{
			if (IsOverflow(strlen(data) * sizeof(char)))
				Grow();
		}
		template <typename T> void CheckBuff(const T& data) requires(std::is_arithmetic_v<T>)
		{
			if (IsOverflow(sizeof(T)))
				Grow();
		}


// push in to buffer
		template <typename T, size_t N> requires std::is_array_v<T[N]> IArchiver& operator<<(T(&a)[N])
		{
			for (size_t i = 0; i < N; ++i)
			{
				CheckBuff<T>(a[i]);
				//buffer += std::to_string(a[i]);
			}
			return *this;
		}
		template <typename T> requires Concepts::IsCharArr<T> || std::is_arithmetic_v<T> IArchiver & operator<<(const T & data)
		{
			CheckBuff<T>(data);
			if constexpr (Concepts::IsCharArr<T>) {}
			else if constexpr (std::is_arithmetic_v<T>) {}
			//buffer += std::to_string(data);
			//std::cout << data << std::endl;
			return *this;
		}

		template <typename ...Args> IArchiver& Add(Args... arg)
		{
			((*this << arg), ...);
			return *this;
		}

		template <typename T>  IArchiver& operator<<(const T& values) requires(Concepts::IsStdArray<T> || Concepts::IsStdVector<T> || Concepts::IsStdMap<T> || Concepts::IsStdString<T>)
		{
			CheckBuff<T>(values);
			if constexpr (Concepts::IsStdMap<T>)
			{
				//for (auto begin = values.begin(); begin != values.end(); ++begin)
					//buffer += std::to_string(begin->first) + std::to_string(begin->second);
			}
		//	else
				//for (auto begin = values.begin(); begin != values.end(); ++begin)
					//std::cout << *begin << std::endl;
					//buffer += std::to_string(*begin);
			return *this;
		}


};