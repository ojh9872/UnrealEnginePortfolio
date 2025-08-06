// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewDataWrapper.generated.h"

class UPaperSprite;
enum class EGunCategory : uint8;
enum class EInventoryItemCategory : uint8;
enum class EShopItemCategory : uint8;
enum class EItemGrade : uint8;

/**
 *
 */
USTRUCT(BlueprintType)
struct FCharacterTileData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText characterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperSprite* characterSprite;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* gunTypeIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 maxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 characterGrade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGunCategory category;
};

USTRUCT(BlueprintType)
struct FInventoryTileData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemGrade grade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 count;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventoryItemCategory category;
};

USTRUCT(BlueprintType)
struct FShopTileData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 price;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 discountPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 count;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemGrade grade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 maxLimitBuyCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 currentLimitBuyCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EShopItemCategory category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isSoldOut;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMaxLevel);

UCLASS(BlueprintType, Abstract)
class UTileViewDataWrapper : public UObject
{
    GENERATED_BODY()
    
public:
    virtual void Init(const UScriptStruct* structType, const void* structData) PURE_VIRTUAL(UTileViewDataWrapper::Init, );
    virtual void Init(const UScriptStruct* structType, const void* structData, FName rowName) PURE_VIRTUAL(UTileViewDataWrapper::Init, );

    UFUNCTION(BlueprintCallable)
    virtual void SetLevel(int32 level) PURE_VIRTUAL(UTileViewDataWrapper::SetLevel, );

    UPROPERTY(BlueprintAssignable)
    FOnLevelChanged OnLevelChanged;

    UPROPERTY(BlueprintAssignable)
    FMaxLevel MaxLevel;
};

UCLASS(BlueprintType)
class UCharacterTileViewDataWrapper : public UTileViewDataWrapper
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FCharacterTileData characterData;

    UPROPERTY(BlueprintReadOnly)
    FName rowName;

    virtual void Init(const UScriptStruct* structType, const void* structData, FName inRowName) override
    {
        if (structType
            && structType == FCharacterTileData::StaticStruct()
            && structData)
        {
            characterData = *static_cast<const FCharacterTileData*>(structData);
            rowName = inRowName;
        }
    }

    virtual void SetLevel(int32 level) override
    {
        if (characterData.maxLevel < level)
        {
            MaxLevel.Broadcast();
        }
        else if (level > characterData.level)
        {
            characterData.level = level;
            OnLevelChanged.Broadcast(characterData.level);
        }
        else
        {
            // 레벨이 감소하는 경우
        }
    }
};

UCLASS(BlueprintType)
class UInventoryTileViewDataWrapper : public UTileViewDataWrapper
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FInventoryTileData inventoryData;

    virtual void Init(const UScriptStruct* structType, const void* structData) override
    {
        if (structType
            && structType == FInventoryTileData::StaticStruct()
            && structData)
        {
            inventoryData = *static_cast<const FInventoryTileData*>(structData);
        }
    }
};

UCLASS(BlueprintType)
class UShopTileViewDataWrapper : public UTileViewDataWrapper
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FShopTileData shopData;

    virtual void Init(const UScriptStruct* structType, const void* structData) override
    {
        if (structType
            && structType == FShopTileData::StaticStruct()
            && structData)
        {
            shopData = *static_cast<const FShopTileData*>(structData);
        }
    }
};