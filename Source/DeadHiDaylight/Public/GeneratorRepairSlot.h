﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generator.h"
#include "Components/BoxComponent.h"
#include "GeneratorRepairSlot.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADHIDAYLIGHT_API UGeneratorRepairSlot : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGeneratorRepairSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	TObjectPtr<class AGenerator> Generator = nullptr;
	
	FName BindBoneName = FName(NAME_None);
	
	UPROPERTY()
	TObjectPtr<class ACamper> AttachedCamper = nullptr;

	void Init(USkeletalMeshComponent* GeneratorMesh, const FName BoneName);
	void AttachCamper(ACamper* Camper);
	void DetachCamper();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
