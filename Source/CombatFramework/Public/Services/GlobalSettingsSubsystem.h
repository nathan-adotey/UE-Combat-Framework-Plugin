// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once
#include "Data/CEnumerators.h"
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "GlobalSettingsSubsystem.generated.h"

UENUM()
enum class EFrameLimit : uint8
{
	FPS_30,
	FPS_60,
	FPS_90,
	FPS_120,
	FPS_240,
	Custom
};

UENUM()
enum class EScreenResolution : uint8
{
	_1200x720,
	_1200x800,
	_1280x720,
	_1280x800,
	_1280x1024,
	_1366x768,
	_1600x900,
	_1920x1080,
	_1920x1200,
	_2560x1440,
	_2560X1600,
	_3840x2160
};

// Forward declare necessary classes
class UGameUserSettings;

UCLASS()
class COMBATFRAMEWORK_API UGlobalSettingsSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (UIMin = "0.5", UIMax = "2.0", ClampMin = "0.5", ClampMax = "2.0"))
	float targetLockZoomOutDistance;

private:
	UGameUserSettings* gameSettings;

public:
	UFUNCTION(BlueprintCallable, Category = "Display")
	void UpdateScreenResolution(EScreenResolution screenResolution = EScreenResolution::_1920x1080);

	UFUNCTION(BlueprintCallable, Category = "Display")
	void UpdateFrameLimit(EFrameLimit frameLimit = EFrameLimit::FPS_60, const int customLimit = 0);

	UFUNCTION(BlueprintCallable, Category = "Display")
	void UpdatePixelResolutionScale(const int resolutionScale = 100);

	UFUNCTION(BlueprintCallable, Category = "Display")
	void ToggleDynamicResolution(bool bUseDynamicResolution = false);

	UFUNCTION(BlueprintCallable, Category = "Display")
	void ToggleVSync(bool bvsync = false);

	UFUNCTION(BlueprintCallable, Category = "Display")
	void ResetGlobalDisplaySettings();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpdateTargetLockZoomOutDistance(const float scale = 1.0f);

private:
	void SaveSettings();
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.