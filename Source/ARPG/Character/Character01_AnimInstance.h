// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterType.h"
#include "Character01_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCharacter01_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	/**
		 * ���� UCharacter01_AnimInstance ��Ĺ��캯����
		 * ��������������Ҫ�����⺯�������ڳ�ʼ���͸��¶���ʵ����
		 */
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	/**
	 * ���� UCharacter01_AnimInstance ��Ĺ��캯����
	 * ��������������Ҫ�����⺯�������ڳ�ʼ���͸��¶���ʵ����
	 */

	UPROPERTY(BlueprintReadOnly)
	class ACharacter01* Character01;// �������ý�ɫ�����ָ�롣

	UPROPERTY(BlueprintReadOnly,Category = "Movement")
	class UCharacterMovementComponent* Character01Movement;// �������ý�ɫ�ƶ������ָ�롣

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;// ���ڴ洢�����ٶȵĸ�����ֵ��

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;
	UPROPERTY(BlueprintReadOnly, Category = "Movement | CharacterState")
	ECharacterState CharacterState;
	
};



