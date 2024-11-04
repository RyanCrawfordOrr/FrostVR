/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

using UnrealBuildTool;
using System.IO;

public class EmbeddedVoiceChatLibrary : ModuleRules
{
    public EmbeddedVoiceChatLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        CppStandard = CppStandardVersion.Cpp17;

        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "libdatachannel"));
        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "miniaudio"));
        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "rnnoise"));
        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "socketio"));

        PublicDependencyModuleNames.AddRange(new string[] { "libOpus" });

//         PublicDefinitions.Add("EMBEDDED_VOICE_CHAT_USE_IMPORT_EXPORT=1");
        PublicDefinitions.Add("RTC_ENABLE_MEDIA=0");
        PublicDefinitions.Add("RTC_ENABLE_WEBSOCKET=0");
        PublicDefinitions.Add("Allow_Voice_Debug=0");

        string ThirdPartyPath = System.IO.Path.Combine(ModuleDirectory, Target.Platform.ToString());

        if (Target.Type != TargetRules.TargetType.Server)
        {
            if (Target.Platform == UnrealTargetPlatform.Linux)
            {
		ThirdPartyPath = System.IO.Path.Combine(ThirdPartyPath, "x86_64-unknown-linux-gnu");

                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "librnnoise.a"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libusrsctp.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libjuice-static.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libdatachannel-static.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libsioclient_tls.a"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libEmbeddedVoiceChat.a"));
            }
		else if (Target.Platform == UnrealTargetPlatform.LinuxArm64) {
			ThirdPartyPath = System.IO.Path.Combine(ThirdPartyPath, "aarch64-unknown-linux-gnu");

                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "librnnoise.a"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libusrsctp.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libjuice-static.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libdatachannel-static.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libsioclient_tls.a"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libEmbeddedVoiceChat.a"));
		}
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(ModuleDirectory, "EmbeddedVoiceChatSDK_UPL.xml"));

                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

                {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libsrtp2.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libjuice-static.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libusrsctp.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libdatachannel-static.a"));

                   PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libsioclient_tls.a"));

                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "librnnoise.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libEmbeddedVoiceChat.a"));
                }

                {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libsrtp2.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libjuice-static.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libusrsctp.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libdatachannel-static.a"));

                   PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libsioclient_tls.a"));

                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "librnnoise.a"));
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libEmbeddedVoiceChat.a"));
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
          
             	PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "EmbeddedVoiceChat.lib"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "sioclient_tls.lib"));

             	PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "datachannel-static.lib"));
             	PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "juice-static.lib"));
             	PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "usrsctp.lib"));

             	PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "librnnoise-0.lib"));

				string BinariesDirectory = System.IO.Path.Combine(PluginDirectory, "Binaries", Target.Platform.ToString());
				if (!Directory.Exists(BinariesDirectory))
				{
					Directory.CreateDirectory(BinariesDirectory);
				}

				if (File.Exists(System.IO.Path.Combine(BinariesDirectory, "librnnoise-0.dll")) == false)
				{
					File.Copy(System.IO.Path.Combine(ThirdPartyPath, "librnnoise-0.dll"), System.IO.Path.Combine(BinariesDirectory, "librnnoise-0.dll"));
				}

                RuntimeDependencies.Add(System.IO.Path.Combine("$(BinaryOutputDir)", "librnnoise-0.dll"), System.IO.Path.Combine(ThirdPartyPath, "librnnoise-0.dll"));
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
               AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "librnnoise.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libjuice-static.a"));
               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libusrsctp.a"));
               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libdatachannel-static.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libsioclient_tls.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libEmbeddedVoiceChat.a"));
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "librnnoise.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libjuice-static.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libsrtp2.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libusrsctp.a"));
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libdatachannel-static.a"));

               PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libsioclient_tls.a"));

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libEmbeddedVoiceChat.a"));
            }
            }
        }
    }
