// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewDataWrapper.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "TileShopViewEntry.generated.h"

/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileShopViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	virtual void NativeOnListItemObjectSet(UObject* listItemObject) override;

	FShopTileData shopTileData;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	FText GetName() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	int32 GetDiscountPrice() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	int32 GetCount() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	EItemGrade GetGrade() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	int32 GetMaxLimitBuyCount() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	int32 GetCurrentLimitBuyCount() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	EShopItemCategory GetCategory() const;

	UFUNCTION(BlueprintCallable, Category = "ShopTileData")
	bool GetIsSoldOut() const;
};
