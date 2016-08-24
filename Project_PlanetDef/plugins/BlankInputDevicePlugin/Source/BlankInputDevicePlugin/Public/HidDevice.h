#pragma once
#include "GenericHIDSupport.h"
#include "HidDevice.generated.h"


UENUM(BlueprintType)
enum EHIDReadResult
{
	EHRR_ReadOK,
	EHRR_ReadNone,      
	EHRR_ReadErr
};


UCLASS(BlueprintType)
class UHidDevice: public UObject
{
	GENERATED_BODY()
public:
	~UHidDevice()
	{
		DeviceHandle = nullptr;
	}
	UFUNCTION(BlueprintCallable, Category = "HID")
	void SendOutputReport(TArray<uint8> Data, uint8 ReportNumber);
	
	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult ReadInputReport(TArray<uint8>& ReportBuffer);

	UFUNCTION(BlueprintCallable, Category = "HID")
	bool SendFeatureReport( TArray<uint8> Data, int32 FeatureNumber);
	
	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult ReadFeatureReport(TArray<uint8>& ReportBuffer, uint8 ReportID = 0);

	UFUNCTION(BlueprintCallable, Category = "HID")
	void CloseDevice();

	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult GetManufacturerString(FString& ManufacturerString);

	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult GetProductString(FString& ProductString);

	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult GetSerialNumberString(FString& SerialNumberString);

	UFUNCTION(BlueprintCallable, Category = "HID")
	EHIDReadResult GetStringByIndex(int32 Index, FString& IndexedString);


	UHidDevice()
		: DeviceHandle(nullptr) {};
	
	//this may need to be changed depending on whether the pointer can still go out of scope
	void Init(hid_device* InDeviceHandle);
	
	UFUNCTION(BlueprintCallable, Category = "HID")
	inline bool IsValid() { return DeviceHandle != nullptr; };

	virtual void BeginDestroy() override;

private:
	hid_device* DeviceHandle;
};