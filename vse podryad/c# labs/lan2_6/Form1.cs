using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lan2_6
{
    public partial class Form1 : Form
    {
        int matrixsize;
        public Form1()
        {
            InitializeComponent();
        }
        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            matrixsize = trackBar2.Value;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            tableLayoutPanel1.Controls.Clear();
            tableLayoutPanel2.Controls.Clear();
            tableLayoutPanel1.RowCount = matrixsize;
            tableLayoutPanel1.ColumnCount = matrixsize;
            tableLayoutPanel2.RowCount = matrixsize;
            tableLayoutPanel2.ColumnCount = matrixsize;
            FillTable(tableLayoutPanel1);
            FillTable(tableLayoutPanel2);
        }

        private void FillTable(TableLayoutPanel tableLayout)
        {
            for (int i = 0; i < matrixsize; i++)
            {
                for (int j = 0; j < matrixsize; j++)
                {
                    TextBox textBox = new TextBox();
                    tableLayout.Controls.Add(textBox, j, i);
                }
            }
        }

        

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                double[,] matrixA = ReadMatrixFromTable(tableLayoutPanel1);
                double[,] matrixB = ReadMatrixFromTable(tableLayoutPanel2);
                double[,] matrixC = MakeMatrixC(matrixA, matrixB);
                tableLayoutPanel3.Controls.Clear();
                tableLayoutPanel3.RowCount = matrixsize;
                tableLayoutPanel3.ColumnCount = matrixsize;
                DisplayMatrix(matrixC, tableLayoutPanel3);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка: " + ex.Message);
            }
        }
        private double[,] ReadMatrixFromTable(TableLayoutPanel tableLayout)
        {
            double[,] matrix = new double[matrixsize, matrixsize];
            for (int i = 0; i < matrixsize; i++)
            {
                for (int j = 0; j < matrixsize; j++)
                {
                    TextBox textBox = (TextBox)tableLayout.GetControlFromPosition(j, i);
                    if (double.TryParse(textBox.Text, out double value))
                    {
                        matrix[i, j] = value;
                    }
                    else
                    {
                        throw new FormatException("Некорректные данные в таблице.");
                    }
                }
            }
            return matrix;
        }
        private double[,] MakeMatrixC(double[,] matrixA, double[,] matrixB)
        {
            double[,] matrixC = new double[matrixsize, matrixsize];
            for (int i = 0; i < matrixsize; i++)
            {
                for (int j = 0; j < matrixsize; j++)
                {
                    if ((i + j + 2) % 3 == 0) matrixC[i, j] = matrixB[i, j] - matrixA[i, j];
                    if ((i + j + 2) % 3 == 1) matrixC[i, j] = matrixA[i, j] + matrixB[i, j];
                    if ((i + j + 2) % 3 == 2) matrixC[i, j] = matrixA[i, j] - matrixB[i, j];
                }
            }
            return matrixC;
        }
        private void DisplayMatrix(double[,] matrix, TableLayoutPanel tableLayout)
        {
            for (int i = 0; i < matrixsize; i++)
            {
                for (int j = 0; j < matrixsize; j++)
                {
                    TextBox textBox = new TextBox();
                    textBox.Text = matrix[i, j].ToString();
                    textBox.ReadOnly = true;
                    tableLayout.Controls.Add(textBox, j, i);
                }
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
