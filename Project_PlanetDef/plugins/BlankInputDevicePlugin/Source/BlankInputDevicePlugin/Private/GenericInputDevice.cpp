// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
 
#include "BlankInputDevicePluginPrivatePCH.h"
#include "../Public/GenericInputDevice.h"
#include "../Public/HIDFunctionLibrary.h"
#include "IInputInterface.h"
 

const FKey FCustomControllerInputs::LeftDial("LeftDial");
const FKey FCustomControllerInputs::RightDial("RightDial");
const FKey FCustomControllerInputs::Slider("Slider");
const FKey FCustomControllerInputs::ControllerButton1("CustomControllerButton1");
const FKey FCustomControllerInputs::ControllerButton2("CustomControllerButton2");
const FKey FCustomControllerInputs::ControllerButton3("CustomControllerButton3");
const FKey FCustomControllerInputs::ControllerButton4("CustomControllerButton4");
const FKey FCustomControllerInputs::ControllerButton5("CustomControllerButton5");


 
FGenericInputDevice::FGenericInputDevice(const 
TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{
	UE_LOG(LogTemp, Warning, TEXT("Enumerating HIDs"));

	TArray<FHIDDeviceInfo> DeviceInfos;
	UHIDFunctionLibrary::EnumerateHIDDevices(DeviceInfos, 0x1209, 0xedda);
	if (DeviceInfos.Num())
	{
		CurrentDevice = UHIDFunctionLibrary::OpenHIDDevice(0x1209, 0xedda);

	}
	else
	{
		CurrentDevice = nullptr;
	}
}
 
 
FGenericInputDevice::~FGenericInputDevice()
{
	// Close your device here
	UE_LOG(LogTemp, Warning, TEXT("Closing Current HID "));

	if ((CurrentDevice) && CurrentDevice->IsValidLowLevel())
	{
		CurrentDevice->ConditionalBeginDestroy();
		CurrentDevice = nullptr;
	}
}
 
 
void FGenericInputDevice::Tick(float DeltaTime)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}
 
 
void FGenericInputDevice::SendControllerEvents()
{

	if (!CurrentDevice->IsValidLowLevel())
	{
		return;
	}
	// Poll your device here and fire off events related to its current state
	TArray<uint8_t> InputReport;
	if (CurrentDevice->ReadInputReport(InputReport) != EHRR_ReadOK)
	{
		return;
	}
	switch (InputReport[0])
	{
	case 1:
	{
		float AxisValue = ((((signed short)InputReport[2]) << 8) | InputReport[1]) / 2048.0f;
		MessageHandler->OnControllerAnalog(FGamepadKeyNames::LeftAnalogX, 0, AxisValue-1);
		float AxisValue2 = ((((signed short)InputReport[4]) << 8) | InputReport[3]) / -2048.0f;
		MessageHandler->OnControllerAnalog(FGamepadKeyNames::LeftAnalogY, 0, AxisValue2+1 );
	}

		break;
	case 2:
	{
		float AxisValue = ((((signed short)InputReport[2]) << 8) | InputReport[1]) / 2048.0f;
		MessageHandler->OnControllerAnalog(FGamepadKeyNames::RightAnalogX, 0, AxisValue - 1);
		float AxisValue2 = ((((signed short)InputReport[4]) << 8) | InputReport[3]) / -2048.0f;
		MessageHandler->OnControllerAnalog(FGamepadKeyNames::RightAnalogY, 0, AxisValue2 + 1);
	}
	break;
	case 3:
	{
		float AxisValue = ((((signed short)InputReport[2]) << 8) | InputReport[1]) /*/ 2048.0f*/;
		MessageHandler->OnControllerAnalog(FName("Slider"), 0, AxisValue );
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%d"), InputReport[1]));
	}
	break;
	case 4:
	{
		float AxisValue = InputReport[1] & 0x1;
		MessageHandler->OnControllerAnalog(FName("CustomControllerButton1"), 0, AxisValue);
		
		AxisValue = (InputReport[1] & (0x1 <<1)) >>1;
		MessageHandler->OnControllerAnalog(FName("CustomControllerButton2"), 0, AxisValue);
		
		AxisValue = (InputReport[1] & (0x1 << 2)) >> 2;
		MessageHandler->OnControllerAnalog(FName("CustomControllerButton3"), 0, AxisValue);
		
		AxisValue = (InputReport[1] & (0x1 << 3)) >> 3;
		MessageHandler->OnControllerAnalog(FName("CustomControllerButton4"), 0, AxisValue);
		
		AxisValue = (InputReport[1] & (0x1 << 4)) >> 4;
		MessageHandler->OnControllerAnalog(FName("CustomControllerButton5"), 0, AxisValue);
	}
	break;
	case 8:
	{
		float LeftDialValue = ((((signed short)InputReport[2]) << 8) | InputReport[1]) /*/ 2048.0f*/;
		MessageHandler->OnControllerAnalog(FName("RightDial"), 0, LeftDialValue);
		float RightDialValue = ((((signed short)InputReport[4]) << 8) | InputReport[3]) /*/ 2048.0f*/;
		MessageHandler->OnControllerAnalog(FName("LeftDial"), 0, RightDialValue);

	}
	default:
		break;
	}
	
}
 
 
void FGenericInputDevice::SetMessageHandler(const TSharedRef< 
FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
	UE_LOG(LogTemp, Warning, TEXT("MessageHandler Set"));

}
 
 
bool FGenericInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
	return false;
}
 
 
void FGenericInputDevice::SetChannelValue(int32 ControllerId, 
FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}
 
 
void FGenericInputDevice::SetChannelValues(int32 ControllerId, const 
FForceFeedbackValues &values)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}
