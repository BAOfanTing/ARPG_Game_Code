// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "ARPG/Character/Character01.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	// 调用 AttachMeshToSocket 函数将武器的 Mesh 附加到指定的骨骼插槽上
	AttachMeshToSocket(InParent, InSocketName);

	// 设置武器的状态为在手上
	ItemState = EItemState::EIS_OnHand;

	// 如果设置了装备音效，就在武器的位置播放音效
	if (EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());
	}
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	// 创建一个 FAttachmentTransformRules 对象，规定附着的规则。
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	// 将武器的 ItemMesh 附着到InParent的 Mesh 上，并使用Socket作为附着点
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 调用父类的 OnSphereOverlap 函数，如果有的话。
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
