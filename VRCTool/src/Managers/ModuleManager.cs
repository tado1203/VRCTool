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
		private static readonly List<ModuleBase> _modules = new List<ModuleBase>();

		public static void Init()
		{
            _modules.Add(new Menu());
		}

		public static void UpdateModules()
		{
			foreach (var module in _modules)
			{
				module.CheckKeyBind();
				module.OnUpdate();
			}
		}

		public static void RenderModules()
		{
			foreach (var module in _modules)
			{
				module.OnImGuiRender();
			}
		}
	}
}
