// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

// Sets default values
ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	//�������������壬���Ҹ����ڸ������
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	// ����һ����Ϊ "CameraArm" ��Ĭ���Ӷ���,�� CameraArm ��������RootComponent������
	//��������۵�Ŀ�곤��
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.f;
	//����һ����Ϊ "Camera" ��Ĭ���Ӷ���,���������ʹ���λ�� CameraArm ��ĩ��
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);



	//�����Զ������������0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABird::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward,Value);
	}
}

void ABird::Turn(float Value)
{	
	AddControllerYawInput(Value);
}

void ABird::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// �󶨡�MoveForward�������ᵽ MoveForward ����������Ӧ�������
	// ���� FName("MoveForward") ָ���������������
	// this ָ�뽫 ABird ��ĵ�ǰʵ�������������
	// &ABird::MoveForward �Ǵ�������ĺ����������������ᷢ���仯ʱ������
	PlayerInputComponent->BindAxis(FName("MoveForward"),this,&ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"),this,&ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"),this,&ABird::LookUp);
}

