// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetTextLibrary.h"
#include "GameFramework/GameStateBase.h"

// Sets default values
AHouse::AHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	WallStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallStaticMeshComponent"));
	WallStaticMeshComponent->SetupAttachment(SceneComponent);
	WindowsDoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WindowsDoorStaticMeshComponent"));
	WindowsDoorStaticMeshComponent->SetupAttachment(SceneComponent);
	GrassStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrassStaticMeshComponent"));
	GrassStaticMeshComponent->SetupAttachment(SceneComponent);
	GlassStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassStaticMeshComponent"));
	GlassStaticMeshComponent->SetupAttachment(SceneComponent);
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(SceneComponent);
	CoinProgressbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CoinProgressbarWidget"));
	CoinProgressbarWidget->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{
	Super::BeginPlay();

	CoinProgressWidget = Cast<UCoinProgressBar>(CoinProgressbarWidget->GetUserWidgetObject());
}

// Called every frame
void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHouse::StartBuildHouse()
{
	StateBuilding = EStateBuilding::Construction;
	ParticleSystemComponent->Activate();
	WallStaticMeshComponent->SetHiddenInGame(true);
	GlassStaticMeshComponent->SetHiddenInGame(true);
	WindowsDoorStaticMeshComponent->SetHiddenInGame(true);
	StartTimeBuilding = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	GetWorld()->GetTimerManager().SetTimer(TimerCheckProgress, this, &AHouse::CheckProgressBuilding, 1.f, true);
}

void AHouse::CheckProgressBuilding() 
{
	if ((StartTimeBuilding + (TimeBuildingHouse / 4)) <= GetWorld()->GetGameState()->GetServerWorldTimeSeconds()) 
	{
		WindowsDoorStaticMeshComponent->SetHiddenInGame(false);
		if ((StartTimeBuilding + (TimeBuildingHouse / 2)) <= GetWorld()->GetGameState()->GetServerWorldTimeSeconds())
		{
			GlassStaticMeshComponent->SetHiddenInGame(false);
			if ((StartTimeBuilding + (TimeBuildingHouse / 1.2)) <= GetWorld()->GetGameState()->GetServerWorldTimeSeconds())
			{
				WallStaticMeshComponent->SetHiddenInGame(false);
				if ((StartTimeBuilding + TimeBuildingHouse ) <= GetWorld()->GetGameState()->GetServerWorldTimeSeconds())
				{
					ParticleSystemComponent->Deactivate();
					GetWorld()->GetTimerManager().ClearTimer(TimerCheckProgress);
					TimerCheckProgress.Invalidate();
					CoinProgressbarWidget->SetHiddenInGame(false);
					StateBuilding = EStateBuilding::Production;
					GetWorld()->GetTimerManager().SetTimer(TimerProduction, this, &AHouse::ProductionAndCheckState, 1.f, true);
				}
			}
		}
	}
}

void AHouse::ProductionAndCheckState()
{
	
	if (CoinProgressWidget->CountCoin_Text->GetText().ToString() != MaxStorageCoin)
	{
		CoinProgressWidget->Production_ProgressBar->SetPercent(CoinProgressWidget->Production_ProgressBar->Percent + ProgressForOneTime);
		if (CoinProgressWidget->Production_ProgressBar->Percent == 1.0)
		{
			CoinProgressWidget->UpdateCountCoins();
			CoinProgressWidget->Production_ProgressBar->SetPercent(0.0);
		}
	}
	else
	{
		CoinProgressWidget->Production_ProgressBar->SetPercent(1.0);
		CoinProgressWidget->SetTextMaxCountCoins(FText::FromString("max"));
		GetWorld()->GetTimerManager().ClearTimer(TimerProduction);
		TimerProduction.Invalidate();
	}
}