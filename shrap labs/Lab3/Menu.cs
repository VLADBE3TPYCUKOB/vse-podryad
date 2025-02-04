using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.DataFormats;

namespace Lab3
{
    public partial class Menu : Form
    {
        private void InitializeMyButton()
        {
            Button button1 = new Button();
            button1.DialogResult = DialogResult.OK;
            button1.Text = "ZedGraph Drawing";
            button1.AutoSize = true;
            button1.Location = new Point(325, 120);
            button1.Click += new System.EventHandler(this.button1_Click);
            Controls.Add(button1);
            Button button2 = new Button();
            button2.DialogResult = DialogResult.OK;
            button2.Text = "System Drawing";
            button2.AutoSize = true;
            button2.Location = new Point(335, 180);
            button2.Click += new System.EventHandler(this.button2_Click);
            Controls.Add(button2);
            Button button3 = new Button();
            button3.DialogResult = DialogResult.OK;
            button3.Text = "Euler diagram";
            button3.AutoSize = true;
            button3.Location = new Point(343, 240);
            button3.Click += new System.EventHandler(this.button3_Click);
            Controls.Add(button3);
        }
        public Menu()
        {
            InitializeComponent();
            InitializeMyButton();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Zed_Draw newForm = new Zed_Draw(this);
            newForm.Show();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            System_Draw newForm = new System_Draw(this);
            newForm.Show();
        }
        private void button3_Click(object sender, EventArgs e)
        {
            Euler newForm = new Euler(this);
            newForm.Show();
        }
    }
}
