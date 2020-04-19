using System;

class Program
{
    static string LongestCommonSubstring(string a, string b)
    {
        var n = a.Length;
        var m = b.Length;
        var array = new int[n, m];
        var maxValue = 0;
        var maxI = 0;
        int i = 0, j = 0;

        while (i < n)
        {
            j = 0;
            while (j < m)
            {
                
                if (a[i] == b[j])
                {
                    if (i == 0 || j == 0)
                        array[i, j] = 1;
                    else
                        array[i, j] = array[i - 1, j - 1] + 1;
                    
                    if (array[i, j] > maxValue)
                    {
                        maxValue = array[i, j];
                        maxI = i;
                    }
                }
                j++;
            }
            i++;
        }

        return a.Substring(maxI + 1 - maxValue, maxValue);
    }

    static void Main(string[] args)
    {
        Console.Write("First the word: ");
        var s1 = Console.ReadLine();
        Console.Write("Second the word: ");
        var s2 = Console.ReadLine();

        Console.WriteLine("maxsubstring : {0}", LongestCommonSubstring(s1, s2));
        Console.ReadLine();
    }
}
