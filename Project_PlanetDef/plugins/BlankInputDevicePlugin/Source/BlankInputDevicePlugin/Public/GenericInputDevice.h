#pragma once
//#include "InputInterface.h"
#include "IInputDevice.h"
#include  "../Public/HidDevice.h"

struct FCustomControllerInputs
{
	static const FKey LeftDial;
	static const FKey RightDial;
	static const FKey Slider;
	static const FKey ControllerButton1;
	static const FKey ControllerButton2;
	static const FKey ControllerButton3;
	static const FKey ControllerButton4;
	static const FKey ControllerButton5;

};


class FGenericInputDevice : public IInputDevice
{
public:
	FGenericInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& 
InMessageHandler);
	~FGenericInputDevice();
 
	/** Tick the interface (e.g. check for new controllers) */
	virtual void Tick(float DeltaTime) override;
 
	/** Poll for controller state and send events if needed */
	virtual void SendControllerEvents() override;
 
	/** Set which MessageHandler will get the events from SendControllerEvents. */
	virtual void SetMessageHandler(const TSharedRef< 
FGenericApplicationMessageHandler >& InMessageHandler) override;
 
	/** Exec handler to allow console commands to be passed through for debugging 
*/
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) 
override;
 
	/** IForceFeedbackSystem pass through functions **/
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType 
ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues 
&values) override;
 
private:
	/* Message handler */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
	UHidDevice* CurrentDevice;
};
