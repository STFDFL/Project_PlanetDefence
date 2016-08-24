#pragma once
#include "../GenericHIDSupport.h"
#include "../HidDevice.h"
#include "../HidDeviceInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StudioBoardFunctions.generated.h"
#define FLIP_SEGMENTS 1

#ifdef FLIP_SEGMENTS
enum LCDSegments
{
	Segment_D = 1 << 0,
	Segment_E = 1 << 1,
	Segment_F = 1 << 2,
	Segment_A = 1 << 3,
	Segment_B = 1 << 4,
	Segment_C = 1 << 5,
	Segment_G = 1 << 6
};
#else
enum LCDSegments
{
	Segment_A = 1 << 0,
	Segment_B = 1 << 1,
	Segment_C = 1 << 2,
	Segment_D = 1 << 3,
	Segment_E = 1 << 4,
	Segment_F = 1 << 5,
	Segment_G = 1 << 6
};
#endif

UENUM(BlueprintType)
enum LCDDigits 
{
	Digit_0,
	Digit_1,
	Digit_2,
	Digit_3,
	Digit_4,
	Digit_5,
	Digit_6,
	Digit_7,
	Digit_8,
	Digit_9,
	Digit_A,
	Digit_B,
	Digit_C,
	Digit_D,
	Digit_E,
	Digit_F,
	Digit_G,
	Digit_H,
	Digit_I,
	Digit_J,
	Digit_L,
	Digit_N,
	Digit_O,
	Digit_P,
	Digit_Q,
	Digit_R,
	Digit_S,
	Digit_U,
	Digit_Y
};

uint8 GetValueForDigit(LCDDigits InDigit)
{
	switch (InDigit)
	{
	case Digit_0: return Segment_A + Segment_B + Segment_C + Segment_D + Segment_E + Segment_F;
	case Digit_1: return Segment_B + Segment_C;
	case Digit_2: return Segment_A + Segment_B + Segment_G + Segment_E + Segment_D;
	case Digit_3: return Segment_A + Segment_B + Segment_G + Segment_C + Segment_D;
	case Digit_4: return Segment_F + Segment_G + Segment_B + Segment_C;
	case Digit_5: return Segment_A + Segment_F + Segment_G + Segment_C + Segment_D;
	case Digit_6: return Segment_A + Segment_F + Segment_G + Segment_C + Segment_D + Segment_E;
	case Digit_7: return Segment_A + Segment_B + Segment_C;
	case Digit_8: return Segment_A + Segment_B + Segment_C + Segment_D + Segment_E + Segment_F + Segment_G;
	case Digit_9: return Segment_A + Segment_B + Segment_C + Segment_F + Segment_G;
	case Digit_A: return Segment_A + Segment_B + Segment_C + Segment_E + Segment_F + Segment_G;
	case Digit_B: return Segment_C + Segment_D + Segment_E + Segment_F + Segment_G;
	case Digit_C: return Segment_A + Segment_D + Segment_E + Segment_F;
	case Digit_D: return Segment_B + Segment_C + Segment_D + Segment_E + Segment_G;
	case Digit_E: return Segment_A + Segment_B + Segment_C + Segment_D + Segment_E + Segment_F + Segment_G;
	case Digit_F: return Segment_A + Segment_D + Segment_E + Segment_F + Segment_G;
	case Digit_G: return Segment_A + Segment_B + Segment_C + Segment_D + Segment_F + Segment_G;
	case Digit_H: return Segment_B + Segment_C + Segment_E + Segment_F + Segment_G;
	case Digit_I: return Segment_C;
	case Digit_J: return Segment_B + Segment_C + Segment_D;
	case Digit_L: return Segment_D + Segment_E + Segment_F;
	case Digit_N: return Segment_C + Segment_E + Segment_G;
	case Digit_O: return Segment_A + Segment_B + Segment_C + Segment_D + Segment_E + Segment_F;
	case Digit_P: return Segment_A + Segment_B + Segment_E + Segment_F + Segment_G;
	case Digit_Q: return Segment_A + Segment_B + Segment_C + Segment_F + Segment_G;
	case Digit_R: return Segment_E + Segment_G;
	case Digit_S: return Segment_A + Segment_C + Segment_D + Segment_F + Segment_G;
	case Digit_U: return Segment_B + Segment_C + Segment_D + Segment_E + Segment_F;
	case Digit_Y: return Segment_B + Segment_C + Segment_D + Segment_F + Segment_G;
	default:
		return 0xff;
	}
}
/*

0 a+b+c+d+e+f
1 b+c
2 a+b+G+e+d
3 a+b+g+c+d
4 f+g+b+c
5 a+f+g+c+d
6 a+f+g+c+d+e
7 a+b+c
8 a+b+c+d+e+f+g
9 a+b+c+f+g
A a+b+c+e+f+g
b c+d+e+f+g
C a+d+e+f
d b+c+d+e+g
E a+b+c+d+e+f+g
F a+d+e+f+g
G a+b+c+d+f+g
H b+c+e+f+g
I c
J b+c+d
L d+e+f
N c+e+g
0 a+b+c+d+e+f
P a+b+e+f+g
Q a+b+c+f+g
r e+g
S a+c+d+f+g
U b+c+d+e+f
Y b+c+d+f+g


orientation:
vertical
a swap d
e swap f 
c swap b
horizontal
f swap b
c swap e


*/


