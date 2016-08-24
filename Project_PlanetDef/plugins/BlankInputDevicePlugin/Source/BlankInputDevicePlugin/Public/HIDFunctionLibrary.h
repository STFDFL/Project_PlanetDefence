#pragma once
#include "GenericHIDSupport.h"
#include "HidDevice.h"
#include "HidDeviceInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HIDFunctionLibrary.generated.h"
UCLASS()
 class  UHIDFunctionLibrary: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = HID, BlueprintPure)
	static int32 ConvertHexStringToInteger(FString InInteger);
	UFUNCTION(BlueprintCallable, Category = HID)
	static void EnumerateHIDDevices(TArray<FHIDDeviceInfo>& DeviceInfo, int32 VendorID = 0,int32 ProductID = 0);
	UFUNCTION(BlueprintCallable, Category = HID)
	static UHidDevice* OpenHIDDevice(int32 VendorID, int32 ProductID, FString SerialNumber = TEXT(""));
	UFUNCTION(BlueprintCallable, Category = HID)
	static UHidDevice* OpenHIDDeviceByPath(FString Path);
	
	UFUNCTION(BlueprintCallable, Category = HID)
	static FString ToString(const FHIDDeviceInfo& DeviceInfo)
	{
		return FString::Printf(TEXT("%d_%d UsagePage:%d Usage:%d InterfaceNumber:%d Manufacturer:%s Product:%s"), DeviceInfo.VendorID, DeviceInfo.ProductID, DeviceInfo.UsagePage, DeviceInfo.Usage, DeviceInfo.InterfaceNumber, *(DeviceInfo.ManufacturerString), *(DeviceInfo.ProductString));
	}
};

