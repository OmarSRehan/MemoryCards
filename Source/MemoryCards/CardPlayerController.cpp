#include "CardPlayerController.h"

void ACardPlayerController::BeginPlay() {
	if (InputComponent)
		InputComponent->BindAction("FlipCard", IE_Pressed, this, &ACardPlayerController::ClickCard);
	else
		UE_LOG(LogTemp, Warning, TEXT("InputComponent in PlayerController is null"));
}

void ACardPlayerController::ClickCard() {
	FHitResult OutHit;

	FVector StartPos = PlayerCameraManager->GetCameraLocation();
	FVector ForwardVec = PlayerCameraManager->GetCameraRotation().Vector();
	FVector EndPos = StartPos + (ForwardVec * 1000.0f);

	//UE_LOG(LogTemp, Warning, TEXT("Start Pos: %s"), *StartPos.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("End   Pos: %s"), *EndPos.ToString());

	FCollisionQueryParams CollisionParams;
	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1.0f, 0.0f, 10.0f);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_PhysicsBody, FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	if (bHit) {
		AActor* CardActor = OutHit.GetActor();
		//UE_LOG(LogTemp, Warning, TEXT("%s has been hit"), *CardActor->GetName());
		
		ICard* Card = Cast<ICard>(CardActor->GetComponentByClass(UCardInfoComponent::StaticClass()));
		if (Card)
			Card->HandleClick();
		else
			UE_LOG(LogTemp, Warning, TEXT("Cast to ICard failed"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("no hits"));
	}
}