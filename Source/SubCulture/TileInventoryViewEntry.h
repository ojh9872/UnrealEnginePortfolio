// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewDataWrapper.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "TileInventoryViewEntry.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileInventoryViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	virtual void NativeOnListItemObjectSet(UObject* listItemObject) override;

    FInventoryTileData inventoryTileData;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_ItemGrade;

    UFUNCTION(BlueprintCallable, Category = "InventoryTileData")
    EItemGrade GetItemGrade() const;

    UFUNCTION(BlueprintCallable, Category = "InventoryTileData")
    int32 GetItemCount() const;

    UFUNCTION(BlueprintCallable, Category = "InventoryTileData")
    EInventoryItemCategory GetItemCategory() const;
};
