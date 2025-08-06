// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewContainer.h"
#include "TileCharacterView.generated.h"

class UCheckBox;
enum class EGunCategory : uint8;

/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileCharacterView : public UTileViewContainer
{
	GENERATED_BODY()

private:
    TSet<EGunCategory> activeFilters;

    void LoadCharacterData();
    void UpdateActiveFilters(EGunCategory category, bool isAdd);
    void OnCheckChanged(bool isChecked, EGunCategory category);

    UFUNCTION()
    void OnCheckAllChanged(bool isChecked);
    UFUNCTION()
    void OnCheckARChanged(bool isChecked);
    UFUNCTION()
    void OnCheckSMGChanged(bool isChecked);
    UFUNCTION()
    void OnCheckSGChanged(bool isChecked);
    UFUNCTION()
    void OnCheckSRChanged(bool isChecked);
    UFUNCTION()
    void OnCheckRLChanged(bool isChecked);
    UFUNCTION()
    void OnCheckMGChanged(bool isChecked);

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    virtual void SetCurrentSortType(ETileSortType sortType) override;
    virtual void SetIsDescending(bool isTrue) override;
    virtual bool CompareTileData(const UTileViewDataWrapper* A, const UTileViewDataWrapper* B) const override;
    virtual void ApplyFilter() override;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_All;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_AR;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_SMG;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_SG;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_SR;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_RL;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_MG;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
    UDataTable* CharacterDataTable;
};
