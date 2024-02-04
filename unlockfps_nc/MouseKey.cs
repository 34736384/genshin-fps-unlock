using Gma.System.MouseKeyHook;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;
using unlockfps_nc.Model;
using unlockfps_nc.Service;

namespace unlockfps_nc
{

    public sealed class MouseKey
    {
        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool RegisterHotKey(IntPtr? hWnd, int id, int fsModifiers, char vk);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool UnregisterHotKey(IntPtr? hWnd, int id);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        [DllImport("user32.dll")]
        public static extern int GetWindowTextLength(IntPtr hWnd);
        //获取当前活动窗口(当前焦点窗口,键盘可操作的那种)
        [DllImport("user32.dll")]
        static extern IntPtr GetActiveWindow();

        //获取当前置顶窗口(窗口总在最前,类似于QQ那种)
        [DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();
        [DllImport("user32.dll")]
        static extern IntPtr GetShellWindow();
        [DllImport("user32.dll")]
        static extern IntPtr GetDesktopWindow();
        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("user32.dll", EntryPoint = "mouse_event")]
        public static extern void mouse_event(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
        [DllImport("user32.dll", EntryPoint = "keybd_event")]
        public static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);

        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int left;   // x 坐标左上角点
            public int top;    // y 坐标左上角点
            public int right;  // x 坐标右下角点
            public int bottom; // y 坐标右下角点
        }

        const int MOUSEEVENTF_LEFTDOWN = 0x0002;
        const int MOUSEEVENTF_LEFTUP = 0x0004;
        const int MOUSEEVENTF_RIGHTDOWN = 0x0008;
        const int MOUSEEVENTF_RIGHTUP = 0x0010;
        const int KEYEVENTF_KEYUP = 0x0002;
        const int MOUSEEVENTF_MOVE = 0x0001;
        const int MOUSEEVENTF_ABSOLUTE = 0x8000;
        private const int VK_SPACE = 0x20;

        private static MouseKey instance = null;
        Thread threadHotkeyP;
        Thread threadHotkeyH;
        private Config _config;
        private BackgroundWorker backgroundWorker;
        int currentLoop = 0;
        public const int P = (char)11;
        public const int AP = (char)21;
        public const int H = (char)12;
        public const int AH = (char)22;
        public const int S = (char)13;
        public const int AS = (char)23;
        public const int M = (char)14;
        public const int N = (char)15;


        MouseKey()
        {
            backgroundWorker = new BackgroundWorker();
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.WorkerSupportsCancellation = true;
            backgroundWorker.DoWork += new DoWorkEventHandler(hotKey);// todo
            backgroundWorker.RunWorkerAsync();
        }
        public void exit(IntPtr hwnd)
        {
            UnRegHotKey(hwnd, MouseKey.P); //销毁热键
            UnRegHotKey(hwnd, MouseKey.H); //销毁热键
            UnRegHotKey(hwnd, MouseKey.S); //销毁热键
            UnRegHotKey(hwnd, MouseKey.AP); //销毁热键
            UnRegHotKey(hwnd, MouseKey.AH); //销毁热键
            UnRegHotKey(hwnd, MouseKey.AS); //销毁热键
            currentLoop = -1;
            Unsubscribe();
            return;
        }

        void hotKey(Object sender, DoWorkEventArgs e)
        {
            if (null == threadHotkeyP)
            {
                threadHotkeyP = new Thread(loop);
                threadHotkeyP.IsBackground = true;
                threadHotkeyP.Start();
            }
            return;
        }

        public void hook()
        {
            SetupHook();
        }


        public static MouseKey GetInstance()
        {
            if (instance == null)
            {
                instance = new MouseKey();
            }
            return instance;
        }



        public void showTips(int SelectedIndex, String Text, bool isSideKey)
        {
            String tip = isSideKey ? "长按侧键期间生效" : "按下快捷键开始\r\n再次按下快捷键结束";
            switch (SelectedIndex)
            {
                case 4:
                    MessageBox.Show("持续期间不断循环触发那维莱特0.25秒无前摇重击", tip);
                    break;
                case 5:
                    MessageBox.Show("持续期间触发那维莱特0.25秒无前摇重击\r\n并且持续快速转动\r\n" +
                        "能够吸收360°的源水之滴\r\n\r\n", tip);
                    break;
                case 8:
                    MessageBox.Show("更加推荐10AAZ，因为功能暂不稳定，\r\n可能遇到帧率不稳导致重击打不出来，丢失索敌等问题", tip);
                    break;
                case 0:
                    break;
                case 1:
                case 2:
                case 3:
                default:
                    MessageBox.Show(tip, tip);
                    break;
            }
        }


        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool RegisterHotKey(IntPtr hWnd, int id, int fsModifiers, char vk);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool UnregisterHotKey(IntPtr hWnd, int id);


        [Flags()]
        public enum KeyModifiers { None = 0, Alt = 1, Ctrl = 2, Shift = 4, WindowsKey = 8 }

