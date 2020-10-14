using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;
using System.Linq.Expressions;
using System.Reflection;
using System.Threading;

namespace UARTCOM2
{
    
    public partial class Form1 : Form
    {
        
        SerialPort ComPort = new SerialPort();
        byte buffer_iterator = 0;
        byte buffer_length = 9;
        byte[] buffer;
        uint currFilter = 0;

        //SUBTRACTIVE GLOBALS
        int filtertype = 1;
        int waveformtype = 1;
        int highfreq = 1;
        int lowfreq = 1;

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
            refreshPorts();
            ComPort.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
        }

        private void btnGetSerialPorts_Click(object sender, EventArgs e)
        {
            refreshPorts();
        }

        private void refreshPorts()
        {
            string[] ArrayComPortsNames = null;
            int index = -1;
            string ComPortName = null;

            ArrayComPortsNames = SerialPort.GetPortNames();
            comboBox_port.Items.Clear();
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
                    case 100:   // SUBTRACTIVE
                        if (Buffer_pull(7) == 101)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_subtractive_en.Invoke((MethodInvoker)delegate {
                                        button_subtractive_en.Text = "Enabled";
                                    });
                                    button_subtractive_en.Invoke((MethodInvoker)delegate {
                                        button_subtractive_en.ForeColor = Color.Green;
                                    });
                                } else if (Buffer_pull(1) == 2)
                                {
                                    button_subtractive_en.Invoke((MethodInvoker)delegate {
                                        button_subtractive_en.Text = "Disabled";
                                    });
                                    button_subtractive_en.Invoke((MethodInvoker)delegate {
                                        button_subtractive_en.ForeColor = Color.Red;
                                    });
                                }
                            }
                        }
                        break;
                    case 101:   // ADDITIVE
                        if (Buffer_pull(7) == 102)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_additive_hammond_en.Invoke((MethodInvoker)delegate {
                                        button_additive_hammond_en.Text = "Enabled";
                                    });
                                    button_additive_hammond_en.Invoke((MethodInvoker)delegate {
                                        button_additive_hammond_en.ForeColor = Color.Green;
                                    });
                                }
                                else if (Buffer_pull(1) == 2)
                                {
                                    button_additive_hammond_en.Invoke((MethodInvoker)delegate {
                                        button_additive_hammond_en.Text = "Disabled";
                                    });
                                    button_additive_hammond_en.Invoke((MethodInvoker)delegate {
                                        button_additive_hammond_en.ForeColor = Color.Red;
                                    });
                                }
                            }
                        }
                        break;

                    case 102:   // FM
                        if (Buffer_pull(7) == 103)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_fm_en.Invoke((MethodInvoker)delegate {
                                        button_fm_en.Text = "Enabled";
                                    });
                                    button_fm_en.Invoke((MethodInvoker)delegate {
                                        button_fm_en.ForeColor = Color.Green;
                                    });
                                }
                                else if (Buffer_pull(1) == 2)
                                {
                                    button_fm_en.Invoke((MethodInvoker)delegate {
                                        button_fm_en.Text = "Disabled";
                                    });
                                    button_fm_en.Invoke((MethodInvoker)delegate {
                                        button_fm_en.ForeColor = Color.Red;
                                    });
                                }

                                if (Buffer_pull(1) == 5)
                                {
                                    button_fm_bell_en.Invoke((MethodInvoker)delegate {
                                        button_fm_bell_en.Text = "Enabled";
                                    });
                                    button_fm_bell_en.Invoke((MethodInvoker)delegate {
                                        button_fm_bell_en.ForeColor = Color.Green;
                                    });
                                }
                                else if (Buffer_pull(1) == 6)
                                {
                                    button_fm_bell_en.Invoke((MethodInvoker)delegate {
                                        button_fm_bell_en.Text = "Disabled";
                                    });
                                    button_fm_bell_en.Invoke((MethodInvoker)delegate {
                                        button_fm_bell_en.ForeColor = Color.Red;
                                    });
                                }
                            }
                        }
                        break;
                    case 109:   // flute
                        if (Buffer_pull(7) == 110)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_flute_en.Invoke((MethodInvoker)delegate {
                                        button_flute_en.Text = "Enabled";
                                    });
                                    button_flute_en.Invoke((MethodInvoker)delegate {
                                        button_flute_en.ForeColor = Color.Green;
                                    });
                                }
                                else if (Buffer_pull(1) == 2)
                                {
                                    button_flute_en.Invoke((MethodInvoker)delegate {
                                        button_flute_en.Text = "Disabled";
                                    });
                                    button_flute_en.Invoke((MethodInvoker)delegate {
                                        button_flute_en.ForeColor = Color.Red;
                                    });
                                }
                            }
                        }
                        break;
                    case 170:
                        if (Buffer_pull(7) == 171)
                        {
                            if (Checksum() == Buffer_pull(8))
                            {
                                if (Buffer_pull(1) == 1)
                                {
                                    button_fm_en.Invoke((MethodInvoker)delegate {
                                        //disableAllMethods();
                                    });
                                }
                                else if (Buffer_pull(1) == 2)
                                {

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
        void sendInt(byte id, byte subid, UInt32 data)
        {
            byte[] intbytes = BitConverter.GetBytes(data);

            send(id, subid, intbytes[0], intbytes[1], intbytes[2], intbytes[3], 0);

        }
        void send(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6)
        {
            byte suma = (byte)(b1 + b2 + b3 + b4 + b5 + b6);
            byte[] bytes = { b0, b1, b2, b3, b4, b5, b6, (byte)(b0 + 1), suma };
            if (ComPort.IsOpen)
            {
                ComPort.Write(bytes, 0, bytes.Length);
            }
            Thread.Sleep(10);
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
        private void disableAllMethods()
        {
            button_subtractive_en.Text = "Disabled";
            button_subtractive_en.ForeColor = Color.Red;

            button_additive_hammond_en.Text = "Disabled";
            button_additive_hammond_en.ForeColor = Color.Red;

            button_fm_en.Text = "Disabled";
            button_fm_en.ForeColor = Color.Red;
        }
        private void button_subtractive_en_Click(object sender, EventArgs e)
        {
            Console.WriteLine("siemsa");
            if (button_subtractive_en.Text.Equals("Disabled"))
            {
                send(100, 1, 0, 0, 0, 0, 0);
            }
            else
            {
                send(100, 2, 0, 0, 0, 0, 0);
            }
        }

        private void richTextBox_received_MouseUp(object sender, MouseEventArgs e)
        {
            Console.WriteLine("siema");
        }


        private void trackBar_subtractive_freq1_Scroll(object sender, EventArgs e)
        {
            textBox_subtractive_freq1.Text = trackBar_subtractive_freq1.Value.ToString();
        }

        private void trackBar_subtractive_freq2_Scroll(object sender, EventArgs e)
        {
            textBox_subtractive_freq2.Text = trackBar_subtractive_freq2.Value.ToString();
        }

        private void radioButton_subtractive_lowpass_CheckedChanged(object sender, EventArgs e)
        {
            trackBar_subtractive_freq2.Enabled = true;
            textBox_subtractive_freq2.Enabled = true;
            trackBar_subtractive_freq1.Enabled = false;
            textBox_subtractive_freq1.Enabled = false;
            highfreq = trackBar_subtractive_freq2.Value;
            filtertype = 0;
            sendSubtractiveParameters();
        }

        private void radioButton_subtractive_highpass_CheckedChanged(object sender, EventArgs e)
        {
            trackBar_subtractive_freq1.Enabled = true;
            textBox_subtractive_freq1.Enabled = true;
            trackBar_subtractive_freq2.Enabled = false;
            textBox_subtractive_freq2.Enabled = false;
           
            filtertype = 1;
            lowfreq = trackBar_subtractive_freq1.Value;
            highfreq = 96000;
            sendSubtractiveParameters();
        }

        private void radioButton_subtractive_bandpass_CheckedChanged(object sender, EventArgs e)
        {
            trackBar_subtractive_freq1.Enabled = true;
            textBox_subtractive_freq1.Enabled = true;
            trackBar_subtractive_freq2.Enabled = true;
            textBox_subtractive_freq2.Enabled = true;

            filtertype = 2;
            lowfreq = trackBar_subtractive_freq1.Value;
            highfreq = trackBar_subtractive_freq2.Value;
            sendSubtractiveParameters();
        }

        private void radioButton_subtractive_bandstop_CheckedChanged(object sender, EventArgs e)
        {
            trackBar_subtractive_freq1.Enabled = true;
            textBox_subtractive_freq1.Enabled = true;
            trackBar_subtractive_freq2.Enabled = true;
            textBox_subtractive_freq2.Enabled = true;
            
            filtertype = 3;
            lowfreq = trackBar_subtractive_freq1.Value;
            highfreq = trackBar_subtractive_freq2.Value;
            sendSubtractiveParameters();
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click_1(object sender, EventArgs e)
        {

        }

        private void button_additive_en_Click(object sender, EventArgs e)
        {
            Console.WriteLine("siemsa");
            if (button_additive_hammond_en.Text.Equals("Disabled"))
            {
                send(101, 1, 0, 0, 0, 0, 0);
            }
            else
            {
                send(101, 2, 0, 0, 0, 0, 0);
            }
        }

        private void drawbar3_Load(object sender, EventArgs e)
        {

        }


        private void tabPage_additive_Click(object sender, EventArgs e)
        {

        }

        private void tabPage_additive_hammond_Click(object sender, EventArgs e)
        {

        }

        private void textBox_subtractive_freq1_TextChanged(object sender, EventArgs e)
        {
            int val = Convert.ToInt32(textBox_subtractive_freq1.Text);
            if (val > trackBar_subtractive_freq1.Maximum)
                val = trackBar_subtractive_freq1.Maximum;
            if (val < trackBar_subtractive_freq1.Minimum)
                val = trackBar_subtractive_freq1.Minimum;

            trackBar_subtractive_freq1.Value = val;
            textBox_subtractive_freq1.Text = val.ToString();
        }

        private void textBox_subtractive_freq2_TextChanged(object sender, EventArgs e)
        {
            int val = Convert.ToInt32(textBox_subtractive_freq2.Text);
            if (val > trackBar_subtractive_freq2.Maximum)
                val = trackBar_subtractive_freq2.Maximum;
            if (val < trackBar_subtractive_freq2.Minimum)
                val = trackBar_subtractive_freq2.Minimum;

            trackBar_subtractive_freq2.Value = val;
            textBox_subtractive_freq2.Text = val.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // SEND VALUES
            highfreq = trackBar_subtractive_freq2.Value;
            lowfreq = trackBar_subtractive_freq1.Value;

            sendSubtractiveParameters();
        }

        private void textBox_fm_modamp_TextChanged(object sender, EventArgs e)
        {
            int val = Convert.ToInt32(textBox_fm_modamp.Text);
            if (val > trackBar_fm_modamp.Maximum)
                val = trackBar_fm_modamp.Maximum;
            if (val < trackBar_fm_modamp.Minimum)
                val = trackBar_fm_modamp.Minimum;

            trackBar_fm_modamp.Value = val;
            textBox_fm_modamp.Text = val.ToString();
        }

        private void trackBar_fm_modamp_Scroll(object sender, EventArgs e)
        {
            textBox_fm_modamp.Text = trackBar_fm_modamp.Value.ToString();
        }

        private void trackBar_fm_modfreq_Scroll(object sender, EventArgs e)
        {
            textBox_fm_modfreq.Text = trackBar_fm_modfreq.Value.ToString();
        }

        private void textBox_fm_modfreq_TextChanged(object sender, EventArgs e)
        {
            int val = Convert.ToInt32(textBox_fm_modfreq.Text);
            if (val > trackBar_fm_modfreq.Maximum)
                val = trackBar_fm_modfreq.Maximum;
            if (val < trackBar_fm_modfreq.Minimum)
                val = trackBar_fm_modfreq.Minimum;

            trackBar_fm_modfreq.Value = val;
            textBox_fm_modfreq.Text = val.ToString();
        }

        private void button_fm_en_Click(object sender, EventArgs e)
        {
            if (button_fm_en.Text.Equals("Disabled"))
            {
                send(102, 1, 0, 0, 0, 0, 0);
            }
            else
            {
                send(102, 2, 0, 0, 0, 0, 0);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // FM - signal 102
            sendInt(102, 4, (UInt32)trackBar_fm_modamp.Value);
            sendInt(102, 3, (UInt32)trackBar_fm_modfreq.Value);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // ADDITIVE - signal 101
            byte[] knob1Array = BitConverter.GetBytes(drawbar1.Value);
            send(101, 11, knob1Array[0], knob1Array[1], 0, 0, 0);

            byte[] knob2Array = BitConverter.GetBytes(drawbar2.Value);
            send(101, 12, knob2Array[0], knob2Array[1], 0, 0, 0);

            byte[] knob3Array = BitConverter.GetBytes(drawbar3.Value);
            send(101, 13, knob3Array[0], knob3Array[1], 0, 0, 0);

            byte[] knob4Array = BitConverter.GetBytes(drawbar4.Value);
            send(101, 14, knob4Array[0], knob4Array[1], 0, 0, 0);

            byte[] knob5Array = BitConverter.GetBytes(drawbar5.Value);
            send(101, 15, knob5Array[0], knob5Array[1], 0, 0, 0);

            byte[] knob6Array = BitConverter.GetBytes(drawbar6.Value);
            send(101, 16, knob6Array[0], knob6Array[1], 0, 0, 0);

            byte[] knob7Array = BitConverter.GetBytes(drawbar7.Value);
            send(101, 17, knob7Array[0], knob7Array[1], 0, 0, 0);

            byte[] knob8Array = BitConverter.GetBytes(drawbar8.Value);
            send(101, 18, knob8Array[0], knob8Array[1], 0, 0, 0);

            byte[] knob9Array = BitConverter.GetBytes(drawbar9.Value);
            send(101, 19, knob9Array[0], knob9Array[1], 0, 0, 0);
        }

        private void button_adsr_set_Click(object sender, EventArgs e)
        {
            // ADSR - signal 200
            byte[] byteArray;
            // attack
            double att_log = Math.Pow(knobControl_attack.Maximum - Convert.ToInt32(knobControl_attack.Value) + 1, 2); // logarithm, base 2
            int att_val = knobControl_attack.Maximum - Convert.ToInt32(knobControl_attack.Value) + 1;
            byteArray = BitConverter.GetBytes((int)(att_val*0.75) + 1);
            send(200, 1, byteArray[0], byteArray[1], 0, 0, 0);

            // decay
            double dec_log = Math.Log(knobControl_decay.Maximum - Convert.ToInt32(knobControl_decay.Value) + 1, 2);
            int dec_val = knobControl_decay.Maximum - Convert.ToInt32(knobControl_decay.Value) + 1;
            byteArray = BitConverter.GetBytes((int)(dec_val*0.75) + 1);
            send(200, 2, byteArray[0], byteArray[1], 0, 0, 0);

            // sustain
            byteArray = BitConverter.GetBytes(Convert.ToInt32(knobControl_sustain.Value));
            send(200, 3, byteArray[0], byteArray[1], 0, 0, 0);

            // release
            double rel_log = Math.Log(knobControl_release.Maximum - Convert.ToInt32(knobControl_release.Value) + 1, 2); // logarithm, base 2
            int rel_val = knobControl_release.Maximum - Convert.ToInt32(knobControl_release.Value) + 1;
            byteArray = BitConverter.GetBytes((int)(rel_val*0.5) + 1);
            send(200, 4, byteArray[0], byteArray[1], 0, 0, 0);
        }

        private void radioButton_subtractive_square_CheckedChanged(object sender, EventArgs e)
        {
            waveformtype = 1;
            sendSubtractiveParameters();
        }
        private void sendSubtractiveParameters()
        {
            sendInt(100, 4, (UInt32)highfreq); // set higher frequency
            sendInt(100, 3, (UInt32)lowfreq); // zero lower frequency
            sendInt(100, 5, (UInt32)filtertype); // set 0(lowpass) filter type
            sendInt(100, 6, (UInt32)waveformtype); // set 0(lowpass) filter type
        }

        private void radioButton_subtractive_triangle_CheckedChanged(object sender, EventArgs e)
        {
            waveformtype = 2;
            sendSubtractiveParameters();
        }

        private void radioButton_subtractive_sawtooth_CheckedChanged(object sender, EventArgs e)
        {
            waveformtype = 3;
            sendSubtractiveParameters();
        }

        private void button_fm_bell_Click(object sender, EventArgs e)
        {
            // FM - signal 102
            sendInt(102, 7, (UInt32)trackBar_fm_bell.Value);
        }

        private void button_fm_bell_en_Click(object sender, EventArgs e)
        {
            if (button_fm_bell_en.Text.Equals("Disabled"))
            {
                send(102, 5, 0, 0, 0, 0, 0);
            }
            else
            {
                send(102, 6, 0, 0, 0, 0, 0);
            }
        }

        private void button_flute_en_Click(object sender, EventArgs e)
        {
            // Flute - signal 109
            if (button_subtractive_en.Text.Equals("Disabled"))
            {
                send(109, 1, 0, 0, 0, 0, 0);
            }
            else
            {
                send(109, 2, 0, 0, 0, 0, 0);
            }
        }
    }
}
