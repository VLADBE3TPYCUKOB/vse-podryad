namespace Lab3
{
    partial class Zed_Draw
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private TextBox Zeros;
        private ZedGraph.ZedGraphControl zedGraph;
        private System.Windows.Forms.Label coordLabel;

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
            this.components = new System.ComponentModel.Container();
            this.zedGraph = new ZedGraph.ZedGraphControl();
            this.coordLabel = new System.Windows.Forms.Label();
            this.Zeros = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // zedGraph
            // 
            this.zedGraph.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.zedGraph.Location = new System.Drawing.Point(12, 12);
            this.zedGraph.Name = "zedGraph";
            this.zedGraph.ScrollGrace = 0;
            this.zedGraph.ScrollMaxX = 0;
            this.zedGraph.ScrollMaxY = 0;
            this.zedGraph.ScrollMaxY2 = 0;
            this.zedGraph.ScrollMinX = 0;
            this.zedGraph.ScrollMinY = 0;
            this.zedGraph.ScrollMinY2 = 0;
            this.zedGraph.Size = new System.Drawing.Size(568, 408);
            this.zedGraph.TabIndex = 0;
            this.zedGraph.MouseClick += new System.Windows.Forms.MouseEventHandler(this.zedGraph_MouseClick);
            // 
            // coordLabel
            // 
            this.coordLabel.AutoSize = true;
            this.coordLabel.Location = new System.Drawing.Point(12, 438);
            this.coordLabel.Name = "coordLabel";
            this.coordLabel.Size = new System.Drawing.Size(0, 13);
            this.coordLabel.TabIndex = 1;
            //textbox
            this.Zeros.Location = new System.Drawing.Point(12, 450);
            this.Zeros.Multiline = true;
            this.Zeros.Name = "MouseCoord";
            this.Zeros.ReadOnly = true;
            this.Zeros.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Zeros.Size = new System.Drawing.Size(400, 100);
            this.Zeros.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1000, 600);
            this.Controls.Add(this.coordLabel);
            this.Controls.Add(this.Zeros);
            this.Controls.Add(this.zedGraph);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        
    }
}