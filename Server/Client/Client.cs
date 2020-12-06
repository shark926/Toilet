using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Server
{
    internal class Program
    {
        private static void Main(string[] args)
        {

            IPEndPoint remoteIpEndPoint = new IPEndPoint(IPAddress.Parse("192.168.0.115"), 8266);
            UdpClient udp = new UdpClient(8265);

            IPEndPoint receivePE = new IPEndPoint(IPAddress.Any, 0);

            while (true)
            {
                try
                {

                    string sendString = Console.ReadLine();

                    Console.Out.WriteLine($"send:{sendString}");

                    byte[] sendData = Encoding.Default.GetBytes(sendString);

                    udp.Send(sendData, sendData.Length, remoteIpEndPoint);//将数据发送到远程端点
                                                                          //remoteClient.Close();//关闭连接

                    byte[] receiveData = udp.Receive(ref receivePE);

                    string receiveText = Encoding.Default.GetString(receiveData);

                    Console.Out.WriteLine($"receive:{receiveText}");
                }
                catch (Exception e)
                {
                    Console.Out.WriteLine(e);
                }
            }
        }

        //private static void Test()
        //{
        //    IPEndPoint remoteIpEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8266);
        //    // This constructor arbitrarily assigns the local port number.
        //    UdpClient udpClient = new UdpClient(8265);

        //    //IPEndPoint object will allow us to read datagrams sent from any source.
        //    IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
        //    try
        //    {
        //        //udpClient.Connect("www.contoso.com", 11000);

        //        // Sends a message to the host to which you have connected.
        //        Byte[] sendBytes = Encoding.ASCII.GetBytes("Is anybody there?");

        //        udpClient.Send(sendBytes, sendBytes.Length, remoteIpEndPoint);



        //        // Blocks until a message returns on this socket from a remote host.
        //        Byte[] receiveBytes = udpClient.Receive(ref RemoteIpEndPoint);
        //        string returnData = Encoding.ASCII.GetString(receiveBytes);

        //        // Uses the IPEndPoint object to determine which of these two hosts responded.
        //        Console.WriteLine("This is the message you received " +
        //                                     returnData.ToString());
        //        Console.WriteLine("This message was sent from " +
        //                                    RemoteIpEndPoint.Address.ToString() +
        //                                    " on their port number " +
        //                                    RemoteIpEndPoint.Port.ToString());

        //        udpClient.Close();
        //    }
        //    catch (Exception e)
        //    {
        //        Console.WriteLine(e.ToString());
        //    }
        //}
    }
}