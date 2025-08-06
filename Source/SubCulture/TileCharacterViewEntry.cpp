// Fill out your copyright notice in the Description page of Project Settings.


#include "TileCharacterViewEntry.h"
#include "PaperSprite.h"
#include "Components/WidgetSwitcher.h"

void UTileCharacterViewEntry::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTileCharacterViewEntry::NativeDestruct()
{
    Super::NativeDestruct();

    if (CharacterTileViewDataWrapper)
    {
        CharacterTileViewDataWrapper->OnLevelChanged.RemoveDynamic(this, &UTileCharacterViewEntry::OnCharacterLevelChanged);
    }
}

void UTileCharacterViewEntry::NativeOnListItemObjectSet(UObject* listItemObject)
{
    UCharacterTileViewDataWrapper* newCharacterTileViewDataWrapper = Cast<UCharacterTileViewDataWrapper>(listItemObject);
    if (newCharacterTileViewDataWrapper)
    {
        if (CharacterTileViewDataWrapper)
        {
            CharacterTileViewDataWrapper->OnLevelChanged.RemoveDynamic(this, &UTileCharacterViewEntry::OnCharacterLevelChanged);
        }

        CharacterTileViewDataWrapper = newCharacterTileViewDataWrapper;
        CharacterTileViewDataWrapper->OnLevelChanged.AddDynamic(this, &UTileCharacterViewEntry::OnCharacterLevelChanged);

        characterTileData = CharacterTileViewDataWrapper->characterData;
        rowName = CharacterTileViewDataWrapper->rowName;
        if (WidgetSwitcher_Rank)
        {
            WidgetSwitcher_Rank->SetActiveWidgetIndex(characterTileData.characterGrade);
        }
    }
}


void UTileCharacterViewEntry::OnCharacterLevelChanged(int32 level)
{
    characterTileData.level = level;
}

FText UTileCharacterViewEntry::GetCharacterName() const
{
    return characterTileData.characterName;
}

FSlateBrush UTileCharacterViewEntry::GetCharacterSprite() const
{
    FSlateBrush brush;
    if (characterTileData.characterSprite)
    {
        brush.SetResourceObject(characterTileData.characterSprite);
    }

    return brush;
}

FSlateBrush UTileCharacterViewEntry::GetGunTypeIcon() const
{
    FSlateBrush brush;
    if (characterTileData.gunTypeIcon)
    {
        brush.SetResourceObject(characterTileData.gunTypeIcon);
    }

    return brush;
}

int32 UTileCharacterViewEntry::GetCharacterLevel() const
{
    return characterTileData.level;
}