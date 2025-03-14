#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Camper.generated.h"

UCLASS()
class DEADHIDAYLIGHT_API ACamper : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACamper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UCharacterMovementComponent* moveComp;
	//Input IMC
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_Camper;
	//Input Move 변수
	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Look;
	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Run;

	UPROPERTY(EditAnywhere)
	class UCamperAnimInstance* Anim;
	
	UPROPERTY()
	FVector direction;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camper)
	float moveSpeed = 226;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camper)
	float maxSpeed = 400;
	
	void CamperMove(const FInputActionValue& value);
	void Look(const struct FInputActionValue& value);
	void Run(const struct FInputActionValue& value);

	/*
	 * Temp for Interact with Generator
	 */
public:
	UPROPERTY()
	class UGeneratorRepairSlot* OverlappedGeneratorSlot = nullptr;
	void BeginGeneratorOverlap(UGeneratorRepairSlot* GeneratorRepairSlot);
	void EndGeneratorOverlap(const UGeneratorRepairSlot* GeneratorRepairSlot);
	void StartRepair();
	void EndRepair();
};
