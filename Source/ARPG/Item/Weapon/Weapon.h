// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPG/Item/item.h"
#include "Weapon.generated.h"

/**
 * 
 */
 class USoundBase;

UCLASS()
class ARPG_API AWeapon : public Aitem
{
	GENERATED_BODY()

public:
	// 装备武器的函数，将武器附加到指定的骨骼插槽上
	void Equip(USceneComponent* InParent, FName InSocketName);

	// 将武器的Mesh附加到指定的骨骼插槽上
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	// 重写基类的碰撞开始函数，用于处理武器的特定碰撞逻辑
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	// 重写基类的碰撞结束函数，用于处理武器的特定碰撞结束逻辑
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	// 武器装备时播放的音效
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
};

