// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileViewDataWrapper.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "TileCharacterViewEntry.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class SUBCULTURE_API UTileCharacterViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
    virtual void NativeOnListItemObjectSet(UObject* listItemObject) override;

    FCharacterTileData characterTileData;
    FName rowName;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UFUNCTION()
    void OnCharacterLevelChanged(int32 level);

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* WidgetSwitcher_Rank;

    UFUNCTION(BlueprintCallable, Category = "CharacterTileData")
    FText GetCharacterName() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterTileData")
    FSlateBrush GetCharacterSprite() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterTileData")
    FSlateBrush GetGunTypeIcon() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterTileData")
    int32 GetCharacterLevel() const;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCharacterTileViewDataWrapper* CharacterTileViewDataWrapper;
};
