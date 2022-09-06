module;

export module sender;
export import ThreadSafeQueue;
export import buffer;
//export import iCrypter;


export class Sender
{
	
	TQueue<NetBuffer> outgoingPackets;



	public:
		Sender();
		~Sender();

		void AddPacket();
		void Send()
		{
			/*auto iResult = send(ConnectSocket, &buf[0], static_cast<int>(buf.length()), 0);
			if (iResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}

			printf("Bytes Sent: %d\n", iResult);

			// shutdown the connection since no more data will be sent
			iResult = shutdown(ConnectSocket, SD_SEND);
			if (iResult == SOCKET_ERROR)
			{
				printf("shutdown failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}
			*/
		}
};
