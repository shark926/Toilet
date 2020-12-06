using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Client
{
    internal struct SeatState
    {
        private const float Throttle = 2f;

        private System.DateTime lastSetTime;

        public void SetOccupy()
        {
            lastSetTime = DateTime.Now;
        }

        public bool IsOccupied()
        {
            return (DateTime.Now - lastSetTime).Seconds < Throttle;
        }
    }

    internal class Program
    {
        private const int WebListenPort = 8080;
        private const int ReportUdpPort = 8266;

        private static string GetLocalIp()
        {
            ///获取本地的IP地址
            string addressIP = string.Empty;
            foreach (IPAddress _IPAddress in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
            {
                if (_IPAddress.AddressFamily.ToString() == "InterNetwork")
                {
                    addressIP = _IPAddress.ToString();
                }
            }
            return addressIP;
        }

        private static void Main(string[] args)
        {
            SeatState[] seatState = new SeatState[] { new SeatState() };

            StringBuilder pageText = new StringBuilder(128);

            string pageTemple = "<html><body>{0}</body></html>";

            EnbededWebServer enbededWebServer = new EnbededWebServer(WebListenPort, () =>
            {
                pageText.Clear();

                for (int i = 0; i < seatState.Length; i++)
                {
                    string itemText = null;
                    if (seatState[i].IsOccupied())
                    {
                        itemText = $"<p><font color = \"red\">坑位[{i}]->占用</font></p>";
                    }
                    else
                    {
                        itemText = $"<p><font color = \"green\">坑位[{i}]->空闲</font></p>";
                    }

                    pageText.AppendLine(itemText);
                }

                return string.Format(pageTemple, pageText.ToString());
            });

            string localIp = GetLocalIp();

            Console.WriteLine($"Web access address:http://{localIp}:{WebListenPort}");

            UdpClient udp = new UdpClient(ReportUdpPort);

            Console.WriteLine($"Receive Report on {localIp}:{ReportUdpPort}");

            //实例化一个远程端点，IP和端口可以随意指定，等调用client.Receive(ref remotePoint)时会将该端点改成真正发送端端点
            IPEndPoint remotePoint = new IPEndPoint(IPAddress.Any, 0);

            //string echo = "klklgh";
            //byte[] sendData = Encoding.ASCII.GetBytes(echo);
            while (true)
            {
                try
                {
                    byte[] recivceData = udp.Receive(ref remotePoint);
                    if (recivceData != null && recivceData.Length > 0)
                    {
                        Console.Out.WriteLine($"{System.DateTime.Now}:receive Report");

                        if (recivceData.Length != seatState.Length)
                        {
                            seatState = new SeatState[recivceData.Length];
                        }

                        for (int i = 0; i < recivceData.Length; i++)
                        {
                            if (recivceData[i] != 0)
                            {
                                seatState[i].SetOccupy();
                                Console.Out.WriteLine($"{System.DateTime.Now}:receive occupy {i}");
                            }
                        }
                    }
                    //string strMsg = Encoding.ASCII.GetString(recivceData, 0, recivceData.Length);

                    //Console.Out.WriteLine($"{remotePoint}：{strMsg}");

                    //udp.Send(sendData, sendData.Length, remotePoint);
                    //Console.Out.WriteLine($"send:{echo}");
                }
                catch (System.Exception e)
                {
                    Console.Out.WriteLine(e);
                }
            }
        }
    }
}