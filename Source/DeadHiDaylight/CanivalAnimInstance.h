// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CanivalAnimInstance.generated.h"
UENUM(BlueprintType)
enum class ECanivalState : uint8
{
	Idle,
	Move,
	RaiseHammer,
	SwingHammer
};


UCLASS()
class DEADHIDAYLIGHT_API UCanivalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
public:
	UCanivalAnimInstance();
	
	//상태
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
	ECanivalState CurrentState;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* MyAnimMontage;

	void UpdateFSM(float DeltaTime); //상태 제어 메서드
	void ChangeState(ECanivalState NewState); // 상태 전환 메서드

	void HandleIdleState();
	void HandleMoveState();
	void HandleRaiseHammerState();
	void HandleSwingHammerState();


	//몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimMontage* RaiseHammerMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimMontage* SwingHammerMontage;

	//공격 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bIsMoving;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bCanAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bInputLMB;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	float ElapsedTime;
	
	FTimerHandle HammerTimerHandle;

	//공격 함수
	void StartRaiseHammer();
	void AutoSwingHammer();
	void StopSwingHammer();

	
	
};
