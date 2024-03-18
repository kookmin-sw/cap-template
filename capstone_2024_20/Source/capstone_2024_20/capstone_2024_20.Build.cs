// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class capstone_2024_20 : ModuleRules
{
    public capstone_2024_20(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystemSteam", "OnlineSubsystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "UMG" });


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}