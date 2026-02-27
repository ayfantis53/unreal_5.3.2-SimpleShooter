// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// ____________________________	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "AI/SS_Bt_service_player_location.h"

// Unreal headers.
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


USS_Bt_service_player_location::USS_Bt_service_player_location()
{
	NodeName = TEXT("Update Player Location");
}

auto USS_Bt_service_player_location::TickNode(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float delta_seconds) -> void
{
	Super::TickNode(owner_comp, node_memory, delta_seconds);

	// Make sure Player exists.
	APawn* player_pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (player_pawn == nullptr)
	{
		return;
	}

	// Set Player's location so enemy AI knows where to move to, to attack.
	owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), player_pawn->GetActorLocation());
}


