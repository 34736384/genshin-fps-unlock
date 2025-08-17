using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace unlockfps_nc.Model
{
    public class VersionInfo
    {
        [JsonPropertyName("Version")]
        public int Version { get; set; }

        [JsonPropertyName("Url")]
        public string Url { get; set; } = string.Empty;
    }
}
