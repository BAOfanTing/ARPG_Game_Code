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
	//使得鼠标旋转人物也能旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.f;
	//让人物不跟随旋转
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);

	//创建头发,绑定到骨架并且附加到头的这个点位
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
{	//判断攻击时不能移动
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && Value!=0) 
	{	//找到哪个向量是向前的
		// 获取控制器的旋转方向,创建一个只包含Yaw旋转的FRotator对象
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f,ControlRotation.Yaw,0.f); 
		// 根据Yaw旋转创建一个方向向量，提取X轴方向的单位向量
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Value);
	}
}

void ACharacter01::MoveRight(float Value)
{	//判断攻击时不能移动
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && Value != 0)
	{	//找到哪个向量是向前的
		// 获取控制器的旋转方向,创建一个只包含Yaw旋转的FRotator对象
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		// 根据Yaw旋转创建一个方向向量，提取Y轴方向的单位向量,为向右
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
{	//当重叠的物体为武器类获取改物体
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
	// 获取角色的骨架并检查是否存在动画实例以及攻击蒙太奇（Montage）
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{	// 在动画实例上播放攻击蒙太奇
		AnimInstance->Montage_Play(AttackMontage);
		// 生成一个随机数，选择攻击动作的不同部分
		const int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		// 根据随机数选择不同的攻击部分
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
		// 跳转到所选的攻击部分
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void ACharacter01::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

//判断上一次是否播放完以及人物是否有武器
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

