namespace unlockfps_nc
{
    partial class SettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            LabelAutoSave = new Label();
            TabCtrlSettings = new TabControl();
            TabGeneral = new TabPage();
            ComboPriority = new ComboBox();
            LabelPriority = new Label();
            CBPowerSave = new CheckBox();
            CBAutoClose = new CheckBox();
            CBStartMinimized = new CheckBox();
            TabLaunchOptions = new TabPage();
            CBUseMobileUI = new CheckBox();
            InputMonitorNum = new NumericUpDown();
            LabelMonitor = new Label();
            ComboFullscreenMode = new ComboBox();
            LabelWindowMode = new Label();
            InputResY = new NumericUpDown();
            LabelX = new Label();
            InputResX = new NumericUpDown();
            LabelCustomRes = new Label();
            CBCustomRes = new CheckBox();
            CBFullscreen = new CheckBox();
            CBPopup = new CheckBox();
            TabDlls = new TabPage();
            CBSuspendLoad = new CheckBox();
            BtnRemoveDll = new Button();
            BtnAddDll = new Button();
            ListBoxDlls = new ListBox();
            label1 = new Label();
            ToolTipSettings = new ToolTip(components);
            DllAddDialog = new OpenFileDialog();
            TabCtrlSettings.SuspendLayout();
            TabGeneral.SuspendLayout();
            TabLaunchOptions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputMonitorNum).BeginInit();
            ((System.ComponentModel.ISupportInitialize)InputResY).BeginInit();
            ((System.ComponentModel.ISupportInitialize)InputResX).BeginInit();
            TabDlls.SuspendLayout();
            SuspendLayout();
            // 
            // LabelAutoSave
            // 
            LabelAutoSave.AutoSize = true;
            LabelAutoSave.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            LabelAutoSave.Location = new Point(12, 9);
            LabelAutoSave.Name = "LabelAutoSave";
            LabelAutoSave.Size = new Size(219, 15);
            LabelAutoSave.TabIndex = 0;
            LabelAutoSave.Text = "All settings will be saved automatically";
            // 
            // TabCtrlSettings
            // 
            TabCtrlSettings.Controls.Add(TabGeneral);
            TabCtrlSettings.Controls.Add(TabLaunchOptions);
            TabCtrlSettings.Controls.Add(TabDlls);
            TabCtrlSettings.Location = new Point(12, 27);
            TabCtrlSettings.Name = "TabCtrlSettings";
            TabCtrlSettings.SelectedIndex = 0;
            TabCtrlSettings.Size = new Size(260, 222);
            TabCtrlSettings.TabIndex = 1;
            // 
            // TabGeneral
            // 
            TabGeneral.Controls.Add(ComboPriority);
            TabGeneral.Controls.Add(LabelPriority);
            TabGeneral.Controls.Add(CBPowerSave);
            TabGeneral.Controls.Add(CBAutoClose);
            TabGeneral.Controls.Add(CBStartMinimized);
            TabGeneral.Location = new Point(4, 24);
            TabGeneral.Name = "TabGeneral";
            TabGeneral.Padding = new Padding(3);
            TabGeneral.Size = new Size(252, 194);
            TabGeneral.TabIndex = 0;
            TabGeneral.Text = "General";
            TabGeneral.UseVisualStyleBackColor = true;
            // 
            // ComboPriority
            // 
            ComboPriority.FormattingEnabled = true;
            ComboPriority.Items.AddRange(new object[] { "Realtime", "High", "Above Normal", "Normal", "Below Normal", "Low" });
            ComboPriority.Location = new Point(125, 82);
            ComboPriority.Name = "ComboPriority";
            ComboPriority.Size = new Size(121, 23);
            ComboPriority.TabIndex = 5;
            ComboPriority.Text = "Normal";
            // 
            // LabelPriority
            // 
            LabelPriority.AutoSize = true;
            LabelPriority.Location = new Point(3, 85);
            LabelPriority.Name = "LabelPriority";
            LabelPriority.Size = new Size(122, 15);
            LabelPriority.TabIndex = 4;
            LabelPriority.Text = "Game Process Priority";
            // 
            // CBPowerSave
            // 
            CBPowerSave.AutoSize = true;
            CBPowerSave.Location = new Point(6, 56);
            CBPowerSave.Name = "CBPowerSave";
            CBPowerSave.Size = new Size(97, 19);
            CBPowerSave.TabIndex = 3;
            CBPowerSave.Text = "Power Saving";
            ToolTipSettings.SetToolTip(CBPowerSave, "Sets fps to 10 and low process priority upon losing focus (e.g. tabbing out of game)");
            CBPowerSave.UseVisualStyleBackColor = true;
            // 
            // CBAutoClose
            // 
            CBAutoClose.AutoSize = true;
            CBAutoClose.Location = new Point(6, 31);
            CBAutoClose.Name = "CBAutoClose";
            CBAutoClose.Size = new Size(84, 19);
            CBAutoClose.TabIndex = 2;
            CBAutoClose.Text = "Auto Close";
            ToolTipSettings.SetToolTip(CBAutoClose, "Unlocker will exit upon game closing");
            CBAutoClose.UseVisualStyleBackColor = true;
            // 
            // CBStartMinimized
            // 
            CBStartMinimized.AutoSize = true;
            CBStartMinimized.Location = new Point(6, 6);
            CBStartMinimized.Name = "CBStartMinimized";
            CBStartMinimized.Size = new Size(167, 19);
            CBStartMinimized.TabIndex = 1;
            CBStartMinimized.Text = "Start Minimized (Unlocker)";
            ToolTipSettings.SetToolTip(CBStartMinimized, "Unlocker will minimized to tray on starup");
            CBStartMinimized.UseVisualStyleBackColor = true;
            // 
            // TabLaunchOptions
            // 
            TabLaunchOptions.Controls.Add(CBUseMobileUI);
            TabLaunchOptions.Controls.Add(InputMonitorNum);
            TabLaunchOptions.Controls.Add(LabelMonitor);
            TabLaunchOptions.Controls.Add(ComboFullscreenMode);
            TabLaunchOptions.Controls.Add(LabelWindowMode);
            TabLaunchOptions.Controls.Add(InputResY);
            TabLaunchOptions.Controls.Add(LabelX);
            TabLaunchOptions.Controls.Add(InputResX);
            TabLaunchOptions.Controls.Add(LabelCustomRes);
            TabLaunchOptions.Controls.Add(CBCustomRes);
            TabLaunchOptions.Controls.Add(CBFullscreen);
            TabLaunchOptions.Controls.Add(CBPopup);
            TabLaunchOptions.Location = new Point(4, 24);
            TabLaunchOptions.Name = "TabLaunchOptions";
            TabLaunchOptions.Padding = new Padding(3);
            TabLaunchOptions.Size = new Size(252, 194);
            TabLaunchOptions.TabIndex = 1;
            TabLaunchOptions.Text = "Launch Options";
            TabLaunchOptions.UseVisualStyleBackColor = true;
            // 
            // CBUseMobileUI
            // 
            CBUseMobileUI.AutoSize = true;
            CBUseMobileUI.Location = new Point(6, 81);
            CBUseMobileUI.Name = "CBUseMobileUI";
            CBUseMobileUI.Size = new Size(99, 19);
            CBUseMobileUI.TabIndex = 11;
            CBUseMobileUI.Text = "Use Mobile UI";
            CBUseMobileUI.UseVisualStyleBackColor = true;
            CBUseMobileUI.CheckStateChanged += LaunchOptionsChanged;
            // 
            // InputMonitorNum
            // 
            InputMonitorNum.Location = new Point(111, 168);
            InputMonitorNum.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            InputMonitorNum.Name = "InputMonitorNum";
            InputMonitorNum.Size = new Size(135, 23);
            InputMonitorNum.TabIndex = 10;
            InputMonitorNum.Value = new decimal(new int[] { 1, 0, 0, 0 });
            // 
            // LabelMonitor
            // 
            LabelMonitor.AutoSize = true;
            LabelMonitor.Location = new Point(6, 170);
            LabelMonitor.Name = "LabelMonitor";
            LabelMonitor.Size = new Size(56, 15);
            LabelMonitor.TabIndex = 9;
            LabelMonitor.Text = "Monitor: ";
            // 
            // ComboFullscreenMode
            // 
            ComboFullscreenMode.FormattingEnabled = true;
            ComboFullscreenMode.Items.AddRange(new object[] { "Borderless", "Exclusive" });
            ComboFullscreenMode.Location = new Point(111, 139);
            ComboFullscreenMode.Name = "ComboFullscreenMode";
            ComboFullscreenMode.Size = new Size(135, 23);
            ComboFullscreenMode.TabIndex = 8;
            ComboFullscreenMode.Text = "Borderless";
            // 
            // LabelWindowMode
            // 
            LabelWindowMode.AutoSize = true;
            LabelWindowMode.Location = new Point(6, 142);
            LabelWindowMode.Name = "LabelWindowMode";
            LabelWindowMode.Size = new Size(97, 15);
            LabelWindowMode.TabIndex = 7;
            LabelWindowMode.Text = "Fullscreen Mode:";
            // 
            // InputResY
            // 
            InputResY.Location = new Point(191, 110);
            InputResY.Maximum = new decimal(new int[] { 4320, 0, 0, 0 });
            InputResY.Minimum = new decimal(new int[] { 200, 0, 0, 0 });
            InputResY.Name = "InputResY";
            InputResY.Size = new Size(55, 23);
            InputResY.TabIndex = 6;
            InputResY.Value = new decimal(new int[] { 1080, 0, 0, 0 });
            // 
            // LabelX
            // 
            LabelX.AutoSize = true;
            LabelX.Location = new Point(172, 112);
            LabelX.Name = "LabelX";
            LabelX.Size = new Size(13, 15);
            LabelX.TabIndex = 5;
            LabelX.Text = "x";
            // 
            // InputResX
            // 
            InputResX.Location = new Point(111, 110);
            InputResX.Maximum = new decimal(new int[] { 7680, 0, 0, 0 });
            InputResX.Minimum = new decimal(new int[] { 200, 0, 0, 0 });
            InputResX.Name = "InputResX";
            InputResX.Size = new Size(55, 23);
            InputResX.TabIndex = 4;
            InputResX.Value = new decimal(new int[] { 1920, 0, 0, 0 });
            // 
            // LabelCustomRes
            // 
            LabelCustomRes.AutoSize = true;
            LabelCustomRes.Location = new Point(6, 112);
            LabelCustomRes.Name = "LabelCustomRes";
            LabelCustomRes.Size = new Size(69, 15);
            LabelCustomRes.TabIndex = 3;
            LabelCustomRes.Text = "Resolution: ";
            // 
            // CBCustomRes
            // 
            CBCustomRes.AutoSize = true;
            CBCustomRes.Location = new Point(6, 56);
            CBCustomRes.Name = "CBCustomRes";
            CBCustomRes.Size = new Size(127, 19);
            CBCustomRes.TabIndex = 2;
            CBCustomRes.Text = "Custom Resolution";
            CBCustomRes.UseVisualStyleBackColor = true;
            CBCustomRes.CheckStateChanged += LaunchOptionsChanged;
            // 
            // CBFullscreen
            // 
            CBFullscreen.AutoSize = true;
            CBFullscreen.Location = new Point(6, 31);
            CBFullscreen.Name = "CBFullscreen";
            CBFullscreen.Size = new Size(79, 19);
            CBFullscreen.TabIndex = 1;
            CBFullscreen.Text = "Fullscreen";
            CBFullscreen.UseVisualStyleBackColor = true;
            CBFullscreen.CheckStateChanged += LaunchOptionsChanged;
            // 
            // CBPopup
            // 
            CBPopup.AutoSize = true;
            CBPopup.Location = new Point(6, 6);
            CBPopup.Name = "CBPopup";
            CBPopup.Size = new Size(127, 19);
            CBPopup.TabIndex = 0;
            CBPopup.Text = "Borderless Window";
            CBPopup.UseVisualStyleBackColor = true;
            CBPopup.CheckStateChanged += LaunchOptionsChanged;
            // 
            // TabDlls
            // 
            TabDlls.Controls.Add(CBSuspendLoad);
            TabDlls.Controls.Add(BtnRemoveDll);
            TabDlls.Controls.Add(BtnAddDll);
            TabDlls.Controls.Add(ListBoxDlls);
            TabDlls.Controls.Add(label1);
            TabDlls.Location = new Point(4, 24);
            TabDlls.Name = "TabDlls";
            TabDlls.Padding = new Padding(3);
            TabDlls.Size = new Size(252, 194);
            TabDlls.TabIndex = 2;
            TabDlls.Text = "DLLs";
            TabDlls.UseVisualStyleBackColor = true;
            // 
            // CBSuspendLoad
            // 
            CBSuspendLoad.AutoSize = true;
            CBSuspendLoad.Location = new Point(138, 79);
            CBSuspendLoad.Name = "CBSuspendLoad";
            CBSuspendLoad.Size = new Size(100, 19);
            CBSuspendLoad.TabIndex = 4;
            CBSuspendLoad.Text = "Suspend Load";
            ToolTipSettings.SetToolTip(CBSuspendLoad, "This can ensure dll gets loaded before the game starts\r\nIt may not work all the times\r\nUncheck this if the game crashes");
            CBSuspendLoad.UseVisualStyleBackColor = true;
            // 
            // BtnRemoveDll
            // 
            BtnRemoveDll.Location = new Point(132, 50);
            BtnRemoveDll.Name = "BtnRemoveDll";
            BtnRemoveDll.Size = new Size(114, 23);
            BtnRemoveDll.TabIndex = 3;
            BtnRemoveDll.Text = "Remove";
            BtnRemoveDll.UseVisualStyleBackColor = true;
            BtnRemoveDll.Click += BtnRemoveDll_Click;
            // 
            // BtnAddDll
            // 
            BtnAddDll.Location = new Point(132, 21);
            BtnAddDll.Name = "BtnAddDll";
            BtnAddDll.Size = new Size(114, 23);
            BtnAddDll.TabIndex = 2;
            BtnAddDll.Text = "Add";
            BtnAddDll.UseVisualStyleBackColor = true;
            BtnAddDll.Click += BtnAddDll_Click;
            // 
            // ListBoxDlls
            // 
            ListBoxDlls.FormattingEnabled = true;
            ListBoxDlls.ItemHeight = 15;
            ListBoxDlls.Location = new Point(6, 21);
            ListBoxDlls.Name = "ListBoxDlls";
            ListBoxDlls.Size = new Size(120, 169);
            ListBoxDlls.TabIndex = 1;
            ListBoxDlls.Format += ListBoxDlls_Format;
            ListBoxDlls.MouseMove += ListBoxDlls_MouseMove;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 3);
            label1.Name = "label1";
            label1.Size = new Size(232, 15);
            label1.TabIndex = 0;
            label1.Text = "DLLs will be injected in the order of this list";
            // 
            // ToolTipSettings
            // 
            ToolTipSettings.AutoPopDelay = 5000;
            ToolTipSettings.InitialDelay = 500;
            ToolTipSettings.ReshowDelay = 500;
            // 
            // DllAddDialog
            // 
            DllAddDialog.Filter = "DLL (*.dll)|*.dll|All files (*.*)|*.*";
            DllAddDialog.Multiselect = true;
            DllAddDialog.RestoreDirectory = true;
            // 
            // SettingsForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(284, 261);
            Controls.Add(TabCtrlSettings);
            Controls.Add(LabelAutoSave);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "SettingsForm";
            StartPosition = FormStartPosition.CenterParent;
            Text = "Settings";
            FormClosing += SettingsForm_FormClosing;
            Load += SettingsForm_Load;
            TabCtrlSettings.ResumeLayout(false);
            TabGeneral.ResumeLayout(false);
            TabGeneral.PerformLayout();
            TabLaunchOptions.ResumeLayout(false);
            TabLaunchOptions.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)InputMonitorNum).EndInit();
            ((System.ComponentModel.ISupportInitialize)InputResY).EndInit();
            ((System.ComponentModel.ISupportInitialize)InputResX).EndInit();
            TabDlls.ResumeLayout(false);
            TabDlls.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label LabelAutoSave;
        private TabControl TabCtrlSettings;
        private TabPage TabGeneral;
        private TabPage TabLaunchOptions;
        private TabPage TabDlls;
        private ComboBox ComboPriority;
        private Label LabelPriority;
        private CheckBox CBPowerSave;
        private CheckBox CBAutoClose;
        private CheckBox CBStartMinimized;
        private NumericUpDown InputResY;
        private Label LabelX;
        private NumericUpDown InputResX;
        private Label LabelCustomRes;
        private CheckBox CBCustomRes;
        private CheckBox CBFullscreen;
        private CheckBox CBPopup;
        private NumericUpDown InputMonitorNum;
        private Label LabelMonitor;
        private ComboBox ComboFullscreenMode;
        private Label LabelWindowMode;
        private Label label1;
        private ListBox ListBoxDlls;
        private Button BtnRemoveDll;
        private Button BtnAddDll;
        private ToolTip ToolTipSettings;
        private CheckBox CBSuspendLoad;
        private CheckBox CBUseMobileUI;
        private OpenFileDialog DllAddDialog;
    }
}