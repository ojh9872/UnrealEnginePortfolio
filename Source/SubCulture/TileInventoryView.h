// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewContainer.h"
#include "TileInventoryView.generated.h"

class UCheckBox;
enum class EInventoryItemCategory :uint8;
/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileInventoryView : public UTileViewContainer
{
    GENERATED_BODY()

private:
    TSet<EInventoryItemCategory> activeFilters;

    void LoadInventoryData();
    void UpdateActiveFilters(EInventoryItemCategory category, bool isAdd);
    void OnCheckChanged(bool isChecked, EInventoryItemCategory category);

    UFUNCTION()
    void OnCheckAllChanged(bool isChecked);
    UFUNCTION()
    void OnCheckMaterialChanged(bool isChecked);
    UFUNCTION()
    void OnCheckConsumableChanged(bool isChecked);
    UFUNCTION()
    void OnCheckEquipmentChanged(bool isChecked);

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    virtual void SetCurrentSortType(ETileSortType sortType) override;
    virtual void SetIsDescending(bool isTrue) override;
    virtual bool CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const override;
    virtual void ApplyFilter() override;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_All;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Material;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Consumable;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryData")
    class UDataTable* InventoryDataTable;
};