        public static void RegHotKey(IntPtr hwnd, int hotKeyId, KeyModifiers keyModifiers, Keys key)
        {
            if (!RegisterHotKey(hwnd, hotKeyId, (int)keyModifiers, (char)key))
            {
                int errorCode = Marshal.GetLastWin32Error();
                if (errorCode == 1409)
                {
                    //MessageBox.Show("热键被占用 ！");
                }
                else
                {
                    //MessageBox.Show("注册热键失败！错误代码：" + errorCode);
                }
            }
        }

        public static void UnRegHotKey(IntPtr hwnd, int hotKeyId)
        {
            //注销指定的热键
            UnregisterHotKey(hwnd, hotKeyId);
        }


        public bool init(Config c, IntPtr hwnd)
        {
            if (_config != null)
            {
                return false;
            }
            _config = c;

            RegHotKey(hwnd, MouseKey.P, KeyModifiers.Ctrl, Keys.P);
            RegHotKey(hwnd, MouseKey.H, KeyModifiers.Ctrl, Keys.H);
            RegHotKey(hwnd, MouseKey.S, KeyModifiers.Ctrl, Keys.Space);
            RegHotKey(hwnd, MouseKey.AP, KeyModifiers.Alt, Keys.P);
            RegHotKey(hwnd, MouseKey.AH, KeyModifiers.Alt, Keys.H);
            RegHotKey(hwnd, MouseKey.AS, KeyModifiers.Alt, Keys.Space);
            return true;
        }

        private bool isForeGroundGenshin()
        {
            var foregroundHandle = GetForegroundWindow();
            if (foregroundHandle != IntPtr.Zero)
            {
                var titleLength = GetWindowTextLength(foregroundHandle);
                if (titleLength > 0)
                {
                    var sbTitle = new StringBuilder(titleLength + 1);
                    GetWindowText(foregroundHandle, sbTitle, sbTitle.Capacity);
                    return StringBuilder.Equals("Genshin Impact", sbTitle.ToString()) | StringBuilder.Equals("原神", sbTitle.ToString());
                }
            }
            return false;
        }



        private bool CheckFullscreen()
        {
            IntPtr hWnd = GetForegroundWindow();
            RECT rcApp, rcDesk;
            GetWindowRect(GetDesktopWindow(), out rcDesk);
            if (hWnd != GetDesktopWindow() && hWnd != GetShellWindow())
            {
                GetWindowRect(hWnd, out rcApp);
                if (rcApp.left <= rcDesk.left
                    && rcApp.top <= rcDesk.top
                    && rcApp.right >= rcDesk.right
                    && rcApp.bottom >= rcDesk.bottom)
                {
                    return true;
                }
            }
            return false;
        }

