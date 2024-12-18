using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VRC.SDKBase;

namespace VRCTool.src.SDK
{
    public class SDK
    {
        public static bool IsInWorld()
        {
            return Networking.LocalPlayer != null;
        }
    }
}
