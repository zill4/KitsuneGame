// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Kitsune : ModuleRules
{
	public Kitsune(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
                                                            "Http", "Json", "JsonUtilities",
                                                            "UMG", "EnhancedInput" });

        PublicDependencyModuleNames.Add("GameplayAbilities");
        PublicDependencyModuleNames.Add("OnlineSubsystem");
        PublicDependencyModuleNames.Add("GameplayAbilities");
        PublicDependencyModuleNames.Add("GameplayTags");
        PublicDependencyModuleNames.Add("GameplayTasks");

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
