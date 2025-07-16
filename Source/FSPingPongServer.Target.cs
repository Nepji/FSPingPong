using UnrealBuildTool;
using System.Collections.Generic;

public class FSPingPongServerTarget : TargetRules
{
    public FSPingPongServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        ExtraModuleNames.AddRange(new string[] { "FSPingPong" });
    }
}