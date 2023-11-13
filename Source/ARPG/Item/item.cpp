// 填写版权信息通常需要在项目设置的描述页面中完成，这里的代码文件定义了一个名为 "item" 的类。

#include "item.h"
#include "ARPG/DebugMacros.h"
#include "ARPG/Character/Character01.h"

// 设置默认值
Aitem::Aitem()
{
	// 允许该 Actor 每帧调用 Tick() 函数。如果不需要，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个名为 "ItemMesh" 的 UStaticMeshComponent 对象并设置为根组件
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;  // 让 "ItemMesh" 成为根组件
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);  // 将 "Sphere" 组件附加到根组件
}

// 游戏开始时或生成 Actor 时调用
void Aitem::BeginPlay()
{
	Super::BeginPlay();

	// 通过委托将 OnSphereOverlap 函数与 Sphere 组件的 OnComponentBeginOverlap 事件绑定
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &Aitem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&Aitem::EndSphereOverlap);
}

// 自定义函数，返回一个经过函数计算的正弦值
float Aitem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * 5.f);
}

// 当 Sphere 组件与其他组件发生重叠时调用的函数
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

// 每帧都会被调用
void Aitem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 记录经过的总时间
	RunningTime += DeltaTime;
	//当物体不被拿起时漂浮
	if (ItemState == EItemState::EIS_UnOnHand)
	{
		AddActorWorldOffset(FVector(0.f,0.f,TransformedSin()));
	}
}
