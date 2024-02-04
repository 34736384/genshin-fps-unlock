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

            comboWindowHotKeyP = new ComboBox();
            comboWindowHotKeyPTip = new ToolTip();
            labelPlusP = new Label();
            comboWindowP = new ComboBox();

            comboWindowHotKeyH = new ComboBox();
            comboWindowHotKeyHTip = new ToolTip();
            labelPlusH = new Label();
            comboWindowH = new ComboBox();

            comboWindowHotKeyS = new ComboBox();
            comboWindowHotKeySTip = new ToolTip();
            labelPlusS = new Label();
            comboWindowS = new ComboBox();



            comboWindowHotKeyMTip = new ToolTip();
            labelPlusM = new Label();
            comboWindowM = new ComboBox();

            comboWindowHotKeyNTip = new ToolTip();
            labelPlusN = new Label();
            comboWindowN = new ComboBox();


            neuvilletteSpinPixelsTip = new Label();
            inputNeuvilletteSpinPixels = new NumericUpDown();
             

        OptionsMenuStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputFPS).BeginInit();
            ((System.ComponentModel.ISupportInitialize)SliderFPS).BeginInit();
            ((System.ComponentModel.ISupportInitialize)inputNeuvilletteSpinPixels).BeginInit();
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
            SettingsMenuItem.Size = new Size(116, 22);
            SettingsMenuItem.Text = "Settings";
            SettingsMenuItem.Click += SettingsMenuItem_Click;
            // 
            // SetupMenuItem
            // 
            SetupMenuItem.Name = "SetupMenuItem";
            SetupMenuItem.Size = new Size(116, 22);
            SetupMenuItem.Text = "Setup";
            SetupMenuItem.Click += SetupMenuItem_Click;
            // 
            // AboutMenuItem
            // 
            AboutMenuItem.Name = "AboutMenuItem";
            AboutMenuItem.Size = new Size(116, 22);
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
            // comboWindowHotKeyP
            // 
            comboWindowHotKeyP.DropDownStyle =ComboBoxStyle.DropDownList;
            comboWindowHotKeyP.FormattingEnabled = true;
            comboWindowHotKeyP.Items.AddRange(new object[]{ "ALT","CTRL" });
            comboWindowHotKeyP.Location = new Point(15, 120);
            comboWindowHotKeyP.Name = "comboWindowHotKey";
            comboWindowHotKeyP.Size = new Size(50, 21);
            comboWindowHotKeyP.TabStop = false;
            comboWindowHotKeyPTip.SetToolTip(comboWindowHotKeyP, "ALT\r\nCTRL");
         
            // comboWindowHotKeyPTip
            // 
            comboWindowHotKeyPTip.AutoPopDelay = 5000;
            comboWindowHotKeyPTip.InitialDelay = 1;
            comboWindowHotKeyPTip.ReshowDelay = 100;
            // 
            // labelPlusP
            // 
            labelPlusP.AutoSize = true;
            labelPlusP.Location = new Point(70, 125);
            labelPlusP.Name =  "labelPlusP";
            labelPlusP.Size = new Size(33, 13);
            labelPlusP.Text =  "+ P    => ";
            // 
            // comboWindowP
            // 
            comboWindowP.DropDownStyle =ComboBoxStyle.DropDownList;
            comboWindowP.FormattingEnabled = true;
            comboWindowP.Items.AddRange(items);
            comboWindowP.Location = new Point(135, 120);
            comboWindowP.Name = "comboWindowP";
            comboWindowP.Size = new Size(140, 21);
            comboWindowP.TabStop = false;

            
            // 
            // comboWindowHotKeyH
            // 
            comboWindowHotKeyH.DropDownStyle =  ComboBoxStyle.DropDownList;
            comboWindowHotKeyH.FormattingEnabled = true;
            comboWindowHotKeyH.Items.AddRange(new object[]{ "ALT", "CTRL" });
            comboWindowHotKeyH.Location = new Point(15, 155);
            comboWindowHotKeyH.Name = "comboWindowHotKeyH";
            comboWindowHotKeyH.Size = new Size(50, 21);
            comboWindowHotKeyH.TabStop = false;
            comboWindowHotKeyHTip.SetToolTip(comboWindowHotKeyH, "ALT\r\nCTRL");
            // comboWindowHotKeyHTip
            // 
            comboWindowHotKeyHTip.AutoPopDelay = 5000;
            comboWindowHotKeyHTip.InitialDelay = 1;
            comboWindowHotKeyHTip.ReshowDelay = 100;
            // 
            // labelPlusH
            // 
            labelPlusH.AutoSize = true;
            labelPlusH.Location = new Point(70, 160);
            labelPlusH.Name = "labelPlusH";
            labelPlusH.Size = new Size(33, 13);
            labelPlusH.Text = "+ H    => ";
            // 
            // comboWindowH
            // 
            comboWindowH.DropDownStyle =  ComboBoxStyle.DropDownList;
            comboWindowH.FormattingEnabled = true;
            comboWindowH.Items.AddRange(items);
            comboWindowH.Location = new Point(135, 155);
            comboWindowH.Name = "comboWindowH";
            comboWindowH.Size = new Size(140, 21);
            comboWindowH.TabStop = false;


            // 
            // comboWindowHotKeyS
            // 
            comboWindowHotKeyS.DropDownStyle =  ComboBoxStyle.DropDownList;
            comboWindowHotKeyS.FormattingEnabled = true;
            comboWindowHotKeyS.Items.AddRange(new object[] { "ALT", "CTRL" });
            comboWindowHotKeyS.Location = new Point(15, 190);
            comboWindowHotKeyS.Name = "comboWindowHotKeyS";
            comboWindowHotKeyS.Size = new Size(50, 21);
            comboWindowHotKeyS.TabStop = false;
            comboWindowHotKeySTip.SetToolTip(comboWindowHotKeyS, "ALT\r\nCTRL");
            // comboWindowHotKeySTip
            // 
            comboWindowHotKeySTip.AutoPopDelay = 5000;
            comboWindowHotKeySTip.InitialDelay = 1;
            comboWindowHotKeySTip.ReshowDelay = 100;
            // 
            // labelPlusS
            // 
            labelPlusS.AutoSize = true;
            labelPlusS.Location = new Point(70, 195);
            labelPlusS.Name = "labelPlusS";
            labelPlusS.Size = new Size(33, 13);
            labelPlusS.Text = "+ 空格 => ";
            // 
            // comboWindowS
            // 
            comboWindowS.DropDownStyle = ComboBoxStyle.DropDownList;
            comboWindowS.FormattingEnabled = true;
            comboWindowS.Items.AddRange(items);
            comboWindowS.Location = new Point(135, 190);
            comboWindowS.Name = "comboWindowS";
            comboWindowS.Size = new Size(140, 21);
            comboWindowS.TabStop = false;

            
            // comboWindowHotKeyMTip
            // 
            comboWindowHotKeyMTip.AutoPopDelay = 5000;
            comboWindowHotKeyMTip.InitialDelay = 1;
            comboWindowHotKeyMTip.ReshowDelay = 100;
            // 
            // labelPlusM
            // 
            labelPlusM.AutoSize = true;
            labelPlusM.Location = new Point(15, 230);
            labelPlusM.Name = "labelPlusM";
            labelPlusM.Size = new Size(33, 13);
            labelPlusM.Text = "侧键前进=>";
            // 
            // comboWindowM
            // 
            comboWindowM.DropDownStyle = ComboBoxStyle.DropDownList;
            comboWindowM.FormattingEnabled = true;
            comboWindowM.Items.AddRange(items);
            comboWindowM.Location = new Point(90, 228);
            comboWindowM.Name = "comboWindowM";
            comboWindowM.Size = new Size(180, 21);
            comboWindowM.TabStop = false;

            // comboWindowHotKeyNTip
            // 
            comboWindowHotKeyNTip.AutoPopDelay = 5000;
            comboWindowHotKeyNTip.InitialDelay = 1;
            comboWindowHotKeyNTip.ReshowDelay = 100;
            // 
            // labelPlusN
            // 
            labelPlusN.AutoSize = true;
            labelPlusN.Location = new Point(15, 265);
            labelPlusN.Name = "labelPlusM";
            labelPlusN.Size = new Size(33, 13);
            labelPlusN.Text = "侧键后退=>";
            // 
            // comboWindowN
            // 
            comboWindowN.DropDownStyle = ComboBoxStyle.DropDownList;
            comboWindowN.FormattingEnabled = true;
            comboWindowN.Items.AddRange(items);
            comboWindowN.Location = new Point(90, 263);
            comboWindowN.Name = "comboWindowM";
            comboWindowN.Size = new Size(180, 21);
            comboWindowN.TabStop = false;

            
            // 
            // neuvilletteSpinPixelsTip
            // 
            neuvilletteSpinPixelsTip.AutoSize = true;
            neuvilletteSpinPixelsTip.Location = new Point(15, 300);
            neuvilletteSpinPixelsTip.Name = "neuvilletteSpinPixelsTip";
            neuvilletteSpinPixelsTip.Size = new Size(33, 13);
            neuvilletteSpinPixelsTip.Text = "那维莱特旋转摆幅";
            // 
            // inputNeuvilletteSpinPixels
            // 
            inputNeuvilletteSpinPixels.Location = new Point(125, 295);
            inputNeuvilletteSpinPixels.Maximum = new decimal(new int[] { 30000, 0, 0, 0 });
            inputNeuvilletteSpinPixels.Minimum = new decimal(new int[] { 300, 0, 0, 0 });
            inputNeuvilletteSpinPixels.Name = "inputNeuvilletteSpinPixels";
            inputNeuvilletteSpinPixels.Size = new Size(60, 20);
            inputNeuvilletteSpinPixels.TabIndex = 4;
            inputNeuvilletteSpinPixels.TabStop = false;
            inputNeuvilletteSpinPixels.Value = new decimal(new int[] { 15000, 0, 0, 0 });

             



            // 
            // BtnStartGame
            // 
            BtnStartGame.Location = new Point(197, 295);
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
            NotifyIconMain.Text = "FPS Unlocker";
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
            ClientSize = new Size(284, 341);

            Controls.Add(comboWindowHotKeyP);
            //Controls.Add(comboWindowHotKeyPTip);
            Controls.Add(labelPlusP);
            Controls.Add(comboWindowP);


            Controls.Add(comboWindowHotKeyH);
            //Controls.Add(comboWindowHotKeyHTip);
            Controls.Add(labelPlusH);
            Controls.Add(comboWindowH);


            Controls.Add(comboWindowHotKeyS);
            //Controls.Add(comboWindowHotKeySTip);
            Controls.Add(labelPlusS);
            Controls.Add(comboWindowS);


            //Controls.Add(comboWindowHotKeyMTip);
            Controls.Add(labelPlusM);
            Controls.Add(comboWindowM);
            //Controls.Add(comboWindowHotKeyNTip);
            Controls.Add(labelPlusN);
            Controls.Add(comboWindowN);
            Controls.Add(neuvilletteSpinPixelsTip);
            Controls.Add(inputNeuvilletteSpinPixels);

              


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
            ((System.ComponentModel.ISupportInitialize)inputNeuvilletteSpinPixels).EndInit();
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

        private ComboBox comboWindowHotKeyP;
        private ToolTip comboWindowHotKeyPTip;
        private Label labelPlusP;
        private ComboBox comboWindowP;

        private ComboBox comboWindowHotKeyH;
        private ToolTip comboWindowHotKeyHTip;
        private Label labelPlusH;
        private ComboBox comboWindowH;

        private ComboBox comboWindowHotKeyS;
        private ToolTip comboWindowHotKeySTip;
        private Label labelPlusS;
        private ComboBox comboWindowS;

        private ToolTip comboWindowHotKeyMTip;
        private Label labelPlusM;
        private ComboBox comboWindowM;

        private ToolTip comboWindowHotKeyNTip;
        private Label labelPlusN;
        private ComboBox comboWindowN;

        private Label neuvilletteSpinPixelsTip;
        private NumericUpDown inputNeuvilletteSpinPixels;


        private object[] items = {
            "无",
            "快速强化圣遗物/武器",
            "胡桃10AAZ【推荐1命】",
            "快速点剧情",
            "那维莱特无前摇重击",
            "那维莱特一键重击转圈", 
            "胡桃10AZ跳【推荐0命】", 
            "胡桃8AAZ跳【推荐0命】", 
            "胡桃11AAZ【1命120帧】"
            }; 
    }
}
