// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowToggle.h"
#include "Components/CheckBox.h"

void UArrowToggle::NativeConstruct()
{
    Super::NativeConstruct();

    if (CheckBox_Arrow)
    {
        CheckBox_Arrow->OnCheckStateChanged.AddDynamic(this, &UArrowToggle::OnCheckChanged);
    }
}

void UArrowToggle::NativeDestruct()
{
    Super::NativeDestruct();
}

void UArrowToggle::OnCheckChanged(bool isChecked)
{
    if (true == isChecked)
    {
        if (AnimRotateUp)
        {
            PlayAnimation(AnimRotateUp);
        }
    }
    else
    {
        if (AnimRotateDown)
        {
            PlayAnimation(AnimRotateDown);
        }
    }
}