// Fill out your copyright notice in the Description page of Project Settings.


#include "CanivalAnimInstance.h"

#include "Canival.h"
#include "GameFramework/Character.h"

UCanivalAnimInstance::UCanivalAnimInstance()
{

	//초기 상태
	CurrentState = ECanivalState::Idle;
	bIsMoving = false;
	bCanAttack=true;
	bInputLMB=false;
	ElapsedTime=0.0f;
	
}

void UCanivalAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	auto* Owner = Cast<ACanival>(GetOwningActor());
	if (Owner)
	{
		float Velocity = Owner->GetVelocity().Length();
		UE_LOG(LogTemp, Warning, TEXT("%f"), Velocity);
		if (Velocity != 0.0f)                           
		{                                              
			bIsMoving = true;                          
		}
		else
		{
			bIsMoving = false;
		}
	}
	// UpdateFSM(DeltaTime);
}
void UCanivalAnimInstance::UpdateFSM(float DeltaTime)
{
	switch (CurrentState)
	{
	case ECanivalState::Idle:
		HandleIdleState();
		break;
		
	case ECanivalState::Move:
		HandleMoveState();
		break;

	case ECanivalState::RaiseHammer:
		HandleRaiseHammerState();
		break;

	case ECanivalState::SwingHammer:
		HandleSwingHammerState();
		break;
	}
}

void UCanivalAnimInstance::HandleIdleState()
{
	if (bInputLMB && bCanAttack)
	{
		ChangeState(ECanivalState::RaiseHammer);
	}
}

void UCanivalAnimInstance::HandleMoveState()
{
	if (!bIsMoving)
	{
		ChangeState(ECanivalState::Idle);
	}
}


void UCanivalAnimInstance::HandleRaiseHammerState()
{
	ElapsedTime+=GetWorld()->GetDeltaSeconds();

	//1초 뒤 자동 휘두르기
	if (ElapsedTime > 1.0f)
	{
		AutoSwingHammer();
	}

	
	//마우스 클릭 해제 시 휘두르기
	else if (!bInputLMB)
	{
		StopSwingHammer();
	}
}

void UCanivalAnimInstance::HandleSwingHammerState()
{
	if (!Montage_IsPlaying(SwingHammerMontage))
	{
		ChangeState(ECanivalState::Idle);
	}

}


void UCanivalAnimInstance::ChangeState(ECanivalState NewState)
{
	if (NewState == CurrentState)
		return;

	CurrentState = NewState;

	UE_LOG(LogTemp, Display, TEXT("State Changed: %s"), *UEnum::GetValueAsString(NewState));

	switch (NewState)
	{
	case ECanivalState::RaiseHammer:
		Montage_Play(RaiseHammerMontage);
		ElapsedTime = 0.0f;
		GetWorld()->GetTimerManager().SetTimer(
			HammerTimerHandle, 
			this, 
			&UCanivalAnimInstance::AutoSwingHammer, 
			1.0f, 
			false
		);
		break;

	case ECanivalState::SwingHammer:
		Montage_Play(SwingHammerMontage);
		break;

	case ECanivalState::Idle:
		ElapsedTime = 0.0f;
		break;
	}
}

//휘두르기

void UCanivalAnimInstance::StartRaiseHammer()
{
	ChangeState(ECanivalState::RaiseHammer);
}

void UCanivalAnimInstance::AutoSwingHammer()
{
	ChangeState(ECanivalState::SwingHammer);
}

void UCanivalAnimInstance::StopSwingHammer()
{
	GetWorld()->GetTimerManager().ClearTimer(HammerTimerHandle);
	ChangeState(ECanivalState::SwingHammer);
}