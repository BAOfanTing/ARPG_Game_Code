// Fill out your copyright notice in the Description page of Project Settings.


#include "Character01_AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character01.h"
#include "GameFramework/CharacterMovementComponent.h"
//��δ�����Ҫ�漰��ɫ����ʵ���ĳ�ʼ���͸��¡��ڳ�ʼ���У������Ի�ȡPawn��ͨ���ǽ�ɫ��
//�������ƶ������ֵ��CharacterMovement���ڸ����У���ʹ��Velocity���ٶ�ʸ��������GroundSpeed�������ٶȣ�
//�Ա��ڶ�����ʹ�á�

void UCharacter01_AnimInstance::NativeInitializeAnimation()
{
	// ���ø���ĳ�ʼ������
	Super::NativeInitializeAnimation();

	// ���Ի�ȡӵ�д˶���ʵ����Pawn��ͨ���ǽ�ɫ��
	Character01 = Cast<ACharacter01>(TryGetPawnOwner());

	// ����ɹ���ȡ��Pawn�������ƶ������ֵ��CharacterMovement
	if (Character01)
	{
		Character01Movement = Character01->GetCharacterMovement();
	}
}

void UCharacter01_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	// ���ø���ĸ��¶�������������Deltaʱ��
	Super::NativeUpdateAnimation(DeltaTime);

	// ���CharacterMovement�Ѿ���ֵ
	if (Character01Movement)
	{
		// ����GroundSpeed�������ٶȣ���ʹ��UKismetMathLibrary��VSizeXY����
		// ����������ڼ���2Dʸ���ĳ��ȣ��������ڼ���Pawn���ٶ�ʸ���ĳ���
		GroundSpeed = UKismetMathLibrary::VSizeXY(Character01Movement->Velocity);
		IsFalling = Character01Movement->IsFalling(); 
		CharacterState = Character01->GetCharacterState();
	}
}







