// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblina.h"
#include "GoblinaEatAnimNotify.h"
#include "Animation/AnimInstance.h"

UGoblinaEatAnimNotify::UGoblinaEatAnimNotify()
{

}

void UGoblinaEatAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        AGoblina* GoblinaRef = Cast<AGoblina>(MeshComp->GetOwner());
        if (GoblinaRef)
        {
            GoblinaRef->StopEatAnimation();
        }
    }

}

/*
void UEndAnimationsAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        APlayerBehaviour* Player = Cast<APlayerBehaviour>(MeshComp->GetOwner());
        if (Player)
        {
            Player->bInteracting = false;
            Player->GetCharacterMovement()->SetMovementMode((EMovementMode::MOVE_Walking));
        }
    }
}
*/