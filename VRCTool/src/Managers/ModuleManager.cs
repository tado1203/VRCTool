using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VRCTool.Managers
{
	using VRCTool.Modules;
    using VRCTool.Modules.Visual;

    public class ModuleManager
	{
		public static List<ModuleBase> Modules = new List<ModuleBase>();

		public static void Init()
		{
            Modules.Add(new Menu());
		}

		public static void UpdateModules()
		{
			foreach (var module in Modules)
			{
				module.CheckKeyBind();
				module.OnUpdate();
			}
		}

		public static void RenderModules()
		{
			foreach (var module in Modules)
			{
				module.OnImGuiRender();
			}
		}
	}
}
