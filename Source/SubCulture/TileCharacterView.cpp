// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCharacterView.h"
#include "TileViewDataWrapper.h"
#include "GameEnums.h"
#include "Components/CheckBox.h"

void UTileCharacterView::NativeConstruct()
{
    Super::NativeConstruct();

    if (CheckBox_All)
    {
        CheckBox_All->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckAllChanged);
    }

    if (CheckBox_AR)
    {
        CheckBox_AR->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckARChanged);
    }

    if (CheckBox_SMG)
    {
        CheckBox_SMG->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckSMGChanged);
    }

    if (CheckBox_SG)
    {
        CheckBox_SG->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckSGChanged);
    }

    if (CheckBox_SR)
    {
        CheckBox_SR->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckSRChanged);
    }

    if (CheckBox_RL)
    {
        CheckBox_RL->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckRLChanged);
    }

    if (CheckBox_MG)
    {
        CheckBox_MG->OnCheckStateChanged.AddDynamic(this, &UTileCharacterView::OnCheckMGChanged);
    }

    LoadCharacterData();
}

void UTileCharacterView::NativeDestruct()
{
    Super::NativeDestruct();
}

void UTileCharacterView::LoadCharacterData()
{
    if (!CharacterDataTable)
    {
        return;
    }
    tileDataList.Empty();

    TArray<FCharacterTileData*> characterTileDataList;
    CharacterDataTable->ForeachRow<FCharacterTileData>(TEXT("LoadCharacterData"), [this](const FName& rowName, const FCharacterTileData& data)
        {
            UCharacterTileViewDataWrapper* characterTileWrapper = NewObject<UCharacterTileViewDataWrapper>(this);

            characterTileWrapper->Init(FCharacterTileData::StaticStruct(), &data, rowName);
            tileDataList.Add(characterTileWrapper);
        });

    ApplyFilter();
}

void UTileCharacterView::SetCurrentSortType(ETileSortType sortType)
{
    Super::SetCurrentSortType(sortType);
}

void UTileCharacterView::SetIsDescending(bool isTrue)
{
    Super::SetIsDescending(isTrue);
}

void UTileCharacterView::ApplyFilter()
{
    if (!TileView)
    {
        return;
    }

    TArray<UTileViewDataWrapper*> filteredTileDataList;
    if (activeFilters.Num() == 0 || activeFilters.Contains(EGunCategory::All) == true)
    {
        filteredTileDataList.Append(tileDataList);
    }
    else
    {
        for (UTileViewDataWrapper* data : tileDataList)
        {
            if (data)
            {
                if (UCharacterTileViewDataWrapper* characterWrapper = Cast<UCharacterTileViewDataWrapper>(data))
                {
                    if (activeFilters.Contains(characterWrapper->characterData.category) == true)
                    {
                        filteredTileDataList.Add(characterWrapper);
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

void UTileCharacterView::UpdateActiveFilters(EGunCategory category, bool isAdd)
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

bool UTileCharacterView::CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const
{
    const UCharacterTileViewDataWrapper* firstCharacterTileWrapper = Cast<UCharacterTileViewDataWrapper>(first);
    const UCharacterTileViewDataWrapper* secondCharacterTileWrapper = Cast<UCharacterTileViewDataWrapper>(second);
    if (!firstCharacterTileWrapper || !secondCharacterTileWrapper)
    {
        return false;
    }

    const FCharacterTileData& firstCharacterData = firstCharacterTileWrapper->characterData;
    const FCharacterTileData& secondCharacterData = secondCharacterTileWrapper->characterData;
    switch (currentSortType)
    {
    case ETileSortType::Level:
        return isDescending ? firstCharacterData.level < secondCharacterData.level : secondCharacterData.level < firstCharacterData.level;
    case ETileSortType::Grade:
        if (firstCharacterData.characterGrade == secondCharacterData.characterGrade)
        {
            return secondCharacterData.level < firstCharacterData.level;
        }

        return isDescending ? firstCharacterData.characterGrade < secondCharacterData.characterGrade : secondCharacterData.characterGrade < firstCharacterData.characterGrade;
    case ETileSortType::BattlePoint:
        return isDescending ? firstCharacterData.level < secondCharacterData.level : secondCharacterData.level < firstCharacterData.level;
    default:
        return false;
    }
}

void UTileCharacterView::OnCheckAllChanged(bool isChecked)
{
    if (isChecked)
    {
        if (CheckBox_AR)
        {
            CheckBox_AR->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_SMG)
        {
            CheckBox_SMG->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_SG)
        {
            CheckBox_SG->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_SR)
        {
            CheckBox_SR->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_RL)
        {
            CheckBox_RL->SetCheckedState(ECheckBoxState::Unchecked);
        }

        if (CheckBox_MG)
        {
            CheckBox_MG->SetCheckedState(ECheckBoxState::Unchecked);
        }

        activeFilters.Empty();
        activeFilters.Add(EGunCategory::All);
    }
    else
    {
        CheckBox_All->SetCheckedState(ECheckBoxState::Checked);
    }

    ApplyFilter();
}

void UTileCharacterView::OnCheckChanged(bool isChecked, EGunCategory category)
{
    if (isChecked == true
        && CheckBox_All
        && CheckBox_All->IsChecked() == true)
    {
        CheckBox_All->SetCheckedState(ECheckBoxState::Unchecked);
        activeFilters.Remove(EGunCategory::All);
    }

    UpdateActiveFilters(category, isChecked);
}

void UTileCharacterView::OnCheckARChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::AR);
}

void UTileCharacterView::OnCheckSMGChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::SMG);
}

void UTileCharacterView::OnCheckSGChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::SG);
}

void UTileCharacterView::OnCheckSRChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::SR);
}

void UTileCharacterView::OnCheckRLChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::RL);
}

void UTileCharacterView::OnCheckMGChanged(bool isChecked)
{
    OnCheckChanged(isChecked, EGunCategory::MG);
}