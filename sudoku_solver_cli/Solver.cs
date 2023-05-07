using System;
using System.Text;
using System.IO;
using System.Collections;
using System.Collections.Generic;

namespace cs
{
    class Solver
    {
        private int size = 9;
        private string filePath;
        private int[][] numbers;
        private string resultFilePath;

        public Solver(string filePath)
        {
            this.numbers = new int[size][];
            for (int i = 0; i < this.numbers.Length; i++)
            {
                this.numbers[i] = new int[size];
            }
            this.filePath = filePath;
            this.resultFilePath = "solved_sudoku.txt";
        }
        
        ~Solver()
        {

        }

        public bool solve()
        {
            if (this.checkValidity() == true)
            {
                Console.WriteLine("Solving sudoku...");
                return this.solveSudoku();
            }
            else
            {
                Console.WriteLine("Not valid input...");
                return false;
            }
        }

        private bool solveSudoku()
        {
            int row = -1;
            int column = -1;
            bool isEmpty = true;

            for (int y = 0; y < this.size; y++)
            {
                for (int x = 0; x < this.size; x++)
                {
                    if (this.numbers[y][x] == 0)
                    {
                        row = y;
                        column = x;
                        
                        isEmpty = false;
                        break;
                    }
                }

                if (isEmpty == false)
                {
                    break;
                }
            }

            if (isEmpty == true)
            {
                return true;
            }

            var safeNumbers = this.getUnusedNumbers(row, column);
            foreach (var safeNum in safeNumbers)
            {
                this.set(row, column, safeNum);
                if (this.solveSudoku())
                {
                    return true;
                }
                else
                {
                    this.set(row, column, 0);
                }
            }

            return false;
        }

        /*--------------------------------------------------------------*/

        private bool checkValidity()
        {
            for (int i = 0; i < this.size; i++)
            {
                if (this.checkLine(i) == false)
                    return false;
                if (this.checkColumn(i) == false)
                    return false;
            }

            for (int i = 0; i <= 6; i += 3)
            {
                for (int j = 0; j <= 6; j += 3)
                {
                    if (this.checkRect(i, j) == false)
                        return false;
                }
            }

            return true;
        }

        private bool checkLine(int id)
        {
            if (id < 0 || id >= this.size)
                return false;

            var line = new SortedSet<int>();
            for (int i = 0; i < this.size; i++)
            {
                if (this.numbers[id][i] == 0)
                {
                    continue;
                }

                if (line.Contains(this.numbers[id][i]) == true)
                {
                    return false;
                }
                else
                {
                    line.Add(this.numbers[id][i]);
                }
            }    

            return true;
        }

        private bool checkColumn(int id)
        {
            if (id < 0 || id >= this.size)
                return false;

            var line = new SortedSet<int>();
            for (int i = 0; i < this.size; i++)
            {
                if (this.numbers[i][id] == 0)
                {
                    continue;
                }

                if (line.Contains(this.numbers[i][id]) == true)
                {
                    return false;
                }
                else
                {
                    line.Add(this.numbers[i][id]);
                }
            }    

            return true;
        }

        private bool checkRect(int y, int x)
        {
            if (x < 0 || y < 0 || x >= 9 || y >= 9)
                return false;

            var line = new SortedSet<int>();
            int minY = y / 3;
            minY *= 3;
            for (int i = minY; i < minY + 3; i++)
            {
                int minX = x / 3;
                minX *= 3;
                for (int j = minX; j < minX + 3; j++)
                {
                    if (this.numbers[i][j] == 0)
                    {
                        continue;
                    }

                    if (line.Contains(this.numbers[i][j]) == true)
                    {
                        return false;
                    }
                    else
                    {
                        line.Add(this.numbers[i][j]);
                    }
                }
            }

            return true;
        }

        /*--------------------------------------------------------------*/

        private SortedSet<int> getUnusedNumbers(int y, int x)
        {
            SortedSet<int> used = getUsedNumbers(y, x);
            SortedSet<int> unused = new SortedSet<int>();
            
            for (int i = 1; i < 10; i++)
            {
                if (used.Contains(i) == false)
                {
                    unused.Add(i);
                }
            }

            return unused;
        }

        private SortedSet<int> getUsedNumbers(int y, int x)
        {
            var line = this.getLine(y);
            var row = this.getColumn(x);
            var rect = this.getRect(y,x);

            SortedSet<int> set = new SortedSet<int>();
            set.UnionWith(line);
            set.UnionWith(row);
            set.UnionWith(rect);

            return set;
        }

        private SortedSet<int> getLine(int id)
        {
            var line = new SortedSet<int>();
            if (!(id < 0 || id >= this.size))
            {
                for (int i = 0; i < this.size; i++)
                {
                    line.Add(this.numbers[id][i]);
                }    
            }

            return line;
        }

        private SortedSet<int> getColumn(int id)
        {
            var line = new SortedSet<int>();
            if (!(id < 0 || id >= this.size))
            {
                for (int i = 0; i < this.size; i++)
                {
                    line.Add(this.numbers[i][id]);
                }
            }

            return line;
        }

        private SortedSet<int> getRect(int y, int x)
        {
            var line = new SortedSet<int>();
            if (!(x < 0 || y < 0 || x >= 9 || y >= 9))
            {
                int minY = y / 3;
                minY *= 3;
                for (int i = minY; i < minY + 3; i++)
                {
                    int minX = x / 3;
                    minX *= 3;
                    for (int j = minX; j < minX + 3; j++)
                    {
                        line.Add(this.numbers[i][j]);
                    }
                }
            }
            return line;
        }

        public int get(int y, int x)
        {
            if (y < 0 || x < 0 || y >= size || x >= size)
            {
                return -1;
            }
            else
            {
                return numbers[y][x];
            }
        }

        public void set(int y, int x, int val)
        {
            if (val < 0 || val > 9) return;

            if (!(y < 0 || x < 0 || y >= size || x >= size))
            {
                numbers[y][x] = val;
            }
        }

        public void load()
        {
            Console.WriteLine("Loading data...");
            
            string[] lines = System.IO.File.ReadAllLines(this.filePath);
            for (int i = 0; i < this.size; i++)
            {
                for (int j = 0; j < this.size; j++)
                {
                    if (lines[i][j] >= '0' && lines[i][j] <= '9')
                    {
                        this.numbers[i][j] = lines[i][j] - '0';
                    }
                }
            }
        }

        public void save()
        {
            Console.WriteLine("Saving data...");

            var stringBuilder = new StringBuilder();
            for (int i = 0; i < this.numbers.Length; i++)
            {
                for (int j = 0; j < this.numbers[i].Length; j++)
                {
                    stringBuilder.Append(this.numbers[i][j].ToString());
                }
                stringBuilder.Append("\n");
            }

            File.WriteAllText(this.resultFilePath, stringBuilder.ToString());
        }

        public void print()
        {
            for (int i = 0; i < this.numbers.Length; i++)
            {
                for (int j = 0; j < this.numbers[0].Length; j++)
                {
                    Console.Write(this.numbers[i][j] + " ");
                }
                Console.WriteLine();
            }
        }

        private void printLine(SortedSet<int> line)
        {
            Console.Write("[ ");
            foreach (var item in line)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine("]");
        }
    }
}
