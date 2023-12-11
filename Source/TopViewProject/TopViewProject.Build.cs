// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopViewProject : ModuleRules
{
	public TopViewProject(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("SlateCore");

        PublicDependencyModuleNames.Add("AIModule");
        PublicDependencyModuleNames.Add("GameplayTasks");
        PublicDependencyModuleNames.Add("NavigationSystem");

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Niagara" });
	}
}
