using BepInEx;
using BepInEx.Logging;
using BepInEx.Unity.IL2CPP;
using System;
using UnityEngine;

namespace VRCTool
{
	[BepInPlugin(MyPluginInfo.PLUGIN_GUID, MyPluginInfo.PLUGIN_NAME, MyPluginInfo.PLUGIN_VERSION)]
	public class Plugin : BasePlugin
	{
		internal static new ManualLogSource Log;

		public override void Load()
		{
			Log = base.Log;
			Log.LogInfo($"Plugin {MyPluginInfo.PLUGIN_GUID} is loaded!");
            Managers.ModuleManager.Init();
            DearImGuiInjection.DearImGuiInjection.Render += Managers.ModuleManager.RenderModules;
			AddComponent<MainMonoBehaviour>();
		}
	}

	public class MainMonoBehaviour : MonoBehaviour
	{
		public MainMonoBehaviour(IntPtr handle) : base(handle) { }

		private void Update()
		{
			Managers.ModuleManager.UpdateModules();
        }
	}
}
