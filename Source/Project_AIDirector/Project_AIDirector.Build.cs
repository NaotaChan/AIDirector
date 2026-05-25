// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_AIDirector : ModuleRules
{
	public Project_AIDirector(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTags" });
    }
}
