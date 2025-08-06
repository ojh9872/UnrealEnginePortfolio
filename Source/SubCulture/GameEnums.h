// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGunCategory : uint8
{
    All             UMETA(DisplayName = "All"),
    AR              UMETA(DisplayName = "AR"),
    SMG             UMETA(DisplayName = "SMG"),
    SG              UMETA(DisplayName = "SG"),
    SR              UMETA(DisplayName = "SR"),
    RL              UMETA(DisplayName = "RL"),
    MG              UMETA(DisplayName = "MG"),
};

UENUM(BlueprintType)
enum class EInventoryItemCategory : uint8
{
    All             UMETA(DisplayName = "All"),
    Material        UMETA(DisplayName = "Material"),
    Consumable      UMETA(DisplayName = "Consumable"),
    Equipment       UMETA(DisplayName = "Equipment"),
};

UENUM(BlueprintType)
enum class EShopItemCategory : uint8
{
    Normal          UMETA(DisplayName = "Normal"),
    Material        UMETA(DisplayName = "Material"),
    Consumable      UMETA(DisplayName = "Consumable"),
    Equipment       UMETA(DisplayName = "Equipment"),
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
    Normal          UMETA(DisplayName = "Nomal"),
    Rare            UMETA(DisplayName = "Rare"),
    Unique          UMETA(DisplayName = "Unique"),
    Legendary       UMETA(DisplayName = "Legendary"),
    Myth            UMETA(DisplayName = "Myth"),
};

UENUM(BlueprintType)
enum class ETileSortType : uint8
{
    Default         UMETA(DisplayName = "Default"),
    Level           UMETA(DisplayName = "Level"),
    Grade           UMETA(DisplayName = "Grade"),
    BattlePoint     UMETA(DisplayName = "BattlePoint"),
};