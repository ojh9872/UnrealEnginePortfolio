// Fill out your copyright notice in the Description page of Project Settings.


#include "TileShopView.h"
#include "GameEnums.h"
#include "Components/CheckBox.h"

void UTileShopView::NativeConstruct()
{
    Super::NativeConstruct();

    if (CheckBox_Normal)
    {
        CheckBox_Normal->OnCheckStateChanged.AddDynamic(this, &UTileShopView::OnCheckNormalChanged);
        CheckBox_Normal->SetCheckedState(ECheckBoxState::Unchecked);
    }

    if (CheckBox_Material)
    {
        CheckBox_Material->OnCheckStateChanged.AddDynamic(this, &UTileShopView::OnCheckMaterialChanged);
        CheckBox_Material->SetCheckedState(ECheckBoxState::Unchecked);
    }

    if (CheckBox_Consumable)
    {
        CheckBox_Consumable->OnCheckStateChanged.AddDynamic(this, &UTileShopView::OnCheckConsumableChanged);
        CheckBox_Consumable->SetCheckedState(ECheckBoxState::Unchecked);
    }

    if (CheckBox_Equipment)
    {
        CheckBox_Equipment->OnCheckStateChanged.AddDynamic(this, &UTileShopView::OnCheckEquipmentChanged);
        CheckBox_Equipment->SetCheckedState(ECheckBoxState::Unchecked);
    }

    initCategory = EShopItemCategory::Normal;
    UCheckBox* initCheckBox = CheckBox_Normal;
    switch (initCategory)
    {
    case EShopItemCategory::Material:
        initCheckBox = CheckBox_Material;
        break;
    case EShopItemCategory::Consumable:
        initCheckBox = CheckBox_Consumable;
        break;
    case EShopItemCategory::Equipment:
        initCheckBox = CheckBox_Equipment;
        break;
    default:
        break;
    }

    if (initCheckBox)
    {
        initCheckBox->SetCheckedState(ECheckBoxState::Checked);
    }

    LoadShopData();
}

void UTileShopView::NativeDestruct()
{
    Super::NativeDestruct();
}

void UTileShopView::LoadShopData()
{
    if (!shopDataTable)
    {
        return;
    }
    tileDataList.Empty();

    TArray<FShopTileData*> shopTileDataList;
    shopDataTable->GetAllRows<FShopTileData>(TEXT("LoadShopData"), shopTileDataList);

    for (const FShopTileData* data : shopTileDataList)
    {
        if (data)
        {
            UShopTileViewDataWrapper* shopTileWrapper = NewObject<UShopTileViewDataWrapper>(this);
            shopTileWrapper->Init(FShopTileData::StaticStruct(), data);
            tileDataList.Add(shopTileWrapper);
        }
    }

    ApplyFilter();
}


void UTileShopView::SetCurrentSortType(ETileSortType sortType)
{
    Super::SetCurrentSortType(sortType);
    ApplyFilter();
}

void UTileShopView::SetIsDescending(bool isTrue)
{
    Super::SetIsDescending(isTrue);
    ApplyFilter();
}

void UTileShopView::ApplyFilter()
{
    if (!TileView)
    {
        return;
    }

    TArray<UTileViewDataWrapper*> filteredTileView;
    if (activeCategory.IsSet() == true)
    {
        for (UTileViewDataWrapper* data : tileDataList)
        {
            if (data)
            {
                if (UShopTileViewDataWrapper* shopWrapper = Cast<UShopTileViewDataWrapper>(data))
                {
                    if (shopWrapper->shopData.category == activeCategory.GetValue())
                    {
                        filteredTileView.Add(shopWrapper);
                    }
                }
            }
        }
    }
    else
    {
        for (UTileViewDataWrapper* data : tileDataList)
        {
            if (data)
            {
                if (UShopTileViewDataWrapper* shopWrapper = Cast<UShopTileViewDataWrapper>(data))
                {
                    if (shopWrapper->shopData.category == initCategory)
                    {
                        filteredTileView.Add(shopWrapper);
                    }
                }
            }
        }
    }

    filteredTileView.Sort([this](const UTileViewDataWrapper& first, const UTileViewDataWrapper& second)
        {
            return CompareTileData(&first, &second);
        });


    SetAndRefreshTileView(filteredTileView);
}

