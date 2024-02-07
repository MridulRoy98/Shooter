// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity(ShooterCharacter->GetVelocity());
		Velocity.Z = 0;
		Speed = Velocity.Size();
	
		// Check if character in air
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is character Accelerating?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		/* Gets the rotation of the controller,
			gets the rotation of the character with respect to its forward direction,
			then calculates the offset between two rotators */
		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
		float MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		FString hh = FString::Printf(TEXT("%f"), MovementOffsetYaw);

		UE_LOG(LogTemp, Warning, TEXT("Movement Offset Yaw: %s"), *hh);


	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
}
