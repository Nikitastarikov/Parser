using System;
class Begin
{
    static void Main()
    {
        Console.WriteLine(GCD(10, 50));    
    }
    
    static int Min(int x, int y)
    {
        if(x < y) return x;
        else return y;
    }

    static int Max(int x, int y)
    {
        if(x > y) return x;
        else return y;
    }
    
    static int GCD(int a, int b)
    {
        if (a == 0)
        {
            return b;
        }
        else
        {
            int min = Min(a, b);
            int max = Max(a, b);
            //вызываем метод с новыми аргументами
            return GCD(max - min, min);
        }
    }
}
