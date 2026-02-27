// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "AI/SS_Enemy_ai_controller.h"
#include "Characters/SS_Shooter_character.h"

// Unreal headers.
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"



ASS_Enemy_ai_controller::ASS_Enemy_ai_controller()
{
	// Set AI Behavior Tree.
	static  ConstructorHelpers::FObjectFinder<UBehaviorTree> ai_behavior_tree_container(*behavior_tree_path_);
	if (ai_behavior_tree_container.Succeeded())
	{
		ai_behavior_tree_ = ai_behavior_tree_container.Object;
	}
}

auto ASS_Enemy_ai_controller::BeginPlay() -> void
{
	Super::BeginPlay();

	if (ai_behavior_tree_ != nullptr)
	{
		APawn* player_pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// Run AI behavior actions with behavior tree.
		RunBehaviorTree(ai_behavior_tree_);
		// Set starting location so Enemy knows where to return to.
		GetBlackboardComponent()->SetValueAsVector(TEXT("start_location"), GetPawn()->GetActorLocation());
	}
}

auto ASS_Enemy_ai_controller::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);
}

auto ASS_Enemy_ai_controller::b_is_dead() const -> bool
{
	// Find out if player is dead.
	if (ASS_Shooter_character* controlled_character = Cast<ASS_Shooter_character>(GetPawn()))
	{
		return controlled_character->get_is_dead();
	}

	return true;
}