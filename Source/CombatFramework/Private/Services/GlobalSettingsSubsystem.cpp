// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameframework/GameUserSettings.h"
#include "Services/GlobalSettingsSubsystem.h"

void UGlobalSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	gameSettings = GEngine->GameUserSettings; // Initialize game user settings object
	targetLockZoomOutDistance = 1.0f;
}

void UGlobalSettingsSubsystem::Deinitialize()
{

}

void UGlobalSettingsSubsystem::UpdateScreenResolution(EScreenResolution screenResolution)
{
	FIntPoint resolution;

	switch (screenResolution)
	{
	case EScreenResolution::_1200x720:
		resolution.X = 1200;
		resolution.Y = 720;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1200x800:
		resolution.X = 1200;
		resolution.Y = 800;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1280x720:
		resolution.X = 1280;
		resolution.Y = 720;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1280x800:
		resolution.X = 1280;
		resolution.Y = 800;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1280x1024:
		resolution.X = 1280;
		resolution.Y = 1024;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1366x768:
		resolution.X = 1366;
		resolution.Y = 768;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1600x900:
		resolution.X = 1600;
		resolution.Y = 900;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1920x1080:
		resolution.X = 1920;
		resolution.Y = 1080;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_1920x1200:
		resolution.X = 1920;
		resolution.Y = 1200;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_2560x1440:
		resolution.X = 2560;
		resolution.Y = 1440;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_2560X1600:
		resolution.X = 2560;
		resolution.Y = 1600;
		gameSettings->SetScreenResolution(resolution);
		break;
	case EScreenResolution::_3840x2160:
		resolution.X = 3840;
		resolution.Y = 2160;
		gameSettings->SetScreenResolution(resolution);
		break;
	default:
		break;
	}
	// Apply & save
	SaveSettings();
}

void UGlobalSettingsSubsystem::UpdateFrameLimit(EFrameLimit frameLimit, const int customLimit)
{
	if (frameLimit == EFrameLimit::Custom)
	{
		gameSettings->SetFrameRateLimit(static_cast<float>(UKismetMathLibrary::Clamp(customLimit, 1, 300)));
	}
	else
	{
		switch (frameLimit)
		{
		case EFrameLimit::FPS_30:
			gameSettings->SetFrameRateLimit(30);
			break;
		case EFrameLimit::FPS_60:
			gameSettings->SetFrameRateLimit(60);
			break;
		case EFrameLimit::FPS_90:
			gameSettings->SetFrameRateLimit(90);
			break;
		case EFrameLimit::FPS_120:
			gameSettings->SetFrameRateLimit(120);
			break;
		case EFrameLimit::FPS_240:
			gameSettings->SetFrameRateLimit(240);
			break;
		case EFrameLimit::Custom:
			break;
		default:
			break;
		}
	}
	// Apply & save
	SaveSettings();
}

void UGlobalSettingsSubsystem::UpdatePixelResolutionScale(const int resolutionScale)
{
	// Initialize player controller reference
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Clamp input
	int c_resolutionScale = UKismetMathLibrary::Clamp(resolutionScale, 1, 200);
	
	// Format the console command string
	FString command = "r.ScreenPercentage ";
	FString value = FString::FromInt(c_resolutionScale);
	
	// Adjust screen resolution percentage
	playerController->ConsoleCommand(command + value);

	// Apply & save
	SaveSettings();
}

void UGlobalSettingsSubsystem::ToggleDynamicResolution(bool bUseDynamicResolution)
{
	gameSettings->SetDynamicResolutionEnabled(bUseDynamicResolution);
	SaveSettings();
}

void UGlobalSettingsSubsystem::ToggleVSync(bool bvsync)
{
	gameSettings->SetVSyncEnabled(bvsync);
	SaveSettings();
}

void UGlobalSettingsSubsystem::ResetGlobalDisplaySettings()
{
	UpdatePixelResolutionScale(100);
	UpdateFrameLimit(EFrameLimit::FPS_60, 0);
}

void UGlobalSettingsSubsystem::UpdateTargetLockZoomOutDistance(const float scale)
{
	targetLockZoomOutDistance = scale;
}

void UGlobalSettingsSubsystem::SaveSettings()
{
	gameSettings->ApplyResolutionSettings(true);
	gameSettings->ApplySettings(true);
	gameSettings->SaveSettings();
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.