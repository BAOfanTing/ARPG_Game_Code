// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bird.generated.h"


UCLASS()
class ARPG_API ABird : public APawn
{
	GENERATED_BODY()

public:

	ABird();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;


private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

};
