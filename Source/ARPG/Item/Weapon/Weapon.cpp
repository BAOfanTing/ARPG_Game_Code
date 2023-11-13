// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "ARPG/Character/Character01.h"

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{	
	// 创建一个 FAttachmentTransformRules 对象，规定附着的规则。
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	// 将武器的 ItemMesh 附着到InParent的 Mesh 上，并使用Socket作为附着点
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
	ItemState = EItemState::EIS_OnHand;
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 调用父类的 OnSphereOverlap 函数，如果有的话。
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
