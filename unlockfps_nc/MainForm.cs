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
        }

        private void SettingsMenuItem_Click(object sender, EventArgs e)
        {
            ShowSettingsForm();
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
        }

        private void SetupMenuItem_Click(object sender, EventArgs e)
        {
            ShowSetupForm();
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

        private void SettingsBtn_Click(object sender, EventArgs e)
        {
            ShowSettingsForm();
        }

        private void ShowSettingsForm()
        {
            var settingsForm = Program.ServiceProvider.GetRequiredService<SettingsForm>();
            settingsForm.ShowDialog();
        }
    }
}
