export module buffer.Crypt;
export import iCrypter;




export class BufferXorCrypt : public ICrypter
{
	const unsigned char xorArr[7]{ 52, 252, 44, 21, 3, 125, 200 };
	
	public:
		template <typename T> void Encrpyt(T& val) { return; }
		template <typename T> void Decrypt(T& val) { return; }
};