        private bool mouseEvent(int sleep1, int sleep2)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            if (sleep1 > 0) Thread.Sleep(sleep1);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            if (sleep2 > 0) Thread.Sleep(sleep2);
            return true;
        }

        private bool keyEvent(byte key, int sleep1, int sleep2)
        {
            keybd_event(key, 0, 0, 0);
            if (sleep1 > 0) Thread.Sleep(sleep1);
            keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
            if (sleep2 > 0) Thread.Sleep(sleep2);
            return true;
        }
        private bool pressd(int x, int y, int sleep)
        {
            if (isForeGroundGenshin())
            {
                mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x * 65536 / 2560, y * 65536 / 1440, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Thread.Sleep(sleep);
                return true;
            }
            return false;
        }

        private void artifactsFastEnhance()
        {
            do
            {
                //keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
            } while (currentLoop == 1 && pressd(200, 288, 100)
                && currentLoop == 1 && pressd(2400, 1040, 100)
                && currentLoop == 1 && pressd(2400, 1350, 400)
                && currentLoop == 1 && pressd(200, 200, 100)
                && currentLoop == 1 && pressd(200, 300, 100));

            currentLoop = 0;
            return;
        }

        private void neuvilletteFastChargeAttack()
        {
            while (currentLoop == 4 && isForeGroundGenshin() && mouseEvent(245, 5)) ;
            currentLoop = 0;
            return;
        }

        private void neuvilletteSpin()
        {
            int count = 0;
            while (currentLoop == 5)
            {
                if (count % 6 == 0)
                {
                    if (isForeGroundGenshin())
                    {
                        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    }
                    else
                    {
                        break;
                    }
                }
                if (count % 6 == 5)
                {
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
                if (count % 8 == 0 || count % 8 == 6)
                {
                    mouse_event(0x00000001, _config.neuvilletteSpinPixels, 0, 0, 0);
                }
                if (count % 8 == 2 || count % 8 == 4)
                {
                    mouse_event(0x00000001, -1 * _config.neuvilletteSpinPixels, 0, 0, 0);
                }

                count++;
                Thread.Sleep(50);
            }
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            currentLoop = 0;
            return;
        }

        private void hutaoAZT()
        {
            while (currentLoop == 6 && isForeGroundGenshin()
                && currentLoop == 6 && mouseEvent(420, 0)
                && currentLoop == 6 && keyEvent(VK_SPACE, 35, 480)) ;
            currentLoop = 0;
            return;
        }

        private void hutaoAAZT()
        {
            while (currentLoop == 7 && isForeGroundGenshin()
                && currentLoop == 7 && mouseEvent(50, 215)
                && currentLoop == 7 && mouseEvent(55, 35)
                && currentLoop == 7 && mouseEvent(275, 10)
                && currentLoop == 7 && keyEvent(VK_SPACE, 45, 480)) ;
            currentLoop = 0;
            return;
        }

        private void hutao11AAZ()
        {
            if (currentLoop == 8 && isForeGroundGenshin())
                while (currentLoop == 8 && mouseEvent(50, 180)
                    && currentLoop == 8 && mouseEvent(50, 30)
                    && currentLoop == 8 && mouseEvent(260, 25)
                    && currentLoop == 8 && keyEvent(0x10, 40, 30)
                    && currentLoop == 8 && keyEvent((byte)'S', 100, 50)
                    && currentLoop == 8 && keyEvent((byte)'W', 30, 25)) ;
            currentLoop = 0;
            return;
        }

        private void hutao()
        {
            if (currentLoop == 2 && isForeGroundGenshin())
                while (currentLoop == 2 && mouseEvent(50, 215)
                && currentLoop == 2 && mouseEvent(55, 35)
                && currentLoop == 2 && mouseEvent(275, 30)
                && currentLoop == 2 && keyEvent(0x10, 45, 25)
                && currentLoop == 2 && keyEvent((byte)'S', 105, 55)
                && currentLoop == 2 && keyEvent((byte)'W', 45, 5)) ;
            currentLoop = 0;
            return;
        }


        private void skip()
        {
            while (currentLoop == 3 && pressd(1800, 1080, 30)) ;
            currentLoop = 0;
            return;
        }

        private void loop()
        {
            while (true)
            {
                switch (currentLoop)
                {
                    case 1:
                        artifactsFastEnhance();
                        break;
                    case 2:
                        hutao();
                        break;
                    case 3:
                        skip();
                        break;
                    case 4:
                        neuvilletteFastChargeAttack();
                        break;
                    case 5:
                        neuvilletteSpin();
                        break;
                    case 6:
                        hutaoAZT();
                        break;
                    case 7:
                        hutaoAAZT();
                        break;
                    case 8:
                        hutao11AAZ();
                        break;
                    case -1:
                        threadHotkeyP = null;
                        return;
                        break;
                    default:
                        break;
                }
            }
        }

        public void deals(int wParam)
        {
            if(_config == null)
            {
                return;
            }
            if (currentLoop < 0)
            {
                return;
            }
            if (wParam < 0)
            {
                currentLoop = 0;
                return;
            }
            if (!isForeGroundGenshin())
            {
                currentLoop = 0;
                return;
            }

            if (!CheckFullscreen())
            {
                MessageBox.Show("仅限全屏模式下生效");
                currentLoop = 0;
                return;
            }
            if (currentLoop != 0)
            {
                currentLoop = 0;
                return;
            }
            switch (wParam)
            {
                case P:
                    if (_config.hotkeyP == 1)
                        currentLoop = _config.valueP;
                    break;
                case S:
                    if (_config.hotkeyS == 1)
                        currentLoop = _config.valueS;
                    break;
                case H:
                    if (_config.hotkeyH == 1)
                        currentLoop = _config.valueH;
                    break;
                case AP:
                    if (_config.hotkeyP == 0)
                        currentLoop = _config.valueP;
                    break;
                case AS:
                    if (_config.hotkeyS == 0)
                        currentLoop = _config.valueS;
                    break;
                case AH:
                    if (_config.hotkeyS == 0)
                        currentLoop = _config.valueH;
                    break;
                case M:
                    currentLoop = _config.valueM;
                    break;
                case N:
                    currentLoop = _config.valueN;
                    break;
            }
        }




        private IKeyboardMouseEvents m_Events;
        private void Subscribe(IKeyboardMouseEvents events)
        {
            m_Events = events;

            m_Events.MouseUp += OnMouseUp;
            m_Events.MouseDown += OnMouseDown;
        }

        private void Unsubscribe()
        {
            if (m_Events == null) return;
            m_Events.MouseUp -= OnMouseUp;
            m_Events.MouseDown -= OnMouseDown;

            m_Events.Dispose();
            m_Events = null;
        }


        private void SubscribeGlobal()
        {
            Unsubscribe();
            Subscribe(Hook.GlobalEvents());
        }


        private void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.XButton1)
                deals(N);
            else if (e.Button == MouseButtons.XButton2)
                deals(M);
        }

        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.XButton1)
                deals(-1);
            else if (e.Button == MouseButtons.XButton2)
                deals(-1);
        }


        public void SetupHook()
        {
            SubscribeGlobal();
            return;
        }

 

    }

}
