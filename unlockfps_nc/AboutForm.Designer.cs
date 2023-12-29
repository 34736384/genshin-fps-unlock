namespace unlockfps_nc
{
    partial class AboutForm
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
            LabelTitle = new Label();
            LabelDescription = new Label();
            LinkLabelSource = new LinkLabel();
            LinkLabelIssues = new LinkLabel();
            SuspendLayout();
            // 
            // LabelTitle
            // 
            LabelTitle.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            LabelTitle.Location = new Point(12, 9);
            LabelTitle.Name = "LabelTitle";
            LabelTitle.Size = new Size(320, 36);
            LabelTitle.TabIndex = 0;
            LabelTitle.Text = "Genshin FPS Unlocker\r\nv3.0.3";
            LabelTitle.TextAlign = ContentAlignment.TopCenter;
            // 
            // LabelDescription
            // 
            LabelDescription.Location = new Point(12, 45);
            LabelDescription.Name = "LabelDescription";
            LabelDescription.Size = new Size(320, 20);
            LabelDescription.TabIndex = 1;
            LabelDescription.Text = "This program is free and open source";
            LabelDescription.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // LinkLabelSource
            // 
            LinkLabelSource.LinkArea = new LinkArea(8, 46);
            LinkLabelSource.Location = new Point(12, 65);
            LinkLabelSource.Name = "LinkLabelSource";
            LinkLabelSource.Size = new Size(320, 20);
            LinkLabelSource.TabIndex = 2;
            LinkLabelSource.TabStop = true;
            LinkLabelSource.Text = "Source: https://github.com/34736384/genshin-fps-unlock";
            LinkLabelSource.TextAlign = ContentAlignment.MiddleCenter;
            LinkLabelSource.UseCompatibleTextRendering = true;
            LinkLabelSource.LinkClicked += LinkLabelSource_LinkClicked;
            // 
            // LinkLabelIssues
            // 
            LinkLabelIssues.LinkArea = new LinkArea(84, 53);
            LinkLabelIssues.Location = new Point(12, 85);
            LinkLabelIssues.Name = "LinkLabelIssues";
            LinkLabelIssues.Size = new Size(320, 67);
            LinkLabelIssues.TabIndex = 3;
            LinkLabelIssues.TabStop = true;
            LinkLabelIssues.Text = "If you encounter any problems or have a suggestion\r\nGo ahead and submit an issue at\r\n\r\nhttps://github.com/34736384/genshin-fps-unlock/issues\r\n\r\n";
            LinkLabelIssues.TextAlign = ContentAlignment.MiddleCenter;
            LinkLabelIssues.UseCompatibleTextRendering = true;
            LinkLabelIssues.LinkClicked += LinkLabelIssues_LinkClicked;
            // 
            // AboutForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(344, 171);
            Controls.Add(LinkLabelIssues);
            Controls.Add(LinkLabelSource);
            Controls.Add(LabelDescription);
            Controls.Add(LabelTitle);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "AboutForm";
            StartPosition = FormStartPosition.CenterParent;
            Text = "About";
            ResumeLayout(false);
        }

        #endregion

        private Label LabelTitle;
        private Label LabelDescription;
        private LinkLabel LinkLabelSource;
        private LinkLabel LinkLabelIssues;
    }
}