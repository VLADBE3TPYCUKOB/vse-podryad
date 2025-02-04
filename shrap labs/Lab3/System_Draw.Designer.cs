namespace Lab3
{
    partial class System_Draw
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private StatusStrip statusStrip;
        private TextBox MouseCoord;
        private TextBox Zeros;

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
        /// 

        private int W = 1000;
        private int H = 650;
        private void InitializeComponent()
        {
            this.MouseCoord = new System.Windows.Forms.TextBox();
            this.Zeros = new System.Windows.Forms.TextBox();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.SuspendLayout();

            //textbox
            this.MouseCoord.Location = new System.Drawing.Point(12, 350);
            this.MouseCoord.Multiline = true;
            this.MouseCoord.Name = "MouseCoord";
            this.MouseCoord.ReadOnly = true;
            this.MouseCoord.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.MouseCoord.Size = new System.Drawing.Size(150, 30);
            this.MouseCoord.TabIndex = 1;
            //textbox
            this.Zeros.Location = new System.Drawing.Point(12, 400);
            this.Zeros.Multiline = true;
            this.Zeros.Name = "MouseCoord";
            this.Zeros.ReadOnly = true;
            this.Zeros.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Zeros.Size = new System.Drawing.Size(400, 100);
            this.Zeros.TabIndex = 1;
            // 
            // statusStrip
            // 
            this.statusStrip.Location = new System.Drawing.Point(0, 450);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(800, 22);
            this.statusStrip.TabIndex = 2;
            this.statusStrip.Text = "statusStrip";
            //Form
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(W, H);
            this.Text = "System_Draw";
            this.Controls.Add(this.MouseCoord);
            this.Controls.Add(this.Zeros);
            this.Controls.Add(this.statusStrip);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        

    }
}