// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
 
#include "BlankInputDevicePluginPrivatePCH.h"
#include "../Public/GenericInputDevice.h"
#include "../Public/GenericHIDSupport.h"
#include "../Public/HidDeviceInfo.h"
#include "../Public/HIDFunctionLibrary.h"
 
class FBlankInputDevicePlugin : public IBlankInputDevicePlugin
{
	/** Implements the rest of the IInputDeviceModule interface **/
 
	/** Creates a new instance of the IInputDevice associated with this 
IInputDeviceModule **/
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const 
TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
 
	/** Called right after the module DLL has been loaded and the module object 
has been created **/
	virtual void StartupModule() override;
 
	/** Called before the module is unloaded, right before the module object is 
destroyed. **/
	virtual void ShutdownModule() override;
};
 
IMPLEMENT_MODULE( FBlankInputDevicePlugin, BlankInputDevicePlugin )
 
 
TSharedPtr<class IInputDevice> FBlankInputDevicePlugin::CreateInputDevice(const 
TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(LogTemp, Warning, TEXT("Created new input device!"));
 
	// See GenericInputDevice.h for the definition of the IInputDevice we are 
//returning here
	return MakeShareable(new FGenericInputDevice(InMessageHandler));
}
 
 
void FBlankInputDevicePlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after 
//global variables are initialized, of course.)
	// Custom module-specific init can go here.
	UE_LOG(LogTemp, Warning, TEXT("Initializing Plugin"));

	hid_init();
	// IMPORTANT: This line registers our input device module with the engine.
	//	      If we do not register the input device module with the engine,
	//	      the engine won't know about our existence. Which means 
	//	      CreateInputDevice never gets called, which means the engine
	//	      will never try to poll for events from our custom input device.
	
IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), 
this);
FKeyDetails LeftDial(FCustomControllerInputs::LeftDial, FText::FromString(TEXT("Left Dial")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller"));
EKeys::AddKey(LeftDial);
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::RightDial, FText::FromString(TEXT("Right Dial")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::Slider, FText::FromString(TEXT("Slider")), (FKeyDetails::FloatAxis ) , FName("Custom Controller")));

EKeys::AddKey(FKeyDetails(FCustomControllerInputs::ControllerButton1, FText::FromString(TEXT("Custom Controller Button 1")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::ControllerButton2, FText::FromString(TEXT("Custom Controller Button 2")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::ControllerButton3, FText::FromString(TEXT("Custom Controller Button 3")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::ControllerButton4, FText::FromString(TEXT("Custom Controller Button 4")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));
EKeys::AddKey(FKeyDetails(FCustomControllerInputs::ControllerButton5, FText::FromString(TEXT("Custom Controller Button 5")), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey, FName("Custom Controller")));

}
 
 
void FBlankInputDevicePlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For 
//modules that support dynamic reloading,
	// we call this function before unloading the module.
 
	UE_LOG(LogTemp, Warning, TEXT("BlankInputDevicePlugin shut down!"));
	hid_exit();

	// Unregister our input device module
	
IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), 
this);
}
