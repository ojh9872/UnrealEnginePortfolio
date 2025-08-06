// Fill out your copyright notice in the Description page of Project Settings.


#include "TileShopViewEntry.h"

void UTileShopViewEntry::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTileShopViewEntry::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTileShopViewEntry::NativeOnListItemObjectSet(UObject* listItemObject)
{
    UShopTileViewDataWrapper* shopTileDataWrapper = Cast<UShopTileViewDataWrapper>(listItemObject);
    if (shopTileDataWrapper)
    {
        shopTileData = shopTileDataWrapper->shopData;
    }
}

FText UTileShopViewEntry::GetName() const
{
	return shopTileData.name;
}

int32 UTileShopViewEntry::GetPrice() const
{
	return shopTileData.price;
}

int32 UTileShopViewEntry::GetDiscountPrice() const
{
	return shopTileData.discountPrice;
}

int32 UTileShopViewEntry::GetCount() const
{
	return shopTileData.count;
}

EItemGrade UTileShopViewEntry::GetGrade() const
{
	return shopTileData.grade;
}

int32 UTileShopViewEntry::GetMaxLimitBuyCount() const
{
	return shopTileData.maxLimitBuyCount;
}

int32 UTileShopViewEntry::GetCurrentLimitBuyCount() const
{
	return shopTileData.currentLimitBuyCount;
}
EShopItemCategory UTileShopViewEntry::GetCategory() const
{
	return shopTileData.category;
}

bool UTileShopViewEntry::GetIsSoldOut() const
{
	return shopTileData.isSoldOut;
}
