module;
import <concepts>;
export module iCrypter;


// Avoiding pimpl implementation with templating
// and using std::is_convertible_v
export class ICrypter
{
	public:
		template <typename T> void Encrypt([[maybe_unused]] T& val) { return; }
		template <typename T> void Decrypt([[maybe_unused]] T& val) { return; }
};	



// Add in to conecpts namespace
export namespace Concepts
{
	template <typename T> concept HasCrypterInterface = std::is_convertible_v<T, ICrypter>;
}
