// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPG/Item/item.h"
#include "Weapon.generated.h"

/**
 * 
 */

UCLASS()
class ARPG_API AWeapon : public Aitem
{
	GENERATED_BODY()

public:

	void Equip(USceneComponent* InParent,FName InSocketName);
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
};
