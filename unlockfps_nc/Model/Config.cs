using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace unlockfps_nc.Model
{
    public class Config
    {
        public string GamePath { get; set; } = "";

        public bool AutoStart { get; set; }
        public bool AutoClose { get; set; }
        public bool PopupWindow { get; set; }
        public bool Fullscreen { get; set; } = true;

        public int hotkeyP { get; set; } = 0;
        public int hotkeyH { get; set; } = 0;
        public int hotkeyS { get; set; } = 0;
        public int valueP { get; set; } = 1;
        public int valueH { get; set; } = 2;
        public int valueS { get; set; } = 3;
        public int valueM { get; set; } = 5;
        public int valueN { get; set; } = 2;
        public int neuvilletteSpinPixels { get; set; } = 15000;
         
        public bool UseCustomRes { get; set; }
        public bool IsExclusiveFullscreen { get; set; }
        public bool StartMinimized { get; set; }
        public bool UsePowerSave { get; set; }
        public bool SuspendLoad { get; set; }
        public bool UseMobileUI { get; set; }

        public int FPSTarget { get; set; } = 120;
        public int CustomResX { get; set; } = 1920;
        public int CustomResY { get; set; } = 1080;
        public int MonitorNum { get; set; } = 1;
        public int Priority { get; set; } = 3;

        public List<string> DllList { get; set; } = new();
    }
}
