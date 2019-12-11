namespace NetDemo
{
    partial class AddCloudDevice
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
            this.URLText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.OKBtn = new System.Windows.Forms.Button();
            this.UserNameText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.PasswordText = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.CannelBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // URLText
            // 
            this.URLText.Location = new System.Drawing.Point(108, 43);
            this.URLText.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.URLText.Name = "URLText";
            this.URLText.Size = new System.Drawing.Size(179, 22);
            this.URLText.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(33, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 16);
            this.label1.TabIndex = 1;
            this.label1.Text = "URL";
            // 
            // OKBtn
            // 
            this.OKBtn.Location = new System.Drawing.Point(108, 199);
            this.OKBtn.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.OKBtn.Name = "OKBtn";
            this.OKBtn.Size = new System.Drawing.Size(60, 30);
            this.OKBtn.TabIndex = 3;
            this.OKBtn.Text = "OK";
            this.OKBtn.UseVisualStyleBackColor = true;
            this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
            // 
            // UserNameText
            // 
            this.UserNameText.Location = new System.Drawing.Point(108, 91);
            this.UserNameText.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.UserNameText.Name = "UserNameText";
            this.UserNameText.Size = new System.Drawing.Size(179, 22);
            this.UserNameText.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(33, 95);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 16);
            this.label2.TabIndex = 1;
            this.label2.Text = "User Name";
            // 
            // PasswordText
            // 
            this.PasswordText.Location = new System.Drawing.Point(108, 140);
            this.PasswordText.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PasswordText.MaxLength = 64;
            this.PasswordText.Name = "PasswordText";
            this.PasswordText.PasswordChar = '*';
            this.PasswordText.Size = new System.Drawing.Size(179, 22);
            this.PasswordText.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 144);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 16);
            this.label3.TabIndex = 1;
            this.label3.Text = "Password";
            // 
            // CannelBtn
            // 
            this.CannelBtn.Location = new System.Drawing.Point(227, 199);
            this.CannelBtn.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.CannelBtn.Name = "CannelBtn";
            this.CannelBtn.Size = new System.Drawing.Size(60, 30);
            this.CannelBtn.TabIndex = 4;
            this.CannelBtn.Text = "Cannel";
            this.CannelBtn.UseVisualStyleBackColor = true;
            this.CannelBtn.Click += new System.EventHandler(this.CannelBtn_Click);
            // 
            // AddCloudDevice
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(331, 260);
            this.Controls.Add(this.CannelBtn);
            this.Controls.Add(this.OKBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PasswordText);
            this.Controls.Add(this.UserNameText);
            this.Controls.Add(this.URLText);
            this.Font = new System.Drawing.Font("微软雅黑", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddCloudDevice";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Cloud Account";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox URLText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button OKBtn;
        private System.Windows.Forms.TextBox UserNameText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox PasswordText;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button CannelBtn;
    }
}