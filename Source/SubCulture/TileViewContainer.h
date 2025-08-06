// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileViewContainer.generated.h"

class UTileView;
class UTileViewDataWrapper;
enum class ETileSortType : uint8;
/**
 *
 */


UCLASS()
class SUBCULTURE_API UTileViewContainer : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    virtual bool CompareTileData(const UTileViewDataWrapper* first, const UTileViewDataWrapper* second) const PURE_VIRTUAL(UTileViewContainer::CompareTileData, return false;);
    virtual void ApplyFilter() PURE_VIRTUAL(UTileViewContainer::ApplyFilter, );

    UFUNCTION(BlueprintCallable, Category = "TileView")
    virtual void SetCurrentSortType(ETileSortType sortType);

    UFUNCTION(BlueprintCallable, Category = "TileView")
    virtual void SetIsDescending(bool isTrue);

    UFUNCTION(BlueprintCallable, Category = "TileView")
    void SetAndRefreshTileView(const TArray<UTileViewDataWrapper*>& inTileDataList);

    ETileSortType currentSortType;
    bool isDescending;

    UPROPERTY()
    TArray<UTileViewDataWrapper*> tileDataList;
    UPROPERTY(meta = (BindWidget))
    UTileView* TileView;
};
