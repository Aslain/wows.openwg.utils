using System;
using System.IO;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;

using Newtonsoft.Json.Linq;

namespace XVM.Extensions
{
    public class XVM
    {
        private static HttpClient client { get; } = new HttpClient();

        private string Token { get; set; } = "-";

        public string ServerUrl { get; } = "https://stat.modxvm.com";

        public string ApiVersion { get; } = "4.0";

        public XVM()
        {
            Token = "-";
        }

        public XVM(string token)
        {
            Token = token;
        }

        private string getRequestUri(string requestType, string requestData)
        {
            return $"{ServerUrl}/{ApiVersion}/{requestType}/{Token}/{requestData}";
        }

        public async Task<Version> GetLatestVersion(string region)
        {
            return await GetLatestVersion(Wot.GetRegionFromString(region));
        }

        public async Task<Version> GetLatestVersion(WotClientRegion region)
        {
            System.Net.ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12 | SecurityProtocolType.Tls11 | SecurityProtocolType.Tls;

            var requestUrl = getRequestUri("getVersionWithLimit", $"{Wot.GetIdsRangeForRegion(region).Min}/0/0");

            var responseMessage = await client.GetAsync(requestUrl);
            var responseContent = await responseMessage.Content.ReadAsStringAsync();
            var responseJson = JObject.Parse(responseContent);

            var versionString = responseJson.SelectToken("info.ver").Value<string>();
            return new Version(versionString);
        }

        /// <summary>
        /// Returns version of installed XVM
        /// </summary>
        /// <param name="clientPath">full path to World of Tanks client</param>
        /// <returns>XVM version or null if XVM is not installed</returns>
        public static Version GetVersion(string clientPath)
        {
            if(string.IsNullOrEmpty(clientPath))
            {
                return null;
            }

            var clientResmods = Path.Combine(clientPath, "res_mods");
            if(!Directory.Exists(clientResmods))
            {
                return null;
            }

            var xvmManifest = Path.Combine(clientResmods, "mods\\xfw_packages\\xvm_main\\xfw_package.json");
            if (!File.Exists(xvmManifest))
            {
                return null;
            }

            try
            {
                var v = JObject.Parse(File.ReadAllText(xvmManifest)).SelectToken("version").Value<string>();
                return new Version(v.Substring(0, v.LastIndexOf('.')));
            }
            catch (Exception)
            {
                return null;
            }
        }
    }
}