using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.PortableExecutable;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using unlockfps_nc.Model;
using unlockfps_nc.Service;

namespace unlockfps_nc
{
    public partial class SettingsForm : Form
    {
        private readonly ConfigService _configService;
        private readonly Config _config;

        public SettingsForm(ConfigService configService)
        {
            InitializeComponent();
            _configService = configService;
            _config = _configService.Config;

            SetupBindings();
        }

        private void SetupBindings()
        {
            // General
            CBStartMinimized.DataBindings.Add("Checked", _config, "StartMinimized", true, DataSourceUpdateMode.OnPropertyChanged);
            CBAutoClose.DataBindings.Add("Checked", _config, "AutoClose", true, DataSourceUpdateMode.OnPropertyChanged);
            CBPowerSave.DataBindings.Add("Checked", _config, "UsePowerSave", true, DataSourceUpdateMode.OnPropertyChanged);
            ComboPriority.DataBindings.Add("SelectedIndex", _config, "Priority", true, DataSourceUpdateMode.OnPropertyChanged);
            
            // Launch Options
            CBPopup.DataBindings.Add("Checked", _config, "PopupWindow", true, DataSourceUpdateMode.OnPropertyChanged);
            CBFullscreen.DataBindings.Add("Checked", _config, "Fullscreen", true, DataSourceUpdateMode.OnPropertyChanged);
            CBCustomRes.DataBindings.Add("Checked", _config, "UseCustomRes", true, DataSourceUpdateMode.OnPropertyChanged);
            InputResX.DataBindings.Add("Value", _config, "CustomResX", true, DataSourceUpdateMode.OnPropertyChanged);
            InputResY.DataBindings.Add("Value", _config, "CustomResY", true, DataSourceUpdateMode.OnPropertyChanged);
            ComboFullscreenMode.DataBindings.Add("SelectedIndex", _config, "IsExclusiveFullscreen", true, DataSourceUpdateMode.OnPropertyChanged);
            InputMonitorNum.DataBindings.Add("Value", _config, "MonitorNum", true, DataSourceUpdateMode.OnPropertyChanged);

            // DLLs            
            RefreshDllList();
            CBSuspendLoad.DataBindings.Add("Checked", _config, "SuspendLoad", true, DataSourceUpdateMode.OnPropertyChanged);
        }

        private void RefreshDllList()
        {
            _config.DllList = _config.DllList
                .Where(VerifyDll)
                .ToList();

            ListBoxDlls.Items.Clear();
            ListBoxDlls.Items.AddRange(_config.DllList.ToArray());
        }

        private void UpdateControlState()
        {
            if (_config.PopupWindow) // they can't coexist (?) so disable the other
                _config.Fullscreen = false;

            CBPopup.Enabled = !_config.Fullscreen;
            CBFullscreen.Enabled = !_config.PopupWindow;
            InputResX.Enabled = _config.UseCustomRes;
            InputResY.Enabled = _config.UseCustomRes;
            ComboFullscreenMode.Enabled = _config is { Fullscreen: true, PopupWindow: false };
        }

        public void LaunchOptionsChanged(object sender, EventArgs e)
        {
            UpdateControlState();
        }

        private void SettingsForm_Load(object sender, EventArgs e)
        {
            UpdateControlState();
        }

        private void SettingsForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _configService.Save();
        }

        private void BtnAddDll_Click(object sender, EventArgs e)
        {
            if (DllAddDialog.ShowDialog() != DialogResult.OK)
                return;
            
            var selectedFiles = DllAddDialog.FileNames.ToList();
            selectedFiles = selectedFiles
                .Where(x => VerifyDll(x) || MessageBox.Show(
                    $@"Invalid File: {Environment.NewLine}{x}{Environment.NewLine}{Environment.NewLine}Only native x64 dlls are supported",
                    @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error) != DialogResult.OK)
                .Where(x => !_config.DllList.Contains(x))
                .ToList();

            _config.DllList.AddRange(selectedFiles);
            RefreshDllList();
        }

        private bool VerifyDll(string fullPath)
        {
            if (!File.Exists(fullPath))
                return false;

            using var fs = new FileStream(fullPath, FileMode.Open, FileAccess.Read);
            using var peReader = new PEReader(fs);

            if (peReader.HasMetadata)
                return false;

            return peReader.PEHeaders.CoffHeader.Machine == Machine.Amd64;
        }

        private void ListBoxDlls_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = Path.GetFileName(e.Value as string);
        }

        private void ListBoxDlls_MouseMove(object sender, MouseEventArgs e)
        {
            var index = ListBoxDlls.IndexFromPoint(e.Location);
            if (index == -1)
                return;

            var toolTipText = _config.DllList[index];
            ToolTipSettings.SetToolTip(ListBoxDlls, toolTipText);
        }

        private void BtnRemoveDll_Click(object sender, EventArgs e)
        {
            var selectedIndex = ListBoxDlls.SelectedIndex;
            if (selectedIndex == -1)
                return;
            
            _config.DllList.RemoveAt(selectedIndex);
            RefreshDllList();
        }
    }
}
