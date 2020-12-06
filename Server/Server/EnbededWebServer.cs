using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

//https://www.c-sharpcorner.com/article/creating-your-own-web-server-using-C-Sharp/
internal class EnbededWebServer
{
    private TcpListener tcpListener;
    private System.Func<string> requestPage;

    //The constructor which make the TcpListener start listening on th
    //given port. It also calls a Thread on the method StartListen().
    public EnbededWebServer(int port, System.Func<string> requestPage)
    {
        this.requestPage = requestPage;

        try
        {
            //start listing on the given port
            tcpListener = new TcpListener(IPAddress.Any, port);
            tcpListener.Start();
            Console.WriteLine("Web Server Running... Press ^C to Stop...");
            //start the thread which calls the method 'StartListen'
            Thread th = new Thread(new ThreadStart(StartListen));
            th.Start();
        }
        catch (Exception e)
        {
            Console.WriteLine("An Exception Occurred while Listening :" + e.ToString());
        }
    }

    private void StartListen()
    {
        while (true)
        {
            using (Socket socket = tcpListener.AcceptSocket())
            {
                //Console.WriteLine("Socket Type " + mySocket.SocketType);
                if (socket.Connected)
                {
                    //ProcessRequest(socket);

                    string pageText = requestPage != null ? requestPage.Invoke() : "<H2>error</H2>";

                    string respond = Respond(pageText);

                    //Console.WriteLine(respond);
                    //Console.WriteLine("fs");
                    SendToBrowser(respond, socket);

                    //延迟关闭socket是为了chrome浏览器能正确接收
                    Thread.Sleep(10);
                    
                    socket.Close();
                }
            }
        }
    }

    private void ProcessRequest(Socket socket)
    {
        Byte[] data = new Byte[1024];
        int i = socket.Receive(data, data.Length, 0);

        Console.WriteLine("******************************************");
        Console.WriteLine(Encoding.ASCII.GetString(data));
        Console.WriteLine("------------------------------------------");
    }

    private string Respond(string text)
    {
        StringBuilder builder = new StringBuilder(1024);

        builder.Append("HTTP/1.1 200 OK\r\n");
        builder.Append("Server: cx1193719-b\r\n");
        builder.Append("Content-Type: text/html; charset=utf-8\r\n");// Default Mime Type is text/html,Content-Type: text/html; charset=utf-8
        builder.Append("Accept-Ranges: bytes\r\n");
        builder.Append($"Content-Length: {text.Length}\r\n");
        builder.Append("\r\n");

        builder.Append(text);

        return builder.ToString();
    }

    private void SendToBrowser(String text, Socket socket)
    {
        SendToBrowser(Encoding.UTF8.GetBytes(text), socket);
    }

    private void SendToBrowser(Byte[] data, Socket socket)
    {
        try
        {
            if (socket.Connected)
            {
                int numBytes = 0;
                if ((numBytes = socket.Send(data)) == -1)
                {
                    Console.WriteLine("Socket Error cannot Send Packet");
                }
                else
                {
                    //Console.WriteLine("No. of bytes send {0}", numBytes);
                }
            }
            else
            {
                Console.WriteLine("Connection Dropped....");
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Error Occurred : {0} ", e);
        }
    }
}