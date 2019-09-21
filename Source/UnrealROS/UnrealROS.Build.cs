using UnrealBuildTool;
using System.IO;

public class UnrealROS : ModuleRules
{
    public UnrealROS(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateIncludePaths.AddRange(new string[] { "UnrealROS/Private" });
        //PublicIncludePaths.AddRange(new string[] { "UnrealROS/Public" });
        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core" });
		PrivatePCHHeaderFile = "Private/UnrealROSPrivatePCH.h";

    }
}
