// ��д��Ȩ��Ϣͨ����Ҫ����Ŀ���õ�����ҳ������ɣ�����Ĵ����ļ�������һ����Ϊ "item" ���ࡣ

#include "item.h"
#include "ARPG/DebugMacros.h"
#include "ARPG/Character/Character01.h"

// ����Ĭ��ֵ
Aitem::Aitem()
{
	// ����� Actor ÿ֡���� Tick() �������������Ҫ�����Թر���������ܡ�
	PrimaryActorTick.bCanEverTick = true;

	// ����һ����Ϊ "ItemMesh" �� UStaticMeshComponent ��������Ϊ�����
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;  // �� "ItemMesh" ��Ϊ�����
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);  // �� "Sphere" ������ӵ������
}

// ��Ϸ��ʼʱ������ Actor ʱ����
void Aitem::BeginPlay()
{
	Super::BeginPlay();

	// ͨ��ί�н� OnSphereOverlap ������ Sphere ����� OnComponentBeginOverlap �¼���
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &Aitem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&Aitem::EndSphereOverlap);
}

// �Զ��庯��������һ�������������������ֵ
float Aitem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * 5.f);
}

// �� Sphere �����������������ص�ʱ���õĺ���
void Aitem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter01* Character01 = Cast<ACharacter01>(OtherActor);
	
	if (Character01)
	{
		Character01->SetOverlappingItem(this);
		if (ItemState == EItemState::EIS_UnOnHand)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Press E to Pick Up!"));
		}
	}
}

void Aitem::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter01* Character01 = Cast<ACharacter01>(OtherActor);
	if (Character01)
	{
		Character01->SetOverlappingItem(nullptr);
	}
}

// ÿ֡���ᱻ����
void Aitem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��¼��������ʱ��
	RunningTime += DeltaTime;
	//�����岻������ʱƯ��
	if (ItemState == EItemState::EIS_UnOnHand)
	{
		AddActorWorldOffset(FVector(0.f,0.f,TransformedSin()));
	}
}
