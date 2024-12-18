using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace VRCTool.Modules
{
    public enum ModuleCategory
    {
        Visual
    }

    public abstract class ModuleBase
    {
        public bool IsEnabled;

        public string Name { get; private set; }
        public string Description { get; private set; }
        public ModuleCategory Category { get; private set; }
        public KeyCode KeyBind { get; private set; }
        public List<ModuleSetting> Settings { get; private set; } = new List<ModuleSetting>();

        protected ModuleBase(string name, string desc, ModuleCategory category, KeyCode key = KeyCode.None)
        {
            Name = name;
            Description = desc;
            Category = category;
            KeyBind = key;
        }

        public virtual void OnUpdate() { }
        public virtual void OnImGuiRender() { }

        public void Toggle()
        {
            IsEnabled = !IsEnabled;
        }

        public void AddSetting(ModuleSetting setting)
        {
            Settings.Add(setting);
        }

        public void CheckKeyBind()
        {
            if (KeyBind != KeyCode.None && Input.GetKeyDown(KeyBind))
            {
                Toggle();
            }
        }
    }
}
