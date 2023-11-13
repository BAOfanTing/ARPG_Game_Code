// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

// Sets default values
ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	//创建骨骼网格体，并且附加在根组件下
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	// 创建一个名为 "CameraArm" 的默认子对象,将 CameraArm 与根组件（RootComponent）关联
	//设置相机臂的目标长度
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.f;
	//创建一个名为 "Camera" 的默认子对象,关联相机臂使相机位于 CameraArm 的末端
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);



	//设置自动接收输入玩家0
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
	// 绑定“MoveForward”输入轴到 MoveForward 函数，以响应玩家输入
	// 参数 FName("MoveForward") 指定了输入轴的名称
	// this 指针将 ABird 类的当前实例与输入组件绑定
	// &ABird::MoveForward 是处理输入的函数，它会在输入轴发生变化时被调用
	PlayerInputComponent->BindAxis(FName("MoveForward"),this,&ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"),this,&ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"),this,&ABird::LookUp);
}

