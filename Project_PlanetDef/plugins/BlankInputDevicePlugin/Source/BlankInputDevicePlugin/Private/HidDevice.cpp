#include "BlankInputDevicePluginPrivatePCH.h"

#include "../Public/GenericHIDSupport.h"
#include "../Public/HidDevice.h"

void UHidDevice::SendOutputReport(TArray<uint8> Data, uint8 ReportNumber)
{

	UE_LOG(LogTemp, Warning, TEXT("Sending Output Report"));
	if (!IsValid())
	{
		return;
	}
	Data.Insert(ReportNumber, 0);
	hid_write(DeviceHandle, Data.GetData(), Data.Num());
}

EHIDReadResult UHidDevice::ReadInputReport(TArray<uint8>& ReportBuffer)
{
	UE_LOG(LogTemp, Warning, TEXT("Reading Input Report"));

	if (!IsValid())
	{
		return EHRR_ReadErr;
	}
	unsigned char RawBuffer[64] = { 0 };
	int32 BytesRead = hid_read(DeviceHandle, RawBuffer, 64);
	switch (BytesRead)
	{
	case -1:
		return EHRR_ReadErr;
		break;
	case 0:
		return EHRR_ReadNone;
		break;
	default:
		ReportBuffer.Empty();
		for (unsigned char ReportByte : RawBuffer)
		{
			ReportBuffer.Add(ReportByte);
		}
		return EHRR_ReadOK;
		break;
	}
}

bool UHidDevice::SendFeatureReport( TArray<uint8> Data, int32 FeatureNumber)
{
	if (!IsValid())
	{
		return false;
	}
	Data.Insert(FeatureNumber, 0);
	return (hid_send_feature_report(DeviceHandle, Data.GetData(), Data.Num()) != -1);

}

EHIDReadResult UHidDevice::ReadFeatureReport(TArray<uint8>& ReportBuffer, uint8 ReportID /*= 0*/)
{
	if (!IsValid())
	{
		return EHRR_ReadErr;
	}

	ReportBuffer.Insert(ReportID, 0);
	
	int32 BytesRead = hid_get_feature_report(DeviceHandle, ReportBuffer.GetData(), 64);
	switch (BytesRead)
	{
	case -1:
		return EHRR_ReadErr;
		break;
	case 0:
		return EHRR_ReadNone;
		break;
	default:
		ReportBuffer.Empty();
		for (unsigned char ReportByte : ReportBuffer)
		{
			ReportBuffer.Add(ReportByte);
		}
		return EHRR_ReadOK;
		break;
	}
}

void UHidDevice::CloseDevice()
{
	UE_LOG(LogTemp, Warning, TEXT("Closing Device"));

	if (!IsValid())
	{
		return;
	}

	hid_close(DeviceHandle);
}

EHIDReadResult UHidDevice::GetManufacturerString(FString& ManufacturerString)
{
	
	if (!IsValid())
	{
		return EHRR_ReadErr;
	}

	wchar_t RawString[128] = { 0 };
	switch (hid_get_manufacturer_string(DeviceHandle, RawString, 128))
	{
		case -1:
			ManufacturerString.Empty();
			return EHRR_ReadErr;
			break;
		default:
			ManufacturerString = FString(RawString);
			return EHRR_ReadOK;
			break;
	}
}

EHIDReadResult UHidDevice::GetProductString(FString& ProductString)
{
	
	if (!IsValid())
	{
		return EHRR_ReadErr;
	}

	wchar_t RawString[128] = { 0 };
	switch (hid_get_product_string(DeviceHandle, RawString, 128))
	{
	case -1:
		ProductString.Empty();
		return EHRR_ReadErr;
		break;
	default:
		ProductString = FString(RawString);
		return EHRR_ReadOK;
		break;
	}
}

EHIDReadResult UHidDevice::GetSerialNumberString(FString& SerialNumberString)
{
	if (!IsValid())
	{
		return EHRR_ReadErr;
	}


	wchar_t RawString[128] = { 0 };
	switch (hid_get_serial_number_string(DeviceHandle, RawString, 128))
	{
	case -1:
		SerialNumberString.Empty();
		return EHRR_ReadErr;
		break;
	default:
		SerialNumberString= FString(RawString);
		return EHRR_ReadOK;
		break;
	}
}

EHIDReadResult UHidDevice::GetStringByIndex(int32 Index, FString& IndexedString)
{
	
	if (!IsValid())
	{
		return EHRR_ReadErr;
	}

	wchar_t RawString[128] = { 0 };
	switch (hid_get_indexed_string(DeviceHandle, Index, RawString, 128))
	{
	case -1:
		IndexedString.Empty();
		return EHRR_ReadErr;
		break;
	default:
		IndexedString = FString(RawString);
		return EHRR_ReadOK;
		break;
	}
}

void UHidDevice::Init(hid_device* InDeviceHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("HID init"));

	DeviceHandle = InDeviceHandle;
}

void UHidDevice::BeginDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("HID Destroy"));

	CloseDevice();
	Super::BeginDestroy();
}
