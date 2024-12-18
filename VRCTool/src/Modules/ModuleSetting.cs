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
		public bool Value;

		public BoolSetting(string name, bool defaultValue) : base(name)
		{
			Value = defaultValue;
		}
	}

	public class FloatSetting : ModuleSetting
	{
		public float Value;

        public float Min { get; private set; }
        public float Max { get; private set; }

        public FloatSetting(string name, float defaultValue, float min, float max) : base(name)
		{
			Value = defaultValue;
			Min = min;
			Max = max;
		}
	}

	public class IntSetting : ModuleSetting
	{
        public int Value;

        public int Min { get; private set; }
        public int Max { get; private set; }

        public IntSetting(string name, int defaultValue, int min, int max) : base(name)
        {
            Value = defaultValue;
			Min = min;
			Max = max;
        }
    }
}
