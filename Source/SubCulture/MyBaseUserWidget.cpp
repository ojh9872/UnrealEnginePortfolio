// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseUserWidget.h"

void UMyBaseUserWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UMyBaseUserWidget::NativeDestruct()
{
    Super::NativeDestruct();
}

void UMyBaseUserWidget::SetActive(bool bIsActive)
{
    if (bIsActive == true)
    {
        OnActivated();
    }
    else
    {
        OnDeactivated();
    }
}