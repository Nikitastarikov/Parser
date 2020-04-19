using System;
class Begin
{
    static void Main()
    {
        var array = new int[10]{1, 5, -1, 2, 35, 16, 3, 7, 9, 4};
        int min = array[0];
        int i = 0;
        while(i < 10)
        {
            if(min > array[i])
                min = array[i];
            i = i + 1;
        }
        Console.WriteLine(min);
    }
}