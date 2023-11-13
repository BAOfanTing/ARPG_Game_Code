#pragma once


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequiped UMETA(DisplayName = "Unequiped"),
	ECS_EquipedOneHandWeapon UMETA(DisplayName = "EquipedOneHandWeapon"),
	ECS_EquipedTwoHandWeapon UMETA(DisplayName = "EquipedTwoHandWeapon")
};

UENUM(BlueprintType)
enum class EActionState:uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking")
};