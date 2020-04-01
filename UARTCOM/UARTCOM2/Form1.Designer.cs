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
            this.button_subtractive_en = new System.Windows.Forms.Button();
            this.tabPage_Connection.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage_subtractive.SuspendLayout();
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
            this.tabPage_subtractive.Controls.Add(this.button_subtractive_en);
            this.tabPage_subtractive.Location = new System.Drawing.Point(4, 22);
            this.tabPage_subtractive.Name = "tabPage_subtractive";
            this.tabPage_subtractive.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_subtractive.Size = new System.Drawing.Size(792, 426);
            this.tabPage_subtractive.TabIndex = 1;
            this.tabPage_subtractive.Text = "Subtractive";
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
    }
}

