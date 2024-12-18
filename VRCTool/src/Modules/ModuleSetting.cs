using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VRCTool.Modules
{
	public abstract class ModuleSetting
	{
		public string Name { get; private set; }

		protected ModuleSetting(string name)
		{
			Name = name;
		}
	}

	public class BoolSetting : ModuleSetting
	{
		public bool Value { get; set; }

		public BoolSetting(string name, bool defaultValue) : base(name)
		{
			Value = defaultValue;
		}
	}

	public class FloatSetting : ModuleSetting
	{ 
		public float Value { get; set; }

		public FloatSetting(string name, float defaultValue) : base(name)
		{
			Value = defaultValue;
		}
	}

	public class IntSetting : ModuleSetting
	{
        public int Value { get; set; }

        public IntSetting(string name, int defaultValue) : base(name)
        {
            Value = defaultValue;
        }
    }
}
