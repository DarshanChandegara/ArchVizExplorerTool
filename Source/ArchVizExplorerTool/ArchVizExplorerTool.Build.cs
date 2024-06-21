// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArchVizExplorerTool : ModuleRules
{
	public ArchVizExplorerTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core",
                "InputCore",
                "EnhancedInput",
                "UMG",
                "Slate",
                "SlateCore",
                 "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "EnhancedInput",
                "HeadMountedDisplay",
                "NavigationSystem",
                "AIModule",
                "Niagara",
                "GameplayTasks",
                "UMG",
                "ProceduralMeshComponent" });

		PrivateDependencyModuleNames.AddRange(new string[] {"Core",
                "InputCore",
                "EnhancedInput",
                "UMG",
                "Slate",
                "SlateCore",
                 "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "EnhancedInput",
                "HeadMountedDisplay",
                "NavigationSystem",
                "AIModule",
                "Niagara",
                "GameplayTasks",
                "UMG",
                "ProceduralMeshComponent"  });
	}
}
