// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"
#include "CharacterType.h"
#include "Character01.generated.h"

class Aitem;

UCLASS()
class ARPG_API ACharacter01 : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacter01();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ������һ���������� SetOverlappingItem���������������ص�����Ʒ��
	// �ú��������� Item ��ֵ����Ա���� OverlappingItem��
	FORCEINLINE void SetOverlappingItem(Aitem* Item){OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState(){return CharacterState;}
protected:
	virtual void BeginPlay() override;

	/*
	����Ļص�
	*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();
	void Attack();

	/*
	������̫��ĺ���
	*/
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	void CanAttack();

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USpringArmComponent* CameraArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	//����ͷ����üë
	UPROPERTY(VisibleAnywhere,Category = Hair)
	UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;
	//�����ʼ״̬��δװ������ 
	ECharacterState CharacterState = ECharacterState::ECS_Unequiped;

	UPROPERTY(BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/*
	//Animation montages
	*/
	UPROPERTY(EditDefaultsOnly,Category = Montages)
	class UAnimMontage* AttackMontage;

private:
	UPROPERTY(VisibleInstanceOnly)
	class Aitem* OverlappingItem;



};
