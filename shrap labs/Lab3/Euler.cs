using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab3
{
    public partial class Euler : Form
    {
        private float scaleFactor = 40.0f;
        private List<PointF> pointsList = new List<PointF>();
        private float r = 2.5f;
        private float a = 2f, b = 3f;
        private List<PointF> GeneratePoints()
        { 
            float step = 0.01f;

            for (float t = 0; t <= 2 * Math.PI; t += step)
            {
                float xCircle = r * (float)Math.Cos(t);
                float yCircle = r * (float)Math.Sin(t);

                if (Math.Pow(xCircle, 2) / 4 + Math.Pow(yCircle, 2) / 9 <= 1 && yCircle>=0)
                {
                    pointsList.Add(new PointF(xCircle * scaleFactor + this.ClientSize.Width / 2, yCircle * scaleFactor + this.ClientSize.Height / 2));
                }
            }

            for (float t = 0; t <= 2 * Math.PI; t += step)
            {

                float xEllipse = a * (float)Math.Cos(t);
                float yEllipse = b * (float)Math.Sin(t);

                if(Math.Pow(xEllipse, 2)+Math.Pow(yEllipse, 2)<=6.25 && xEllipse<=0)
                pointsList.Add(new PointF(xEllipse * scaleFactor + this.ClientSize.Width / 2, yEllipse * scaleFactor + this.ClientSize.Height / 2));
            }

            for (float t = 0; t <= 2 * Math.PI; t += step)
            {
                float xCircle = r * (float)Math.Cos(t);
                float yCircle = r * (float)Math.Sin(t);

                if (Math.Pow(xCircle, 2) / 4 + Math.Pow(yCircle, 2) / 9 <= 1 && yCircle <= 0)
                {
                    pointsList.Add(new PointF(xCircle * scaleFactor + this.ClientSize.Width / 2, yCircle * scaleFactor + this.ClientSize.Height / 2));
                }
            }

            for (float t = (float)(2 * Math.PI); t >= 0; t -= step)
            {

                float xEllipse = a * (float)Math.Cos(t);
                float yEllipse = b * (float)Math.Sin(t);

                if (Math.Pow(xEllipse, 2) + Math.Pow(yEllipse, 2) <= 6.25 && yEllipse>=0 && xEllipse>=0)
                    pointsList.Add(new PointF(xEllipse * scaleFactor + this.ClientSize.Width / 2, yEllipse * scaleFactor + this.ClientSize.Height / 2));
            }
            for (float t = (float)0; t <= (2 * Math.PI); t += step)
            {

                float xEllipse = a * (float)Math.Cos(t);
                float yEllipse = b * (float)Math.Sin(t);

                if (Math.Pow(xEllipse, 2) + Math.Pow(yEllipse, 2) <= 6.25 && yEllipse <= 0 && xEllipse >= 0)
                    pointsList.Add(new PointF(xEllipse * scaleFactor + this.ClientSize.Width / 2, yEllipse * scaleFactor + this.ClientSize.Height / 2));
            }

            return pointsList;
        }


        private void DrawEuler(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            List<PointF> points = GeneratePoints();

            Brush brush = new SolidBrush(Color.White);
            Pen borPen = new Pen(Color.Blue);

            float centerX = this.ClientSize.Width / 2;
            float centerY = this.ClientSize.Height / 2;

            float scaledA = a * scaleFactor;
            float scaledB = b * scaleFactor;
            float scaledRadius = r * scaleFactor;

            Brush ellipseBrush = new SolidBrush(Color.Blue);
            g.FillEllipse(ellipseBrush, centerX - scaledA, centerY - scaledB, 2 * scaledA, 2 * scaledB);

            Brush circleBrush = new SolidBrush(Color.Blue);
            g.FillEllipse(circleBrush, centerX - scaledRadius, centerY - scaledRadius, 2 * scaledRadius, 2 * scaledRadius);

            g.FillPolygon(brush, points.ToArray());

            Pen ellipsePen = new Pen(Color.Black, 3);
            g.DrawEllipse(ellipsePen, centerX - scaledA, centerY - scaledB, 2 * scaledA, 2 * scaledB);

            Pen circlePen = new Pen(Color.Black, 3);
            g.DrawEllipse(circlePen, centerX - scaledRadius, centerY - scaledRadius, 2 * scaledRadius, 2 * scaledRadius);

            brush.Dispose();
        }
        public Euler()
        {
            InitializeComponent();
        }
        public Euler(Menu f)
        {
            this.Text = "Euler";
            this.Size = new Size(800, 600);
            this.Paint += new PaintEventHandler(DrawEuler);
            
        }
    }
}
