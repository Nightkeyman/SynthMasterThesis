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
        byte buffer_iterator = 0;
        byte buffer_length = 9;
        byte[] buffer;
        void Buffer_push(byte data)
        {
            buffer_iterator++;
            if (buffer_iterator >= buffer_length)
                buffer_iterator = 0;
            buffer[buffer_iterator] = data;
        }

        byte Buffer_pull(sbyte offset)
        {
            offset = (sbyte)(offset - buffer_length + 1);
            int index = 0;
            if (buffer_iterator + offset >= 0)
                index = buffer_iterator + offset;
            else
                index = buffer_length + buffer_iterator + offset;
            return buffer[index];

        }
        void Buffer_clear()
        {
            byte i = 0;
            for (i = 0; i < buffer_length; i++)
                buffer[i] = 0;
        }
        public Form1()
        {
            InitializeComponent();
            buffer = new byte[buffer_length];
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
                byte x = (byte)ComPort.ReadByte();
                Console.WriteLine(x);
               
                setText( getText() +  x.ToString("X2") + " " );
                Buffer_push(x);
                switch (Buffer_pull(0))
                {
                    case 100:
                        if (Buffer_pull(7) == 101)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_subtractive_en.Text = "Enabled";
                                    button_subtractive_en.ForeColor = Color.Green;
                                } else if (Buffer_pull(1) == 2)
                                {
                                    button_subtractive_en.Text = "Disabled";
                                    button_subtractive_en.ForeColor = Color.Red;
                                }
                            }
                        }
                        break;
                }
            }
                
        }
        byte Checksum()
        {
            return (byte)(Buffer_pull(1) + Buffer_pull(2) + Buffer_pull(3) + Buffer_pull(4) + Buffer_pull(5) + Buffer_pull(6));
        }
        void send(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6)
        {
            byte suma = (byte)(b1 + b2 + b3 + b4 + b5 + b6);
            byte[] bytes = { b0, b1, b2, b3, b4, b5, b6, (byte)(b0 + 1), suma };
            if (ComPort.IsOpen)
            {
                ComPort.Write(bytes, 0, bytes.Length);
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

        private void button_subtractive_en_Click(object sender, EventArgs e)
        {
            if (button_subtractive_en.Text.Equals("Disabled"))
            {
                send(100, 1, 0, 0, 0, 0, 0);
                
            }
            else
            {
                send(100, 2, 0, 0, 0, 0, 0);
               
            }
        }
    }
}
