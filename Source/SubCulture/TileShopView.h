// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewContainer.h"
#include "TileViewDataWrapper.h"
#include "TileShopView.generated.h"

class UCheckBox;
/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileShopView : public UTileViewContainer
{
	GENERATED_BODY()

private:
    void LoadShopData();
    void SetOnlyOneCheckBoxChecked(UCheckBox* selectedCheckBox, EShopItemCategory shopItemCategory);

    UFUNCTION()
    void OnCheckNormalChanged(bool isChecked);
    UFUNCTION()
    void OnCheckMaterialChanged(bool isChecked);
    UFUNCTION()
    void OnCheckConsumableChanged(bool isChecked);
    UFUNCTION()
    void OnCheckEquipmentChanged(bool isChecked);

    TOptional<EShopItemCategory> activeCategory;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    virtual void SetCurrentSortType(ETileSortType sortType) override;
    virtual void SetIsDescending(bool isTrue) override;
    virtual bool CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const override;
    virtual void ApplyFilter() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopFilter")
    EShopItemCategory initCategory;
	
    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Normal;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Material;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Consumable;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CheckBox_Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopData")
    class UDataTable* shopDataTable;
};
