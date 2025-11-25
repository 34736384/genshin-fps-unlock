using System.Diagnostics;
using System.Text.Json;
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

        private bool _notifyOnce = false;

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
            _ = Task.Run(CheckVersion);

            _windowLocation = Location;
            _windowSize = Size;
            if (_config.AutoStart)
                BtnStartGame_Click(null, null);
            else if (_config.StartMinimized)
                WindowState = FormWindowState.Minimized;
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

            if (_processService.StartGame())
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
            if (!_notifyOnce) {
                NotifyIconMain.Visible = true;
                NotifyIconMain.Text = $@"FPS Unlocker (FPS: {_config.FPSTarget})";
                NotifyIconMain.ShowBalloonTip(500);
                _notifyOnce = true;
            }

            ShowInTaskbar = false;
            Hide();
        }

        private void NotifyIconMain_DoubleClick(object sender, EventArgs e)
        {
            RestoreFromTray();
        }

        private void AboutMenuItem_Click(object sender, EventArgs e)
        {
            var aboutForm = new AboutForm();
            aboutForm.ShowDialog();
        }

        private void StartGameMenuItem_Click(object sender, EventArgs e)
        {
            BtnStartGame_Click(sender, e);
        }

        public void RestoreFromTray()
        {
            if (InvokeRequired) {
                Invoke(RestoreFromTray);
                return;
            }

            WindowState = FormWindowState.Normal;
            ShowInTaskbar = true;
            TopMost = true;
            Show();
            Activate();
            TopMost = false;
            
            Location = _windowLocation;
            Size = _windowSize;
        }

        async Task CheckVersion()
        {

            using var client = new HttpClient();
            try
            {
                var response = await client.GetAsync("https://ys.ex-m.net/fps-unlock/version");
                response.EnsureSuccessStatusCode();
                var content = await response.Content.ReadAsStringAsync();
                var remoteVersion = JsonSerializer.Deserialize<VersionInfo>(content);
                
                if (remoteVersion == null || remoteVersion.Version <= Program.Version)
                    return;

                var utcNow = DateTimeOffset.UtcNow;
                var lastNotify = DateTimeOffset.FromUnixTimeSeconds(_config.LastVersionNotify);
                if (utcNow - lastNotify < TimeSpan.FromDays(7))
                    return;

                var message = $@"A new version is available!{Environment.NewLine}" +
                              $@"Current version: {Program.Version}{Environment.NewLine}" +
                              $@"Latest version: {remoteVersion.Version}{Environment.NewLine}" +
                              $@"Would you like to go to the release page?";

                var result = MessageBox.Show(message, @"FPS Unlocker", MessageBoxButtons.YesNo, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                
                if (result == DialogResult.Yes) {
                    var psi = new ProcessStartInfo
                    {
                        FileName = remoteVersion.Url,
                        UseShellExecute = true
                    };
                    Process.Start(psi);
                }
                else {
                    _config.LastVersionNotify = utcNow.ToUnixTimeSeconds();
                    _configService.Save();
                }

            }
            catch
            {
                // ignored
            }

        }

    }
}
