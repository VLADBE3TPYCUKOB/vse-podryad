using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace Lab3
{
    public partial class System_Draw : Form
    {
        private double epsilon = 0.0001;
        private double f(double x)
        {
            return Math.Asin(2 * x / (1 + x * x));
        }
        private double fDiv(double x)
        {
            return -2 * (x * x - 1) / (Math.Sqrt(x * x * x * x - 2 * (x * x) + 1) * Math.Sqrt(x * x * x * x + 2 * (x * x) + 1));
        }
        private void DrawGraph(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen redPen = new Pen(Color.Red, 3);
            Pen greenPen = new Pen(Color.Green, 3);
            Pen axisPen = new Pen(Color.Black, 1);

            g.DrawLine(axisPen, 0, 200, 500, 200);
            g.DrawLine(axisPen, 250, 0, 250, 400);


            double xmin = Math.PI * -10;
            double xmax = Math.PI * 3.2;
            float prevX = (float)(xmin * 25 + 250);
            float prevY = (float)(-f(xmin) * 40 + 200);
            for (double x = xmin+0.01; x <= xmax; x += 0.01)
            {
                float currX = (float)(x*25+250);
                float currY = (float)(-f(x)*40+200);
                
                g.DrawLine(redPen, currX, currY, prevX, prevY);
                prevX = currX;
                prevY = currY;
            }
            

            prevX = (float)(xmin * 25 + 250);
            prevY = (float)(-fDiv(xmin) * 40 + 200);
            for (double x = xmin; x <= xmax; x += 0.01)
            {
                float currX = (float)(x * 25 + 250);
                float currY = (float)(-fDiv(x) * 40 + 200);
                
                g.DrawLine(greenPen, currX, currY, prevX, prevY);
                prevX = currX;
                prevY = currY;
            }
            
        }
        private void System_draw_MouseMove(object sender, MouseEventArgs e)
        {
            double x = (e.X - 250) / 25.0;
            double y = (200 - e.Y) / 40.0;
            if (x >= -10 && x <= 10 && y >= -10 && y <= 10)
            {
                MouseCoord.Clear();
                MouseCoord.AppendText($"X: {x:F2}, Y: {y:F2}");
            }
        }
        public System_Draw()
        {
            InitializeComponent();
        }
        public System_Draw(Menu f)
        {
            InitializeComponent();
            Zeros.AppendText("Zeros: 0 \r\n" + Environment.NewLine);
            Zeros.AppendText("Zeros of the derivative: -1, 1");
            this.Paint += new PaintEventHandler(DrawGraph);
            this.MouseMove += new MouseEventHandler(System_draw_MouseMove);
        }
    }
}
