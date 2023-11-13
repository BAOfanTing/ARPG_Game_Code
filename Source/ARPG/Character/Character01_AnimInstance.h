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
		 * 这是 UCharacter01_AnimInstance 类的构造函数。
		 * 它声明了两个重要的虚拟函数，用于初始化和更新动画实例。
		 */
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	/**
	 * 这是 UCharacter01_AnimInstance 类的构造函数。
	 * 它声明了两个重要的虚拟函数，用于初始化和更新动画实例。
	 */

	UPROPERTY(BlueprintReadOnly)
	class ACharacter01* Character01;// 用于引用角色对象的指针。

	UPROPERTY(BlueprintReadOnly,Category = "Movement")
	class UCharacterMovementComponent* Character01Movement;// 用于引用角色移动组件的指针。

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;// 用于存储地面速度的浮点数值。

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;
	UPROPERTY(BlueprintReadOnly, Category = "Movement | CharacterState")
	ECharacterState CharacterState;
	
};



