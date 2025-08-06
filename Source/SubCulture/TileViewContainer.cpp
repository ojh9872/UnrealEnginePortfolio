// Fill out your copyright notice in the Description page of Project Settings.


#include "TileViewContainer.h"
#include "TileViewDataWrapper.h"
#include "GameEnums.h"
#include "Components/TileView.h"

void UTileViewContainer::NativeConstruct()
{
    Super::NativeConstruct();

    currentSortType = ETileSortType::Default;
    isDescending = false;
}

void UTileViewContainer::NativeDestruct()
{
    Super::NativeDestruct();
}

void UTileViewContainer::SetCurrentSortType(ETileSortType sortType)
{
    if (currentSortType == sortType)
    {
        return;
    }

    currentSortType = sortType;
    ApplyFilter();

}

void UTileViewContainer::SetIsDescending(bool isTrue)
{
    isDescending = isTrue;
    ApplyFilter();
}

void UTileViewContainer::SetAndRefreshTileView(const TArray<UTileViewDataWrapper*>& inTileDataList)
{
    if (!TileView)
    {
        return;
    }

    TileView->SetListItems(inTileDataList);
}