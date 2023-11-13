// Fill out your copyright notice in the Description page of Project Settings.


#include "Character01_AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character01.h"
#include "GameFramework/CharacterMovementComponent.h"
//这段代码主要涉及角色动画实例的初始化和更新。在初始化中，它尝试获取Pawn（通常是角色）
//并将其移动组件赋值给CharacterMovement。在更新中，它使用Velocity（速度矢量）计算GroundSpeed（地面速度）
//以便在动画中使用。

void UCharacter01_AnimInstance::NativeInitializeAnimation()
{
	// 调用父类的初始化函数
	Super::NativeInitializeAnimation();

	// 尝试获取拥有此动画实例的Pawn（通常是角色）
	Character01 = Cast<ACharacter01>(TryGetPawnOwner());

	// 如果成功获取了Pawn，将其移动组件赋值给CharacterMovement
	if (Character01)
	{
		Character01Movement = Character01->GetCharacterMovement();
	}
}

void UCharacter01_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	// 调用父类的更新动画函数，传递Delta时间
	Super::NativeUpdateAnimation(DeltaTime);

	// 如果CharacterMovement已经赋值
	if (Character01Movement)
	{
		// 计算GroundSpeed（地面速度），使用UKismetMathLibrary的VSizeXY函数
		// 这个函数用于计算2D矢量的长度，这里用于计算Pawn的速度矢量的长度
		GroundSpeed = UKismetMathLibrary::VSizeXY(Character01Movement->Velocity);
		IsFalling = Character01Movement->IsFalling(); 
		CharacterState = Character01->GetCharacterState();
	}
}







