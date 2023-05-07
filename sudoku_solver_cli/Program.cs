using System;
using System.Text;
using System.IO;
using System.Collections;
using System.Collections.Generic;

namespace cs
{
    class Program
    {
        static private void implementation(string filename)
        {
            Console.WriteLine("Start >> " + filename);
            Solver sudoku = new Solver(filename);
            sudoku.load();
            sudoku.print();
            bool result = sudoku.solve();
            sudoku.print();
            Console.WriteLine(result);
            sudoku.save();
            Console.WriteLine();
        }

        private static void test1()
        {
            HashSet<int> hs = new HashSet<int>();
            SortedSet<int> ss = new SortedSet<int>();
            ss.Add(1);
            hs.UnionWith(ss);
        }

        static void Main(string[] args)
        {
            implementation("input_text.txt");
            implementation("input_text2.txt");
        }
    }
}
