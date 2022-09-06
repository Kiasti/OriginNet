module;

export module iArchiver;
export import Concept;

export class IArchiver
{
	public:
		[[nodiscard]] bool IsOverflow([[maybe_unused]] const size_t nSize) const {
			return true;
		}
		virtual void Grow() = 0;

		template <typename T> void CheckBuff([[maybe_unused]] const T& data) 
			requires(Concepts::IsStdArray<T> || Concepts::IsStdVector<T> || Concepts::IsStdMap<T> || Concepts::IsStdString<T>)
		{
		}
		template <typename T, size_t N> void CheckBuff([[maybe_unused]] T(&a)[N]) requires (std::is_array_v<T[N]>)
		{
		}
		template <typename T> void CheckBuff([[maybe_unused]] const T& data) requires(Concepts::IsCharArr<T>)
		{
		}
		template <typename T> void CheckBuff([[maybe_unused]] const T& data) requires(std::is_arithmetic_v<T>)
		{
		}

		template <typename T, size_t N> requires std::is_array_v<T[N]> IArchiver& operator<<([[maybe_unused]] T(&a)[N])
		{
			return *this;
		}
		template <typename T> requires Concepts::IsCharArr<T> || std::is_arithmetic_v<T> IArchiver & operator<<([[maybe_unused]] const T & data)
		{
			return *this;
		}

		template <typename ...Args> IArchiver& Add([[maybe_unused]] Args... arg)
		{
			return *this;
		}

		template <typename T>  IArchiver& operator<<([[maybe_unused]] const T& values) requires(Concepts::IsStdArray<T> || Concepts::IsStdVector<T> || Concepts::IsStdMap<T> || Concepts::IsStdString<T>)
		{
			return *this;
		}
};