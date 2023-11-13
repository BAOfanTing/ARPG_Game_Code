// Fill out your copyright notice in the Description page of Project Settings.


#include "Character01.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARPG/Item/item.h"
#include "ARPG/Item/Weapon/Weapon.h"
#include "Animation/AnimMontage.h"

// Sets default values
ACharacter01::ACharacter01()
{
	PrimaryActorTick.bCanEverTick = true;
	//ʹ�������ת����Ҳ����ת
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.f;
	//�����ﲻ������ת
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);

	//����ͷ��,�󶨵��Ǽܲ��Ҹ��ӵ�ͷ�������λ
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");


}

void ACharacter01::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacter01::MoveForward(float Value)
{	//�жϹ���ʱ�����ƶ�
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && Value!=0) 
	{	//�ҵ��ĸ���������ǰ��
		// ��ȡ����������ת����,����һ��ֻ����Yaw��ת��FRotator����
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f,ControlRotation.Yaw,0.f); 
		// ����Yaw��ת����һ��������������ȡX�᷽��ĵ�λ����
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Value);
	}
}

void ACharacter01::MoveRight(float Value)
{	//�жϹ���ʱ�����ƶ�
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && Value != 0)
	{	//�ҵ��ĸ���������ǰ��
		// ��ȡ����������ת����,����һ��ֻ����Yaw��ת��FRotator����
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		// ����Yaw��ת����һ��������������ȡY�᷽��ĵ�λ����,Ϊ����
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACharacter01::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ACharacter01::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACharacter01::EKeyPressed()
{	//���ص�������Ϊ�������ȡ������
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Amplitude = 0.f;
		OverlappingWeapon->Equip(GetMesh(),FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquipedOneHandWeapon;
	}
}

void ACharacter01::Attack()
{	
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void ACharacter01::PlayAttackMontage()
{
	// ��ȡ��ɫ�ĹǼܲ�����Ƿ���ڶ���ʵ���Լ�������̫�棨Montage��
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{	// �ڶ���ʵ���ϲ��Ź�����̫��
		AnimInstance->Montage_Play(AttackMontage);
		// ����һ���������ѡ�񹥻������Ĳ�ͬ����
		const int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		// ���������ѡ��ͬ�Ĺ�������
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}
		// ��ת����ѡ�Ĺ�������
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void ACharacter01::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

//�ж���һ���Ƿ񲥷����Լ������Ƿ�������
bool ACharacter01::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_Unequiped;
}



void ACharacter01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacter01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ACharacter01::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"),this,&ACharacter01::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ACharacter01::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ACharacter01::LookUp);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"),IE_Pressed,this,&ACharacter01::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ACharacter01::Attack);
}

