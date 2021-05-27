// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "EnumStateBuilding.h"
#include "Widgets/CoinProgressBar.h"
#include "House.generated.h"

UENUM(BlueprintType)
enum class EStateBuilding : uint8
{
	PreConstruction,
	Construction,
	Production
};

UCLASS()
class CITYBUILDER_API AHouse : public AActor
{
	GENERATED_BODY()

	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponent")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallStaticMeshComponent")
	UStaticMeshComponent* WallStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindowsDoorStaticMeshComponent")
	UStaticMeshComponent* WindowsDoorStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrassStaticMeshComponent")
	UStaticMeshComponent* GrassStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GlassStaticMeshComponent")
	UStaticMeshComponent* GlassStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystemComponent")
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinProgressbarWidget")
	UWidgetComponent* CoinProgressbarWidget;
	// Sets default values for this actor's properties

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerCheckProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerProduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartTimeBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCoinProgressBar* CoinProgressWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStateBuilding StateBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="GD_Options")
	float TimeBuildingHouse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GD_Options")
	FString MaxStorageCoin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GD_Options")
	float ProgressForOneTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AHouse();

	UFUNCTION(BlueprintCallable)
	void StartBuildHouse();

	UFUNCTION(BlueprintCallable)
	void CheckProgressBuilding();

	UFUNCTION(BlueprintCallable)
	void ProductionAndCheckState();
};
