using System;
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
    }
}