void UTileShopView::SetOnlyOneCheckBoxChecked(UCheckBox* selectedCheckBox, EShopItemCategory shopItemCategory)
{
    if (selectedCheckBox->IsChecked() == true 
        && activeCategory.IsSet() == true
        && activeCategory.GetValue() == shopItemCategory)
    {
        return;
    }

    TArray<UCheckBox*> checkBoxList = 
    { 
        CheckBox_Normal, 
        CheckBox_Material, 
        CheckBox_Consumable, 
        CheckBox_Equipment 
    };

    for (UCheckBox* checkBox : checkBoxList)
    {
        if (checkBox
            && checkBox != selectedCheckBox)
        {
            checkBox->SetCheckedState(ECheckBoxState::Unchecked);
        }
    }

    activeCategory = shopItemCategory;
    ApplyFilter();
}

bool UTileShopView::CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const
{
    return false;
}

void UTileShopView::OnCheckNormalChanged(bool isChecked)
{
    if (isChecked == true)
    {
        SetOnlyOneCheckBoxChecked(CheckBox_Normal, EShopItemCategory::Normal);
    }
    else
    {
        if (activeCategory.IsSet() == true
            && activeCategory.GetValue() == EShopItemCategory::Normal 
            && !CheckBox_Material || CheckBox_Material->IsChecked() == false 
            && !CheckBox_Consumable || CheckBox_Consumable->IsChecked() == false 
            && !CheckBox_Equipment || CheckBox_Equipment->IsChecked() == false)
        {
            if (CheckBox_Normal)
            {
                CheckBox_Normal->SetIsChecked(true);
            }
        }
    }
}

void UTileShopView::OnCheckMaterialChanged(bool isChecked)
{
    if (isChecked == true)
    {
        SetOnlyOneCheckBoxChecked(CheckBox_Material, EShopItemCategory::Material);
    }
    else
    {
        if (activeCategory.IsSet() == true
            && activeCategory.GetValue() == EShopItemCategory::Material
            && !CheckBox_Normal || CheckBox_Normal->IsChecked() == false
            && !CheckBox_Consumable || CheckBox_Consumable->IsChecked() == false
            && !CheckBox_Equipment || CheckBox_Equipment->IsChecked() == false)
        {
            if (CheckBox_Material)
            {
                CheckBox_Material->SetIsChecked(true);
            }
        }
    }
}

void UTileShopView::OnCheckConsumableChanged(bool isChecked)
{
    if (isChecked == true)
    {
        SetOnlyOneCheckBoxChecked(CheckBox_Consumable, EShopItemCategory::Consumable);
    }
    else
    {
        if (activeCategory.IsSet() == true
            && activeCategory.GetValue() == EShopItemCategory::Consumable
            && !CheckBox_Normal || CheckBox_Normal->IsChecked() == false
            && !CheckBox_Material || CheckBox_Material->IsChecked() == false
            && !CheckBox_Equipment || CheckBox_Equipment->IsChecked() == false)
        {
            if (CheckBox_Consumable)
            {
                CheckBox_Consumable->SetIsChecked(true);
            }
        }
    }
}

void UTileShopView::OnCheckEquipmentChanged(bool isChecked)
{
    if (isChecked == true)
    {
        SetOnlyOneCheckBoxChecked(CheckBox_Equipment, EShopItemCategory::Equipment);
    }
    else
    {
        if (activeCategory.IsSet() == true
            && activeCategory.GetValue() == EShopItemCategory::Equipment
            && !CheckBox_Normal || CheckBox_Normal->IsChecked() == false
            && !CheckBox_Material || CheckBox_Material->IsChecked() == false
            && !CheckBox_Consumable || CheckBox_Consumable->IsChecked() == false)
        {
            if (CheckBox_Equipment)
            {
                CheckBox_Equipment->SetIsChecked(true);
            }
        }
    }
}