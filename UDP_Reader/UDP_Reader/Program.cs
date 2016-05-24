using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace UDP_Reader
{
    class Program
    {
        public class UDPListener
        {
            private const int listenPort = 6000;

            private static void StartListener()
            {
                bool done = false;

                UdpClient listener = new UdpClient(listenPort);
                IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, listenPort);

                try
                {
                    while (!done)
                    {
                        Console.WriteLine("Waiting for broadcast");
                        byte[] bytes = listener.Receive(ref groupEP);

                        Console.WriteLine("Received broadcast from {0} :\n {1}\n",
                            groupEP.ToString(),
                            Encoding.ASCII.GetString(bytes, 0, bytes.Length));
                    }

                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
                finally
                {
                    listener.Close();
                }
            }
            static void Main(string[] args)
            {
                StartListener();


            }
        }
    }
}
