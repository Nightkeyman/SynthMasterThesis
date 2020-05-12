namespace UARTCOM2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnGetSerialPorts = new System.Windows.Forms.Button();
            this.comboBox_port = new System.Windows.Forms.ComboBox();
            this.textBox_baudrate = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button_open = new System.Windows.Forms.Button();
            this.richTextBox_received = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button_clear = new System.Windows.Forms.Button();
            this.textBox_send = new System.Windows.Forms.TextBox();
            this.button_send = new System.Windows.Forms.Button();
            this.tabPage_Connection = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage_subtractive = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_subtractive_frequency = new System.Windows.Forms.TextBox();
            this.knobControl1 = new KnobControl.KnobControl();
            this.button_subtractive_en = new System.Windows.Forms.Button();
            this.button_subtractive_toggle = new System.Windows.Forms.Button();
            this.radioButton_subtractive_square = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_triangle = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_sawtooth = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButton_subtractive_lowpass = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_highpass = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_bandpass = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_bandstop = new System.Windows.Forms.RadioButton();
            this.trackBar_subtractive_freq1 = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_subtractive_freq1 = new System.Windows.Forms.TextBox();
            this.textBox_subtractive_freq2 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.trackBar_subtractive_freq2 = new System.Windows.Forms.TrackBar();
            this.tabPage_Connection.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage_subtractive.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq2)).BeginInit();
            this.SuspendLayout();
            // 
            // btnGetSerialPorts
            // 
            this.btnGetSerialPorts.Location = new System.Drawing.Point(171, 66);
            this.btnGetSerialPorts.Name = "btnGetSerialPorts";
            this.btnGetSerialPorts.Size = new System.Drawing.Size(75, 23);
            this.btnGetSerialPorts.TabIndex = 0;
            this.btnGetSerialPorts.Text = "Refresh";
            this.btnGetSerialPorts.UseVisualStyleBackColor = true;
            this.btnGetSerialPorts.Click += new System.EventHandler(this.btnGetSerialPorts_Click);
            // 
            // comboBox_port
            // 
            this.comboBox_port.FormattingEnabled = true;
            this.comboBox_port.Location = new System.Drawing.Point(65, 68);
            this.comboBox_port.Name = "comboBox_port";
            this.comboBox_port.Size = new System.Drawing.Size(100, 21);
            this.comboBox_port.TabIndex = 2;
            // 
            // textBox_baudrate
            // 
            this.textBox_baudrate.Location = new System.Drawing.Point(65, 95);
            this.textBox_baudrate.Name = "textBox_baudrate";
            this.textBox_baudrate.Size = new System.Drawing.Size(181, 20);
            this.textBox_baudrate.TabIndex = 3;
            this.textBox_baudrate.Text = "115200";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(30, 71);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Port:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Baudrate:";
            // 
            // button_open
            // 
            this.button_open.Location = new System.Drawing.Point(65, 122);
            this.button_open.Name = "button_open";
            this.button_open.Size = new System.Drawing.Size(181, 23);
            this.button_open.TabIndex = 6;
            this.button_open.Text = "Open";
            this.button_open.UseVisualStyleBackColor = true;
            this.button_open.Click += new System.EventHandler(this.button_open_Click);
            // 
            // richTextBox_received
            // 
            this.richTextBox_received.Location = new System.Drawing.Point(9, 215);
            this.richTextBox_received.Name = "richTextBox_received";
            this.richTextBox_received.Size = new System.Drawing.Size(225, 175);
            this.richTextBox_received.TabIndex = 7;
            this.richTextBox_received.Text = "";
            this.richTextBox_received.MouseUp += new System.Windows.Forms.MouseEventHandler(this.richTextBox_received_MouseUp);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 199);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Received:";
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(159, 189);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 23);
            this.button_clear.TabIndex = 9;
            this.button_clear.Text = "Clear";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.button_clear_Click);
            // 
            // textBox_send
            // 
            this.textBox_send.Location = new System.Drawing.Point(9, 396);
            this.textBox_send.Name = "textBox_send";
            this.textBox_send.Size = new System.Drawing.Size(144, 20);
            this.textBox_send.TabIndex = 10;
            // 
            // button_send
            // 
            this.button_send.Location = new System.Drawing.Point(159, 396);
            this.button_send.Name = "button_send";
            this.button_send.Size = new System.Drawing.Size(75, 23);
            this.button_send.TabIndex = 11;
            this.button_send.Text = "Send";
            this.button_send.UseVisualStyleBackColor = true;
            this.button_send.Click += new System.EventHandler(this.button_send_Click);
            // 
            // tabPage_Connection
            // 
            this.tabPage_Connection.Controls.Add(this.tabPage1);
            this.tabPage_Connection.Controls.Add(this.tabPage_subtractive);
            this.tabPage_Connection.Location = new System.Drawing.Point(-1, 0);
            this.tabPage_Connection.Name = "tabPage_Connection";
            this.tabPage_Connection.SelectedIndex = 0;
            this.tabPage_Connection.Size = new System.Drawing.Size(800, 452);
            this.tabPage_Connection.TabIndex = 12;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.SystemColors.Menu;
            this.tabPage1.Controls.Add(this.btnGetSerialPorts);
            this.tabPage1.Controls.Add(this.button_send);
            this.tabPage1.Controls.Add(this.comboBox_port);
            this.tabPage1.Controls.Add(this.textBox_send);
            this.tabPage1.Controls.Add(this.textBox_baudrate);
            this.tabPage1.Controls.Add(this.button_clear);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.richTextBox_received);
            this.tabPage1.Controls.Add(this.button_open);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(792, 426);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Connection";
            // 
            // tabPage_subtractive
            // 
            this.tabPage_subtractive.BackColor = System.Drawing.SystemColors.Menu;
            this.tabPage_subtractive.Controls.Add(this.groupBox2);
            this.tabPage_subtractive.Controls.Add(this.groupBox1);
            this.tabPage_subtractive.Controls.Add(this.button_subtractive_en);
            this.tabPage_subtractive.Location = new System.Drawing.Point(4, 22);
            this.tabPage_subtractive.Name = "tabPage_subtractive";
            this.tabPage_subtractive.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_subtractive.Size = new System.Drawing.Size(792, 426);
            this.tabPage_subtractive.TabIndex = 1;
            this.tabPage_subtractive.Text = "Subtractive";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton_subtractive_sawtooth);
            this.groupBox1.Controls.Add(this.radioButton_subtractive_triangle);
            this.groupBox1.Controls.Add(this.radioButton_subtractive_square);
            this.groupBox1.Controls.Add(this.button_subtractive_toggle);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textBox_subtractive_frequency);
            this.groupBox1.Controls.Add(this.knobControl1);
            this.groupBox1.Location = new System.Drawing.Point(10, 36);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(182, 325);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Waveform";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 293);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Frequency:";
            // 
            // textBox_subtractive_frequency
            // 
            this.textBox_subtractive_frequency.Location = new System.Drawing.Point(89, 290);
            this.textBox_subtractive_frequency.Name = "textBox_subtractive_frequency";
            this.textBox_subtractive_frequency.Size = new System.Drawing.Size(59, 20);
            this.textBox_subtractive_frequency.TabIndex = 2;
            this.textBox_subtractive_frequency.Text = "100";
            // 
            // knobControl1
            // 
            this.knobControl1.DrawDivInside = true;
            this.knobControl1.EndAngle = 405F;
            this.knobControl1.ImeMode = System.Windows.Forms.ImeMode.Close;
            this.knobControl1.KnobBackColor = System.Drawing.Color.White;
            this.knobControl1.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.knobControl1.LargeChange = 5;
            this.knobControl1.Location = new System.Drawing.Point(6, 121);
            this.knobControl1.Maximum = 12000;
            this.knobControl1.Minimum = 0;
            this.knobControl1.Name = "knobControl1";
            this.knobControl1.PointerColor = System.Drawing.Color.LightSteelBlue;
            this.knobControl1.ScaleColor = System.Drawing.Color.Black;
            this.knobControl1.ScaleDivisions = 11;
            this.knobControl1.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.knobControl1.ScaleSubDivisions = 4;
            this.knobControl1.ShowLargeScale = true;
            this.knobControl1.ShowSmallScale = false;
            this.knobControl1.Size = new System.Drawing.Size(159, 159);
            this.knobControl1.SmallChange = 1;
            this.knobControl1.StartAngle = 135F;
            this.knobControl1.TabIndex = 1;
            this.knobControl1.Value = 100;
            this.knobControl1.ValueChanged += new KnobControl.ValueChangedEventHandler(this.knobControl1_ValueChanged);
            this.knobControl1.Load += new System.EventHandler(this.knobControl1_Load);
            // 
            // button_subtractive_en
            // 
            this.button_subtractive_en.ForeColor = System.Drawing.Color.Red;
            this.button_subtractive_en.Location = new System.Drawing.Point(6, 6);
            this.button_subtractive_en.Name = "button_subtractive_en";
            this.button_subtractive_en.Size = new System.Drawing.Size(75, 23);
            this.button_subtractive_en.TabIndex = 0;
            this.button_subtractive_en.Text = "Disabled";
            this.button_subtractive_en.UseVisualStyleBackColor = true;
            this.button_subtractive_en.Click += new System.EventHandler(this.button_subtractive_en_Click);
            // 
            // button_subtractive_toggle
            // 
            this.button_subtractive_toggle.Location = new System.Drawing.Point(65, 190);
            this.button_subtractive_toggle.Name = "button_subtractive_toggle";
            this.button_subtractive_toggle.Size = new System.Drawing.Size(38, 23);
            this.button_subtractive_toggle.TabIndex = 4;
            this.button_subtractive_toggle.Text = "High";
            this.button_subtractive_toggle.UseVisualStyleBackColor = true;
            this.button_subtractive_toggle.Click += new System.EventHandler(this.button_subtractive_toggle_Click);
            // 
            // radioButton_subtractive_square
            // 
            this.radioButton_subtractive_square.AutoSize = true;
            this.radioButton_subtractive_square.Location = new System.Drawing.Point(7, 20);
            this.radioButton_subtractive_square.Name = "radioButton_subtractive_square";
            this.radioButton_subtractive_square.Size = new System.Drawing.Size(59, 17);
            this.radioButton_subtractive_square.TabIndex = 5;
            this.radioButton_subtractive_square.TabStop = true;
            this.radioButton_subtractive_square.Text = "Square";
            this.radioButton_subtractive_square.UseVisualStyleBackColor = true;
            // 
            // radioButton_subtractive_triangle
            // 
            this.radioButton_subtractive_triangle.AutoSize = true;
            this.radioButton_subtractive_triangle.Location = new System.Drawing.Point(6, 44);
            this.radioButton_subtractive_triangle.Name = "radioButton_subtractive_triangle";
            this.radioButton_subtractive_triangle.Size = new System.Drawing.Size(63, 17);
            this.radioButton_subtractive_triangle.TabIndex = 6;
            this.radioButton_subtractive_triangle.TabStop = true;
            this.radioButton_subtractive_triangle.Text = "Triangle";
            this.radioButton_subtractive_triangle.UseVisualStyleBackColor = true;
            // 
            // radioButton_subtractive_sawtooth
            // 
            this.radioButton_subtractive_sawtooth.AutoSize = true;
            this.radioButton_subtractive_sawtooth.Location = new System.Drawing.Point(6, 68);
            this.radioButton_subtractive_sawtooth.Name = "radioButton_subtractive_sawtooth";
            this.radioButton_subtractive_sawtooth.Size = new System.Drawing.Size(70, 17);
            this.radioButton_subtractive_sawtooth.TabIndex = 7;
            this.radioButton_subtractive_sawtooth.TabStop = true;
            this.radioButton_subtractive_sawtooth.Text = "Sawtooth";
            this.radioButton_subtractive_sawtooth.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_subtractive_freq2);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.trackBar_subtractive_freq2);
            this.groupBox2.Controls.Add(this.textBox_subtractive_freq1);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.trackBar_subtractive_freq1);
            this.groupBox2.Controls.Add(this.radioButton_subtractive_bandstop);
            this.groupBox2.Controls.Add(this.radioButton_subtractive_bandpass);
            this.groupBox2.Controls.Add(this.radioButton_subtractive_highpass);
            this.groupBox2.Controls.Add(this.radioButton_subtractive_lowpass);
            this.groupBox2.Location = new System.Drawing.Point(198, 36);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(518, 325);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Filter";
            // 
            // radioButton_subtractive_lowpass
            // 
            this.radioButton_subtractive_lowpass.AutoSize = true;
            this.radioButton_subtractive_lowpass.Location = new System.Drawing.Point(7, 20);
            this.radioButton_subtractive_lowpass.Name = "radioButton_subtractive_lowpass";
            this.radioButton_subtractive_lowpass.Size = new System.Drawing.Size(70, 17);
            this.radioButton_subtractive_lowpass.TabIndex = 0;
            this.radioButton_subtractive_lowpass.TabStop = true;
            this.radioButton_subtractive_lowpass.Text = "Low pass";
            this.radioButton_subtractive_lowpass.UseVisualStyleBackColor = true;
            this.radioButton_subtractive_lowpass.CheckedChanged += new System.EventHandler(this.radioButton_subtractive_lowpass_CheckedChanged);
            // 
            // radioButton_subtractive_highpass
            // 
            this.radioButton_subtractive_highpass.AutoSize = true;
            this.radioButton_subtractive_highpass.Location = new System.Drawing.Point(7, 44);
            this.radioButton_subtractive_highpass.Name = "radioButton_subtractive_highpass";
            this.radioButton_subtractive_highpass.Size = new System.Drawing.Size(72, 17);
            this.radioButton_subtractive_highpass.TabIndex = 1;
            this.radioButton_subtractive_highpass.TabStop = true;
            this.radioButton_subtractive_highpass.Text = "High pass";
            this.radioButton_subtractive_highpass.UseVisualStyleBackColor = true;
            this.radioButton_subtractive_highpass.CheckedChanged += new System.EventHandler(this.radioButton_subtractive_highpass_CheckedChanged);
            // 
            // radioButton_subtractive_bandpass
            // 
            this.radioButton_subtractive_bandpass.AutoSize = true;
            this.radioButton_subtractive_bandpass.Location = new System.Drawing.Point(7, 68);
            this.radioButton_subtractive_bandpass.Name = "radioButton_subtractive_bandpass";
            this.radioButton_subtractive_bandpass.Size = new System.Drawing.Size(75, 17);
            this.radioButton_subtractive_bandpass.TabIndex = 2;
            this.radioButton_subtractive_bandpass.TabStop = true;
            this.radioButton_subtractive_bandpass.Text = "Band pass";
            this.radioButton_subtractive_bandpass.UseVisualStyleBackColor = true;
            this.radioButton_subtractive_bandpass.CheckedChanged += new System.EventHandler(this.radioButton_subtractive_bandpass_CheckedChanged);
            // 
            // radioButton_subtractive_bandstop
            // 
            this.radioButton_subtractive_bandstop.AutoSize = true;
            this.radioButton_subtractive_bandstop.Location = new System.Drawing.Point(7, 92);
            this.radioButton_subtractive_bandstop.Name = "radioButton_subtractive_bandstop";
            this.radioButton_subtractive_bandstop.Size = new System.Drawing.Size(73, 17);
            this.radioButton_subtractive_bandstop.TabIndex = 3;
            this.radioButton_subtractive_bandstop.TabStop = true;
            this.radioButton_subtractive_bandstop.Text = "Band stop";
            this.radioButton_subtractive_bandstop.UseVisualStyleBackColor = true;
            this.radioButton_subtractive_bandstop.CheckedChanged += new System.EventHandler(this.radioButton_subtractive_bandstop_CheckedChanged);
            // 
            // trackBar_subtractive_freq1
            // 
            this.trackBar_subtractive_freq1.AllowDrop = true;
            this.trackBar_subtractive_freq1.Enabled = false;
            this.trackBar_subtractive_freq1.LargeChange = 50;
            this.trackBar_subtractive_freq1.Location = new System.Drawing.Point(6, 168);
            this.trackBar_subtractive_freq1.Maximum = 12000;
            this.trackBar_subtractive_freq1.Name = "trackBar_subtractive_freq1";
            this.trackBar_subtractive_freq1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_subtractive_freq1.Size = new System.Drawing.Size(490, 45);
            this.trackBar_subtractive_freq1.SmallChange = 10;
            this.trackBar_subtractive_freq1.TabIndex = 4;
            this.trackBar_subtractive_freq1.TickFrequency = 1000;
            this.trackBar_subtractive_freq1.Scroll += new System.EventHandler(this.trackBar_subtractive_freq1_Scroll);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 152);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(69, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Frequency 1:";
            // 
            // textBox_subtractive_freq1
            // 
            this.textBox_subtractive_freq1.Enabled = false;
            this.textBox_subtractive_freq1.Location = new System.Drawing.Point(81, 149);
            this.textBox_subtractive_freq1.Name = "textBox_subtractive_freq1";
            this.textBox_subtractive_freq1.Size = new System.Drawing.Size(100, 20);
            this.textBox_subtractive_freq1.TabIndex = 6;
            this.textBox_subtractive_freq1.Text = "0";
            // 
            // textBox_subtractive_freq2
            // 
            this.textBox_subtractive_freq2.Enabled = false;
            this.textBox_subtractive_freq2.Location = new System.Drawing.Point(81, 235);
            this.textBox_subtractive_freq2.Name = "textBox_subtractive_freq2";
            this.textBox_subtractive_freq2.Size = new System.Drawing.Size(100, 20);
            this.textBox_subtractive_freq2.TabIndex = 9;
            this.textBox_subtractive_freq2.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 238);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(69, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Frequency 2:";
            // 
            // trackBar_subtractive_freq2
            // 
            this.trackBar_subtractive_freq2.AllowDrop = true;
            this.trackBar_subtractive_freq2.Enabled = false;
            this.trackBar_subtractive_freq2.LargeChange = 50;
            this.trackBar_subtractive_freq2.Location = new System.Drawing.Point(6, 190);
            this.trackBar_subtractive_freq2.Maximum = 12000;
            this.trackBar_subtractive_freq2.Name = "trackBar_subtractive_freq2";
            this.trackBar_subtractive_freq2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_subtractive_freq2.Size = new System.Drawing.Size(490, 45);
            this.trackBar_subtractive_freq2.SmallChange = 10;
            this.trackBar_subtractive_freq2.TabIndex = 7;
            this.trackBar_subtractive_freq2.TickFrequency = 1000;
            this.trackBar_subtractive_freq2.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.trackBar_subtractive_freq2.Scroll += new System.EventHandler(this.trackBar_subtractive_freq2_Scroll);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabPage_Connection);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tabPage_Connection.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage_subtractive.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGetSerialPorts;
        private System.Windows.Forms.ComboBox comboBox_port;
        private System.Windows.Forms.TextBox textBox_baudrate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button_open;
        private System.Windows.Forms.RichTextBox richTextBox_received;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_clear;
        private System.Windows.Forms.TextBox textBox_send;
        private System.Windows.Forms.Button button_send;
        private System.Windows.Forms.TabControl tabPage_Connection;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage_subtractive;
        private System.Windows.Forms.Button button_subtractive_en;
        private KnobControl.KnobControl knobControl1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_subtractive_frequency;
        private System.Windows.Forms.Button button_subtractive_toggle;
        private System.Windows.Forms.RadioButton radioButton_subtractive_sawtooth;
        private System.Windows.Forms.RadioButton radioButton_subtractive_triangle;
        private System.Windows.Forms.RadioButton radioButton_subtractive_square;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton radioButton_subtractive_bandstop;
        private System.Windows.Forms.RadioButton radioButton_subtractive_bandpass;
        private System.Windows.Forms.RadioButton radioButton_subtractive_highpass;
        private System.Windows.Forms.RadioButton radioButton_subtractive_lowpass;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TrackBar trackBar_subtractive_freq1;
        private System.Windows.Forms.TextBox textBox_subtractive_freq2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TrackBar trackBar_subtractive_freq2;
        private System.Windows.Forms.TextBox textBox_subtractive_freq1;
    }
}

