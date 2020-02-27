using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace UARTCOM2
{
    
    public partial class Form1 : Form
    {
        SerialPort ComPort = new SerialPort();
        public Form1()
        {
            InitializeComponent();
            ComPort.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
        }

        private void btnGetSerialPorts_Click(object sender, EventArgs e)
        {
            string[] ArrayComPortsNames = null;
            int index = -1;
            string ComPortName = null;

            ArrayComPortsNames = SerialPort.GetPortNames();
            do
            {
                index += 1;
                comboBox_port.Items.Add(ArrayComPortsNames[index]);
            }

            while (!((ArrayComPortsNames[index] == ComPortName)
                          || (index == ArrayComPortsNames.GetUpperBound(0))));
            Array.Sort(ArrayComPortsNames);

            //want to get first out
            if (index == ArrayComPortsNames.GetUpperBound(0))
            {
                ComPortName = ArrayComPortsNames[0];
            }
            comboBox_port.Text = ArrayComPortsNames[0];
        }

        private void button_open_Click(object sender, EventArgs e)
        {
            if (button_open.Text.Equals("Open"))
            {
                ComPort.BaudRate = Convert.ToInt32(textBox_baudrate.Text);
                ComPort.PortName = comboBox_port.Text;
                ComPort.Open();
                
                button_open.Text = "Close";
            } else
            {
               
                ComPort.Close();
                button_open.Text = "Open";
            }
               
        }
        delegate void SetTextCallback(string text);
        private void setText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.richTextBox_received.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(setText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.richTextBox_received.Text = text;
            }
        }
        delegate string GetTextCallback();
        private string getText()
        {
            string ret = "";
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.richTextBox_received.InvokeRequired)
            {
                GetTextCallback d = new GetTextCallback(getText);
                ret = (string)this.Invoke(d);
            }
            else
            {
                ret = this.richTextBox_received.Text;
            }
            return ret;
        }
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // Show all the incoming data in the port's buffer
            while (ComPort.BytesToRead > 0)
            {
                int x = ComPort.ReadByte();
                Console.WriteLine(x);
               
                setText( getText() +  x.ToString("X2") + " " );
                
            }
                
        }

        private void button_clear_Click(object sender, EventArgs e)
        {
            setText("");
        }

        private void button_send_Click(object sender, EventArgs e)
        {
            if (ComPort.IsOpen)
            {
                byte[] bytes = textBox_send.Text.Split(' ').Select(s => Convert.ToByte(s, 16)).ToArray();
                ComPort.Write(bytes, 0, bytes.Length);
            }
        }
    }
}
