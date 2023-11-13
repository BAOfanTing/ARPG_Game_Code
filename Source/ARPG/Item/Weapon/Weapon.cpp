// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "ARPG/Character/Character01.h"

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{	
	// ����һ�� FAttachmentTransformRules ���󣬹涨���ŵĹ���
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	// �������� ItemMesh ���ŵ�InParent�� Mesh �ϣ���ʹ��Socket��Ϊ���ŵ�
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
	ItemState = EItemState::EIS_OnHand;
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���ø���� OnSphereOverlap ����������еĻ���
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
