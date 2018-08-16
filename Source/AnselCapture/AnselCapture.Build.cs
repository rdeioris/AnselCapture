// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class AnselCapture : ModuleRules
{
    private string EnginePath
    {
        get { return EngineDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(EnginePath, "Plugins/Runtime/Nvidia/Ansel/ThirdParty/")); }
    }

    private string LibraryPath
    {
        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "NVAnselSDK", "lib")); }
    }

    private string BinariesPath
    {
        get { return Path.GetFullPath(Path.Combine(EnginePath, "Plugins/Runtime/Nvidia/Ansel/Binaries/ThirdParty/")); }
    }

    public AnselCapture(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string NvCameraSDKSourcePath = ThirdPartyPath + "NVAnselSDK/";

        string NvCameraSDKIncPath = NvCameraSDKSourcePath + "include/";
        PublicSystemIncludePaths.Add(NvCameraSDKIncPath);

        string NvCameraSDKLibPath = NvCameraSDKSourcePath + "lib/";
        PublicLibraryPaths.Add(NvCameraSDKLibPath);

        bool FoundAnselDirs = true;
        if (!Directory.Exists(NvCameraSDKSourcePath))
        {
            System.Console.WriteLine(string.Format("Ansel SDK source path not found: {0}", NvCameraSDKSourcePath));
            FoundAnselDirs = false;
        }

        string LibName;
        if ((Target.Platform == UnrealTargetPlatform.Win64 ||
             Target.Platform == UnrealTargetPlatform.Win32)
             && FoundAnselDirs)
        {
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                LibName = "AnselSDK64";
            }
            else
            {
                LibName = "AnselSDK32";
            }

            bool HaveDebugLib = File.Exists(BinariesPath + LibName + "d" + ".dll");

            if (HaveDebugLib &&
                Target.Configuration == UnrealTargetConfiguration.Debug &&
                Target.bDebugBuildsActuallyUseDebugCRT)
            {
                LibName += "d";
            }

            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibName + ".lib"));

            string DLLName = LibName + ".dll";
            PublicDelayLoadDLLs.Add(DLLName);
            RuntimeDependencies.Add(BinariesPath + DLLName);

            PublicDefinitions.Add("WITH_ANSEL=1");
            PublicDefinitions.Add("ANSEL_DLL=" + DLLName);
        }
        else
        {
            PublicDefinitions.Add("WITH_ANSEL=0");
            PublicDefinitions.Add("ANSEL_DLL=");
        }        

        PrivateDependencyModuleNames.AddRange(new string[]
        {
			"Core",
			"CoreUObject",
            "SlateCore",
			"Engine",
		});

        PublicDependencyModuleNames.Add("Engine");
    }
}
