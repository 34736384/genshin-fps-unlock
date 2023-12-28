namespace unlockfps_nc
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            OptionsMenuStrip = new MenuStrip();
            optionsToolStripMenuItem = new ToolStripMenuItem();
            SettingsMenuItem = new ToolStripMenuItem();
            SetupMenuItem = new ToolStripMenuItem();
            AboutMenuItem = new ToolStripMenuItem();
            LabelFPS = new Label();
            InputFPS = new NumericUpDown();
            SliderFPS = new TrackBar();
            CBAutoStart = new CheckBox();
            BtnStartGame = new Button();
            ToolTipMain = new ToolTip(components);
            NotifyIconMain = new NotifyIcon(components);
            ContextNotify = new ContextMenuStrip(components);
            ExitMenuItem = new ToolStripMenuItem();
            OptionsMenuStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputFPS).BeginInit();
            ((System.ComponentModel.ISupportInitialize)SliderFPS).BeginInit();
            ContextNotify.SuspendLayout();
            SuspendLayout();
            // 
            // OptionsMenuStrip
            // 
            OptionsMenuStrip.Items.AddRange(new ToolStripItem[] { optionsToolStripMenuItem });
            OptionsMenuStrip.Location = new Point(0, 0);
            OptionsMenuStrip.Name = "OptionsMenuStrip";
            OptionsMenuStrip.Size = new Size(284, 24);
            OptionsMenuStrip.TabIndex = 0;
            OptionsMenuStrip.Text = "menuStrip1";
            // 
            // optionsToolStripMenuItem
            // 
            optionsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { SettingsMenuItem, SetupMenuItem, AboutMenuItem });
            optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            optionsToolStripMenuItem.Size = new Size(61, 20);
            optionsToolStripMenuItem.Text = "Options";
            // 
            // SettingsMenuItem
            // 
            SettingsMenuItem.Name = "SettingsMenuItem";
            SettingsMenuItem.Size = new Size(180, 22);
            SettingsMenuItem.Text = "Settings";
            SettingsMenuItem.Click += SettingsMenuItem_Click;
            // 
            // SetupMenuItem
            // 
            SetupMenuItem.Name = "SetupMenuItem";
            SetupMenuItem.Size = new Size(180, 22);
            SetupMenuItem.Text = "Setup";
            SetupMenuItem.Click += SetupMenuItem_Click;
            // 
            // AboutMenuItem
            // 
            AboutMenuItem.Name = "AboutMenuItem";
            AboutMenuItem.Size = new Size(180, 22);
            AboutMenuItem.Text = "About";
            AboutMenuItem.Click += AboutMenuItem_Click;
            // 
            // LabelFPS
            // 
            LabelFPS.AutoSize = true;
            LabelFPS.Location = new Point(12, 33);
            LabelFPS.Name = "LabelFPS";
            LabelFPS.Size = new Size(29, 15);
            LabelFPS.TabIndex = 1;
            LabelFPS.Text = "FPS:";
            // 
            // InputFPS
            // 
            InputFPS.Location = new Point(47, 31);
            InputFPS.Maximum = new decimal(new int[] { 420, 0, 0, 0 });
            InputFPS.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            InputFPS.Name = "InputFPS";
            InputFPS.Size = new Size(225, 23);
            InputFPS.TabIndex = 2;
            InputFPS.Value = new decimal(new int[] { 120, 0, 0, 0 });
            // 
            // SliderFPS
            // 
            SliderFPS.Location = new Point(12, 60);
            SliderFPS.Maximum = 420;
            SliderFPS.Minimum = 1;
            SliderFPS.Name = "SliderFPS";
            SliderFPS.Size = new Size(260, 45);
            SliderFPS.TabIndex = 3;
            SliderFPS.TickStyle = TickStyle.None;
            SliderFPS.Value = 120;
            // 
            // CBAutoStart
            // 
            CBAutoStart.AutoSize = true;
            CBAutoStart.Location = new Point(12, 90);
            CBAutoStart.Name = "CBAutoStart";
            CBAutoStart.Size = new Size(161, 19);
            CBAutoStart.TabIndex = 4;
            CBAutoStart.Text = "Start Game Automatically";
            ToolTipMain.SetToolTip(CBAutoStart, "This will take effect on subsequent launch");
            CBAutoStart.UseVisualStyleBackColor = true;
            // 
            // BtnStartGame
            // 
            BtnStartGame.Location = new Point(197, 86);
            BtnStartGame.Name = "BtnStartGame";
            BtnStartGame.Size = new Size(75, 23);
            BtnStartGame.TabIndex = 5;
            BtnStartGame.Text = "Start Game";
            BtnStartGame.UseVisualStyleBackColor = true;
            BtnStartGame.Click += BtnStartGame_Click;
            // 
            // NotifyIconMain
            // 
            NotifyIconMain.BalloonTipIcon = ToolTipIcon.Info;
            NotifyIconMain.BalloonTipText = "Minimized to tray";
            NotifyIconMain.BalloonTipTitle = "FPS Unlcoker";
            NotifyIconMain.ContextMenuStrip = ContextNotify;
            NotifyIconMain.Icon = (Icon)resources.GetObject("NotifyIconMain.Icon");
            NotifyIconMain.Text = "FPS Unlcoker";
            NotifyIconMain.Visible = true;
            NotifyIconMain.DoubleClick += NotifyIconMain_DoubleClick;
            // 
            // ContextNotify
            // 
            ContextNotify.Items.AddRange(new ToolStripItem[] { ExitMenuItem });
            ContextNotify.Name = "ContextNotify";
            ContextNotify.Size = new Size(94, 26);
            // 
            // ExitMenuItem
            // 
            ExitMenuItem.Name = "ExitMenuItem";
            ExitMenuItem.Size = new Size(93, 22);
            ExitMenuItem.Text = "Exit";
            ExitMenuItem.Click += ExitMenuItem_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(284, 121);
            Controls.Add(BtnStartGame);
            Controls.Add(CBAutoStart);
            Controls.Add(SliderFPS);
            Controls.Add(InputFPS);
            Controls.Add(LabelFPS);
            Controls.Add(OptionsMenuStrip);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MainMenuStrip = OptionsMenuStrip;
            MaximizeBox = false;
            Name = "MainForm";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Genshin FPS Unlocker";
            FormClosing += MainForm_FormClosing;
            Load += MainForm_Load;
            Resize += MainForm_Resize;
            OptionsMenuStrip.ResumeLayout(false);
            OptionsMenuStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)InputFPS).EndInit();
            ((System.ComponentModel.ISupportInitialize)SliderFPS).EndInit();
            ContextNotify.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip OptionsMenuStrip;
        private ToolStripMenuItem optionsToolStripMenuItem;
        private ToolStripMenuItem SettingsMenuItem;
        private ToolStripMenuItem SetupMenuItem;
        private ToolStripMenuItem AboutMenuItem;
        private Label LabelFPS;
        private NumericUpDown InputFPS;
        private TrackBar SliderFPS;
        private CheckBox CBAutoStart;
        private Button BtnStartGame;
        private ToolTip ToolTipMain;
        private NotifyIcon NotifyIconMain;
        private ContextMenuStrip ContextNotify;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem ExitMenuItem;
    }
}
