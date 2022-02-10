// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblina.h"
#include "GoblinaAnimInstance.h"
#include "Components/WidgetComponent.h"


// Sets default values
AGoblina::AGoblina( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("Name"));
	SetRootComponent(WidgetComp);

}

// Called when the game starts or when spawned
void AGoblina::BeginPlay()
{
	Super::BeginPlay();

	GoblinaAnimRef = Cast<UGoblinaAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AGoblina::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGoblina::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGoblina::StartEatAnimation()
{
	GoblinaAnimRef->bEatRef = true;
}

void AGoblina::StopEatAnimation()
{
	GoblinaAnimRef->bEatRef = false;
}