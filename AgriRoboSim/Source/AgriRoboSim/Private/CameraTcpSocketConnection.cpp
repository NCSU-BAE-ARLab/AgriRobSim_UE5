// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\CameraTcpSocketConnection.h"

void ACameraTcpSocketConnection::OnConnected(int32 connection)
{
	UE_LOG(LogTemp, Log, TEXT("Connected"));
}

void ACameraTcpSocketConnection::OnDisconnected(int32 ConId)
{
	UE_LOG(LogTemp, Log, TEXT("Disconnected"));
}

void ACameraTcpSocketConnection::OnMessageReceived(int32 ConId, TArray<uint8>& Message)
{
	while (Message.Num() != 0)
	{
		int32 MsgLength = Message_ReadInt(Message);
		if (MsgLength == -1)
		{
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::FromInt(MsgLength));
		if(!Message_ReadBytes(MsgLength, Message, MessageBytes))
		{
			UE_LOG(LogTemp, Log, TEXT("Failed to Read Bytes"));
			continue;
		}
		for (auto MessageByte : MessageBytes)
		{
			MessageString.AppendChar(MessageByte);
		}
		bool clear = MessageProcessImplementableEvent();
		if (clear)
		{
			CleanUpNativeEvent();
		}
		
	}
}

void ACameraTcpSocketConnection::ConnectToGameServer()
{
	if (isConnected(ConnectionIdGameServer))
	{
		UE_LOG(LogTemp, Error, TEXT("Already Connected"));
		return;
	}
	FTcpSocketDisconnectDelegate DisconnectDelegate;
	DisconnectDelegate.BindDynamic(this, &ACameraTcpSocketConnection::OnDisconnected);

	FTcpSocketConnectDelegate ConnectDelegate;
	ConnectDelegate.BindDynamic(this, &ACameraTcpSocketConnection::OnConnected);

	FTcpSocketReceivedMessageDelegate ReceivedMessageDelegate;
	ReceivedMessageDelegate.BindDynamic(this, &ACameraTcpSocketConnection::OnMessageReceived);

	Connect(IPAddr,Port,DisconnectDelegate,ConnectDelegate,ReceivedMessageDelegate,ConnectionIdGameServer);
}

void ACameraTcpSocketConnection::CleanUpNativeEvent_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *MessageString);
	MessageBytes.Empty();
	MessageString.Empty();
}

float ACameraTcpSocketConnection::DecodeToFloat(TArray<uint8> Message, int start, bool reverse)
{
	uint32_t CombinedByte;
	if (reverse)
		CombinedByte = (Message[start+3] << 24) | (Message[start+2] << 16) | (Message[start+1] << 8) | (Message[start]);
	else
		CombinedByte = (Message[start] << 24) | (Message[start+1] << 16) | (Message[start+2] << 8) | (Message[start+3]);
	UE_LOG(LogTemp, Warning, TEXT("%d"), CombinedByte);
	return *reinterpret_cast<float*>(&CombinedByte);
}
TArray<uint8> ACameraTcpSocketConnection::DecodeToBytes(float value, bool reverse)
{
	const uint8_t* Bytes = reinterpret_cast<uint8_t*>(&value);
	UE_LOG(LogTemp, Warning, TEXT("%d"), Bytes);
	TArray<uint8> RetBytes;
	if (reverse) {
		RetBytes.Add(Bytes[0]);
		RetBytes.Add(Bytes[1]);
		RetBytes.Add(Bytes[2]);
		RetBytes.Add(Bytes[3]);
	} else {
		RetBytes.Add(Bytes[3]);
		RetBytes.Add(Bytes[2]);
		RetBytes.Add(Bytes[1]);
		RetBytes.Add(Bytes[0]);
	}
	return RetBytes;
}


