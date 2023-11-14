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
	// װ�������ĺ��������������ӵ�ָ���Ĺ��������
	void Equip(USceneComponent* InParent, FName InSocketName);

	// ��������Mesh���ӵ�ָ���Ĺ��������
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	// ��д�������ײ��ʼ���������ڴ����������ض���ײ�߼�
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	// ��д�������ײ�������������ڴ����������ض���ײ�����߼�
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	// ����װ��ʱ���ŵ���Ч
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
};

