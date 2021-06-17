/*
ID: caleb.h1
LANG: C#
PROG: ride
*/
using System;
using System.IO;
// using System.Threading.Tasks;


public class ride
{
    public static void Main()
    {
        string[] lines = File.ReadAllLines(@"./ride.in");
        uint[] values = new uint[2]{1, 1};
        for (uint i=0; i<2; ++i)
        {
            foreach (char c in lines[i])
            {
                values[i] *= (uint)c - 64;
            }
        }
        File.WriteAllText(@"./ride.out", values[0] % 47 == values[1] % 47 ? "GO\n" : "STAY\n");
    }
}