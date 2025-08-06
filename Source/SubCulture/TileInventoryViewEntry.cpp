// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryViewEntry.h"
#include "Components/WidgetSwitcher.h"

void UTileInventoryViewEntry::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTileInventoryViewEntry::NativeDestruct()
{
    Super::NativeDestruct();
}

void UTileInventoryViewEntry::NativeOnListItemObjectSet(UObject* listItemObject)
{
    UInventoryTileViewDataWrapper* inventoryTileDataWrapper = Cast<UInventoryTileViewDataWrapper>(listItemObject);
    if (inventoryTileDataWrapper)
    {
        inventoryTileData = inventoryTileDataWrapper->inventoryData;
        if (WidgetSwitcher_ItemGrade)
        {
            WidgetSwitcher_ItemGrade->SetActiveWidgetIndex(static_cast<int32>(inventoryTileData.grade));
        }
    }
}

EItemGrade UTileInventoryViewEntry::GetItemGrade() const
{
	return inventoryTileData.grade;
}

int32 UTileInventoryViewEntry::GetItemCount() const
{
	return inventoryTileData.count;
}

EInventoryItemCategory UTileInventoryViewEntry::GetItemCategory() const
{
	return inventoryTileData.category;
}