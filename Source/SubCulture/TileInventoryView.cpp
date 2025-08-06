// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInventoryView.h"
#include "TileShopView.h"
#include "TileCharacterView.h"
#include "GameEnums.h"
#include "Components/CheckBox.h"

void UTileInventoryView::NativeConstruct()
{
    Super::NativeConstruct();

    if (CheckBox_All)
    {
        CheckBox_All->OnCheckStateChanged.AddDynamic(this, &UTileInventoryView::OnCheckAllChanged);
    }

    if (CheckBox_Material)
    {
        CheckBox_Material->OnCheckStateChanged.AddDynamic(this, &UTileInventoryView::OnCheckMaterialChanged);
    }

    if (CheckBox_Consumable)
    {
        CheckBox_Consumable->OnCheckStateChanged.AddDynamic(this, &UTileInventoryView::OnCheckConsumableChanged);
    }

    if (CheckBox_Equipment)
    {
        CheckBox_Equipment->OnCheckStateChanged.AddDynamic(this, &UTileInventoryView::OnCheckEquipmentChanged);
    }

    LoadInventoryData();
}

void UTileInventoryView::NativeDestruct()
{
    Super::NativeDestruct();
}

void UTileInventoryView::LoadInventoryData()
{
    if (!InventoryDataTable)
    {
        return;
    }
    tileDataList.Empty();

    TArray<FInventoryTileData*> inventoryTileDataList;
    InventoryDataTable->GetAllRows<FInventoryTileData>(TEXT("LoadInventoryData"), inventoryTileDataList);

    for (const FInventoryTileData* data : inventoryTileDataList)
    {
        if (data)
        {
            UInventoryTileViewDataWrapper* inventoryTileWrapper = NewObject<UInventoryTileViewDataWrapper>(this);
            inventoryTileWrapper->Init(FInventoryTileData::StaticStruct(), data);
            tileDataList.Add(inventoryTileWrapper);
        }
    }

    ApplyFilter();
}

void UTileInventoryView::SetCurrentSortType(ETileSortType sortType)
{
    Super::SetCurrentSortType(sortType);
}

void UTileInventoryView::SetIsDescending(bool isTrue)
{
    Super::SetIsDescending(isTrue);
}

void UTileInventoryView::ApplyFilter()
{
    if (!TileView)
    {
        return;
    }

    TArray<UTileViewDataWrapper*> filteredTileDataList;
    if (activeFilters.Num() == 0 || activeFilters.Contains(EInventoryItemCategory::All) == true)
    {
        filteredTileDataList.Append(tileDataList);
    }
    else
    {
        for (UTileViewDataWrapper* data : tileDataList)
        {
            if (data)
            {
                if (UInventoryTileViewDataWrapper* InventoryWrapper = Cast<UInventoryTileViewDataWrapper>(data))
                {
                    if (activeFilters.Contains(InventoryWrapper->inventoryData.category) == true)
                    {
                        filteredTileDataList.Add(InventoryWrapper);
                    }
                }
            }
        }
    }

    filteredTileDataList.Sort([this](const UTileViewDataWrapper& first, const UTileViewDataWrapper& second)
        {
            return CompareTileData(&first, &second);
        });

    SetAndRefreshTileView(filteredTileDataList);
}

void UTileInventoryView::UpdateActiveFilters(EInventoryItemCategory category, bool isAdd)
{
    if (isAdd == true)
    {
        activeFilters.Add(category);
    }
    else
    {
        activeFilters.Remove(category);
    }

    if (activeFilters.IsEmpty() == true)
    {
        CheckBox_All->SetCheckedState(ECheckBoxState::Checked);
    }

    ApplyFilter();
}

bool UTileInventoryView::CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const
{
    const UInventoryTileViewDataWrapper* firstInventoryTileWrapper = Cast<UInventoryTileViewDataWrapper>(first);
    const UInventoryTileViewDataWrapper* secondInventoryTileWrapper = Cast<UInventoryTileViewDataWrapper>(second);
    if (!firstInventoryTileWrapper || !secondInventoryTileWrapper)
    {
        return false;
    }

    const FInventoryTileData& firstInventoryData = firstInventoryTileWrapper->inventoryData;
    const FInventoryTileData& secondInventoryData = secondInventoryTileWrapper->inventoryData;
    bool bResult = false;
    switch (currentSortType)
    {
    case ETileSortType::Grade:
        return isDescending ? firstInventoryData.grade < secondInventoryData.grade : secondInventoryData.grade < firstInventoryData.grade;
    default:
        return false;
    }
}

void UTileInventoryView::OnCheckAllChanged(bool isChecked)
{
    if (isChecked)
    {
        if (CheckBox_Material)
        {
            CheckBox_Material->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_Consumable)
        {
            CheckBox_Consumable->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_Equipment)
        {
            CheckBox_Equipment->SetCheckedState(ECheckBoxState::Unchecked);
        }

        activeFilters.Empty();
        activeFilters.Add(EInventoryItemCategory::All);
    }
    else
    {
        CheckBox_All->SetCheckedState(ECheckBoxState::Checked);
    }

    ApplyFilter();
}

void UTileInventoryView::OnCheckChanged(bool isChecked, EInventoryItemCategory category)
{
    if (isChecked == true
        && CheckBox_All
        && CheckBox_All->IsChecked() == true)
    {
        CheckBox_All->SetCheckedState(ECheckBoxState::Unchecked);
        activeFilters.Remove(EInventoryItemCategory::All);
    }

    UpdateActiveFilters(category, isChecked);
}

void UTileInventoryView::OnCheckMaterialChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EInventoryItemCategory::Material);
}

void UTileInventoryView::OnCheckConsumableChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EInventoryItemCategory::Consumable);
}

void UTileInventoryView::OnCheckEquipmentChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EInventoryItemCategory::Equipment);
}