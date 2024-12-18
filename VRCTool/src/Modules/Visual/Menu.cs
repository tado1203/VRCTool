using ImGuiNET;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace VRCTool.Modules.Visual
{
	public class Menu : ModuleBase
	{
		public Menu() : base("Menu", "Shows a menu", ModuleCategory.Visual) { }

		public override void OnImGuiRender()
		{
			if (!DearImGuiInjection.DearImGuiInjection.IsCursorVisible) return;

            ImGui.SetNextWindowSize(new Vector2(400.0f, 400.0f), ImGuiCond.Once);
            ImGui.Begin("VRCTool");

            int numCategory = 1;
            string[] categoryNames = { "Visual" };

            ImGui.BeginTabBar("category");

            for (int i = 0; i < numCategory; ++i)
            {
                ImGui.BeginTabItem(categoryNames[i]);

                foreach (var module in Managers.ModuleManager.Modules)
                {
                    if ((int)module.Category != i) continue;
                    if (module.Name == "Menu") continue;
                    
                    ImGui.Checkbox(module.Name, ref module.IsEnabled);
                    ImGui.TextDisabled(module.Description);

                    foreach (var setting in module.Settings)
                    {
                        switch (setting)
                        {
                            case BoolSetting boolSetting:
                                ImGui.Checkbox(boolSetting.Name, ref boolSetting.Value);
                                break;
                            case FloatSetting floatSetting:
                                ImGui.SliderFloat(floatSetting.Name, ref floatSetting.Value, floatSetting.Min, floatSetting.Max);
                                break;
                            case IntSetting intSetting:
                                ImGui.SliderInt(intSetting.Name, ref intSetting.Value, intSetting.Min, intSetting.Max);
                                break;
                        }
                    }
                }

                ImGui.EndTabItem();
            }


            ImGui.EndTabBar();

            ImGui.End();

        }
	}
}
