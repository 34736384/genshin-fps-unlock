namespace unlockfps_nc
{
    partial class SetupForm
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
            LabelResult = new Label();
            LabelSelect = new Label();
            ComboResult = new ComboBox();
            LabelHint = new Label();
            BtnBrowse = new Button();
            BtnConfirm = new Button();
            LabelCurrentPath = new Label();
            BrowseDialog = new OpenFileDialog();
            SuspendLayout();
            // 
            // LabelResult
            // 
            LabelResult.AutoSize = true;
            LabelResult.Location = new Point(12, 48);
            LabelResult.Name = "LabelResult";
            LabelResult.Size = new Size(67, 15);
            LabelResult.TabIndex = 0;
            LabelResult.Text = "LabelResult";
            // 
            // LabelSelect
            // 
            LabelSelect.AutoSize = true;
            LabelSelect.Location = new Point(12, 63);
            LabelSelect.Name = "LabelSelect";
            LabelSelect.Size = new Size(38, 15);
            LabelSelect.TabIndex = 1;
            LabelSelect.Text = "Select";
            // 
            // ComboResult
            // 
            ComboResult.FormattingEnabled = true;
            ComboResult.Location = new Point(12, 81);
            ComboResult.Name = "ComboResult";
            ComboResult.Size = new Size(435, 23);
            ComboResult.TabIndex = 2;
            // 
            // LabelHint
            // 
            LabelHint.AutoSize = true;
            LabelHint.Location = new Point(12, 117);
            LabelHint.Name = "LabelHint";
            LabelHint.Size = new Size(359, 45);
            LabelHint.TabIndex = 3;
            LabelHint.Text = "If your game is not listed above, you can either:\r\n1. Open the game now and the unlocker will try to find it's location\r\n2. Use the browse button below";
            // 
            // BtnBrowse
            // 
            BtnBrowse.Location = new Point(12, 176);
            BtnBrowse.Name = "BtnBrowse";
            BtnBrowse.Size = new Size(75, 23);
            BtnBrowse.TabIndex = 4;
            BtnBrowse.Text = "Browse";
            BtnBrowse.UseVisualStyleBackColor = true;
            BtnBrowse.Click += BtnBrowse_Click;
            // 
            // BtnConfirm
            // 
            BtnConfirm.Location = new Point(372, 176);
            BtnConfirm.Name = "BtnConfirm";
            BtnConfirm.Size = new Size(75, 23);
            BtnConfirm.TabIndex = 5;
            BtnConfirm.Text = "Confirm";
            BtnConfirm.UseVisualStyleBackColor = true;
            BtnConfirm.Click += BtnConfirm_Click;
            // 
            // LabelCurrentPath
            // 
            LabelCurrentPath.Location = new Point(12, 9);
            LabelCurrentPath.Name = "LabelCurrentPath";
            LabelCurrentPath.Size = new Size(435, 39);
            LabelCurrentPath.TabIndex = 6;
            LabelCurrentPath.Text = "LabelCurrentPath";
            // 
            // BrowseDialog
            // 
            BrowseDialog.Filter = "Executable Files (*.exe)|GenshinImpact.exe;YuanShen.exe";
            BrowseDialog.RestoreDirectory = true;
            BrowseDialog.Title = "Select GenshinImpact.exe or YuanShen.exe";
            // 
            // SetupForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(459, 211);
            Controls.Add(LabelCurrentPath);
            Controls.Add(BtnConfirm);
            Controls.Add(BtnBrowse);
            Controls.Add(LabelHint);
            Controls.Add(ComboResult);
            Controls.Add(LabelSelect);
            Controls.Add(LabelResult);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "SetupForm";
            StartPosition = FormStartPosition.CenterParent;
            Text = "Setup";
            FormClosing += SetupForm_FormClosing;
            Load += SetupForm_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label LabelResult;
        private Label LabelSelect;
        private ComboBox ComboResult;
        private Label LabelHint;
        private Button BtnBrowse;
        private Button BtnConfirm;
        private Label LabelCurrentPath;
        private OpenFileDialog BrowseDialog;
    }
}