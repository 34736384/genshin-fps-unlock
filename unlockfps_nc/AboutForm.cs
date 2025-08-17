using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace unlockfps_nc
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void LinkLabelSource_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/34736384/genshin-fps-unlock");
        }

        private void LinkLabelIssues_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/34736384/genshin-fps-unlock/issues");
        }

        private void OpenLink(string url)
        {
            var psi = new ProcessStartInfo
            {
                FileName = url,
                UseShellExecute = true
            };

            Process.Start(psi);
        }

        private string GetVersionText(int versionNumber)
        {
            string version = versionNumber.ToString();
            string major = version[0].ToString();
            string minor = version[1].ToString();
            string build = int.Parse(version.Substring(2)).ToString();
            string originalBuild = version.Substring(2);
            if (originalBuild.Length > 1 && !originalBuild.EndsWith("0"))
                build = originalBuild;

            return $"{major}.{minor}.{build}";
        }

        private void AboutForm_Load(object sender, EventArgs e)
        {
            LabelTitle.Text += GetVersionText(Program.Version);
        }
    }
}
