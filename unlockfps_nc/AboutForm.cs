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
        private void linkLabelgitee_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://gitee.com/zhouchengang/genshin-fps-unlock/releases");
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

    }
}
