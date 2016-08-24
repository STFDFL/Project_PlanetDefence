#pragma once
#include "HidDeviceInfo.generated.h"
USTRUCT(BlueprintType)
struct FHIDDeviceInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category= HID)
	FString DevicePath;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 VendorID;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 ProductID;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	FString SerialNumber;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 ReleaseNumber;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	FString ManufacturerString;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	FString ProductString;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 UsagePage;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 Usage;
	UPROPERTY(BlueprintReadOnly, Category= HID)
	int32 InterfaceNumber;
	

	FHIDDeviceInfo(FString InDevicePath, int32 InVendorID, int32 InProductID,
		FString InSerialNumber, int32 InReleaseNumber, FString InManufacturerString, FString InProductString,
		int32 InUsagePage, int32 InUsage, int32 InInterfaceNumber)
		:
		DevicePath(InDevicePath),
		VendorID(InVendorID),
		ProductID(InProductID),
		SerialNumber(InSerialNumber),
		ReleaseNumber(InReleaseNumber),
		ManufacturerString(InManufacturerString),
		ProductString(InProductString),
		UsagePage(InUsagePage),
		Usage(InUsage),
		InterfaceNumber(InInterfaceNumber)
	{};
	FHIDDeviceInfo()
		:
		DevicePath(FString()),
		VendorID(0),
		ProductID(0),
		SerialNumber(FString()),
		ReleaseNumber(0),
		ManufacturerString(FString()),
		ProductString(FString()),
		UsagePage(0),
		Usage(0),
		InterfaceNumber(0)
	{};

};