USTRUCT(BlueprintType, Blueprintable)
struct FSevenSegmentData
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnableDigit1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnableDigit2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnableDigit3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnableDigit4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<LCDDigits> Digit1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<LCDDigits> Digit2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<LCDDigits> Digit3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<LCDDigits> Digit4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot2; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot3; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot4; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot5; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot6; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot7; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Dot8;

	
};

UCLASS()
class  UStudioBoardFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Display)
		static void SetDisplayData(UHidDevice* Device, FSevenSegmentData SevenSegmentData)
	{
		
		TArray<uint8> MyData;
#ifdef FLIP_SEGMENTS
		
		
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit4)); 
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit3));
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit2));
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit1));
#else
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit1));
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit2));
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit3));
		MyData.Add(GetValueForDigit(SevenSegmentData.Digit4));
#endif
		MyData.Add((uint8)SevenSegmentData.Dot8 << 7 |
			(uint8)SevenSegmentData.Dot7 << 6 |
			(uint8)SevenSegmentData.Dot6 << 5 |
			(uint8)SevenSegmentData.Dot5 << 4 |
			(uint8)SevenSegmentData.Dot4 << 3 |
			(uint8)SevenSegmentData.Dot3 << 2 |
			(uint8)SevenSegmentData.Dot2 << 1 |
			(uint8)SevenSegmentData.Dot1
		);
		MyData.Add((uint8)SevenSegmentData.EnableDigit1 |
			(uint8)SevenSegmentData.EnableDigit2 << 1 |
			(uint8)SevenSegmentData.EnableDigit3 << 2 |
			(uint8)SevenSegmentData.EnableDigit4 << 3
		);
		Device->SendOutputReport(MyData, 7);
	}
	UFUNCTION(BlueprintCallable, Category = LEDs)
		static void SetLEDColour(UHidDevice* Device, FColor LED1Colour, FColor LED2Colour, FColor LED3Colour, FColor LED4Colour)
	{
		TArray<uint8> LEDColourData;
		LEDColourData.Add(FMath::Clamp<uint8>(LED1Colour.R * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED1Colour.G * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED1Colour.B * 255, 0, 255));

		LEDColourData.Add(FMath::Clamp<uint8>(LED2Colour.R * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED2Colour.G * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED2Colour.B * 255, 0, 255));

		LEDColourData.Add(FMath::Clamp<uint8>(LED3Colour.R * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED3Colour.G * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED3Colour.B * 255, 0, 255));

		LEDColourData.Add(FMath::Clamp<uint8>(LED4Colour.R * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED4Colour.G * 255, 0, 255));
		LEDColourData.Add(FMath::Clamp<uint8>(LED4Colour.B * 255, 0, 255));
		Device->SendOutputReport(LEDColourData, 5);
	}
};
