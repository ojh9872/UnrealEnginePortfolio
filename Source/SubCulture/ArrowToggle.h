// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArrowToggle.generated.h"

class UCheckBox;
/**
 * 
 */
UCLASS()
class SUBCULTURE_API UArrowToggle : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UCheckBox* CheckBox_Arrow;

	UPROPERTY(Transient, meta = (BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* AnimRotateUp;

	UPROPERTY(Transient, meta = (BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* AnimRotateDown;

private:
	UFUNCTION()
	void OnCheckChanged(bool isChecked);
};
