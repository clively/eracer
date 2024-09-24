namespace eRacerForms
{
	partial class MainForm
	{
		/// <summary>
		///  Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		///  Clean up any resources being used.
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
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			components = new System.ComponentModel.Container();
			tmrUpdateLog = new System.Windows.Forms.Timer(components);
			tableLayoutPanel1 = new TableLayoutPanel();
			LoggingBox = new Support.ScrollingRichTextBox();
			tbCommandList = new TextBox();
			groupBox1 = new GroupBox();
			BtnConnect = new Button();
			BtnSendCommands = new Button();
			label3 = new Label();
			label2 = new Label();
			label1 = new Label();
			TxtRacerName = new TextBox();
			BtnSetName = new Button();
			tableLayoutPanel1.SuspendLayout();
			groupBox1.SuspendLayout();
			SuspendLayout();
			// 
			// tmrUpdateLog
			// 
			tmrUpdateLog.Interval = 1000;
			tmrUpdateLog.Tick += TmrUpdateLog_Tick;
			// 
			// tableLayoutPanel1
			// 
			tableLayoutPanel1.ColumnCount = 2;
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			tableLayoutPanel1.Controls.Add(LoggingBox, 1, 0);
			tableLayoutPanel1.Controls.Add(tbCommandList, 0, 0);
			tableLayoutPanel1.Dock = DockStyle.Bottom;
			tableLayoutPanel1.Location = new Point(0, 198);
			tableLayoutPanel1.Name = "tableLayoutPanel1";
			tableLayoutPanel1.RowCount = 1;
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 20F));
			tableLayoutPanel1.Size = new Size(1264, 422);
			tableLayoutPanel1.TabIndex = 9;
			// 
			// LoggingBox
			// 
			LoggingBox.Dock = DockStyle.Fill;
			LoggingBox.Location = new Point(635, 3);
			LoggingBox.Name = "LoggingBox";
			LoggingBox.Size = new Size(626, 416);
			LoggingBox.TabIndex = 0;
			LoggingBox.Text = "";
			// 
			// tbCommandList
			// 
			tbCommandList.Dock = DockStyle.Fill;
			tbCommandList.Location = new Point(3, 3);
			tbCommandList.Multiline = true;
			tbCommandList.Name = "tbCommandList";
			tbCommandList.Size = new Size(626, 416);
			tbCommandList.TabIndex = 1;
			// 
			// groupBox1
			// 
			groupBox1.Controls.Add(BtnConnect);
			groupBox1.Controls.Add(BtnSendCommands);
			groupBox1.Controls.Add(label3);
			groupBox1.Controls.Add(label2);
			groupBox1.Controls.Add(label1);
			groupBox1.Controls.Add(TxtRacerName);
			groupBox1.Controls.Add(BtnSetName);
			groupBox1.Dock = DockStyle.Top;
			groupBox1.Location = new Point(0, 0);
			groupBox1.Name = "groupBox1";
			groupBox1.Size = new Size(1264, 163);
			groupBox1.TabIndex = 10;
			groupBox1.TabStop = false;
			// 
			// BtnConnect
			// 
			BtnConnect.Location = new Point(1054, 119);
			BtnConnect.Name = "BtnConnect";
			BtnConnect.Size = new Size(112, 34);
			BtnConnect.TabIndex = 15;
			BtnConnect.Text = "Connect";
			BtnConnect.UseVisualStyleBackColor = true;
			BtnConnect.Click += BtnConnect_Click;
			// 
			// BtnSendCommands
			// 
			BtnSendCommands.Location = new Point(253, 120);
			BtnSendCommands.Name = "BtnSendCommands";
			BtnSendCommands.Size = new Size(112, 34);
			BtnSendCommands.TabIndex = 14;
			BtnSendCommands.Text = "Send";
			BtnSendCommands.UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			label3.AutoSize = true;
			label3.Location = new Point(689, 120);
			label3.Name = "label3";
			label3.Size = new Size(181, 25);
			label3.TabIndex = 13;
			label3.Text = "Communications Log";
			// 
			// label2
			// 
			label2.AutoSize = true;
			label2.Location = new Point(56, 125);
			label2.Name = "label2";
			label2.Size = new Size(172, 25);
			label2.TabIndex = 12;
			label2.Text = "Enter Command List";
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Location = new Point(70, 40);
			label1.Name = "label1";
			label1.Size = new Size(107, 25);
			label1.TabIndex = 11;
			label1.Text = "Racer Name";
			// 
			// TxtRacerName
			// 
			TxtRacerName.Location = new Point(299, 37);
			TxtRacerName.Name = "TxtRacerName";
			TxtRacerName.Size = new Size(357, 31);
			TxtRacerName.TabIndex = 10;
			// 
			// BtnSetName
			// 
			BtnSetName.Location = new Point(700, 37);
			BtnSetName.Name = "BtnSetName";
			BtnSetName.Size = new Size(112, 34);
			BtnSetName.TabIndex = 9;
			BtnSetName.Text = "Set Name";
			BtnSetName.UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			AutoScaleDimensions = new SizeF(10F, 25F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(1264, 620);
			Controls.Add(groupBox1);
			Controls.Add(tableLayoutPanel1);
			Name = "MainForm";
			Text = "eRacer Command";
			tableLayoutPanel1.ResumeLayout(false);
			tableLayoutPanel1.PerformLayout();
			groupBox1.ResumeLayout(false);
			groupBox1.PerformLayout();
			ResumeLayout(false);
		}

		#endregion
		private System.Windows.Forms.Timer tmrUpdateLog;
		private TableLayoutPanel tableLayoutPanel1;
		private GroupBox groupBox1;
		private Label label1;
		private TextBox TxtRacerName;
		private Button BtnSetName;
		private Support.ScrollingRichTextBox LoggingBox;
		private TextBox tbCommandList;
		private Label label3;
		private Label label2;
		private Button BtnSendCommands;
		private Button BtnConnect;
	}
}
