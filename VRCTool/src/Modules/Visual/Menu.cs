using ImGuiNET;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VRCTool.Modules.Visual
{
	public class Menu : ModuleBase
	{
		public Menu() : base("Menu", "Shows a menu", ModuleCategory.Visual) { }

		public override void OnImGuiRender()
		{
			if (DearImGuiInjection.DearImGuiInjection.IsCursorVisible)
			{
				ImGui.Begin("VRCTool");
				ImGui.End();
			}
		}
	}
}
