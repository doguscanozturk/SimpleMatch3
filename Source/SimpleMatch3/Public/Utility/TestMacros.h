#pragma once

namespace TestMacros
{
	#define LogRed(s) \
	{\
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);\
	}
		
	#define LogBlue(s) \
	{\
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, s);\
	}
	
	#define LogYellow(s) \
	{\
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, s);\
	}
		
	#define LogGreen(s) \
	{\
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, s);\
	}

	#define DEBUG(str, ...) UE_LOG(LogTemp, Warning, TEXT("-" str), __VA_ARGS__)
}
