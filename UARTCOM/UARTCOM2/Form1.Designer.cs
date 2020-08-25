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
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox_subtractive_freq2 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.trackBar_subtractive_freq2 = new System.Windows.Forms.TrackBar();
            this.textBox_subtractive_freq1 = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.trackBar_subtractive_freq1 = new System.Windows.Forms.TrackBar();
            this.radioButton_subtractive_bandstop = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_bandpass = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_highpass = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_lowpass = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButton_subtractive_sawtooth = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_triangle = new System.Windows.Forms.RadioButton();
            this.radioButton_subtractive_square = new System.Windows.Forms.RadioButton();
            this.button_subtractive_en = new System.Windows.Forms.Button();
            this.tabPage_additive = new System.Windows.Forms.TabPage();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage_additive_hammond = new System.Windows.Forms.TabPage();
            this.button4 = new System.Windows.Forms.Button();
            this.drawbar1 = new KnobControl.KnobControl();
            this.button_additive_hammond_en = new System.Windows.Forms.Button();
            this.drawbar6 = new KnobControl.KnobControl();
            this.drawbar2 = new KnobControl.KnobControl();
            this.drawbar5 = new KnobControl.KnobControl();
            this.drawbar3 = new KnobControl.KnobControl();
            this.drawbar4 = new KnobControl.KnobControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button_fm_en = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button3 = new System.Windows.Forms.Button();
            this.textBox_fm_modfreq = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBar_fm_modfreq = new System.Windows.Forms.TrackBar();
            this.textBox_fm_modamp = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.trackBar_fm_modamp = new System.Windows.Forms.TrackBar();
            this.ADSR = new System.Windows.Forms.GroupBox();
            this.label_release_knob = new System.Windows.Forms.Label();
            this.label_sustain_knob = new System.Windows.Forms.Label();
            this.label_decay_knob = new System.Windows.Forms.Label();
            this.label_attack_knob = new System.Windows.Forms.Label();
            this.knobControl_release = new KnobControl.KnobControl();
            this.knobControl_decay = new KnobControl.KnobControl();
            this.knobControl_sustain = new KnobControl.KnobControl();
            this.knobControl_attack = new KnobControl.KnobControl();
            this.button_adsr_set = new System.Windows.Forms.Button();
            this.drawbar7 = new KnobControl.KnobControl();
            this.drawbar8 = new KnobControl.KnobControl();
            this.drawbar9 = new KnobControl.KnobControl();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.tabPage_Connection.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage_subtractive.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.tabPage_additive.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage_additive_hammond.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_fm_modfreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_fm_modamp)).BeginInit();
            this.ADSR.SuspendLayout();
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
            this.tabPage_Connection.Controls.Add(this.tabPage_additive);
            this.tabPage_Connection.Controls.Add(this.tabPage2);
            this.tabPage_Connection.Location = new System.Drawing.Point(-1, 0);
            this.tabPage_Connection.Name = "tabPage_Connection";
            this.tabPage_Connection.SelectedIndex = 0;
            this.tabPage_Connection.Size = new System.Drawing.Size(700, 452);
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
            this.tabPage1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tabPage1.Size = new System.Drawing.Size(904, 426);
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
            this.tabPage_subtractive.Size = new System.Drawing.Size(654, 426);
            this.tabPage_subtractive.TabIndex = 1;
            this.tabPage_subtractive.Text = "Subtractive";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button1);
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
            this.groupBox2.Location = new System.Drawing.Point(10, 148);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(604, 268);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Filter";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(502, 177);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(87, 36);
            this.button1.TabIndex = 10;
            this.button1.Text = "Set";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox_subtractive_freq2
            // 
            this.textBox_subtractive_freq2.Enabled = false;
            this.textBox_subtractive_freq2.Location = new System.Drawing.Point(111, 235);
            this.textBox_subtractive_freq2.Name = "textBox_subtractive_freq2";
            this.textBox_subtractive_freq2.Size = new System.Drawing.Size(100, 20);
            this.textBox_subtractive_freq2.TabIndex = 9;
            this.textBox_subtractive_freq2.Text = "20000";
            this.textBox_subtractive_freq2.TextChanged += new System.EventHandler(this.textBox_subtractive_freq2_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 238);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(102, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Lowpass frequency:";
            // 
            // trackBar_subtractive_freq2
            // 
            this.trackBar_subtractive_freq2.AllowDrop = true;
            this.trackBar_subtractive_freq2.Enabled = false;
            this.trackBar_subtractive_freq2.LargeChange = 50;
            this.trackBar_subtractive_freq2.Location = new System.Drawing.Point(6, 190);
            this.trackBar_subtractive_freq2.Maximum = 20000;
            this.trackBar_subtractive_freq2.Name = "trackBar_subtractive_freq2";
            this.trackBar_subtractive_freq2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_subtractive_freq2.Size = new System.Drawing.Size(490, 45);
            this.trackBar_subtractive_freq2.SmallChange = 10;
            this.trackBar_subtractive_freq2.TabIndex = 7;
            this.trackBar_subtractive_freq2.TickFrequency = 1000;
            this.trackBar_subtractive_freq2.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.trackBar_subtractive_freq2.Value = 20000;
            this.trackBar_subtractive_freq2.Scroll += new System.EventHandler(this.trackBar_subtractive_freq2_Scroll);
            // 
            // textBox_subtractive_freq1
            // 
            this.textBox_subtractive_freq1.Enabled = false;
            this.textBox_subtractive_freq1.Location = new System.Drawing.Point(111, 149);
            this.textBox_subtractive_freq1.Name = "textBox_subtractive_freq1";
            this.textBox_subtractive_freq1.Size = new System.Drawing.Size(100, 20);
            this.textBox_subtractive_freq1.TabIndex = 6;
            this.textBox_subtractive_freq1.Text = "0";
            this.textBox_subtractive_freq1.TextChanged += new System.EventHandler(this.textBox_subtractive_freq1_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 152);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(104, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Highpass frequency:";
            // 
            // trackBar_subtractive_freq1
            // 
            this.trackBar_subtractive_freq1.AllowDrop = true;
            this.trackBar_subtractive_freq1.Enabled = false;
            this.trackBar_subtractive_freq1.LargeChange = 50;
            this.trackBar_subtractive_freq1.Location = new System.Drawing.Point(6, 168);
            this.trackBar_subtractive_freq1.Maximum = 20000;
            this.trackBar_subtractive_freq1.Name = "trackBar_subtractive_freq1";
            this.trackBar_subtractive_freq1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_subtractive_freq1.Size = new System.Drawing.Size(490, 45);
            this.trackBar_subtractive_freq1.SmallChange = 10;
            this.trackBar_subtractive_freq1.TabIndex = 4;
            this.trackBar_subtractive_freq1.TickFrequency = 1000;
            this.trackBar_subtractive_freq1.Scroll += new System.EventHandler(this.trackBar_subtractive_freq1_Scroll);
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
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton_subtractive_sawtooth);
            this.groupBox1.Controls.Add(this.radioButton_subtractive_triangle);
            this.groupBox1.Controls.Add(this.radioButton_subtractive_square);
            this.groupBox1.Location = new System.Drawing.Point(10, 36);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(182, 109);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Waveform";
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
            this.radioButton_subtractive_square.CheckedChanged += new System.EventHandler(this.radioButton_subtractive_square_CheckedChanged);
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
            // tabPage_additive
            // 
            this.tabPage_additive.BackColor = System.Drawing.Color.Brown;
            this.tabPage_additive.CausesValidation = false;
            this.tabPage_additive.Controls.Add(this.tabControl1);
            this.tabPage_additive.Location = new System.Drawing.Point(4, 22);
            this.tabPage_additive.Name = "tabPage_additive";
            this.tabPage_additive.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_additive.Size = new System.Drawing.Size(692, 426);
            this.tabPage_additive.TabIndex = 2;
            this.tabPage_additive.Text = "Additive";
            this.tabPage_additive.Click += new System.EventHandler(this.tabPage_additive_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage_additive_hammond);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.ItemSize = new System.Drawing.Size(97, 18);
            this.tabControl1.Location = new System.Drawing.Point(0, 6);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(689, 420);
            this.tabControl1.TabIndex = 7;
            // 
            // tabPage_additive_hammond
            // 
            this.tabPage_additive_hammond.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.tabPage_additive_hammond.Controls.Add(this.label16);
            this.tabPage_additive_hammond.Controls.Add(this.label15);
            this.tabPage_additive_hammond.Controls.Add(this.label14);
            this.tabPage_additive_hammond.Controls.Add(this.label13);
            this.tabPage_additive_hammond.Controls.Add(this.label12);
            this.tabPage_additive_hammond.Controls.Add(this.label11);
            this.tabPage_additive_hammond.Controls.Add(this.label10);
            this.tabPage_additive_hammond.Controls.Add(this.label9);
            this.tabPage_additive_hammond.Controls.Add(this.label8);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar9);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar8);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar7);
            this.tabPage_additive_hammond.Controls.Add(this.button4);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar1);
            this.tabPage_additive_hammond.Controls.Add(this.button_additive_hammond_en);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar6);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar2);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar5);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar3);
            this.tabPage_additive_hammond.Controls.Add(this.drawbar4);
            this.tabPage_additive_hammond.Location = new System.Drawing.Point(4, 22);
            this.tabPage_additive_hammond.Name = "tabPage_additive_hammond";
            this.tabPage_additive_hammond.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_additive_hammond.Size = new System.Drawing.Size(681, 394);
            this.tabPage_additive_hammond.TabIndex = 0;
            this.tabPage_additive_hammond.Text = "Hammond Organs";
            this.tabPage_additive_hammond.Click += new System.EventHandler(this.tabPage_additive_hammond_Click);
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button4.Location = new System.Drawing.Point(274, 338);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(101, 32);
            this.button4.TabIndex = 7;
            this.button4.Text = "Set";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // drawbar1
            // 
            this.drawbar1.BackColor = System.Drawing.Color.DimGray;
            this.drawbar1.EndAngle = 405F;
            this.drawbar1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar1.KnobBackColor = System.Drawing.Color.Transparent;
            this.drawbar1.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar1.LargeChange = 1;
            this.drawbar1.Location = new System.Drawing.Point(59, 57);
            this.drawbar1.Maximum = 8;
            this.drawbar1.Minimum = 0;
            this.drawbar1.MouseWheelBarPartitions = 1;
            this.drawbar1.Name = "drawbar1";
            this.drawbar1.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar1.ScaleColor = System.Drawing.Color.Black;
            this.drawbar1.ScaleDivisions = 9;
            this.drawbar1.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar1.ScaleFontAutoSize = false;
            this.drawbar1.ScaleSubDivisions = 4;
            this.drawbar1.ShowLargeScale = true;
            this.drawbar1.ShowSmallScale = false;
            this.drawbar1.Size = new System.Drawing.Size(122, 122);
            this.drawbar1.SmallChange = 1;
            this.drawbar1.StartAngle = 135F;
            this.drawbar1.TabIndex = 1;
            this.drawbar1.Value = 0;
            this.drawbar1.Load += new System.EventHandler(this.drawbar1_Load_1);
            // 
            // button_additive_hammond_en
            // 
            this.button_additive_hammond_en.ForeColor = System.Drawing.Color.Red;
            this.button_additive_hammond_en.Location = new System.Drawing.Point(6, 3);
            this.button_additive_hammond_en.Name = "button_additive_hammond_en";
            this.button_additive_hammond_en.Size = new System.Drawing.Size(75, 23);
            this.button_additive_hammond_en.TabIndex = 3;
            this.button_additive_hammond_en.Text = "Disabled";
            this.button_additive_hammond_en.UseVisualStyleBackColor = true;
            this.button_additive_hammond_en.Click += new System.EventHandler(this.button_additive_en_Click);
            // 
            // drawbar6
            // 
            this.drawbar6.BackColor = System.Drawing.Color.DimGray;
            this.drawbar6.EndAngle = 405F;
            this.drawbar6.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar6.KnobBackColor = System.Drawing.Color.White;
            this.drawbar6.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar6.LargeChange = 1;
            this.drawbar6.Location = new System.Drawing.Point(134, 210);
            this.drawbar6.Maximum = 8;
            this.drawbar6.Minimum = 0;
            this.drawbar6.MouseWheelBarPartitions = 1;
            this.drawbar6.Name = "drawbar6";
            this.drawbar6.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar6.ScaleColor = System.Drawing.Color.Black;
            this.drawbar6.ScaleDivisions = 9;
            this.drawbar6.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar6.ScaleFontAutoSize = false;
            this.drawbar6.ScaleSubDivisions = 4;
            this.drawbar6.ShowLargeScale = true;
            this.drawbar6.ShowSmallScale = false;
            this.drawbar6.Size = new System.Drawing.Size(122, 122);
            this.drawbar6.SmallChange = 1;
            this.drawbar6.StartAngle = 135F;
            this.drawbar6.TabIndex = 6;
            this.drawbar6.Value = 0;
            // 
            // drawbar2
            // 
            this.drawbar2.BackColor = System.Drawing.Color.DimGray;
            this.drawbar2.EndAngle = 405F;
            this.drawbar2.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar2.KnobBackColor = System.Drawing.Color.White;
            this.drawbar2.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar2.LargeChange = 1;
            this.drawbar2.Location = new System.Drawing.Point(187, 57);
            this.drawbar2.Maximum = 8;
            this.drawbar2.Minimum = 0;
            this.drawbar2.MouseWheelBarPartitions = 1;
            this.drawbar2.Name = "drawbar2";
            this.drawbar2.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar2.ScaleColor = System.Drawing.Color.Black;
            this.drawbar2.ScaleDivisions = 9;
            this.drawbar2.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar2.ScaleFontAutoSize = false;
            this.drawbar2.ScaleSubDivisions = 4;
            this.drawbar2.ShowLargeScale = true;
            this.drawbar2.ShowSmallScale = false;
            this.drawbar2.Size = new System.Drawing.Size(122, 122);
            this.drawbar2.SmallChange = 1;
            this.drawbar2.StartAngle = 135F;
            this.drawbar2.TabIndex = 1;
            this.drawbar2.Value = 0;
            this.drawbar2.Load += new System.EventHandler(this.drawbar2_Load);
            // 
            // drawbar5
            // 
            this.drawbar5.BackColor = System.Drawing.Color.DimGray;
            this.drawbar5.EndAngle = 405F;
            this.drawbar5.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar5.KnobBackColor = System.Drawing.Color.White;
            this.drawbar5.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar5.LargeChange = 1;
            this.drawbar5.Location = new System.Drawing.Point(6, 210);
            this.drawbar5.Maximum = 8;
            this.drawbar5.Minimum = 0;
            this.drawbar5.MouseWheelBarPartitions = 1;
            this.drawbar5.Name = "drawbar5";
            this.drawbar5.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar5.ScaleColor = System.Drawing.Color.Black;
            this.drawbar5.ScaleDivisions = 9;
            this.drawbar5.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar5.ScaleFontAutoSize = false;
            this.drawbar5.ScaleSubDivisions = 4;
            this.drawbar5.ShowLargeScale = true;
            this.drawbar5.ShowSmallScale = false;
            this.drawbar5.Size = new System.Drawing.Size(122, 122);
            this.drawbar5.SmallChange = 1;
            this.drawbar5.StartAngle = 135F;
            this.drawbar5.TabIndex = 5;
            this.drawbar5.Value = 0;
            // 
            // drawbar3
            // 
            this.drawbar3.BackColor = System.Drawing.Color.DimGray;
            this.drawbar3.EndAngle = 405F;
            this.drawbar3.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar3.KnobBackColor = System.Drawing.Color.White;
            this.drawbar3.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar3.LargeChange = 1;
            this.drawbar3.Location = new System.Drawing.Point(315, 57);
            this.drawbar3.Maximum = 8;
            this.drawbar3.Minimum = 0;
            this.drawbar3.MouseWheelBarPartitions = 1;
            this.drawbar3.Name = "drawbar3";
            this.drawbar3.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar3.ScaleColor = System.Drawing.Color.Black;
            this.drawbar3.ScaleDivisions = 9;
            this.drawbar3.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar3.ScaleFontAutoSize = false;
            this.drawbar3.ScaleSubDivisions = 4;
            this.drawbar3.ShowLargeScale = true;
            this.drawbar3.ShowSmallScale = false;
            this.drawbar3.Size = new System.Drawing.Size(122, 122);
            this.drawbar3.SmallChange = 1;
            this.drawbar3.StartAngle = 135F;
            this.drawbar3.TabIndex = 2;
            this.drawbar3.Value = 0;
            this.drawbar3.Load += new System.EventHandler(this.drawbar3_Load);
            // 
            // drawbar4
            // 
            this.drawbar4.BackColor = System.Drawing.Color.DimGray;
            this.drawbar4.EndAngle = 405F;
            this.drawbar4.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar4.KnobBackColor = System.Drawing.Color.White;
            this.drawbar4.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar4.LargeChange = 1;
            this.drawbar4.Location = new System.Drawing.Point(443, 57);
            this.drawbar4.Maximum = 8;
            this.drawbar4.Minimum = 0;
            this.drawbar4.MouseWheelBarPartitions = 1;
            this.drawbar4.Name = "drawbar4";
            this.drawbar4.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar4.ScaleColor = System.Drawing.Color.Black;
            this.drawbar4.ScaleDivisions = 9;
            this.drawbar4.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar4.ScaleFontAutoSize = false;
            this.drawbar4.ScaleSubDivisions = 4;
            this.drawbar4.ShowLargeScale = true;
            this.drawbar4.ShowSmallScale = false;
            this.drawbar4.Size = new System.Drawing.Size(122, 122);
            this.drawbar4.SmallChange = 1;
            this.drawbar4.StartAngle = 135F;
            this.drawbar4.TabIndex = 4;
            this.drawbar4.Value = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(681, 394);
            this.tabPage3.TabIndex = 1;
            this.tabPage3.Text = "tabPage3";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.SystemColors.Menu;
            this.tabPage2.Controls.Add(this.button_fm_en);
            this.tabPage2.Controls.Add(this.groupBox3);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(636, 426);
            this.tabPage2.TabIndex = 3;
            this.tabPage2.Text = "FM";
            // 
            // button_fm_en
            // 
            this.button_fm_en.ForeColor = System.Drawing.Color.Red;
            this.button_fm_en.Location = new System.Drawing.Point(6, 6);
            this.button_fm_en.Name = "button_fm_en";
            this.button_fm_en.Size = new System.Drawing.Size(75, 23);
            this.button_fm_en.TabIndex = 5;
            this.button_fm_en.Text = "Disabled";
            this.button_fm_en.UseVisualStyleBackColor = true;
            this.button_fm_en.Click += new System.EventHandler(this.button_fm_en_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button3);
            this.groupBox3.Controls.Add(this.textBox_fm_modfreq);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.trackBar_fm_modfreq);
            this.groupBox3.Controls.Add(this.textBox_fm_modamp);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.trackBar_fm_modamp);
            this.groupBox3.Location = new System.Drawing.Point(9, 35);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(604, 268);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Modulation parameters";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(6, 161);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 11;
            this.button3.Text = "Set";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // textBox_fm_modfreq
            // 
            this.textBox_fm_modfreq.Location = new System.Drawing.Point(120, 123);
            this.textBox_fm_modfreq.Name = "textBox_fm_modfreq";
            this.textBox_fm_modfreq.Size = new System.Drawing.Size(100, 20);
            this.textBox_fm_modfreq.TabIndex = 9;
            this.textBox_fm_modfreq.Text = "0";
            this.textBox_fm_modfreq.TextChanged += new System.EventHandler(this.textBox_fm_modfreq_TextChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 126);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(112, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Modulation frequency:";
            // 
            // trackBar_fm_modfreq
            // 
            this.trackBar_fm_modfreq.AllowDrop = true;
            this.trackBar_fm_modfreq.Location = new System.Drawing.Point(7, 78);
            this.trackBar_fm_modfreq.Maximum = 50;
            this.trackBar_fm_modfreq.Name = "trackBar_fm_modfreq";
            this.trackBar_fm_modfreq.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_fm_modfreq.Size = new System.Drawing.Size(490, 45);
            this.trackBar_fm_modfreq.TabIndex = 7;
            this.trackBar_fm_modfreq.TickFrequency = 1000;
            this.trackBar_fm_modfreq.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.trackBar_fm_modfreq.Scroll += new System.EventHandler(this.trackBar_fm_modfreq_Scroll);
            // 
            // textBox_fm_modamp
            // 
            this.textBox_fm_modamp.Location = new System.Drawing.Point(120, 37);
            this.textBox_fm_modamp.Name = "textBox_fm_modamp";
            this.textBox_fm_modamp.Size = new System.Drawing.Size(100, 20);
            this.textBox_fm_modamp.TabIndex = 6;
            this.textBox_fm_modamp.Text = "0";
            this.textBox_fm_modamp.TextChanged += new System.EventHandler(this.textBox_fm_modamp_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 40);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(107, 13);
            this.label7.TabIndex = 5;
            this.label7.Text = "Modulation amplitude";
            // 
            // trackBar_fm_modamp
            // 
            this.trackBar_fm_modamp.AllowDrop = true;
            this.trackBar_fm_modamp.LargeChange = 50;
            this.trackBar_fm_modamp.Location = new System.Drawing.Point(7, 56);
            this.trackBar_fm_modamp.Maximum = 300;
            this.trackBar_fm_modamp.Name = "trackBar_fm_modamp";
            this.trackBar_fm_modamp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trackBar_fm_modamp.Size = new System.Drawing.Size(490, 45);
            this.trackBar_fm_modamp.SmallChange = 10;
            this.trackBar_fm_modamp.TabIndex = 4;
            this.trackBar_fm_modamp.TickFrequency = 1000;
            this.trackBar_fm_modamp.Scroll += new System.EventHandler(this.trackBar_fm_modamp_Scroll);
            // 
            // ADSR
            // 
            this.ADSR.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ADSR.Controls.Add(this.label_release_knob);
            this.ADSR.Controls.Add(this.label_sustain_knob);
            this.ADSR.Controls.Add(this.label_decay_knob);
            this.ADSR.Controls.Add(this.label_attack_knob);
            this.ADSR.Controls.Add(this.knobControl_release);
            this.ADSR.Controls.Add(this.knobControl_decay);
            this.ADSR.Controls.Add(this.knobControl_sustain);
            this.ADSR.Controls.Add(this.knobControl_attack);
            this.ADSR.Controls.Add(this.button_adsr_set);
            this.ADSR.ForeColor = System.Drawing.SystemColors.Control;
            this.ADSR.Location = new System.Drawing.Point(705, 71);
            this.ADSR.Name = "ADSR";
            this.ADSR.Size = new System.Drawing.Size(331, 324);
            this.ADSR.TabIndex = 13;
            this.ADSR.TabStop = false;
            this.ADSR.Text = "ADSR";
            // 
            // label_release_knob
            // 
            this.label_release_knob.AutoSize = true;
            this.label_release_knob.ForeColor = System.Drawing.SystemColors.Control;
            this.label_release_knob.Location = new System.Drawing.Point(208, 157);
            this.label_release_knob.Name = "label_release_knob";
            this.label_release_knob.Size = new System.Drawing.Size(46, 13);
            this.label_release_knob.TabIndex = 22;
            this.label_release_knob.Text = "Release";
            // 
            // label_sustain_knob
            // 
            this.label_sustain_knob.AutoSize = true;
            this.label_sustain_knob.ForeColor = System.Drawing.SystemColors.Control;
            this.label_sustain_knob.Location = new System.Drawing.Point(60, 157);
            this.label_sustain_knob.Name = "label_sustain_knob";
            this.label_sustain_knob.Size = new System.Drawing.Size(42, 13);
            this.label_sustain_knob.TabIndex = 21;
            this.label_sustain_knob.Text = "Sustain";
            // 
            // label_decay_knob
            // 
            this.label_decay_knob.AutoSize = true;
            this.label_decay_knob.ForeColor = System.Drawing.SystemColors.Control;
            this.label_decay_knob.Location = new System.Drawing.Point(216, 20);
            this.label_decay_knob.Name = "label_decay_knob";
            this.label_decay_knob.Size = new System.Drawing.Size(38, 13);
            this.label_decay_knob.TabIndex = 20;
            this.label_decay_knob.Text = "Decay";
            // 
            // label_attack_knob
            // 
            this.label_attack_knob.AutoSize = true;
            this.label_attack_knob.ForeColor = System.Drawing.SystemColors.Control;
            this.label_attack_knob.Location = new System.Drawing.Point(60, 20);
            this.label_attack_knob.Name = "label_attack_knob";
            this.label_attack_knob.Size = new System.Drawing.Size(38, 13);
            this.label_attack_knob.TabIndex = 14;
            this.label_attack_knob.Text = "Attack";
            // 
            // knobControl_release
            // 
            this.knobControl_release.EndAngle = 405F;
            this.knobControl_release.ImeMode = System.Windows.Forms.ImeMode.On;
            this.knobControl_release.KnobBackColor = System.Drawing.Color.Maroon;
            this.knobControl_release.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.line;
            this.knobControl_release.LargeChange = 5;
            this.knobControl_release.Location = new System.Drawing.Point(188, 173);
            this.knobControl_release.Maximum = 1000;
            this.knobControl_release.Minimum = 1;
            this.knobControl_release.Name = "knobControl_release";
            this.knobControl_release.PointerColor = System.Drawing.Color.Lavender;
            this.knobControl_release.ScaleColor = System.Drawing.Color.Transparent;
            this.knobControl_release.ScaleDivisions = 11;
            this.knobControl_release.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.knobControl_release.ScaleFontAutoSize = false;
            this.knobControl_release.ScaleSubDivisions = 4;
            this.knobControl_release.ShowLargeScale = false;
            this.knobControl_release.ShowSmallScale = false;
            this.knobControl_release.Size = new System.Drawing.Size(92, 92);
            this.knobControl_release.SmallChange = 1;
            this.knobControl_release.StartAngle = 135F;
            this.knobControl_release.TabIndex = 19;
            this.knobControl_release.Value = 50;
            // 
            // knobControl_decay
            // 
            this.knobControl_decay.EndAngle = 405F;
            this.knobControl_decay.ImeMode = System.Windows.Forms.ImeMode.On;
            this.knobControl_decay.KnobBackColor = System.Drawing.Color.Maroon;
            this.knobControl_decay.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.line;
            this.knobControl_decay.LargeChange = 5;
            this.knobControl_decay.Location = new System.Drawing.Point(188, 36);
            this.knobControl_decay.Maximum = 1000;
            this.knobControl_decay.Minimum = 1;
            this.knobControl_decay.Name = "knobControl_decay";
            this.knobControl_decay.PointerColor = System.Drawing.Color.Lavender;
            this.knobControl_decay.ScaleColor = System.Drawing.Color.Transparent;
            this.knobControl_decay.ScaleDivisions = 11;
            this.knobControl_decay.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.knobControl_decay.ScaleFontAutoSize = false;
            this.knobControl_decay.ScaleSubDivisions = 4;
            this.knobControl_decay.ShowLargeScale = false;
            this.knobControl_decay.ShowSmallScale = false;
            this.knobControl_decay.Size = new System.Drawing.Size(92, 92);
            this.knobControl_decay.SmallChange = 1;
            this.knobControl_decay.StartAngle = 135F;
            this.knobControl_decay.TabIndex = 18;
            this.knobControl_decay.Value = 500;
            // 
            // knobControl_sustain
            // 
            this.knobControl_sustain.EndAngle = 405F;
            this.knobControl_sustain.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.knobControl_sustain.ImeMode = System.Windows.Forms.ImeMode.On;
            this.knobControl_sustain.KnobBackColor = System.Drawing.Color.Maroon;
            this.knobControl_sustain.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.line;
            this.knobControl_sustain.LargeChange = 5;
            this.knobControl_sustain.Location = new System.Drawing.Point(36, 173);
            this.knobControl_sustain.Maximum = 1000;
            this.knobControl_sustain.Minimum = 1;
            this.knobControl_sustain.Name = "knobControl_sustain";
            this.knobControl_sustain.PointerColor = System.Drawing.Color.Lavender;
            this.knobControl_sustain.ScaleColor = System.Drawing.Color.Transparent;
            this.knobControl_sustain.ScaleDivisions = 11;
            this.knobControl_sustain.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.knobControl_sustain.ScaleFontAutoSize = false;
            this.knobControl_sustain.ScaleSubDivisions = 4;
            this.knobControl_sustain.ShowLargeScale = false;
            this.knobControl_sustain.ShowSmallScale = false;
            this.knobControl_sustain.Size = new System.Drawing.Size(92, 92);
            this.knobControl_sustain.SmallChange = 1;
            this.knobControl_sustain.StartAngle = 135F;
            this.knobControl_sustain.TabIndex = 17;
            this.knobControl_sustain.Value = 800;
            // 
            // knobControl_attack
            // 
            this.knobControl_attack.EndAngle = 405F;
            this.knobControl_attack.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.knobControl_attack.ImeMode = System.Windows.Forms.ImeMode.On;
            this.knobControl_attack.KnobBackColor = System.Drawing.Color.Maroon;
            this.knobControl_attack.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.line;
            this.knobControl_attack.LargeChange = 5;
            this.knobControl_attack.Location = new System.Drawing.Point(36, 36);
            this.knobControl_attack.Maximum = 1000;
            this.knobControl_attack.Minimum = 1;
            this.knobControl_attack.Name = "knobControl_attack";
            this.knobControl_attack.PointerColor = System.Drawing.Color.Lavender;
            this.knobControl_attack.ScaleColor = System.Drawing.Color.Transparent;
            this.knobControl_attack.ScaleDivisions = 11;
            this.knobControl_attack.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.knobControl_attack.ScaleFontAutoSize = false;
            this.knobControl_attack.ScaleSubDivisions = 4;
            this.knobControl_attack.ShowLargeScale = false;
            this.knobControl_attack.ShowSmallScale = false;
            this.knobControl_attack.Size = new System.Drawing.Size(92, 92);
            this.knobControl_attack.SmallChange = 1;
            this.knobControl_attack.StartAngle = 135F;
            this.knobControl_attack.TabIndex = 16;
            this.knobControl_attack.Value = 500;
            // 
            // button_adsr_set
            // 
            this.button_adsr_set.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button_adsr_set.Location = new System.Drawing.Point(112, 277);
            this.button_adsr_set.Name = "button_adsr_set";
            this.button_adsr_set.Size = new System.Drawing.Size(102, 41);
            this.button_adsr_set.TabIndex = 15;
            this.button_adsr_set.Text = "Set";
            this.button_adsr_set.UseVisualStyleBackColor = true;
            this.button_adsr_set.Click += new System.EventHandler(this.button_adsr_set_Click);
            // 
            // drawbar7
            // 
            this.drawbar7.BackColor = System.Drawing.Color.DimGray;
            this.drawbar7.EndAngle = 405F;
            this.drawbar7.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar7.KnobBackColor = System.Drawing.Color.White;
            this.drawbar7.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar7.LargeChange = 1;
            this.drawbar7.Location = new System.Drawing.Point(262, 210);
            this.drawbar7.Maximum = 8;
            this.drawbar7.Minimum = 0;
            this.drawbar7.MouseWheelBarPartitions = 1;
            this.drawbar7.Name = "drawbar7";
            this.drawbar7.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar7.ScaleColor = System.Drawing.Color.Black;
            this.drawbar7.ScaleDivisions = 9;
            this.drawbar7.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar7.ScaleFontAutoSize = false;
            this.drawbar7.ScaleSubDivisions = 4;
            this.drawbar7.ShowLargeScale = true;
            this.drawbar7.ShowSmallScale = false;
            this.drawbar7.Size = new System.Drawing.Size(122, 122);
            this.drawbar7.SmallChange = 1;
            this.drawbar7.StartAngle = 135F;
            this.drawbar7.TabIndex = 8;
            this.drawbar7.Value = 0;
            // 
            // drawbar8
            // 
            this.drawbar8.BackColor = System.Drawing.Color.DimGray;
            this.drawbar8.EndAngle = 405F;
            this.drawbar8.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar8.KnobBackColor = System.Drawing.Color.White;
            this.drawbar8.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar8.LargeChange = 1;
            this.drawbar8.Location = new System.Drawing.Point(390, 210);
            this.drawbar8.Maximum = 8;
            this.drawbar8.Minimum = 0;
            this.drawbar8.MouseWheelBarPartitions = 1;
            this.drawbar8.Name = "drawbar8";
            this.drawbar8.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar8.ScaleColor = System.Drawing.Color.Black;
            this.drawbar8.ScaleDivisions = 9;
            this.drawbar8.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar8.ScaleFontAutoSize = false;
            this.drawbar8.ScaleSubDivisions = 4;
            this.drawbar8.ShowLargeScale = true;
            this.drawbar8.ShowSmallScale = false;
            this.drawbar8.Size = new System.Drawing.Size(122, 122);
            this.drawbar8.SmallChange = 1;
            this.drawbar8.StartAngle = 135F;
            this.drawbar8.TabIndex = 9;
            this.drawbar8.Value = 0;
            // 
            // drawbar9
            // 
            this.drawbar9.BackColor = System.Drawing.Color.DimGray;
            this.drawbar9.EndAngle = 405F;
            this.drawbar9.ImeMode = System.Windows.Forms.ImeMode.On;
            this.drawbar9.KnobBackColor = System.Drawing.Color.White;
            this.drawbar9.KnobPointerStyle = KnobControl.KnobControl.KnobPointerStyles.circle;
            this.drawbar9.LargeChange = 1;
            this.drawbar9.Location = new System.Drawing.Point(518, 210);
            this.drawbar9.Maximum = 8;
            this.drawbar9.Minimum = 0;
            this.drawbar9.MouseWheelBarPartitions = 1;
            this.drawbar9.Name = "drawbar9";
            this.drawbar9.PointerColor = System.Drawing.Color.MidnightBlue;
            this.drawbar9.ScaleColor = System.Drawing.Color.Black;
            this.drawbar9.ScaleDivisions = 9;
            this.drawbar9.ScaleFont = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.drawbar9.ScaleFontAutoSize = false;
            this.drawbar9.ScaleSubDivisions = 4;
            this.drawbar9.ShowLargeScale = true;
            this.drawbar9.ShowSmallScale = false;
            this.drawbar9.Size = new System.Drawing.Size(122, 122);
            this.drawbar9.SmallChange = 1;
            this.drawbar9.StartAngle = 135F;
            this.drawbar9.TabIndex = 10;
            this.drawbar9.Value = 0;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.ForeColor = System.Drawing.SystemColors.Control;
            this.label8.Location = new System.Drawing.Point(92, 41);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(56, 13);
            this.label8.TabIndex = 11;
            this.label8.Text = "Drawbar 1";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.ForeColor = System.Drawing.SystemColors.Control;
            this.label9.Location = new System.Drawing.Point(218, 41);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(56, 13);
            this.label9.TabIndex = 12;
            this.label9.Text = "Drawbar 2";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.ForeColor = System.Drawing.SystemColors.Control;
            this.label10.Location = new System.Drawing.Point(347, 41);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 13);
            this.label10.TabIndex = 13;
            this.label10.Text = "Drawbar 3";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.SystemColors.Control;
            this.label11.Location = new System.Drawing.Point(475, 41);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(56, 13);
            this.label11.TabIndex = 14;
            this.label11.Text = "Drawbar 4";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.ForeColor = System.Drawing.SystemColors.Control;
            this.label12.Location = new System.Drawing.Point(35, 194);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(56, 13);
            this.label12.TabIndex = 15;
            this.label12.Text = "Drawbar 5";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.ForeColor = System.Drawing.SystemColors.Control;
            this.label13.Location = new System.Drawing.Point(166, 194);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(56, 13);
            this.label13.TabIndex = 16;
            this.label13.Text = "Drawbar 6";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.ForeColor = System.Drawing.SystemColors.Control;
            this.label14.Location = new System.Drawing.Point(294, 194);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(56, 13);
            this.label14.TabIndex = 17;
            this.label14.Text = "Drawbar 7";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.ForeColor = System.Drawing.SystemColors.Control;
            this.label15.Location = new System.Drawing.Point(423, 194);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(56, 13);
            this.label15.TabIndex = 18;
            this.label15.Text = "Drawbar 8";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.ForeColor = System.Drawing.SystemColors.Control;
            this.label16.Location = new System.Drawing.Point(554, 194);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(56, 13);
            this.label16.TabIndex = 19;
            this.label16.Text = "Drawbar 9";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1055, 449);
            this.Controls.Add(this.ADSR);
            this.Controls.Add(this.tabPage_Connection);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tabPage_Connection.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage_subtractive.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_subtractive_freq1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabPage_additive.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage_additive_hammond.ResumeLayout(false);
            this.tabPage_additive_hammond.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_fm_modfreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_fm_modamp)).EndInit();
            this.ADSR.ResumeLayout(false);
            this.ADSR.PerformLayout();
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
        private System.Windows.Forms.GroupBox groupBox1;
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
        private System.Windows.Forms.TabPage tabPage_additive;
        private System.Windows.Forms.Button button_additive_hammond_en;
        private KnobControl.KnobControl drawbar3;
        private KnobControl.KnobControl drawbar2;
        private KnobControl.KnobControl drawbar4;
        private KnobControl.KnobControl drawbar6;
        private KnobControl.KnobControl drawbar5;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage_additive_hammond;
        private KnobControl.KnobControl drawbar1;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button button_fm_en;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox textBox_fm_modfreq;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trackBar_fm_modfreq;
        private System.Windows.Forms.TextBox textBox_fm_modamp;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TrackBar trackBar_fm_modamp;
        private System.Windows.Forms.GroupBox ADSR;
        private System.Windows.Forms.Button button_adsr_set;
        private System.Windows.Forms.Label label_attack_knob;
        private KnobControl.KnobControl knobControl_decay;
        private KnobControl.KnobControl knobControl_sustain;
        private KnobControl.KnobControl knobControl_attack;
        private System.Windows.Forms.Label label_decay_knob;
        private System.Windows.Forms.Label label_release_knob;
        private System.Windows.Forms.Label label_sustain_knob;
        public KnobControl.KnobControl knobControl_release;
        private System.Windows.Forms.Button button4;
        private KnobControl.KnobControl drawbar9;
        private KnobControl.KnobControl drawbar8;
        private KnobControl.KnobControl drawbar7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
    }
}

