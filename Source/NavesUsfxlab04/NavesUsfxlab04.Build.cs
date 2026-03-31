// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NavesUsfxlab04 : ModuleRules
{
	public NavesUsfxlab04(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
