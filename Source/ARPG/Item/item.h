// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ARPG/Character/CharacterType.h"
#include "item.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_UnOnHand UMETA(DisplayName="UnOnHand"),
	EIS_OnHand UMETA(DisplayName = "OnHand")
};


UCLASS()
class ARPG_API Aitem : public AActor
{
	GENERATED_BODY()
	
public:	
	Aitem();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	float Amplitude = 2.f;

	//一开始未被拿起
	UPROPERTY(BlueprintReadWrite)
	EItemState ItemState = EItemState::EIS_UnOnHand;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadonly,meta = (AllowPrivateAccess = "true"))
	float RunningTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;


};

