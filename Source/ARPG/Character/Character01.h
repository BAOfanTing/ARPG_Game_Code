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
class UAnimMontage;
class AWeapon;

UCLASS()
class ARPG_API ACharacter01 : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacter01();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 定义了一个内联函数 SetOverlappingItem，用于设置正在重叠的物品。
	// 该函数将参数 Item 赋值给成员变量 OverlappingItem。
	FORCEINLINE void SetOverlappingItem(Aitem* Item){OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState(){return CharacterState;}
protected:
	virtual void BeginPlay() override;

	/*
	输入的回调
	*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();
	void Attack();

	/*
	播放蒙太奇的函数
	*/
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	//能够攻击
	bool CanAttack();

	//能够卸下武器
	bool CanDisarm();
	bool Canarm();
	void PlayEquipMontage(FName SectionName);
	UPROPERTY(VisibleAnywhere,Category = Weapon)
	AWeapon* EquippedWeapon;
	UFUNCTION(BlueprintCallable)
	void Disarm();
	UFUNCTION(BlueprintCallable)
	void Arm();
	UFUNCTION(BlueprintCallable)
	void FinishPlayAnim();

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USpringArmComponent* CameraArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	//定义头发和眉毛
	UPROPERTY(VisibleAnywhere,Category = Hair)
	UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;
	//定义初始状态，未装备武器 
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/*
	//Animation montages
	*/
	UPROPERTY(EditDefaultsOnly,Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

private:
	UPROPERTY(VisibleInstanceOnly)
	class Aitem* OverlappingItem;



};
