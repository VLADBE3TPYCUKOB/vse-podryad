using System.Globalization;
using System.Reflection.Metadata.Ecma335;


//поменять местами соседние слова
public class lab1_7
{
    static void Swap_words(ref string a, ref string b)
    {
        string tmp = a;
        a = b;
        b = tmp;
    }
    static void Main()
    {
        try
        {
            string str;
            StreamReader sr = new StreamReader("C:\\Users\\Kudra\\Desktop\\c# labs\\lab1_7\\input.txt");
            str = sr.ReadLine();
            sr.Close();
            string[] words = str.Split(' ');
            if (words.Length % 2 == 0)
            {
                for (int i = 0; i < words.Length; i += 2)
                {
                    Swap_words(ref words[i], ref words[i + 1]);
                }
            }
            else
            {
                for (int i = 0; i < words.Length - 1; i += 2)
                {
                    Swap_words(ref words[i], ref words[i + 1]);
                }
            }
            StreamWriter sw = new StreamWriter("C:\\Users\\Kudra\\Desktop\\c# labs\\lab1_7\\output.txt");
            for (int i = 0; i < words.Length; i++)
            {
                sw.Write(words[i] + ' ');
            }
            sw.Close();
        }
        catch
        {
            return;
        }
    }
}
