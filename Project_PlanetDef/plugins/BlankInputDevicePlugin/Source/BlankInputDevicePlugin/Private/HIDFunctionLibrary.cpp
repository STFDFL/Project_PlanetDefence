#include "BlankInputDevicePluginPrivatePCH.h"
#include "../Public/GenericHIDSupport.h"
#include "../Public/HidDeviceInfo.h"
#include "../Public/HidDevice.h"
#include "../Public/HIDFunctionLibrary.h"

int32 UHIDFunctionLibrary::ConvertHexStringToInteger(FString InInteger)
{
	return FParse::HexNumber(*InInteger);
}

void UHIDFunctionLibrary::EnumerateHIDDevices(TArray<FHIDDeviceInfo>& DeviceInfo, int32 VendorID, int32 ProductID)
{      
	hid_device_info* EnumeratedInfo = nullptr;
	EnumeratedInfo = hid_enumerate(VendorID, ProductID);
	while (EnumeratedInfo)
	{
		//Virtual devices have invalid vendor IDs
		if (EnumeratedInfo->vendor_id != 0x0) 
		{
			FHIDDeviceInfo Device = FHIDDeviceInfo(FString(ANSI_TO_TCHAR(EnumeratedInfo->path)),
				EnumeratedInfo->vendor_id, EnumeratedInfo->product_id,
				FString(EnumeratedInfo->serial_number),
				EnumeratedInfo->release_number,
				FString(EnumeratedInfo->manufacturer_string),
				FString(EnumeratedInfo->product_string),
				EnumeratedInfo->usage_page,     
				EnumeratedInfo->usage,
				EnumeratedInfo->interface_number);

			DeviceInfo.Add(Device);
		}
		EnumeratedInfo = EnumeratedInfo->next;
	}
	//cleanup
	hid_free_enumeration(EnumeratedInfo);
}

UHidDevice* UHIDFunctionLibrary::OpenHIDDevice(int32 VendorID, int32 ProductID, FString SerialNumber /*= FString()*/)
{
	UHidDevice* Device = NewObject<UHidDevice>();
	Device->AddToRoot();
	auto dev = hid_open(VendorID, ProductID, SerialNumber.Len() > 0 ? *SerialNumber : nullptr);
	Device->Init(dev);
	return Device;
}

UHidDevice* UHIDFunctionLibrary::OpenHIDDeviceByPath(FString Path)
{
	UHidDevice* Device = NewObject<UHidDevice>();
	Device->Init(hid_open_path(Path.Len() > 0 ? TCHAR_TO_ANSI(*Path ): nullptr));
	return Device;
}
