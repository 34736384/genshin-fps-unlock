using Microsoft.Extensions.DependencyInjection;
using unlockfps_nc.Model;
using unlockfps_nc.Service;

namespace unlockfps_nc
{
    public partial class MainForm : Form
    {
        private Point _windowLocation;
        private Size _windowSize;

        private readonly ConfigService _configService;
        private readonly Config _config;
        private readonly ProcessService _processService;

        public MainForm(
            ConfigService configService,
            ProcessService processService)
        {
            InitializeComponent();
            _configService = configService;
            _config = _configService.Config;
            _processService = processService;
            SetupBindings();
            comboWindowP.SelectedIndex = _config.valueP;
            comboWindowH.SelectedIndex = _config.valueH;
            comboWindowS.SelectedIndex = _config.valueS;
            comboWindowM.SelectedIndex = _config.valueM;
            comboWindowN.SelectedIndex = _config.valueN;
            comboWindowHotKeyP.SelectedIndex = _config.hotkeyP;
            comboWindowHotKeyH.SelectedIndex = _config.hotkeyH;
            comboWindowHotKeyS.SelectedIndex = _config.hotkeyS;

            comboWindowHotKeyP.SelectedIndexChanged += save;
            comboWindowHotKeyH.SelectedIndexChanged += save;
            comboWindowHotKeyS.SelectedIndexChanged += save;
            comboWindowP.SelectedIndexChanged += save;
            comboWindowH.SelectedIndexChanged += save;
            comboWindowS.SelectedIndexChanged += save;
            comboWindowM.SelectedIndexChanged += save;
            comboWindowN.SelectedIndexChanged += save;

            save(null,null);
        }
 


        private const int WM_HOTKEY = 0x312; //窗口消息：热键
        private const int WM_CREATE = 0x1; //窗口消息：创建
        private const int WM_DESTROY = 0x2; //窗口消息：销毁





        protected override void WndProc(ref Message msg)
        {
            base.WndProc(ref msg);
            switch (msg.Msg)
            {
                case WM_HOTKEY: //窗口消息：热键   
                    int tmpWParam = msg.WParam.ToInt32();
                    MouseKey.GetInstance().deals(tmpWParam);
                    break;
                case WM_CREATE: //窗口消息：创建
                    MouseKey.GetInstance().init(_config, this.Handle);
                    MouseKey.GetInstance().hook();
                    break;
                case WM_DESTROY: //窗口消息：销毁
                    //MouseKey.GetInstance().exit(this.Handle);
                    break;
                default:
                    break;
            }
        }
 

        private void SettingsMenuItem_Click(object sender, EventArgs e)
        {
            var settingsForm = Program.ServiceProvider.GetRequiredService<SettingsForm>();
            settingsForm.ShowDialog();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _configService.Save();
            _processService.OnFormClosing();
            NotifyIconMain.Visible = false;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            _windowLocation = Location;
            _windowSize = Size;
            if (_config.AutoStart)
                BtnStartGame_Click(null, null);
        }

        private void SetupBindings()
        {
            InputFPS.DataBindings.Add("Value", _config, "FPSTarget", true, DataSourceUpdateMode.OnPropertyChanged);
            SliderFPS.DataBindings.Add("Value", _config, "FPSTarget", true, DataSourceUpdateMode.OnPropertyChanged);
            CBAutoStart.DataBindings.Add("Checked", _config, "AutoStart", true, DataSourceUpdateMode.OnPropertyChanged);
            inputNeuvilletteSpinPixels.DataBindings.Add("Value", _config, "neuvilletteSpinPixels", true, DataSourceUpdateMode.OnPropertyChanged);
        }

        private void SetupMenuItem_Click(object sender, EventArgs e)
        {
            ShowSetupForm();
        }

 
        public void save(object sender, EventArgs e)
        {
            if (_config.valueP != comboWindowP.SelectedIndex)
                MouseKey.GetInstance().showTips(comboWindowP.SelectedIndex, comboWindowP.Text, false);
            if (_config.valueH != comboWindowH.SelectedIndex)
                MouseKey.GetInstance().showTips(comboWindowH.SelectedIndex, comboWindowH.Text, false);
            if (_config.valueS != comboWindowS.SelectedIndex)
                MouseKey.GetInstance().showTips(comboWindowS.SelectedIndex, comboWindowS.Text, false);
            if (_config.valueM != comboWindowM.SelectedIndex)
                MouseKey.GetInstance().showTips(comboWindowM.SelectedIndex, comboWindowM.Text, true);
            if (_config.valueN != comboWindowN.SelectedIndex)
                MouseKey.GetInstance().showTips(comboWindowN.SelectedIndex, comboWindowN.Text, true);
            _config.hotkeyP = comboWindowHotKeyP.SelectedIndex;
            _config.hotkeyH = comboWindowHotKeyH.SelectedIndex;
            _config.hotkeyS = comboWindowHotKeyS.SelectedIndex;
            _config.valueP = comboWindowP.SelectedIndex;
            _config.valueH = comboWindowH.SelectedIndex;
            _config.valueS = comboWindowS.SelectedIndex;
            _config.valueM = comboWindowM.SelectedIndex;
            _config.valueN = comboWindowN.SelectedIndex;
            inputNeuvilletteSpinPixels.Visible = (_config.valueM == 5 || _config.valueN == 5);
            neuvilletteSpinPixelsTip.Visible = (_config.valueM == 5 || _config.valueN == 5);
            _configService.Save();
        }


        private void BtnStartGame_Click(object sender, EventArgs e)
        {
            if (!File.Exists(_config.GamePath))
                ShowSetupForm();

            if (_processService.Start())
                WindowState = FormWindowState.Minimized;
        }

        private void ShowSetupForm()
        {
            var setupForm = Program.ServiceProvider.GetRequiredService<SetupForm>();
            setupForm.ShowDialog();
        }

        private void ExitMenuItem_Click(object sender, EventArgs e)
        {
            MouseKey.GetInstance().exit(this.Handle);
            Application.Exit();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
                NotifyAndHide();
        }

        private void NotifyAndHide()
        {
            NotifyIconMain.Visible = true;
            NotifyIconMain.Text = $@"FPS Unlocker (FPS: {_config.FPSTarget})";
            NotifyIconMain.ShowBalloonTip(500);

            ShowInTaskbar = false;
            Hide();
        }

        private void NotifyIconMain_DoubleClick(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
            ShowInTaskbar = true;
            Show();
            Activate();

            Location = _windowLocation;
            Size = _windowSize;
        }

        private void AboutMenuItem_Click(object sender, EventArgs e)
        {
            var aboutForm = new AboutForm();
            aboutForm.ShowDialog();
        }
    }
}
