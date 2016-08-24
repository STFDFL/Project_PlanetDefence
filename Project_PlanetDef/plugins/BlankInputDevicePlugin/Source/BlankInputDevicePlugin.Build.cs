// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using System.IO;
 
namespace UnrealBuildTool.Rules
{
	public class BlankInputDevicePlugin : ModuleRules
	{
		public BlankInputDevicePlugin(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here 
				}
				);
 
			PrivateIncludePaths.AddRange(
				new string[] {
					"Public",
					// ... add other private include paths 
				}
				);
 
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
                    "CoreUObject",
					"Engine",
					"Slate",
					"InputCore",
					"InputDevice",
                 	// ... add other public dependencies that you statically link with here ...
				}
				);
 
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    // ... add private dependencies that you statically link with here ...
				}
				);
 
			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
 
			
		}
	}
}
