// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyBaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUBCULTURE_API UMyBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "WidgetActive", DisplayName = "OnWidgetActivated")
    void OnActivated(); 

    UFUNCTION(BlueprintImplementableEvent, Category = "WidgetActive", DisplayName = "OnWidgetDeactivated")
    void OnDeactivated(); 

public:
    UFUNCTION(BlueprintCallable, Category = "WidgetActive")
    virtual void SetActive(bool bIsActive);
};
