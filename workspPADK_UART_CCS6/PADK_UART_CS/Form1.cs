using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PADK_UART_CS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.serialPort1.Open();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //System.IO.Ports.SerialData.
            //e.EventType.
            //if (!(e.Equals()))
            //            if (!(e.Equals()EventType == System.IO.Ports.e))
            try
            {
                String xx = this.serialPort1.ReadLine();
            }
            catch (TimeoutException)
            {

            }
        }

        private void wyslij_b1_Click(object sender, EventArgs e)
        {
            this.serialPort1.Write("tekst");
        }
    }
}
